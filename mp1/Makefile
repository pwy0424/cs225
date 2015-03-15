# variable declaration
COMPILER = g++
COMPILER_FLAGS = -c -g -O0 -Wall -Werror
LINKER = g++

# linking
mp1 : main.o png.o rgbapixel.o
	$(LINKER) main.o png.o rgbapixel.o -lpng -o mp1

# compilation
# compile main.cpp
main.o : main.cpp  png.h rgbapixel.h
	$(COMPILER) $(COMPILER_FLAGS) main.cpp
# compile png.cpp
png.o : png.cpp png.h 
	$(COMPILER) $(COMPILER_FLAGS) png.cpp
# compile rgbapixel.cpp
rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(COMPILER) $(COMPILER_FLAGS) rgbapixel.cpp

# clean
clean : 
	-rm -f *.o mp1
	
