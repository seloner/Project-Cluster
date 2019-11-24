#include "assignment.h"

void lloydAssignmentClusterCurvesFunction(vector<curve> curves, vector<curve> randomSelectionForCurves, vector<cluster_curves> &lloydAssignmentClusterArray)
{
    int insideElements = 0;
    curve *clusterarraycurve;
    //ta prwta kentra do8ikan ston lloyd
    int min_distance;
    int candidateCluster;
    curve *nodeCurveToPass;
    //pame na ftiaxoume ta kentra
    for (int kampilesLoop = 0; kampilesLoop < curves.size(); kampilesLoop++)
    {
        for (int kentraLoop = 0; kentraLoop < randomSelectionForCurves.size(); kentraLoop++)
        {
            int distance = dtw(randomSelectionForCurves[kentraLoop], curves[kampilesLoop]);
            if (kentraLoop == 0)
            {
                //exoume: mikroteri apostasi, to ipopsifio cluster pou 8a proste8ei, kai h kampili pou 8a proste8ei me deikth ston teliko cluster
                min_distance = distance;
                candidateCluster = kentraLoop;
                nodeCurveToPass = &curves[kampilesLoop];
            }
            else
            {
                //if we have a new min update
                if (distance < min_distance && distance != 0)
                {
                    min_distance = distance;
                    candidateCluster = kentraLoop;
                    nodeCurveToPass = &curves[kampilesLoop];
                }
            }
        }
        //TODO (maybe not ?) allagi tou intoCLuster
        lloydAssignmentClusterArray[candidateCluster].cluster_curves.push_back(nodeCurveToPass);
    }

    //test results
    //cout << endl
    //<< "Clusters from phase 1:" << endl;
    // for (int i = 0; i < lloydAssignmentClusterArray.size(); i++)
    // {
    //     // cout << "Cluster: " << i << endl;
    //     // cout << "Center (curve id): " << lloydAssignmentClusterArray[i].centerOfCluster.machingCurve->id << endl;
    //     // cout << "Curves Inside (ids)>>" << endl;
    //     // for (int j = 0; j < lloydAssignmentClusterArray[i].nodes.size(); j++)
    //     // {
    //     //     cout << lloydAssignmentClusterArray[i].nodes[j].machingCurve->id << ", ";
    //     // }
    //     // cout << endl;
    // }
}
