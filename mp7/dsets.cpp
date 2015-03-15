#include "dsets.h"

void DisjointSets::addelements(int num)
{
	for(int i = 0; i < num; i++) myvector.push_back(-1);
}

int DisjointSets::find(int elem)
{
	int size = myvector.size();
	int root = elem;
	if ((elem < 0) || elem >= size) return elem;
	while (myvector[root] >= 0) root = myvector[root];
	while (elem != root)
	{
		int temp;
		temp = myvector[elem];
		myvector[elem] = root;
		elem = temp;
	}
	return root;
}

void DisjointSets::setunion(int a, int b)
{
	int size = myvector.size();
	bool invalidA = (a < 0)||(a >= size);
	bool invalidB = (b < 0)||(b >= size);
	if (invalidA||invalidB) return;
	int tempA = find(a);
	int tempB = find(b);
	if (tempA == tempB) return;
	else if(myvector[tempA] > myvector[tempB])
	{
		myvector[tempB] = myvector[tempB] + myvector[tempA];
		myvector[tempA] = tempB;
	}
	else
	{
		myvector[tempA] = myvector[tempA] + myvector[tempB];
		myvector[tempB] = tempA;
	}
}


