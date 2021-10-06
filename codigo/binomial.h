/*

JAVIER G�MEZ MORALEDA, 2021.

IMPLEMENTACI�N DEL MONT�CULO BINOMIAL PARA LA ASIGNATURA M�TODOS ALGOR�TMICOS EN RESOLUCI�N DE PROBLEMAS.

*/

#pragma once

#include <iostream>
#include "dcola.h"

using namespace std;

/* Clase Mont�culo Binomial. */
class MonticuloBinomial {

	public:

		/* Clase interna Nodo. Contiene varios punteros, un valor elem y el grado del subarbol que representa. */
		class Nodo {
		public:

			/* Constructor de un nodo que representa a un �rbol con 1 elemento */
			Nodo(int elem) : _elem(elem), _hijo(NULL), _padre(NULL), _hermano(NULL), _grado(0) {}

			/* Constructor de un nodo con el resto de par�metros */
			Nodo(int elem, Nodo* hijo, Nodo* padre, Nodo* hermano, int grado) : _elem(elem), _hijo(hijo), _padre(padre), _hermano(hermano), _grado(grado) {}

			/* Elemento contenido en cada nodo, en nuestro caso un entero. */
			int _elem;

			/* Puntero al hijo m�s a la izquierda */
			Nodo* _hijo;

			/* Puntero al padre */
			Nodo* _padre;

			/* Puntero al hermano de la derecha */
			Nodo* _hermano;

			/* Grado del �rbol binomial */
			int _grado;
		};

		/* Constructor de un mont�culo binomial de un �nico elemento. */
		MonticuloBinomial(int elem) : _inicio(new Nodo(elem)), _minimo(_inicio), _anteriorMinimo(NULL) {}

		/* Constructor de un mont�culo binomial con un nodo de inicio.
		   (Utilizado si hemos inicializado un nodo en concreto)
	     */
		MonticuloBinomial(Nodo* nodo) : _inicio(nodo), _minimo(NULL), _anteriorMinimo(NULL) {
			actualizaMinimoMonticulo();
		}

		/*Devuelve un puntero al nodo m�nimo. */
		Nodo* consultaMinimoMonticulo() {
			return _minimo;
		}

		/* Une dos monticulos binomiales en uno. */
		void unionMonticulo(MonticuloBinomial m2) {
			
			//Funci�n auxiliar para unir todas las raices
			unionAuxiliarMonticulo(m2);

			if (_inicio != NULL) {

				//Inicializaci�n de nodos
				Nodo* anterior = NULL;
				Nodo* actual = _inicio;
				Nodo* siguiente = actual->_hermano;

				//Bucle para recorrer la lista principal de m1
				while (siguiente != NULL) {

					//Si tienen grados distintos o tengo 3 grados iguales seguidos me "salto" ese nodo
					if ((actual->_grado != siguiente->_grado) || siguiente->_hermano != NULL && (actual->_grado == siguiente->_hermano->_grado)) {
						anterior = actual;
						actual = siguiente;
						siguiente = siguiente->_hermano;
					}

					//Si tengo ex�ctamente dos �rboles con grados iguales, tengo que unirlos
					else {

						//Si el primero es menor o igual, cuelgo el segundo del mismo
						if (actual->_elem <= siguiente->_elem) {
							actual->_hermano = siguiente->_hermano;
							unionArbolBinomial(siguiente, actual);
						}

						//Si el segundo es mayor, cuelgo el primero del mismo
						else {

							//Si anterior no existe, significa que el primer nodo ser� hijo del segundo
							if (anterior == NULL) {
								_inicio = siguiente;
							}

							//En otro caso, estoy entre nodos
							else {
								anterior->_hermano = siguiente;
							}

							unionArbolBinomial(actual, siguiente);
							actual = siguiente;
						}
					}

					//Actualizo puntero siguiente
					siguiente = actual->_hermano;
				
				}
			}

			//Funci�n auxiliar para actualizar el m�nimo del mont�culo
			actualizaMinimoMonticulo();
		}

		/* Inserta un elemento nuevo en el mont�culo. */
		void insercionMonticulo(int elem) {

			//Creo un nuevo mont�culo a partir del elemento
			MonticuloBinomial* m2 = new MonticuloBinomial(elem);
			
			//Uno ambos mont�culos
			unionMonticulo(*m2);
		}

