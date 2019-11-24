#include "initialization.h"
#include <random>
#include "dtw.h"
vector<vector_struct> k_means_vector(vector_struct *vectors_array, unsigned int k, unsigned int size)
{
    vector<probability_space_vector> probability_density;
    vector<vector_struct> centres;
    probability_space_vector prob_space;
    unsigned int random_number, floored_end;
    double distance, sum = 0, probability;
    vector_struct *init_centre;
    random_number = rand() % size;
    init_centre = &vectors_array[random_number];
    centres.push_back(*init_centre);
    //loop k -1 times to find the remaining centers
    for (unsigned j = 0; j < k - 1; j++)
    {
        sum = 0;
        probability_density.clear();
        //loop through all input and calculate the distance
        for (unsigned int i = 0; i < size; i++)
        {
            //if vector is alrady selected as center skip
            if (init_centre->id.compare(vectors_array[i].id) != 0)
            {
                prob_space.start = sum;
                prob_space.vector_struct_ptr = &vectors_array[i];
                distance = manhattanDistance(init_centre->vectors, vectors_array[i].vectors);
                sum += pow(distance, 2);
                prob_space.end = sum;
                probability_density.push_back(prob_space);
            }
        };
        probability = static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / sum));
        //loop through every probability space
        for (unsigned k = 0; k < probability_density.size(); k++)
        {
            //check if probability space is smaller than current space
            if (probability < probability_density[k].end)
            {
                //new centre found
                centres.push_back(*init_centre);
                //init the centre so to start again until we have k centres
                init_centre = probability_density[k].vector_struct_ptr;
                break;
            }
        }
    }
    return centres;
}
vector<curve> k_means_curve(vector<curve> curves_array, unsigned int k, unsigned int size)
{
    vector<probability_space_curve> probability_density;
    vector<curve> centres;
    probability_space_curve prob_space;
    unsigned int random_number, floored_end;
    double distance, sum = 0, probability;
    curve *init_centre;
    random_number = rand() % size;
    init_centre = &curves_array[random_number];
    centres.push_back(*init_centre);
    //loop k -1 times to find the remaining centers
    for (unsigned j = 0; j < k - 1; j++)
    {
        sum = 0;
        probability_density.clear();
        //loop through all input and calculate the distance
        for (unsigned int i = 0; i < size; i++)
        {
            //if curve is alrady selected as center skip
            if (init_centre->id != curves_array[i].id)
            {
                prob_space.start = sum;
                prob_space.curve_ptr = &curves_array[i];
                distance = dtw(*init_centre, curves_array[i]);
                sum += pow(distance, 2);
                prob_space.end = sum;
                probability_density.push_back(prob_space);
            }
        };
        probability = static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / sum));
        //loop through every probability space
        for (unsigned k = 0; k < probability_density.size(); k++)
        {
            //check if probability space is smaller than current space
            if (probability < probability_density[k].end)
            {
                //new centre found
                centres.push_back(*init_centre);
                //init the centre so to start again until we have k centres
                init_centre = probability_density[k].curve_ptr;
                break;
            }
        }
    }
    return centres;
}

void random_selection_vector(vector_struct *vectors_array, unsigned int k, unsigned int size, vector<vector_struct> &allCenters)
{
    int random_number = 0;

    for (int i = 0; i < k; i++)
    {
        random_number = rand() % size;
        cout << "Random Selection of Vector: " << vectors_array[random_number].id << endl;
        allCenters.push_back(vectors_array[random_number]);
    }
}

void random_selection_curves(vector<curve> curves, unsigned int k, unsigned int size, vector<curve> &allCenters)
{
    int random_number = 0;

    for (int i = 0; i < k; i++)
    {
        random_number = rand() % size;
        cout << "Random Selection of Curve: " << curves[random_number].id << endl;
        allCenters.push_back(curves[random_number]);
    }
}

vector<cluster_curves> init_clusters_curves(unsigned int number_of_clusters)
{
    vector<cluster_curves> clusters;
    cluster_curves cluster;
    for (unsigned int i = 0; i < number_of_clusters; i++)
    {
        clusters.push_back(cluster);
    }
    return clusters;
}
