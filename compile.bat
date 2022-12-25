gcc -static main.c game.c frac.c common.c -I"include" -L"lib" -lSDL2 -lm -lmingw32 -mwindows -Wl,--dynamicbase -Wl, -Wl, -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid -o frac.exe
pause
::gcc main.c game.c frac.c common.c -g -I"include" -L"lib" -lSDL2_ttf -lSDL2 -o frac.exe
::pause