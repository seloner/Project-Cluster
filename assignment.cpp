#include "assignment.h"

void lloydAssignmentCurves(vector<curve> randomSelectionForCurves,  vector<clusterarraycurves> &lloydAssignmentCurvesArray)
{
    int insideElements = 0;
    clusterarraycurves clusterarraycurve;
    for (vector<curve>::iterator it = randomSelectionForCurves.begin(); it != randomSelectionForCurves.end(); ++it)
    {
        //parnoume ta kentra twn curves apo to randomSelection kai tis dinoume stin nea domi prokeimenou na efarmosoyme se autes ton lloyd
        clusterarraycurve.centerOfCluster.machingCurve = &randomSelectionForCurves[insideElements];
        lloydAssignmentCurvesArray.push_back(clusterarraycurve);
        
            //test assignment
            cout << "Assign: "<< lloydAssignmentCurvesArray[insideElements].centerOfCluster.machingCurve->id <<" to lloyd vector as first try of centers" <<endl;

        insideElements++;
    }
    insideElements = 0;
    //ta prwta kentra do8ikan ston lloyd
}