		/* Elimina el m�nimo del mont�culo y devuelve el nuevo nodo m�nimo. */
		Nodo* eliminarMinimoMonticulo() {

			if (_inicio == _minimo && _inicio->_hermano == NULL && _inicio->_grado == 0) {
				cout << "NO PUEDES ELIMINAR EL MINIMO DE UN MONTICULO CON 1 ELEMENTO!!" << endl;
			}

			else {

				//Si el m�nimo es un �rbol de grado 0, no tendra hijos
				if (_minimo->_grado == 0) {
					_inicio = _inicio->_hermano;
					actualizaMinimoMonticulo();
				}

				else {
					//Guardo los punteros viejos
					Nodo* antMinimo = _anteriorMinimo;
					Nodo* minimo = _minimo;
					_anteriorMinimo = NULL;
					_minimo = NULL;

					//Desengancho el nodo m�nimo de la ra�z
					if (antMinimo != NULL) {
						antMinimo->_hermano = minimo->_hermano;
					}

					//Punteros para recorrer los hijos del m�nimo
					Nodo* recorrido = minimo->_hijo;
					Nodo* anterior = NULL;

					//Desengancho cada hijo de su padre e invierto el orden
					while (recorrido != NULL) {

						//Lo desengancho de su padre
						recorrido->_padre = NULL;

						//Me guardo un nodo auxiliar con su hermano
						Nodo* aux = recorrido->_hermano;

						//Lo invierto haciendo que apunte al anterior
						recorrido->_hermano = anterior;

						//El anterior pasa a ser el actual
						anterior = recorrido;

						//El actual pasa a ser su antiguo hermano
						recorrido = aux;
					}

					//Creo un nuevo mont�culo binomial a partir de los hijos
					MonticuloBinomial* m2 = new MonticuloBinomial(anterior);

					//Si ocurre esta situaci�n, significa que s�lo tengo 1 �rbol en mi mont�culo, por lo que el nuevo mont�culo debe ser construido con los hijos
					if (minimo == _inicio && minimo->_hermano == NULL) {
						_inicio = m2->_inicio;
					}
					else {

						//Si el primer �rbol del mont�culo conten�a el m�nimo
						if (_inicio == minimo) {
							_inicio = minimo->_hermano;
						}

						unionMonticulo(*m2);
					}
					actualizaMinimoMonticulo();
					delete minimo;
				}
			}
			
			return _minimo;
		}

		/* Decrece una clave del mont�culo dado su puntero. */
		void decrecerClaveMonticulo(Nodo* p, int k) {

			//Me guardo el m�nimo anterior por si cambia
			int minimo = _minimo->_elem;

			//Si el nuevo valor es mayor, la operaci�n no tiene efecto
			if (p->_elem < k) {
				cout << "El valor k es mayor que la clave." << endl;
			}

			else {

				//Cambio el valor del elemento de p
				p->_elem = k;

				//Puntero al padre
				Nodo* padre = p->_padre;

				//Voy comparando si es menor que su padre hasta que he llegado a la ra�z, o bien el padre es menos
				while (padre != NULL && p->_elem < padre->_elem) {
					
					//Intercambio sus elementos
					int aux = padre->_elem;
					padre->_elem = p->_elem;
					p->_elem = aux;

					//Actualizo punteros
					p = padre;
					padre = p->_padre;
				}

				//Si k es menor que el m�nimo, tengo que actualizar los punteros.
				if (k < minimo) {
					actualizaMinimoMonticulo();
				}
			}
		}

		/* Funci�n que imprime el mont�culo por niveles. Recorro la ra�z principal monstrando el recorrido por niveles de todos sus �rboles. */
		void imprimeMonticulo() {

			//Puntero para recorrer el mont�culo
			Nodo* recorrido = _inicio;

			//Bucle principal. Cada iteraci�n es la impresi�n de un �rbol.
			while (recorrido != NULL) {

				//Imprimo el grado de su �rbol
				cout << "ARBOL DE GRADO " << recorrido->_grado << ": " << endl;

				//Cola de nodos doblemente enlazada. En ella cada nodo ir� guardando sus hijos.
				DCola<Nodo*> c;

				//A�ado el nodo ra�z
				c.pon_final(recorrido);

				//Mientras que la cola siga teniendo nodos de este �rbol
				while (!c.esVacia()) {

					//Cojo el primer elemento y lo quito de la cola
					Nodo* muestra = c.primero();
					c.quita_ppio();

					//Lo muestro por pantalla
					cout << muestra->_elem << " ";

					//Puntero para recorrer sus hijos
					Nodo* hijos = muestra->_hijo;

					//A�ado todos los hijos de este nodo (voy avanzando en los hermanos hasta llegar al �ltimo)
					while (hijos != NULL) {
						c.pon_final(hijos);
						hijos = hijos->_hermano;
					}

					//Al llegar aqu�, tendre todos sus hijos y comenzar� todo este proceso con los mismos.
				}

				//Avanzo el recorrido de las ra�ces
				recorrido = recorrido->_hermano;
				cout << endl << endl;
			}
		}

		/* Funci�n que libera toda la memoria ocupada por un mont�culo. */
		void borraMonticulo(Nodo* n) {

			//Si tiene hermanos, hago una llamada recursiva
			if (n->_hermano != NULL) {
				borraMonticulo(n->_hermano);
			}

			//Si tiene hijos, hago una llamada recursiva
			if (n->_hijo != NULL) {
				borraMonticulo(n->_hijo);
			}

			delete n;
		}

