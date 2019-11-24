// void lloydAssignmentClusterCurvesUpdate(vector<curve> curves, vector<clusterarraycurves> &lloydAssignmentClusterArray, unsigned int threshold = 5);
// void lloydAssignmentClusterCurvesUpdate(vector<curve> curves, vector<cluster_curves> &lloydAssignmentClusterArray, unsigned int threshold)
// {
//     double sum = 0, min_distance = 0;
//     curve *new_centre;
//     unsigned int counter = 0;
//     while (counter <= threshold)
//     {
//         counter++;
//         for (unsigned j = 0; j < lloydAssignmentClusterArray.size(); j++)
//         {
//             for (unsigned int i = 0; i < lloydAssignmentClusterArray[j].cluster_curves.size(); i++)
//             {
//                 // cout << lloydAssignmentClusterArray[j].nodes[k].machingCurve->id << endl;
//                 for (unsigned int k = 0; k < lloydAssignmentClusterArray[j].cluster_curves.size(); k++)
//                 {
//                     sum += dtw(*(lloydAssignmentClusterArray[j].cluster_curves[i]), *(lloydAssignmentClusterArray[j].cluster_curves[k]));
//                 }
//                 if (i == 0)
//                 {
//                     min_distance = sum;
//                     new_centre = lloydAssignmentClusterArray[j].cluster_curves[i];
//                 }
//                 else
//                 {
//                     if (sum < min_distance)
//                     {
//                         min_distance = sum;
//                         new_centre = lloydAssignmentClusterArray[j].cluster_curves[i];
//                     }
//                 }
//                 sum = 0;
//             }
//             lloydAssignmentClusterArray[j].centerOfCluster = new_centre;
//             cout << "Cluster " << j << "   centre: " << new_centre->id << endl;
//         }
//     }
// }