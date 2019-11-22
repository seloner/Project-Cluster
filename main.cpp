#include <iostream>
#include <string.h>
#include "vector.h"
#include <stdlib.h>
#include <time.h>
#include "readFunctions.h"
#include "curveStructs.h"
#include "initialization.h"
#include "clusterStructs.h"

using namespace std;
int main(int argc, char const *argv[])
{
    unsigned int DIMENSIONS = 0, INPUT_SIZE = 0, i, curve_file = 0, vector_file = 0;
    char INPUT_PATH[300], CONF_PATH[300], OUTPUT_PATH[300];
    vector_struct *array_of_vectors;

    //cluster info from conf
    cluster clusterInfo;


    //all the curves
    vector<curve> curves;

    //clusters from random selection
    vector<vector_struct> randomSelectionForPoints;
    vector<curve> randomSelectionForCurves;

    // read args
    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-i") == 0)
        {
            strcpy(INPUT_PATH, argv[i + 1]);
        }
        if (strcmp(argv[i], "-c") == 0)
        {
            if (argc - 1 < i + 1)
            {

                cout << "No -c given" << endl;
            }
            else
            {
                strcpy(CONF_PATH, argv[i + 1]);
            }
        }
        if (strcmp(argv[i], "-o") == 0)
        {
            if (argc - 1 < i + 1)
            {

                cout << "No -o given" << endl;
            }
            else
            {
                strcpy(OUTPUT_PATH, argv[i + 1]);
            }
        }
        
        //TODO (optional) take "-complete" as if argument and do stuff
    }

    // init rand
    srand(time(NULL));

    //calculations
    INPUT_SIZE = calculateInputSize(INPUT_PATH) - 1;
    if (type_of_file(INPUT_PATH) == 0)
    {
        vector_file = 1;
    }
    else
    {
        curve_file = 1;
    }

    //check conf file about clusters
    readClusterConf(CONF_PATH, clusterInfo);
    cout << "test cluster: "<<clusterInfo.number_of_clusters <<endl;

    cout << "Input size: " << INPUT_SIZE << endl;

    if (vector_file) // case type is vector
    {
        DIMENSIONS = calculateDimension(INPUT_PATH);
        array_of_vectors = new vector_struct[INPUT_SIZE];
        fillVectors(DIMENSIONS, INPUT_SIZE, INPUT_PATH, array_of_vectors);

        random_selection_vector(array_of_vectors, 3, INPUT_SIZE, randomSelectionForPoints);

        k_means_vector(array_of_vectors, 3, INPUT_SIZE);
    }
    else // case type is curve
    {
        calculateCurveDimensions(INPUT_PATH, curves, INPUT_SIZE);
        fillVectorWithCurves(INPUT_PATH, curves, INPUT_SIZE);

        random_selection_curves(curves, 3, INPUT_SIZE, randomSelectionForCurves);
    }


    /**
     *
     * FREE MEMORY
     *
     */

    if (vector_file)
    {

        delete[] array_of_vectors;
    }

    //delete clusterInfo
    //delete clusterInfo;

    return 0;
}
