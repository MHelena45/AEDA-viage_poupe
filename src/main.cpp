#include <iostream>
#include "geral.h"
#include "cartao.h"
//#include "viagens.h"
#include "comboios.h"
//#include "bilhetes.h"
#include <iomanip>

using namespace std;


int BaseClientes::id = 0;


void menuInformacao(BaseClientes *r, Frota *f);
void menuComCartao(BaseClientes *r);
void menuSemCartao(BaseClientes *r);


int main(){

	unsigned int menu = 0;

	BaseClientes r;
	Frota f;

	//TESTING

	Comboio *c1 = new Intercidades (20, 200, 0.5, "c1");
	f.adicionaComboio(c1);
	Comboio *c2 = new Intercidades (30, 120 , 0.3, "c2");
	f.adicionaComboio(c2);
	Comboio *c3 = new AlfaPendular (50, 300, 0.7, "c3");
	f.adicionaComboio(c3);
	Comboio *c4 = new AlfaPendular (100, 50, 0.2, "c4");
	f.adicionaComboio(c4);
	Comboio *c5 = new Intercidades (1000, 10, 0.1, "c5");
	f.adicionaComboio(c5);

	Cartao viagem25 ("Viagem 25",39, 75);
	r.adicionaCartao(&viagem25);
	Cartao viagem50 ("Viagem 50",69, 50);
	r.adicionaCartao(&viagem50);
	Cartao viagem100 ("Viagem 100", 149, 0);
	r.adicionaCartao(&viagem100);


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
			menuInformacao(&r, &f);
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

// MENUS

void menuInformacao(BaseClientes *r, Frota *f){

	unsigned int menu = 0;

	while (menu != 5){
		while (true){
		cout << endl << "---Informacao---" << endl << endl;

		cout << endl << "0 - Lista de Comboios" << endl;
		cout << "1 - Lista de Viagens" << endl;
		cout << "5 - Sair" << endl;

		cin >> menu;
		if (cin.fail()){
			cin.clear();
			cin.ignore('\n',100);}
		else break;}

		switch (menu){
		case 0:
			cout << "Lista de Comboios" << endl << endl;
			cout << "Nome" << setw(7) << "Tipo" << setw(9) << "Lotacao" << setw(12) << "Velocidade" << setw(15) << "Preco por Km" << endl;
			for (unsigned int i = 0; i < f->Comboios.size();i++){
				cout << f->Comboios.at(i)->getNome() << setw(7) << f->Comboios.at(i)->getTipo() << setw(9) << f->Comboios.at(i)->getLotacao() << setw(8);
				cout <<	f->Comboios.at(i)->getVelocidade() << " km/h" << setw(12) << f->Comboios.at(i)->getPrecoKM() << "€" << endl;
			}
			break;
		case 1:

			break;
		case 2:

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

void menuComCartao(BaseClientes *r){
	unsigned int numRegs = r->getNumRegistos();
	unsigned int id= numRegs + 1;
	unsigned int menu = 0;
	bool skip = false;

	if (numRegs == 0) {
		cout << endl << "Nao existem registos" << endl;
		return;
	}



	while (id >= numRegs){
		cout << "ID do seu cartao: ";
		cin >> id;
		if (cin.fail()){
			cin.clear();
			cin.ignore('\n',100);
			continue;
		}
		if (id >= numRegs){
			cout << endl << "ID Invalido, tente outra vez" << endl;
		}
	}
	r->setId(id);



	while (menu != 6){

		cout << endl << "---Passageiro Com Cartao---" << endl << endl;

		cout << "ID: " << id << endl << endl;
		cout << r->getInformacao();

		if (!r->getEstado()){
			char ans;
			cout << endl << "Subscricao desativada. Deseja re-ativar? (y/n)" << endl;
			cin >> ans;
			if (ans == 'y'){
				cout << endl << "Cartao re-ativado" << endl << endl;
				cout << "Escolha o tipo de cartao da nova subscricao" << endl;
				r->alterarEstado(true);
				menu = 2;
				skip = true;
			}
			else return;
		}

		while (true){
			if (!skip){
				cout << endl << "0 - Comprar Bilhete" << endl;
				cout << "1 - Devolver Bilhete" << endl;
				cout << "2 - Alterar cartao subscrito" << endl;
				cout << "3 - Remover subscricao" << endl;
				cout << "4 - Re-ativar subscricao" << endl;
				cout << "5 - Historico de Viagens" << endl;
				cout << "6 - Sair" << endl;

				cin >> menu;
				if (cin.fail()){
					cin.clear();
					cin.ignore('\n',100);
				}
				else break;
			}
			else break;
		}
	switch (menu){
		case 0:

			break;
		case 1:

			break;
		case 2:{
			int cart;
			cout << "Tipo de Cartao: " << endl << endl;
			cout << r->getInfoCartao() << endl;;
			cin >> cart;
			r->alterarCartao(r->getCartao(cart));
			cout << endl << "Cartao alterado para \"" << r->getCartao(cart)->getNome() << "\"" << endl;
			return;
		}

			break;
		case 3:{
			r->removeRegisto();
			cout << endl << "Registo removido" << endl;
			return;
		}
		case 4:

			break;
		case 5:

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
		case 2:{
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
			cout << r->getInfoCartao() << endl;;
			cin >> cart;
			Registo *temp = new Registo(r->getCartao(cart), nome, profissao, datanasc);
			r->adicionaRegisto(temp);
			cout << endl << "Cartao registado, o seu ID e: " << r->getNumRegistos() -1 << endl;
			return;
		}
		case 3:
			break;
		case 5:
			return;
		default:
			return;
		}
	}
}
