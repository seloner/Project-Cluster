#include "assignment.h"

void lloydAssignmentClusterCurvesUpdate(vector<curve> curves, vector<clusterarraycurves> &lloydAssignmentClusterArray)
{
    double sum = 0, min_distance = 0;
    curve *new_centre;
    for (unsigned j = 0; j < lloydAssignmentClusterArray.size(); j++)
    {
        cout << "j   " << j << endl;
        for (unsigned int i = 0; i < lloydAssignmentClusterArray[j].nodes.size(); i++)
        {
            // cout << lloydAssignmentClusterArray[j].nodes[k].machingCurve->id << endl;
            for (unsigned int k = 0; k < lloydAssignmentClusterArray[j].nodes.size(); k++)
            {
                sum += dtw(*(lloydAssignmentClusterArray[j].nodes[i].machingCurve), *(lloydAssignmentClusterArray[j].nodes[k].machingCurve));
            }
            if (i == 0)
            {
                min_distance = sum;
                new_centre = lloydAssignmentClusterArray[j].nodes[i].machingCurve;
            }
            else
            {
                if (sum < min_distance)
                {
                    min_distance = sum;
                    new_centre = lloydAssignmentClusterArray[j].nodes[i].machingCurve;
                }
            }
            sum = 0;
        }
        lloydAssignmentClusterArray[j].centerOfCluster.machingCurve = new_centre;
    }
}
void lloydAssignmentClusterCurvesFunction(vector<curve> curves, vector<curve> randomSelectionForCurves, vector<clusterarraycurves> &lloydAssignmentClusterArray)
{
    int insideElements = 0;
    clusterarraycurves clusterarraycurve;
    for (vector<curve>::iterator it = randomSelectionForCurves.begin(); it != randomSelectionForCurves.end(); ++it)
    {
        //parnoume ta kentra twn curves apo to randomSelection kai tis dinoume stin nea domi prokeimenou na efarmosoyme se autes ton lloyd
        clusterarraycurve.centerOfCluster.machingCurve = &randomSelectionForCurves[insideElements];
        lloydAssignmentClusterArray.push_back(clusterarraycurve);

        //test assignment
        //cout << "Assign: " << lloydAssignmentClusterArray[insideElements].centerOfCluster.machingCurve->id << " to lloyd vector as first try of centers" << endl;

        insideElements++;
    }
    insideElements = 0;
    //ta prwta kentra do8ikan ston lloyd
    int min_distance;
    int candidateCluster;
    clusternodecurves nodeCurveToPass;
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
                nodeCurveToPass.machingCurve = &curves[kampilesLoop];
            }
            else
            {
                //if we have a new min update
                if (distance < min_distance && distance != 0)
                {
                    min_distance = distance;
                    candidateCluster = kentraLoop;
                    nodeCurveToPass.machingCurve = &curves[kampilesLoop];
                }
            }
        }
        //TODO (maybe not ?) allagi tou intoCLuster
        lloydAssignmentClusterArray[candidateCluster].nodes.push_back(nodeCurveToPass);
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
