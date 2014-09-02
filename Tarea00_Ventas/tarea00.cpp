#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
#include <string.h>
#include <gd.h>
#include <gdfonts.h>

#define IMG_WIDTH 600
#define IMG_HEIGHT 180
#define BORDE_ANCHO 580
#define BORDE_ALTO 150

/*Para compilar este archivo compilese con el siguiente código: g++ tarea00.cpp -o test -I/usr/include/ -I/usr/include -lgd */

using namespace std;

char NuevaPalabra [15];


//CREACION DE LA ESTRUCTURA DE REGISTRO PARA CADA VENTA
struct registro_venta{
       char nombre_empresa[50];
       int monto;
       struct tm fecha_venta;
}registro;

//PROCEDIMIENTO PARA MOSTRAR LOS INTEGRANTES DEL GRUPO
void integrantes(){
     printf("\nIntegrantes:\n\nGutierrez, Daniel\nLeiva, Daniel\nRojas, Ernesto\n\n");
     printf("Version: 1.3\n");
     printf("Fecha de compilacion: %s - %s\n\n ", __DATE__, __TIME__);//Fecha de compilacion.

}

//ELIMINAR COMILLA DE LA EMPRESA DEL REGISTRO ANALIZADO
void Saca_Comillas(char* palabra){
    int i, desde = 1;
    int hasta = strlen(palabra)-2;
    for (i=0;i<=14;i++) NuevaPalabra [i - 1] = '\0';
    for (i=0;i<=hasta;i++) NuevaPalabra [i - 1] = palabra [i];
    NuevaPalabra[i+1] = '\0';
}

//PROCEDIMIENTO PARA CREAR EL REGUSTRO DE VENTAS
void crear_registro(registro_venta *ventas,char *direccion){
     ifstream file_venta(direccion);
     char extrae_linea[150];
     int contador=0;
     if(file_venta.is_open()){
         while(!file_venta.eof()){
              file_venta.getline(extrae_linea,350,';');
              strcpy(ventas[contador].nombre_empresa,extrae_linea);
              file_venta.getline(extrae_linea,350,'"');
              file_venta.getline(extrae_linea,350,'-');
              ventas[contador].fecha_venta.tm_year=atoi(extrae_linea);
              file_venta.getline(extrae_linea,350,'-');
              ventas[contador].fecha_venta.tm_mon=atoi(extrae_linea)-1;
              file_venta.getline(extrae_linea,350,';');
              ventas[contador].fecha_venta.tm_mday=atoi(extrae_linea);
              file_venta.getline(extrae_linea,350,'"');
              file_venta.getline(extrae_linea,350,'\n');
              ventas[contador].monto=atoi(extrae_linea);
              contador++;
         };
         file_venta.close();
         cout<<"\nLectura de archivo *.csv exitosa"<<endl;
    }else
         cout<<"\nError al abrir el archivo *.csv: "<<direccion<<" . "<<endl;
}

//FUNCION PARA PODER OBTENER LA CANTIDAD MAXIMA DE REGISTROS DEL ARCHIVO CSV
int contar_lineas(char *direccion){
    int total_lineas=0;
    char guarda_extrae[350];
    ifstream recorre_archivo(direccion);
    if(recorre_archivo.is_open()){
         while(!recorre_archivo.eof()){
              recorre_archivo.getline(guarda_extrae,350,'\n');
              total_lineas=total_lineas+1;
         };
         recorre_archivo.close();
         return total_lineas;
    }else
         return 0;
}

