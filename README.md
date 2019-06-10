# minicrt
MiniCRT exists as a small, lightweight replacement for MSVCRT. It is not trying to be a complete reimplementation of MSVCRT; the goal is to allow the creation of compact and portable binaries that don't suffer from the bloat of statically linking MSVCRT or the deployment challenges of dynamically linking and distributing it.

## License

This software is licensed under the terms of the MIT license.

## System Requirements

MiniCRT does not depend on APIs newer than Windows NT 3.1 or Windows 95. A Unicode binary with MiniCRT can run on NT 3.1; an ANSI binary can run on Windows 95. Newer compilers will mark binaries as requiring newer versions of Windows; this is not a limitation of MiniCRT, but a limitation of the compiler.

To compile from source, you need Visual C++, version 2 or newer; or MinGW gcc; or Clang/LLVM. Visual C++ is the primary target for MiniCRT. Free versions of Visual C++ are included in the Visual C++ Build Tools, Windows SDK 7.1 (2010), or Windows SDK 7.0 (2008).

## Build instructions

### Visual C++

Unpack the source, open a Visual C++ command prompt, and run NMAKE. If your version of Visual C++ doesn't create a command prompt shortcut for you, you may need to run VcVars32.bat, then run NMAKE.

### MinGW or Clang

Unpack the source, open a command prompt for the desired compiler, and run make.

### Compilation options

Compilation options can be used by passing arguments to NMAKE or make.

| Option | Definition |
| ------ | ---------- |
| DEBUG= | Enable debug code. Valid values are 0 (disabled) or 1 (enabled.) Default is 0. |

