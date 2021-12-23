#ifndef PILHA_H_
#define PILHA_H_

#include <iostream>
#include <cassert>
using namespace std;

#define TAM_BLOCO   10

template <class TIPO>
class Pilha
{
    private:
        TIPO *dados;
        int topo;
        int capacidade;
        void Realocar();
    public:
        Pilha();
        bool Vazia();
        void Empilha(TIPO elem);
        TIPO Desempilha();
        void Print();
        ~Pilha(); // destrutor da classe PIlha
};

template <class TIPO>
Pilha<TIPO>::Pilha()
{
    topo = -1;
    capacidade = TAM_BLOCO;
    dados = new TIPO[capacidade];
}

template <class TIPO>
bool Pilha<TIPO>::Vazia()
{
    return topo == -1;
}

template <class TIPO>
void Pilha<TIPO>::Empilha(TIPO elem)
{
    if ( topo+1 == capacidade )
        Realocar();
    dados[++topo] = elem;
}

template <class TIPO>
TIPO Pilha<TIPO>::Desempilha()
{
    assert ( !Vazia() ); /// verificar STACK UNDERFLOW
    return dados[topo--];
}

template <class TIPO>
void Pilha<TIPO>::Print()
{
    cout<<'{';
    for(int i=topo; i>0; i--)
        cout<<dados[i]<<", ";
    if ( !Vazia() )
        cout<<dados[0];
    cout<<'}';
}

template <class TIPO>
void Pilha<TIPO>::Realocar()
{
    TIPO *aux = new TIPO[capacidade+TAM_BLOCO];
    for( int i=0; i<capacidade; i++ )
        aux[i] = dados[i];
    delete []dados;
    dados = aux;
    capacidade += TAM_BLOCO;
}

template <class TIPO>
Pilha<TIPO>::~Pilha()
{
    if ( dados )
        delete []dados;
}
#endif
