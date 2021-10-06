/*

JAVIER GÓMEZ MORALEDA, 2021.

IMPLEMENTACIÓN DEL MONTÍCULO BINOMIAL PARA LA ASIGNATURA MÉTODOS ALGORÍTMICOS EN RESOLUCIÓN DE PROBLEMAS.

*/

#pragma once

#include <iostream>
#include "dcola.h"

using namespace std;

/* Clase Montículo Binomial. */
class MonticuloBinomial {

	public:

		/* Clase interna Nodo. Contiene varios punteros, un valor elem y el grado del subarbol que representa. */
		class Nodo {
		public:

			/* Constructor de un nodo que representa a un árbol con 1 elemento */
			Nodo(int elem) : _elem(elem), _hijo(NULL), _padre(NULL), _hermano(NULL), _grado(0) {}

			/* Constructor de un nodo con el resto de parámetros */
			Nodo(int elem, Nodo* hijo, Nodo* padre, Nodo* hermano, int grado) : _elem(elem), _hijo(hijo), _padre(padre), _hermano(hermano), _grado(grado) {}

			/* Elemento contenido en cada nodo, en nuestro caso un entero. */
			int _elem;

			/* Puntero al hijo más a la izquierda */
			Nodo* _hijo;

			/* Puntero al padre */
			Nodo* _padre;

			/* Puntero al hermano de la derecha */
			Nodo* _hermano;

			/* Grado del árbol binomial */
			int _grado;
		};

		/* Constructor de un montículo binomial de un único elemento. */
		MonticuloBinomial(int elem) : _inicio(new Nodo(elem)), _minimo(_inicio), _anteriorMinimo(NULL) {}

		/* Constructor de un montículo binomial con un nodo de inicio.
		   (Utilizado si hemos inicializado un nodo en concreto)
	     */
		MonticuloBinomial(Nodo* nodo) : _inicio(nodo), _minimo(NULL), _anteriorMinimo(NULL) {
			actualizaMinimoMonticulo();
		}

		/*Devuelve un puntero al nodo mínimo. */
		Nodo* consultaMinimoMonticulo() {
			return _minimo;
		}

