@echo off
echo Compilando Blinky Game...
echo.
gcc main.c src/*.c -I include -I C:/Users/arthu/computacao/MySysSetup/mingw64/include -L C:/Users/arthu/computacao/MySysSetup/mingw64/lib -lraylib -lopengl32 -lgdi32 -lwinmm -o blinky.exe
echo.
if %ERRORLEVEL% EQU 0 (
    echo Compilacao concluida com sucesso!
) else (
    echo Erro na compilacao! Codigo: %ERRORLEVEL%
)
echo.
pause