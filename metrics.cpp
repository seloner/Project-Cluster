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