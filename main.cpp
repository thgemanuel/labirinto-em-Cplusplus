#include <bits/stdc++.h>

using namespace std;
#include "fila.h"
#include "Pilha.h"

//Função que recebe a matriz de coordenadas do labirinto e a coordenada de inicio para realizar uma busca em amplitude pela saída e retorna uma pilha correspondente ao caminho tomado.
Pilha<int> encontrasaida(vector< vector<int> > nodes, int inicio) {
    Fila< vector <int> > pesquisa;
    Fila<int> visitados, filaorigem;
    Pilha< vector<int> > origem;
    Pilha<int> caminho;
    vector<int> fetchaux(2), fetch(5);
    fetchaux[0] = inicio;
    fetchaux[1] = inicio;
    int fetchid = inicio;
    bool saida = 0;
    pesquisa.Enfileirar(nodes[inicio]);
    visitados.Enfileirar(inicio);
    filaorigem.Enfileirar(inicio);
    origem.Empilha(fetchaux);
    //Busca em amplitude
    while (!pesquisa.Vazia() && !saida) {

        fetch = pesquisa.Desenfileirar();
        fetchid = filaorigem.Desenfileirar();
        for (int x = 0; x < 4; x++) {
            fetchaux[0] = fetch[x];
            fetchaux[1] = fetchid;
            if (fetch[x] == 0) {
                origem.Empilha(fetchaux);
                saida = 1;
                break;
            } else if (fetch[x] != -1) {

                Fila<int> aux;
                bool visitado = false;
                while (!visitados.Vazia()) {
                    int i = visitados.Desenfileirar();
                    if (fetch[x] == i)
                        visitado = true;
                    aux.Enfileirar(i);
                }
                while (!aux.Vazia()) {
                    visitados.Enfileirar(aux.Desenfileirar());
                }
                if (visitado == false) {
                    pesquisa.Enfileirar(nodes[fetch[x]]);
                    origem.Empilha(fetchaux);
                    visitados.Enfileirar(fetch[x]);
                    filaorigem.Enfileirar(fetch[x]);
                }

            }

        }
    }
    //geracao do caminho para a saída
    if (saida) {
        int atual = 0, procura;
        fetchaux = origem.Desempilha();
        procura = fetchaux[1];
        caminho.Empilha(fetchaux[0]);
        while (atual != inicio && !origem.Vazia()) {
            fetchaux = origem.Desempilha();
            atual = fetchaux[0];
            if (atual == procura) {
                caminho.Empilha(fetchaux[0]);
                procura = fetchaux[1];
            }
        }
    }
    return caminho;
}
//Função que recebe a matriz de coordenadas do labirinto e a coordenada de inicio para realizar uma busca em amplitude pela pedra preciosa mais próxima e retorna uma pilha correspondente ao caminho tomado.
Pilha<int> encontragemas(vector< vector<int> > nodes, int inicio) {
    Fila< vector <int> > pesquisa;
    Fila<int> visitados, filaorigem;
    Pilha< vector<int> > origem;
    Pilha<int> caminho;
    vector<int> fetchaux(2), fetch(5);
    fetchaux[0] = inicio;
    fetchaux[1] = inicio;
    int fetchid = inicio;
    bool gema = false;
    pesquisa.Enfileirar(nodes[inicio]);
    visitados.Enfileirar(inicio);
    filaorigem.Enfileirar(inicio);
    origem.Empilha(fetchaux);
    //Busca em amplitude
    while (!pesquisa.Vazia() && !gema) {
        fetch = pesquisa.Desenfileirar();
        fetchid = filaorigem.Desenfileirar();
        for (int x = 0; x < 4; x++) {
            fetchaux[0] = fetch[x];
            fetchaux[1] = fetchid;
            if (fetch[x] != -1) {
                if (nodes[fetch[x]][4] == 1) {
                    origem.Empilha(fetchaux);
                    gema = true;
                    break;
                } else {
                    Fila<int> aux;
                    bool visitado = false;
                    while (!visitados.Vazia()) {
                        int i = visitados.Desenfileirar();
                        if (fetch[x] == i)
                            visitado = true;
                        aux.Enfileirar(i);
                    }
                    while (!aux.Vazia()) {
                        visitados.Enfileirar(aux.Desenfileirar());
                    }
                    if (visitado == false) {
                        pesquisa.Enfileirar(nodes[fetch[x]]);
                        origem.Empilha(fetchaux);
                        visitados.Enfileirar(fetch[x]);
                        filaorigem.Enfileirar(fetch[x]);
                    }
                }

            }

        }
    }
    //Geração do caminho
    if (gema) {
        int atual = 0, procura;
        fetchaux = origem.Desempilha();
        procura = fetchaux[1];
        caminho.Empilha(fetchaux[0]);
        while (atual != inicio && !origem.Vazia()) {
            fetchaux = origem.Desempilha();
            atual = fetchaux[0];
            if (atual == procura) {
                caminho.Empilha(fetchaux[0]);
                procura = fetchaux[1];
            }
        }
    }
    return caminho;
}

