/*

JAVIER G�MEZ MORALEDA, 2021.

FICHERO UTILIZADO EN LA CREACI�N DE GR�FICAS DEL MONT�CULO BINOMIAL PARA LA ASIGNATURA M�TODOS ALGOR�TMICOS EN RESOLUCI�N DE PROBLEMAS.

*/

#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <fstream>

#include "binomial.h"

using namespace std;

double PCFreq = 0.0;
__int64 CounterStart = 0;

//Inicializa el contador
void StartCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		cout << "QueryPerformanceFrequency failed!\n";

	PCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}

//Obtiene el valor del contador en un determinado momento
double GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}

double tiempo_insercion(int mNodos, int numInserciones);
double tiempo_union(int numNodos);
double tiempo_borraMinimo(int numNodos, int numEliminaciones);
double tiempo_decrecerClave(int numNodos, int numReducciones);

int main() {

	//Variables para almacenar el tiempo
	double tiempo = 0, tiempoTotal = 0;

	//Inicializaci�n del n�mero de nodos y de iteraciones(p.e. el n�mero de borrados del m�nimo consecutivos)
	int numNodos = 1000000, numIteraciones = numNodos * 0.1;

	//Bucle para obtener 3 tiempos de una operaci�n y sacar la media. Para ello se ha ido comentando y descomentando las partes involucradas.
	for (int j = 0; j < 3; j++) {

		// Tiempos para la inserci�n
		//tiempoTotal += tiempo_insercion(numNodos, numIteraciones);
		//tiempo = tiempoTotal / numIteraciones;

		// Tiempos para el borrado del m�nimo
		//tiempoTotal += tiempo_borraMinimo(numNodos, numIteraciones);
		//tiempo = tiempoTotal / numIteraciones;

		//Tiempos para la union
		//tiempo += tiempo_union(numNodos);

		// Tiempos para la reducci�n de una clave
		//tiempoTotal += tiempo_decrecerClave(numNodos, numIteraciones);
		//tiempo = tiempoTotal / numIteraciones;

	}

	tiempoTotal = tiempoTotal / 3;
	tiempo =  tiempo / 3;

	//cout << (numNodos + numNodos - numIteraciones) / 2 << "\t" << tiempoTotal << "\t" << tiempo << endl;
	//cout << (numNodos + numNodos - numIteraciones) / 2 << "\t" << tiempoTotal << "\t" << tiempo << endl;
	//cout << numNodos << "\t" << tiempo << endl;
	//cout << (numNodos + numNodos - numIteraciones) / 2 << "\t" << tiempoTotal << "\t" << tiempo << endl;

	
	return 0;
}

/* Funci�n que devuelve el tiempo de numInserciones de un elemento en una estructura con numNodos elementos. */
double tiempo_insercion(int numNodos, int numInserciones) {
	//Creo un mont�culo binomial con 1 elemento
	MonticuloBinomial* monticulo1 = new MonticuloBinomial(rand() % 1000000);

	//Voy a�adiendo hasta conseguir el n�mero esperado
	for (int i = 1; i < numNodos; i++) {
		monticulo1->insercionMonticulo(rand() % 1000000);
	}

	//Inicio el contador para medir el tiempo
	StartCounter();

	//Realizo el n�mero de eliminaciones deseado
	for (int i = 0; i < numInserciones; i++) {
		monticulo1->insercionMonticulo(rand() % 1000000);
	}

	//Guardo el tiempo que ha tardado
	double tiempo = GetCounter();

	//Libero la memoria ocupada
	monticulo1->borraMonticulo(monticulo1->devuelveInicio());

	return tiempo;
}

/* Funci�n que devuelve el tiempo de numEliminaciones del m�nimo en una estructura con numNodos elementos. */
double tiempo_borraMinimo(int numNodos, int numEliminaciones) {

	//Creo un mont�culo binomial con 1 elemento
	MonticuloBinomial* monticulo1 = new MonticuloBinomial(rand() % 1000000);

	//Voy a�adiendo hasta conseguir el n�mero esperado
	for (int i = 1; i < numNodos; i++) {
		monticulo1->insercionMonticulo(rand() % 1000000);
	}

	//Inicio el contador para medir el tiempo
	StartCounter();

	//Realizo el n�mero de borrados deseado
	for (int i = 0; i < numEliminaciones; i++) {
		monticulo1->eliminarMinimoMonticulo();
	}

	//Guardo el tiempo que ha tardado
	double tiempo = GetCounter();

	//Libero la memoria ocupada
	monticulo1->borraMonticulo(monticulo1->devuelveInicio());

	return tiempo;
}

/* Funci�n que devuelve el tiempo de uni�n de dos mont�culos con numNodos elementos cada uno. */
double tiempo_union(int numNodos) {

	//Declaraci�n de 2 mont�culos con 1 elemento
	MonticuloBinomial* monticulo1 = new MonticuloBinomial(rand() % 10000);
	MonticuloBinomial* monticulo2 = new MonticuloBinomial(rand() % 10000);

	//Los relleno hasta conseguir el n�mero de nodos deseado
	for (int i = 1; i < numNodos; i++) {
		monticulo1->insercionMonticulo(rand() % 10000);
		monticulo2->insercionMonticulo(rand() % 10000);
	}

	//Inicio el contador para medir el tiempo
	StartCounter();

	//Realizo la uni�n
	monticulo1->unionMonticulo(*monticulo2);

	//Guardo el tiempo que ha tardado
	double tiempo = GetCounter();

	//Libero la memoria ocupada
	monticulo1->borraMonticulo(monticulo1->devuelveInicio());

	return tiempo;
}

/* Funci�n que devuelve el tiempo de numReducciones de un elemento en una estructura con numNodos elementos. */
double tiempo_decrecerClave(int numNodos, int numReducciones) {

	//Creo un mont�culo binomial con 1 elemento
	MonticuloBinomial* monticulo1 = new MonticuloBinomial(rand() % 1000000);

	//Voy a�adiendo hasta conseguir el n�mero esperado
	for (int i = 1; i < numNodos; i++) {
		monticulo1->insercionMonticulo(rand() % 1000000);
	}

	//Inicio el contador para medir el tiempo
	StartCounter();

	
	//Pongo una clave negativa puesto que en mi mont�culo solo tendr� elementos positivos
	int clave = -1;

	//Realizo el n�mero de reducciones deseado
	for (int i = 0; i < numReducciones; i++) {

		//La voy reducciendo para asegurarme de que siempre es la menor
		clave--;
		monticulo1->decrecerClaveMonticulo(monticulo1->devuelvePunteroNodo(), clave);
	}

	//Guardo el tiempo que ha tardado
	double tiempo = GetCounter();

	//Libero la memoria ocupada
	monticulo1->borraMonticulo(monticulo1->devuelveInicio());

	return tiempo;
}