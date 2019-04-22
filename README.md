# particleExplosion

This Particle explosion program uses the SDL library.
1) Download the SDL2 for Mingw tar file and extract it. We need the x86-64 directory for 64 bits
2) Copy the content of the lib and include directories to the Mingw compiler lib and include directories respectively
3) Copy bin/SDL2.ddl and bin/sdl2-config to the bin directory of the Mingw compiler
Eclipse setup (linking libraries):
1) Go to project properties, c/c++ build, Mingw c++ linker, libraries and add the following in order
- mingw32
- SDL2main
- SDL2
