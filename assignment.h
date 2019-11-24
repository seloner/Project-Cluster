#ifndef assignment_H_
#define assignment_H_
using namespace std;
#include <iostream>
#include <vector>
#include "clusterStructs.h"
#include "curves.h"
#include <math.h>
#include "dtw.h"
void lloydAssignmentClusterCurvesUpdate(vector<curve> curves, vector<clusterarraycurves> &lloydAssignmentClusterArray, unsigned int threshold = 5);
void lloydAssignmentClusterCurvesFunction(vector<curve> curves, vector<curve> randomSelectionForCurves, vector<clusterarraycurves> &lloydAssignmentCurvesArray);
void lloydAssignmentClusterPointsFunction();

#endif