#ifndef ARVAVL_H
#define ARVAVL_H
#include <iostream>
using namespace std;

class arvAVL
{
protected:
	struct avlNo
	{
		int val;
		avlNo *esq;
		avlNo *dir;
		int fatBal;
		avlNo(int valor) : val(valor), esq(NULL), dir(NULL), fatBal(0) {}
		void mostra() {
			cout << " (";
			if (esq != NULL)
				esq->mostra();
			cout << "|" << val << "|";
			if (dir != NULL)
				dir->mostra();
			cout << ") ";
		}
	};
	avlNo* raiz;
	bool h;
public:
	arvAVL() { raiz = NULL; h = false; }
	~arvAVL() { delete raiz; }
	void mostra();
	void ins(const int &valor);
	void rmv(const int &valor);
	void inicio_no(avlNo* &no, int valor);
	void ins_AVL(int x, avlNo* &pt, bool &h);
	void substitui_succ(avlNo* &pt, int &aux);
	void rmv_AVL(int x, avlNo* &pt, bool &h);
	void caso1(avlNo* &pt, bool &h);
	void caso2(avlNo* &pt, bool &h);
};
#endif
