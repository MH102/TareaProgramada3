#include <iostream>
#include "GraphB.h"
#include "ArchivoAD.h"
#include "Ventana.h"
#include <fstream>
int main()
{
	ArchivoDirecto * ad = new ArchivoDirecto("");
	Ventana v(Point(0,0),1500,900,"Ventana",ad);
	v.wait_for_enter();
	return 0;
}