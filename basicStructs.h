#ifndef BASICSTRUCTS_H_
#define BASICSTRUCTS_H_

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
	bool intoCluster;
    vector<point> vectorPoins;
} curve;

#endif