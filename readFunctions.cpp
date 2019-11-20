#include "readFunctions.h"
#include <bits/stdc++.h>
int type_of_file(char *path)
{
    ifstream file;
    file.open(path, ios::in);
    int number_of_lines = 0;
    string line;
    //get every line from the input
    getline(file, line);
    if (line.compare("vectors") == 0)
    {
        return 0;
    }
    else if (line.compare("curves") == 0)
    {
        return 1;
    }
    else
    {
        cout << "Wrong input file" << endl;
        exit(-1);
    }
    file.close();
    //return number of lines;
    return number_of_lines;
}

int calculateInputSize(char *path)
{
    ifstream file;
    file.open(path, ios::in);
    int number_of_lines = 0;
    string line;
    //get every line from the input
    while (getline(file, line))
    {

        ++number_of_lines;
    }
    file.close();
    //return number of lines;
    return number_of_lines;
}

int calculateDimension(char *path)
{
    ifstream file;
    file.open(path, ios::in);
    string str, temp;
    vector<string> tokens;
    //ingore the first line of the file
    getline(file, str, '\n');
    //calculate the dimension from the second line
    getline(file, str, '\n');
    stringstream line(str);
    //find how many dimensions we have
    while (getline(line, temp, '\t'))
    {
        tokens.push_back(temp);
    }
    file.close();
    //last word is space so dimension=tokens.size-2
    return (tokens.size() - 1);
}