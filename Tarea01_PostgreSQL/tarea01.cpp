/*Bibliotecas utilizadas*/
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <cstdlib>
#include <libpq-fe.h>
#include <fstream>
#include <string.h>
#include <gd.h>
#include <gdfonts.h>

/*Constantes*/
#define _TIME_
#define N 15
#define IMG_WIDTH 600
#define IMG_HEIGHT 180
#define BORDE_ANCHO 580
#define BORDE_ALTO 150

/*compilar este archivo con el siguiente código:
g++ tarea01.cpp -o test -I/usr/include/postgresql -I/usr/include -lpq -lgd  */



using namespace std;


/*Variables Globales*/
char *fecha_i,*fecha_f;  	        //atributos de respaldo de argumentos para la direccion y fechas.
struct tm fecha_desde;  			// estructura para trabajar la fecha de inicio
struct tm fecha_hasta;  			// estructura para trabajar la fecha de termino

/*Variables Globales inherentes  a la conexión con la base de datos*/
PGconn *cnn = NULL;
PGresult *result = NULL, *re2=NULL;
const char *host = "146.83.181.4";
const char *port = "6432";
const char *schema = "isw";
const char *dataBase = "iswdb";
const char *user = "estisw";
const char *passwd = "estisw";

//PROCEDIMIENTO PARA MOSTRAR LOS INTEGRANTES DEL GRUPO
void integrantes(){
     printf("\nIntegrantes:\n\nGutierrez, Daniel\nLeiva, Daniel\nRojas, Ernesto\n\n");
     printf("Version: 1.3\n");
     printf("Fecha de compilacion: %s - %s\n\n ", __DATE__, __TIME__);//Fecha de compilacion.

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
            //return EXIT_SUCCESS;
        };

        if((strlen(fecha_f)!=10)||(fecha_f[4]!='-')||(fecha_f[7]!='-'))
        {
            cout<<"Fecha Final Erronea"<<endl;
            exit(0);
            //return EXIT_SUCCESS;
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
        if((fecha_desde.tm_mon>12)||(fecha_desde.tm_mday>31))
        {
           cout<<"Fecha Inicial Erronea"<<endl;
           exit(0);
           //return EXIT_SUCCESS;
        };

        if((fecha_hasta.tm_mon>12)||(fecha_hasta.tm_mday>31))
        {
           cout<<"Fecha Final Erronea"<<endl;
           exit(0);
           //return EXIT_SUCCESS;
        };


cout<<"Fechas Correctamente Validadas"<<endl;
}

/*Funcion principal y cuerpo del programa*/
int main(int argc, char *argv[])
{
/*Variables de la funcion principal*/
char chartoint[5];      			// char para respaldo y apoyo para traspasar las fechas a digitos individuales
int lineas_totales=0;      			// entero que permite crear el largo total de registro de ventas
int i=0;                   			// contador

/*Validación de argumentos de entrada con opciones -g -t -a -v*/
if((argc==2)||(argc==4))
{

      if((argv[1][0]!='-')){
          cout<<"Error en ingreso de argumentos."<<endl;
          return EXIT_SUCCESS;
      };

      switch (argv[1][1]){

         case 'g':     //ingresando en opcion "g", respaldamos los argumentos.
            Comprobar_Fechas(argv[2], argv[3]);

         break;

         case 't':     //ingresando en opcion "g", respaldamos los argumentos.
            Comprobar_Fechas(argv[2], argv[3]);

         break;

         case 'a':     //ingresando en opcion "g", respaldamos los argumentos.
            Comprobar_Fechas(argv[2], argv[3]);

         break;

         case 'v':
		       integrantes();
         break;

         };
}
else cout<<"Opcion no valida, ingrese correctamente los parametros"<<endl;
return EXIT_SUCCESS;
}
