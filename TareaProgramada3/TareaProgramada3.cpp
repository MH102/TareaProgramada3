#include <iostream>
#include "ArchivoAD.h"
#include "Ventana.h"
#include <fstream>


int main()
{

	ArchivoDirecto * ad = new ArchivoDirecto("");
	ArchivoDirecto2 * ad2 = new ArchivoDirecto2("");
	Ventana v(Point(0,0),1500,750,"Ventana",ad,ad2);
	v.wait_for_enter();
	return 0;
}