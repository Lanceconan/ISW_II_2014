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

/*Constantes*/
#define _TIME_
#define N 15

/*compilar este archivo con el siguiente código: g++ tarea01.cpp -o Ej -I/usr/include/postgresql -I/usr/include -lpq */

using namespace std;

/*Variables Globales*/

PGconn *cnn = NULL;
PGresult *result = NULL, *re2=NULL;

const char *host = "146.83.181.4";
const char *port = "6432";
const char *schema = "isw";
const char *dataBase = "iswdb";
const char *user = "estisw";
const char *passwd = "estisw";


/*Funcion principal y cuerpo del programa*/
int main(int argc, char *argv[])
{
/*Variables de la funcion principal*/

}
