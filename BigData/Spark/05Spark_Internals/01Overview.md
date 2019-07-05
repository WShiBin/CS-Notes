[TOC]

**1.Spark Submit任务提交**

**2.Driver的注册与启动**

**3.SparkContext的初始化**

**4.TaskScheduler的创建和启动**

**5.Application的注册**

**6.Master注册机制-Application的注册与Application的调度算法**

**7.Spark源码阅读:Executor的启动**

**8.CoarseGrainedExecutorBackend的启动**

**9.DAGScheduler源码分析**

**10.DAGScheduler Stage划分与Task最佳位置计算**

**11.TaskScheduler调度算法与调度池**

**12.TaskScheduler任务提交与资源分配**

**13.Task的启动**

**14.Task的结果处理**



* 集群启动start-all.sh. Master-Worker通信
* 任务提交Spark-submit
* SparkContext
* Driver启动
  * DAGScheduler
  * TaskScheduler
  * SparkUI
* Executor
* Job
* BlockManagerMaster-BlockManager
* Shuffle
* Checkpoint





## 任务提交Spark-submit

```shell
> bin/spark-submit \
--class org.apache.spark.examples.SparkPi \
--master spark://hadoop102:7077 \
--executor-memory 1G \
--total-executor-cores 2
```

bin/spark-submit

```shell
#!/usr/bin/env bash

if [ -z "${SPARK_HOME}" ]; then
  source "$(dirname "$0")"/find-spark-home
fi

# disable randomized hash for string in Python 3.3+
export PYTHONHASHSEED=0

exec "${SPARK_HOME}"/bin/spark-class org.apache.spark.deploy.SparkSubmit "$@"
```

bin/spark-class

```shell
#!/usr/bin/env bash

if [ -z "${SPARK_HOME}" ]; then
  source "$(dirname "$0")"/find-spark-home
fi

. "${SPARK_HOME}"/bin/load-spark-env.sh

# Find the java binary
if [ -n "${JAVA_HOME}" ]; then
  RUNNER="${JAVA_HOME}/bin/java"
else
  if [ "$(command -v java)" ]; then
    RUNNER="java"
  else
    echo "JAVA_HOME is not set" >&2
    exit 1
  fi
fi

# Find Spark jars.
if [ -d "${SPARK_HOME}/jars" ]; then
  SPARK_JARS_DIR="${SPARK_HOME}/jars"
else
  SPARK_JARS_DIR="${SPARK_HOME}/assembly/target/scala-$SPARK_SCALA_VERSION/jars"
fi

if [ ! -d "$SPARK_JARS_DIR" ] && [ -z "$SPARK_TESTING$SPARK_SQL_TESTING" ]; then
  echo "Failed to find Spark jars directory ($SPARK_JARS_DIR)." 1>&2
  echo "You need to build Spark with the target \"package\" before running this program." 1>&2
  exit 1
else
  LAUNCH_CLASSPATH="$SPARK_JARS_DIR/*"
fi

# Add the launcher build dir to the classpath if requested.
if [ -n "$SPARK_PREPEND_CLASSES" ]; then
  LAUNCH_CLASSPATH="${SPARK_HOME}/launcher/target/scala-$SPARK_SCALA_VERSION/classes:$LAUNCH_CLASSPATH"
fi

# For tests
if [[ -n "$SPARK_TESTING" ]]; then
  unset YARN_CONF_DIR
  unset HADOOP_CONF_DIR
fi

# The launcher library will print arguments separated by a NULL character, to allow arguments with
# characters that would be otherwise interpreted by the shell. Read that in a while loop, populating
# an array that will be used to exec the final command.
#
# The exit code of the launcher is appended to the output, so the parent shell removes it from the
# command array and checks the value to see if the launcher succeeded.
build_command() {
  "$RUNNER" -Xmx128m -cp "$LAUNCH_CLASSPATH" org.apache.spark.launcher.Main "$@"
  printf "%d\0" $?
}

# Turn off posix mode since it does not allow process substitution
set +o posix
CMD=()
while IFS= read -d '' -r ARG; do
  CMD+=("$ARG")
done < <(build_command "$@")

COUNT=${#CMD[@]}
LAST=$((COUNT - 1))
LAUNCHER_EXIT_CODE=${CMD[$LAST]}

# Certain JVM failures result in errors being printed to stdout (instead of stderr), which causes
# the code that parses the output of the launcher to get confused. In those cases, check if the
# exit code is an integer, and if it's not, handle it as a special error case.
if ! [[ $LAUNCHER_EXIT_CODE =~ ^[0-9]+$ ]]; then
  echo "${CMD[@]}" | head -n-1 1>&2
  exit 1
fi

if [ $LAUNCHER_EXIT_CODE != 0 ]; then
  exit $LAUNCHER_EXIT_CODE
fi

CMD=("${CMD[@]:0:$LAST}")
exec "${CMD[@]}"
```



