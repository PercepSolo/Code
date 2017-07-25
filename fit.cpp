#include "Functions/globais.h"
#include "Functions/mlp.cpp"
#include "Functions/parser.cpp"

/*
	Autor: David Morosini, Gustavo Araújo
	2017

	Arquivo destinado ao treino da rede neural
*/

void exibe_vet_main(vet_int r, vect_data_culturas v_c);
void print_i(vet_int v);
void print_f(vet_float v);

int main(int argc, char * argv[]){
	srand(time(NULL));

	//argv[1] = nome do database das culturas
	//argv[2] = nome do database dos casos de treino

	if(argc == 4){
		//Ler as informações provindas das culturas cadastradas
		vect_data_culturas v = get_data_culturas(argv[1]);
		//Ler as informações provindas dos casos de treino
		vect_data v_data = get_data(argv[2]);
		
		input_rede inp(0, vet_float());
		saida_esperada sexp(0, vet_int());

		//criando os vetores de input e saidas esperadas, para serem postaspara treinamento
		for(int i = 0; i < v_data.size(); i++){
			vet_float v_aux = v_data[i].inputs;
			for(int j = 0; j < v.size(); j++){
				if(v_data[i].id == v[j].id){
					inp.push_back(v_aux);
					sexp.push_back(v[j].saida_esperada);
				}
			}
		}

		//camadas de neuronios e quantidades de neuronios
		vet_int init;
		//cada push_back é uma camada, e o valor cujo push_back foi dado
		//é a quantidade de neurônios daquela camada
		init.push_back(2);
		init.push_back(3);
		//camada de saida, tem a quantidade de neuronios referente a qtd de bits codificados
		init.push_back(v[0].qtd_bits);

		//iniciando a rede neural, com pesos aleatórios e os inputs como 0 menos o BIAS que vale -1 
		//cada neuronio tem seu BIAS
		mlp r = init_rede(init, v_data[0].inputs.size());

		//realiza o treinamento com argv[3] ciclos
		treinamento(&r.r, inp, sexp, atoi(argv[3]));

		int save;
		cout << "Digite 1 para salvar o Arquivo: ";
		if(scanf("%d", &save) && save){
			salvar_rede(r, (char *)"Classificadores/classificador.txt");
			cout << "Classificador salvo em Classificadores/classificador" << endl;
		}
	}else{
		cout << "Parametros incorretos!!" << endl;
		cout << "./[executavel] [nome Arquivo culturas] [nome arquivo treino] [numero de ciclos]" << endl;
	}
	
	return 0;	
}

void exibe_vet_main(vet_int r, vect_data_culturas v_c){
	cout << endl;
	for(int i = 0; i < v_c.size(); i++){
		bool flag = true;
		for(int j = 0; j < r.size(); j++){
			if(v_c[i].saida_esperada[j] != r[j]){
				flag = false;
			}
		}
		if(flag){
			cout << "Cultura recomendada: " << v_c[i].nome_cultura << endl;
			break;
		}
	}
}

void print_f(vet_float v){
	cout << endl;
	for(int i = 0; i < v.size(); i++){
		cout << "| " << v[i] << "\t";
	}
	cout << endl;
}

void print_i(vet_int v){
	cout << endl;
	for(int i = 0; i < v.size(); i++){
		cout << "| " << v[i] << "\t";
	}
	cout << endl;
}