/*

JAVIER GÓMEZ MORALEDA, 2021.

FICHERO CON CASOS DE PRUEBA DEL MONTÍCULO BINOMIAL PARA LA ASIGNATURA MÉTODOS ALGORÍTMICOS EN RESOLUCIÓN DE PROBLEMAS.

*/

#include <iostream>
#include<stdio.h>
#include "binomial.h"

using namespace std;


void ejemploUnion();
void ejemploBorradoMinimo();
void ejemploDecrementar();


int main() {

	//Menú que se mostrará en la ejecución del programa
	int opcion = 0;
	do {
		
		cout << "MONTICULO BINOMIAL" << endl << "REALIZADO POR JAVIER GOMEZ MORALEDA (2021)." << endl << endl;
		cout << "Ejemplos de ejecucion: " << endl;
		cout << "1. Ejemplo de la union de dos monticulos." << endl;
		cout << "2. Ejemplo del borrado del minimo de un monticulo." << endl;
		cout << "3. Ejemplo de decrementar un elemento del monticulo." << endl << endl;
		cout << "0. Salir." << endl << endl;
		cout << "Introduce una opcion: ";
		cin >> opcion;
		cout << endl;

		switch (opcion) {
		case 0: break;
		case 1: ejemploUnion();
			break;
		case 2: ejemploBorradoMinimo();
			break;
		case 3: ejemploDecrementar();
			break;
		default: cout << "La opcion introducida no es valida." << endl << endl;
			break;
		}

	} while (opcion != 0);

	return 0;
}


/* Ejemplo de la unión de dos montículos. */
void ejemploUnion() {

	cout << "MONTICULO 1" << endl << endl;
	MonticuloBinomial* monticulo1 = new MonticuloBinomial(41);
	monticulo1->insercionMonticulo(28);
	monticulo1->insercionMonticulo(33);
	monticulo1->insercionMonticulo(15);
	monticulo1->insercionMonticulo(25);
	monticulo1->insercionMonticulo(7);
	monticulo1->insercionMonticulo(12);
	monticulo1->imprimeMonticulo();
	cout << "MINIMO DEL MONTICULO 1: " << monticulo1->consultaMinimoMonticulo()->_elem << endl << endl;

	cout << "MONTICULO 2" << endl << endl;
	MonticuloBinomial* monticulo2 = new MonticuloBinomial(55);
	monticulo2->insercionMonticulo(45);
	monticulo2->insercionMonticulo(32);
	monticulo2->insercionMonticulo(30);
	monticulo2->insercionMonticulo(24);
	monticulo2->insercionMonticulo(23);
	monticulo2->insercionMonticulo(22);
	monticulo2->insercionMonticulo(8);
	monticulo2->insercionMonticulo(50);
	monticulo2->insercionMonticulo(48);
	monticulo2->insercionMonticulo(31);
	monticulo2->insercionMonticulo(29);
	monticulo2->insercionMonticulo(17);
	monticulo2->insercionMonticulo(10);
	monticulo2->insercionMonticulo(44);
	monticulo2->insercionMonticulo(6);
	monticulo2->insercionMonticulo(37);
	monticulo2->insercionMonticulo(3);
	monticulo2->insercionMonticulo(18);
	monticulo2->imprimeMonticulo();
	cout << "MINIMO DEL MONTICULO 2: " << monticulo2->consultaMinimoMonticulo()->_elem << endl << endl;

	cout << "UNION MONTICULO 1 Y 2" << endl << endl;
	monticulo1->unionMonticulo(*monticulo2);
	monticulo1->imprimeMonticulo();
	cout << "MINIMO DE LA UNION: " << monticulo1->consultaMinimoMonticulo()->_elem << endl << endl;
}

/* Ejemplo del borrado del mínimo de dos montículos. */
void ejemploBorradoMinimo() {

	cout << "MONTICULO" << endl << endl;
	MonticuloBinomial* monticulo = new MonticuloBinomial(27);
	monticulo->insercionMonticulo(11);
	monticulo->insercionMonticulo(17);
	monticulo->insercionMonticulo(8);
	monticulo->insercionMonticulo(38);
	monticulo->insercionMonticulo(14);
	monticulo->insercionMonticulo(29);
	monticulo->insercionMonticulo(6);
	monticulo->insercionMonticulo(42);
	monticulo->insercionMonticulo(26);
	monticulo->insercionMonticulo(23);
	monticulo->insercionMonticulo(16);
	monticulo->insercionMonticulo(18);
	monticulo->insercionMonticulo(12);
	monticulo->insercionMonticulo(25);
	monticulo->insercionMonticulo(1);
	monticulo->insercionMonticulo(77);
	monticulo->insercionMonticulo(28);
	monticulo->insercionMonticulo(13);
	monticulo->insercionMonticulo(10);
	monticulo->insercionMonticulo(41);
	monticulo->insercionMonticulo(37);
	monticulo->imprimeMonticulo();
	cout << "MINIMO: " << monticulo->consultaMinimoMonticulo()->_elem << endl << endl;

	cout << "MONTICULO TRAS EL BORRADO" << endl << endl;
	monticulo->eliminarMinimoMonticulo();
	monticulo->imprimeMonticulo();
	cout << "MINIMO TRAS EL BORRADO: " << monticulo->consultaMinimoMonticulo()->_elem << endl << endl;
}

/* Ejemplo de decrementar una clave en un montículo. */
void ejemploDecrementar() {

	cout << "MONTICULO" << endl << endl;
	MonticuloBinomial* monticulo = new MonticuloBinomial(42);
	monticulo->insercionMonticulo(26);
	monticulo->insercionMonticulo(23);
	monticulo->insercionMonticulo(16);
	monticulo->insercionMonticulo(77);
	monticulo->insercionMonticulo(28);
	monticulo->insercionMonticulo(13);
	monticulo->insercionMonticulo(10);
	monticulo->insercionMonticulo(27);
	monticulo->insercionMonticulo(11);
	monticulo->insercionMonticulo(17);
	monticulo->insercionMonticulo(8);
	monticulo->insercionMonticulo(38);
	monticulo->insercionMonticulo(14);
	monticulo->insercionMonticulo(29);
	monticulo->insercionMonticulo(6);
	monticulo->insercionMonticulo(41);
	monticulo->insercionMonticulo(37);
	monticulo->insercionMonticulo(18);
	monticulo->insercionMonticulo(12);
	monticulo->insercionMonticulo(25);
	monticulo->imprimeMonticulo();
	cout << "MINIMO: " << monticulo->consultaMinimoMonticulo()->_elem << endl << endl;

	cout << "MONTICULO TRAS DECREMENTAR LA CLAVE 26" << endl << endl;
	monticulo->decrecerClaveMonticulo(monticulo->ejemploDecrementar(), 7);
	monticulo->imprimeMonticulo();
	cout << "MINIMO TRAS DECREMENTAR: " << monticulo->consultaMinimoMonticulo()->_elem << endl << endl;
}