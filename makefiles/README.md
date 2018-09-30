# The *makefile* system

## Scope
The makefile system based on GNU gmake enables to build C/C++ sources from a source tree. The tree may contain several libraries, several executables implemented in either C or C++. The system relies on a few conventions and make configuration files (.mk) places in each folder. Hierarchical build is supported and 


## Quick how to
Please note that a *"sample"* project provides a trivial example of the utilization of the make file system.
The following principles must be followed:
1. *"make/Makefile"* has to be linked from each directory that is part of the build
2. Each directory that is part of the build must contains a ".mk" configuration file setting the parameters of the directory. This file has to have the same name as the folder it is contained in. The content of the files depends on the purpose of the directory: top, library, executable
3. The libraries must have the same core name as the folder their source files are contained in i.e. "libsomelib.a" has to be build from the directory "somelib". The library "somelib" is referenced from the executable that requires libsomelib.a library.
4. All the artefacts are buit in the target directory that is created above the root of the source tree. The artefacts are located in the different directories that correspond to the current configuration.
5. A global project.mk contains all the common project parameters.


## Limitations (futrue extension projects)
The make files system lacks the following features:
1. Integrated basic test targets
2. Building dynamic libraries
3. The build hierarchy only allows two levels: top and library/executable
4. No support for packaging, all the artifacts have to be copied manualy
