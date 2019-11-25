#include "assignment.h"

void lloydAssignmentClusterCurvesFunction(vector<curve> curves, vector<cluster_curves> &curves_clusters)
{
        cout<<"[check 2] curves_clusters[0].centerOfCluster->id<: "<<curves_clusters[0].centerOfCluster->id<<endl;
    //ta prwta kentra do8ikan ston lloyd
    double distance;
    int min_distance;
    unsigned int candidateCluster = 0;
    curve *nodeCurveToPass;
    nodeCurveToPass = NULL;
    //pame na ftiaxoume ta kentra
    for (unsigned int kampilesLoop = 0; kampilesLoop < curves.size(); kampilesLoop++)
    {
        for (unsigned int kentraLoop = 0; kentraLoop < curves_clusters.size(); kentraLoop++)
        {
            distance = dtw(*(curves_clusters[kentraLoop].centerOfCluster), curves[kampilesLoop]);
            if (kentraLoop == 0)
            {
                //exoume: mikroteri apostasi, to ipopsifio cluster pou 8a proste8ei, kai h kampili pou 8a proste8ei me deikth ston teliko cluster
                min_distance = distance;
                candidateCluster = kentraLoop;
            }
            else
            {
                //if we have a new min update
                if (distance < min_distance)
                {
                    min_distance = distance;
                    candidateCluster = kentraLoop;
                }
            }
        }
        nodeCurveToPass = &curves[kampilesLoop];

        //TODO (maybe not ?) allagi tou intoCLuster
        curves_clusters[candidateCluster].cluster_curves.push_back(nodeCurveToPass);
    }
        cout<<"[check 3] curves_clusters[0].centerOfCluster->id<: "<<curves_clusters[0].centerOfCluster->id<<endl;
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
