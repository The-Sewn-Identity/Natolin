set lett=%~d0
gcc -Wall -o Natolin ./src/*.c -I./include/ ^
-I"%lett%/Libraries/raylib/include/" -L"%lett%/Libraries/raylib/lib/" ^
-I"%lett%/Libraries/LSLReader/" -L"%lett%/Libraries/LSLReader/" ^
-I"%lett%/Libraries/extutil/" -L"%lett%/Libraries/extutil/" ^
-lraylib -lgdi32 -lwinmm -llslread -lextutil -O3