#include <unistd.h>
#include "dtw.h"
double finddistance(point a, point b)
{
    double afairesi = abs(a.x - b.x);
    double beforeSqrt1 = pow(afairesi, 2);
    afairesi = abs(a.y - b.y);
    double beforeSqrt2 = pow(afairesi, 2);
    double result = sqrt(beforeSqrt1 + beforeSqrt2);
    return result;
}

double dtw(curve curve1, curve curve2)
{
    vector<vector<double>> matrixArray;
    vector<double> nodes;
    double distance = 0;
    int arrayDimensionX, arrayDimensionY;
    arrayDimensionX = curve1.dimensions;
    arrayDimensionY = curve2.dimensions;
    //cout << "curve2.id:" << curve2.id <<" curve2.dimensions:" << curve2.dimensions<< endl;
    //computing 2d array
    //points from curve1
    for (int i = 0; i < arrayDimensionX; i++)
    {
        ///cout << endl<< "DEBUG 1 me i="<<i <<endl;
        nodes.clear();
        //points from curve2
        for (int j = 0; j < arrayDimensionY; j++)
        {
            //cout << "DEBUG 2 me j="<<j <<endl;
            // cases
            if (i == 0 && j == 0)
            {
                distance = finddistance(curve1.vectorPoins[i], curve2.vectorPoins[j]);
                //cout << "DEBUG 3" <<endl;
            }
            else if (i == 0)
            {
                distance = nodes[j - 1] + finddistance(curve1.vectorPoins[i], curve2.vectorPoins[j]);
                //cout << "DEBUG 4" <<endl;
            }
            else if (j == 0)
            {
                distance = matrixArray[i - 1][j] + finddistance(curve1.vectorPoins[i], curve2.vectorPoins[j]);
                //cout << "DEBUG 5" <<endl;
            }
            else
            {
                //we find the distance and we check for the min to add
                // cout << "DEBUG 6" <<endl;

                distance = finddistance(curve1.vectorPoins[i], curve2.vectorPoins[j]);
                // cout << "DEBUG 7" <<endl;

                if (nodes[j - 1] <= matrixArray[i - 1][j] && nodes[j - 1] <= matrixArray[i - 1][j - 1])
                {
                    distance += nodes[j - 1];
                    //   cout << "DEBUG 8" <<endl;
                }
                else if (matrixArray[i - 1][j] <= nodes[j - 1] && matrixArray[i - 1][j] <= matrixArray[i - 1][j - 1])
                {
                    distance += matrixArray[i - 1][j];
                    //  cout << "DEBUG 9" <<endl;
                }
                else
                {
                    distance += matrixArray[i - 1][j - 1];
                    // cout << "DEBUG 10" <<endl;
                }
            }
            //cout << "DEBUG 11" <<endl;

            nodes.push_back(distance);
            // cout << "DEBUG 12" <<endl;
        }
        //cout << "DEBUG 13" <<endl;

        matrixArray.push_back(nodes);
        //cout << "DEBUG 14" <<endl;
    }

    return matrixArray[arrayDimensionX - 1][arrayDimensionY - 1];
}