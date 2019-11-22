#include <bits/stdc++.h>
#include "readFunctions.h"
#include "curveStructs.h"
#include "clusterStructs.h"

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

void calculateCurveDimensions(char *path, vector<curve> &curves, int number_of_lines)
{
    ifstream file;
    file.open(path, ios::in);
    string str, temp;
    vector<string> tokens;

    //we begin from the second line
    getline(file, str);

    for (int i = 0; i < number_of_lines; i++)
    {

        getline(file, str);
        //cout << "[str: " << str << "]"<< endl;

        stringstream line(str);
        int countKena = 0, number = 0;
        while (getline(line, temp, '\t'))
        {
            stringstream line(temp);
            line >> number;
            if (countKena == 0)
            {
                curves.push_back(curve());
                curves[i].id = number;
                curves[i].intoCluster = false;
                cout << "curves[" << i << "].id: " << curves[i].id << endl;
            }
            if (countKena == 1)
            {
                curves[i].dimensions = number;
                cout << "curves[" << i << "].dimensions: " << curves[i].dimensions << endl;
                break;
            }
            countKena++;
        }
    }
    stringstream line(str);
    file.close();
    // cout << "Perasa to close" <<endl;
}

void fillVectorWithCurves(char *path, vector<curve> &curves, int number_of_lines)
{
    ifstream file;
    file.open(path, ios::in);
    string str, temp;
    string doubleFromString, comingString;
    string const delims{"\t(,) "};
    int flag = 0;

    //we begin from the second line
    getline(file, str);

    for (int i = 0; i < number_of_lines; i++)
    {
        size_t beg = 0, pos = 0;
        getline(file, str);
        long double xNumber = 0, yNumber = 0;
        bool alreadyAllocated = false;
        int countKena = 0; //gia apofigi twn 2 prwtwn kenwn

        long double numberFinally = 0;
        int insideCounter = 0;
        while ((beg = str.find_first_not_of(delims, pos)) != std::string::npos)
        {
            //cout << "inside counter twra: "<<insideCounter<<endl;
            if (alreadyAllocated == false)
            {
                //cout << "[EFTIAXE POINT] insideCounter: "<<insideCounter<<endl;
                curves[i].vectorPoins.push_back(point());
                alreadyAllocated = true;
            }

            if (countKena == 0 || countKena == 1)
            {
                countKena++;
                //cout << "countkena: "<< countKena <<endl;
                str.substr(beg, pos - beg);
                pos = str.find_first_of(delims, beg + 1);
                //cout << "continue" <<endl;
                continue;
            }
            pos = str.find_first_of(delims, beg + 1);
            comingString = str.substr(beg, pos - beg);

            numberFinally = stod(comingString);
            //cout << "[PRIN TIN FLAG]: "<<numberFinally<<endl;
            if (flag == 0)
            {
                //cout << "[MPIKE STIN FLAG 0]: "<<numberFinally<<endl;
                curves[i].vectorPoins[insideCounter].x = numberFinally;
                //cout << "curves["<<i<<"].vectorPoins["<<insideCounter<<"].x: "<< curves[i].vectorPoins[insideCounter].x << endl;
                flag = 1;
            }
            else if (flag == 1)
            {
                //cout << "[MPIKE STIN FLAG 1]: "<<numberFinally<<endl;
                curves[i].vectorPoins[insideCounter].y = numberFinally;
                //cout << "curves["<<i<<"].vectorPoins["<<insideCounter<<"].y: "<< curves[i].vectorPoins[insideCounter].y << endl;
                flag = 0;
                insideCounter++;
                //cout << "allazw to alreadyallocated se false" <<endl;
                alreadyAllocated = false;
            }

            // cout << endl;
        }
        cout << "perase cout" << endl;
    }

    file.close();
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
        if(insideCounter == 2)
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
    cout <<"number_of_clusters:"<<getTheNumber<<endl;

    //line 2 of conf
    beg = 0, pos = 0;
    insideCounter = 0;
    getline(file, str);

    while ((beg = str.find_first_not_of(delims, pos)) != std::string::npos)
    {
        if(insideCounter == 2)
        {
            //an einai diaforo tou 0 tote exei do8ei ari8mos ara den exei noima na pame parakatw
            getTheNumber = stoi(comingString);
            if(getTheNumber != 0)break;
        }
        pos = str.find_first_of(delims, beg + 1);
        comingString = str.substr(beg, pos - beg);
        insideCounter++;
        if(insideCounter == 4)
        {
            getTheNumber = stoi(comingString);
            break;
        }
        //cout <<"insideCounter: "<<insideCounter <<" #comingString#"<<endl<< comingString<<endl;
    }
    clusterInfo.number_of_grids = getTheNumber;
    cout <<"number_of_grids:"<<getTheNumber<<endl;

    //line 3 of conf
    beg = 0, pos = 0;
    insideCounter = 0;
    getline(file, str);

    while ((beg = str.find_first_not_of(delims, pos)) != std::string::npos)
    {
        if(insideCounter == 2)
        {
            //an einai diaforo tou 0 tote exei do8ei ari8mos ara den exei noima na pame parakatw
            getTheNumber = stoi(comingString);
            if(getTheNumber != 0)break;
        }
        pos = str.find_first_of(delims, beg + 1);
        comingString = str.substr(beg, pos - beg);
        insideCounter++;
        if(insideCounter == 5)
        {
            getTheNumber = stoi(comingString);
            //cout <<"getTheNumber= "<< getTheNumber<<endl;
            break;
        }
        //cout <<"insideCounter: "<<insideCounter <<" #comingString#"<<endl<< comingString<<endl;
    }
    clusterInfo.number_of_vector_hash_functions = getTheNumber;
    cout <<"number_of_vector_hash_functions:"<<getTheNumber<<endl;

    //line 4 of conf
    beg = 0, pos = 0;
    insideCounter = 0;
    getline(file, str);

    while ((beg = str.find_first_not_of(delims, pos)) != std::string::npos)
    {
        if(insideCounter == 2)
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
    cout <<"number_of_vector_hash_tables:"<<getTheNumber<<endl;
    cout <<endl;
    file.close();
}