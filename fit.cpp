#include "Functions/globais.h"
#include "Functions/mlp.cpp"
#include "Functions/parser.cpp"

void exibe_vet_main(vet_int r, vect_data_culturas v_c);
void print_i(vet_int v);
void print_f(vet_float v);

int main(int argc, char * argv[]){
	srand(time(NULL));

	vect_data_culturas v = get_data_culturas((char *)"Databases/database_culturas.txt");
	vect_data v_data = get_data((char *)"Databases/db_trainvalid.txt");

	/*for(int k = 0; k < v_data.size(); k++){
			print_f(v_data[k].inputs);
	}*/
	
	input_rede inp(0, vet_float());
	saida_esperada sexp(0, vet_int());

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
	init.push_back(2);
	//init.push_back(5);
	//init.push_back(3);
	//init.push_back(5);
	//camada de saida, tem a quantidade de neuronios referente a qtd de bits codificados
	init.push_back(v[0].qtd_bits);

	

	mlp r = init_rede(init, v_data[0].inputs.size());

	treinamento(&r.r, inp, sexp, 20000);
/*
	vet_float ee;
	//0.3 0.3 0.3 0.6 0.9 4
	ee.push_back(0.6);
	ee.push_back(0.267);
	ee.push_back(0.3102);
	ee.push_back(0.3098);
	//ee.push_back(0.589);
	ee.push_back(0.922);


	vet_int x = run(r, ee);

	exibe_vet_main(x, v);
	print_i(x);

	//0.8 0.6 0.2 0.8 0.1 2

	vet_float eee;
	eee.push_back(0.8);
	eee.push_back(0.8);
	eee.push_back(0.6);
	eee.push_back(0.2);
	//eee.push_back(0.8);
	eee.push_back(0.1);


	vet_int xx = run(r, eee);

	exibe_vet_main(xx, v);
	print_i(xx);



	//0.1 0.2 0.25 0.36 0.4 1

	vet_float e;
	e.push_back(0.83);
	e.push_back(0.1);
	e.push_back(0.23);
	e.push_back(0.16);
	//e.push_back(0.41);
	e.push_back(0.4);


	vet_int xxx = run(r, e);

	exibe_vet_main(xxx, v);
	print_i(xxx);

	//0.5 0.7 0.5 0.1 0.2 0
	vet_float teste;
	teste.push_back(0.27);
	teste.push_back(0.549);
	teste.push_back(0.6987);
	teste.push_back(0.5002);
	//teste.push_back(0.09);
	teste.push_back(0.2134);


	vet_int u = run(r, teste);

	exibe_vet_main(u, v);
	print_i(u);
	*/
	int a;
	cout << "Salvar arquivo? " << endl;
	if(scanf("%d", &a) && a){
		salvar_rede(r, (char *)"Classificadores/c_teste.txt");
		cout << "Classificador salvo em Classificadores/" << endl;
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



/*input_rede inp(1, vet_float());
	saida_esperada sexp(1, vet_int());

	vet_float e;
	e.push_back(1.2);
	e.push_back(1.4);
	e.push_back(0.7);
	e.push_back(1.32);

	inp[0] = e;

	e.clear();
	e.push_back(2.3);
	e.push_back(0.0);
	e.push_back(1.23);
	e.push_back(5.7);

	inp.push_back(e);



	vet_int saida_esperada;
	saida_esperada.push_back(0);
	saida_esperada.push_back(1);
	saida_esperada.push_back(0);
	saida_esperada.push_back(0);
	saida_esperada.push_back(1);

	sexp[0] = saida_esperada;

	saida_esperada.clear();
	saida_esperada.push_back(1);
	saida_esperada.push_back(0);
	saida_esperada.push_back(0);
	saida_esperada.push_back(1);
	saida_esperada.push_back(1);

	sexp.push_back(saida_esperada);


	//camadas de neuronios e quantidades de neuronios
	vet_int init;
	init.push_back(2); 
	init.push_back(3);
	init.push_back(4);
	//camada de saida
	init.push_back(saida_esperada.size());

	

	mlp rede = init_rede(init, e.size());

	
	treinamento(&rede.r, inp, sexp, 10000);

	vet_float ee;
	ee.push_back(1.5);
	ee.push_back(1.2);
	ee.push_back(1.0);
	ee.push_back(0.95);

	vet_float x = run(rede, ee);

	exibe_vet_main(x);

	vet_float eee;
	eee.push_back(2.0);
	eee.push_back(0.3);
	eee.push_back(1.4);
	eee.push_back(4.96);

	vet_float xy = run(rede, eee);

	exibe_vet_main(xy);*/