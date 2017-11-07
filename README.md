# LabPack-C: A LabVIEW-Friendly C library for encoding and decoding MessagePack data

[About](#what-is-labpack-c) | [Build](#build)

## What is LabPack-C?

The LabPack-C project is a [LabVIEW](http://www.ni.com/labview)-friendly C library for encoding and decoding [MessagePack](http://www.msgpack.org) data. The library is intended to be used with the [Call Library Function](http://zone.ni.com/reference/en-XX/help/371361P-01/glang/call_library_function/) node to create a LabVIEW library. This provides MessagePack encoding and decoding function to LabVIEW as a Dynamic Link Library (DLL, Windows), Dynamic Library (Dylib, macOS), and/or Shared Object (SO, Linux).

## Dependencies

- [CMake 3.9.x](https://cmake.org/), or newer
- [Microsoft Visual C++ Build Tools 2017](https://www.visualstudio.com/downloads/#build-tools-for-visual-studio-2017), Windows Only
- [XCode Command Line Tools](https://developer.apple.com/xcode/features/), macOS Only
- [Git](https://git-scm.com/)
- [C/C++ Development Tools for NI Linux Real-Time, Eclipse Edition 2017](http://www.ni.com/download/labview-real-time-module-2017/6731/en/), NI Linux RT only

## Build

Ensure all of the [dependencies](#dependencies) are installed and up-to-date before proceeding.

### Windows

The [Microsoft Visual C++ Build Tools 2017](https://www.visualstudio.com/downloads/#build-tools-for-visual-studio-2017) should have installed a `x64 Native Build Tools` command prompt. Start the `x64 Native Build Tools` command prompt. This ensures the appropriate C compiler is available to CMake to build the library. Run the following commands to obtain a copy of the source code and build both the 32-bit and 64-bit DLLs with a `Release` configuration:

    > git clone https://github.com/fieldrndservices/labpack-c.git LabPack-C
    > cd LabPack-c
    > build.bat

The DLLs will be available in the `build32\bin` and `build64\bin` folders. 

### macOS

Ensure the command-line tools for [XCode](https://developer.apple.com/xcode/) have been installed along with [git](https://git-scm.com/) before proceeding. Start the Terminal.app. Run the following commands to obtain a copy of the source code from the repository and build the dynamic library (dylib):

    $ git clone https://github.com/fieldrndservices/labpack-c.git LabPack-C
    $ cd LabPack-C
    $ mkdir build && cd build
    $ cmake ..
    $ cd ..
    $ cmake --build build --config Release

The dynamic library (.dylib) will be available in the `build/bin` folder.

### Linux

If running on Ubuntu or similar distribution, ensure the [build-essential](https://packages.ubuntu.com/trusty/build-essential), [cmake](https://packages.ubuntu.com/trusty/cmake), and [git](https://packages.ubuntu.com/trusty/git) packages are installed before proceeding. These can be installed with the following command from a terminal:

    $ sudo apt-get install build-essential cmake git

Start a terminal, and run the following commands to obtain a copy of the source code from the repository and build the shared object (so):

    $ git clone https://github.com/fieldrndservices/labpack-c.git
    $ cd labpack-c
    $ mkdir build && cd build
    $ cmake ..
    $ cd ..
    $ cmake --build build --config Release

The shared object (.so) will be available in the `build/bin` folder.

### NI Linux RT

NI provides a cross-compiler for their Real-Time (RT) Linux distribution. Before proceeding, download and install the [C/C++ Development Tools for NI Linux Real-Time, Eclipse Edition 2017](http://www.ni.com/download/labview-real-time-module-2017/6731/en/).It is also best to review the [Getting Stared with C/C++ Development Tools for NI Linux Real-Time, Eclipse Edition](http://www.ni.com/tutorial/14625/en/) guide for more general information about configuring the internal builder.

1. Start NI Eclipse. A _Workspace Launcher_ dialog may appear. Use the default.
2. A welcome screen may appear after the application has loaded. Close the welcome screen.
3. Right-click in the _Project Explorer_ on the left and select _Import_ from the context menu that appears. A new dialog will appear.
4. Select `Git->Projects from Git` from the dialog that appears. Click the _Next >_ button. A new page will appear.
5. Select the `Clone URI` from the list that appears in the new page of the dialog. Click the _Next >_ button. A new page will appear.
6. Enter the URI for the git repository in the _URI:_ field, i.e. `https://github.com/fieldrndservices/labpack-c.git`. The _Host:_ and _Repository path:_ fields will populate automatically. Click the _Next >_ button. A new page will appear.
7. Ensure only the `master` checkbox is checked in the _Branch Selection_ page of the _Import Projects from Git_ dialog. Click the _Next >_ button. A new page will appear.
8. Browse to the workspace directory for NI Eclipse to populate the _Directory:_ field. Leave all other fields as the defaults. Click the _Next >_ button. A new page will appear.
9. Select the `Use the New Project wizard` radio button from the options under the _Wizard for project import_ section. Click the _Finish_ button. A new dialog will appears.
10. Select `File->New...->C Project` from the menu. A new dialog will appear.
11. Enter `labpack-c` for the _Project name:_ in the _C Project_ dialog that appeared. A warning will appear, but it is okay.
12. Select `Empty Project` under the _Shared Library_ folder in the _Project type:_ list on the bottom left of the dialog.
13. Ensure the `Cross GCC` item is highlighted under the _Toolchains:_ list on the bottom right.
14. Click the _Next >_ button. A new page will appear in the dialog.
15. Ensure the _Debug_ and _Release_ checkboxes are checked in the _Select Configurations_ page. Click the _Next >_ button. A new page will appear in the dialog.
16. Leave all fields blank in the _Cross GCC Command_ page. Click the _Finish_ button. The dialog should close and a `labpack-c` project should be listed under the _Project Explorer_ on the left.
17. Right-click on the `labpack-c` project in the _Project Explorer_ on the left and select `Properties` from the context menu that appears (its all the way at the bottom). A new dialog will appear.
18. Expand the `C/C++ General` node in the tree on the left. Select `Paths and Symbols`. Select the _Symbols_ tab on the right. Click the _Add..._ button on the far right. A new dialog will appear.
19. Enter `LABPACK_BUILD_SHARED` into the _Name:_ field. Leave the _Value:_ field blank and click the _OK_ button. The _Add symbol_ dialog will close.
20. Click the _Add..._ button on the far right under the _Symbols_ tab. A new dialog will appear.
21. Enter `MPACK_DEBUG` into the _Name:_ field. Enter `0` into the _Value:_ field. Click the _OK_ button. The _Add symbol_ dialog will close.
22. Click the _Add..._ button on the far right under the _Symbols_ tab. A new dialog will appear.
23. Enter `VERSION` into the _Name:_ field. Enter `'"#.#.#"'` into the _Value:_ field, where `#.#.#` is the major, minor, and patch version numbers. Note the single and double quotes are necessary. Click the _OK_ button. The _Add symbol_ dialog will close.
24. Click the _Add..._ button on the far right under the _Symbols_ tab. A new dialog will appear.
25. Enter `VERSION_MAJOR` into the _Name:_ field. Enter `#` into the _Value:_ field, where `#` is the major version number. The version number can be found in the `CMakeList.txt` file. Click the _OK_ button. The _Add symbol_ dialog will close.
26. Click the _Add..._ button on the far right under the _Symbols_ tab. A new dialog will appear.
27. Enter `VERSION_MINOR` into the _Name:_ field. Enter `#` into the _Value:_ field, where `#` is the minor version number. The version number can be found in the `CMakeList.txt` file. Click the _OK_ button. The _Add symbol_ dialog will close.
28. Click the _Add..._ button on the far right under the _Symbols_ tab. A new dialog will appear.
29. Enter `VERSION_PATCH` into the _Name:_ field. Enter `#` into the _Value:_ field, where `#` is the patch version number. The version number can be found in the `CMakeList.txt` file. Click the _OK_ button. The _Add symbol_ dialog will close.
20. Select `C/C++ Build` node from the tree on the left. Change the _Builder type:_ field from `External Builder` to `Internal Builder`. Click the _Apply_ button at the bottom of the dialog. Click the _OK_ button at the bottom of the dialog.
21. Expand the `C/C++ Build` node from the tree on the left. Select the `Settings` item.
22. Expand the `Cross GCC Compiler` item in the tree under the _Tool Settings_ tab on the right. Select the _Miscellaneous_ item.
23. Append the following to the _Other flags_ field:

    -std=c99 --sysroot=C:\build\17.0\x64\sysroots\core2-64-nilrt-linux

24. Check the _Position Independent Code_ (-fPIC) checkbox.
25. Select the `Cross Settings` item from the tree on the left under the _Tool Settings_ tab.
26. Paste the following into the _Prefix_ field:
    
    x86_64-nilrt-linux-
    
27. Paste the following into the _Path_ field:
    
    c:\build\17.0\x64\sysroots\i686-nilrtsdk-mingw32\usr\bin\x86_64-nilrt-linux

28. Click the _Apply_ button.
30. Select the _Build Artifact_ tab from the _Settings_ page under the `C/C++ Build` tree item.
31. Change the _Artifact name:_ field to: `labpack-rt`.
32. Click the _Apply_ button.
33. Expand the _Resource_ item on the left, and select the `Resource Filters` item.
34. Click the _Add..._ button in the far right. A new dialog will appear.
35. Select the `Exclude All` radio button under the _Filter type_ section.
36. Select the `Folders` radio button under the _Applies to_ section.
37. Enter `tests` to the field after the `matches` drop down menu.
38. Click the _Apply_ button.
39. Click the _OK_ button.
40. Select `Project->Build Project` from the menubar to finally build the shared object.

Note, steps 3-39 only need to be done once to setup the project. The `liblabpack-rt.so` will be located in the `Debug` folder under the project's root folder inside the Eclipse workspace folder. The same settings need to be applied to the `Release` build configuration if a release build is desired.

## Tests

All of the tests are located in the `tests` folder. The tests are organized in "modules", where an executable is created that tests each source "module", i.e. writer, reader, etc. The tests are separated from the source, but the tests are built as part of build for the shared library. Each test executable is located in the `bin\tests` folder of the build directory and they can be run independently.

If the `ctest`, or `make test` on non-Windows systems, commands are used _after_ building the tests to run the tests, then the [ctest](https://cmake.org/Wiki/CMake/Testing_With_CTest) test runner framework is used to run the tests. This provides a very high level summary of the results of running all tests. Since the tests are organized into "modules" and suites, the [ctest](https://cmake.org/cmake/help/v3.9/manual/ctest.1.html) command only indicates that a test within a module and suite has failed. It does _not_ indicate which test has failed. To investigate the failed test, the executable in the `bin\tests` folder for test module should be run. For example, if a test in the writer module failed, the ctest test runner will indicate the "writer" test has failed. The `bin\tests\writer` executable should then be run as a standalone application without the ctest test runner to obtain information about which test and assertion failed.

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

### Linux

Start a terminal. Note, if following from the [Build](#build) instructions, the terminal has already been started and the present working directory (pwd) should already be the root folder of the project. Enter the following commands to run the tests:

    $ ctest

Or,

    $ bin/tests/writer
    $ bin/tests/status

Or,

    $ make test

## License

See the LICENSE file for more information about licensing and copyright.

