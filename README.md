# `nttiny v0.3`

OpenGL-based interactive plotting library.

```shell
git clone --recursive git@github.com:haykh/nttiny.git
# or to add as an external library
git add submodule git@github.com:haykh/nttiny.git extern/nttiny
```

## Compilation

Compile the code as a standalone application with the `make nttiny [OPTIONS]` command. To see the help menu with all the options type `make`.

To build a static library simply run `make nttiny_static [OPTIONS]`.

> Prior to compiling the code either as a static library or as a standalone application please make sure all the dependencies are satisfied (see section below).

## Usage

File `src/main.cpp` contains an example usage of the `nttiny` as a standalone app. In most of the scenarios, however, you would need to build and use `nttiny` as a static library. For that, compile the static library, `libnttiny.a`, and put it in your projects directory with other libraries. See `src/main.cpp` for an example of how to use the library.

> Also make sure to copy the header files from the `include/` directory: `cp -r <NTTINY_PATH>/include/nttiny <YOUR_PROJECT>/lib`.

## Dependencies

The dependencies need to be set up just once for each system (or each time you update the submodules). Their source codes are stored in `extern/` directory, while the libraries are stored in either `include/` or `lib/` directories. To update the dependency source codes run the following:

```shell
# from the `nttiny` root directory
git submodule update --remote
```

### `glfw`

In case you already have the `glfw` library installed on your system -- change the `LIBRARIES` variable in `Makefile` from `glfw3` to `glfw` and skip this. Otherwise here's an instruction on how to compile it and put as a static library.

```shell
# for convenience define the path to source code as a variable
export NTTINY_PATH=...

cd $NTTINY_PATH/extern/glfw
# configure cmake
cmake -B build
cd build
# compile
make -j <NCORES>

# move the static library to `lib/`
mv $NTTINY_PATH/extern/glfw/build/src/libglfw3.a $NTTINY_PATH/lib/

# (optional) also move updated header files
# cp -r $NTTINY_PATH/extern/glfw/include/GLFW $NTTINY_PATH/include/

unset NTTINY_PATH
```

<!-- ### `imgui`, `implot`

This library is compiled with the rest of the project, so need to just copy the proper files to `lib/imgui/`.

```shell
# for convenience define the path to source code as a variable
export NTTINY_PATH=...

mkdir -p $NTTINY_PATH/lib/imgui/
cp $NTTINY_PATH/extern/imgui/*.cpp $NTTINY_PATH/lib/imgui/
cp $NTTINY_PATH/extern/imgui/*.h $NTTINY_PATH/lib/imgui/
mkdir -p $NTTINY_PATH/lib/imgui/backends/
cp $NTTINY_PATH/extern/imgui/backends/*_glfw.* $NTTINY_PATH/lib/imgui/backends/
cp $NTTINY_PATH/extern/imgui/backends/*_opengl3.* $NTTINY_PATH/lib/imgui/backends/

mkdir -p $NTTINY_PATH/lib/implot/
cp $NTTINY_PATH/extern/implot/*.cpp $NTTINY_PATH/lib/implot/
cp $NTTINY_PATH/extern/implot/*.h $NTTINY_PATH/lib/implot/

unset NTTINY_PATH
``` -->

<!-- ### `plog`, `rapidcsv`

These are all header-only libraries. So it's only necessary to copy the proper header files.

```shell
# for convenience define the path to source code as a variable
export NTTINY_PATH=...

cp -r $NTTINY_PATH/extern/plog/include/plog $NTTINY_PATH/include
cp -r $NTTINY_PATH/extern/rapidcsv/src $NTTINY_PATH/include/rapidcsv

unset NTTINY_PATH
``` -->

### `glad`

1. Obtain `glad` headers and `glad.c` from [this online server](https://glad.dav1d.de/), for your specific version of OpenGL (use "Profile: Core" and mark the "Generate a loader" tick).

> To find out your OpenGL version run `glxinfo | grep "OpenGL version"`.

2. Download the generated `glad.zip` archive, and unzip it (`unzip glad.zip`). If you do this from the source code directory (`<NTTINY_PATH>`) the headers will be properly placed into `extern/glad` and `extern/KHR` directories (otherwise, do that manually).

3. Move the `glad.c` file to a more appropriate place (and change `.c` to `.cpp`): `mv glad.c lib/glad.cpp`.
