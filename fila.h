/*****************************************************
 * IMPLEMENTAÇÃO DO TAD - Alocação dinâmica
 *****************************************************
 * TAD FILA IMPLEMENTADO UTILIZANDO VETORES E ALOCAÇÃO DINÂMICA
  *****************************************************/
// diretiva de pré-compilação para evitar a redefinição do tipo
#ifndef FILA_H
#define FILA_H

#include <cstdlib> // para usar o apontador NULL

#define BLOCO   5 // tamanho do bloco utilizado para cada redimensionamento do vetor
// Declaração da classe FILA, seus atributos e métodos.
template <class T>
class Fila
{
    private:
        T* dados;
        int head; // descritor (indice) para o início da fila
        int tail; // descritor (indice) para o final da fila

        int capacidade; // atributo que auxilia no processo de redimensionamento
        void Resize();  // função para redimensionamento
    public:
        Fila(); // construtor do TAD fila
        Fila(const Fila&);
        void Enfileirar(T); // método para enfileirar dados no final da fila
        T  Desenfileirar(); // método para desenfileirar dados do inicio da fila
        bool Vazia(); // método para verificar se uma fila está vazia
        ~Fila();
};

// construtor do TAD fila
template <class T>
Fila<T>::Fila()
{
    head = -1;
    tail = -1;
    capacidade = BLOCO;
    dados = new T[capacidade];
}

template <class T>
Fila<T>::Fila(const Fila& f)
{
    head = f.head;
    tail = f.tail;
    capacidade = f.capacidade;
    dados = new T[capacidade];
    for(int i=0;i<capacidade; i++ )
        dados[i] = f.dados[i];
}

// método para enfileirar dados no final da fila
template <class T>
void Fila<T>::Enfileirar(T item)
{
    if ( Vazia() )
        head = 0;
    else
        if ( (tail+1)%capacidade == head ) // verifica se a Fila está cheia
            Resize();

    tail = (tail+1)%capacidade;
    dados[tail] = item;
}

// método para desenfileirar dados do inicio da fila
template <class T>
T  Fila<T>::Desenfileirar()
{
    if ( !Vazia() )
    {
        T aux = dados[head];
        if ( head == tail ) // verifica se o elemento retirado foi o último
            head = tail = -1;
        else
            head = (head+1)%capacidade; // caminha com o descritor...
        return aux;
    }
}

// método para verificar se um fila está vazia
template <class T>
bool Fila<T>::Vazia()
{
    return head==-1;
}


template <class T>
void Fila<T>::Resize() // redimensiona o vetor de dados
{
    T *tmp = new T[capacidade+BLOCO];
    for(int i=0; i<capacidade; i++)
        tmp[i] = dados[(head+i)%capacidade];

    delete []dados;
    dados = tmp;

    head = 0; // atualiza o descritor para o início do vetor
    tail = capacidade-1; // atualiza a cauda para o tamanho do vetor antes de atualizar a capacidade
    capacidade += BLOCO;
}

template <class T>
Fila<T>::~Fila()
{
    delete []dados;
}

#endif
