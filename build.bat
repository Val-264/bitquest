:: Archivo para compilar el proyecto en Windows

@echo off
setlocal enabledelayedexpansion

REM comentario
:: comentario

:: obtenemos el nombre de la carpeta actual
for %%I in (.) do set "CARPETA=%%~nxI"

echo .
echo Compilando el proyecto
echo .

::compilar todos los asm a obj
for %%F in (*.asm) do (
    echo [NASM] Compilando %% F ...
    nasm -f win64 "%%F" -o "%%~nF.obj"
    if errorlevel 1 (
        echo Error al compilar %%F 
        exit /b 1
    )
)

:: hacer que los objects queden en un vector de string 
set "OBJS="
for %%F in (*.obj) do (
    set "OBJS=!OBJS! %%F"
)

set "CSRC="
for %%F in (*.c) do (
    set "CSRC=!CSRC! %%F"
)

::enlazamos con gcc

gcc %CSRC% %OBJS% -o "%CARPETA%.exe"
if errorlevel 1 (
    echo Error en el enlace final
    exit /b 1
)

echo .
echo Compilacion terminada
echo .

endlocal
pause