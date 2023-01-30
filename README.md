# Warrior's Survival
## Allegro Install
1. Goto https://github.com/liballeg/allegro5/releases
2. Download allegro-x86_64-w64-mingw32-gcc-10.2.0-posix-seh-static-5.2.7.0.zip
3. Unzip Allegro and put it in codeblocks' directory
4. Select settings -> Compiler -> Global compiler settings -> Toolchain executables, and set Compiler's installation directory to the path to MinGW you downloaded with codeblocks
5. Right click your project, and select build options
6. Select Search directories, (1)click Add (2)choose "include" in allegro dictionary
7. Select Project -> Debug, and select Linker settings, (1)click Add (2)click to browse file (3)choose monolith-debug.dll.a in allegro/lib/
8. Select Project -> Release, and select Linker settings, (1)click Add (2)click to browse file (3)choose monolith.dll.a in allegro/lib/

## Play
W, A, S, D: Control character to move
Space: attack
