#include "vector.h"
#include <bits/stdc++.h>

void fillVectors(int dimension, int size, char *input_file_path, vector_struct *vectors_array)
{
    unsigned int i, j;
    double x;
    string str, q_str, temp;
    ifstream file;
    ofstream output_file;
    //open the input file
    file.open(input_file_path);
    // ignore first line
    getline(file, str, '\n');
    for (i = 0; i < size; i++)
    {
        //get every line in the file
        getline(file, str, '\n');
        stringstream line(str);
        for (int j = 0; j < dimension; j++)
        {
            getline(line, temp, '\t');
            stringstream convert(temp);
            if (j == 0)
            {
                vectors_array[i].intoCluster = 0;
                vectors_array[i].id = temp;
            }
            else
            {
                vectors_array[i].vectors.push_back(x);
            }
        }
    }
    file.close();
}
