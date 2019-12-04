#include "combinations.h"
#define mBase 2
#define mExp 32
#define mSub 5
/* -------------------------------------------------------------------------- */
/*                           RANDOM LLOYD PAM CURVES                          */
/* -------------------------------------------------------------------------- */

vector<cluster_curves> random_lloyd_pam_curve(vector<curve> curves, cluster clusterInfo, char const *out_path)
{
  vector<cluster_curves> clusters, old_clusters;
  unsigned int THRESHOLD = 100, counter = 0, size = curves.size();
  clusters = random_selection_curves(&curves, clusterInfo.number_of_clusters, size);
  old_clusters = random_selection_curves(&curves, clusterInfo.number_of_clusters, size);
  auto startC = chrono::steady_clock::now();

  /* break when we rearch  threshhold or we get the same Centres  */
  while (compare_curves_clusters(clusters, old_clusters) == true && counter < 5)
  {
    init_clusters_curves(&clusters);
    old_clusters = copy_clusters_curves(&clusters);
    lloydAssignmentClusterCurves(&curves, &clusters);
    lloydAssignmentClusterCurvesUpdate(&clusters);
    counter++;
  }
  auto endC = chrono::steady_clock::now();
  auto diff = endC - startC;
  double clustering_time = (chrono::duration<double, milli>(diff).count()) / 1000;
  runSilhouetteForCurves(clusters, out_path, "RANDOM LLOYD PAM", clustering_time);

  return clusters;
}

/* -------------------------------------------------------------------------- */
/*                          RANDOM LLOYD PAM VECTORS                          */
/* -------------------------------------------------------------------------- */

vector<cluster_vectors> random_lloyd_pam_vector(vector_struct *vectors_array, cluster clusterInfo, unsigned int size, char const *out_path)
{
  vector<cluster_vectors> clusters;
  vector<cluster_vectors> old_clusters;
  unsigned int THRESHOLD = 100, counter = 0;
  clusters = random_selection_vector(vectors_array, clusterInfo.number_of_clusters, size);
  old_clusters = random_selection_vector(vectors_array, clusterInfo.number_of_clusters, size);

  auto startC = chrono::steady_clock::now();
  while (compare_vectors_clusters(clusters, old_clusters) == true && counter < THRESHOLD)
  {
    init_clusters_vectors(&clusters);
    old_clusters = copy_clusters_vector(&clusters);
    lloydAssignmentClusterVectors(vectors_array, &clusters, size);
    lloydAssignmentClusterVectorsUpdate(&clusters);
    counter++;
  }
  auto endC = chrono::steady_clock::now();
  auto diff = endC - startC;
  double clustering_time = (chrono::duration<double, milli>(diff).count()) / 1000;
  runSilhouetteForVectors(clusters, out_path, "RANDOM LLOYD PAM", clustering_time);

  return clusters;
}

/* -------------------------------------------------------------------------- */
/*                          KMEANS LLOYD PAM VECTORS                          */
/* -------------------------------------------------------------------------- */

vector<cluster_vectors> kmeans_lloyd_pam_vector(vector_struct *vectors_array, cluster clusterInfo, unsigned int size, char const *out_path)
{
  vector<cluster_vectors> clusters;
  vector<cluster_vectors> old_clusters;
  unsigned int THRESHOLD = 100, counter = 0;
  auto startC = chrono::steady_clock::now();

  clusters = k_means_vector(vectors_array, clusterInfo.number_of_clusters, size);
  old_clusters = k_means_vector(vectors_array, clusterInfo.number_of_clusters, size);
  /* break when we rearch  threshhold or we get the same Centres  */
  while (compare_vectors_clusters(clusters, old_clusters) == true && counter < THRESHOLD)
  {
    old_clusters = copy_clusters_vector(&clusters);
    init_clusters_vectors(&clusters);
    lloydAssignmentClusterVectors(vectors_array, &clusters, size);
    lloydAssignmentClusterVectorsUpdate(&clusters);
    counter++;
  }
  auto endC = chrono::steady_clock::now();
  auto diff = endC - startC;
  double clustering_time = (chrono::duration<double, milli>(diff).count()) / 1000;
  runSilhouetteForVectors(clusters, out_path, "KMEANS LLOYD PAM", clustering_time);
  return clusters;
}

