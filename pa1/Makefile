EXEMAIN = pa1
EXEBlock = testBlock
EXEGrid = testGridList
OBJS  = main.o PNG.o HSLAPixel.o lodepng.o gridlist.o block.o
OBJS_B = testblock.o PNG.o HSLAPixel.o lodepng.o block.o
OBJS_G = testgridlist.o PNG.o HSLAPixel.o lodepng.o gridlist.o block.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lpthread -lm

all : pa1 testBlock testGridList

$(EXEMAIN) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXEMAIN)

$(EXEBlock) : $(OBJS_B)
	$(LD) $(OBJS_B) $(LDFLAGS) -o $(EXEBlock)

$(EXEGrid) : $(OBJS_G)
	$(LD) $(OBJS_G) $(LDFLAGS) -o $(EXEGrid)

main.o : main.cpp gridlist.h cs221util/PNG.h cs221util/HSLAPixel.h block.h
	$(CXX) $(CXXFLAGS) main.cpp

testblock.o : testblock.cpp cs221util/PNG.h cs221util/HSLAPixel.h block.h
	$(CXX) $(CXXFLAGS) testblock.cpp

testgridlist.o : testgridlist.cpp gridlist.h cs221util/PNG.h cs221util/HSLAPixel.h block.h
	$(CXX) $(CXXFLAGS) testgridlist.cpp

gridlist.o : gridlist_given.cpp gridlist.cpp gridlist.h block.h
	$(CXX) $(CXXFLAGS) gridlist.cpp

block.o : block.cpp block.h cs221util/PNG.h cs221util/HSLAPixel.h cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) block.cpp

PNG.o : cs221util/PNG.cpp cs221util/PNG.h cs221util/HSLAPixel.h cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/PNG.cpp

HSLAPixel.o : cs221util/HSLAPixel.cpp cs221util/HSLAPixel.h
	$(CXX) $(CXXFLAGS) cs221util/HSLAPixel.cpp

lodepng.o : cs221util/lodepng/lodepng.cpp cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/lodepng/lodepng.cpp

clean :
	-rm -f *.o $(EXEMAIN) $(EXEBlock) $(EXEGrid)