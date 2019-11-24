#ifndef assignment_H_
#define assignment_H_
using namespace std;
#include <iostream>
#include <vector>
#include "clusterStructs.h"
#include "curves.h"
#include <math.h>
#include "dtw.h"
void lloydAssignmentClusterCurvesFunction(vector<curve> curves, vector<cluster_curves> &curves_clusters);
void lloydAssignmentClusterPointsFunction();

#endif