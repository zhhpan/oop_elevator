#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Building.h"
#include <vector>
#include<Python.h>
#include<string>
using std::cin;
using std::cout;
using std::endl;

void plot(vector<int> vector1, const int n, vector<int> vector2);
string arr_to_string_list(vector<int> vector1, const int n);
void pythonInitial();

int main()
{
    vector<int> a;
    vector<int> b;
    a.push_back(0);
    Building building;
    int i=0;
    srand(time(NULL));//generate random number seeds
    while(true){
        b.push_back(i);
        if(i==0){
            ++i;
            continue;
        }
        else if(i>=1&&i<15) {
            cout << building.step(20*i,a) << endl; // 5 riders created in a second
            ++i;
        }
        else if(i>=15) {
            cout<<building.step(a)<<endl;
            int judge=0;
            for(int j=0;j<280;++j){
                if(building.isRider[j])
                    judge=1;
            }
            if(judge==0)
                break;
            ++i;
        }

    }
    building.show();
    pythonInitial();
    plot(b, i, a);
    Py_Finalize();
    system("pause");
    return 0;
}

void pythonInitial() {
    Py_Initialize();
    string path = ".";
    string chdir_cmd = string("sys.path.append(\"") + path + "\")";
    const char* cstr_cmd = chdir_cmd.c_str();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString(cstr_cmd);
}
void plot(vector<int> vector1, const int n, vector<int> vector2) {
    PyRun_SimpleString("import matplotlib.pyplot as plt");
    string cmd = "plt.plot(";
    string s1 = arr_to_string_list( vector1, n);
    string s2 = arr_to_string_list(vector2, n);
    cmd += (s1 + "," + s2 + " )");
    PyRun_SimpleString(cmd.c_str());
    PyRun_SimpleString("plt.xlabel('Time',fontsize=14)");
    PyRun_SimpleString("plt.ylabel('The count of Riders',fontsize=14)");
    PyRun_SimpleString("plt.grid(True,color='b')");
    PyRun_SimpleString("plt.gca().get_autoscale_on()");
    PyRun_SimpleString("plt.gca().get_autoscalex_on()");
    PyRun_SimpleString("plt.gca().get_autoscaley_on()");
    PyRun_SimpleString("plt.show()");
}

string arr_to_string_list(vector<int> vector1, const int n) {
    string s = "[";
    for (int i = 0; i < n; ++i) {
        s += std::to_string(vector1[i]);
        if (i != n - 1)
            s += ",";
    }
    s += "]";
    return s;
}
