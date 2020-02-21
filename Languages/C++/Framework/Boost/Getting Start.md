# [1  Get Boost](https://www.boost.org/doc/libs/1_71_0/more/getting_started/unix-variants.html#id20)

1. Download [`boost_1_71_0``.tar.bz2`](https://www.boost.org/users/history/version_1_71_0.html).

2. In the directory where you want to put the Boost installation, execute

   ```
   tar --bzip2 -xf /path/to/boost_1_71_0.tar.bz2
   ```

# [2  The Boost Distribution](https://www.boost.org/doc/libs/1_71_0/more/getting_started/unix-variants.html#id21)

This is a sketch of the resulting directory structure:

```
boost_1_71_0/ .................The “boost root directory”
   index.htm .........A copy of www.boost.org starts here
   boost/ .........................All Boost Header files
    
   libs/ ............Tests, .cpps, docs, etc., by library
     index.html ........Library documentation starts here
     algorithm/
     any/
     array/
                     …more libraries…
   status/ .........................Boost-wide test suite
   tools/ ...........Utilities, e.g. Boost.Build, quickbook, bcp
   more/ ..........................Policy documents, etc.
   doc/ ...............A subset of all Boost library docs
```

# [3  Header-Only Libraries](https://www.boost.org/doc/libs/1_71_0/more/getting_started/unix-variants.html#id22)

The first thing many people want to know is, “how do I build Boost?” The good news is that often, there's nothing to build.

Nothing to Build?

Most Boost libraries are **header-only**: they consist *entirely of header files* containing templates and inline functions, and require no separately-compiled library binaries or special treatment when linking.

The only Boost libraries that *must* be built separately are:

- [Boost.Chrono](https://www.boost.org/doc/libs/1_71_0/libs/chrono/index.html)
- [Boost.Context](https://www.boost.org/doc/libs/1_71_0/libs/context/index.html)
- [Boost.Filesystem](https://www.boost.org/doc/libs/1_71_0/libs/filesystem/index.html)
- [Boost.GraphParallel](https://www.boost.org/doc/libs/1_71_0/libs/graph_parallel/index.html)
- [Boost.IOStreams](https://www.boost.org/doc/libs/1_71_0/libs/iostreams/index.html)
- [Boost.Locale](https://www.boost.org/doc/libs/1_71_0/libs/locale/index.html)
- [Boost.Log](https://www.boost.org/doc/libs/1_71_0/libs/log/index.html) (see [build documentation](https://www.boost.org/doc/libs/1_71_0/libs/log/doc/html/log/installation/config.html))
- [Boost.MPI](https://www.boost.org/doc/libs/1_71_0/libs/mpi/index.html)
- [Boost.ProgramOptions](https://www.boost.org/doc/libs/1_71_0/libs/program_options/index.html)
- [Boost.Python](https://www.boost.org/doc/libs/1_71_0/libs/python/doc/html/building.html) (see the [Boost.Python build documentation](https://www.boost.org/doc/libs/1_71_0/libs/python/doc/html/building.html) before building and installing it)
- [Boost.Regex](https://www.boost.org/doc/libs/1_71_0/libs/regex/index.html)
- [Boost.Serialization](https://www.boost.org/doc/libs/1_71_0/libs/serialization/index.html)
- [Boost.Signals](https://www.boost.org/doc/libs/1_71_0/libs/signals/index.html)
- [Boost.Thread](https://www.boost.org/doc/libs/1_71_0/libs/thread/index.html)
- [Boost.Timer](https://www.boost.org/doc/libs/1_71_0/libs/timer/index.html)
- [Boost.Wave](https://www.boost.org/doc/libs/1_71_0/libs/wave/index.html)

A few libraries have optional separately-compiled binaries:

- [Boost.DateTime](https://www.boost.org/doc/libs/1_71_0/libs/date_time/index.html) has a binary component that is only needed if you're using its `to_string`/`from_string` or serialization features, or if you're targeting Visual C++ 6.x or Borland.
- [Boost.Graph](https://www.boost.org/doc/libs/1_71_0/libs/graph/index.html) also has a binary component that is only needed if you intend to [parse GraphViz files](https://www.boost.org/doc/libs/1_71_0/libs/graph/doc/read_graphviz.html).
- [Boost.Math](https://www.boost.org/doc/libs/1_71_0/libs/math/index.html) has binary components for the TR1 and C99 cmath functions.
- [Boost.Random](https://www.boost.org/doc/libs/1_71_0/libs/random/index.html) has a binary component which is only needed if you're using `random_device`.
- [Boost.Test](https://www.boost.org/doc/libs/1_71_0/libs/test/index.html) can be used in “header-only” or “separately compiled” mode, although **separate compilation is recommended for serious use**.
- [Boost.Exception](https://www.boost.org/doc/libs/1_71_0/libs/exception/index.html) provides non-intrusive implementation of exception_ptr for 32-bit _MSC_VER==1310 and _MSC_VER==1400 which requires a separately-compiled binary. This is enabled by #define BOOST_ENABLE_NON_INTRUSIVE_EXCEPTION_PTR.
- [Boost.System](https://www.boost.org/doc/libs/1_71_0/libs/system/index.html) is header-only since Boost 1.69. A stub library is still built for compatibility, but linking to it is no longer necessary.



# [4  Build a Simple Program Using Boost](https://www.boost.org/doc/libs/1_71_0/more/getting_started/unix-variants.html#id23)

To keep things simple, let's start by using a header-only library. The following program reads a sequence of integers from standard input, uses Boost.Lambda to multiply each number by three, and writes them to standard output:

```c++
#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>

int main()
{
    using namespace boost::lambda;
    typedef std::istream_iterator<int> in;

    std::for_each(
        in(std::cin), in(), std::cout << (_1 * 3) << " " );
}
```

Copy the text of this program into a file called `example.cpp`.

Now, in the directory where you saved `example.cpp`, issue the following command:

```shell
c++ -I path/to/boost_1_71_0 example.cpp -o example
```

To test the result, type:

```shell
echo 1 2 3 | ./example
```



# [6  Link Your Program to a Boost Library](https://www.boost.org/doc/libs/1_71_0/more/getting_started/unix-variants.html#id34)

To demonstrate linking with a Boost binary library, we'll use the following simple program that extracts the subject lines from emails. It uses the [Boost.Regex](https://www.boost.org/doc/libs/1_71_0/libs/regex/index.html) library, which has a separately-compiled binary component.

```c++
#include <boost/regex.hpp>
#include <iostream>
#include <string>

int main()
{
    std::string line;
    boost::regex pat( "^Subject: (Re: |Aw: )*(.*)" );

    while (std::cin)
    {
        std::getline(std::cin, line);
        boost::smatch matches;
        if (boost::regex_match(line, matches, pat))
            std::cout << matches[2] << std::endl;
    }
}
```

There are two main challenges associated with linking:

1. Tool configuration, e.g. choosing command-line options or IDE build settings.
2. Identifying the library binary, among all the build variants, whose compile configuration is compatible with the rest of your project.

There are two main ways to link to libraries:

1. You can specify the full path to each library:

   ```shell
   $ c++ -I path/to/boost_1_71_0 example.cpp -o example \
      ~/boost/stage/lib/libboost_regex-gcc34-mt-d-1_36.a
   ```

2. You can separately specify a directory to search (with `-L`*directory*) and a library name to search for (with `-l`*library*,[2](https://www.boost.org/doc/libs/1_71_0/more/getting_started/unix-variants.html#lowercase-l) dropping the filename's leading `lib` and trailing suffix (`.a` in this case):

   ```shell
   $ c++ -I path/to/boost_1_71_0 example.cpp -o example \
      -L~/boost/stage/lib/ -lboost_regex-gcc34-mt-d-1_36
   ```

   As you can see, this method is just as terse as method A for one library; it *really* pays off when you're using multiple libraries from the same directory. Note, however, that if you use this method with a library that has both static (`.a`) and dynamic (`.so`) builds, the system may choose one automatically for you unless you pass a special option such as `-static` on the command line.

In both cases above, the bold text is what you'd add to [the command lines we explored earlier](https://www.boost.org/doc/libs/1_71_0/more/getting_started/unix-variants.html#build-a-simple-program-using-boost).



## [6.1  Library Naming](https://www.boost.org/doc/libs/1_71_0/more/getting_started/unix-variants.html#id35)

libboost_regex-vc71-mt-d-x86-1_34.lib

* lib:*Prefix*
* boost_regex: library name
* vc71:*Toolset tag*: identifies the [toolset](https://www.boost.org/doc/libs/1_71_0/more/getting_started/unix-variants.html#toolset) and version used to build the binary.
* mt:Threading tag: indicates that the library was built with multithreading support enabled
* d:ABI tag
* x86:*Architecture and address model tag*:
  * x: x86-32, x86-64
  * a:ARM
* 1_34:*Version tag*: the full Boost release number
* .lib:*Extension*