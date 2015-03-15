#ifndef rgbapixel_H
#define rgbapixel_H

class RGBAPixel{
public:
	/*RGBAPixel::*/RGBAPixel(); //default constructor, set rgba to 255
	/*RGBAPixel::*/RGBAPixel(unsigned char newred, unsigned char newgreen, unsigned char newblue);//constructor set rgb, and alpha to 255
	//four variables	
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	unsigned char alpha;
};

#endif //RGBAPixel