/* -------------------------------------------------------------------------- */
/*                           KMEANS LLOYD PAM CURVE                           */
/* -------------------------------------------------------------------------- */

vector<cluster_curves> kmeans_lloyd_pam_curve(vector<curve> curves, cluster clusterInfo, char const *out_path)
{
  vector<cluster_curves> clusters;
  vector<cluster_curves> old_clusters;
  unsigned int THRESHOLD = 100, counter = 0, size = curves.size();
  auto startC = chrono::steady_clock::now();
  clusters = k_means_curve(&curves, clusterInfo.number_of_clusters, size);
  // arxikopoihsh old cluster (thelei allagi mporei h random na epistrepsei ta
  // idia kentra )
  old_clusters = k_means_curve(&curves, clusterInfo.number_of_clusters, size);

  while (compare_curves_clusters(clusters, old_clusters) == true &&
         counter < THRESHOLD)
  {
    init_clusters_curves(&clusters);
    old_clusters = copy_clusters_curves(&clusters);
    lloydAssignmentClusterCurves(&curves, &clusters);
    lloydAssignmentClusterCurvesUpdate(&clusters);
    counter++;
  }
  auto endC = chrono::steady_clock::now();
  auto diff = endC - startC;
  double clustering_time = (chrono::duration<double, milli>(diff).count()) / 1000;
  runSilhouetteForCurves(clusters, out_path, "RANDOM LLOYD PAM", clustering_time);
  return clusters;
}

/* -------------------------------------------------------------------------- */
/*                           KMEANS LSH PAM VECTORS                           */
/* -------------------------------------------------------------------------- */

vector<cluster_vectors> kmeans_lsh_pam_vector(vector_struct *vectors_array, cluster clusterInfo, unsigned int size, char const *out_path)
{
  unsigned int m, M, HASH_TABLE_SIZE = size / 8, THRESHOLD = 100, counter = 0;
  int kDivisionExp, sum = 0;
  vector<cluster_vectors> clusters, old_clusters;
  vector<vector<vector<int>>> siarrays;
  double w;
  vector<int> **hashtables;
  vector<int> lsh_matches;
  /* -------------------------------- LSH INITS -------------------------------
   */
  auto startC = chrono::steady_clock::now();
  int dimension = vectors_array[0].vectors.size();
  m = pow(mBase, mExp) - mSub;
  kDivisionExp = mExp / clusterInfo.number_of_vector_hash_functions;
  M = pow(mBase, kDivisionExp);
  // calculate w
  // // w = calculateW(size, vectors_array);
  w = 5376.42;

  /* ----------------------------------  CLUSTER INIT
   * ---------------------------------- */

  clusters = k_means_vector(vectors_array, clusterInfo.number_of_clusters, size);
  old_clusters = k_means_vector(vectors_array, clusterInfo.number_of_clusters, size);

  while (compare_vectors_clusters(clusters, old_clusters) == true && counter < THRESHOLD)
  {
    init_clusters_vectors(&clusters);
    old_clusters = copy_clusters_vector(&clusters);
    hashtables = new vector<int> *[clusterInfo.number_of_vector_hash_tables];
    /* ------------------------- LSH HASHTABLES CREATION ------------------------
   */

    for (unsigned i = 0; i < clusterInfo.number_of_vector_hash_tables; i++)
    {
      // generate Si
      siarrays.push_back(generateSi(clusterInfo.number_of_vector_hash_functions, w, dimension));
      // create the L hashtable
      hashtables[i] = creteHashTable(HASH_TABLE_SIZE, dimension, vectors_array, size, clusterInfo.number_of_vector_hash_functions, w, M, m, siarrays[i]);
    }

    /* ------------------------- LSH CLUSTER ASSIGNMENT -------------------------
   */

    for (unsigned int i = 0; i < clusters.size(); i++)
    {
      lsh_matches = nearestVectors(siarrays, dimension, clusterInfo.number_of_vector_hash_functions, w, M, m, clusterInfo.number_of_vector_hash_tables, *(clusters[i].centerOfCluster), HASH_TABLE_SIZE, hashtables, vectors_array, size, 4000);
      pushLshResultsToClusterVectors(vectors_array, lsh_matches, &clusters[i]);
    }
    lloydAssignmentClusterVectors(vectors_array, &clusters, size);
    lloydAssignmentClusterVectorsUpdate(&clusters);

    /* ------------------------------- FREE MEMORY ------------------------------
   */
    siarrays.clear();
    for (unsigned int i = 0; i < clusterInfo.number_of_vector_hash_tables; i++)
    {

      delete[] hashtables[i];
    }
    delete[] hashtables;
  }
  auto endC = chrono::steady_clock::now();
  auto diff = endC - startC;
  double clustering_time = (chrono::duration<double, milli>(diff).count()) / 1000;
  runSilhouetteForVectors(clusters, out_path, "KMEANS LSH PAM", clustering_time);
  return clusters;
}

