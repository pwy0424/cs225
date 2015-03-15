// **************************************************************
// *		   
// *  quadtree.cpp
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#include "quadtree.h"
#include <iostream>
using namespace std;

Quadtree::Quadtree()
{
	//cout<<"cstor empty in"<<endl;
	root = NULL;
	d = 0;
	//cout<<"cstor empty out"<<endl;
}

Quadtree::Quadtree(const PNG& source, int resolution)
{
	//cout<<"cstor 2 in"<<endl;
	root = build(source, 0, 0, resolution);
	d = resolution;
	//cout<<"cstor 2 out"<<endl;
}


Quadtree::QuadtreeNode * Quadtree::copy(QuadtreeNode* const & other)
{
	//cout<<"copy helper in"<<endl;
	
	if (other == NULL) return NULL;
	//else if ((orig != NULL)&&(other == NULL)) orig = NULL;
	else
	{
		//orig = new QuadtreeNode();
		/*if (other->nwChild == NULL)
		{
			orig->nwChild = NULL;
			orig->neChild = NULL;
			orig->swChild = NULL;
			orig->seChild = NULL;
			orig->element = other->element;
		}QuadtreeNode* result = new QuadtreeNode();
		else
		{*/
		QuadtreeNode* result = new QuadtreeNode();
		result->nwChild = copy(other->nwChild);
		result->neChild = copy(other->neChild);
		result->swChild = copy(other->swChild);
		result->seChild = copy(other->seChild);
		result->element = other->element;
		return result;
	}
	//cout<<"copy helper out"<<endl;
}

void Quadtree::copy(Quadtree const & other)
{
	root = copy(other.root);
	d = other.d;
}

Quadtree::Quadtree(Quadtree const & other)
{
	//cout<<"copy ctor in"<<endl;
	copy(other);
	//cout<<"copy ctor out"<<endl;
}

void Quadtree::clear(QuadtreeNode* temp)
{
	//cout<<"clear helper in"<<endl;
	
	if(temp == NULL) return;
	/*else if (temp->nwChild == NULL)//temp is a leaf
	{
//cout<<"xxx"<<endl;
		delete temp;
		temp = NULL;
//cout<<"1"<<endl;
		//cout<<"clear helper out"<<endl;
		return;
	}*/
	else//temp is not a leaf
	{
//cout<<"zzz"<<endl;
		clear(temp->nwChild);
		clear(temp->neChild);
		clear(temp->swChild);
		clear(temp->seChild);//use recursion to clear temp's four children.
		delete temp;
		temp = NULL;
//cout<<"2"<<endl;
	}
	//cout<<"clear helper out"<<endl;
}

void Quadtree::clear()
{
	clear(root);
	d = 0;
}

Quadtree::~Quadtree()
{
	//cout<<"dtor in"<<endl;
	clear();
	//cout<<"dtor out"<<endl;
}

Quadtree const & Quadtree::operator=(Quadtree const & other)
{
	//cout<<"= int"<<endl;
	
	if (this != &other)
	{
		clear();
		//root = new QuadtreeNode();
		copy(other);
	}
	//d = other.d;
	//cout<<"= out"<<endl;
	return other;
}

Quadtree::QuadtreeNode* Quadtree::build(PNG const & source, int x, int y, int i)
{
	//cout<<"build helper in"<<endl;
	QuadtreeNode* result = new QuadtreeNode();
	if(i == 1)
	{
		result->nwChild = NULL;
		result->neChild = NULL;
		result->swChild = NULL;
		result->seChild = NULL;
		result->element = *(source(x,y));
	}
	else
	{
		result->nwChild = build(source, x, y, i/2);
		result->neChild = build(source, x + i/2, y, i/2);
		result->swChild = build(source, x, y + i/2, i/2);
		result->seChild = build(source, x + i/2, y + i/2, i/2);

		int red =((result->nwChild->element).red+(result->neChild->element).red+(result->swChild->element).red+(result->seChild->element).red);  
       	int blue=((result->nwChild->element).blue+(result->neChild->element).blue+(result->swChild->element).blue+(result->seChild->element).blue);
       	int green=((result->nwChild->element).green+(result->neChild->element).green+(result->swChild->element).green+(result->seChild->element).green);

		(result->element).red = red/4;
       	(result->element).blue = blue/4;
       	(result->element).green = green/4;
       		
	}
	//cout<<"build helper out"<<endl;
	return result;
}

