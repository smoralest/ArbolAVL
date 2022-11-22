
#ifndef ARBOLAVL_H
#define ARBOLAVL_H
#include <iostream>
#include <cstdlib>
using namespace std;


template <class T>
struct Nodo{T info;
			Nodo <T> *padre;
			int dato;
   			int FE;
   			Nodo <T> *izquierdo;
   			Nodo <T> *derecho;

};
template <class T>
class AVL {Nodo <T> *raiz;
	Nodo <T> *actual;
	Nodo <T> *izq;
	int IZQUIERDO,DERECHO;
	int contador;
	int altura;
   public: 
   // Constructor y destructor básicos:
   AVL(){raiz = NULL;
   		actual = NULL; 
//   		raiz->izquierdo = izq;

   		IZQUIERDO=0;
		DERECHO=0;
   } 
//   ~AVL() { Podar(raiz); }
   // Insertar en árbol ordenado:
	void Insertar(int);
   // Borrar un elemento del árbol:
	void Borrar(int);
   // Función de búsqueda:
	bool Buscar(int);
   // Comprobar si el árbol está vacío:
	bool Vacio(Nodo <T> *r) { return r==NULL; }
   // Comprobar si es un nodo hoja:
	bool EsHoja(Nodo <T> *r) { return !r->derecho && !r->izquierdo; }
   // Contar número de nodos:
	int NumeroNodos();
	int AlturaArbol();
   // Calcular altura de un dato:
	int Altura(int);
   // Devolver referencia al dato del nodo actual:
	int &ValorActual() { return actual->dato; }
   // Moverse al nodo raiz:
	void Raiz() { actual = raiz; }
   // Aplicar una función a cada elemento del árbol:
	void InOrden(void (*func)(int&, int) , Nodo <T>*nodo=NULL, bool r=true);
	void PreOrden(void (*func)(int&, int) , Nodo <T>*nodo=NULL, bool r=true);
	void PostOrden(void (*func)(int&, int) , Nodo <T>*nodo=NULL, bool r=true);
  private:
   // Funciones de equilibrado:
   void Equilibrar(Nodo <T>*nodo, int, bool);
   void RSI(Nodo<T>* nodo); // rotación sencilla izquierda
   void RSD(Nodo<T>* nodo);// rotación sencilla derecha
   void RDI(Nodo<T>* nodo);// rotación doble izquierda
   void RDD(Nodo<T>* nodo);// rotación doble derecha	
   // Funciones auxiliares
   void Podar(Nodo<T>* &);
   void auxContador(Nodo<T>*);
   void auxAltura(Nodo<T>*, int);
};

// Poda: borrar todos los nodos a partir de uno, incluido
template <class T>
void AVL<T>::Podar(Nodo<T>* &nodo){
   // Algoritmo recursivo, recorrido en postorden	
   if(nodo) {
      Podar(nodo->izquierdo); // Podar izquierdo
      Podar(nodo->derecho);   // Podar derecho
      delete nodo;            // Eliminar nodo
      nodo = NULL;
   }
}

// Insertar un dato en el árbol AVL
template <class T>
void AVL<T>::Insertar(int dat){
   Nodo <T>*padre = NULL;

   cout << "Insertar: " << dat << endl;
   actual = raiz;
   // Buscar el dato en el árbol, manteniendo un puntero al nodo padre
   while(!Vacio(actual) && dat != actual->dato) {
      padre = actual;
      cout<<"Entre al primer while"<<endl;
      if(dat > actual->dato) actual = actual->derecho;
      else if(dat < actual->dato) actual = actual->izquierdo;
   }

   // Si se ha encontrado el elemento, regresar sin insertar
   if(!Vacio(actual)) return;

   // Si padre es NULL, entonces el árbol estaba vacío, el nuevo nodo será
   // el nodo raiz
   if(Vacio(padre)){
	cout<<"Soy raiz"<<endl;
	raiz = new Nodo<T>;
	raiz->dato = dat;
   } 
 
   // Si el dato es menor que el que contiene el nodo padre, lo insertamos
   // en la rama izquierda
   else if(dat < padre->dato) {
   		cout<<"primer elseif"<<endl;
   		cout<<"Algo"<<endl;
//      	padre->izquierdo = new Nodo<T>;
		cout<<"soy el dato izquiero de papa"<<padre->izquierdo<<endl;
		padre->izquierdo->dato = dat;
		cout<<"soy el dato izquiero de papa"<<padre->izquierdo->dato<<endl;
		padre = padre->izquierdo;
      Equilibrar(padre, IZQUIERDO, true);
   }
   // Si el dato es mayor que el que contiene el nodo padre, lo insertamos
   // en la rama derecha
   else if(dat > padre->dato) {
   		cout<<"segundo elseif"<<endl;
//		padre->derecho =  new Nodo<T>;

    	padre->derecho->dato = dat;
		padre->derecho = padre;
    	Equilibrar(padre, DERECHO, true);
   }
     cout<<"Estoy valiendo verga aqui"<<endl;
}

