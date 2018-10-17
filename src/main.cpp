#include <iostream>
#include "geral.h"
#include "cartao.h"
/*#include "viagens.h"
#include "comboios.h"
#include "bilhetes.h"*/

using namespace std;

void menuInformacao(BaseClientes *r);
void menuComCartao(BaseClientes *r);
void menuSemCartao(BaseClientes *r);
int BaseClientes::id = 0;

void menuInformacao(BaseClientes *r){

}
void menuComCartao(BaseClientes *r){
	unsigned int id;
	unsigned int menu = 0;
	datas datan;

	while (true){
	cout << "ID do seu cartao: ";
	cin >> id;
	if (cin.fail()){
		cin.clear();
		cin.ignore('\n',100);}
	else break;}
	r->setId(id);
	datan = r->getDataNascimento();

	while (menu != 5){

		cout << endl << "---Passageiro Com Cartao---" << endl << endl;

		cout << "ID: " << id << endl;
		cout << "Nome: " << r->getNome();
		cout << "; Profissao: " << r->getProfissao();
		cout << "; Data de Nascimento: " << datan.dia << "-" << datan.mes << "-"<<datan.ano << endl;

		while (true){
		cout << endl << "0 - Comprar Bilhete" << endl;
		cout << "1 - Devolver Bilhete" << endl;
		cout << "2 - Alterar cartao subscrito" << endl;
		cout << "3 - Remover subscricao" << endl;
		cout << "4 - Historico de Viagens" << endl;
		cout << "5 - Sair" << endl;

		cin >> menu;
		if (cin.fail()){
			cin.clear();
			cin.ignore('\n',100);}
		else break;}

	switch (menu){
		case 0:

			break;
		case 1:

			break;
		case 2:

			break;
		case 3:

			break;
		case 4:

			break;
		default:
			return;
		}

	}
}

void menuSemCartao(BaseClientes *r){
	unsigned int menu = 0;
	datas datanasc;
	int cart;
	string nome;
	string profissao;
	Cartao viagem25 ("Viagem 25",39, 0.75);
	Cartao viagem50 ("Viagem 50",69, 0.50);
	Cartao viagem100 ("Viagem 100", 149, 0.0);


	while (menu != 5){
		while (true){
		cout << endl << "---Passageiro sem Cartao---" << endl << endl;

		cout << endl << "0 - Comprar Bilhete" << endl;
		cout << "1 - Devolver Bilhete" << endl;
		cout << "2 - Subscrever a um cartao" << endl;
		cout << "5 - Sair" << endl;

		cin >> menu;
		if (cin.fail()){
			cin.clear();
			cin.ignore('\n',100);}
		else break;}

		switch (menu){
		case 0:

			break;
		case 1:

			break;
		case 2:
			cin.ignore();
			cin.clear();
			cout << endl << "---Subscricao de cartao---" << endl << endl;
			cout << "Nome: ";
			getline(cin, nome);
			cout << endl << "Profissao: ";
			getline(cin,profissao);
			cout << endl << "Data de Nascimento(DD MM AAAA): ";
			cin >> datanasc.dia >> datanasc.mes >> datanasc.ano;

			cout << "Tipo de Cartao: " << endl << endl;
			cout << "0 - Viagem 25, Custo: " << viagem25.getPreco() << "�/mes"<< ", Desconto: " << 100 - (viagem25.getDesconto() * 100) << "% por viagem"<< endl;
			cout << "1 - Viagem 50, Custo: " << viagem50.getPreco() << "�/mes"<< ", Desconto: " << 100 - (viagem50.getDesconto() * 100) << "% por viagem"<< endl;
			cout << "2 - Viagem 100, Custo: " << viagem100.getPreco() << "�/mes"<< ", Desconto: " <<100 - (viagem100.getDesconto() * 100) << "% por viagem"<< endl;
			cin >> cart;

			if (cart == 0){
				Registo temp(&viagem25, nome, profissao, datanasc);
				r->adicionaRegisto(temp);
			}
			else if (cart == 1){
				Registo temp(&viagem50, nome, profissao, datanasc);
				r->adicionaRegisto(temp);

			}
			else {
				Registo temp(&viagem25, nome, profissao, datanasc);
				r->adicionaRegisto(temp);
			}

			cout << endl << "Cartao registado, o seu ID e: " << r->getNumRegistos() -1 << endl;
			return;
		case 3:

			break;
		case 5:
			return;
		default:
			return;
		}
	}
}


int main(){

	unsigned int menu = 0;
	BaseClientes r;


	while (menu != 5){
		while (true){
		cout << endl << "---MENU INICIAL---" << endl << endl;
		cout << "0 - Informacao" << endl;
		cout << "1 - Passageiro sem cartao" << endl;
		cout << "2 - Passageiro com cartao" << endl;
		cout << "5 - Sair" << endl;

		cin >> menu;
		if (cin.fail()){
			cin.clear();
			cin.ignore('\n',100);}
		else break;}

		switch (menu){
		case 0:
			menuInformacao(&r);
			break;
		case 1:
			menuSemCartao(&r);
			break;
		case 2:
			menuComCartao(&r);
			break;
		default:
			return 0;
		}
	}
	return 0;
}