		/* Devuelve un puntero al nodo inicio. */
		Nodo* devuelveInicio() {
			return _inicio;
		}

		//Utilizada para conseguir el puntero al nodo que me interesa del ejemplo de incrementar
		Nodo* ejemploDecrementar() {
			return _inicio->_hermano->_hermano->_hijo->_hijo->_hijo;
		}

		/* Devuelve el puntero del �ltimo hijo m�s a la izquierda del �rbol m�s a la derecha de mi ra�z principal. */
		Nodo* devuelvePunteroNodo() {
			Nodo* nodo = _inicio;
			while (nodo->_hermano != NULL) {
				nodo = nodo->_hermano;
			}
			while (nodo->_hijo != NULL) {
				nodo = nodo->_hijo;
			}
			return nodo;
		}

	private:

		/* Puntero a la primera ra�z del �rbol */
		Nodo* _inicio;

		/* Puntero al nodo m�nimo */
		Nodo* _minimo;

		/* Puntero al nodo anterior al m�nimo (puede ser nulo si _m�nimo = _inicio) */
		Nodo* _anteriorMinimo;

		/* Funci�n que une dos �rboles binomiales en uno. p1 ser� el hijo de p2. */
		void unionArbolBinomial(Nodo* p1, Nodo* p2) {
			p1->_padre = p2;
			p1->_hermano = p2->_hijo;
			p2->_hijo = p1;
			p2->_grado += 1;
		}

		/* Uni�n auxiliar. Esta funci�n sirve para recorrer los dos �rboles binomiales, e ir insertando en la ra�z principal, los nodos raices del mont�culo b2 en orden por su grado. */
		void unionAuxiliarMonticulo(MonticuloBinomial& m2) {

			//Puntero para recorrer el primer mont�culo
			Nodo* recorrido_m1 = _inicio;

			//Puntero para recorrer el segundo mont�culo
			Nodo* recorrido_m2 = m2._inicio;

			//Puntero al nodo anterior para insertar
			Nodo* anterior = NULL;

			//Inicializaci�n del puntero anterior

			//Si el grado del primero es mayor, el primer nodo de m2 ser� el primero de la lista
			if (recorrido_m1->_grado > recorrido_m2->_grado) {
				_inicio = recorrido_m2;
				anterior = recorrido_m2;
				recorrido_m2 = recorrido_m2->_hermano;
			}

			//En otro caso, el primero ser� el de m1 que ya estar� contenido en el inicio
			else {
				anterior = recorrido_m1;
				recorrido_m1 = recorrido_m1->_hermano;
			}

			//Recorrido hasta haber acabado ambos mont�culos
			while (recorrido_m1 != NULL || recorrido_m2 != NULL) {

				//Si a�n tengo ra�ces en ambos �rboles, comparo e inserto.
				if (recorrido_m1 != NULL && recorrido_m2 != NULL) {

					//Si el de m1 es mayor, el anterior apunta a m2 y mantengo m1
					if (recorrido_m1->_grado > recorrido_m2->_grado) {
						anterior->_hermano = recorrido_m2;
						recorrido_m2 = recorrido_m2->_hermano;
					}

					//En caso contrario el anterior apuntar� a m1
					else {
						anterior->_hermano = recorrido_m1;
						recorrido_m1 = recorrido_m1->_hermano;
					}
				}

				//Si s�lo tengo ra�ces restantes en m1
				else if (recorrido_m1 != NULL) {
					anterior->_hermano = recorrido_m1;
					recorrido_m1 = recorrido_m1->_hermano;
				}

				//Si s�lo tengo ra�ces restantes en m2
				else {
					anterior->_hermano = recorrido_m2;
					recorrido_m2 = recorrido_m2->_hermano;
				}

				//Avanzo el puntero anterior a su hermano
				anterior = anterior->_hermano;

			}
		}

		/* Funci�n para actualizar el m�nimo. Recorre el mont�culo en busca del elemento m�nimo y actualiza los punteros m�nimo y anterior. */
		void actualizaMinimoMonticulo() {

			//Recorrido de los hermanos de nodo inicial
			Nodo* antRecorrido = NULL;
			Nodo* recorrido = _inicio;

			//Punteros con el elemento m�nimo y el nodo anterior
			_anteriorMinimo = NULL;
			_minimo = recorrido;

			//Recorro todos las ra�ces
			while (recorrido->_hermano != NULL) {

				antRecorrido = recorrido;
				recorrido = recorrido->_hermano;

				//Si existe un elemento menor, lo actualizo
				if (_minimo->_elem > recorrido->_elem) {
					_minimo = recorrido;
					_anteriorMinimo = antRecorrido;
				}
			}
		}
};