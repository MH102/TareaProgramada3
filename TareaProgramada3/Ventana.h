#pragma once
#include "GUI.h"
#include "Simple_window.h"
#include <fstream>
#include "GraphB.h"
using namespace Graph_lib;
vector<string> split(string cadena, char divisor) {
	vector<string> vec;
	string palabra;
	for (int i = 0; i < cadena.size(); i++) {
		if (cadena[i] == divisor) {
			vec.push_back(palabra);
			palabra = "";
		}
		else {
			palabra += cadena[i];
		}
	}
	vec.push_back(palabra);
	return vec;
}
struct Ventana :
	public Window
{
	void clear() {
		for (int i = 0; i < vec.size(); i++) {
			Circle * c = vec.at(i);
			vec.at(i) = 0;
			this->detach(*c);
			c->set_fill_color(Color::black);
			vec.at(i) = c;
			this->attach(*c);
		}
		for (int i = 0; i < vec3.size(); i++) {
			Line * l = vec3.at(i);
			vec3.at(i) = 0;
			this->detach(*l);
			l->set_color(Color::blue);
			vec3.at(i) = l;
			this->attach(*l);
		}
		this->redraw();
	}
	void inodo(Nodo n) {
		for (int i = 0; i < vec.size(); i++) {
			if (vec.at(i)->point(0).x == n.coorX + 155 && vec.at(i)->point(0).y == n.coorY - 5) {
				Circle * c = vec.at(i);
				vec.at(i) = 0;
				this->detach(*c);
				c->set_fill_color(Color::red);
				vec.at(i) = c;
				this->attach(*c);
			}
		}
		this->redraw();
	}
	void enter() {
		if (split(entrada.get_string(),' ').at(0) == "import") {
			vec5.push_back(entrada.get_string());
			string s = "";
			for (int i = 0; i < vec5.size(); i++) {
				s += vec5.at(i) + "\n";
			}
			salida.put(s);
			if (open) {
				while (vec.size() != 0) {
					Circle *t = vec.back();
					vec.pop_back();
					this->detach(*t);
					delete(t);
				}
				while (vec2.size() != 0) {
					Text *t = vec2.back();
					vec2.pop_back();
					this->detach(*t);
					delete(t);
				}
				while (vec3.size() != 0) {
					Line *l = vec3.back();
					vec3.pop_back();
					this->detach(*l);
					delete(l);
				}
				while (vec4.size() != 0) {
					Text *t = vec4.back();
					vec4.pop_back();
					this->detach(*t);
					delete(t);
				}
				while (ed.size() != 0) {
					Edge * t = ed.back();
					ed.pop_back();
					delete(t);
				}
			}
			nombre = split(split(entrada.get_string(), ' ').at(1), '.').at(0);
			ad = new ArchivoDirecto(nombre + ".VRT");
			ifstream arch;
			arch.open(split(entrada.get_string(),' ').at(1));
			string info;
			getline(arch, info);
			int tam = stoi(split(info, ',').at(1));
			for (int i = 0; i < tam; i++) {
				getline(arch, info);
				Nodo c(stoi(split(info, ',').at(0)), stoi(split(info, ',').at(1)), stoi(split(info, ',').at(2)));
				ad->actualizar(c);
			}
			while (getline(arch, info)) {
				int a, b, c, d, f;
				vector<string> r = split(info, ',');
				a = stoi(r.at(0));
				b = stoi(r.at(1));
				c = stoi(r.at(2));
				d = stoi(r.at(3));
				f = stoi(r.at(4));
				Edge * e = new Edge(a, b, c, d, f);
				ed.push_back(e);
			}
			arch.close();
			open = true;
			for (int i = 0; i < ad->tam(); i++) {
				Nodo q = ad->leer(i);
				if (q.valor != -1) {
					Circle * c = new Circle(Point(q.coorX + 160, q.coorY), 5);
					Text * t = new Text(Point(q.coorX + 154, q.coorY - 6), to_string(q.valor));
					c->set_color(Color::black);
					c->set_fill_color(Color::black);
					t->set_color(Color::black);
					t->set_font_size(10);
					this->attach(*c);
					this->attach(*t);
					vec.push_back(c);
					vec2.push_back(t);
				}
			}
			for (int i = 0; i < ed.size(); i++) {
				Edge * t = ed.at(i);
				Nodo n1 = ad->leer(t->orig);
				Nodo n2 = ad->leer(t->dest);
				Point start(n1.coorX + 160, n1.coorY);
				Point end(n2.coorX + 160, n2.coorY);
				Line * l = new Line(start,end);
				l->set_color(Color::blue);
				//FLECHA
				Point mid((n1.coorX / 2 + n2.coorX / 2) + 160, n1.coorY / 2 + n2.coorY / 2);
				Point d = Point(start.x - mid.x, start.y - mid.y);
				double dMag = sqrt(pow(d.x, 2) + pow(d.y, 2));
				Point dUnit = Point(d.x / dMag * 7, d.y / dMag * 7);
				Point dTrans = Point(dUnit.x, dUnit.y);
				//Arrow Head End
				Point dPerp = Point(-dTrans.y, dTrans.x);
				Point arrowhead03 = Point(mid.x + dPerp.x + dTrans.x, mid.y + dPerp.y + dTrans.y);
				Point arrowhead04 = Point(mid.x - dPerp.x + dTrans.x, mid.y - dPerp.y + dTrans.y);
				//FLECHA-END
				Line * l2 = new Line(mid, arrowhead03);
				l2->set_color(Color::blue);
				Line * l3 = new Line(mid, arrowhead04);
				l3->set_color(Color::blue);
				mid.y += -8;
				Text * t2 = new Text(arrowhead03, to_string(t->peso));
				t2->set_color(Color::red);
				t2->set_font_size(10);
				this->attach(*l);
				this->attach(*l2);
				this->attach(*l3);
				this->attach(*t2);
				vec3.push_back(l);
				vec3.push_back(l2);
				vec3.push_back(l3);
				vec4.push_back(t2);
			}
			this->redraw();
		}
		if (entrada.get_string() == "salir") {
			button_pushed = true;
		}
		if (entrada.get_string() == "close"){
			ad->cerrar();
			vec5.push_back(entrada.get_string());
			string s = "";
			for (int i = 0; i < vec5.size(); i++) {
				s += vec5.at(i) + "\n";
			}
			salida.put(s);
			while (vec.size() != 0) {
				Circle *t = vec.back();
				vec.pop_back();
				this->detach(*t);
				delete(t);
			}
			while (vec2.size() != 0) {
				Text *t = vec2.back();
				vec2.pop_back();
				this->detach(*t);
				delete(t);
			}
			while (vec3.size() != 0) {
				Line *l = vec3.back();
				vec3.pop_back();
				this->detach(*l);
				delete(l);
			}
			while (vec4.size() != 0) {
				Text *t = vec4.back();
				vec4.pop_back();
				this->detach(*t);
				delete(t);
			}
			while (ed.size() != 0) {
				Edge * t = ed.back();
				ed.pop_back();
				delete(t);
			}
			open = false;
			this->redraw();

		}
		if (entrada.get_string() == "clear") {
			vec5.push_back(entrada.get_string());
			string s = "";
			for (int i = 0; i < vec5.size(); i++) {
				s += vec5.at(i) + "\n";
			}
			salida.put(s);
			clear();
		}
		if (entrada.get_string() == "cleart") {
			salida.put("");
			this->redraw();
			while (vec5.size() != 0) {
				vec5.pop_back();
			}
		}
		if (split(entrada.get_string(),' ').at(0) == "open") {
			if (open) {
				while (vec.size() != 0) {
					Circle *t = vec.back();
					vec.pop_back();
					this->detach(*t);
					delete(t);
				}
				while (vec2.size() != 0) {
					Text *t = vec2.back();
					vec2.pop_back();
					this->detach(*t);
					delete(t);
				}
				while (vec3.size() != 0) {
					Line *l = vec3.back();
					vec3.pop_back();
					this->detach(*l);
					delete(l);
				}
				while (vec4.size() != 0) {
					Text *t = vec4.back();
					vec4.pop_back();
					this->detach(*t);
					delete(t);
				}
				while (ed.size() != 0) {
					Edge * t = ed.back();
					ed.pop_back();
					delete(t);
				}
			}
			vec5.push_back(entrada.get_string());
			string s = "";
			for (int i = 0; i < vec5.size(); i++) {
				s += vec5.at(i) + "\n";
			}
			salida.put(s);
			nombre = split(entrada.get_string(), ' ').at(1);
			ad = new ArchivoDirecto(nombre+ ".VRT" );
			for (int i = 0; i < ad->tam(); i++) {
				Nodo q = ad->leer(i);
				if (q.valor != -1) {
					ad->actualizar(q);
					Circle * c = new Circle(Point(q.coorX + 160, q.coorY), 5);
					Text * t = new Text(Point(q.coorX + 154, q.coorY - 6), to_string(q.valor));
					c->set_color(Color::black);
					c->set_fill_color(Color::black);
					t->set_color(Color::black);
					t->set_font_size(10);
					this->attach(*c);
					this->attach(*t);
					vec.push_back(c);
					vec2.push_back(t);
				}
			}
			this->redraw();
		}
		if (split(entrada.get_string(), ' ').at(0) == "node") {
			int valor = stoi(split(entrada.get_string(), ' ').at(1));
			Nodo n = ad->leer(valor);
			vec5.push_back(entrada.get_string());
			vec5.push_back("Coordenadas: \n(" + to_string(n.coorX) + "," + to_string(n.coorY)+ ")");
			string s = "";
			for (int i = 0; i < vec5.size(); i++) {
				s += vec5.at(i) + "\n";
			}
			inodo(n);
			salida.put(s);
			
		}
		if (split(entrada.get_string(), ' ').at(0) == "arcs") {
			int valor = stoi(split(entrada.get_string(), ' ').at(1));
			Nodo n = ad->leer(valor);
			vec5.push_back(entrada.get_string());
			string s = "";
			for (int i = 0; i < ed.size(); i++) {
				if (n.valor == ed.at(i)->orig) {
					string inf = "Arco " + to_string(n.valor) + "->" + to_string(ed.at(i)->dest) + "\n" + "Distancia: " + to_string(ed.at(i)->dist) + "\nVel Maxima: "+ to_string(ed.at(i)->velMax) + "\nVel Promedio: " + to_string(ed.at(i)->velPro);
					vec5.push_back(inf);
				}
			}
			for (int i = 0; i < vec5.size(); i++) {
				s += vec5.at(i) + "\n";
			}
			salida.put(s);
			for (int i = 0; i < vec3.size(); i++) {
				if (vec3.at(i)->point(0).x == n.coorX + 160 && vec3.at(i)->point(0).y == n.coorY) {
					Line * c = vec3.at(i);
					vec3.at(i) = 0;
					this->detach(*c);
					c->set_color(Color::red);
					vec3.at(i) = c;
					this->attach(*c);
					c = vec3.at(i + 1);
					vec3.at(i + 1) = 0;
					this->detach(*c);
					c->set_color(Color::red);
					vec3.at(i + 1) = c;
					this->attach(*c);
					c = vec3.at(i + 2);
					vec3.at(i + 2) = 0;
					this->detach(*c);
					c->set_color(Color::red);
					vec3.at(i + 2) = c;
					this->attach(*c);
				}
			}
			this->redraw();
		}
		if (split(entrada.get_string(), ' ').at(0) == "spt") {
			if (entrada.get_string().size() < 4) { 
				entrada.clean(); 
				return; 
			}
			vec5.push_back(entrada.get_string());
			string s = "";
			for (int i = 0; i < vec5.size(); i++) {
				s += vec5.at(i) + "\n";
			}
			salida.put(s);
			clear();
			Nodo n = ad->leer(stoi(split(entrada.get_string(), ' ').at(1)));
			inodo(n);
			spts = stoi(split(entrada.get_string(), ' ').at(1));
			vector<vector<int>> temp = driver(ad->gtamn(), stoi(split(entrada.get_string(), ' ').at(1)), ed);
			for (int i = 0; i < temp.size(); i++) {
				for (int k = 0; k < vec3.size(); k++) {
					Nodo n1 = ad->leer(temp.at(i).at(0));
					Nodo n2 = ad->leer(temp.at(i).at(1));
					if (vec3.at(k)->point(0).x == n1.coorX + 160 && vec3.at(k)->point(0).y == n1.coorY && vec3.at(k)->point(1).x == n2.coorX + 160 && vec3.at(k)->point(1).y == n2.coorY) {
						Line * c = vec3.at(k);
						vec3.at(k) = 0;
						this->detach(*c);
						c->set_color(Color::red);
						vec3.at(k) = c;
						this->attach(*c);
						c = vec3.at(k + 1);
						vec3.at(k + 1) = 0;
						this->detach(*c);
						c->set_color(Color::red);
						vec3.at(k + 1) = c;
						this->attach(*c);
						c = vec3.at(k + 2);
						vec3.at(k + 2) = 0;
						this->detach(*c);
						c->set_color(Color::red);
						vec3.at(k + 2) = c;
						this->attach(*c);
					}
				}
				this->redraw();
			}
		}
		if (split(entrada.get_string(), ' ').at(0) == "to") {
			if (split(vec5.back(), ' ').at(0) != "spt") {
				return;
			}
			vec5.push_back(entrada.get_string());
			clear();
			int dests = stoi(split(entrada.get_string(), ' ').at(1));
			vector<vector<int>> temp = driver(ad->gtamn(), spts, ed, dests);
			vector<vector<int>> temp2;
			string costo = to_string(temp.back().at(0));
			temp.pop_back();
			bool tester = false;
			for (int i = 0; i < temp.size(); i++) {
				if (temp.at(i).at(1) == dests) {
					tester = true;
					cout << temp.at(i).at(1) << endl;
					temp2.push_back(temp.at(i));
					break;
				}
			}
			if (!tester) {
				entrada.clean();
				return;
			}
			int cur = temp2.back().at(0);
			while (cur != spts) {
				for (int i = 0; i < temp.size(); i++) {
					if (temp.at(i).at(1) == cur) {
						cur = temp.at(i).at(0);
						temp2.push_back(temp.at(i));
					}
				}
			}
			for (int i = 0; i < temp2.size(); i++) {
				for (int k = 0; k < vec3.size(); k++) {
					Nodo n1 = ad->leer(temp2.at(i).at(0));
					Nodo n2 = ad->leer(temp2.at(i).at(1));
					inodo(n1);
					inodo(n2);
					if (vec3.at(k)->point(0).x == n1.coorX + 160 && vec3.at(k)->point(0).y == n1.coorY && vec3.at(k)->point(1).x == n2.coorX + 160 && vec3.at(k)->point(1).y == n2.coorY) {
						Line * c = vec3.at(k);
						vec3.at(k) = 0;
						this->detach(*c);
						c->set_color(Color::red);
						vec3.at(k) = c;
						this->attach(*c);
						c = vec3.at(k + 1);
						vec3.at(k + 1) = 0;
						this->detach(*c);
						c->set_color(Color::red);
						vec3.at(k + 1) = c;
						this->attach(*c);
						c = vec3.at(k + 2);
						vec3.at(k + 2) = 0;
						this->detach(*c);
						c->set_color(Color::red);
						vec3.at(k + 2) = c;
						this->attach(*c);
					}
				}
				this->redraw();
			}
			vec5.push_back("[Camino de " + to_string(spts) + " a " + to_string(dests));
			while (temp2.size() != 0) {
				vec5.push_back(to_string(temp2.back().at(0)) + " -> " + to_string(temp2.back().at(1)));
				temp2.pop_back();
			}
			vec5.push_back("Costo total: " + costo + "]");
			string s = "";
			for (int i = 0; i < vec5.size(); i++) {
				s += vec5.at(i) + "\n";
			}
			salida.put(s);
		}
		if (vec5.size() > 44) {
			while (vec5.size() != 0) {
				vec5.pop_back();
			}
		}
		entrada.clean();
	}
	bool button_pushed;
public:
	Out_box salida;
	In_box entrada;
	int spts;
	string nombre;
	ArchivoDirecto * ad;
	bool open = false;
	vector<Edge*> ed;
	vector<Circle*> vec;
	vector<Text*> vec2;
	vector<Line*> vec3;
	vector<Text*> vec4;
	vector<string> vec5;
	Ventana(Point xy, int w, int h, const string& title, ArchivoDirecto * ad)
		: Window(xy, w, h, title), 
		button_pushed(false),
		salida(Point(0, 0), 150, 725, "Salida"),
		entrada(Point(0, 725), 150, 25, "Entrada"),
		ad{ ad }
	{
		attach(salida);
		attach(entrada);
	}
	void wait_for_enter()
		// modified event loop
		// handle all events (as per default), but quit when button_pushed becomes true
		// this allows graphics without control inversion
	{
		while (!button_pushed) {
			if (Fl::get_key(FL_Enter)) {
				enter();
			}
			Fl::wait();
		}
		button_pushed = false;
		Fl::redraw();
		
	}

};

