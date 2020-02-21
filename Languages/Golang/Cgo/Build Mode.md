The 'go build' and 'go install' commands take a -buildmode argument which
indicates which kind of object file is to be built. Currently supported values
are:

```shell
    -buildmode=archive
            Build the listed non-main packages into .a files. Packages named
            main are ignored.

    -buildmode=c-archive C静态链接库
            Build the listed main package, plus all packages it imports,
            into a C archive file. The only callable symbols will be those
            functions exported using a cgo //export comment. Requires
            exactly one main package to be listed.

    -buildmode=c-shared C动态库
            Build the listed main package, plus all packages it imports,
            into a C shared library. The only callable symbols will
            be those functions exported using a cgo //export comment.
            Requires exactly one main package to be listed.

    -buildmode=default
            Listed main packages are built into executables and listed
            non-main packages are built into .a files (the default
            behavior).

    -buildmode=shared
            Combine all the listed non-main packages into a single shared
            library that will be used when building with the -linkshared
            option. Packages named main are ignored.

    -buildmode=exe
            Build the listed main packages and everything they import into
            executables. Packages not named main are ignored.

    -buildmode=pie
            Build the listed main packages and everything they import into
            position independent executables (PIE). Packages not named
            main are ignored.

    -buildmode=plugin
            Build the listed main packages, plus all packages that they
            import, into a Go plugin. Packages not named main are ignored.
```

On AIX, when linking a C program that uses a Go archive built with
-buildmode=c-archive, you must pass -Wl,-bnoobjreorder to the C compiler.



# Go 的Build Mode 

- `exe` (静态编译)

- `exe` (动态链接 `libc`)

- `exe` (动态链接 `libc` 和非 Go 代码)

- `pie` 地址无关可执行文件（安全特性）

- `c-archive` C 的静态链接库

  ```shell
  go build -buildmode=c-shared -o add.a add.go
  gcc main.c add.a -o a.out
  ```

  

- `c-shared` C 的动态链接库

  ```shell
  go build -buildmode=c-archive -o number.a
  gcc main.c add.a -o a.out
  ```

  

- `shared` Go 的动态链接库

- `plugin` Go 的插件