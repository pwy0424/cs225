#ifndef image_H
#define image_H
#ifndef png_H
#define png_H
#include "png.h"
//class define
class Image : public PNG
{
public :
	void flipleft();//Flips the image about a vertical line through its center by swapping pixels. 
	void adjustbrightness(int r, int g, int b);//Adds to the red, green, and blue parts of each pixel in the image. 
	void invertcolors();//Makes each RGB component of each pixel iequal to 255 minus its original value. 
	
};

#endif//Image
#endif//PNG
