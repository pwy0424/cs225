#include "rgbapixel.h"
#include "png.h"
#include <iostream>
using namespace std;
int main(void){
	PNG original;
	original.readFromFile("in.png");//take in the original picture
	//rotation(original).writeToFile("out.png");
	PNG result = PNG(original.width(), original.height());//create a new, blank picture to return
	for (int i = 0; i < original.width();i++){
		for (int j = 0; j < original.height();j++){
			result(original.width()-1-i,original.height()-1-j)->red = original(i,j)->red;
			result(original.width()-1-i,original.height()-1-j)->green = original(i,j)->green;
			result(original.width()-1-i,original.height()-1-j)->blue = original(i,j)->blue;
		}
	}//nested for loops to move each pixel from original picture to their right positon in the new result picture
	result.writeToFile("out.png");//out put result picture
	return 0;
}

/*PNG rotation(PNG original){
	PNG result = new PNG(original.width(), original.height());
	for (int i = 0; i < original.width();i++){
		for (int j = 0; j < original.height();j++){
			result(original.width()-1-i,original.height()-1-j)->red = original(i,j)->red;
			result(original.width()-1-i,original.height()-1-j)->green = original(i,j)->green;
			result(original.width()-1-i,original.height()-1-j)->blue = original(i,j)->blue;
		}
	}

	return result;
}*/


