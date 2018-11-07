#include "geral.h"
#include "cartao.h"
#include "viagens.h"
#include "comboios.h"
//#include "bilhetes.h"


using namespace std;


int BaseClientes::id = 0;


void menuInformacao(BaseClientes *r, Frota *f, Bilheteira *b);
void menuComCartao(BaseClientes *r, Bilheteira *b);
void menuSemCartao(BaseClientes *r, Bilheteira *b);


int main(){

	unsigned int menu = 0;

	BaseClientes r;
	Frota f;
	Bilheteira b;

	/*
	 * TESTING
	 *	TO-DO:  escrever e ler ficheiro, documentaçao doxygen
	 *			administraçao(adicionar comboios etc), validaçao inputs, devolver bilhetes,
	 *			ordenar vectores
	 */

	Comboio *c1 = new Intercidades (1, 200, 0.5, "c1");
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

	Datas datan(2222, 10, 5);
	Registo nn (&viagem25, "Nuno", "Estudante", &datan);
	r.adicionaRegisto(&nn);

	Datas *dviagem = new Datas (2018, 11, 9);
	Horas *hviagem = new Horas (00,25);

	Viagem *teste = new Viagem ("Porto", "Lisboa", 300.0, c1, dviagem, hviagem );
	Viagem *teste1 = new Viagem ("asdasd", "dddd", 300.5, c2, dviagem, hviagem );
	Viagem *teste2 = new Viagem ("Paaaa", "sssss", 20.0, c3, dviagem, hviagem );
	Viagem *teste3 = new Viagem ("dasda", "weawe", 50.7, c2, dviagem, hviagem );
	Viagem *teste4 = new Viagem ("Pfds", "ffads", 150.0, c4, dviagem, hviagem );
	Viagem *teste5 = new Viagem ("Pdfs", "asd", 1000.0, c5, dviagem, hviagem );
	Viagem *teste6 = new Viagem ("Porto", "dsf", 320.0, c1, dviagem, hviagem );
	b.adicionaViagem(teste);
	b.adicionaViagem(teste1);
	b.adicionaViagem(teste2);
	b.adicionaViagem(teste3);
	b.adicionaViagem(teste4);
	b.adicionaViagem(teste5);
	b.adicionaViagem(teste6);

	r.setId(0);
	Viagem *temp;
	temp = b.getViagem(0);
	temp->reservaBilhete();
	double precoFinal = temp->getPrecoFinal(r.getRegisto()->getCartao());
	Compra *tempC = new Compra( temp, r.getRegisto()->getCartao(), precoFinal, getDataActual(), getHoraActual() );
	r.getRegisto()->adicionaCompra(tempC);


	/*
	 * TESTING
	 *
	 *
	 */


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
			menuInformacao(&r, &f, &b);
			break;
		case 1:
			menuSemCartao(&r, &b);
			break;
		case 2:
			menuComCartao(&r, &b);
			break;
		default:
			return 0;
		}
	}
	return 0;
}

/*
 * Menus
 *
 *
 */

void menuInformacao(BaseClientes *r, Frota *f, Bilheteira *b){

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
			cout << f->getInformacao();
			break;
		case 1:
			cout << "Lista de Viagens" << endl << endl;
			cout << endl << b->getInfo();
			return;
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

void menuComCartao(BaseClientes *r, Bilheteira *b){
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

		if (!r->getRegisto()->getEstado()){
			char ans;
			cout << endl << "Subscricao desativada. Deseja re-ativar? (y/n)" << endl;
			cin >> ans;
			if (ans == 'y'){
				cout << endl << "Cartao re-ativado" << endl << endl;
				cout << "Escolha o tipo de cartao da nova subscricao" << endl;
				r->getRegisto()->alterarEstado(true);
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
		case 0:{
			int viagemId;
			double precoFinal;
			Viagem *temp;
			cout << "Lista de Viagens" << endl << endl;
			cout << endl << b->getInfo();
			cout << endl << "Escolha o id da viagem a reservar:";
			cin >> viagemId;
			cout << endl;
			temp = b->getViagem(viagemId);
			if (temp->reservaBilhete() == -1){
				cout << endl << "Este comboio já está cheio" << endl;
				break;
			}
			precoFinal = temp->getPrecoFinal(r->getRegisto()->getCartao());
			Compra *tempC = new Compra( temp, r->getRegisto()->getCartao(), precoFinal, getDataActual(), getHoraActual() );
			r->getRegisto()->adicionaCompra(tempC);
			cout << "Compra efectuada" << endl << endl;
			cout << "Preco Base = " << temp->getPrecoBase() << "€" << endl;
			cout << "Desconto = " <<temp->getPrecoBase() - precoFinal << "€"
					<< " (" << 100 - (precoFinal/temp->getPrecoBase() * 100) << "%)"<< endl;
			cout << "Preco Final = " << precoFinal << "€" << endl << endl;

			break;
		}
			break;
		case 1:

			break;
		case 2:{
			int cart;
			cout << "Tipo de Cartao: " << endl << endl;
			cout << r->getInfoCartao() << endl;
			cin >> cart;
			r->getRegisto()->alterarCartao(r->getCartao(cart));
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
			cout << endl <<"Historico de Viagens" << endl << endl;
			cout << r->getRegisto()->getHistorico() << endl;
			break;
		default:
			return;
		}

	}
}

void menuSemCartao(BaseClientes *r, Bilheteira *b){
	unsigned int menu = 0;
	int ano, mes, dia;
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
		case 0:{
			int viagemId;
			double precoFinal;
			Viagem *temp;
			cout << "Lista de Viagens" << endl << endl;
			cout << endl << b->getInfo();
			cout << endl << "Escolha o id da viagem a reservar:";
			cin >> viagemId;
			cout << endl;
			temp = b->getViagem(viagemId);
			if (temp->reservaBilhete() == -1){
				cout << endl << "Este comboio já está cheio" << endl;
				break;
			}
			precoFinal = temp->getPrecoFinal();
			cout << "Compra efectuada" << endl << endl;
			cout << "Preco Base = " << temp->getPrecoBase() << "€" << endl;
			cout << "Desconto = " <<temp->getPrecoBase() - precoFinal << "€"
					<< " (" << 100 - (precoFinal/temp->getPrecoBase() * 100) << "%)"<< endl;
			cout << "Preco Final = " << precoFinal << "€" << endl;


			return;
		}
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
			cin >> dia >> mes >> ano;
			Datas *datanasc = new Datas(ano, mes, dia);

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

Datas* getDataActual(){
	std::time_t t = std::time(0);
	std::tm* now = std::localtime(&t);
	Datas *temp = new Datas(now->tm_year+ 1900, now->tm_mon+1, now->tm_mday);
	return temp;
}

Horas* getHoraActual(){
	std::time_t t = std::time(0);
	std::tm* now = std::localtime(&t);
	Horas *temp = new Horas(now->tm_hour, now->tm_min);
	return temp;
}
