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

vector<int> nearestVectors(vector<vector<vector<int>>> siarrays, int dimension, int k, int w, int M, int m, int L, vector_struct query, int hash_table_size, vector<int> **hashtables,vector_struct *vectors_array,unsigned int size,unsigned int range)
{
    unsigned int position;
    vector<int> bucket_neighbours;
    vector<int> query_neighbours;
    for (unsigned int i = 0; i < L; i++)
    {
        position = gFunction(siarrays[i], dimension, k, w, M, m, query.vectors);
        position = position % hash_table_size;
        bucket_neighbours=bucketRangeSearch(vectors_array,size,hashtables[i][position],query,range);
        for(unsigned int j=0;j<bucket_neighbours.size();j++){
            //if vector's index doesnt exist in the results then push back to the quury results
            if(vectorExists(bucket_neighbours[j],query_neighbours)==0){
                query_neighbours.push_back(bucket_neighbours[j]);
            }
        }
    }

    return query_neighbours;
}


vector<int> bucketRangeSearch(vector_struct *vectors_array,unsigned int size ,vector<int> bucket, vector_struct query,unsigned int range){
    vector<int> results;
    for(unsigned int i=0;i<bucket.size();i++){
        if(manhattanDistance(vectors_array[bucket[i]].vectors,query.vectors)<range){
                results.push_back(bucket[i]);
        } 
    }
    return results;

}

bool vectorExists(unsigned int index,vector<int> all_indexes){
    for(unsigned int i=0;i<all_indexes.size();i++){
        if(index==all_indexes[i]){
             return 1;
         }
    }
    return 0;
}