/* -------------------------------------------------------------------------- */
/*                           RANDOM LSH PAM VECTORS                           */
/* -------------------------------------------------------------------------- */

vector<cluster_vectors> random_lsh_pam_vector(vector_struct *vectors_array, cluster clusterInfo, unsigned int size, char const *out_path)
{
  unsigned int m, M, HASH_TABLE_SIZE = size / 8, THRESHOLD = 100, counter = 0;
  int kDivisionExp, sum = 0;
  vector<cluster_vectors> clusters, old_clusters;
  vector<vector<vector<int>>> siarrays;
  double w;
  vector<int> **hashtables;
  vector<int> lsh_matches;
  /* -------------------------------- LSH INITS -------------------------------
   */
  auto startC = chrono::steady_clock::now();
  int dimension = vectors_array[0].vectors.size();
  m = pow(mBase, mExp) - mSub;
  kDivisionExp = mExp / clusterInfo.number_of_vector_hash_functions;
  M = pow(mBase, kDivisionExp);
  // calculate w
  // // w = calculateW(size, vectors_array);
  w = 5376.42;

  /* ----------------------------------  CLUSTER INIT
   * ---------------------------------- */

  clusters = random_selection_vector(vectors_array, clusterInfo.number_of_clusters, size);
  old_clusters = random_selection_vector(vectors_array, clusterInfo.number_of_clusters, size);

  while (compare_vectors_clusters(clusters, old_clusters) == true && counter < THRESHOLD)
  {
    init_clusters_vectors(&clusters);
    old_clusters = copy_clusters_vector(&clusters);
    hashtables = new vector<int> *[clusterInfo.number_of_vector_hash_tables];
    /* ------------------------- LSH HASHTABLES CREATION ------------------------
   */

    for (unsigned i = 0; i < clusterInfo.number_of_vector_hash_tables; i++)
    {
      // generate Si
      siarrays.push_back(generateSi(clusterInfo.number_of_vector_hash_functions, w, dimension));
      // create the L hashtable
      hashtables[i] = creteHashTable(HASH_TABLE_SIZE, dimension, vectors_array, size, clusterInfo.number_of_vector_hash_functions, w, M, m, siarrays[i]);
    }

    /* ------------------------- LSH CLUSTER ASSIGNMENT -------------------------
   */

    for (unsigned int i = 0; i < clusters.size(); i++)
    {
      lsh_matches = nearestVectors(siarrays, dimension, clusterInfo.number_of_vector_hash_functions, w, M, m, clusterInfo.number_of_vector_hash_tables, *(clusters[i].centerOfCluster), HASH_TABLE_SIZE, hashtables, vectors_array, size, 4000);
      pushLshResultsToClusterVectors(vectors_array, lsh_matches, &clusters[i]);
    }
    lloydAssignmentClusterVectors(vectors_array, &clusters, size);
    lloydAssignmentClusterVectorsUpdate(&clusters);

    /* ------------------------------- FREE MEMORY ------------------------------
   */
    siarrays.clear();
    for (unsigned int i = 0; i < clusterInfo.number_of_vector_hash_tables; i++)
    {

      delete[] hashtables[i];
    }
    delete[] hashtables;
  }
  auto endC = chrono::steady_clock::now();
  auto diff = endC - startC;
  double clustering_time = (chrono::duration<double, milli>(diff).count()) / 1000;
  runSilhouetteForVectors(clusters, out_path, "KMEANS LSH PAM", clustering_time);
  return clusters;
}

