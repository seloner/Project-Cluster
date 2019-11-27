#ifndef update_H_
#define update_H_
#include <iostream>
#include <vector>
#include "curves.h"
#include "clusterStructs.h"
#include "dtw.h"
using namespace std;

void lloydAssignmentClusterCurvesUpdate(vector<curve> *curves, vector<cluster_curves> *lloydAssignmentClusterArray);

#endif