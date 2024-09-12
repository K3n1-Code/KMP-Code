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
    11.1607, 8.4966, 7.5809, 7.5448, 7.1635, 6.9509, 6.6544, 5.7351, 5.4893, 4.5388,
    3.6308, 3.3844, 3.1671, 3.0129, 3.0034, 2.4705, 2.0720, 1.8121, 1.7779, 1.2899,
    1.1016, 1.0074, 0.2902, 0.2722, 0.1965, 0.1962
};

// Função para calcular a hash de um caractere
int hashChar(char c) {
    return tolower(c) - 'a';
}

void insertionSort(vector<pair<double, int>> arr)
{
    for (int i = 1; i < arr.size(); ++i) {
        double key = arr[i].first;
        int cha = arr[i].second;
        int j = i - 1;

        while (j >= 0 && arr[j].first > key) {
            arr[j + 1].first = arr[j].first;
            arr[j + 1].second = arr[j].second;
            j = j - 1;
        }
        arr[j + 1].first = key;
        arr[j + 1].second = cha;
    }
}

string quebraCifraFrequencia(const string& textoCifrado) {
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
    double frequenciasRelativasCifrado[26];
    for (int i = 0; i < 26; i++) {
        frequenciasRelativasCifrado[i] = (double)frequenciasCifrado[i] / totalLetras * 100;
    }

    // Criar arrays de mapeamento manual
    char mapeamento[26]; // Para mapear de 'a' a 'z'
    vector<pair<double, int>> sortedFrequencies;

    for (int i = 0; i < 26; i++) {
        sortedFrequencies.push_back({frequenciasRelativasCifrado[i], i});
    }

    insertionSort(sortedFrequencies);
    //sort(sortedFrequencies.rbegin(), sortedFrequencies.rend()); // Ordenar em ordem decrescente

    // Preencher o array de mapeamento manual
    for (int i = 0; i < 26; i++) {
        mapeamento[sortedFrequencies[i].second] = 'a' + i; // Mapear manualmente com base na frequência
    }

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

    cout << "chave original: " << alfabeto << "\n";


    string nomeArquivo = "alice_in_wonderland.txt";
    ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }

    string textoCifrado;
    string textoACifrar;
    string textoOriginal;
    string linha;
    while (getline(arquivo, linha)) {
        textoACifrar += linha;
    }

    arquivo.close();
    //cout << "Texto Original: " << textoACifrar <<"\n"<< endl;

    textoCifrado = cifra(textoACifrar, alfabeto);

    //cout << "Texto cifrado: " << textoCifrado <<"\n"<< endl;

    textoOriginal = quebraCifraFrequencia(textoCifrado);
    cout << "Texto Original decodificado: " << textoOriginal << "\n" << endl;

    string textoDescriptografado = decifra(textoCifrado, alfabeto);
    cout << "Texto Descriptografado: " << textoDescriptografado << endl; 

    return 0;
}