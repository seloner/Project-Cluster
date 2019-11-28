#include "lsh.h"

vector<vector<int>> generateSi(int k, int w, int dimension)
{
    vector<int> temp;
    vector<vector<int>> array_temp;
    int x;

    for (int i = 0; i < k; i++)
    {
        //for every k allocate space for one vector
        for (int j = 0; j < dimension; j++)
        {
            //generate a random x
            x = rand() % w + 1;
            temp.push_back(x);
            //push x into the vector
        }
        array_temp.push_back(temp);
        temp.clear();
    }
    return array_temp;
}
vector<int> *creteHashTable(int hash_table_size, int dimension, vector_struct *vectors_array, unsigned int size, int k, int w, int M, int m, vector<vector<int>> siarray)
{

    unsigned int i = 0, position;
    vector<int> *hashtable;
    hashtable = new vector<int>[hash_table_size];
    for (i = 0; i < size; i++)
    {
        position = gFunction(siarray, dimension, k, w, M, m, vectors_array[i].vectors);
        position = position % hash_table_size;
        hashtable[position].push_back(i);
    }
    return hashtable;
}

vector<int> nearestVectors(vector<vector<vector<int>>> siarrays, int dimension, int k, int w, int M, int m, int L, vector<double> query, int hash_table_size, vector<int> **hashtables)
{
    unsigned int position;
    vector<int> neighbours;
    for (unsigned int i = 0; i < L; i++)
    {
        position = gFunction(siarrays[i], dimension, k, w, M, m, query);
        position = position % hash_table_size;
    }

    return neighbours;
}
