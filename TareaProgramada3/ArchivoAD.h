#include <iostream>
#include <fstream>
#include <string>
#include "string.h"

using namespace std;

struct Nodo {
	int valor;
	int coorX;
	int coorY;
	Nodo(int valorP, int coorXP, int coorYP) {
		valor = valorP;
		coorX = coorXP;
		coorY = coorYP;
	}
};
ostream& operator <<(ostream& os, const Nodo&p) {
	return os << "[" << p.valor << "] = (" << p.coorX << "," << p.coorY << ")" << endl;
}

char * as_bytes(int p) {
	void * addr = &p;
	return static_cast<char*>(addr);
}
char * as_bytes(Nodo& p) {
	void * addr = &p;
	return static_cast<char*>(addr);
}
void escribeCabecera(int n, fstream &fs) {
	fs.seekp(0);
	fs.write(as_bytes(n), sizeof(n));
}

class ArchivoDirecto {
private:
	string nArchivo;
	int nRegistros;
	int tamn;
	fstream fs;
	bool abierto;
public:
	ArchivoDirecto(string nombre);
	ArchivoDirecto();
	string info();
	void cerrar();
	int tam();
	void actualizar(Nodo& r);
	void agregarFinal(Nodo& r);
	void init();
	Nodo leer(int i);
	void limpiar();
};
ArchivoDirecto::ArchivoDirecto(string nombre) {
	fs.open(nombre, ios_base::binary | ios_base::in | ios_base::out);
	if (!fs) {
		fs.open(nombre, ios_base::binary | ios_base::out);
		nRegistros = 0;
		tamn = 0;
		escribeCabecera(nRegistros,fs);
		fs.close();
		fs.open(nombre, ios_base::binary | ios_base::in | ios_base::out);
	}
	else {
		fs.seekg(0);
		fs.read(as_bytes(nRegistros), sizeof(nRegistros));
	}
	nArchivo = nombre;
	abierto = true;
	init();
}
string ArchivoDirecto::info() {
	if (abierto)
		return "Archivo   : " + nArchivo + "\nRegistros : " + to_string(this->tamn) + "\n";
	else return "***";
}
void ArchivoDirecto::cerrar() {
	fs.close();
	abierto = false;
}
int ArchivoDirecto::tam() {
	return (abierto ? nRegistros : 0);
}
void ArchivoDirecto::actualizar(Nodo& r) {
	if (abierto && r.valor < nRegistros) {
		fs.seekp(sizeof(int) + r.valor * sizeof(Nodo));
		fs.write(as_bytes(r), sizeof(Nodo));
		tamn++;
	}
}
void ArchivoDirecto::agregarFinal(Nodo& r) {
	if (abierto) {
		fs.seekp(sizeof(int) + nRegistros * sizeof(Nodo));
		fs.write(as_bytes(r), sizeof(Nodo));
		nRegistros++;
		escribeCabecera(nRegistros, fs);
	}
}
void ArchivoDirecto::init() {
	if (abierto) {
		for (int i = 0; i < 1000; i++) {
			Nodo q(-1, -1, -1);
			agregarFinal(q);
		}
	}
}
Nodo ArchivoDirecto::leer(int i) {
	if (!abierto || i >= nRegistros)
		throw 1001;
	fs.seekp(sizeof(int) + i * sizeof(Nodo));
	Nodo r = Nodo(0, 0, 0);
	fs.read(as_bytes(r), sizeof(Nodo));
	return r;
}
void ArchivoDirecto::limpiar() {
	if (abierto)
		fs.close();
	fs.open(nArchivo, ios_base::trunc | ios_base::in | ios_base::out | ios_base::binary);
	nRegistros = 0;
	escribeCabecera(nRegistros, fs);
}