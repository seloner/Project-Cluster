#ifndef assignment_H_
#define assignment_H_
#include <iostream>
#include <vector>
#include "clusterStructs.h"
#include "curves.h"
#include <math.h>
#include "dtw.h"

using namespace std;

void lloydAssignmentClusterCurvesFunction(vector<curve> curves, vector<cluster_curves> curves_clusters);
void lloydAssignmentClusterPointsFunction();
void lloydAssignmentClusterCurves(vector<cluster_curves> *clusters, vector<curve> *curves);

#endif
