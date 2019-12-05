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

vector<int> *creteHashTablev2(int hash_table_size, int dimension, vector<vector<double>> vectors, int k, int w, int M, int m, vector<vector<int>> siarray)
{

    unsigned int i = 0, position;
    vector<int> *hashtable;
    hashtable = new vector<int>[hash_table_size];
    for (i = 0; i < vectors.size(); i++)
    {
        position = gFunctionv2(siarray, dimension - 1, k, w, M, m, vectors[i]);
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

vector<int> nearestCurves(vector<vector<vector<int>>> siarrays, vector<int> dimensionsQueryTable, int k, int w, int M, int m, curve queryCurves, vector<curve> allCurves, int L, grid_vectors *grid_vectors_query, int hash_table_size, vector<int> **hashtables)
{   
    unsigned int position;
    vector<int> bucket_neighbours;
    vector<int> query_neighbours;

    for (int j = 0; j < L; j++)
    {
        position = gFunctionv2(siarrays[j], dimensionsQueryTable[j] - 1, k, w, M, m, grid_vectors_query[j].vectors[0]);
        position = position % hash_table_size;
        bucket_neighbours = dtwNearestInBucket(hashtables[j][position], allCurves, 0, queryCurves);
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

unsigned int gFunctionv2(vector<vector<int>> siarrays, int dimension, int k, int w, int M, int m, vector<double> xiArray)
{
    w = 300000;
    vector<int> results;
    unsigned int result = 0, position = 0;
    //calculate every h function result
    for (int j = 0; j < k; j++)
    {
        result = hFunctionv2(siarrays[j], dimension, w, M, m, xiArray);
        results.push_back(result);
    }
    //concentrate all bits
    position = bitsConcetrate(results, 32 / k);
    results.clear();
    //return position
    return position;
}

unsigned int hFunctionv2(vector<int> siArray, int dimensions, int W, int M, int m, vector<double> xiArray)
{
    int floorResult = 0, floorResultWithMod = 0, expResult = 0, expResultWithMod = 0, multiplyFloorExp = 0, multiplyFloorExpWithMod = 0, finalResult = 0, expToSend = 0;
    unsigned int finalResultWithMod = 0;
    for (int i = 0; i < dimensions; i++)
    {
        floorResult = floor((double)(xiArray[i + 1] - siArray[i]) / (double)W);
        floorResultWithMod = modFunction(floorResult, M);
        expToSend = dimensions - 1 - i;
        expResult = modularExp(m, expToSend, M);
        expResultWithMod = modFunction(expResult, M);

        multiplyFloorExp = floorResultWithMod * expResultWithMod; // (A * B) mod C = (A mod C * B mod C) mod C
        multiplyFloorExpWithMod = multiplyFloorExp % M;

        finalResult += multiplyFloorExpWithMod;
    }
    finalResultWithMod = finalResult % M;

    return finalResultWithMod;
}

vector<int> dtwNearestInBucket(vector<int> bucket, vector<curve> curves, int threshold, curve query)
{
    unsigned int i = 0, limit = 0;
    double distance = 0, minDistance = 0;
    vector<int> results;
    //threshold 0 ->search all the bucket
    if (threshold == 0)
    {
        limit = bucket.size();
    }
    else
    {
        //if threshhold <bucket size ->serach until the threshold
        if (threshold < bucket.size())
            limit = threshold;
        //else serach all bucket
        else
            limit = bucket.size();
    }
    //init info node
    //info.id = -1;
    // info.distance = 0;
    //loop until the limit

    for (i = 0; i < limit; i++)
    {
        distance = dtw(curves[bucket[i]], query);
        //for first curve set min
        if (i == 0)
        {
            minDistance = distance;
        }
        else
        {
            //if distance is small than current distance update info
            if (distance < minDistance && distance > 0)
            {
                minDistance = distance;
            }
        }
        results.push_back(bucket[i]);
    }

    return results;
}