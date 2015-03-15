#include "image.h"

//Flips the image about a vertical line through its center by swapping pixels. 
void Image::flipleft()
{
	int w = (*this).width();
	int h = (*this).height();	
	for (int x = 0; x < w/2; x++)
	{
		for (int y = 0; y < h; y++)
		{
			unsigned char tempr = (*this)(x,y)->red;
			(*this)(x,y)->red = (*this)(w-1-x,y)->red;			
			(*this)(w-1-x,y)->red = tempr;
			
			unsigned char tempg = (*this)(x,y)->green;
			(*this)(x,y)->green = (*this)(w-1-x,y)->green;			
			(*this)(w-1-x,y)->green = tempg;
			
			unsigned char tempb = (*this)(x,y)->blue;
			(*this)(x,y)->blue = (*this)(w-1-x,y)->blue;			
			(*this)(w-1-x,y)->blue = tempb;

		}
	}
}

//Adds to the red, green, and blue parts of each pixel in the image. 
void Image::adjustbrightness(int r, int g, int b)
{
	int w = (*this).width();
	int h = (*this).height();	
	for (int x = 0; x < w; x++)
	{
		for (int y = 0; y < h; y++)
		{
			if (((*this)(x,y)->red) + r > 255)
			{
				(*this)(x,y)->red = 255;		
			}
			else
			{
				if (((*this)(x,y)->red) + r < 0)
				{
					(*this)(x,y)->red = 0;		
				}
				else
				{
					((*this)(x,y)->red) += r;
				}
			}

			if (((*this)(x,y)->green) + g > 255)
			{
				(*this)(x,y)->green = 255;		
			}
			else
			{
				if (((*this)(x,y)->green) + g < 0)
				{
					(*this)(x,y)->green = 0;		
				}
				else
				{
					((*this)(x,y)->green) += g;
				}
			}

			if (((*this)(x,y)->blue) + b > 255)
			{
				(*this)(x,y)->blue = 255;		
			}
			else
			{
				if (((*this)(x,y)->blue) + b < 0)
				{
					(*this)(x,y)->blue = 0;		
				}
				else
				{
					((*this)(x,y)->blue) += b;
				}
			}
		}
	}
}

//Makes each RGB component of each pixel iequal to 255 minus its original value. 
void Image::invertcolors()
{
	int w = (*this).width();
	int h = (*this).height();	
	for (int x = 0; x < w; x++)
	{
		for (int y = 0; y < h; y++)
		{
			(*this)(x,y)->red = 255 - (*this)(x,y)->red;
			(*this)(x,y)->green = 255 - (*this)(x,y)->green;
			(*this)(x,y)->blue = 255 - (*this)(x,y)->blue;
		}
	}
}
