#ifndef vector_H_
#define vector_H_
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
typedef struct
{
    vector<double> vectors;
    string id;
    bool intoCluster;
} vector_struct;
void fillVectors(int dimension, int size, char *input_file_path, vector_struct *vectors_array);
double NearestNeighbourDistance(int size, vector_struct *array, vector_struct query);
double calculateW(int size, vector_struct *array);


#endif