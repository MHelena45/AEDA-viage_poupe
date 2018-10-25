#include <iostream>
#include <iomanip>
#include "geral.h"
#include "cartao.h"
#include "comboios.h"
//#include "viagens.h"
//#include "bilhetes.h"

using namespace std;

void menuInformacao(BaseClientes *r, Frota *f);
void menuComCartao(BaseClientes *r);
void menuSemCartao(BaseClientes *r);
int BaseClientes::id = 0;

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
			cout << "0 - Viagem 25, Custo: " << viagem25.getPreco() << "ï¿½/mes"<< ", Desconto: " << 100 - (viagem25.getDesconto() * 100) << "% por viagem"<< endl;
			cout << "1 - Viagem 50, Custo: " << viagem50.getPreco() << "ï¿½/mes"<< ", Desconto: " << 100 - (viagem50.getDesconto() * 100) << "% por viagem"<< endl;
			cout << "2 - Viagem 100, Custo: " << viagem100.getPreco() << "ï¿½/mes"<< ", Desconto: " <<100 - (viagem100.getDesconto() * 100) << "% por viagem"<< endl;
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
