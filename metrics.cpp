#include "metrics.h"
#include <vector>
double manhattanDistance(vector<double> vector1, vector<double> vector2)
{
    double total_distance = 0;
    if (vector1.size() != vector2.size())
    {
        cout << "CAUTION,VECTORS NOT THE SAME SIZE" << endl;
        return 0;
    }
    else
    {
        //for every point in the vector 1 calculate the distance from vector2
        //ignore the first field because its the id (i=1)
        for (unsigned int i = 0; i < vector1.size(); i++)
        //get the absolute value
        {
            total_distance += fabs(vector1.at(i) - vector2.at(i));
        }
    }
    return total_distance;
}

unsigned int gFunction(vector<vector<int>> siarrays, int dimension, int k, int w, int M, int m, vector<double> xiArray)
{
    vector<int> results;
    unsigned int result = 0, position = 0;
    //calculate every h function result
    for (int j = 0; j < k; j++)
    {
        result = hFunction(siarrays[j], dimension, w, M, m, xiArray);
        results.push_back(result);
    }
    //concentrate all bits
    position = bitsConcetrate(results, 32 / k);
    results.clear();
    //return position
    return position;
}

unsigned int hFunction(vector<int> siArray, int dimensions, int W, int M, int m, vector<double> xiArray)
{
    int floorResult = 0, floorResultWithMod = 0, expResult = 0, expResultWithMod = 0, multiplyFloorExp = 0, multiplyFloorExpWithMod = 0, finalResult = 0, expToSend = 0;
    unsigned int finalResultWithMod = 0;
    for (int i = 0; i < dimensions; i++)
    {
        floorResult = floor((double)(xiArray[i] - siArray[i]) / (double)W);
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
int modularExp(int vasi, int ekthetis, int modwith)
{
    unsigned int result = 0;
    long number = 0;
    // elegxos vasis
    if (vasi == 0)
        return 0;
    if (ekthetis == 0)
        return 1;

    if (ekthetis % 2 == 0) // an o ekthetis einai artios
    {
        number = modularExp(vasi, ekthetis / 2, modwith);
        number = (number * number) % modwith;
    }
    else // an o ekthetis einai perittos
    {
        number = vasi % modwith;
        number = (number * modularExp(vasi, ekthetis - 1, modwith) % modwith) % modwith;
    }
    result = (number + modwith) % modwith;
    return result;
}

int modFunction(int a, int mod_b)
{
    int result = a % mod_b;
    if (result < 0)
        result += mod_b;
    return result;
}

unsigned int bitsConcetrate(vector<int> bits, int bits_size)
{
    //subtract the padding
    int base = 32;
    int padding = base - bits.size() * bits_size;
    base = base - padding;
    unsigned int sum = 0;
    // vector to save the concetrated values
    vector<unsigned int> concetratedValue;
    for (int i = 0; i < bits.size(); i++)
    {
        //for every k-bit number calculate the concetrated value
        //subtract k
        base = base - bits_size;
        //save the concetrated value
        concetratedValue.push_back(bits.at(i) << base);
    }
    //calculate the sum of the concetrated values
    for (int i = 0; i < concetratedValue.size(); i++)
    {

        sum += concetratedValue.at(i);
    }

    return sum;
}