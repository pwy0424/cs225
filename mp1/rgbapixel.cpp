#include "rgbapixel.h"
//default constructor, set rgba to 255
RGBAPixel::RGBAPixel(){
	red = 255;
	green = 255;
	blue = 255;
	alpha = 255;
}

//constructor set rgb, and alpha to 255
RGBAPixel::RGBAPixel(unsigned char newred, unsigned char newgreen, unsigned char newblue){
	red = newred;
	green = newgreen;
	blue = newblue;
	alpha = 255;
}
