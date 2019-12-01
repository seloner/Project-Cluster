#include "combinations.h"
#define mBase 2
#define mExp 32
#define mSub 5
/* -------------------------------------------------------------------------- */
/*                           RANDOM LLOYD PAM CURVES                          */
/* -------------------------------------------------------------------------- */

vector<cluster_curves> random_lloyd_pam_curve(vector<curve> curves,
                                              cluster clusterInfo,
                                              unsigned int size, curve *temp) {
  vector<cluster_curves> clusters;
  int counter = 0;
  clusters =
      random_selection_curves(&curves, clusterInfo.number_of_clusters, size);
  while (counter < 5) {
    lloydAssignmentClusterCurves(&curves, &clusters);

    for (int i = 0; i < clusters.size(); i++) {
      cout << "Cluster: " << i
           << "  centre: " << clusters[i].centerOfCluster->id << endl;
    }
    lloydAssignmentClusterCurvesUpdate(&clusters);
    counter++;
  }

  // for (unsigned int i = 0; i < clusters[0].cluster_curves.size(); i++)
  // {
  //     cout << " id   " << clusters[0].cluster_curves[i]->id << endl;
  // }
  // for (unsigned int i = 0; i < clusters[1].cluster_curves.size(); i++)
  // {
  //     cout << " id   " << clusters[1].cluster_curves[i]->id << endl;
  // }

  return clusters;
}

/* -------------------------------------------------------------------------- */
/*                          RANDOM LLOYD PAM VECTORS                          */
/* -------------------------------------------------------------------------- */

vector<cluster_vectors> random_lloyd_pam_vector(vector_struct *vectors_array,
                                                cluster clusterInfo,
                                                unsigned int size) {
  vector<cluster_vectors> clusters;
  vector<cluster_vectors> old_clusters;
  unsigned int THRESHOLD = 100, counter = 0;
  clusters = random_selection_vector(vectors_array,
                                     clusterInfo.number_of_clusters, size);
  // arxikopoihsh old cluster (thelei allagi mporei h random na epistrepsei ta
  // idia kentra )
  old_clusters = random_selection_vector(vectors_array,
                                         clusterInfo.number_of_clusters, size);

  while (compare_vectors_clusters(clusters, old_clusters) == true &&
         counter < THRESHOLD) {
    old_clusters = copy_clusters_vector(&clusters);
    lloydAssignmentClusterVectors(vectors_array, &clusters, size);
    lloydAssignmentClusterVectorsUpdate(&clusters);
    counter++;
  }
  return clusters;
}

/* -------------------------------------------------------------------------- */
/*                          KMEANS LLOYD PAM VECTORS                          */
/* -------------------------------------------------------------------------- */

vector<cluster_vectors> kmeans_lloyd_pam_vector(vector_struct *vectors_array,
                                                cluster clusterInfo,
                                                unsigned int size) {
  vector<cluster_vectors> clusters;
  vector<cluster_vectors> old_clusters;
  unsigned int THRESHOLD = 100, counter = 0;
  clusters =
      k_means_vector(vectors_array, clusterInfo.number_of_clusters, size);
  // arxikopoihsh old cluster (thelei allagi mporei h random na epistrepsei ta
  // idia kentra )
  old_clusters =
      k_means_vector(vectors_array, clusterInfo.number_of_clusters, size);

  while (compare_vectors_clusters(clusters, old_clusters) == true &&
         counter < THRESHOLD) {
    old_clusters = copy_clusters_vector(&clusters);
    for (unsigned int i = 0; i < old_clusters.size(); i++) {
      cout << "cluster old  " << i << "  centre     "
           << old_clusters[i].centerOfCluster->id << endl;
    }
    lloydAssignmentClusterVectors(vectors_array, &clusters, size);
    lloydAssignmentClusterVectorsUpdate(&clusters);
    counter++;
  }
  return clusters;
}

/* -------------------------------------------------------------------------- */
/*                           KMEANS LLOYD PAM CURVE                           */
/* -------------------------------------------------------------------------- */

vector<cluster_curves> kmeans_lloyd_pam_curve(vector<curve> curves,
                                              cluster clusterInfo,
                                              unsigned int size, curve *temp) {
  vector<cluster_curves> clusters;
  vector<cluster_curves> old_clusters;
  unsigned int THRESHOLD = 100, counter = 0;
  clusters = k_means_curve(&curves, clusterInfo.number_of_clusters, size);
  // arxikopoihsh old cluster (thelei allagi mporei h random na epistrepsei ta
  // idia kentra )
  old_clusters = k_means_curve(&curves, clusterInfo.number_of_clusters, size);

  while (compare_curves_clusters(clusters, old_clusters) == true &&
         counter < THRESHOLD) {
    old_clusters = copy_clusters_curves(&clusters);
    for (unsigned int i = 0; i < old_clusters.size(); i++) {
      cout << "cluster old  " << i << "  centre     "
           << old_clusters[i].centerOfCluster->id << endl;
    }
    lloydAssignmentClusterCurves(&curves, &clusters);
    lloydAssignmentClusterCurvesUpdate(&clusters);
    counter++;
  }
  return clusters;
}