/* -------------------------------------------------------------------------- */
/*                           RANDOM LSH PAM CURVES                            */
/* -------------------------------------------------------------------------- */

vector<cluster_curves> random_lsh_pam_curve(vector<curve> curves_array, cluster clusterInfo, unsigned int size, char const *out_path)
{
  unsigned int m, M, HASH_TABLE_SIZE = size / 8, THRESHOLD = 100, counter = 0;
  int kDivisionExp, sum = 0;
  vector<cluster_curves> clusters, old_clusters;
  vector<vector<vector<int>>> siarrays;
  double w;
  vector<int> **hashtables;
  vector<int> lsh_matches;
  /* -------------------------------- LSH INITS -------------------------------
   */
  auto startC = chrono::steady_clock::now();
  int dimension = curves_array[0].vectorPoins.size();
  m = pow(mBase, mExp) - mSub;
  kDivisionExp = mExp / clusterInfo.number_of_vector_hash_functions;
  M = pow(mBase, kDivisionExp);
  // calculate w
  // // w = calculateW(size, vectors_array);
  w = 5376.42;

  /* ----------------------------------  CLUSTER INIT   * ---------------------------------- */

  clusters = random_selection_curves(&curves_array, clusterInfo.number_of_clusters, size);
  old_clusters = random_selection_curves(&curves_array, clusterInfo.number_of_clusters, size);

  // while (compare_curves_clusters(clusters, old_clusters) == true && counter < THRESHOLD)
  // {
  //   init_clusters_vectors(&clusters);
  //   old_clusters = copy_clusters_vector(&clusters);
  //   hashtables = new vector<int> *[clusterInfo.number_of_vector_hash_tables];
  //   /* ------------------------- LSH HASHTABLES CREATION ------------------------
  //  */

  //   for (unsigned i = 0; i < clusterInfo.number_of_vector_hash_tables; i++)
  //   {
  //     // generate Si
  //     siarrays.push_back(generateSi(clusterInfo.number_of_vector_hash_functions, w, dimension));
  //     // create the L hashtable
  //     hashtables[i] = creteHashTable(HASH_TABLE_SIZE, dimension, vectors_array, size, clusterInfo.number_of_vector_hash_functions, w, M, m, siarrays[i]);
  //   }

  //   /* ------------------------- LSH CLUSTER ASSIGNMENT -------------------------
  //  */

  //   for (unsigned int i = 0; i < clusters.size(); i++)
  //   {
  //     lsh_matches = nearestVectors(siarrays, dimension, clusterInfo.number_of_vector_hash_functions, w, M, m, clusterInfo.number_of_vector_hash_tables, *(clusters[i].centerOfCluster), HASH_TABLE_SIZE, hashtables, vectors_array, size, 4000);
  //     pushLshResultsToClusterVectors(vectors_array, lsh_matches, &clusters[i]);
  //   }
  //   lloydAssignmentClusterVectors(vectors_array, &clusters, size);
  //   lloydAssignmentClusterVectorsUpdate(&clusters);

  //   /* ------------------------------- FREE MEMORY ------------------------------
  //  */
  //   siarrays.clear();
  //   for (unsigned int i = 0; i < clusterInfo.number_of_vector_hash_tables; i++)
  //   {

  //     delete[] hashtables[i];
  //   }
  //   delete[] hashtables;
  // }
  // auto endC = chrono::steady_clock::now();
  // auto diff = endC - startC;
  // double clustering_time = (chrono::duration<double, milli>(diff).count()) / 1000;
  // runSilhouetteForVectors(clusters, out_path, "KMEANS LSH PAM", clustering_time);
  // return clusters;
}