org.apache.spark.deploy.SparkSubmit.scala

```scala
  def main(args: Array[String]): Unit = {
    val appArgs = new SparkSubmitArguments(args)
    if (appArgs.verbose) {
      // scalastyle:off println
      printStream.println(appArgs)
      // scalastyle:on println
    }
    appArgs.action match {
      // submit
      case SparkSubmitAction.SUBMIT => submit(appArgs)
      case SparkSubmitAction.KILL => kill(appArgs)
      case SparkSubmitAction.REQUEST_STATUS => requestStatus(appArgs)
    }
  }

  @tailrec
  private def submit(args: SparkSubmitArguments): Unit = {
    val (childArgs, childClasspath, sysProps, childMainClass) = prepareSubmitEnvironment(args)

    def doRunMain(): Unit = {
      if (args.proxyUser != null) {
        val proxyUser = UserGroupInformation.createProxyUser(args.proxyUser,
          UserGroupInformation.getCurrentUser())
        try {
          proxyUser.doAs(new PrivilegedExceptionAction[Unit]() {
            override def run(): Unit = {
              runMain(childArgs, childClasspath, sysProps, childMainClass, args.verbose)
            }
          })
        } catch {
          case e: Exception =>
            // Hadoop's AuthorizationException suppresses the exception's stack trace, which
            // makes the message printed to the output by the JVM not very helpful. Instead,
            // detect exceptions with empty stack traces here, and treat them differently.
            if (e.getStackTrace().length == 0) {
              // scalastyle:off println
              printStream.println(s"ERROR: ${e.getClass().getName()}: ${e.getMessage()}")
              // scalastyle:on println
              exitFn(1)
            } else {
              throw e
            }
        }
      } else {
        runMain(childArgs, childClasspath, sysProps, childMainClass, args.verbose)
      }
    }

     // In standalone cluster mode, there are two submission gateways:
     //   (1) The traditional RPC gateway using o.a.s.deploy.Client as a wrapper
     //   (2) The new REST-based gateway introduced in Spark 1.3
     // The latter is the default behavior as of Spark 1.3, but Spark submit will fail over
     // to use the legacy gateway if the master endpoint turns out to be not a REST server.
    if (args.isStandaloneCluster && args.useRest) {
      try {
        // scalastyle:off println
        printStream.println("Running Spark using the REST application submission protocol.")
        // scalastyle:on println
        doRunMain()
      } catch {
        // Fail over to use the legacy submission gateway
        case e: SubmitRestConnectionException =>
          printWarning(s"Master endpoint ${args.master} was not a REST server. " +
            "Falling back to legacy submission gateway instead.")
          args.useRest = false
          submit(args)
      }
    // In all other modes, just run the main class as prepared
    } else {
      doRunMain()
    }
  }

  private def runMain(
      childArgs: Seq[String],
      childClasspath: Seq[String],
      sysProps: Map[String, String],
      childMainClass: String,
      verbose: Boolean): Unit = {
    // scalastyle:off println
    if (verbose) {
      printStream.println(s"Main class:\n$childMainClass")
      printStream.println(s"Arguments:\n${childArgs.mkString("\n")}")
      printStream.println(s"System properties:\n${sysProps.mkString("\n")}")
      printStream.println(s"Classpath elements:\n${childClasspath.mkString("\n")}")
      printStream.println("\n")
    }
    // scalastyle:on println

    val loader =
      if (sysProps.getOrElse("spark.driver.userClassPathFirst", "false").toBoolean) {
        new ChildFirstURLClassLoader(new Array[URL](0),
          Thread.currentThread.getContextClassLoader)
      } else {
        new MutableURLClassLoader(new Array[URL](0),
          Thread.currentThread.getContextClassLoader)
      }
    Thread.currentThread.setContextClassLoader(loader)

    for (jar <- childClasspath) {
      addJarToClasspath(jar, loader)
    }

    for ((key, value) <- sysProps) {
      System.setProperty(key, value)
    }

    var mainClass: Class[_] = null

    try {
      mainClass = Utils.classForName(childMainClass)
    } catch {
      case e: ClassNotFoundException =>
        e.printStackTrace(printStream)
        if (childMainClass.contains("thriftserver")) {
          // scalastyle:off println
          printStream.println(s"Failed to load main class $childMainClass.")
          printStream.println("You need to build Spark with -Phive and -Phive-thriftserver.")
          // scalastyle:on println
        }
        System.exit(CLASS_NOT_FOUND_EXIT_STATUS)
      case e: NoClassDefFoundError =>
        e.printStackTrace(printStream)
        if (e.getMessage.contains("org/apache/hadoop/hive")) {
          // scalastyle:off println
          printStream.println(s"Failed to load hive class.")
          printStream.println("You need to build Spark with -Phive and -Phive-thriftserver.")
          // scalastyle:on println
        }
        System.exit(CLASS_NOT_FOUND_EXIT_STATUS)
    }

    // SPARK-4170
    if (classOf[scala.App].isAssignableFrom(mainClass)) {
      printWarning("Subclasses of scala.App may not work correctly. Use a main() method instead.")
    }

    val mainMethod = mainClass.getMethod("main", new Array[String](0).getClass)
    if (!Modifier.isStatic(mainMethod.getModifiers)) {
      throw new IllegalStateException("The main method in the given main class must be static")
    }

    @tailrec
    def findCause(t: Throwable): Throwable = t match {
      case e: UndeclaredThrowableException =>
        if (e.getCause() != null) findCause(e.getCause()) else e
      case e: InvocationTargetException =>
        if (e.getCause() != null) findCause(e.getCause()) else e
      case e: Throwable =>
        e
    }

    try {
      // 调用 --class org.apache.spark.examples.SparkPi 的main方法
      mainMethod.invoke(null, childArgs.toArray)
    } catch {
      case t: Throwable =>
        findCause(t) match {
          case SparkUserAppException(exitCode) =>
            System.exit(exitCode)

          case t: Throwable =>
            throw t
        }
    }
  }
```