int main(int argc, char** argv) {

    fstream labirinto;
//Abre  arquivo
    labirinto.open("labirinto01a.txt", ios::in | ios::binary);
    if (labirinto.is_open()) {

        string line;
        int i, inicio = 0, tamanhomax;
        //Lê o arquivo e transforma as letras em coordenadas numéricas, que então são usadas para alocar um vetor do tamanho correto.
        for (i = 0; getline(labirinto, line); ++i) {
            for (unsigned int j = 0; j < line.length(); ++j) {
                line.erase(remove(line.begin(), line.end(), ':'), line.end());
            }
            stringstream ssin(line);
            int x = 0;
            while (ssin.good() && x < 4) {
                string temp;
                ssin >> temp;
                if (x == 0) {
                    int y = 0, j = 0, tamanho = 0;
                    if (temp[0] == '*') {
                        for (unsigned int k = 0; k < temp.length(); ++k) {
                            temp.erase(remove(temp.begin(), temp.end(), '*'), temp.end());
                        }
                        for (y = 0, j = (temp.length() - 1); y <= (temp.length() - 1) && j >= 0; y++, j--) {

                            tamanho += (temp[y] % 64) * pow(26, j);

                        }
                    } else {
                        for (y = 0, j = (temp.length() - 1); y <= (temp.length() - 1) && j >= 0; y++, j--) {

                            tamanho += (temp[y] % 64) * pow(26, j);

                        }
                    }
                    tamanhomax = tamanho + 1;
                }
                ++x;
            }
        }
        vector< vector<int> > nodes(tamanhomax);
        for (int x = 0; x < tamanhomax; x++)
            nodes[x].resize(5);
        //Reseta o arquivo e novamente começa a transformar as letras em coordenadas que agora são salvas no vetor já alocado de forma ordenada.
        labirinto.clear();
        labirinto.seekg(0, ios::beg);
        for (i = 0; getline(labirinto, line); ++i) {
            for (unsigned int j = 0; j < line.length(); ++j) {
                line.erase(remove(line.begin(), line.end(), ':'), line.end());
            }
            stringstream ssin(line);
            int x = 0;
            if (i == 0) {
                for (int y = 0, j = (line.length() - 2); y <= (line.length() - 2) && j >= 0; y++, j--) {
                    inicio += (line[y] % 64) * pow(26, j);
                }

            } else {
                int id = 0;
                while (ssin.good() && x < 5) {
                    string temp;
                    ssin >> temp;
                    if (x == 0) {
                        int y = 0, j = 0;
                        if (temp[0] == '*') {
                            for (unsigned int k = 0; k < temp.length(); ++k) {
                                temp.erase(remove(temp.begin(), temp.end(), '*'), temp.end());
                            }
                            for (y = 0, j = (temp.length() - 1); y <= (temp.length() - 1) && j >= 0; y++, j--) {

                                id += (temp[y] % 64) * pow(26, j);

                            }
                            nodes[id][4] = 1;
                        } else {
                            for (y = 0, j = (temp.length() - 1); y <= (temp.length() - 1) && j >= 0; y++, j--) {

                                id += (temp[y] % 64) * pow(26, j);

                            }
                            nodes[id][4] = 0;
                        }
                    } else {
                        int valor = 0;
                        if (temp != "w" && temp != "saída") {
                            for (int y = 0, j = (temp.length() - 1); y <= (temp.length() - 1) && j >= 0; y++, j--) {

                                valor += (temp[y] % 64) * pow(26, j);

                            }
                        } else if (temp == "w") {
                            valor = -1;
                        } else if (temp == "saída") {
                            valor = 0;
                        } else {
                            valor = -1;
                        }
                        nodes[id][x - 1] = valor;
                    }
                    ++x;
                }
            }

        }
        string caminhofinal;
        int nmovimentos = 0;
        //Chama a função de encontrar gemas até que ela retorne uma pilha vazia, garantindo qiue todas as gemas foram coletadas. Transforma coordenadas novamente em letras para melhor entendimento
        while (!encontragemas(nodes, inicio).Vazia()) {
            Pilha<int> caminho = encontragemas(nodes, inicio);
            while (!caminho.Vazia()) {
                int conversao = caminho.Desempilha(), aux = conversao;
                string coordenada;
                do {
                    int resultado = (conversao % 26) + 64;
                    conversao = conversao / 26;
                    if (resultado == 64) {
                        resultado = 90;
                        conversao--;
                    }
                    coordenada = (char) resultado + coordenada;
                } while (conversao != 0);
                if (nodes[aux][4] != 1) {
                    caminhofinal = caminhofinal + coordenada + " -> ";
                    nmovimentos++;
                } else {
                    caminhofinal += "(Pedra preciosa)";
                    nodes[aux][4] = 0;
                    inicio = aux;
                }
            }
        }
        //Chama a função de encontrar saída e finaliza a string de caminho com o uso de letras
        Pilha<int> caminho = encontrasaida(nodes, inicio);
        if (!caminho.Vazia()) {
            while (!caminho.Vazia()) {
                int conversao = caminho.Desempilha();
                string coordenada;
                do {
                    if (conversao == 0) {
                        coordenada = "saída";
                    } else {
                        int resultado = (conversao % 26) + 64;
                        conversao = conversao / 26;
                        if (resultado == 64) {
                            resultado = 90;
                            conversao--;
                        }
                        coordenada = (char) resultado + coordenada;
                    }
                } while (conversao != 0);
                if (coordenada != "saída") {
                    caminhofinal = caminhofinal + coordenada + " -> ";
                    nmovimentos++;
                } else
                    caminhofinal = caminhofinal + coordenada;

            }
            cout << "\n" << caminhofinal << ". Labirinto resolvido em " << nmovimentos << " movimentos.\n";
        } else
            cout << "Não foi encontrada a saída, possivel labirinto sem solução";
        labirinto.close();
    } else {
        cout << "Erro ao abrir arquivo!!!";
    }

    return 0;
}

