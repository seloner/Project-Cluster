#include "grid_functions.h"
#include <random>
#include <iostream>
#include <vector>

using namespace std;
t generate_t()
{
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    t t_result;
    normal_distribution<double> distribution(1, 0.005);
    t_result.x = distribution(generator);
    t_result.y = distribution(generator);
    return t_result;
}

point grid_match(t t_random, double delta, point point_input)
{
    point result;
    double i = floor(((double)point_input.x - t_random.x) / delta);
    double j = floor(((double)point_input.y - t_random.y) / delta);
    result.x = i * delta + t_random.x;
    result.y = j * delta + t_random.y;
    return result;
}

grid_vectors curve_to_grid(vector<curve> curves, int number_of_curves, t t_random, double delta)
{
    grid_vectors grid_vectors;
    point match;
    int flag;
    unsigned int j = 0, i = 0;
    vector<point> points;
    vector<point>::iterator result;
    vector<double> vector;
    for (i = 0; i < number_of_curves; i++)
    {
        for (j = 0; j < curves[i].vectorPoins.size(); j++)
        {
            //find a match to grid
            match = grid_match(t_random, delta, curves[i].vectorPoins[j]);
            //check if match exists already
            flag = find_match(points, match);
            //if it doenst exist then push it to the vector
            if (flag == 0)
            {
                points.push_back(match);
            }
        }
        //create the vector
        vector.push_back(curves[i].id);
        for (j = 0; j < points.size(); j++)
        {

            vector.push_back(points[j].x);
            vector.push_back(points[j].y);
        }
        grid_vectors.vectors.push_back(vector);
        vector.clear();
        points.clear();
    }
    return grid_vectors;
}

int find_match(vector<point> points, point match)
{
    unsigned int i = 0;

    for (i = 0; i < points.size(); i++)
    {
        if (points[i].x == match.x && points[i].y == match.y)
        {

            return 1;
        }
    }
    return 0;
}

int calculate_max_dimension(grid_vectors grid_vectors)
{
    unsigned int i = 0;
    int max_dimension = 0;
    for (i = 0; i < grid_vectors.vectors.size(); i++)
    {
        if (grid_vectors.vectors[i].size() > max_dimension)
            max_dimension = grid_vectors.vectors[i].size();
    }
    return max_dimension;
}

void padding(grid_vectors *grid_vectors, double padding_value, int dimension)
{
    unsigned int i;
    for (i = 0; i < grid_vectors->vectors.size(); i++)
    {
        while (grid_vectors->vectors[i].size() < dimension)
        {
            grid_vectors->vectors[i].push_back(padding_value);
        }
    }
}

void check_dimensions(grid_vectors grid_vectors)
{
    unsigned int i;
    for (i = 0; i < grid_vectors.vectors.size(); i++)
    {
        cout << "i:" << i << "   " << grid_vectors.vectors[i].size() << endl;
    }
}

void grid_vectors_to_vectors(grid_vectors grid_vectors, vector_struct *vectors_array)
{

    for (unsigned int i = 0; i < grid_vectors.vectors.size(); i++)
    {
        for (unsigned int j = 0; j < grid_vectors.vectors[i].size(); j++)
        {
            if (j == 0)
            {
                auto string_id = to_string((unsigned int)grid_vectors.vectors[i][j]);
                vectors_array[i].id = string_id;
                vectors_array[i].in_cluster = false;
            }
            else
                vectors_array[i].vectors.push_back(grid_vectors.vectors[i][j]);
        }
    }
}