		/* Une dos monticulos binomiales en uno. */
		void unionMonticulo(MonticuloBinomial m2) {
			
			//Función auxiliar para unir todas las raices
			unionAuxiliarMonticulo(m2);

			if (_inicio != NULL) {

				//Inicialización de nodos
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

					//Si tengo exáctamente dos árboles con grados iguales, tengo que unirlos
					else {

						//Si el primero es menor o igual, cuelgo el segundo del mismo
						if (actual->_elem <= siguiente->_elem) {
							actual->_hermano = siguiente->_hermano;
							unionArbolBinomial(siguiente, actual);
						}

						//Si el segundo es mayor, cuelgo el primero del mismo
						else {

							//Si anterior no existe, significa que el primer nodo será hijo del segundo
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

			//Función auxiliar para actualizar el mínimo del montículo
			actualizaMinimoMonticulo();
		}

		/* Inserta un elemento nuevo en el montículo. */
		void insercionMonticulo(int elem) {

			//Creo un nuevo montículo a partir del elemento
			MonticuloBinomial* m2 = new MonticuloBinomial(elem);
			
			//Uno ambos montículos
			unionMonticulo(*m2);
		}

		/* Elimina el mínimo del montículo y devuelve el nuevo nodo mínimo. */
		Nodo* eliminarMinimoMonticulo() {

			if (_inicio == _minimo && _inicio->_hermano == NULL && _inicio->_grado == 0) {
				cout << "NO PUEDES ELIMINAR EL MINIMO DE UN MONTICULO CON 1 ELEMENTO!!" << endl;
			}

			else {

				//Si el mínimo es un árbol de grado 0, no tendra hijos
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

					//Desengancho el nodo mínimo de la raíz
					if (antMinimo != NULL) {
						antMinimo->_hermano = minimo->_hermano;
					}

					//Punteros para recorrer los hijos del mínimo
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

					//Creo un nuevo montículo binomial a partir de los hijos
					MonticuloBinomial* m2 = new MonticuloBinomial(anterior);

					//Si ocurre esta situación, significa que sólo tengo 1 árbol en mi montículo, por lo que el nuevo montículo debe ser construido con los hijos
					if (minimo == _inicio && minimo->_hermano == NULL) {
						_inicio = m2->_inicio;
					}
					else {

						//Si el primer árbol del montículo contenía el mínimo
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

		/* Decrece una clave del montículo dado su puntero. */
		void decrecerClaveMonticulo(Nodo* p, int k) {

			//Me guardo el mínimo anterior por si cambia
			int minimo = _minimo->_elem;

			//Si el nuevo valor es mayor, la operación no tiene efecto
			if (p->_elem < k) {
				cout << "El valor k es mayor que la clave." << endl;
			}

			else {

				//Cambio el valor del elemento de p
				p->_elem = k;

				//Puntero al padre
				Nodo* padre = p->_padre;

				//Voy comparando si es menor que su padre hasta que he llegado a la raíz, o bien el padre es menos
				while (padre != NULL && p->_elem < padre->_elem) {
					
					//Intercambio sus elementos
					int aux = padre->_elem;
					padre->_elem = p->_elem;
					p->_elem = aux;

					//Actualizo punteros
					p = padre;
					padre = p->_padre;
				}

				//Si k es menor que el mínimo, tengo que actualizar los punteros.
				if (k < minimo) {
					actualizaMinimoMonticulo();
				}
			}
		}

		/* Función que imprime el montículo por niveles. Recorro la raíz principal monstrando el recorrido por niveles de todos sus árboles. */
		void imprimeMonticulo() {

			//Puntero para recorrer el montículo
			Nodo* recorrido = _inicio;

			//Bucle principal. Cada iteración es la impresión de un árbol.
			while (recorrido != NULL) {

				//Imprimo el grado de su árbol
				cout << "ARBOL DE GRADO " << recorrido->_grado << ": " << endl;

				//Cola de nodos doblemente enlazada. En ella cada nodo irá guardando sus hijos.
				DCola<Nodo*> c;

				//Añado el nodo raíz
				c.pon_final(recorrido);

				//Mientras que la cola siga teniendo nodos de este árbol
				while (!c.esVacia()) {

					//Cojo el primer elemento y lo quito de la cola
					Nodo* muestra = c.primero();
					c.quita_ppio();

					//Lo muestro por pantalla
					cout << muestra->_elem << " ";

					//Puntero para recorrer sus hijos
					Nodo* hijos = muestra->_hijo;

					//Añado todos los hijos de este nodo (voy avanzando en los hermanos hasta llegar al último)
					while (hijos != NULL) {
						c.pon_final(hijos);
						hijos = hijos->_hermano;
					}

					//Al llegar aquí, tendre todos sus hijos y comenzará todo este proceso con los mismos.
				}

				//Avanzo el recorrido de las raíces
				recorrido = recorrido->_hermano;
				cout << endl << endl;
			}
		}

		/* Función que libera toda la memoria ocupada por un montículo. */
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

		/* Devuelve el puntero del último hijo más a la izquierda del árbol más a la derecha de mi raíz principal. */
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

		/* Puntero a la primera raíz del árbol */
		Nodo* _inicio;

		/* Puntero al nodo mínimo */
		Nodo* _minimo;

		/* Puntero al nodo anterior al mínimo (puede ser nulo si _mínimo = _inicio) */
		Nodo* _anteriorMinimo;

		/* Función que une dos árboles binomiales en uno. p1 será el hijo de p2. */
		void unionArbolBinomial(Nodo* p1, Nodo* p2) {
			p1->_padre = p2;
			p1->_hermano = p2->_hijo;
			p2->_hijo = p1;
			p2->_grado += 1;
		}

		/* Unión auxiliar. Esta función sirve para recorrer los dos árboles binomiales, e ir insertando en la raíz principal, los nodos raices del montículo b2 en orden por su grado. */
		void unionAuxiliarMonticulo(MonticuloBinomial& m2) {

			//Puntero para recorrer el primer montículo
			Nodo* recorrido_m1 = _inicio;

			//Puntero para recorrer el segundo montículo
			Nodo* recorrido_m2 = m2._inicio;

			//Puntero al nodo anterior para insertar
			Nodo* anterior = NULL;

			//Inicialización del puntero anterior

			//Si el grado del primero es mayor, el primer nodo de m2 será el primero de la lista
			if (recorrido_m1->_grado > recorrido_m2->_grado) {
				_inicio = recorrido_m2;
				anterior = recorrido_m2;
				recorrido_m2 = recorrido_m2->_hermano;
			}

			//En otro caso, el primero será el de m1 que ya estará contenido en el inicio
			else {
				anterior = recorrido_m1;
				recorrido_m1 = recorrido_m1->_hermano;
			}

			//Recorrido hasta haber acabado ambos montículos
			while (recorrido_m1 != NULL || recorrido_m2 != NULL) {

				//Si aún tengo raíces en ambos árboles, comparo e inserto.
				if (recorrido_m1 != NULL && recorrido_m2 != NULL) {

					//Si el de m1 es mayor, el anterior apunta a m2 y mantengo m1
					if (recorrido_m1->_grado > recorrido_m2->_grado) {
						anterior->_hermano = recorrido_m2;
						recorrido_m2 = recorrido_m2->_hermano;
					}

					//En caso contrario el anterior apuntará a m1
					else {
						anterior->_hermano = recorrido_m1;
						recorrido_m1 = recorrido_m1->_hermano;
					}
				}

				//Si sólo tengo raíces restantes en m1
				else if (recorrido_m1 != NULL) {
					anterior->_hermano = recorrido_m1;
					recorrido_m1 = recorrido_m1->_hermano;
				}

				//Si sólo tengo raíces restantes en m2
				else {
					anterior->_hermano = recorrido_m2;
					recorrido_m2 = recorrido_m2->_hermano;
				}

				//Avanzo el puntero anterior a su hermano
				anterior = anterior->_hermano;

			}
		}

		/* Función para actualizar el mínimo. Recorre el montículo en busca del elemento mínimo y actualiza los punteros mínimo y anterior. */
		void actualizaMinimoMonticulo() {

			//Recorrido de los hermanos de nodo inicial
			Nodo* antRecorrido = NULL;
			Nodo* recorrido = _inicio;

			//Punteros con el elemento mínimo y el nodo anterior
			_anteriorMinimo = NULL;
			_minimo = recorrido;

			//Recorro todos las raíces
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