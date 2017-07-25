#include "globais.h"

vect_data_culturas get_data_culturas(char * path){
	FILE * arq = fopen(path, "r");
	vect_data_culturas vet;
	if(arq != NULL){
		int qtd_culturas, qtd_bits;
		fscanf(arq, "%d %d", &qtd_culturas, &qtd_bits);
		for(int i = 0; i < qtd_culturas; i++){
			data_culturas d;
			d.qtd_bits = qtd_bits;
			fscanf(arq, "%d %s", &d.id, d.nome_cultura);
			//pego os atribs anteriores
			for(int j = 0; j < qtd_bits; j++){
				int valor;
				fscanf(arq, "%d", &valor);
				d.saida_esperada.push_back(valor);
			}
			vet.push_back(d);
		}
		fclose(arq);
	}
	return vet; 
}

vect_data get_data(char * path){
	FILE * arq = fopen(path, "r");
	vect_data vet;
	if(arq != NULL){
		int qtd_exemplos, qtd_colunas;
		fscanf(arq, "%d %d", &qtd_exemplos, &qtd_colunas);
		for(int i = 0; i < qtd_exemplos; i++){
			data d;
			//a ultima coluna é o ID
			for(int j = 0; j < (qtd_colunas - 1); j++){
				float v_aux;
				fscanf(arq, "%f", &v_aux);
				d.inputs.push_back(v_aux);
			}
			fscanf(arq, "%d", &d.id);
			vet.push_back(d);
		}
	}
	return vet;
}

