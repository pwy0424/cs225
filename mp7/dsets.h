#include <vector>

#ifndef DSETS_H
#define DSETS_H

class DisjointSets
{
	public:
	void addelements(int num);
	int find(int elem);
	void setunion(int a, int b);

	private:
	std::vector<int> myvector;
};

#endif
