#include <iostream>
#include "ArbolAVL.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void Mostrar(int &d, int FE){
	cout << d << "(" << FE << "),";
}
int main(int argc, char** argv) {
 // Un árbol de enteros
   AVL<int> ArbolInt;

   // Inserción de nodos en árbol:
   
   /*ArbolInt.Insertar(90);
   ArbolInt.Insertar(38);
   ArbolInt.Insertar(40);
   ArbolInt.Insertar(80);
   ArbolInt.Insertar(73);
   ArbolInt.Insertar(25);
   ArbolInt.Insertar(30);
   ArbolInt.Insertar(84);
   ArbolInt.Insertar(100);
   ArbolInt.Insertar(20);
   ArbolInt.Insertar(88);
   ArbolInt.Insertar(79);
   ArbolInt.Insertar(85);
   ArbolInt.Insertar(70);
   ArbolInt.Insertar(89);
   ArbolInt.Insertar(110);
   ArbolInt.Insertar(87);*/
   
   ArbolInt.Insertar(100);
   ArbolInt.Insertar(90);
   ArbolInt.Insertar(80);
   ArbolInt.Insertar(110);
   ArbolInt.Insertar(95);
   ArbolInt.Insertar(120);
   ArbolInt.Insertar(130);
   ArbolInt.Insertar(140);
   ArbolInt.Insertar(111);
   
   

   cout << "Altura de arbol " << ArbolInt.AlturaArbol() << endl;

   // Mostrar el árbol en tres ordenes distintos:
   cout << "InOrden: ";
   ArbolInt.InOrden(Mostrar);
   cout << endl;
   cout << "PreOrden: ";
   ArbolInt.PreOrden(Mostrar);
   cout << endl;
   cout << "PostOrden: ";
   ArbolInt.PostOrden(Mostrar);
   cout << endl;

	ArbolInt.Borrar(100);
	cout << endl;
	cout << "InOrden: ";
	ArbolInt.InOrden(Mostrar);
	cout << endl;
	cout << "PreOrden: ";
	ArbolInt.PreOrden(Mostrar);
	cout << endl;
	
	ArbolInt.Insertar(128);
   ArbolInt.Insertar(97);
   ArbolInt.Insertar(85);
   ArbolInt.Insertar(94);
   ArbolInt.Insertar(72);
   ArbolInt.Insertar(92);
   ArbolInt.Insertar(76);
   ArbolInt.Insertar(70);
   ArbolInt.Insertar(81);
   ArbolInt.Insertar(74);
   
	cout << endl;
	cout << "InOrden: ";
	ArbolInt.InOrden(Mostrar);
	cout << endl;
	cout << "PreOrden: ";
	ArbolInt.PreOrden(Mostrar);
	cout << endl;

   cout << endl;
   return 0;
}
