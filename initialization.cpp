#include "initialization.h"
#include <random>
#include "dtw.h"
vector<cluster_vectors> k_means_vector(vector_struct *vectors_array, unsigned int k, unsigned int size)
{
    vector<probability_space_vector> probability_density;
    vector<cluster_vectors> clusters;
    probability_space_vector prob_space;
    unsigned int random_number, floored_end;
    double distance, sum = 0, probability;
    vector_struct *init_centre;
    random_number = rand() % size;
    init_centre = &vectors_array[random_number];
    clusters = init_clusters_vectors(k);
    clusters[0].centerOfCluster = init_centre;
    //loop k -1 times to find the remaining centers
    for (unsigned j = 1; j < k; j++)
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
                //init the centre so to start again until we have k centres
                init_centre = probability_density[k].vector_struct_ptr;
                clusters[j].centerOfCluster = init_centre;
                break;
            }
        }
    }
    return clusters;
}
vector<cluster_curves> k_means_curve(vector<curve> *curves_array, unsigned int k, unsigned int size)
{
    vector<probability_space_curve> probability_density;
    probability_space_curve prob_space;
    unsigned int random_number, floored_end;
    double distance, sum = 0, probability;
    curve *init_centre;
    vector<cluster_curves> clusters;
    random_number = rand() % size;
    init_centre = &(curves_array->at(random_number));

    clusters = init_clusters_curves(k);
    clusters[0].centerOfCluster = init_centre;
    //loop k -1 times to find the remaining centers
    for (unsigned int j = 1; j < k; j++)
    {
        sum = 0;
        probability_density.clear();
        //loop through all input and calculate the distance
        for (unsigned int i = 0; i < size; i++)
        {
            //if curve is alrady selected as center skip
            if (init_centre->id != curves_array->at(i).id)
            {
                prob_space.start = sum;
                prob_space.curve_ptr = &(curves_array->at(i));
                distance = dtw(*init_centre, curves_array->at(i));
                sum += pow(distance, 2);
                prob_space.end = sum;
                probability_density.push_back(prob_space);
            }
        }
        probability = static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / sum));
        //loop through every probability space
        for (unsigned k = 0; k < probability_density.size(); k++)
        {
            //check if probability space is smaller than current space
            if (probability < probability_density[k].end)
            {

                //init the centre so to start again until we have k centres
                init_centre = probability_density[k].curve_ptr;
                clusters[j].centerOfCluster = init_centre;
                break;
            }
        }
    }
    return clusters;
}

vector<cluster_vectors> random_selection_vector(vector_struct *vectors_array, unsigned int k, unsigned int size)
{
    int random_number = 0;
    vector<cluster_vectors> clusters;
    vector_struct *init_centre;

    clusters = init_clusters_vectors(k);

    for (int i = 0; i < k; i++)
    {
        random_number = rand() % size;
        init_centre = &vectors_array[random_number];
        clusters[i].centerOfCluster = init_centre;
    }
    return clusters;
}

vector<cluster_curves> random_selection_curves(vector<curve> *curves_array, unsigned int k, unsigned int size)
{
    int random_number = 0;
    curve *init_centre;
    vector<cluster_curves> clusters;
    clusters = init_clusters_curves(k);

    for (unsigned int i = 0; i < k; i++)
    {
        random_number = rand() % size;
        cout << "Random Selection of Vector: " << curves_array->at(random_number).id << endl;
        init_centre = &(curves_array->at(random_number));
        clusters[i].centerOfCluster = init_centre;
    }
    return clusters;
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

vector<cluster_vectors> init_clusters_vectors(unsigned int number_of_clusters)
{
    vector<cluster_vectors> clusters;
    cluster_vectors cluster;
    for (unsigned int i = 0; i < number_of_clusters; i++)
    {
        clusters.push_back(cluster);
    }
    return clusters;
}