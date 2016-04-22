#include "arvAVL.h"
#include <cstdlib>
#include <iostream>

using namespace std;

int main(void)
{
	arvAVL *arv1;
	arv1 = new arvAVL();

	arv1->ins(7);
	arv1->ins(6);
	arv1->ins(5);
	arv1->ins(4);
	arv1->ins(3);
	arv1->ins(2);
	arv1->ins(1);
	//arv1->ins(40);

	arv1->mostra();

	arv1->rmv(3);

	arv1->mostra();

	system("pause");
	return 0;
}
