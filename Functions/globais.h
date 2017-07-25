#ifndef GLOBAIS_H
#define GLOBAIS_H

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <cmath>
#include <cstdio>

using namespace std;

#define MAX_RANGE 100
#define BIAS -1.0
#define TAXA_APRENDIZADO 0.15
#define MOMENTUM 1
#define TAM_NOME 50



//////////////////////////  REDE NEURAL
typedef struct Neuronio neuronio;
typedef struct MLP mlp;
typedef vector<int> args_init;
typedef vector<neuronio> layer;
typedef vector<layer> rede;


//input para treinamento da rede
typedef vector<float> vet_float;
typedef vector<vet_float > input_rede;
typedef int t_data;
typedef vector<t_data> vet_int;
typedef vector<vet_int > saida_esperada;


//neuronio
struct Neuronio{
	float erro, sinal, e;
	vet_float pesos, inputs;
};

struct MLP{
	rede r;
};


////////////////////////////// ESTRUTURAS DE DADOS
typedef struct Database data;
typedef struct DatabaseCulturas data_culturas;
typedef vector<data> vect_data;
typedef vector<data_culturas> vect_data_culturas;

struct Database{
	vet_float inputs; 
	int id;
};

struct DatabaseCulturas{
	int id, qtd_bits;
	char nome_cultura[TAM_NOME];
	vet_int saida_esperada;
};





#endif