#include "scene.h"
#include <iostream>
using namespace std;

//Initializes this Scene object to be able to hold "max" number of images with indices 0 through max-1.
Scene::Scene(int max)
{
	array = new Image*[max];
	xcoordarray = new int[max];
	ycoordarray = new int[max];
	for(int i = 0; i < max; i++)
	{
		array[i] = NULL;
		xcoordarray[i] = 0;
		ycoordarray[i] = 0;
	}
	
	arraysize = max;
	
}

//The copy() helper function that will be used in cctor and operator=.
void Scene::copy(const Scene& source)
{
	//cout << "copy start" << endl;
	arraysize = source.arraysize;
	array = new Image*[arraysize];
	xcoordarray = new int[arraysize];
	ycoordarray = new int[arraysize];
	for(int i = 0; i < arraysize; i++)
	{
		array[i] = NULL;
		//xcoordarray[i] = 0;
		//ycoordarray[i] = 0;
	}
	for (int j = 0; j < arraysize; j++)
	{
		if (source.array[j]!=NULL)
		{
		array[j] = new Image;
		(*array[j]) = *(source.array[j]);
		}
		xcoordarray[j] = (source.xcoordarray)[j];
		ycoordarray[j] = (source.ycoordarray)[j];
	}
	//cout << "copy end" << endl;
}

//The clear() helper function that will be used in operator= and dtor.
void Scene::clear()
{
	for (int i = 0; i < arraysize; i++)
	{
		if (array[i]!=NULL) 
		{
			delete array[i];
			array[i] = NULL;
		}
	}
	delete []array;
	delete []xcoordarray;
	delete []ycoordarray;
	xcoordarray = NULL;
	ycoordarray = NULL;
	array = NULL;
	//delete arraysize;
}

//The copy constructor makes this Scene an independent copy of the source.
Scene::Scene(const Scene &source)
{	
	//clear();
	copy(source);
	//clear();
	//copy(source);
}

//The assignment operator for the Scene class.
const Scene & Scene::operator=(const Scene &source)
{
//cout <<"= start"<< endl;
	if (this!=&source)
	{
		clear();
		copy(source);
	}
//cout <<"= end"<< endl;
	return source;
}

//Modifies the size of the array of Image pointers without changing their indices.
void Scene::changemaxlayers(int newmax)
{
//cout <<"changemax start"<< endl;
	if (newmax < arraysize){
		for (int i = newmax-1; i < arraysize; i++)
		{
			if (array[i]!=NULL)
			{
				cout << "invalid newmax" << endl;
				return;
			}
		}
	}
	Image** newarray = new Image*[newmax];
	int * newxcoordarray = new int[newmax];
	int * newycoordarray = new int[newmax];
	for (int i = 0; i < arraysize; i++)
	{
		newarray[i] = array[i];
		newxcoordarray[i] = xcoordarray[i];
		newycoordarray[i] = xcoordarray[i];
	}
	arraysize = newmax;
	delete array;
	delete xcoordarray;
	delete ycoordarray;
	array = newarray;
	xcoordarray = newxcoordarray;
	ycoordarray = newycoordarray;
//cout <<"changemax emd"<< endl;
}	

//This function will add a picture to the scene, by placing it in the array cell corresponding to the given index, and storing its x coordinate and y coordinate.
void Scene::addpicture(const char* Filename, int index, int x, int y)
{
//cout <<"add start"<< endl;
	if ((index >= arraysize)||(index<0))
	{
		cout << "index out of bounds" << endl;
		return;
	}
	Image* file = new Image;
	file->readFromFile(Filename);
	if (array[index]!=NULL) delete array[index];
	//array[index] = NULL;
	//if (array[index]==NULL) array[index] = new Image;
		//delete array[index];	
	//array[index] = new Image;
	array[index] = file;
	xcoordarray[index] = x;
	ycoordarray[index] = y;
	//delete file;
	//file = NULL;
//cout <<"add end"<< endl;
}

//Moves an Image from one layer to another.
void Scene::changelayer(int index, int newindex)
{
//cout <<"changelayer start"<< endl;	
	if ((index >= arraysize)||(index<0)||(newindex >= arraysize)||(newindex<0))
	{
		cout << "invalid index" << endl;
		return;
	}
	if (index == newindex)
	{
		return;
	}
	array[newindex] = array[index];
	xcoordarray[newindex] = xcoordarray[index];
	ycoordarray[newindex] = ycoordarray[index];
	array[index] = NULL;
	xcoordarray[index] = 0;
	ycoordarray[index] = 0;
//cout <<"changelayer end"<< endl;
}

//Changes the x and y coordinates of the Image in the specified layer.
void Scene::translate(int index, int xcoord, int ycoord)
{
//cout <<"translate start"<< endl;
	if ((index>=arraysize)||(index<0)||(array[index]==NULL))
	{
		cout << "invalid index" << endl;
		return;
	}
	xcoordarray[index] = xcoord;
	ycoordarray[index] = ycoord;
//cout <<"translate end"<< endl;
}

//Deletes the Image at the given index.
void Scene::deletepicture(int index)
{
//cout <<"deletepicture start"<< endl;
	if ((index>=arraysize)||(index<0)||(array[index]==NULL))
	{
		cout << "invalid index" << endl;
		return;
	}
	delete array[index];
	array[index] = NULL;
	xcoordarray[index] = 0;
	ycoordarray[index] = 0;
//cout <<"deletepicture e"<< endl;
}

//This function will return a pointer to the Image at the specified index, not a copy of it.
Image* Scene::getpicture(int index) const
{
//cout <<"getpictre s"<< endl;
	if ((index>=arraysize)||(index<0))
	{
//cout << "1";
		cout << "invalid index" << endl;
		return NULL;
	}
//cout <<"getpic e"<< endl;
	return array[index];
}

//Draws the whole scene on one Image and returns that Image by value.
Image Scene::drawscene() const
{
//cout <<"draw s"<< endl;
	int width = 0;
	int height = 0;
	for (int i = 0; i < arraysize; i++)
	{
		if (array[i]!=NULL)
		{
			int w = xcoordarray[i]+(array[i]->width());
			int h = ycoordarray[i]+(array[i]->height());
			if (w > width) width = w;
			if (h > height) height = h;
		}
	}
	Image result;
	result.resize(width,height);
	for (int i = 0; i < arraysize; i++)
	{
		if (array[i]!=NULL)
		{
			for (int x = 0; x < array[i]->width(); x++)
			{
				for (int y = 0; y < array[i]->height(); y++)
				{
					result(x + xcoordarray[i],y + ycoordarray[i])->red = (*array[i])(x,y)->red;
					result(x + xcoordarray[i],y + ycoordarray[i])->green = (*array[i])(x,y)->green; 
					result(x + xcoordarray[i],y + ycoordarray[i])->blue = (*array[i])(x,y)->blue; 
				}
			}
		}
	}
	//cout <<"draw e"<< endl;
	return result;
}

//dtor
Scene::~Scene()
{
	clear();
}

