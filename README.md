# Paragon Game Engine

This engine is an in-development hobbist project I am building for use as a portfolio project. Its only 2 months in development but in this time I developed an asset database with async directory watching, an Instrumentor for debugging based on The Cherno's instrumentor class, a Logger singleton, and support for Wren through a custom fork of the language called Finch.

There are 3 projects in this directory:
    - Engine: Builds as a Dll to be used by the other 2 projects;
    - Editor: Currently is only a basic ImGui application with some custom utilities for loading themes;
    - Sandbox: A project to test the engine as I go;

## Prerequisites

- MSVC compiler and toolchain;
- Any CMake version above 3.11

The project uses VCPKG as a package manager and Ninja as a build system but both are included in the repo.

## Building

To build the project just run the script located in ".\scripts\build.ps1". If it is your first time building the project it will setup all the libraries and build the project in a build directory.

When in a command line located in the root of the project simply run:

```ps1
.\scripts\build.ps1
```

## Quirks

To run the editor it needs to be pointed at a project. 
Any folder containing a file called .project and an assets directory is a valid project for now.

For simplicity I'm adding a sample project and a "run_editor" script.

## Contact

Any issues feel free to email me at pbentes@eckle.io