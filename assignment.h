#ifndef assignment_H_
#define assignment_H_
#include <iostream>
#include <vector>
#include "clusterStructs.h"
#include "curves.h"
#include <math.h>
#include "dtw.h"
#include "metrics.h"
#include "vector.h"

using namespace std;

void lloydAssignmentClusterCurves(unsigned int size, vector<cluster_curves> &curves_clusters);
void lloydAssignmentClusterVectors(vector_struct *vectors_array, vector<cluster_vectors> *clusters, unsigned int size);
void test(vector<curve> curves);
#endif
