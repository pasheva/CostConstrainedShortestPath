
all: cpath

clean:
	rm -f  cpath

cpath: Graph.h CPath.h g.h
	g++ -std=c++11 cpath.cpp -o cpath


