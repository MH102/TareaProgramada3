#include<stdio.h>
#include<conio.h>
using namespace std;
const long int MaxT = 10;
typedef long int pIndex;

struct Edge {
	int orig;
	int dest;
	int dist;
	int velMax;
	int velPro;
	int peso;
	Edge(int origP, int destP, int distP, int velMaxP, int velProP) {
		orig = origP;
		dest = destP;
		dist = distP;
		velMax = velMaxP;
		velPro = velProP;
		if (velPro == 0) {
			peso = 100;
		}
		else {
			peso = (dist * 60) / velPro;
		}
	}
};
int llaveEdge(Edge t) {
	int llave = 0;
	llave = 1000 * (1000 + t.orig) + t.dest;
	return llave;
}
struct BTreeNode
{
	int *data;
	BTreeNode **child_ptr;
	bool leaf;
	int n;
}*root = NULL, *np = NULL, *x = NULL;
BTreeNode * init()
{
	int i;
	np = new BTreeNode;
	np->data = new int[5];
	np->child_ptr = new BTreeNode *[6];
	np->leaf = true;
	np->n = 0;
	for (i = 0; i < 6; i++)
	{
		np->child_ptr[i] = NULL;
	}
	return np;
}
void traverse(BTreeNode *p)
{
	cout << endl;
	int i;
	for (i = 0; i < p->n; i++)
	{
		if (p->leaf == false)
		{
			traverse(p->child_ptr[i]);
		}
		cout << " " << p->data[i];
	}
	if (p->leaf == false)
	{
		traverse(p->child_ptr[i]);
	}
	cout << endl;
}
void sort(int *p, int n)
{
	int i, j, temp;
	for (i = 0; i < n; i++)
	{
		for (j = i; j <= n; j++)
		{
			if (p[i] > p[j])
			{
				temp = p[i];
				p[i] = p[j];
				p[j] = temp;
			}
		}
	}
}
int split_child(BTreeNode *x, int i)
{
	int j, mid;
	BTreeNode *np1, *np3, *y;
	np3 = init();
	np3->leaf = true;
	if (i == -1)
	{
		mid = x->data[2];
		x->data[2] = 0;
		x->n--;
		np1 = init();
		np1->leaf = false;
		x->leaf = true;
		for (j = 3; j < 5; j++)
		{
			np3->data[j - 3] = x->data[j];
			np3->child_ptr[j - 3] = x->child_ptr[j];
			np3->n++;
			x->data[j] = 0;
			x->n--;
		}
		for (j = 0; j < 6; j++)
		{
			x->child_ptr[j] = NULL;
		}
		np1->data[0] = mid;
		np1->child_ptr[np1->n] = x;
		np1->child_ptr[np1->n + 1] = np3;
		np1->n++;
		root = np1;
	}
	else
	{
		y = x->child_ptr[i];
		mid = y->data[2];
		y->data[2] = 0;
		y->n--;
		for (j = 3; j < 5; j++)
		{
			np3->data[j - 3] = y->data[j];
			np3->n++;
			y->data[j] = 0;
			y->n--;
		}
		x->child_ptr[i + 1] = y;
		x->child_ptr[i + 1] = np3;
	}
	return mid;
}
void insert(int a)
{
	int i, temp;
	x = root;
	if (x == NULL)
	{
		root = init();
		x = root;
	}
	else
	{
		if (x->leaf == true && x->n == 5)
		{
			temp = split_child(x, -1);
			x = root;
			for (i = 0; i < (x->n); i++)
			{
				if ((a > x->data[i]) && (a < x->data[i + 1]))
				{
					i++;
					break;
				}
				else if (a < x->data[0])
				{
					break;
				}
				else
				{
					continue;
				}
			}
			x = x->child_ptr[i];
		}
		else
		{
			while (x->leaf == false)
			{
				for (i = 0; i < (x->n); i++)
				{
					if ((a > x->data[i]) && (a < x->data[i + 1]))
					{
						i++;
						break;
					}
					else if (a < x->data[0])
					{
						break;
					}
					else
					{
						continue;
					}
				}
				if ((x->child_ptr[i])->n == 5)
				{
					temp = split_child(x, i);
					x->data[x->n] = temp;
					x->n++;
					continue;
				}
				else
				{
					x = x->child_ptr[i];
				}
			}
		}
	}
	x->data[x->n] = a;
	sort(x->data, x->n);
	x->n++;
}

char * as_bytes2(int p) {
	void * addr = &p;
	return static_cast<char*>(addr);
}
char * as_bytes2(Edge& p) {
	void * addr = &p;
	return static_cast<char*>(addr);
}
void escribeCabecera2(int n, fstream &fs) {
	fs.seekp(0);
	fs.write(as_bytes2(n), sizeof(n));
}

