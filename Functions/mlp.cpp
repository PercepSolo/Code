#include "globais.h"


/*
	Funcao de ativação do neuronio
*/
float funcao_ativacao(float num){
	return (1 / (1 + pow(M_E, -num)));
}

/*
	Funcao correspondente a derivada da funcao de ativação
*/
float funcao_derivada(float valor){
	return (valor * (1 - valor));
}

/*
	Usada para inicializar os pesos dos inputs
*/
float gera_num_entre_0_1(void){
	return (float)(rand()%(MAX_RANGE + 1)) / (float)MAX_RANGE;
}

void new_neronio(neuronio * n, int qtd_entradas){
	(* n).erro = 0;
	(* n).sinal = 0;
	//a primeira posicao é sempre ocupada pelo BIAS
	(* n).inputs.push_back(BIAS);
	(* n).pesos.push_back(gera_num_entre_0_1());
	//ambos os inputs são inicializados com peso aleatorio e 0 de entrada
	for(int i = 1; i <= qtd_entradas; i++){
		(* n).inputs.push_back(0);
		(* n).pesos.push_back(gera_num_entre_0_1());
	}
	
}


mlp init_rede(vet_int args, int qtd_inputs){
	mlp nova;
	nova.r = vector<layer>(args.size());
	//o tamanho do vector significa a quantidade de camadas, e cada numero representa a quantidade de neuronios
	for(int i = 0; i < nova.r.size(); i++){
		nova.r[i] = vector<neuronio>(args[i]);
		int qtd_inputs_aux = qtd_inputs;
		if(i != 0){
			qtd_inputs_aux = nova.r[i - 1].size();
		}

		for(int j = 0; j < (nova.r[i]).size(); j++){
			new_neronio(&(nova.r[i])[j], qtd_inputs_aux);
		}
		
	}
	return nova;
}

//funcao para relaizar treinamento
void propaga_sinal(rede * r, vet_float input, vet_int s_esp){

	//setando a primeira camada
	//entrada
	for(int j = 0; j < (*r)[0].size(); j++){
		for(int i = 0; i < input.size(); i++){
			//posicao 0 é sempre o BIAS
			((*r)[0])[j].inputs[i + 1] = input[i];
		}
	}


	float sum;
	vet_int resp;
	for(int i = 0; i < (*r).size(); i++){
		for(int j = 0; j < (*r)[i].size(); j++){
			sum = 0;
			for(int k = 0; k < ((*r)[i])[j].inputs.size(); k++){
				sum += ((*r)[i])[j].pesos[k] * ((*r)[i])[j].inputs[k];
			}
			((*r)[i])[j].sinal = funcao_ativacao(sum);
			((*r)[i])[j].e = sum;
			if(i < (*r).size() - 1){
				for(int l = 0; l < (*r)[i + 1].size(); l++){
					((*r)[i + 1])[l].inputs[j + 1] = ((*r)[i])[j].sinal;
				}
			}
		}	

	}

	for(int i = 0; i < (*r)[(*r).size() - 1].size(); i++){
		((*r)[(*r).size() - 1])[i].erro = (float)s_esp[i] - ((*r)[(*r).size() - 1])[i].sinal;
	}
}

void retropropaga_erro(rede * r){
	float erro;
	//percorrer todas as camadas 
	for(int i = (*r).size() - 1; i > 0; i--){
		//+1 por causa do BIAS
		//de cada camada percorrer todos os neuronios, comecando da ultima camada
		//para retropropagar o erro do fim para o inicio
		for(int j = 0; j < ((*r)[i - 1]).size(); j++){
			erro = 0;
			for(int k = 0; k < (*r)[i].size(); k++){
				//erro += ((*r)[i])[k].inputs[j] * ((*r)[i])[k].pesos[j];
				erro += ((*r)[i])[k].erro * ((*r)[i])[k].pesos[j];
			}
			//mapeando o erro atual, dos inputs que representando o neuronio atual
			((*r)[i - 1])[j].erro = erro;
		}	
	}
}