void Quadtree::buildTree(PNG const & source, int resolution)
{
	//cout<<"buildtree in"<<endl;
	//clear();
	root = build(source, 0, 0, resolution);
	d = resolution;
	//cout<<"buildtree out"<<endl;
}
/*
int Quadtree::getdepth(QuadtreeNode* temp) const
{
	cout<<"get depth"<<endl;
	if(temp == NULL) {cout<<"0"<<endl;return 0;}
	else {cout<<"1"<<endl;return (1 + getdepth(temp->seChild));}
}*/

RGBAPixel Quadtree::getPixel(int x, int y) const
{
	//cout<<"getpixel in"<<endl;
	if (root == NULL) return RGBAPixel();
	else if ((x >= d)||(y >= d)||(x < 0 )||(y < 0)) return RGBAPixel();
	else return getpixel(root, x, y, d);
}

RGBAPixel Quadtree::getpixel(QuadtreeNode* temp, int x, int y, int i) const
{
	//cout<<"getpixel helper in"<<endl;
	if (temp == NULL) return RGBAPixel();
	else if (temp->nwChild == NULL){ //cout<<"getpixel helper out1"<<endl;
	return temp->element;}
	else if (i == 1) {// cout<<"getpixel helper out2"<<endl;
	return temp->element;}
	else
	{
		if ((x < i/2) && (y < i/2)) { //cout<<"getpixel helper out3"<<endl;
		return getpixel(temp->nwChild, x, y, i/2);}
		else if ((x >= i/2) && (y < i/2)){ //cout<<"getpixel helper out4"<<endl;
		return getpixel(temp->neChild, x-i/2, y, i/2);}
		else if ((x < i/2) && (y >= i/2)){ //cout<<"getpixel helper out5"<<endl;
		return getpixel(temp->swChild, x, y-i/2, i/2);}
		else { //cout<<"getpixel helper out1"<<endl;
		return getpixel(temp->seChild, x-i/2, y-i/2, i/2);}
	}
}


PNG Quadtree::decompress() const
{
	//cout<<"decompress in"<<endl;
	if (root == NULL) 
	{
		//cout<<"decompress out"<<endl;
		return PNG();
	}
	else 
	{
		//cout<<"???"<<endl;

		PNG result = PNG(d, d);
		//cout<<"!!!"<<endl;
		//for (int i = 0; i < d; i++)
		//{
		//	for (int j = 0; j < d; j++)
		//	{
		//		*result(i,j) = getPixel(i,j);			
		//	}
		//}
			//cout<<"decompress out"<<endl;
		decompress(root, 0, 0, d, result);
		return result;
	}
}

void Quadtree::decompress(QuadtreeNode* temp,int x,int y, int i, PNG & result) const
{
	if (temp->nwChild == NULL) 
	{
		for (int a = 0; a < i; a++)
		{
			for (int b = 0; b < i; b++)
			{			
				*(result(x+a,y+b)) = temp->element;
			}
		}
	}
	else
	{
		decompress(temp->nwChild, x, y, i/2, result);
		decompress(temp->neChild, x+i/2, y, i/2, result);
		decompress(temp->swChild, x, y+i/2, i/2, result);
		decompress(temp->seChild, x+i/2, y+i/2, i/2, result);
	}
}

Quadtree::QuadtreeNode::QuadtreeNode()
{
	nwChild = NULL;
	neChild = NULL;
	swChild = NULL;
	seChild = NULL;
	element = RGBAPixel();
}

void Quadtree::clockwiseRotate()
{
	clockwiseRotate(root);
}

void Quadtree::clockwiseRotate(QuadtreeNode * input)
{
	if (input == NULL) return;
	else
	{
		clockwiseRotate(input->nwChild);
		clockwiseRotate(input->neChild);
		clockwiseRotate(input->swChild);
		clockwiseRotate(input->seChild);
		QuadtreeNode * temp = input->nwChild;
		input->nwChild = input->swChild;
		input->swChild = input->seChild;
		input->seChild = input->neChild;
		input->neChild = temp;
	}
}

