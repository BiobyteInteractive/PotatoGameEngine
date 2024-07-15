# Paragon Game Engine

This engine is an in-development hobbist project I am building for use as a portfolio project. Its only 2 months into development but at this time I developed an asset database with async directory watching, an Instrumentor for debugging based on The Cherno's instrumentor class, a Logger singleton, and support for Wren scripting through a custom fork of the language called Finch.

There are 3 projects in this directory:

- Engine: Builds as a Dll to be used by the other 2 projects;
- Editor: Currently is only a basic ImGui application;
- Sandbox: A project to test the engine as I go;

## Prerequisites

- MSVC compiler and toolchain;
- Any CMake 3.16 and above;

## Build

This project uses CMake to fetch and build the dependencies. I regularly test the builds with ninja and Visual Studio.