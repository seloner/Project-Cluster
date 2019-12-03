#ifndef combinations_H_
#define combinations_H_
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <time.h>
#include "assignment.h"
#include "initialization.h"
#include "update.h"
#include "lsh.h"
using namespace std;

typedef struct Silhouette
{
    double a;
    double b;
} Silhouette;

vector<cluster_curves> random_lloyd_pam_curve(vector<curve> curves, cluster clusterInfo, unsigned int size, curve *temp, char const *out_path);
vector<cluster_vectors> random_lloyd_pam_vector(vector_struct *vectors_array, cluster clusterInfo, unsigned int size, char const *out_path);
vector<cluster_vectors> copy_clusters_vector(vector<cluster_vectors> *clusters);
//returns 0 if same clusters ,1 if different  clusters
bool compare_vectors_clusters(vector<cluster_vectors> current, vector<cluster_vectors> old);
void pushLshResultsToClusterVectors(vector_struct *vectors_array, vector<int> results, cluster_vectors *cluster);
void pushLshResultsToClusterCurves(vector<curve> *curves, vector<int> results, cluster_curves *cluster);
bool compare_curves_clusters(vector<cluster_curves> current, vector<cluster_curves> old);
vector<cluster_curves> copy_clusters_curves(vector<cluster_curves> *clusters);

vector<cluster_curves> kmeans_lloyd_pam_curve(vector<curve> curves, cluster clusterInfo, unsigned int size, curve *temp);
vector<cluster_vectors> kmeans_lloyd_pam_vector(vector_struct *vectors_array, cluster clusterInfo, unsigned int size, char const *out_path);
vector<cluster_vectors> kmeans_lsh_pam_vector(vector_struct *vectors_array, cluster clusterInfo, unsigned int size);

vector<float> runSilhouetteForVectors(vector<cluster_vectors> clusters, char const *outfile, char const *case_name, double clustering_time);
vector<float> runSilhouetteForCurves(vector<cluster_curves> *clusters);
vector<Silhouette> calculate_a_b_vectors(vector<cluster_vectors> clusters, cluster_vectors current_cluster, unsigned int current_cluster_index);
double calculateAverageSilhouetteVectors(cluster_vectors cluster, vector_struct vector);
unsigned int calcluateClosestClusterIndexVectors(vector<cluster_vectors> clusters, vector_struct vector, unsigned int current_cluster_index);
double calculateSVectors(vector<Silhouette> a_b_vector);

#endif