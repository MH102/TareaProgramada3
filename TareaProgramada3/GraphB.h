using namespace std;
const long int MaxT = 10;
typedef long int pIndex;

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