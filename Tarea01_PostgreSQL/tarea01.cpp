/*Bibliotecas utilizadas*/
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <time.h>
#include <cstdlib>
#include <libpq-fe.h>
#include <fstream>
#include <string.h>
#include <gd.h>
#include <gdfonts.h>

/*Constantes*/
#define LargoConsulta 200
#define _TIME_
#define N 15

#define IMG_WIDTH 800
#define IMG_HEIGHT 600
#define IMG_BPP 24

#define BORDE_ANCHO 70
#define BORDE_ALTO 50

/*compilar este archivo con el siguiente código:
g++ tarea01.cpp -o test -I/usr/include/postgresql -I/usr/include -lpq -lgd  */

using namespace std;

/*Variables Globales*/
char Consulta[LargoConsulta];       //Cadena que permite la consulta
char *fecha_i,*fecha_f;  	        //atributos de respaldo de argumentos para la direccion y fechas.
struct tm fecha_desde;  			// estructura para trabajar la fecha de inicio
struct tm fecha_hasta;  			// estructura para trabajar la fecha de termino

//FUNCION QUE PERMITE IR LIBERANDO LA VARIABLE DE CONSULTA PARA EVITAR ERRORES
void LimpiarConsulta(void)
{
    for(int i = 0; i < LargoConsulta; i++ )
        Consulta[i] = '\0';
}

// FUNCION PARA GENERAR UN NUMERO ALEATORIO
int aleatoreo() {
    return rand() % 256;
}

//FUNCION QUE SE UTILIZA PARA GENERAR UNA ETIQUETA DE MES EN LUGAR DE UN NUMERO SIMPLE
char* etiquetaMes(int num) {

    char* mes = NULL;
    mes = (char *) calloc(65, sizeof (char *));

    if (num == 1) {
        strcpy(mes, "Ene");
        return mes;
    } else if (num == 2) {
        strcpy(mes, "Feb");
        return mes;
    } else if (num == 3) {
        strcpy(mes, "Mar");
        return mes;
    } else if (num == 4) {
        strcpy(mes, "Abr");
        return mes;
    } else if (num == 5) {
        strcpy(mes, "May");
        return mes;
    } else if (num == 6) {
        strcpy(mes, "Jun");
        return mes;
    } else if (num == 7) {
        strcpy(mes, "Jul");
        return mes;
    } else if (num == 8) {
        strcpy(mes, "Ago");
        return mes;
    } else if (num == 9) {
        strcpy(mes, "Sep");
        return mes;
    } else if (num == 10) {
        strcpy(mes, "Oct");
        return mes;
    } else if (num == 11) {
        strcpy(mes, "Nov");
        return mes;
    } else if (num == 12) {
        strcpy(mes, "Dic");
        return mes;
    } else {
        strcpy(mes, "");
        return mes;
    }
}

// Transforma un entero a una Cadena de caracteres
char* longStr(long num) {
    char* texto = NULL;
    texto = (char *) calloc(65, sizeof (char *));
    snprintf(texto, 64, "%ld", num);
    return texto;
}


//FUNCION PARA MOSTRAR LOS INTEGRANTES DEL GRUPO
void integrantes(){
     printf("\nIntegrantes:\n\nGutierrez, Daniel\nLeiva, Daniel\nRojas, Ernesto\n\n");
     printf("Version: 1.3\n");
     printf("Fecha de compilacion: %s - %s\n\n", __DATE__, __TIME__);//Fecha de compilacion.

}

