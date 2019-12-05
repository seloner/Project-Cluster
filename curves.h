#ifndef curves_H_
#define curves_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;

typedef struct Point
{
    double x;
    double y;
} point;

typedef struct Curve
{
    int id;
    int dimensions;
    bool in_cluster;
    vector<point> vectorPoins;
} curve;
// void calculateCurveDimensions(char *path, vector<curve> &curves, int number_of_lines);
//void fillVectorWithCurves(char *path, vector<curve> &curves, int number_of_lines);
string convertToString(char *array, int size);
void printCurves(vector<curve> curves, int number_of_lines);
void bruteForceCurves(int d, int size, char *input_file_path, char *query_file_path, char *output_file_path, vector<point> **array);
void calculateCurveDimensions(char *path, vector<curve> &curves, int number_of_lines);
void printCurves(vector<curve> curves, int number_of_lines);
void fillVectorWithCurves(char *path, vector<curve> &curves, int number_of_lines);
#endif