/* -------------------------------------------------------------------------- */
/*                           KMEANS LSH PAM VECTORS                           */
/* -------------------------------------------------------------------------- */

vector<cluster_vectors> kmeans_lsh_pam_vector(vector_struct *vectors_array,
                                              cluster clusterInfo,
                                              unsigned int size) {
  unsigned int m, M, HASH_TABLE_SIZE = size / 8;
  int kDivisionExp;
  vector<cluster_vectors> clusters;
  vector<vector<vector<int>>> siarrays;
  double w;
  vector<int> **hashtables;
  hashtables = new vector<int> *[clusterInfo.number_of_vector_hash_tables];
  vector<int> lsh_matches;
  /* -------------------------------- LSH INITS -------------------------------
   */

  int dimension = vectors_array[0].vectors.size();
  m = pow(mBase, mExp) - mSub;
  kDivisionExp = mExp / clusterInfo.number_of_vector_hash_functions;
  M = pow(mBase, kDivisionExp);
  // calculate w
  // // w = calculateW(size, vectors_array);
  w = 5376.42;

  /* ----------------------------------  CLUSTER INIT
   * ---------------------------------- */

  clusters =
      k_means_vector(vectors_array, clusterInfo.number_of_clusters, size);

  /* ------------------------- LSH HASHTABLES CREATION ------------------------
   */

  for (unsigned i = 0; i < clusterInfo.number_of_vector_hash_tables; i++) {
    // generate Si
    siarrays.push_back(
        generateSi(clusterInfo.number_of_vector_hash_functions, w, dimension));
    // create the L hashtable
    hashtables[i] = creteHashTable(
        HASH_TABLE_SIZE, dimension, vectors_array, size,
        clusterInfo.number_of_vector_hash_functions, w, M, m, siarrays[i]);
  }

  /* ------------------------- LSH CLUSTER ASSIGNMENT -------------------------
   */

  for (unsigned int i = 0; i < clusters.size(); i++) {
        lsh_matches = nearestVectors(
        siarrays, dimension, clusterInfo.number_of_vector_hash_functions, w, M,
        m, clusterInfo.number_of_vector_hash_tables,
        *(clusters[i].centerOfCluster), HASH_TABLE_SIZE, hashtables,
        vectors_array, size, 500);
    cout << "-------------------------------------------\n" << endl;
     for(unsigned int l=0;l<lsh_matches.size();l++){

            cout<<"match position : "<<lsh_matches[l]<<endl;

        }
    pushLshResultsToClusterVectors(vectors_array, lsh_matches, &clusters[i]);
  }
  /* ------------------------------- FREE MEMORY ------------------------------
   */

  for (unsigned int i = 0; i < clusterInfo.number_of_vector_hash_tables; i++) {

    delete[] hashtables[i];
  }
  delete[] hashtables;
  return clusters;
}

/* -------------------------------------------------------------------------- */
/*                                   HELPERS                                  */
/* -------------------------------------------------------------------------- */

vector<cluster_vectors>
copy_clusters_vector(vector<cluster_vectors> *clusters) {
  vector<cluster_vectors> new_clusters;
  for (unsigned int i = 0; i < clusters->size(); i++) {
    new_clusters.push_back(clusters->at(i));
  }
  return new_clusters;
}

bool compare_vectors_clusters(vector<cluster_vectors> current,
                              vector<cluster_vectors> old) {
  bool flag = 0;
  for (unsigned int i = 0; i < current.size(); i++) {
    if (current[i].centerOfCluster != old[i].centerOfCluster) {
      flag = 1;
      break;
    }
  }
  return flag;
}

vector<cluster_curves> copy_clusters_curves(vector<cluster_curves> *clusters) {
  vector<cluster_curves> new_clusters;
  for (unsigned int i = 0; i < clusters->size(); i++) {
    new_clusters.push_back(clusters->at(i));
  }
  return new_clusters;
}

bool compare_curves_clusters(vector<cluster_curves> current,
                             vector<cluster_curves> old) {
  bool flag = 0;
  for (unsigned int i = 0; i < current.size(); i++) {
    if (current[i].centerOfCluster != old[i].centerOfCluster) {
      flag = 1;
      break;
    }
  }
  return flag;
}

void pushLshResultsToClusterVectors(vector_struct *vectors_array,
                                    vector<int> results,
                                    cluster_vectors *cluster) {
  for (unsigned int i = 0; i < results.size(); i++) {
    cluster->cluster_vectors.push_back(&(vectors_array[results[i]]));
  }
}

void pushLshResultsToClusterCurves(vector<curve> *curves, vector<int> results,
                                   cluster_curves *cluster) {
  for (unsigned int i = 0; i < results.size(); i++) {
    cluster->cluster_curves.push_back(&curves->at(results[i]));
  }
}
