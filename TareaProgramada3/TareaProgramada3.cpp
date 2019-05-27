#include <iostream>
#include "GraphB.h"
#include "ArchivoAD.h"
int main()
{
	ArchivoDirecto ad("prueba.dat");
	cout << ad.info();

	Nodo q(10, 10, 30);
	ad.actualizar(q);
	q = Nodo(52, 200, 100);
	ad.actualizar(q);
	q = Nodo(11, 50, 50);
	ad.actualizar(q);
	q = Nodo(999, 21, 44);
	ad.actualizar(q);
	q = Nodo(13, 10, 10);
	ad.actualizar(q);
	cout << ad.info();
	for(int i = 0; i < ad.tam(); i++) {
		q = ad.leer(i);
		if (q.valor != -1) {
			cout << q;
		}
	}
	return 0;
}