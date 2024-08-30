#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

bool is_vector_zero(vector<int> a){
    for(const int &n: a){
        if(n!=0)return false;
    }
    return true;
}

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
    
    void print(bool not_zero){
        for(int k=0;k<width(); k++){
            if(not_zero && is_vector_zero(matrix[k])) continue;
            cout<<"\n";
            cout<<(char)k;
            cout<<" : ";
            for(int l=0;l<height();l++){
                cout<<matrix[k][l];
                cout<<" ";
            }
        }
    }

    void print(){
        print(true);
    }

};


int KMP(const string &pattern, const string &text, Matrix &f) {
    int j = 0; // posição atual na palavra pattern
    int patternLength = pattern.length(); // comprimento do padrão
    int textLength = text.length(); // comprimento do texto

    for (int i = 0; i < textLength; i++) { 

        // cout<<"jota"<< j<<"\n";
        // cout <<"length" <<patternLength<<"\n";
        // i é a posição atual no texto
        j = f[text[i]][j]; // atualiza a posição no padrão usando a função de falha
        if (j == patternLength-1) { // se encontrou uma correspondência completa
            return i - j + 1; // retorna a posição da primeira ocorrência
        }
    }
    return -1; // sem ocorrências
}

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
    string test = "ABABAABAAACBAACAAACCCAACABB";
    Matrix m = computeFailureFunction(test);
    m.print();
    
}