#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;

void makePalindromes(ostream& ofile, char* options, int size);


int main(int argc, char* argv[])
{
  if(argc < 4){
    cerr << "Please provide an output file, a string of characters, and the max length" << endl;
    return 1;
  }

  ofstream ofile(argv[1]);
  int len = atoi(argv[3]);
  makePalindromes(ofile, argv[2], len);
  ofile.close();
  return 0;
}

