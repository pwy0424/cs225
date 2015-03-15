// **************************************************************
// *		   
// *  quadtree.h
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

class Quadtree
{
	public:
		Quadtree();
		Quadtree(const PNG& source, int resolution);
		Quadtree(Quadtree const & other);
		~Quadtree();
		Quadtree const & operator=(Quadtree const & other);
		void buildTree(PNG const & source, int resolution);
		RGBAPixel getPixel(int x, int y) const;
		PNG decompress() const;
	
		void clockwiseRotate();
		
		void prune(int tolerance);

		int pruneSize(int tolerance) const;
		int idealPrune(int numLeaves) const;

	private:
		

	// A simple class representing a single node of a Quadtree.
	// You may want to add to this class; in particular, it could probably
	// use a constructor or two...
	class QuadtreeNode
	{
		public:
		QuadtreeNode* nwChild;  // pointer to northwest child
		QuadtreeNode* neChild;  // pointer to northeast child
		QuadtreeNode* swChild;  // pointer to southwest child
		QuadtreeNode* seChild;  // pointer to southeast child

		RGBAPixel element;  // the pixel stored as this node's "data"
		
		QuadtreeNode();
	};
	
	QuadtreeNode* root;    // pointer to root of quadtree
	int d;
	
	void clockwiseRotate(QuadtreeNode * input);
	
	RGBAPixel getaverage(QuadtreeNode* input) const;

	void pruning(RGBAPixel average, QuadtreeNode* input);

	bool doprune(QuadtreeNode* inpu1, QuadtreeNode* input, int tolerance) const;

	void prune(int tolerance, QuadtreeNode* input);

	void clear();//the helper function that deletes the current contents of this 
					 //Quadtree object.

	void clear(QuadtreeNode*  temp);//the helper function for clear() helper
									//function.
		
	//helper function to build quadtree.
	int fakeprune(QuadtreeNode* input) const;

	int pruneSize(int tolerance, QuadtreeNode* input) const;

	Quadtree::QuadtreeNode* build(PNG const & source, int x, int y, int d);
		
	void copy(Quadtree const & other);
		

	QuadtreeNode* copy(QuadtreeNode* const & other);

	void copy(QuadtreeNode* orig, QuadtreeNode const & other);

	//int getdepth(QuadtreeNode* temp) const;
	int idealPrune(int numLeaves, int low, int hi) const;
	void decompress(QuadtreeNode* temp,int x,int y, int i, PNG & result) const;
	RGBAPixel getpixel(QuadtreeNode* temp, int x, int y, int i) const;
	
	/**** Functions added for testing/grading                ****/
	/**** Do not remove this line or copy its contents here! ****/
	#include "quadtree_given.h"
};

#endif
