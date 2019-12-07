# Weird Trans Formations

Simple implementation of 3D transformations in C.

In order to build type:

```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

then in order to test:

```
$ make test
```

and to install (surprise, surprise):

```
$ make install
```

To install in a dedicated location use, e.g. `-DCMAKE_INSTALL_PREFIX=../install` cmake argument.

Examples need SDL2 library to work so if you don't want to compile them use:

```
$ cmake .. -DBUILD_EXAMPLES=OFF
```