WordCount.scala

```scala
package com.ishibin.basic

import org.apache.spark.rdd.RDD
import org.apache.spark.{SparkConf, SparkContext}

object WordCountApp {

    def main(args: Array[String]): Unit = {
        val sparkConf: SparkConf = new SparkConf()
            .setMaster("local[*]")
            .setAppName(this.getClass.getSimpleName)
        val sparkContext = new SparkContext(sparkConf)

        //sparkContext.textFile("/Users/ben/WorkSpace/LearnSpark/SparkBasics/src/main/scala/com/ishibin/WordCountApp.scala")
        val rdd: RDD[(String, Int)] = sparkContext.textFile("hdfs://shibins-mbp:9000/Spark_Basic.md")
            .flatMap(_.split("\\W+"))
            .map((_, 1))
            .reduceByKey(_ + _)
        val r1: RDD[(String, Int)] = rdd.cache()
        //.cogroup(null)
        //.foreach(println)
        r1.foreach(println)
    }

}
```



SparkConf

new SparkContext

​	SparkContext.createTaskScheduler(this, master, deployMode)

​	_dagScheduler = new DAGScheduler(this)

​	SparkUI

SparkEnv

​	createSparkEnv(_conf, isLocal, listenerBus)

​		createExecutorEnv

rdd.foreach(println)

​	sparkContext.runjob

​		DAGScheduler:runjob

​			submitJob(rdd, func, partitions, callSite, resultHandler, properties)

​				eventProcessLoop.post(JobSubmitted())

​					DAGSchedulerEventProcessLoop:onReceive():doOnReceive()

​						dagScheduler.handleJobSubmitted(jobId, rdd, func, partitions, callSite, listener, properties)

​							finalStage = createResultStage(finalRDD, func, partitions, jobId, callSite)

​							submitStage(stage: Stage)

​								val missing: List[Stage] = getMissingParentStages(stage).sortBy(_.id) 宽窄依赖划分

​									getOrCreateShuffleMapStage(shufDep, stage.firstJobId)

​										createShuffleMapStage(shuffleDep, firstJobId)

​											val stage = new ShuffleMapStage()

​								submitMissingTasks(stage, jobId.get)

​								taskScheduler.submitTasks(new TaskSet())

​									TaskSchedulerImpl:backend.reviveOffers()

​										CoarseGrainedSchedulerBackend:driverEndpoint.send(ReviveOffers)

​										CoarseGrainedExecutorBackend:receive()—>case LaunchTask(data)

​											executor.launchTask(this, taskId, attemptNumber,name, serializedTask)

​											Executor:**TaskRunner**:run()

​												Task:task.run(taskId, attemptNumber, env.metricsSystem)

​													runTask(context):ResultTask/ShuffleMapTask

​														rdd.iterator(partition, context)—>computeOrReadCheckpoint()

​														MapPartition:compute(split, context)

​														



```scala
    val tr = new TaskRunner(context, taskId, attemptNumber, taskName,serializedTask)
    runningTasks.put(taskId, tr)
    threadPool.execute(tr)
```



SparkSubmit:main()

—> submit(args: SparkSubmitArguments)

—> doRunMain()

—> runMain(childArgs, childClasspath, sysProps, childMainClass, args.verbose)

—> mainMethod.invoke(null, childArgs.toArray) Client:main()

​										

​													