/*Funcion para corroborar fechas*/
void Comprobar_Fechas(char *Inicio, char *Termino)
{
char chartoint[5];      			// char para respaldo y apoyo para traspasar las fechas a digitos individuales
fecha_i=Inicio;
fecha_f=Termino;

 //comprobamos la estructura de las fechas.
        if((strlen(fecha_i)!=10)||(fecha_i[4]!='-')||(fecha_i[7]!='-'))
        {
            cout<<"Fecha Inicial Erronea"<<endl;
            exit(0);
        };

        if((strlen(fecha_f)!=10)||(fecha_f[4]!='-')||(fecha_f[7]!='-'))
        {
            cout<<"Fecha Final Erronea"<<endl;
            exit(0);
        };

        //respaldamos las fechas divididas en anio, mes y dia de las fechas de inicio y fin.
        chartoint[0]=fecha_i[0];chartoint[1]=fecha_i[1];chartoint[2]=fecha_i[2];chartoint[3]=fecha_i[3];chartoint[4]='\n';
        fecha_desde.tm_year=atoi(chartoint);
        chartoint[0]=fecha_i[5];chartoint[1]=fecha_i[6];chartoint[2]='\n';
        fecha_desde.tm_mon=atoi(chartoint)-1;
        chartoint[0]=fecha_i[8];chartoint[1]=fecha_i[9];chartoint[2]='\n';

        fecha_desde.tm_mday=atoi(chartoint);
        chartoint[0]=fecha_f[0];chartoint[1]=fecha_f[1];chartoint[2]=fecha_f[2];chartoint[3]=fecha_f[3];chartoint[4]='\n';
        fecha_hasta.tm_year=atoi(chartoint);
        chartoint[0]=fecha_f[5];chartoint[1]=fecha_f[6];chartoint[2]='\n';
        fecha_hasta.tm_mon=atoi(chartoint)-1;
        chartoint[0]=fecha_f[8];chartoint[1]=fecha_f[9];chartoint[2]='\n';
        fecha_hasta.tm_mday=atoi(chartoint);

        //comprobamos si las fechas son reales o correctas.
        if((fecha_desde.tm_mon>11)||(fecha_desde.tm_mday>31))
        {
           cout<<"Fecha Inicial Erronea"<<endl;
           exit(0);
        };

        if((fecha_hasta.tm_mon>11)||(fecha_hasta.tm_mday>31))
        {
           cout<<"Fecha Final Erronea"<<endl;
           exit(0);
        };

        if((fecha_hasta.tm_mon < fecha_desde.tm_mon)||(fecha_hasta.tm_mday < fecha_desde.tm_mday) || (fecha_hasta.tm_year < fecha_desde.tm_year) )
        {
           cout<<"Fecha Final es Menor a la Fecha Inicial"<<endl;
           exit(0);
        };


cout<<"\nNOTA: Si el archivo generado está en blanco, se debe a que las fechas tecleadas no existen en el calendario o no existen registros para las fechas en la Base de Datos\n"<<endl;
}

