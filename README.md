# PMAL
The Performance Memory Allocation Library (PMAL) has been created due to a passion for performance critical applications, specifically, in the video games industry and a want for creating something of high quality that is both easy to use and is lightweight.

### What This Is
Simply put, it is a suite of memory allocators and smart pointers for the user to allocate memory, where all the memory management is done behind the scenes in a performant manner. This library will also provide memory statistics natively to the user which is optional (e.g. if build type is debug then enable statistics, etc)
- The philosophy of this is simplicity to the user.
- Extensibility and modularity to the user. For example, this library will provide its own allocators, however, if the user wants to create there own allocator but work with PMAL, the API should allow them to do so.

### Why?
- I believe my idea with this project is cool and wanted to put it to the test.
- I want learn how to architect and design projects.
- Learn more deeply about memory inside computers and potentially peripheries.
- Develop my skills with C++ and learn how to squeeze as much performance as possible.

### What This Isn't
- This is not me thinking I can do it better than well established libraries already out there. However, if in the furture this comes good then I'll be more than satisfied.

## Build Dependencies
The only dependencies are:
- Compiler capable of C++ 20 (LLVM > GCC > MSVC)
- CMAKE (version 3.30 or later)
- Ninja build tool (optional as CMAKE needs ninja or unix makefile generators for clangd to play nice): really only needed if you plan on adding to the code

Should be platform agnostic and majority of distros of Linux should play nice too.  
**NOTE:** Not supported for windows just yet

### Building
To build, ensure you are in the directory and run:

```sh
./build.sh
```
If you want to run the test application to see what it can do then:
```
./build.sh -r
```
The following are other flags:
- -r, -run : runs associated .exe
- -d, -debug : build with debug information
- -rd, -releasedebug : build release + debug information
- -c, -clean : clean build

**NOTE:** An absence of the '-d' -'rd' flags defaults to release build
