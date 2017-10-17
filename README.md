# LabPack-C: A LabVIEW-Friendly C library for encoding and decoding MessagePack data

[About](#what-is-labpack-c) | [Build](#build)

## What is LabPack-C?

The LabPack-C project is a [LabVIEW](http://www.ni.com/labview)-friendly C library for encoding and decoding [MessagePack](http://www.msgpack.org) data. The library is intended to be used with the [Call Library Function](http://zone.ni.com/reference/en-XX/help/371361P-01/glang/call_library_function/) node to create a LabVIEW library. This provides MessagePack encoding and decoding function to LabVIEW as a Dynamic Link Library (DLL, Windows), Dynamic Library (Dylib, macOS), and/or Shared Object (SO, Linux).

## Dependencies

- [CMake 3.9.x](https://cmake.org/), or newer
- [Microsoft Visual C++ Build Tools 2017](https://www.visualstudio.com/downloads/#build-tools-for-visual-studio-2017), Windows Only
- [XCode Command Line Tools](https://developer.apple.com/xcode/features/), macOS Only
- [Git](https://git-scm.com/)

## Build

Ensure all of the [dependencies](#dependencies) are installed and up-to-date before proceeding.

### Windows

The [Microsoft Visual C++ Build Tools 2017](https://www.visualstudio.com/downloads/#build-tools-for-visual-studio-2017) should have installed a `x64 Native Build Tools` command prompt. Start the `x64 Native Build Tools` command prompt. This ensures the appropriate C compiler is available to CMake to build the library. Run the following commands to obtain a copy of the source code and build both the 32-bit and 64-bit DLLs with a `Release` configuration:

    > git clone https://github.com/fieldrndservices/labpack-c.git LabPack-C
    > cd LabPack-c
    > build.bat

The DLLs will be available in the `build32\bin` and `build64\bin` folders. 

### macOS

Start the Terminal.app. Run the following commands to obtain a copy of the source code from the repository and build the dynamic library (dylib):

    $ git clone https://github.com/fieldrndservices/labpack-c.git LabPack-C
    $ cd LabPack-C
    $ mkdir build && cd build
    $ cmake ..
    $ cd ..
    $ cmake --build build --config Release

The dynamic library (.dylib) will be available in the `build/bin` folder.

## Tests

All of the tests are located in the `tests` folder. The tests are organized in "modules", where an executable is created that tests each source "module", i.e. writer, reader, etc. The tests are separated from the source, but the tests are built as part of build for the shared library. Each test executable is located in the `bin\tests` folder of the build directory and they can be run independently.

### Windows

Start a terminal command prompt and navigate to the root folder of the project. Note, if following from the [Build](#build) instructions, a command prompt should already be available at the root folder of the project. Enter the following commands to run the tests:

    > ctest -C "Debug"

Or

    > bin\tests\writer
    > bin\tests\status

### macOS

Start the Terminal.app. Note, if following from the [Build](#build) instructions, the Terminal.app has already been started and the present working directory (pwd) should already be the root folder of the project. Enter the following commands to run the tests:

    $ ctest

Or,

    $ bin/tests/writer
    $ bin/tests/status

Or,

    $ make test

## License

See the LICENSE file for more information about licensing and copyright.

