# variable declaration
COMPILER = g++
COMPILER_FLAGS = -c -g -O0 -Wall 
LINKER = g++

#define all
all: testimage testscene

# linking
testimage : testimage.o png.o rgbapixel.o image.o
	$(LINKER) testimage.o png.o rgbapixel.o image.o -lpng -o testimage

testscene : testscene.o png.o rgbapixel.o image.o scene.o
	$(LINKER) testscene.o png.o rgbapixel.o image.o scene.o -lpng -o testscene

# compilation
# compile testimage.cpp
testimage.o : testimage.cpp  image.h
	$(COMPILER) $(COMPILER_FLAGS) testimage.cpp

# compile png.cpp
png.o : png.cpp png.h 
	$(COMPILER) $(COMPILER_FLAGS) png.cpp

# compile rgbapixel.cpp
rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(COMPILER) $(COMPILER_FLAGS) rgbapixel.cpp

# compile image.cpp
image.o : image.cpp image.h
	$(COMPILER) $(COMPILER_FLAGS) image.cpp

#compile scene.cpp
scene.o : scene.cpp scene.h
	$(COMPILER) $(COMPILER_FLAGS) scene.cpp

# clean
clean : 
	-rm -f *.o testimage
