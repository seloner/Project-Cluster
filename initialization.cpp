#include "initialization.h"
vector<vector_struct> k_means_vector(vector_struct *vectors_array, unsigned int k, unsigned int size)
{
    vector<vector_struct> centres;
    int random_number;
    vector_struct init_centre;
    random_number = rand() % size;
    cout << random_number << endl;
    init_centre = vectors_array[random_number];
    cout << init_centre.id << endl;
    return centres;
}