/* -------------------------------------------------------------------------- */
/*                                   HELPERS                                  */
/* -------------------------------------------------------------------------- */

vector<cluster_vectors>
copy_clusters_vector(vector<cluster_vectors> *clusters)
{
  vector<cluster_vectors> new_clusters;
  for (unsigned int i = 0; i < clusters->size(); i++)
  {
    new_clusters.push_back(clusters->at(i));
  }
  return new_clusters;
}

bool compare_vectors_clusters(vector<cluster_vectors> current, vector<cluster_vectors> old)
{
  bool flag = 0;
  for (unsigned int i = 0; i < current.size(); i++)
  {
    if (current[i].centerOfCluster->id != old[i].centerOfCluster->id)
    {
      flag = 1;
      break;
    }
  }

  return flag;
}

vector<cluster_curves> copy_clusters_curves(vector<cluster_curves> *clusters)
{
  vector<cluster_curves> new_clusters;
  for (unsigned int i = 0; i < clusters->size(); i++)
  {
    new_clusters.push_back(clusters->at(i));
  }
  return new_clusters;
}

bool compare_curves_clusters(vector<cluster_curves> current,
                             vector<cluster_curves> old)
{
  bool flag = 0;
  for (unsigned int i = 0; i < current.size(); i++)
  {
    if (current[i].centerOfCluster->id != old[i].centerOfCluster->id)
    {
      flag = 1;
      break;
    }
  }
  return flag;
}

void pushLshResultsToClusterVectors(vector_struct *vectors_array, vector<int> results, cluster_vectors *cluster)
{
  cout << "size: " << results.size() << endl;
  for (unsigned int i = 0; i < results.size(); i++)
  {
    if (vectors_array[results[i]].in_cluster == 0)
    {
      cluster->cluster_vectors.push_back(&(vectors_array[results[i]]));
      vectors_array[results[i]].in_cluster = 1;
    }
  }
}

void pushLshResultsToClusterCurves(vector<curve> *curves, vector<int> results, cluster_curves *cluster)
{
  for (unsigned int i = 0; i < results.size(); i++)
  {
    cluster->cluster_curves.push_back(&curves->at(results[i]));
  }
}

void runSilhouetteForVectors(vector<cluster_vectors> clusters, char const *outfile, char const *case_name, double clustering_time)
{
  vector<vector<Silhouette>> a_b_results;
  vector<double> s_results;
  double s_average = 0;
  ofstream file;
  file.open(outfile);
  file << "Algorithm:  " << case_name << endl;
  for (unsigned int i = 0; i < clusters.size(); i++)
  {

    file << "CLUSTER-" << i << "    "
         << "{ size: " << clusters[i].cluster_vectors.size() << ", centroid: " << clusters[i].centerOfCluster->id << "}" << endl;

    a_b_results.push_back(calculate_a_b_vectors(clusters, clusters[i], i));
    s_results.push_back(calculateSVectors(a_b_results[i]));
  }
  file << "clustering_time: " << clustering_time << endl;
  file << "Silhouette:[";
  for (unsigned int i = 0; i < s_results.size(); i++)
  {
    s_average += s_results[i];
    file << s_results[i] << ", ";
  }
  s_average = s_average / s_results.size();
  file << s_average << "]" << endl;
  file.close();
}

