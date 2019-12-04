#include "curves.h"
#include <unistd.h>

void printCurves(vector<curve> curves, int number_of_lines)
{
    for (int i = 0; i < number_of_lines; i++)
    {
        cout << "curves[" << i << "].dimensions: " << curves[i].dimensions << endl;
        cout << "curves[" << i << "].id: " << curves[i].id << endl;
        for (int j = 0; j < curves[i].vectorPoins.size(); j++)
        {
            cout << "curves[" << i << "].vectorPoins[" << j << "].x: " << curves[i].vectorPoins[j].x << endl;
            cout << "curves[" << i << "].vectorPoins[" << j << "].y: " << curves[i].vectorPoins[j].y << endl;
        }
    }
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
                curves[i].in_cluster = false;
                // cout << "curves[" << i << "].id: " << curves[i].id << endl;
            }
            if (countKena == 1)
            {
                curves[i].dimensions = number;
                // cout << "curves[" << i << "].dimensions: " << curves[i].dimensions << endl;
                break;
            }
            countKena++;
        }
    }
    stringstream line(str);
    file.close();
    // cout << "Perasa to close" <<endl;
}

string convertToString(char *array, int size)
{
    int i;
    string str = "";
    for (i = 0; i < size; i++)
    {
        str = str + array[i];
    }
    return str;
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
        //cout << "perase cout" << endl;
    }

    file.close();
}
