#ifndef readFunctions_H_
#define readFunctions_H_
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
// return 0 vector , return 1 curve
int type_of_file(char *path);
int calculateInputSize(char *path);
int calculateDimension(char *path);
#endif