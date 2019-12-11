# Weird Trans Formations

Simple implementation of 3D transformations in C. Don't use this library. It was written just for fun and to learn C as well as to learn about quaterinons and coordinate system transformations. 

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

I you would like to commit any changes, please run (depending on what changed):

```
$ ./clang-format-all src/ include/ test/ example/
```

## References

- Understanding Quaternions - www.3dgep.com/understanding-quaternions
- Lear OpenGL - www.learnopengl.com/Getting-started/Coordinate-Systems
- The Perspective and Orthographic Projection Matrix - www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/projection-matrix-introduction