//INICIO DE LA FUNCION PRINCIPAL
int main(int argc, char *argv[])
{
    char *captura_arg,*fecha_i,*fecha_f;  	//atributos de respaldo de argumentos para la direccion y fechas.
    struct tm fecha_desde;  			// estructura para trabajar la fecha de inicio
    struct tm fecha_hasta;  			// estructura para trabajar la fecha de termino
    char chartoint[5];      			// char para respaldo y apoyo para traspasar las fechas a digitos individuales
    registro_venta *ventas;    			// estructura de venta creada al inicio
    int lineas_totales=0;      			// entero que permite crear el largo total de registro de ventas
    int i=0;                   			// contador

    long long int SumaMonto [4];
    /*Array para guardar montos por tienda
     * 0: Cencosux
     * 1: Falaferia
     * 2: Porahi
     * 3: Replay
     */

    /*Variables usadas para mostrar datos*/
    gdImagePtr imagen;
    FILE *archivo;
    gdFontPtr fuente = gdFontGetSmall();
    imagen = gdImageCreateTrueColor(IMG_WIDTH, IMG_HEIGHT);
    int blanco, negro, color;
    char titulo[513];

    if((argc==2)||(argc==5)){

      if((argv[1][0]!='-')){
          cout<<"Error en ingreso de argumentos."<<endl;
          system("PAUSE");
          return EXIT_SUCCESS;
      };

      switch (argv[1][1]){

         case 'g':     //ingresando en opcion "g", respaldamos los argumentos.
                       fecha_i=argv[2];
                       fecha_f=argv[3];
                       captura_arg=argv[4];

                       //comprobamos la estructura de las fechas.
                       if((strlen(fecha_i)!=10)||(fecha_i[4]!='-')||(fecha_i[7]!='-')){
                            cout<<"Fecha Inicial Erronea"<<endl;
                            return EXIT_SUCCESS;
                       };
                       if((strlen(fecha_f)!=10)||(fecha_f[4]!='-')||(fecha_f[7]!='-')){
                            cout<<"Fecha Final Erronea"<<endl;
                            return EXIT_SUCCESS;
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
                       if((fecha_desde.tm_mon>12)||(fecha_desde.tm_mday>31)){
                            cout<<"Fecha Inicial Erronea"<<endl;
                            return EXIT_SUCCESS;
                       };
                       if((fecha_hasta.tm_mon>12)||(fecha_hasta.tm_mday>31)){
                            cout<<"Fecha Final Erronea"<<endl;
                            return EXIT_SUCCESS;
                       };

                       //verificamos el archivo y solicitamos la creacion del registro de las ventas
                       lineas_totales=contar_lineas(captura_arg);

                       if(lineas_totales==0){
                            cout<<"\nArchivo No Existente o Vacio\n\n"<<endl;
                            return EXIT_SUCCESS;
                       }else{

                            ventas = new registro_venta[lineas_totales];
                            crear_registro(ventas,captura_arg);
                            //en esta seccion se puede insertacion los "if" para limitar las fechas.
                        SumaMonto [0] = 0;
                        SumaMonto [1] = 0;
                        SumaMonto [2] = 0;
                        SumaMonto [3] = 0;
                        for(i=0;i<lineas_totales+1;i++)
                        {
                            if(fecha_desde.tm_year<= ventas[i].fecha_venta.tm_year && ventas[i].fecha_venta.tm_year <= fecha_hasta.tm_year){
                                if(fecha_desde.tm_mon<= ventas[i].fecha_venta.tm_mon && ventas[i].fecha_venta.tm_mon <= fecha_hasta.tm_mon){
                                    if(fecha_desde.tm_mday<= ventas[i].fecha_venta.tm_mday && ventas[i].fecha_venta.tm_mday <= fecha_hasta.tm_mday){
                                    /* Se considera que por enunciado las tiendas tienen el nombre indicado en el requerimiento
                                    * Array long long SumaMonto [4] para guardar montos por tienda
                                    * 0: CencoSux
                                    * 1: Falaferia
                                    * 2: Porahi
                                    * 3: Replay
                                    */
                                    Saca_Comillas(ventas[i].nombre_empresa);
                                         if (strcmp("CencoSux", NuevaPalabra) == 0) SumaMonto[0] = SumaMonto [0] + ventas[i].monto;
                                    else if (strcmp("Falaferia", NuevaPalabra) == 0) SumaMonto[1] = SumaMonto [1] + ventas[i].monto;
                                    else if (strcmp("Porahi", NuevaPalabra) == 0) SumaMonto[2] = SumaMonto [2] + ventas[i].monto;
                                    else if (strcmp("Replay", NuevaPalabra) == 0) SumaMonto[3] = SumaMonto [3] + ventas[i].monto;
                                    }
                                }
                            }
                        }
                        //cout<<"LA CANTIDAD DE REGISTROS RECONOCIDOS EN EL ARCHIVO ES: "<<lineas_totales<<endl;
                        cout<<" \nLAS VENTAS ENTRE LAS FECHAS INGRESADAS SE DEFINE EN 'grafico_venta.jpg'"<<endl;
                        cout<<"EN LA CARPETA DE EJECUCION DEL PROGRAMA"<<endl;
                        //cout<<"\tPara la empresa CencoSux\t: $ "<<SumaMonto[0]<<endl;
                        //cout<<"\tPara la empresa Falaferia\t: $ "<<SumaMonto[1]<<endl;
                        //cout<<"\tPara la empresa Porahi\t\t: $ "<<SumaMonto[2]<<endl;
                        //cout<<"\tPara la empresa Replay\t\t: $ "<<SumaMonto[3]<<endl;
                        cout<<""<<endl;

                       /*Seccion para generar jpg*/

                       blanco = gdImageColorAllocate(imagen, 255, 255, 255);
                       negro = gdImageColorAllocate(imagen, 0, 0, 0);

                        // Pintamos el fondo Blanco
                        gdImageFill(imagen, 0, 0, blanco);

                        // Se imprime el titulo
                        memset(titulo, 0, 513);
                        snprintf(titulo, 512, "LAS VENTAS ENTRE LAS FECHAS INGRESADAS  [%s] a [%s] SE DEFINE", fecha_i, fecha_f);
                        gdImageString(imagen, fuente, (int) IMG_WIDTH * 0.15, 10, (unsigned char *) titulo, negro);
                        fflush(stdout);

                        // Para la empresa CencoSux
                        memset(titulo, 0, 513);
                        snprintf(titulo, 512, "Para la empresa CencoSux: $ %lld", SumaMonto[0]);
                        gdImageString(imagen, fuente, (int) IMG_WIDTH * 0.1, 50, (unsigned char *) titulo, negro);
                        fflush(stdout);

                        // Para la empresa Falaferia
                        memset(titulo, 0, 513);
                        snprintf(titulo, 512, "Para la empresa Falaferia: $ %lld", SumaMonto[1]);
                        gdImageString(imagen, fuente, (int) IMG_WIDTH * 0.1, 70, (unsigned char *) titulo, negro);
                        fflush(stdout);

                        // Para la empresa Porahi
                        memset(titulo, 0, 513);
                        snprintf(titulo, 512, "Para la empresa Porahi: $ %lld", SumaMonto[2]);
                        gdImageString(imagen, fuente, (int) IMG_WIDTH * 0.1, 90, (unsigned char *) titulo, negro);
                        fflush(stdout);

                        // Para la empresa Replay
                        memset(titulo, 0, 513);
                        snprintf(titulo, 512, "Para la empresa Replay: $ %lld", SumaMonto[3]);
                        gdImageString(imagen, fuente, (int) IMG_WIDTH * 0.1, 110, (unsigned char *) titulo, negro);
                        fflush(stdout);

                        // Se enmarcan los valores en un rectangulo
                        gdImageLine(imagen, BORDE_ANCHO, BORDE_ALTO, (IMG_WIDTH - BORDE_ANCHO), BORDE_ALTO, negro);
                        gdImageLine(imagen, BORDE_ANCHO, (IMG_HEIGHT - BORDE_ALTO), (IMG_WIDTH - BORDE_ANCHO), (IMG_HEIGHT - BORDE_ALTO), negro);
                        gdImageLine(imagen, BORDE_ANCHO, BORDE_ALTO, BORDE_ANCHO, (IMG_HEIGHT - BORDE_ALTO), negro);
                        gdImageLine(imagen, (IMG_WIDTH - BORDE_ANCHO), BORDE_ALTO, (IMG_WIDTH - BORDE_ANCHO), (IMG_HEIGHT - BORDE_ALTO), negro);

                       // Se guarda la imagen en un archivo
                        archivo = fopen("grafico_ventas.jpg", "wb");
                        if (archivo != NULL) {
                            gdImageJpeg(imagen, archivo, 100);
                            fclose(archivo);
                        }
                        else cout<<"\n\n\t No se pudo crear el archivo"<<endl;
                        gdImageDestroy(imagen);

                       /*Final de Seccion para generar jpg*/

                       }
                       break;

         case 'v':
		       integrantes();
                       break;
         };
    }else
         cout<<"Opcion no valida, ingrese correctamente los parametros"<<endl;
    return EXIT_SUCCESS;
}
