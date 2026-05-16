ProbablyTetris
=============

Overview
--------
This is a C++ showcase project developed in Microsoft Visual Studio using DirectX 9 and FMOD

Development Environment
-----------------------
- IDE: Visual Studio
- Language: C++
- Graphics API: DirectX 9
- Audio Library: FMOD
- Character Set: Multi-Byte Character Set
- Runtime Library: /MT (Static Runtime)

Required Dependencies
---------------------
The following dependencies are required to build the project:

1. DirectX SDK (June 2010)
   Required libraries:
   - d3dx9.lib
   - d3d9.lib
   - dxguid.lib
   - dinput8.lib

2. FMOD Studio API (Windows)
   Required library:
   - fmod_vc.lib

3. Required DLLs:
   - fmod.dll
   - D3DX9_43.dll

Runnable Build and Source Code link:
https://github.com/Diastey/ProbablyTetris/releases

Project Configuration
---------------------
VC++ Include Directories:
- $(ProjectDir)External\FMOD\inc
- $(ProjectDir)External\DirectX\inc
- $(IncludePath)

VC++ Library Directories:
- $(ProjectDir)External\FMOD\lib\x86
- $(ProjectDir)External\DirectX\lib\x86
- $(LibraryPath)

Character Set:
- Use Multi-Byte Character Set

Linker System:
- Not Set

Linker Dependencies:
- d3dx9.lib
- d3d9.lib
- dxguid.lib
- dinput8.lib
- fmod_vc.lib

Build Instructions
------------------
1. Open Project.sln in Visual Studio.
2. Verify include and library directories are correctly configured.
3. Verify character set and linker settings are correctly configured.
4. Build the solution in the Release configuration in x86 bit.

Running the Program
-------------------
If using a compiled executable, ensure the required FMOD runtime DLL is located in the same directory as the executable.

Notes
-----
This project was developed as a showcase/portfolio project.