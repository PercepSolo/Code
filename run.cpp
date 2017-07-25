#include "Functions/globais.h"
#include "Functions/mlp.cpp"
#include "Functions/parser.cpp"

/*
	Autor: David Morosini, Gustavo Araújo
	2017

	Arquivo destinado ao teste do classificador gerado pela rede neural
*/

vector<vet_float> coleta_teste(void);
void exibe_vet_main(vet_int r, vect_data_culturas v_c);

int main(int argc, char * argv[]){

	//argv[1] = nome do database das culturas
	//argv[2] = nome do classificador  

	if(argc == 3){

		//carregando as instancias do database das culturas 
		//para que o resultado seja em forma textual
		vect_data_culturas v_c = get_data_culturas(argv[1]);

		//carregando o arquivo com o classificador previamente
		//gerado pelo arquivo fit.cpp
		mlp r = get_mlp(argv[2]);
		//os arquivos de teste serão redirecionados pela entrada padrão
		//função para pegar os dados de teste
		vector<vet_float> v = coleta_teste();
		
		//realizando o teste dos dodados
		for(int i = 0; i < v.size(); i++){
			vet_int u = run(r, v[i]);
			exibe_vet_main(u, v_c);
		}
	}else{
		cout << "Parametros incorretos!!" << endl;
		cout << "./[executavel] [nome Arquivo culturas] [nome arquivo classificador] < [arquivo de exemplos]" << endl;
	}


	return 0;
}

vector<vet_float> coleta_teste(void){
	int qtd_testes, qtd_colunas;
	scanf("%d %d", &qtd_testes, &qtd_colunas);
	vector<vet_float> resp(0, vet_float());
	for(int i = 0; i < qtd_testes; i++){
		vet_float v;
		for(int j = 0; j < qtd_testes; j++){
			float aux;
			scanf("%f", &aux);
			v.push_back(aux);
		}
		resp.push_back(v);
	}
	return resp;
}

//pesquisando na base de dados e exibindo a cultura correta
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