
#include <iostream>
#include "Graph.h"


int main(int argc, char *argv[]){
  graph g;

  if(argc != 2) 
    std::cout << "usage:  display <filename>\n";
  else {
    if(!g.read_file(argv[1]))
      std::cout << "could not open file '" << argv[1] << "'\n";
  }

  std::cout << "\nADJACENCY-LIST REPRESENTATION:\n\n";
  g.display();


  return 0;
}

