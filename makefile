
all: dfs bfs topo display

clean:
	rm -f dfs bfs topo display cpath

cpath: demo.cpp Graph.h CPath.h
	g++ -std=c++11 cpath.cpp -o cpath

demo2: demo.cpp Graph.h
	g++ -std=c++11 demo2.cpp -o demo2

demo: demo.cpp Graph.h
	g++ -std=c++11 demo.cpp -o demo

display: display.cpp Graph.h
	g++ -std=c++11 display.cpp -o display

dfs: dfs.cpp Graph.h
	g++ -std=c++11 dfs.cpp -o dfs

bfs: bfs.cpp Graph.h
	g++ -std=c++11 bfs.cpp -o bfs

topo: topo.cpp Graph.h
	g++ -std=c++11 topo.cpp -o topo

epaths: epaths.cpp Graph.h
	g++ -std=c++11 epaths.cpp -o epaths
