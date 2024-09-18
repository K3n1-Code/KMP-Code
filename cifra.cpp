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

// Frequência das letras em inglês (aproximada)
double frequenciasIngles[] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.253,
    1.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 	9.056,
    2.758, 0.978, 2.360, 0.250, 1.974, 0.074
};

// double frequenciasIngles[] = {
//     8.2, 1.5, 2.8, 4.3, 12.7, 2.2, 2.0, 6.1, 7.0, 0.15,
//     0.77, 4.0, 2.4, 6.7, 7.5, 1.9, 0.095, 6.0, 6.3, 9.1,
//     2.8, 0.98, 2.4, 0.15, 2.0, 0.074
// };

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

string quebraCifraFrequencia(const string& textoCifrado, const vector<int> &freq) {
    int frequenciasCifrado[26] = {0};
    int totalLetras = 0;

    // Calcular a frequência das letras no texto cifrado
    for (char c : textoCifrado) {
        if (isalpha(c)) {
            frequenciasCifrado[hashChar(c)]++;
            totalLetras++;
        }
    }

    // Criar arrays de mapeamento manual
    string mapeamento="abcdefghijklmnopqrstuvwxyz"; // Para mapear de 'a' a 'z'
    vector<pair<double, int>> sortedFrequenciesCifrado;
    vector<pair<double, int>> sortedFrequenciesIngles;

    // Preencher vetores de pares (frequência, letra)
    for (int i = 0; i < 26; i++) {
        sortedFrequenciesCifrado.push_back({frequenciasCifrado[i], i});
        sortedFrequenciesIngles.push_back({freq[i], i});
    }

    // Ordenar as frequências em ordem decrescente
    insertionSort(sortedFrequenciesCifrado, true);
    insertionSort(sortedFrequenciesIngles, true);

    
    // Preencher o array de mapeamento manual
    for (int i = 0; i < 26; i++) {
        mapeamento[sortedFrequenciesCifrado[i].second] = 'a' + sortedFrequenciesIngles[i].second; // Mapear manualmente com base na frequência   
    }
    
    return mapeamento;
}

string quebraCifraFrequencia(const string& textoCifrado){
    vector<int> vect;
    for(int i :frequenciasIngles){
        vect.push_back(i);
    }
    return quebraCifraFrequencia(textoCifrado,vect);
}

vector<int> get_letter_frequency(const string &text){
    vector<int> freq(26);
    for (char c : text) {
        if (isalpha(c)) {
            freq[hashChar(c)]++;
        }
    }
    return freq;
}

int main() {
    srand(time(0));
    string alfabeto = "abcdefghijklmnopqrstuvwxyz";
    random_shuffle(alfabeto.begin(), alfabeto.end());

    cout << "Alfabeto      : " << "abcdefghijklmnopqrstuvwxyz" << "\n";
    cout << "Chave original: " << alfabeto << "\n";
    

    string nomeArquivo = "alice_in_wonderland.txt";
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
    //cout << "Texto cifrado: " << textoCifrado << endl;

    string antiChave = quebraCifraFrequencia(textoCifrado);
    string textoOriginalDecifrado = cifra(textoCifrado,antiChave);
    string chavegerada = cifra(alfabeto, antiChave);
    cout <<"chave gerada: "<< chavegerada<< endl;
    cout << "Texto decodificado pela analise de frequencia: " << textoOriginalDecifrado << endl;
   
     
    return 0;
}