void runSilhouetteForCurves(vector<cluster_curves> clusters, char const *outfile, char const *case_name, double clustering_time)
{
  vector<vector<Silhouette>> a_b_results;
  vector<double> s_results;
  double s_average = 0;
  ofstream file;
  file.open(outfile);
  file << "Algorithm:  " << case_name << endl;
  for (unsigned int i = 0; i < clusters.size(); i++)
  {

    file << "CLUSTER-" << i << "    "
         << "{ size: " << clusters[i].cluster_curves.size() << ", centroid: " << clusters[i].centerOfCluster->id << "}" << endl;

    a_b_results.push_back(calculate_a_b_curves(clusters, clusters[i], i));
    s_results.push_back(calculateSVectors(a_b_results[i]));
  }
  file << "clustering_time: " << clustering_time << endl;
  file << "Silhouette:[";
  for (unsigned int i = 0; i < s_results.size(); i++)
  {
    s_average += s_results[i];
    file << s_results[i] << ", ";
  }
  s_average = s_average / s_results.size();
  file << s_average << "]" << endl;
  file.close();
}

vector<Silhouette> calculate_a_b_vectors(vector<cluster_vectors> clusters, cluster_vectors current_cluster, unsigned int current_cluster_index)
{
  vector<Silhouette> silhouette;
  Silhouette current_a_b;
  double max_a = 0, max_b = 0;
  unsigned int closest_cluster_index;
  for (unsigned int i = 0; i < current_cluster.cluster_vectors.size(); i++)
  {
    current_a_b.a = calculateAverageSilhouetteVectors(current_cluster, *(current_cluster.cluster_vectors[i]));
    closest_cluster_index = calcluateClosestClusterIndexVectors(clusters, *(current_cluster.cluster_vectors[i]), current_cluster_index);
    current_a_b.b = calculateAverageSilhouetteVectors(clusters[closest_cluster_index], *(current_cluster.cluster_vectors[i]));
    if (current_a_b.a > max_a)
      max_a = current_a_b.a;

    if (current_a_b.b > max_b)
      max_b = current_a_b.b;

    silhouette.push_back(current_a_b);
  }
  //push max a_b at the end of the vector
  current_a_b.a = max_a;
  current_a_b.b = max_b;
  silhouette.push_back(current_a_b);
  return silhouette;
}

vector<Silhouette> calculate_a_b_curves(vector<cluster_curves> clusters, cluster_curves current_cluster, unsigned int current_cluster_index)
{
  vector<Silhouette> silhouette;
  Silhouette current_a_b;
  double max_a = 0, max_b = 0;
  unsigned int closest_cluster_index;
  for (unsigned int i = 0; i < current_cluster.cluster_curves.size(); i++)
  {
    current_a_b.a = calculateAverageSilhouetteCurves(current_cluster, *(current_cluster.cluster_curves[i]));
    closest_cluster_index = calcluateClosestClusterIndexCurves(clusters, *(current_cluster.cluster_curves[i]), current_cluster_index);
    current_a_b.b = calculateAverageSilhouetteCurves(clusters[closest_cluster_index], *(current_cluster.cluster_curves[i]));
    if (current_a_b.a > max_a)
      max_a = current_a_b.a;

    if (current_a_b.b > max_b)
      max_b = current_a_b.b;

    silhouette.push_back(current_a_b);
  }
  //push max a_b at the end of the vector
  current_a_b.a = max_a;
  current_a_b.b = max_b;
  silhouette.push_back(current_a_b);
  return silhouette;
}

double calculateAverageSilhouetteVectors(cluster_vectors cluster, vector_struct vector)
{
  double average = 0, sum = 0;
  if (cluster.cluster_vectors.size() - 1 <= 0)
    return 0;
  for (unsigned int i = 0; i < cluster.cluster_vectors.size(); i++)
  {
    sum += manhattanDistance(vector.vectors, cluster.cluster_vectors[i]->vectors);
  }
  return sum / (cluster.cluster_vectors.size() - 1);
}

double calculateAverageSilhouetteCurves(cluster_curves cluster, curve curve)
{
  double average = 0, sum = 0;
  if (cluster.cluster_curves.size() - 1 <= 0)
    return 0;
  for (unsigned int i = 0; i < cluster.cluster_curves.size(); i++)
  {
    sum += dtw(curve, (*cluster.cluster_curves[i]));
  }
  return sum / (cluster.cluster_curves.size() - 1);
}

