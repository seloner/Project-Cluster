#include <bits/stdc++.h>
#include "readFunctions.h"
#include "clusterStructs.h"
#include <algorithm>

int type_of_file(char *path)
{
    ifstream file;
    file.open(path, ios::in);
    int number_of_lines = 0;
    string line;
    //get every line from the input
    getline(file, line);
    if (!line.empty() && line[line.length() - 1] == '\r')
    {
        line.erase(line.length() - 1);
    }
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

void readClusterConf(char *path, cluster &clusterInfo)
{
    ifstream file;
    file.open(path, ios::in);
    string str;
    string comingString;
    string const delims{"\t<>= "};

    int getTheNumber = 0;
    int insideCounter = 0;

    //line 1 of conf
    size_t beg = 0, pos = 0;
    getline(file, str);

    while ((beg = str.find_first_not_of(delims, pos)) != std::string::npos)
    {
        if (insideCounter == 2)
        {
            getTheNumber = stoi(comingString);
            break;
        }
        pos = str.find_first_of(delims, beg + 1);
        comingString = str.substr(beg, pos - beg);
        //cout <<"#comingString#"<<endl<< comingString<<endl;
        insideCounter++;
    }
    clusterInfo.number_of_clusters = getTheNumber;
    cout << "number_of_clusters:" << getTheNumber << endl;

    //line 2 of conf
    beg = 0, pos = 0;
    insideCounter = 0;
    getline(file, str);

    while ((beg = str.find_first_not_of(delims, pos)) != std::string::npos)
    {
        if (insideCounter == 2)
        {
            //an einai diaforo tou 0 tote exei do8ei ari8mos ara den exei noima na pame parakatw
            getTheNumber = stoi(comingString);
            if (getTheNumber != 0)
                break;
        }
        pos = str.find_first_of(delims, beg + 1);
        comingString = str.substr(beg, pos - beg);
        insideCounter++;
        if (insideCounter == 4)
        {
            getTheNumber = stoi(comingString);
            break;
        }
        //cout <<"insideCounter: "<<insideCounter <<" #comingString#"<<endl<< comingString<<endl;
    }
    clusterInfo.number_of_grids = getTheNumber;
    cout << "number_of_grids:" << getTheNumber << endl;

    //line 3 of conf
    beg = 0, pos = 0;
    insideCounter = 0;
    getline(file, str);

    while ((beg = str.find_first_not_of(delims, pos)) != std::string::npos)
    {
        if (insideCounter == 2)
        {
            //an einai diaforo tou 0 tote exei do8ei ari8mos ara den exei noima na pame parakatw
            getTheNumber = stoi(comingString);
            if (getTheNumber != 0)
                break;
        }
        pos = str.find_first_of(delims, beg + 1);
        comingString = str.substr(beg, pos - beg);
        insideCounter++;
        if (insideCounter == 5)
        {
            getTheNumber = stoi(comingString);
            //cout <<"getTheNumber= "<< getTheNumber<<endl;
            break;
        }
        //cout <<"insideCounter: "<<insideCounter <<" #comingString#"<<endl<< comingString<<endl;
    }
    clusterInfo.number_of_vector_hash_functions = getTheNumber;
    cout << "number_of_vector_hash_functions:" << getTheNumber << endl;

    //line 4 of conf
    beg = 0, pos = 0;
    insideCounter = 0;
    getline(file, str);

    while ((beg = str.find_first_not_of(delims, pos)) != std::string::npos)
    {
        if (insideCounter == 2)
        {
            getTheNumber = stoi(comingString);
            break;
        }
        pos = str.find_first_of(delims, beg + 1);
        comingString = str.substr(beg, pos - beg);
        //cout <<"#comingString#"<<endl<< comingString<<endl;
        insideCounter++;
    }
    clusterInfo.number_of_vector_hash_tables = getTheNumber;
    cout << "number_of_vector_hash_tables:" << getTheNumber << endl;
    cout << endl;
    file.close();
}