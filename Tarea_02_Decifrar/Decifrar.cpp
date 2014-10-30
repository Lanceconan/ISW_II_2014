#include <iostream>
#include <fstream>
using namespace std;

int main () {
 fstream ParteUno, ParteDos;
 char LetraUno, LetraDos;
 ofstream Salida("TextoSalida.txt");
 ParteUno.open ("p1.txt", ios::in);
 ParteDos.open ("p2.txt", ios::in);
 if (ParteUno.is_open()&&ParteUno.is_open()) {
 while (! ParteUno.eof() ) {
 ParteUno >> LetraUno;
 ParteDos >> LetraDos;
 Salida << LetraUno;
 Salida << LetraDos;
 cout << LetraUno << " ";
 cout << LetraDos << " ";
 }
 ParteUno.close();
 ParteDos.close();
 }
 else cout << "Fichero inexistente" << endl;
 return 0;
}
