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
		peso = (dist * 60) / velPro;
	}
};
struct TKey {
	char valor[MaxT];
	pIndex pRegistro;
	TKey(string s, pIndex p) {
		strcpy_s(valor, s.c_str());
		pRegistro = p;
	}
	TKey() {
		valor[0] = 0;
		pRegistro = 0;
	}
	TKey(char m[], pIndex p) {
		memcpy(valor, m, MaxT);
		pRegistro = p;
	}
};
const short int T = 100;
const short int M = 2 * T - 1;

struct BTreePage {
	pIndex addr;
	short int n;
	TKey key[M];
	pIndex tp[M + 1];
	bool isLeaf;
	bool isDel;

	BTreePage()
		: addr{ 0 }, n{ 0 }, isLeaf{ true }, isDel{ false }{}

	BTreePage(TKey k, pIndex izq, pIndex der) {
		addr = 0;
		n = 1;
		isLeaf = false;
		isDel = false;
		key[0] = k;
		tp[0] = izq;
		tp[1] = der;
	}
	
};

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

	
	vector<vector<int>> shortestPath(int s, vector<Edge*> ed , int k);
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

