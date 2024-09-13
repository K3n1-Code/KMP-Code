#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>
#include <fstream>
#include <vector>

using namespace std;

string cifra(const string& texto, const string& chave) {
    string textoCifrado = texto;
    for (size_t i = 0; i < textoCifrado.size(); i++) {
        if (isalpha(textoCifrado[i])) {
            char letra = tolower(textoCifrado[i]);
            int posicao = letra - 'a';
            textoCifrado[i] = chave[posicao];
        }
    }
    return textoCifrado;
}

string decifra(const string& textoCifrado, const string& chave) {
    string textoOriginal = textoCifrado;
    for (size_t i = 0; i < textoOriginal.size(); i++) {
        if (isalpha(textoOriginal[i])) {
            char letra = tolower(textoOriginal[i]);
            int posicao = find(chave.begin(), chave.end(), letra) - chave.begin();
            textoOriginal[i] = 'a' + posicao;
        }
    }
    return textoOriginal;
}

// Frequência das letras em inglês (aproximada)
double frequenciasIngles[] = {
    8.2, 1.5, 2.8, 4.3, 12.7, 2.2, 2.0, 6.1, 7.0, 0.15,
    0.77, 4.0, 2.4, 6.7, 7.5, 1.9, 0.095, 6.0, 6.3, 9.1,
    2.8, 0.98, 2.4, 0.15, 2.0, 0.074
};

// Função para calcular a hash de um caractere
int hashChar(char c) {
    return tolower(c) - 'a';
}

void insertionSort(vector<pair<double, int>>& arr, bool decrescente = true) {
    for (int i = 1; i < arr.size(); ++i) {
        double key = arr[i].first;
        int cha = arr[i].second;
        int j = i - 1;

        // Alterado para ordenação decrescente
        while (j >= 0 && ((decrescente && arr[j].first < key) || (!decrescente && arr[j].first > key))) {
            arr[j + 1].first = arr[j].first;
            arr[j + 1].second = arr[j].second;
            j = j - 1;
        }
        arr[j + 1].first = key;
        arr[j + 1].second = cha;
    }
}

string quebraCifraFrequencia(const string& textoCifrado,const string& alfa) {
    int frequenciasCifrado[26] = {0};
    int totalLetras = 0;

    // Calcular a frequência das letras no texto cifrado
    for (char c : textoCifrado) {
        if (isalpha(c)) {
            frequenciasCifrado[hashChar(c)]++;
            totalLetras++;
        }
    }

    // Calcular as frequências relativas
    /*double frequenciasRelativasCifrado[26];
    for (int i = 0; i < 26; i++) {
        frequenciasRelativasCifrado[i] = (double)frequenciasCifrado[i] / totalLetras * 100;
    }*/

    // Criar arrays de mapeamento manual
    char mapeamento[26]; // Para mapear de 'a' a 'z'
    vector<pair<double, int>> sortedFrequenciesCifrado;
    vector<pair<double, int>> sortedFrequenciesIngles;

    // Preencher vetores de pares (frequência, letra)
    for (int i = 0; i < 26; i++) {
        sortedFrequenciesCifrado.push_back({frequenciasCifrado[i], i});
        sortedFrequenciesIngles.push_back({frequenciasIngles[i], i});
    }

    // Ordenar as frequências em ordem decrescente
    insertionSort(sortedFrequenciesCifrado, true);
    for(pair<double, int> a: sortedFrequenciesCifrado){
        cout<<to_string(0)+","+(char)('a'+a.second)+"; ";
    }
    insertionSort(sortedFrequenciesIngles, true);
    cout<<"\n\n";
    for(pair<double, int> a: sortedFrequenciesIngles){
        cout<<to_string(0)+","+(char)('a'+a.second)+"; ";
    }
    
    cout<<"\n\n";

    // Preencher o array de mapeamento manual
    for (int i = 0; i < 26; i++) {
        mapeamento[sortedFrequenciesCifrado[i].second] = 'a' + sortedFrequenciesIngles[i].second; // Mapear manualmente com base na frequência   
    }

    /*for(char a : mapeamento){
        cout<<a;
    }*/

    cout<<cifra(alfa,mapeamento);

    // Decifrar o texto usando o mapeamento manual
    string textoDecifrado = "";
    for (char c : textoCifrado) {
        if (isalpha(c)) {
            textoDecifrado += mapeamento[hashChar(c)];
        } else {
            textoDecifrado += c;
        }
    }

    return textoDecifrado;
}

int main() {
    srand(time(0));
    string alfabeto = "abcdefghijklmnopqrstuvwxyz";
    random_shuffle(alfabeto.begin(), alfabeto.end());

    cout << "Alfabeto      : " << "abcdefghijklmnopqrstuvwxyz" << "\n";
    cout << "Chave original: " << alfabeto << "\n";
    

    string nomeArquivo = "big.txt";
    ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }

    string textoCifrado;
    string textoACifrar;
    string linha;
    while (getline(arquivo, linha)) {
        textoACifrar += linha;
    }

    arquivo.close();

    textoCifrado = cifra(textoACifrar, alfabeto);
    //scout << "Texto cifrado: " << textoCifrado << endl;

    string textoOriginalDecifrado = quebraCifraFrequencia(textoCifrado,alfabeto);
    //cout << "Texto decodificado pela análise de frequência: " << textoOriginalDecifrado << endl;

    return 0;
}

