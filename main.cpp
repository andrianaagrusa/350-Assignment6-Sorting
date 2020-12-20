#include <iostream>
#include <string>
#include <fstream>
#include "Sorting.h"
using namespace std;

int main(int argc, char **argv )
{
  cout << "Enter file: "  << endl;
  string fileName;
  cin >> fileName;
  Sorting *s = new Sorting(fileName);
  s->sortAll();

  return 0;
}
