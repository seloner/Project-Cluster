#include "vector.h"
#include "metrics.h"
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
            convert >> x;
            if (j == 0)
            {
                vectors_array[i].cluster_index = -1;
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

double NearestNeighbourDistance(int size, vector_struct *array, vector_struct query)
{
    double distance = 0, min_distance, id;
    //for every item in th array
    for (int i = 0; i < size; i++)
    {
        //calculate the distance
        distance = manhattanDistance(array[i].vectors, query.vectors);
        //if it is the first item set  min
        if (i == 0)
        {
            min_distance = distance;
            //get the id of the item
        }
        else
        {
            //if we have a new min update
            if (distance < min_distance && distance != 0)
            {

                min_distance = distance;
            }
        }
    }
    //return the id
    return min_distance;
}

double calculateW(int size, vector_struct *array)
{
    double sum = 0;
    double w = 0;
    for (int i = 0; i < size; i++)
    {

        sum += NearestNeighbourDistance(size, array, array[i]);
    }
    w = 4 * (sum / size);
    return w;
}