#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <fstream>

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
            cout<<", "+to_string(k);
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
        if (j == patternLength) { // se encontrou uma correspondência completa
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

    for(int k=1;k<str.length();k++){
        for(int c=0;c<256;c++){
            func[c][k]=func[c][x];
        }
        func[str[k]][k]=k+1;
        x=func[str[k]][x];
    }

    return func;
}

bool is_valid(char X){
    int x = (int)X;
    return (x>=65&&x<=90)||(x>96&&x<=122)||(x>=127&&x<=165)||(x>=180&&x<=183)||(x==198||x==199)||(x>=210&&x<=216)||(x>=222&&x<=237);
}

bool is_valid(string str){

    for(int k=0;k<str.length();k++){
        if(!is_valid(str[k])) return false;
    }
    return true;
}

string remove_slash(string str){
    int k;
    for(k=0;k<str.length();k++){
        if(str[k]=='/') break;
    }
    return str.substr(0,k);
}

class CorrectedWord{
    public:
    string word;
    int position;
    int distance;
    bool correct;

    CorrectedWord();

    CorrectedWord(string w, int p, int d, bool c){
        word=w;
        position=p;
        distance=d;
        correct=c;
    }

    void print(){
        cout<< '['+word+','+to_string(position)+','+to_string(distance)+','+to_string(correct)+"]\n";
    }
};

vector<CorrectedWord> correct_word(string word, vector<string> dictionary){
    int score=-1;
    vector<int> pos;
    
    for(int k=0;k<dictionary.size();k++){
        int sum=word.length()-dictionary[k].length();
        sum = abs(sum);
        if(sum>=score && score!=-1) continue;
    
        for(int c=0;c<word.length();c++){
            sum+=tolower(word[c])!=tolower(dictionary[k][c]);
        }
        if(sum<score || score==-1) {
            score= sum;
            pos.clear();
        }

        if(sum==score){
            pos.push_back(k);
        }

        if(score==0){
            break;
        }
    }

    vector<CorrectedWord> vect;
    for(int k=0;k<pos.size();k++){
        vect.push_back(CorrectedWord((string)dictionary[pos[k]],pos[k],score,score==0));
    }
    cout<<pos.size();
    cout<<" ";
    return vect;
}

int main(){
    string test = "alaude";
    vector<string> dictionary;

    //reading file for dictionary
    ifstream fileRead("pt_BR.dic");
    string line;
    while(getline(fileRead,line)){
        if(is_valid(remove_slash(line))){
            dictionary.push_back(remove_slash(line));
            //cout<<remove_slash(line)+"\n";
        }
    }
    Matrix m = computeFailureFunction(test);
    m.print();
    /*for(CorrectedWord W :correct_word(test,dictionary)){
        W.print();
    };*/
}