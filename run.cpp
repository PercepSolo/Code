#include "Functions/globais.h"
#include "Functions/mlp.cpp"
#include "Functions/parser.cpp"

vector<vet_float> coleta_teste(void);
void exibe_vet_main(vet_int r, vect_data_culturas v_c);

int main(int argc, char * argv[]){
	if(argc != 2){
		cout << ".run [arq classificador]" << endl;
	}else{
		vect_data_culturas v_c = get_data_culturas((char *)"Databases/database_culturas.txt");

		mlp r = get_mlp(argv[1]);
		vector<vet_float> v = coleta_teste();
		
		for(int i = 0; i < v.size(); i++){
			vet_int u = run(r, v[i]);
			exibe_vet_main(u, v_c);
		}

		//vet_int u = run(r, v[1]);
		//exibe_vet_main(u, v_c);


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