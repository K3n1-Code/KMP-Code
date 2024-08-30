#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

class Matrix{
    private:
    vector<vector<int>> matrix;
    int size[2];

    public:
    Matrix(int w, int h){
        size[0]=w;
        size[1]=h;
        matrix=vector<vector<int>>(w);
        for(int k=0;k<w;k++){
            matrix[k]=vector<int>(h);
        }
    }

    Matrix(){
        this->matrix=vector<vector<int>>();
        size[0]=0;
        size[1]=0;
    }

    public:
    int width(){return size[0];}

    int height(){return size[1];}

    vector<int>& operator[](const int &w){
        return matrix[w];
    }
};

Matrix computeFailureFunction(const string &str){
    Matrix func(256,str.length());
    for(int c=0;c<256;c++){
        func[c][0]=0;
    }
    func[(int)str[0]][0]=1;
    int x=0;

    for(int k=1;k<str.length()-1;k++){
        for(int c=0;c<256;c++){
            func[c][k]=func[c][x];
        }
        func[str[k]][k]=k+1;
        x=func[str[k]][x];
    }

    return func;
}

int main(){
    string test = "Marcus";
    Matrix m = computeFailureFunction(test);
}