void Quadtree::prune(int tolerance)
{
	if (root == NULL) return;
	prune(tolerance, root);
}

void Quadtree::prune(int tolerance, QuadtreeNode* input)
{
	if (input->nwChild == NULL) return;
	else
	{
		//RGBAPixel average = getaverage(input);
		if (doprune(input, input, tolerance))
		{
			clear(input->nwChild);
			clear(input->neChild);
			clear(input->swChild);
			clear(input->seChild);
			input->nwChild = NULL;
			input->neChild = NULL;
			input->swChild = NULL;
			input->seChild = NULL;
		}
		else
		{
			prune(tolerance, input->nwChild);
			prune(tolerance, input->neChild);
			prune(tolerance, input->swChild);
			prune(tolerance, input->seChild);
		}	
	}
}

/*
RGBAPixel Quadtree::getaverage(QuadtreeNode* input) const
{
	if (input->nwChild == NULL) return (input->element);
	else
	{
		RGBAPixel result = RGBAPixel();
		result.red = ((getaverage(input->nwChild).red) + (getaverage(input->neChild).red) + (getaverage(input->swChild).red) + (getaverage(input->seChild).red))/4;
		result.green = ((getaverage(input->nwChild).green) + (getaverage(input->neChild).green) + (getaverage(input->swChild).green) + (getaverage(input->seChild).green))/4;
		result.blue = ((getaverage(input->nwChild).blue) + (getaverage(input->neChild).blue) + (getaverage(input->swChild).blue) + (getaverage(input->seChild).blue))/4;
		return result;
	}
}
*/

/*
void Quadtree::pruning(RGBAPixel average, QuadtreeNode* input)
{
	clear(input->nwChild);
	clear(input->neChild);
	clear(input->swChild);
	clear(input->seChild);
}
*/

bool Quadtree::doprune(QuadtreeNode* input1, QuadtreeNode* input2, int tolerance) const
{
	if (input2 == NULL) return true;
	else if (input2->nwChild == NULL) 
	{
//return ((((input->element.red - average.red)^2) + ((input->element.green - average.green)^2) + ((input->element.blue - average.blue)^2)) <= tolerance);
		//int x = (((input->element.red - average.red)^2) + ((input->element.green - average.green)^2) + ((input->element.blue - average.blue)^2));
		//cout<<x<<endl;
		int reddiff = (input1->element).red - (input2->element).red;
		int bluediff = (input1->element).blue - (input2->element).blue;
		int greendiff = (input1->element).green - (input2->element).green;
		int totaldiff = reddiff * reddiff + bluediff * bluediff + greendiff * greendiff;
		return (totaldiff <= tolerance);
	}
	else return ( (doprune(input1, input2->nwChild, tolerance)) && (doprune(input1, input2->neChild, tolerance)) && (doprune(input1, input2->swChild, tolerance)) && (doprune(input1, input2->seChild, tolerance)));
}

int Quadtree::pruneSize(int tolerance) const
{
	return pruneSize(tolerance, root);
}

int Quadtree::pruneSize(int tolerance, QuadtreeNode* input) const
{
	if (input->nwChild == NULL) return 1;
	else if (doprune(input, input, tolerance)) return 1;
	else return (pruneSize(tolerance, input->nwChild) + pruneSize(tolerance, input->neChild) + pruneSize(tolerance, input->swChild) + pruneSize(tolerance, input->seChild));
}

/*
int Quadtree::fakeprune(QuadtreeNode* input) const
{
	if (input->nwChild == NULL) return 1;
	else return (fakeprune(input->nwChild) + fakeprune(input->neChild) + fakeprune(input->swChild) + fakeprune(input->seChild));

}
*/

int Quadtree::idealPrune(int numLeaves) const
{
	return idealPrune(numLeaves, 0, 200000);
}

int Quadtree::idealPrune(int numLeaves, int low, int hi) const
{
	if (low+1 >= hi) return hi;
	else
	{
		int mid = (low + hi)/2;
		int tmp = pruneSize(mid);
		if (tmp > numLeaves) return idealPrune(numLeaves, mid, hi);
		else return idealPrune(numLeaves, low, mid);
	}
}
