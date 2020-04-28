@echo off

rem Options
set PRJ=injector
set SRC=src/injector.c
set LIB=-lgdi32 -luser32 -lshlwapi
set OPT=all release debug clean

goto :main

:all
call :release
call :debug
exit /b

:release
tcc.exe -m64 -Wall -Os -o bin\%PRJ%.exe %SRC% %LIB%
exit /b

:debug
tcc.exe -m64 -Wall -g -o bin\%PRJ%-debug.exe %SRC% %LIB%
exit /b

:clean
del bin\%PRJ%.exe bin\%PRJ%-debug.exe
exit /b

:main
if not exist "bin" mkdir "bin"
if "%1" == "" goto :%OPT%
(for %%a in (%OPT%) do (
    if "%1" == "%%a" goto :%%a
))

echo %OPT%