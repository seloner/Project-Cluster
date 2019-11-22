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

void random_selection_vector (vector_struct *vectors_array, unsigned int k, unsigned int size, vector<vector_struct> &allCenters)
{
    int random_number = 0;

    for(int i = 0; i<k; i++)
    {
        random_number = rand() % size;
        cout << "Random Selection of Vector: " << vectors_array[random_number].id << endl;
        allCenters.push_back(vectors_array[random_number]);
    }
}

void random_selection_curves (vector<curve> curves, unsigned int k, unsigned int size, vector<curve> &allCenters)
{
    int random_number = 0;

    for(int i = 0; i<k; i++)
    {
        random_number = rand() % size;
        cout << "Random Selection of Curve: " << curves[random_number].id << endl;
        allCenters.push_back(curves[random_number]);
    }
}