#ifndef scene_H
#define scene_H

#include "image.h"

class Scene
{
private:
	int arraysize;
	Image** array;
	int* xcoordarray;
	int* ycoordarray;
	
public :
	//Scene();
	Scene(int max);
	~Scene();
	Scene(const Scene &source);
	const Scene& operator=(const Scene &source);
	void changemaxlayers(int newmax);
	void addpicture(const char *FileName, int index, int x, int y);
	void changelayer(int index, int newindex);
	void translate(int index, int xcoord, int ycoord);
	void deletepicture(int index);
	Image* getpicture(int index) const;
	Image drawscene() const;
	void clear();
	void copy(const Scene& source);
};

#endif//class Scene