void reajusta_pesos(rede * r){
	for(int i = 0; i < (* r).size(); i++){
		for(int j = 0; j < (*r)[i].size(); j++){
			for(int k = 0; k < ((*r)[i])[j].inputs.size(); k++){
				float aux = ((*r)[i])[j].erro * funcao_derivada(((*r)[i])[j].sinal);
     			((*r)[i])[j].pesos[k] += TAXA_APRENDIZADO * aux * ((*r)[i])[j].inputs[k];
			}
		}
	}

}





void treinamento(rede * r, input_rede input, saida_esperada s_esp, int ciclos){
	int i = 0;
	while(i < ciclos){
		//treinando com todos os exemplos vindos
		for(int j = 0; j < s_esp.size(); j++){
			propaga_sinal(r, input[j], s_esp[j]);
			retropropaga_erro(r);
			reajusta_pesos(r);

			//cout << "#################################################################################" << endl;
			//exibe_rede2(*r);
		}
		i++;
	}
}

vet_int run(mlp rede, vet_float e){
	
	//posiciona os dados da entrada no inicio da rede
	for(int j = 0; j < rede.r[0].size(); j++){
		for(int i = 1; i <= e.size(); i++){
			(rede.r[0])[j].inputs[i] = e[i - 1];
		}
	}

	float sum;
	vet_int resp;
	for(int i = 0; i < rede.r.size(); i++){
		for(int j = 0; j < rede.r[i].size(); j++){
			sum = 0;
			for(int k = 0; k < (rede.r[i])[j].inputs.size(); k++){
				sum += (rede.r[i])[j].pesos[k] * (rede.r[i])[j].inputs[k];
			}
			(rede.r[i])[j].sinal = funcao_ativacao(sum);
			(rede.r[i])[j].e = sum;
			if(i < rede.r.size() - 1){
				for(int l = 0; l < rede.r[i + 1].size(); l++){
					(rede.r[i + 1])[l].inputs[j + 1] = (rede.r[i])[j].sinal;
				}
			}
		}	

	}

	sum = 0;
	for(int i = 0; i < rede.r[rede.r.size() - 1].size(); i++){
		if((rede.r[rede.r.size() - 1])[i].sinal > 0.5){
			resp.push_back(1);
		}else{
			resp.push_back(0);
		}
	}
	return resp;
}

void salvar_rede(mlp r, char * path){
	FILE * arq = fopen(path, "w");
	if(arq != NULL){
		//quantidade de camadaa
		int qtd_Camadas = r.r.size(); 
		fprintf(arq, "%i\n", qtd_Camadas);
		for(int i = 0; i < r.r.size(); i++){
			int qtd_neuronios = r.r[i].size(); 
			fprintf(arq, "%i\n", qtd_neuronios);
			for(int j = 0; j < r.r[i].size(); j++){
				int qtd_pesos = (r.r[i])[j].pesos.size();
				fprintf(arq, "%d\n", qtd_pesos);
				for(int k = 0; k < qtd_pesos; k++){
					fprintf(arq, "%f\n", (r.r[i])[j].pesos[k]);
				}
			}
			
		}
		fclose(arq);
	}
}




mlp get_mlp(char * path){
	FILE * arq = fopen(path, "r");
	mlp r;
	if(arq != NULL){
		int qtd_Camadas, qtd_neuronios, qtd_inputs;
		fscanf(arq, "%d", &qtd_Camadas);
		r.r = vector<layer>(qtd_Camadas);
		for(int i = 0; i < qtd_Camadas; i++){
			fscanf(arq, "%d", &qtd_neuronios);
			r.r[i] = vector<neuronio>(qtd_neuronios);
			for(int j = 0; j < qtd_neuronios; j++){
				fscanf(arq, "%d", &qtd_inputs);
				new_neronio(&(r.r[i])[j], qtd_inputs);
				for(int k = 0; k < qtd_inputs; k++){
					float aux;
					fscanf(arq, "%f", &aux);
					(r.r[i])[j].pesos[k] = aux;
				}
			}
		}
	}
	return r;
}