/*Funcion principal y cuerpo del programa*/
int main(int argc, char *argv[])
{
/*Variables de la funcion principal*/
char chartoint[5];      			// char para respaldo y apoyo para traspasar las fechas a digitos individuales
int lineas_totales=0;      			// entero que permite crear el largo total de registro de ventas
int i=0, j=0, UltimoMes, PrimerMes, PivoteMes;
ofstream archivoCSV;                // variable tipo archivo para generar CSV con peticiones
// Array que almacena la cantidad de peticiones por mes
long long int CantidadxMes [12], Mayor = 0, CantidadPeticiones = 0;

/*Variables inherentes  a la conexión con la base de datos*/
PGconn *conexion = NULL;
PGresult *resultado_SQL = NULL;
const char *servidor = "146.83.181.4";
const char *puerto = "6432";
const char *esquema = "isw";
const char *baseDato = "iswdb";
const char *usuario = "estisw";
const char *contrasena = "estisw";
char ResultadoParcial[30];

/*Variables usadas para mostrar datos en JPEG*/
gdImagePtr imagen;
FILE *archivo;
gdFontPtr fuente = gdFontGetSmall();
imagen = gdImageCreateTrueColor(IMG_WIDTH, IMG_HEIGHT);
int blanco, negro, colorAleatorio, alto = 50, ancho = 70, ValorGrafico, CantidadGraficada = 0;
long paso = 0, maximo = 0;
char titulo[513];
double porcentaje = 0.0, PorcentajeParcial = 0.0;

/*Validación de argumentos de entrada con opciones -g -t -a -v*/
if((argc==2)||(argc==4))
{

      if((argv[1][0]!='-')){
          cout<<"Error en ingreso de argumentos."<<endl;
          return EXIT_SUCCESS;
      };

      switch (argv[1][1]){

         case 'g':     //ingresando en opcion "g",
            Comprobar_Fechas(argv[2], argv[3]);
            LimpiarConsulta();

            strcpy(Consulta,"SELECT EXTRACT (month FROM fecha) AS mes, COUNT(peticion) as contador FROM isw.accesos WHERE fecha >= '");
            strcat(Consulta, argv[2]);
            strcat(Consulta, " 00:00:00' and fecha <= '");
            strcat(Consulta, argv[3]);
            strcat(Consulta, " 23:59:59' GROUP BY EXTRACT (month FROM fecha) ORDER BY EXTRACT (month FROM fecha);");

            /*Conexion con la base de datos*/
            conexion = PQsetdbLogin(servidor,puerto,NULL,NULL,baseDato,usuario,contrasena);

                if (PQstatus(conexion) != CONNECTION_BAD) {
                resultado_SQL = PQexec(conexion, Consulta);

                    if (resultado_SQL != NULL)
                    {
                        int tuplas = PQntuples(resultado_SQL);
                        int campos = PQnfields(resultado_SQL);

                        for (i=0; i < tuplas; i++)
                        {
                            for (j=0; j < campos; j++)
                            {
                                /*se guarda el resultado parcial de una consulta en una variable
                                temporal, obteniendose el ultimo mes entregado por la consulta y se guarda en un array
                                el valor de las peticiones por mes*/

                                strcpy(ResultadoParcial, PQgetvalue(resultado_SQL,i,j));

                                if (i == 0 && j == 0)
                                {
                                    PrimerMes = atoi(ResultadoParcial);
                                    PivoteMes = PrimerMes;
                                }
                                if (j == 1)
                                {
                                    CantidadxMes[PivoteMes] = atoi(ResultadoParcial);
                                    if (Mayor <= CantidadxMes[PivoteMes]) Mayor = CantidadxMes[PivoteMes];
                                    PivoteMes++;
                                }
                                if (i == tuplas-1 && j == 0) UltimoMes = atoi(ResultadoParcial);
                            }
                        }
                        /*Seccion que genera el JPEG*/

                            blanco = gdImageColorAllocate(imagen, 255, 255, 255);
                            negro = gdImageColorAllocate(imagen, 0, 0, 0);

                            // Se pinta el fondo Blanco
                            gdImageFill(imagen, 0, 0, blanco);

                            // Se imprime el titulo
                            memset(titulo, 0, 513);
                            snprintf(titulo, 513, "PETICIONES POR MES ENTRE LAS FECHAS INGRESADAS  [%s] a [%s]", argv[2], argv[3]);
                            gdImageString(imagen, fuente, (int) IMG_WIDTH * 0.35, 90, (unsigned char *) titulo, negro);
                            fflush(stdout);

                            // Se coloca la etiqueta al costado del gráfico
                            for (int y = BORDE_ALTO; y <= (BORDE_ALTO + 500); y = y + 50)
                            {

                                gdImageString(imagen, fuente, 5, IMG_HEIGHT - y, (unsigned char *) longStr(paso), negro);
                                paso += (Mayor / 9);
                            }

                            for (int mes = PrimerMes; mes <= UltimoMes ; mes++)
                            {
                                // Se le asigna acada mes un color aleatorio
                                colorAleatorio = gdImageColorAllocate(imagen, aleatoreo(), aleatoreo(), aleatoreo());
                                porcentaje = ((double) CantidadxMes[mes] / Mayor);

                                // El alto máximo serán 500px que será el 100%
                                alto = (int) (450 * porcentaje);
                                // Barra
                                gdImageFilledRectangle(imagen, ancho, IMG_HEIGHT - BORDE_ALTO, ancho + 55, IMG_HEIGHT - (BORDE_ALTO + alto), colorAleatorio);
                                // Borde Negro
                                gdImageRectangle(imagen, ancho, IMG_HEIGHT - BORDE_ALTO, ancho + 55, IMG_HEIGHT - (BORDE_ALTO + alto), negro);
                                // Etiqueta del Mes
                                gdImageString(imagen, fuente, ancho + 19, IMG_HEIGHT - BORDE_ALTO + 5, (unsigned char *) etiquetaMes(mes), colorAleatorio);
                                // Monto
                                gdImageString(imagen, fuente, ancho + 10, IMG_HEIGHT - (BORDE_ALTO + alto + 20), (unsigned char *) longStr(CantidadxMes[mes]), negro);

                                ancho += 55;
                            }

                            // Se etiqueta eje horizontal X
                            memset(titulo, 0, 513);
                            snprintf(titulo, 513, "MESES (X)");
                            gdImageString(imagen, fuente, IMG_WIDTH - BORDE_ANCHO, IMG_HEIGHT - BORDE_ALTO + 5, (unsigned char *) titulo, negro);
                            fflush(stdout);

                             // Se etiqueta eje horizontal Y
                            memset(titulo, 0, 513);
                            snprintf(titulo, 513, "PETICIONES (Y)");
                            gdImageString(imagen, fuente, 8, 23, (unsigned char *) titulo, negro);
                            fflush(stdout);

                            // Se enmarcan los ejes
                            gdImageLine(imagen, BORDE_ANCHO, (IMG_HEIGHT - BORDE_ALTO), (IMG_WIDTH - BORDE_ANCHO), (IMG_HEIGHT - BORDE_ALTO), negro);
                            gdImageLine(imagen, BORDE_ANCHO, BORDE_ALTO, BORDE_ANCHO, (IMG_HEIGHT - BORDE_ALTO), negro);

                            // Se guarda la imagen en un archivo
                            archivo = fopen("Peticiones_Mes.jpg", "wb");
                            if (archivo != NULL)
                            {
                                gdImageJpeg(imagen, archivo, 100);
                                fclose(archivo);
                            }
                            else cout<<"\n\n No se pudo crear el archivo jpeg\nPor favor ejecute nuevamente"<<endl;

                            gdImageDestroy(imagen);
                            cout<< "Se genero el archivo Peticiones_Mes.jpg en la carpeta de ejecucion del programa\n" << endl;

                        /*FIN Seccion que genera el JPEG*/
                    }
                }

                else cout<<"Hubo un error en la conexion a la base de datos"<<endl;

            PQfinish(conexion);
            /*FIn de la conexion con la base de datos*/

         break;

         case 't':     //ingresando en opcion "t"
            Comprobar_Fechas(argv[2], argv[3]);
            LimpiarConsulta();

            strcpy(Consulta,"SELECT estado as estado, COUNT(peticion) AS contador FROM isw.accesos WHERE fecha >= '");
            strcat(Consulta, argv[2]);
            strcat(Consulta, " 00:00:00' and fecha <= '");
            strcat(Consulta, argv[3]);
            strcat(Consulta, " 23:59:59' GROUP BY estado ORDER BY contador DESC");

            /*Conexion con la base de datos*/
            conexion = PQsetdbLogin(servidor,puerto,NULL,NULL,baseDato,usuario,contrasena);

            /*Seccion que genera el JPEG*/

            blanco = gdImageColorAllocate(imagen, 255, 255, 255);
            negro = gdImageColorAllocate(imagen, 0, 0, 0);

            // Se pinta el fondo Blanco
            gdImageFill(imagen, 0, 0, blanco);

            // Se imprime el titulo
            memset(titulo, 0, 513);
            snprintf(titulo, 513, "PETICIONES POR ESTADO ENTRE LAS FECHAS INGRESADAS  [%s] a [%s]", argv[2], argv[3]);
            gdImageString(imagen, fuente, (int) IMG_WIDTH * 0.1, 10, (unsigned char *) titulo, negro);
            fflush(stdout);

                if (PQstatus(conexion) != CONNECTION_BAD) {
                resultado_SQL = PQexec(conexion, Consulta);

                    if (resultado_SQL != NULL)
                    {

                        int tuplas = PQntuples(resultado_SQL);
                        int campos = PQnfields(resultado_SQL);
                        // Primero obtener la cantidad total de peticiones y normalizar el gráfico
                        for (i=0; i < tuplas; i++)
                            for (j=0; j < campos; j++)
                                if (j == 1) CantidadPeticiones = CantidadPeticiones + atoi(PQgetvalue(resultado_SQL,i,j));

                        // Se obtienen los porcentajes y dibujar graficos
                        int ValorAnterior = 0;
                        int pasoLineaColores = 385;
                        for (i=0; i < tuplas; i++)
                        {
                            for (j=0; j < campos; j++)
                            {
                                if (j == 1)
                                {
                                    PorcentajeParcial = ((double)atoi(PQgetvalue(resultado_SQL,i,j))/CantidadPeticiones);
                                    ValorGrafico = (PorcentajeParcial) * 360;

                                    /*Se grafican de manera individual cada una de las peticiones por mes que son
                                    apreciables, aplicando el filtro que al menos debe tener el valor 1 en la conversion
                                    proporcional del porcentaje de peticiones y el grafico de torta (360 grados) */
                                    if (ValorGrafico >= 1)
                                    {

                                        colorAleatorio = gdImageColorAllocate(imagen, aleatoreo(), aleatoreo(), aleatoreo());
                                        gdImageFilledArc(imagen, 220, 300, 400, 400, ValorAnterior, ValorGrafico + ValorAnterior, colorAleatorio, gdPie);
                                        gdImageFilledArc(imagen, 570, pasoLineaColores, 10, 10, 0, 360, colorAleatorio, gdPie);
                                        ValorAnterior = ValorGrafico + ValorAnterior;
                                        pasoLineaColores = pasoLineaColores + 30;
                                        CantidadGraficada++;
                                    }
                                }
                            }
                        }

                        /* Se completa el grafico con otras peticiones que son despreciables graficamente hablando*/
                        colorAleatorio = gdImageColorAllocate(imagen, aleatoreo(), aleatoreo(), aleatoreo());
                        gdImageFilledArc(imagen, 220, 300, 400, 400, ValorAnterior, 360, colorAleatorio, gdPie);
                        gdImageFilledArc(imagen, 570, pasoLineaColores, 10, 10, 0, 360, colorAleatorio, gdPie);

                        /*Normalizar el gráfico*/

                        // Se etiqueta un subtitulo
                        int pasoLinea = 50;
                        memset(titulo, 0, 513);
                        snprintf(titulo, 513, "De un total de [%llu] Peticiones", CantidadPeticiones);
                        gdImageString(imagen, fuente, 470, pasoLinea , (unsigned char *) titulo, negro);
                        fflush(stdout);
                        pasoLinea = pasoLinea + 20;

                        for (i=0; i < tuplas; i++)
                        {
                            // Se publican los porcentajes
                            pasoLinea = pasoLinea + 13;
                            memset(titulo, 0, 513);
                            snprintf(titulo, 513, "Peticion [%s] tuvo un Porcentaje de: [%f]", PQgetvalue(resultado_SQL,i,0), (atof(PQgetvalue(resultado_SQL,i,1))/CantidadPeticiones)*100);
                            gdImageString(imagen, fuente, 470, pasoLinea, (unsigned char *) titulo, negro);
                            fflush(stdout);
                        }

                        // Se indexa el grafico para su interpretacion
                        pasoLinea = 380 ;
                        for (i=0; i < CantidadGraficada; i++)
                        {
                            // Se publican los porcentajes
                            memset(titulo, 0, 513);
                            snprintf(titulo, 513, "Peticion [%s]", PQgetvalue(resultado_SQL,i,0));
                            gdImageString(imagen, fuente, 600, pasoLinea, (unsigned char *) titulo, negro);
                            fflush(stdout);
                            pasoLinea = pasoLinea + 30;
                        }

                        // Otros Porcentajes
                        memset(titulo, 0, 513);
                        snprintf(titulo, 513, "Otras Peticiones");
                        gdImageString(imagen, fuente, 600, pasoLinea, (unsigned char *) titulo, negro);
                        fflush(stdout);


                        // Se guarda la imagen en un archivo
                        archivo = fopen("Peticiones_Estado.jpg", "wb");
                        if (archivo != NULL)
                        {
                           gdImageJpeg(imagen, archivo, 100);
                           fclose(archivo);
                        }
                        else cout<<"\n\n No se pudo crear el archivo jpeg\nPor favor ejecute nuevamente"<<endl;

                        gdImageDestroy(imagen);
                        cout<< "Se genero el archivo Peticiones_Estado.jpg en la carpeta de ejecucion del programa\n" << endl;
                        /*FIN Seccion que genera el JPEG*/
                    }
                }
                else cout<<"Hubo un error en la conexion a la base de datos\n"<<endl;
            PQfinish(conexion);
            /*Fin de conexion con la base de datos*/

         break;

         case 'a':     //ingresando en opcion "a"
            Comprobar_Fechas(argv[2], argv[3]);
            LimpiarConsulta();

            strcpy(Consulta,"SELECT peticion, COUNT (*) as contador FROM isw.accesos WHERE fecha >= '");
            strcat(Consulta, argv[2]);
            strcat(Consulta, " 00:00:00' and fecha <= '");
            strcat(Consulta, argv[3]);
            strcat(Consulta, " 23:59:59' GROUP BY peticion ORDER BY contador DESC limit 100;");

            /*Creación de Archivo CSV con las 100 peticiones*/
            archivoCSV.open ("Cien_Peticiones.csv");
            archivoCSV << "RANKING;PETICION;TOTAL OCURRENCIAS\n";
            //archivoCSV.close();

            /*Conexion con la base de datos*/
            conexion = PQsetdbLogin(servidor,puerto,NULL,NULL,baseDato,usuario,contrasena);

                if (PQstatus(conexion) != CONNECTION_BAD) {
                resultado_SQL = PQexec(conexion, Consulta);

                    if (resultado_SQL != NULL)
                    {
                        int ID = 1;
                        int tuplas = PQntuples(resultado_SQL);
                        int campos = PQnfields(resultado_SQL);

                        for (i=0; i < tuplas; i++)
                        {
                            archivoCSV << ID << ";";
                            for (j=0; j < campos; j++)
                            {
                                /*Falta corregir problema de los punto y coma en las peticiones*/

                                /*Segmento que genera la tupla a ingresar al csv */
                                archivoCSV << PQgetvalue(resultado_SQL,i,j) << ";";

                            }
                            archivoCSV << "\n";
                            ID++;
                        }
                        /*Fin de creación de Archivo CSV con las 100 peticiones*/
                        archivoCSV.close();
                    }
                }
                else cout<<"Hubo un error en la conexion a la base de datos\n"<<endl;
            cout<<"Se creo el archivo Cien_Peticiones.csv en la carpeta de ejecucion del programa\n"<<endl;
            PQfinish(conexion);
            /*Fin de conexion con la base de datos*/

         break;

         case 'v':
            integrantes();
         break;

         };
}
else cout<<"Opcion no valida, ingrese correctamente los parametros"<<endl;
return EXIT_SUCCESS;
}
