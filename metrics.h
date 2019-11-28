#ifndef distances_H_
#define distances_H_
using namespace std;
#include <iostream>
#include <vector>
#include <math.h>
double manhattanDistance(vector<double> vector1, vector<double> vector2);
unsigned int gFunction(vector<vector<int>> siarrays, int dimension, int k, int w, int M, int m, vector<double> xiArray);
unsigned int hFunction(vector<int> siArray, int dimensions, int W, int M, int m, vector<double> xiArray);
int modularExp(int vasi, int ekthetis, int modwith);
int modFunction(int a, int mod_b);
unsigned int bitsConcetrate(vector<int> bits, int bits_size);

#endif