unsigned int calcluateClosestClusterIndexVectors(vector<cluster_vectors> clusters, vector_struct vector, unsigned int current_cluster_index)
{
  unsigned int min_index;
  double min_distance = 0, distance = 0;
  for (unsigned int i = 0; i < clusters.size(); i++)
  {
    if (current_cluster_index == 0)
    {
      if (i != current_cluster_index)
      {
        if (i == current_cluster_index + 1)
        {
          min_distance = manhattanDistance(vector.vectors, clusters[i].centerOfCluster->vectors);
          min_index = i;
        }
        else
        {
          if (manhattanDistance(vector.vectors, clusters[i].centerOfCluster->vectors) < min_distance)
          {

            min_distance = manhattanDistance(vector.vectors, clusters[i].centerOfCluster->vectors);
            min_index = i;
          }
        }
      }
    }
    else
    {
      if (i == 0)
      {
        min_distance = manhattanDistance(vector.vectors, clusters[i].centerOfCluster->vectors);
        min_index = i;
      }
      else
      {
        if (i == current_cluster_index + 1)
        {
          if (manhattanDistance(vector.vectors, clusters[i].centerOfCluster->vectors) < min_distance)
          {

            min_distance = manhattanDistance(vector.vectors, clusters[i].centerOfCluster->vectors);
            min_index = i;
          }
        }
      }
    }
  }
  return min_index;
}

unsigned int calcluateClosestClusterIndexCurves(vector<cluster_curves> clusters, curve curve, unsigned int current_cluster_index)
{
  unsigned int min_index;
  double min_distance = 0, distance = 0;
  for (unsigned int i = 0; i < clusters.size(); i++)
  {
    if (current_cluster_index == 0)
    {
      if (i != current_cluster_index)
      {
        if (i == current_cluster_index + 1)
        {
          min_distance = dtw(curve, (*clusters[i].centerOfCluster));
          min_index = i;
        }
        else
        {
          if (distance = dtw(curve, *clusters[i].centerOfCluster) < min_distance)
          {

            min_distance = distance;
            min_index = i;
          }
        }
      }
    }
    else
    {
      if (i == 0)
      {
        min_distance = dtw(curve, *(clusters[i].centerOfCluster));
        min_index = i;
      }
      else
      {
        if (i == current_cluster_index + 1)
        {
          if (distance = dtw(curve, *(clusters[i].centerOfCluster)) < min_distance)
          {

            min_distance = distance;
            min_index = i;
          }
        }
      }
    }
  }
  return min_index;
}

double calculateSVectors(vector<Silhouette> a_b_vector)
{
  double max_a = a_b_vector[a_b_vector.size() - 1].a;
  double max_b = a_b_vector[a_b_vector.size() - 1].b;
  double s = 0, sum = 0;
  if (max_a == 0 || max_b == 0)
    return 0;
  for (unsigned int i = 0; i < (a_b_vector.size() - 1); i++)
  {
    if (a_b_vector[i].b > a_b_vector[i].a)
    {
      sum += 1 - a_b_vector[i].a / a_b_vector[i].b;
    }
    else if (a_b_vector[i].b < a_b_vector[i].a)
    {
      sum += a_b_vector[i].b / a_b_vector[i].a - 1;
    }
  }
  s = sum / (a_b_vector.size() - 1);
  return s;
}

void init_clusters_vectors(vector<cluster_vectors> *clusters)
{

  for (unsigned int i = 0; i < clusters->size(); i++)
  {
    for (unsigned int j = 0; j < clusters->at(i).cluster_vectors.size(); j++)
    {
      clusters->at(i).cluster_vectors[j]->in_cluster = false;
    }
    clusters->at(i).cluster_vectors.clear();
  }
}
void init_clusters_curves(vector<cluster_curves> *clusters)
{

  for (unsigned int i = 0; i < clusters->size(); i++)
  {
    for (unsigned int j = 0; j < clusters->at(i).cluster_curves.size(); j++)
    {
      clusters->at(i).cluster_curves[j]->in_cluster = false;
    }
    clusters->at(i).cluster_curves.clear();
  }
}
