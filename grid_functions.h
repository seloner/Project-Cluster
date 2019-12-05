#ifndef grid_functions_H_
#define grid_functions_H_
#include "curves.h"
#include "vector.h"
#include <string>

typedef struct t
{
    double x;
    double y;
} t;
typedef struct grid_point
{
    double x;
    double y;

} grid_point;

typedef struct grid_vectors
{
    vector<vector<double>> vectors;

} grid_vectors;
t generate_t();

point grid_match(t t_random, double delta, point point);
grid_vectors curve_to_grid(vector<curve> curves, int number_of_curves, t t_random, double delta);
int find_match(vector<point> points, point match);
int calculate_max_dimension(grid_vectors grid_vectors);
void padding(grid_vectors *grid_vectors, double padding_value, int dimension);
void check_dimensions(grid_vectors grid_vectors);
void grid_vectors_to_vectors(grid_vectors grid_vectors, vector_struct *vectors_array);

#endif