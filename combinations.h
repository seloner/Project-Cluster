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
#include "grid_functions.h"

using namespace std;

typedef struct Silhouette
{
    double a;
    double b;
} Silhouette;
/* vectors */
vector<cluster_vectors> random_lloyd_pam_vector(vector_struct *vectors_array, cluster clusterInfo, unsigned int size, char const *out_path);
vector<cluster_vectors> kmeans_lloyd_pam_vector(vector_struct *vectors_array, cluster clusterInfo, unsigned int size, char const *out_path);
vector<cluster_vectors> kmeans_lsh_pam_vector(vector_struct *vectors_array, cluster clusterInfo, unsigned int size, char const *out_path);
vector<cluster_vectors> random_lsh_pam_vector(vector_struct *vectors_array, cluster clusterInfo, unsigned int size, char const *out_path);

/* curves */
vector<cluster_curves> random_lloyd_pam_curve(vector<curve> curves, cluster clusterInfo, char const *out_path);
vector<cluster_curves> kmeans_lloyd_pam_curve(vector<curve> curves, cluster clusterInfo, char const *out_path);
vector<cluster_curves> random_lsh_pam_curve(vector<curve> curves, cluster clusterInfo, unsigned int size, char const *out_path);

/* helpers */

//returns 0 if same clusters ,1 if different  clusters
bool compare_vectors_clusters(vector<cluster_vectors> current, vector<cluster_vectors> old);
void pushLshResultsToClusterCurves(vector<curve> *curves, vector<int> results, cluster_curves *cluster);
void pushLshResultsToClusterVectors(vector_struct *vectors_array, vector<int> results, cluster_vectors *cluster);
bool compare_curves_clusters(vector<cluster_curves> current, vector<cluster_curves> old);
vector<cluster_curves> copy_clusters_curves(vector<cluster_curves> *clusters);
void init_clusters_vectors(vector<cluster_vectors> *clusters);
void init_clusters_curves(vector<cluster_curves> *clusters);
vector<cluster_vectors> copy_clusters_vector(vector<cluster_vectors> *clusters);
unsigned int calcluateClosestClusterIndexVectors(vector<cluster_vectors> clusters, vector_struct vector, unsigned int current_cluster_index);
unsigned int calcluateClosestClusterIndexCurves(vector<cluster_curves> clusters, curve curve, unsigned int current_cluster_index);

/* silhouette */

double calculateAverageSilhouetteVectors(cluster_vectors cluster, vector_struct vector);
double calculateAverageSilhouetteCurves(cluster_curves cluster, curve curve);
double calculateSVectors(vector<Silhouette> a_b_vector);

vector<Silhouette> calculate_a_b_vectors(vector<cluster_vectors> clusters, cluster_vectors current_cluster, unsigned int current_cluster_index);
vector<Silhouette> calculate_a_b_curves(vector<cluster_curves> clusters, cluster_curves current_cluster, unsigned int current_cluster_index);

void runSilhouetteForCurves(vector<cluster_curves> clusters, char const *outfile, char const *case_name, double clustering_time);
void runSilhouetteForVectors(vector<cluster_vectors> clusters, char const *outfile, char const *case_name, double clustering_time);
#endif