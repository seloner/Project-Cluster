#ifndef update_H_
#define update_H_
#include <iostream>
#include <vector>
#include "curves.h"
#include "clusterStructs.h"
#include "dtw.h"
#include "metrics.h"
using namespace std;

void lloydAssignmentClusterCurvesUpdate(vector<cluster_curves> *lloydAssignmentClusterArray);
void lloydAssignmentClusterVectorsUpdate(vector<cluster_vectors> *lloydAssignmentClusterArray);

#endif