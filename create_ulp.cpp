#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/*
 * string str = "commands";
 * exit(str);
 *
 */

const string INFILE = "data.txt";

int main() {
  ofstream file;
  file.open("create_polygon.ulp");
  ifstream infile;
  infile.open(INFILE);

  file << "string str = \"";
  char c;
  while (infile.get(c)) {
    if (c == '\n') continue;
    file << c;
  }
  file << "\";" << endl;
  file << "exit(str);" << endl;

  infile.close();
  file.close();
}