// Equilibrar árbol AVL partiendo del nodo nuevo
template <class T>
void AVL<T>::Equilibrar(Nodo<T> *nodo, int rama, bool nuevo){
   bool salir = false;

   // Recorrer camino inverso actualizando valores de FE:
   while(nodo && !salir) {
   	cout<<"Hola soy rama"<<rama<<endl;
   	   	cout<<"Hola soy izquierdo"<<IZQUIERDO<<endl;
      if(nuevo)
         if(rama == IZQUIERDO) nodo->FE--; // Depende de si añadimos ...
         else                  nodo->FE++;
      else
         if(rama == IZQUIERDO) nodo->FE++; // ... o borramos
         else                  nodo->FE--;
      if(nodo->FE == 0) salir = true; // La altura de las rama que
                                      // empieza en nodo no ha variado,
                                      // salir de Equilibrar
      else if(nodo->FE == -2) { // Rotar a derechas y salir:
         if(nodo->izquierdo->FE == 1) RDD(nodo); // Rotación doble
         else RSD(nodo);                         // Rotación simple
         salir = true;
      }
      else if(nodo->FE == 2) {  // Rotar a izquierdas y salir:
         if(nodo->derecho->FE == -1) RDI(nodo); // Rotación doble
         else RSI(nodo);                        // Rotación simple
         salir = true;
      }
      if(nodo->padre) 
         if(nodo->padre->derecho == nodo) rama = DERECHO; else rama = IZQUIERDO;
      nodo = nodo->padre; // Calcular FE, siguiente nodo del camino.
   }   
}

// Rotación doble a derechas
template <class T>
void AVL<T>::RDD(Nodo<T>* nodo){
   cout << "RDD" << endl;
   Nodo <T> *Padre = nodo->padre;
   Nodo <T> *P = nodo;
   Nodo <T> *Q = P->izquierdo;
   Nodo <T> *R = Q->derecho;
   Nodo <T> *B = R->izquierdo;
   Nodo <T> *C = R->derecho;

   if(Padre) 
     if(Padre->derecho == nodo) Padre->derecho = R;
     else Padre->izquierdo = R;
   else raiz = R;

   // Reconstruir árbol:
   Q->derecho = B;
   P->izquierdo = C;
   R->izquierdo = Q;
   R->derecho = P;
   
   // Reasignar padres:
   R->padre = Padre;
   P->padre = Q->padre = R;
   if(B) B->padre = Q;
   if(C) C->padre = P;

   // Ajustar valores de FE:
   switch(R->FE) {
      case -1: Q->FE = 0; P->FE = 1; break;
      case 0:  Q->FE = 0; P->FE = 0; break;
      case 1:  Q->FE = -1; P->FE = 0; break;
   }
   R->FE = 0;
}

// Rotación doble a izquierdas
template <class T>
void AVL<T>::RDI(Nodo <T>* nodo){
   cout << "RDI" << endl;
   Nodo <T>*Padre = nodo->padre;
   Nodo	<T>*P = nodo;
   Nodo <T>*Q = P->derecho;
   Nodo <T>*R = Q->izquierdo;
   Nodo <T>*B = R->izquierdo;
   Nodo <T>*C = R->derecho;

   if(Padre)
     if(Padre->derecho == nodo) Padre->derecho = R;
     else Padre->izquierdo = R;
   else raiz = R;

   // Reconstruir árbol:
   P->derecho = B;
   Q->izquierdo = C;
   R->izquierdo = P;
   R->derecho = Q;
   
   // Reasignar padres:
   R->padre = Padre;
   P->padre = Q->padre = R;
   if(B) B->padre = P;
   if(C) C->padre = Q;

   // Ajustar valores de FE:
   switch(R->FE) {
      case -1: P->FE = 0; Q->FE = 1; break;
      case 0:  P->FE = 0; Q->FE = 0; break;
      case 1:  P->FE = -1; Q->FE = 0; break;
   }
   R->FE = 0;
}

