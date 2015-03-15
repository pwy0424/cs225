#include <cstdlib>
#include "png.h"
#include <iostream>
using namespace std;

// sets up the output image
PNG * setupOutput(int w, int h);

// Returns my favorite color
RGBAPixel * myFavoriteColor(int intensity);

int main()
{
	// Load in.png
	PNG * original;
	original = new PNG;
	//cout << "Reached line 14" << endl;
	original->readFromFile("in.png");
	int width  = original->width();
	int height = original->height();
	//cout << "Reached line 18" << endl;
	// Create out.png
	PNG * output;
	output = setupOutput(width, height);	

	// Loud our favorite color to color the outline
	RGBAPixel * myPixel;
	myPixel = myFavoriteColor(192);

	// Go over the whole image, and if a pixel differs from that to its upper
	// left, color it my favorite color in the output
	for (int y = 0; /*0 < */y < height; y++)
	{
		//cout << y << endl;
		for (int x = 0; /*0 < */x < width; x++)
		{
			// Calculate the pixel difference
			if(x!=0&&y!=0)
			{			
				RGBAPixel * prev = (*original)(x-1, y-1);
				RGBAPixel * curr = (*original)(x  , y  );
				int diff = abs(curr->red   - prev->red  ) +
					   abs(curr->green - prev->green) +
					   abs(curr->blue  - prev->blue );
			
				
				//RGBAPixel * currOutPixel = (*output)(x,y);
				if (diff > 100)
				{
					(*output)(x,y)->red = myPixel->red;
					(*output)(x,y)->green = myPixel->green;
					(*output)(x,y)->blue = myPixel->blue;
				}
			}
			// If the pixel is an edge pixel,
			// color the output pixel with my favorite color
			else 
			{
				//RGBAPixel * currOutPixel = (*output)(x,y);
				//(*output)(x,y)->red = myPixel->red;
				//(*output)(x,y)->green = myPixel->green;
				//(*output)(x,y)->blue = myPixel->blue;
			}		
		}
		//cout << y << endl;
	}
	//cout << "!!!" << endl;
	// Save the output file
	output->writeToFile("out.png");
	//cout << "!!!!!!!!!!!!!!" << endl;
	// Clean up memory
	//delete myPixel;
	//myPixel = NULL;
	delete output;
	output = NULL;
	delete original;
	original = NULL;
	//cout << "????" << endl;
	return 0;
}


// sets up the output image
PNG * setupOutput(int w, int h)
{
	PNG * image = new PNG(w, h);
	return image;
}


// Returns my favorite color
RGBAPixel * myFavoriteColor(int intensity)
{
	RGBAPixel* color;
	color->red   = 0;
	color->green = intensity/2;
	color->blue  = intensity;
	return color;
}

