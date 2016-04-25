#include "arvAVL.h"
#include <cstdlib>
#include <iostream>
using namespace std;

// imprime a �rvore AVL, se esta n�o for vazia
void arvAVL::mostra() {
	if (raiz == NULL)
		cout << "Arvore vazia ";
	else
		raiz->mostra();
	cout << endl;
}

// verifica se o n� a ser inserido ser� a raiz da �rvore ou n�o.
void arvAVL::ins(const int& valor) {
	if (raiz == NULL)
		raiz = new avlNo(valor);
	else
		ins_AVL(valor, raiz, h);

}

// inicializa um novo n�
void arvAVL::inicio_no(avlNo* &no, int valor) {
	no = new avlNo(valor);
}

// insere um n� na �rvore, se este n�o existir ainda, e verifica o balanceamento da �rvore
void arvAVL::ins_AVL(int x, avlNo* &pt, bool &h) {

    /*cout << "cacete: ";
	raiz->mostra();
	cout << endl;
    */

	// Local do n� encontrado. Insere o novo n� na �rvore
	if (pt == NULL) {
		inicio_no(pt, x);
		h = true;
	}

	// Busca o local onde o novo valor dever� ser inserido, se este n�o pertencer a �rvore.
	// Faz as opera��es de balanceamento na �rvore, quando o novo n� for inserido
	else {
		if (x == pt->val) {
			cout << "O no ja pertence a arvore!" << endl;
			return;
		}
		if (x < pt->val) {
			ins_AVL(x, pt->esq, h);
			if (h == true) {
				switch (pt->fatBal)
				{
				case 1: pt->fatBal = 0; h = false; break;
				case 0: pt->fatBal = -1; break;
				case -1: caso1(pt, h); break;
				}
			}
		}
		if (x > pt->val) {
			ins_AVL(x, pt->dir, h);
			if (h == true) {
				switch (pt->fatBal)
				{
				case -1: pt->fatBal = 0; h = false; break;
				case 0: pt->fatBal = 1; break;
				case 1: caso2(pt, h); break;
				}
			}
		}
	}
}
// realiza rota��es de sub�rvore esquerda: rota��o direita e rota��o dupla direita
void arvAVL::caso1(avlNo* &pt, bool &h) {
	avlNo *ptu, *aux;
	ptu = pt->esq;

	if (ptu->fatBal == -1) { // rota��o direita
		pt->fatBal = 0;
		pt->esq = ptu->dir;
		ptu->dir = pt;

		if (pt == raiz)
			raiz = ptu;

		pt = ptu;
	}
	else { // rota��o dupla direita

        aux = ptu->dir;
		ptu->dir = aux->esq;
		aux->esq = ptu;
		pt->esq = aux->dir;
		aux->dir = pt;


		if (aux->fatBal == -1)
            pt->fatBal = 1;
		else
            pt->fatBal = 0;

		if (aux->fatBal == 1)
			ptu->fatBal = -1;
		else
			ptu->fatBal = 0;

		pt = aux;
	}
	pt->fatBal = 0;

	h = false;
}

// realiza rota��es de sub�rvore direita: rota��o esquerda e rota��o dupla esquerda
void arvAVL::caso2(avlNo* &pt, bool &h) {
    avlNo *ptu, *aux;
	ptu = pt->dir;

	if (ptu->fatBal == 1) { // rota��o esquerda
		pt->fatBal = 0;
		pt->dir = ptu->esq;
		ptu->esq = pt;

		if (pt == raiz)
			raiz = ptu;

		pt = ptu;
	}
	else { // rota��o dupla esquerda
		aux = ptu->esq;
		ptu->esq = aux->dir;
		aux->dir = ptu;
		pt->dir = aux->esq;
		aux->esq = pt;

		if (aux->fatBal == 1)
			pt->fatBal = -1;
		else
			pt->fatBal = 0;

		if (aux->fatBal == -1)
			ptu->fatBal = 1;
		else
			ptu->fatBal = 0;

		pt = aux;
	}
	pt->fatBal = 0;

	h = false;

}


void arvAVL::rmv(const int& valor) {
	if (raiz == NULL)
		cout << "arvore ja esta vazia!" << endl;
	else
		rmv_AVL(valor, raiz, h);
}


/*
 * @TODO: Confirmação de que o valor buscado esteja na árvore, no momento entra em loop (recursão) infinito
 *
 *
 */

void arvAVL::rmv_AVL(int x, avlNo* &pt, bool &h) {
	// Valor encontrado. Faz as operações de substituição do nó pelo seu sucessor, garantindo o balanceamento


	if (pt->val == x) {
		if ((pt->dir == NULL) && (pt->esq == NULL)) {
			avlNo *q = pt;
			pt= NULL;
			delete q;
		}
		else {
			if (pt->dir != NULL) {
				int aux;
				substitui_succ(pt->dir, aux);
				pt->val=aux;
			}
			else
				if (pt->esq != NULL){
					avlNo *q = pt;
					pt = pt->esq;
					delete q;
				}
		}
		h = true;
	}


	//Busca o valor a ser removido, se este pertencer a árvore.
	// Chama as devidas rotações de balanceamento, quando o valor for removido.
	else {
		if (pt == NULL) {
			cout << "O no nao pertence a arvore!" << endl;
			return;
		}
		if (x < pt->val) {
            rmv_AVL(x, pt->esq, h);
			if (h == true)
				switch (pt->fatBal){
				    case -1:
				        pt->fatBal = 0;
                        break;
                    case 0:
                        pt->fatBal = 1;
                        h = false;
                        break;
                    case 1:
                        caso2(pt, h);
                        break;
				}
		}

        if (x > pt->val) {
            rmv_AVL(x, pt->dir, h);
            if (h == true)
                switch (pt->fatBal){
                    case -1:
                        caso1(pt, h);
                        break;
                    case 0:
                        pt->fatBal = -1;
                        h = false;
                        break;
                    case 1:
                        pt->fatBal = 0;
                        break;
                }
        }
    }

}


void arvAVL::substitui_succ(avlNo* &pt, int &aux) {
	if (pt->esq != NULL) {
		substitui_succ(pt->esq, aux);

		if (h == true)
			switch (pt->fatBal){
                case -1:
                    pt->fatBal = 0;
                    break;
                case 0:
                    pt->fatBal = 1;
                    h = false;
                    break;
                case 1:
                    caso2(pt, h);
                    break;
		}
	}
	else {
		avlNo *q = pt;
		aux = pt->val;
		pt = pt->dir;
		delete q;
		h = true;
	}

}
