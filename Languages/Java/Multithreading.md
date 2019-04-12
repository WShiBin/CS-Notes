## 实现方式

* 继承 Thread
* 实现 Runnable
* 用 Callable(有返回值)

```java
public class CallableTest {
	public static void main(String[] args) throws ExecutionException, InterruptedException {
		
		Callable<String> callable = new Callable<String>() {
			@Override
			public String call() throws Exception {
				Thread.sleep(3000);
				System.out.println("hello");
				return "hello";
			}
		};
		
		FutureTask<String> futureTask = new FutureTask<String>(callable);

		new Thread(futureTask).start();

		String str = futureTask.get();
		System.out.println(str);
	}
}
```



## 线程状态

## 线程通信

* synchronized
* ReentrantLock
  * ReentrantReadWriteLock.ReadLock
  * ReentrantReadWriteLock.WriteLock



## 线程池

