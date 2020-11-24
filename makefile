
all: dfs bfs topo display

clean:
	rm -f dfs bfs topo display

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
