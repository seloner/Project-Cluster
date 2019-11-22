#include "assignment.h"

void lloydAssignmentClusterArray(vector<curve> curves, vector<curve> randomSelectionForCurves, vector<clusterarraycurves> &lloydAssignmentClusterArray)
{
    int insideElements = 0;
    clusterarraycurves clusterarraycurve;
    for (vector<curve>::iterator it = randomSelectionForCurves.begin(); it != randomSelectionForCurves.end(); ++it)
    {
        //parnoume ta kentra twn curves apo to randomSelection kai tis dinoume stin nea domi prokeimenou na efarmosoyme se autes ton lloyd
        clusterarraycurve.centerOfCluster.machingCurve = &randomSelectionForCurves[insideElements];
        lloydAssignmentClusterArray.push_back(clusterarraycurve);

        //test assignment
        cout << "Assign: " << lloydAssignmentClusterArray[insideElements].centerOfCluster.machingCurve->id << " to lloyd vector as first try of centers" << endl;

        insideElements++;
    }
    insideElements = 0;
    //ta prwta kentra do8ikan ston lloyd
}
