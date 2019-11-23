#ifndef assignment_H_
#define assignment_H_
using namespace std;
#include <iostream>
#include <vector>
#include "clusterStructs.h"
#include "curves.h"
#include <math.h>
#include "dtw.h"

void lloydAssignmentClusterArray(vector<curve> curves, vector<curve> randomSelectionForCurves, vector<clusterarraycurves> &lloydAssignmentCurvesArray);

#endif