#include <iostream>
#include <string.h>
#include "vector.h"
#include <stdlib.h>
#include <time.h>
#include "readFunctions.h"
#include "curves.h"
#include "initialization.h"
#include "clusterStructs.h"
#include "assignment.h"
#include "combinations.h"
using namespace std;
int main(int argc, char const *argv[])
{
    unsigned int DIMENSIONS = 0, INPUT_SIZE = 0, i, curve_file = 0, vector_file = 0;
    char INPUT_PATH[300], CONF_PATH[300], OUTPUT_PATH[300];
    vector_struct *array_of_vectors;

    vector<curve> curves;

    vector<cluster_curves> curves_clusters;
    vector<cluster_vectors> vectors_clusters;
    cluster clusterInfo;

    //we use this at Silhouette
    ofstream outputFile;

    // read args
    if (argc < 7)
    {
        cout << "Not enough arguments" << endl;
        return -1;
    }
    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-i") == 0)
        {
            strcpy(INPUT_PATH, argv[i + 1]);
        }
        if (strcmp(argv[i], "-c") == 0)
        {

            strcpy(CONF_PATH, argv[i + 1]);
        }
        if (strcmp(argv[i], "-o") == 0)
        {
            strcpy(OUTPUT_PATH, argv[i + 1]);
        }
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

    cout << "Input size: " << INPUT_SIZE << endl;

    if (vector_file) // case type is vector
    {
        DIMENSIONS = calculateDimension(INPUT_PATH);
        array_of_vectors = new vector_struct[INPUT_SIZE];
        fillVectors(DIMENSIONS, INPUT_SIZE, INPUT_PATH, array_of_vectors);
        // vectors_clusters = random_lloyd_pam_vector(array_of_vectors, clusterInfo, INPUT_SIZE, OUTPUT_PATH);
        // vectors_clusters = kmeans_lsh_pam_vector(array_of_vectors, clusterInfo, INPUT_SIZE, OUTPUT_PATH);
        vectors_clusters = random_lsh_pam_vector(array_of_vectors, clusterInfo, INPUT_SIZE, OUTPUT_PATH);
        // vectors_clusters = kmeans_lloyd_pam_vector(array_of_vectors, clusterInfo, INPUT_SIZE, OUTPUT_PATH);
    }
    else // case type is curve
    {
        curve *array_of_curves = new curve[INPUT_SIZE];
        for (unsigned int i = 0; i < curves.size(); i++)
        {
            array_of_curves[i] = curves[i];
        }
        calculateCurveDimensions(INPUT_PATH, curves, INPUT_SIZE);
        fillVectorWithCurves(INPUT_PATH, curves, INPUT_SIZE);
        //curves_clusters = random_lloyd_pam_curve(curves, clusterInfo, INPUT_SIZE, array_of_curves, OUTPUT_PATH);
        curves_clusters = random_lsh_pam_curve(curves, clusterInfo, INPUT_SIZE, OUTPUT_PATH);
        //curves_clusters = kmeans_lloyd_pam_curve(curves, clusterInfo, INPUT_SIZE, array_of_curves);
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
    return 0;
}