// Rotación simple a derechas
template <class T>
void AVL<T>::RSD(Nodo<T>* nodo){
   cout << "RSD" << endl;
   Nodo <T>*Padre = nodo->padre;
   Nodo <T>*P = nodo;
   Nodo <T>*Q = P->izquierdo;
   Nodo <T>*B = Q->derecho;

   if(Padre) 
     if(Padre->derecho == P) Padre->derecho = Q;
     else Padre->izquierdo = Q;
   else raiz = Q;

   // Reconstruir árbol:
   P->izquierdo = B;
   Q->derecho = P;
   
   // Reasignar padres:
   P->padre = Q;
   if(B) B->padre = P;
   Q->padre = Padre;

   // Ajustar valores de FE:
   P->FE = 0;
   Q->FE = 0;
}

// Rotación simple a izquierdas
template <class T>
void AVL<T>::RSI(Nodo<T>* nodo){
   cout << "RSI" << endl;
   Nodo <T>*Padre = nodo->padre;
   Nodo <T>*P = nodo;
   Nodo <T>*Q = P->derecho;
   Nodo <T>*B = Q->izquierdo;

   if(Padre) 
     if(Padre->derecho == P) Padre->derecho = Q;
     else Padre->izquierdo = Q;
   else raiz = Q;

   // Reconstruir árbol:
   P->derecho = B;
   Q->izquierdo = P;
   
   // Reasignar padres:
   P->padre = Q;
   if(B) B->padre = P;
   Q->padre = Padre;
   
   // Ajustar valores de FE:
   P->FE = 0;
   Q->FE = 0;
}

// Eliminar un elemento de un árbol AVL
template <class T>
void AVL<T>::Borrar(int dat){
   Nodo <T>*padre = NULL;
   Nodo <T>*nodo;
   int aux;

   actual = raiz;
   // Mientras sea posible que el valor esté en el árbol
   while(!Vacio(actual)) {
      if(dat == actual->dato) { // Si el valor está en el nodo actual
         if(EsHoja(actual)) { // Y si además es un nodo hoja: lo borramos
            if(padre) // Si tiene padre (no es el nodo raiz)
               // Anulamos el puntero que le hace referencia
               if(padre->derecho == actual) padre->derecho = NULL;
               else if(padre->izquierdo == actual) padre->izquierdo = NULL;
            delete actual; // Borrar el nodo
            actual = NULL;
            // El nodo padre del actual puede ser ahora un nodo hoja, por lo tanto su
            // FE es cero, pero debemos seguir el camino a partir de su padre, si existe.
            if((padre->derecho == actual && padre->FE == 1) ||
               (padre->izquierdo == actual && padre->FE == -1)) {
               padre->FE = 0;
               actual = padre;
               padre = actual->padre;
            }
            if(padre)
               if(padre->derecho == actual) Equilibrar(padre, DERECHO, false);
               else                         Equilibrar(padre, IZQUIERDO, false);
            return;
         }
         else { // Si el valor está en el nodo actual, pero no es hoja
            // Buscar nodo
            padre = actual;
            // Buscar nodo más izquierdo de rama derecha
            if(actual->derecho) {
               nodo = actual->derecho;
               while(nodo->izquierdo) {
                  padre = nodo;
                  nodo = nodo->izquierdo;
               }
            }
            // O buscar nodo más derecho de rama izquierda
            else {
               nodo = actual->izquierdo;
               while(nodo->derecho) {
                  padre = nodo;
                  nodo = nodo->derecho;
               }
            }
            // Intercambiar valores de no a borrar u nodo encontrado
            // y continuar, cerrando el bucle. El nodo encontrado no tiene
            // por qué ser un nodo hoja, cerrando el bucle nos aseguramos
            // de que sólo se eliminan nodos hoja.
            aux = actual->dato;
            actual->dato = nodo->dato;
            nodo->dato = aux;
            actual = nodo;
         }
      }
      else { // Todavía no hemos encontrado el valor, seguir buscándolo
         padre = actual;
         if(dat > actual->dato) actual = actual->derecho;
         else if(dat < actual->dato) actual = actual->izquierdo;
      }
   }
}

