=============================================================================================
                       INSTRUCCIONES DE COMPILACION Y EJECUCION 
=============================================================================================

------ Instrucciones para Windows ------

> Desde la carpeta del proyecto:
    - Dar doble clic sobre el build.bat
    - Dar doble clic sobre el archivo .exe

> Desde la terminal 
    - Ejecutar los comandos en el siguiente orden 
        1- nasm -f win64 rutinas.asm -o rutinas.obj     
        2- gcc main.c juego.c rutinas.obj -o BitQuest.exe
        3- ./BitQuest.exe  