# what you want your executable (.exe) file to be named 
EXECUTABLE := project3 

# which compiler to use, if using mingw - g++ 
CXX := g++ 

# variables for our source and header files 
SRC_FILES := $(wildcard *.cpp)  

HEADER_FILES := $(wildcard *.h)  

# variable for intermediate binary files (.o files) 
OBJ_FILES := $(patsubst %.cpp,%.o,$(SRC_FILES))  

# flags for the compiler 
LDFLAGS := -g -ggdb -static-libstdc++ -std=gnu++17 -Wall -Wextra -pedantic 

CPPFLAGS := -g -ggdb -static-libstdc++ -std=gnu++17 -Wall -Wextra -pedantic 

# command run to build the executable 
${EXECUTABLE}: $(OBJ_FILES)  

	@${CXX} $(LDFLAGS) -o $@ $^  

# command run to compile our .cpp files to .o binaries 
%.o: %.cpp $(HEADER_FILES)  

	@${CXX} $(CPPFLAGS) -c -o $@ $<  