// Recorrido de árbol en inorden, aplicamos la función func, que tiene
// el prototipo:
// void func(int&, int);
template <class T>
void AVL<T>::InOrden(void (*func)(int&, int) , Nodo <T>*nodo, bool r){
   if(r) nodo = raiz;
   if(nodo->izquierdo) InOrden(func, nodo->izquierdo, false);
   func(nodo->dato, nodo->FE);
   if(nodo->derecho) InOrden(func, nodo->derecho, false);
}

// Recorrido de árbol en preorden, aplicamos la función func, que tiene
// el prototipo:
// void func(int&, int);
template <class T>
void AVL<T>::PreOrden(void (*func)(int&, int), Nodo <T>*nodo, bool r){
   if(r) nodo = raiz;
   func(nodo->dato, nodo->FE);
   if(nodo->izquierdo) PreOrden(func, nodo->izquierdo, false);
   if(nodo->derecho) PreOrden(func, nodo->derecho, false);
}

// Recorrido de árbol en postorden, aplicamos la función func, que tiene
// el prototipo:
// void func(int&, int);
template <class T>
void AVL<T>::PostOrden(void (*func)(int&, int), Nodo <T>*nodo, bool r){
   if(r) nodo = raiz;
   if(nodo->izquierdo) PostOrden(func, nodo->izquierdo, false);
   if(nodo->derecho) PostOrden(func, nodo->derecho, false);
   func(nodo->dato, nodo->FE);
}

// Buscar un valor en el árbol
template <class T>
bool AVL<T>::Buscar(int dat){
   actual = raiz;

   // Todavía puede aparecer, ya que quedan nodos por mirar
   while(!Vacio(actual)) {
      if(dat == actual->dato) return true; // dato encontrado
      else if(dat > actual->dato) actual = actual->derecho; // Seguir
      else if(dat < actual->dato) actual = actual->izquierdo;
   }
   return false; // No está en árbol
}

// Calcular la altura del nodo que contiene el dato dat
template <class T>
int AVL<T>::Altura(int dat){
   int altura = 0;
   actual = raiz;

   // Todavía puede aparecer, ya que quedan nodos por mirar
   while(!Vacio(actual)) {
      if(dat == actual->dato) return altura; // dato encontrado
      else {
         altura++; // Incrementamos la altura, seguimos buscando
         if(dat > actual->dato) actual = actual->derecho;
         else if(dat < actual->dato) actual = actual->izquierdo;
      }
   }
   return -1; // No está en árbol
}

// Contar el número de nodos
template <class T>
int AVL<T>::NumeroNodos(){
   contador = 0;

   auxContador(raiz); // FUnción auxiliar
   return contador;
}

// Función auxiliar para contar nodos. Función recursiva de recorrido en
//   preorden, el proceso es aumentar el contador
template <class T>
void AVL<T>::auxContador(Nodo <T>*nodo){
   contador++;  // Otro nodo
   // Continuar recorrido
   if(nodo->izquierdo) auxContador(nodo->izquierdo);
   if(nodo->derecho)   auxContador(nodo->derecho);
}

// Calcular la altura del árbol, que es la altura del nodo de mayor altura.
template <class T>
int AVL<T>::AlturaArbol(){
   altura = 0;

   auxAltura(raiz, 0); // Función auxiliar
   return altura;
}

// Función auxiliar para calcular altura. Función recursiva de recorrido en
// postorden, el proceso es actualizar la altura sólo en nodos hojas de mayor
// altura de la máxima actual
template <class T>
void AVL<T>::auxAltura(Nodo <T>*nodo, int a){
   // Recorrido postorden
   if(nodo->izquierdo) auxAltura(nodo->izquierdo, a+1);
   if(nodo->derecho)   auxAltura(nodo->derecho, a+1);
   // Proceso, si es un nodo hoja, y su altura es mayor que la actual del
   // árbol, actualizamos la altura actual del árbol
   if(EsHoja(nodo) && a > altura) altura = a;
}

// Función de prueba para recorridos del árbol
//template <class T>
//void Mostrar(int &d, int FE)
//{
//   cout << d << "(" << FE << "),";
//}
#endif
