# Lab_2_sistope
en carpeta incl se guardan cabezeras de los archivos
en carpeta obj se guardan archivos O generados al compilar el programa
en carpeta src se guardan los codigos del programa
    archivo image.c: contiene las funciones que trabajaran con las imagenes o loas arreglos de esta
    archivo images_data.c: contiene TDA basico de lista en donde seran guardados los datos de las imagenes
Etapas Pipeline:
    main.c: obtiene los parametros de entrada del programa.
    main2.c: lee los datos de la imagen (pixels, ancho y altura).
    main3.c: realiza la conversion a gris de la imagen leida.
    main4.c: aplica el filtro laplaciano.
    main5.c: binariza la imagen.
    main6.c: clasifica la imagen en si corresponde a nearly black o no.
    main7.c: muestra resultados del programa.


PARA EJECUTAR COMPILAR PROGRAMA EJECUTAR COMANDO make EN LA CONSOLA DE COMANDOS UBICADA EN LA CARPETA QUE CONTENGA EL ARCHIVO makefile.