#include "assignment.h"

void lloydAssignmentClusterCurvesFunction(vector<curve> curves, vector<cluster_curves> &curves_clusters)
{
    //int insideElements = 0;
    //curve *clusterarraycurve;
    //ta prwta kentra do8ikan ston lloyd
    int distance;
    int min_distance;
    int candidateCluster = 0;
    curve *nodeCurveToPass;
    //pame na ftiaxoume ta kentra
    for (int kampilesLoop = 0; kampilesLoop < curves.size(); kampilesLoop++)
    {
        //cout << "VIMA 1"<<endl;
        for (int kentraLoop = 0; kentraLoop < curves_clusters.size(); kentraLoop++)
        {
        //cout << "VIMA 2"<<endl;

            distance = dtw(*(curves_clusters[kentraLoop].centerOfCluster), curves[kampilesLoop]);
        //cout << "VIMA 2a"<<endl;
            if (kentraLoop == 0)
            {
        //cout << "VIMA 3"<<endl;
                //exoume: mikroteri apostasi, to ipopsifio cluster pou 8a proste8ei, kai h kampili pou 8a proste8ei me deikth ston teliko cluster
                min_distance = distance;
                candidateCluster = kentraLoop;
                nodeCurveToPass = &curves[kampilesLoop];
            }
            else
            {
        //cout << "VIMA 4"<<endl;
                //if we have a new min update
                if (distance < min_distance)
                {
        //cout << "VIMA 5"<<endl;
                    min_distance = distance;
                    candidateCluster = kentraLoop;
                    nodeCurveToPass = &curves[kampilesLoop];
                }
            }
        //cout << "VIMA 6"<<endl;
        }
        //cout << "VIMA 7"<<endl;
        //TODO (maybe not ?) allagi tou intoCLuster
        curves_clusters[candidateCluster].cluster_curves.push_back(nodeCurveToPass);
                //cout << "VIMA 8"<<endl;

    }

            //test results
            // cout << endl<< "############### from function ##############" << endl;
            // cout << endl<< "Clusters from phase 1:" << endl;
            // for (int i = 0; i < curves_clusters.size() ; i++)
            // {
            //     cout << "Cluster: " << i << endl;
            //     cout << "Center (curve id): " << curves_clusters[i].centerOfCluster->id << endl;
            //     cout << "Curves Inside (ids)>>" << endl;
            //     for (int j = 0; j < curves_clusters[i].cluster_curves.size(); j++)
            //     {
            //         cout << curves_clusters[i].cluster_curves[j]->id << ", ";
            //         if(curves_clusters[i].cluster_curves[j]->id == 0)
            //         {
            //             cout<< "Cluster: "<<i<<endl;
            //             cout<< "Cluster Address: "<< &curves_clusters[i] <<endl;
            //             cout<< "cluster_curves Address: "<< &curves_clusters[i].cluster_curves <<endl;
            //             cout<< "Curve Address: "<< curves_clusters[i].cluster_curves[j] <<endl;
            //             cout << "Curve id: " << curves_clusters[i].cluster_curves[j]->id << endl;
            //             cout << "Curve dimensions: " << curves_clusters[i].cluster_curves[j]->dimensions << endl;
            //         }
            //     }

            //     cout << endl;
            // }
}