class ArchivoDirecto2 {
private:
	string nArchivo;
	int nRegistros;
	int tamn;
	fstream fs;
	bool abierto;
	bool test = false;
public:
	ArchivoDirecto2(string nombre);
	ArchivoDirecto2();
	string info();
	void cerrar();
	int tam();
	void actualizar(int i, Edge& r);
	void agregarFinal(Edge& r);
	void init();
	int gtamn();
	Edge leer(int i);
	void limpiar();
};
ArchivoDirecto2::ArchivoDirecto2(string nombre) {
	fs.open(nombre, ios_base::binary | ios_base::in | ios_base::out);
	if (!fs) {
		fs.open(nombre, ios_base::binary | ios_base::out);
		nRegistros = 0;
		tamn = 0;
		escribeCabecera2(nRegistros, fs);
		fs.close();
		fs.open(nombre, ios_base::binary | ios_base::in | ios_base::out);
	}
	else {
		fs.seekg(0);
		fs.read(as_bytes2(nRegistros), sizeof(nRegistros));
		test = true;
	}
	abierto = true;
	nArchivo = nombre;
	init();
}
string ArchivoDirecto2::info() {
	if (abierto)
		return "Archivo   : " + nArchivo + "\nRegistros : " + to_string(this->tam()) + "\n";
	else return "***";
}
void ArchivoDirecto2::cerrar() {
	fs.close();
	abierto = false;
}
int ArchivoDirecto2::tam() {
	return (abierto ? nRegistros : 0);
}
int ArchivoDirecto2::gtamn() {
	return tamn;
}
void ArchivoDirecto2::actualizar(int i, Edge& r) {
	if (abierto && r.orig < nRegistros) {
		fs.seekp(sizeof(int) + i * sizeof(Edge));
		fs.write(as_bytes(r), sizeof(Edge));
		if (r.orig == -1) {
			tamn++;
		}
	}
}
void ArchivoDirecto2::agregarFinal(Edge& r) {
	if (abierto) {
		fs.seekp(sizeof(int) + nRegistros * sizeof(Edge));
		fs.write(as_bytes(r), sizeof(Edge));
		nRegistros++;
		escribeCabecera2(nRegistros, fs);
	}
}
void ArchivoDirecto2::init() {
	if (!test) {
		for (int i = 0; i < 1000; i++) {
			Edge q(-1, -1, -1, -1, -1);
			agregarFinal(q);
		}
	}
	else {
		nRegistros = 999;
	}
}
Edge ArchivoDirecto2::leer(int i) {
	if (!abierto || i >= nRegistros)
		throw 1001;
	fs.seekp(sizeof(int) + i * sizeof(Edge));
	Edge r(0,0,0,0,0);
	fs.read(as_bytes2(r), sizeof(Edge));
	return r;
}
void ArchivoDirecto2::limpiar() {
	if (abierto)
		fs.close();
	fs.open(nArchivo, ios_base::trunc | ios_base::in | ios_base::out | ios_base::binary);
	nRegistros = 0;
	escribeCabecera2(nRegistros, fs);
}

#include <queue> 
using namespace std;
# define INF 0x3f3f3f3f 


typedef pair<int, int> iPair;

class Graph
{
	int V;


	list< pair<int, int> > *adj;

public:
	Graph(int V);


	void addEdge(int u, int v, int w);


	vector<vector<int>> shortestPath(int s, vector<Edge*> ed, int k);
};


Graph::Graph(int V)
{
	this->V = V;
	adj = new list<iPair>[V];
}

void Graph::addEdge(int u, int v, int w)
{
	adj[u].push_back(make_pair(v, w));
	//adj[v].push_back(make_pair(u, w));
}


vector<vector<int>> Graph::shortestPath(int src, vector<Edge*> ed, int drst)
{
	priority_queue< iPair, vector <iPair>, greater<iPair> > pq;


	vector<int> dist(V, INF);
	vector<vector<int>> temp;


	pq.push(make_pair(0, src));
	dist[src] = 0;
	while (!pq.empty())
	{

		int u = pq.top().second;
		pq.pop();

		list< pair<int, int> >::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
		{

			int v = (*i).first;
			int weight = (*i).second;


			if (dist[v] > dist[u] + weight)
			{
				dist[v] = dist[u] + weight;
				pq.push(make_pair(dist[v], v));
				temp.push_back({ u,v });
			}
		}
	}
	if (drst != -1) {
		temp.push_back({ dist[drst],dist[drst] });
	}
	return temp;
}
vector<vector<int>> driver(int tam, int src, vector<Edge*> ed, int dests = -1)
{
	Graph g(tam);
	for (int i = 0; i < ed.size(); i++) {
		g.addEdge(ed.at(i)->orig, ed.at(i)->dest, ed.at(i)->peso);
	}
	vector<vector<int>> temp = g.shortestPath(src, ed, dests);
	return temp;
}
