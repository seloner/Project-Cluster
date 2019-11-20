#include <iostream>
#include <string.h>
#include "readFunctions.h"
#include "vector.h"
using namespace std;
int main(int argc, char const *argv[])
{
    unsigned int DIMENSIONS = 0, INPUT_SIZE = 0, i, curve_file = 0, vector_file = 0;
    char INPUT_PATH[300];
    vector_struct *array_of_vectors;
    // read args
    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-i") == 0)
        {
            strcpy(INPUT_PATH, argv[i + 1]);
        }
    }
    //calculations
    INPUT_SIZE = calculateInputSize(INPUT_PATH) - 1;
    DIMENSIONS = calculateDimension(INPUT_PATH);
    if (type_of_file(INPUT_PATH) == 0)
    {
        vector_file = 1;
    }
    else
    {
        curve_file = 1;
    }
    // case type is vector
    if (vector_file)
    {
        array_of_vectors = new vector_struct[INPUT_SIZE];
        fillVectors(DIMENSIONS, INPUT_SIZE, INPUT_PATH, array_of_vectors);
    }
    cout << "Input size: " << INPUT_SIZE << ", dimension size:" << DIMENSIONS << endl;

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
