#include "geral.h"
#include "bilheteira.h"
#include "cartao.h"
#include "viagens.h"
#include "comboios.h"

using namespace std;


void menuInformacao(BaseClientes *r, Frota *f, Bilheteira *b);
void menuComCartao(BaseClientes *r, Bilheteira *b);
void menuSemCartao(BaseClientes *r, Bilheteira *b);
void menuAdministracao(BaseClientes *r, Frota *f, Bilheteira *b);


/*
 * TO-DO: Relatorio, Doxygen, adicionar comboios/cartoes/viagens, excep�oes/validar inputs
 * 			verificar se existem viagens ao comprar bilhete
 *
 *
 */


int main(){

	unsigned int menu = 0;

	BaseClientes r;
	Frota f;
	Bilheteira b(&f);

	while (menu != 5){
		while (true){
		cout << endl << "---MENU INICIAL---" << endl << endl;
		cout << "0 - Informacao" << endl;
		cout << "1 - Passageiro sem cartao" << endl;
		cout << "2 - Passageiro com cartao" << endl;
		cout << "3 - Administracao" << endl;
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
		case 3:
			menuAdministracao(&r, &f, &b);
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

//				ADMINISTRACAO

void menuAdministracao (BaseClientes *r, Frota *f, Bilheteira *b){

	unsigned int menu = 0;

		while (menu != 5){
			while (true){
			cout << endl << "---Administracao---" << endl << endl;

			cout << endl << "0 - Guardar Dados" << endl;
			cout << "1 - Carregar Dados" << endl;
			cout << "2 - Adicionar Comboios" << endl;
			cout << "3 - Adicionar Cartoes" << endl;
			cout << "4 - Adicionar Viagens" << endl;

			cout << "5 - Sair" << endl;

			cin >> menu;
			if (cin.fail()){
				cin.clear();
				cin.ignore('\n',100);}
			else break;}

			switch (menu){
			case 0:{

				f->saveComboios();
				r->saveCartoes();
				r->saveRegistos();
				b->saveViagens();

				break;
			}
			case 1:{
				f->loadComboios();
				r->loadCartoes();
				r->loadRegistos();
				b->loadViagens();
				break;

				}

			case 2: {//falta verificar se o comboio ja existe
				int lotacao, velocidade;
				double precoKM;
				string nome, tipo;
				Comboio *c;
				while (true){
					cout<<endl<<"Introduza a informação do comboio (lotacao, velocidade, precoKM, nome, tipo)"<<endl;
					cin>>lotacao>> velocidade>> precoKM>> nome>> tipo;
					if (cin.fail()){
						cin.clear();
						cin.ignore('\n',100);
						cout<<"Invalid input."<<endl;}
					else if (lotacao>0 && velocidade>0 && precoKM>0 && (tipo=="IC" || tipo== "AP"))
						break;
					else cout<<"Invalid input."<<endl;
				}
				if (tipo == "IC")
					c = new Intercidades (lotacao, velocidade, precoKM, nome);
				else c = new AlfaPendular (lotacao, velocidade, precoKM, nome);
					f->adicionaComboio(c);


			break;
			}
			case 3: {


				//Adicionar Cartoes

				break;
			}

			case 4:{

				//Adicionar Viagens (Listar Comboios, para escoher o comboio)

				break;
			}

			case 5:
				return;

			default:
				return;
			}
		}
}

//			INFORMACAO

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

//				MENU UTILIZADORES REGISTADOS

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
			if (temp->reservaBilhete(true) == -1){
				cout << endl << "Este comboio j� est� cheio" << endl;
				break;
			}
			precoFinal = temp->getPrecoFinal(r->getRegisto()->getCartao());
			Compra *tempC = new Compra( temp, r->getRegisto()->getCartao(), precoFinal, getDataActual(), getHoraActual() );
			r->getRegisto()->adicionaCompra(tempC);
			cout << "Compra efectuada" << endl << endl;
			cout << "Preco Base = " << temp->getPrecoBase() << "�" << endl;
			cout << "Desconto = " <<temp->getPrecoBase() - precoFinal << "�"
					<< " (" << 100 - (precoFinal/temp->getPrecoBase() * 100) << "%)"<< endl;
			cout << "Preco Final = " << precoFinal << "�" << endl << endl;

			break;
		}
			break;
		case 1:{
			int compraId;
			vector <Compra *> cmps = r->getRegisto()->getCompraAtiva();
			cout << "Bilhetes nao usados" << endl << endl;
			cout << r->getRegisto()->listCompraActiva() << endl;

			cout << "Escolha o bilhete a devolver:";
			cin >> compraId;
			cout << endl;

			cmps.at(compraId)->getViagem()->devolveBilhete(true);
			r->getRegisto()->eliminaCompra(cmps.at(compraId));

			cout << "Bilhete devolvido" << endl << endl;

			break;
		}
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

//					MENU UTILIZADORES ANONIMOS

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
		cout << "3 - Sair" << endl;

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
			if (temp->reservaBilhete(false) == -1){
				cout << endl << "Este comboio j� est� cheio" << endl;
				break;
			}
			precoFinal = temp->getPrecoFinal();
			cout << "Compra efectuada" << endl << endl;
			cout << "Preco Base = " << temp->getPrecoBase() << "�" << endl;
			cout << "Desconto = " <<temp->getPrecoBase() - precoFinal << "�"
					<< " (" << 100 - (precoFinal/temp->getPrecoBase() * 100) << "%)"<< endl;
			cout << "Preco Final = " << precoFinal << "�" << endl;


			return;
		}
		case 1:
			int viagemId;
			Viagem *temp;
			cout << "Lista de Viagens" << endl << endl;
			cout << endl << b->getInfo();
			cout << endl << "Escolha o id da viagem a cancelar:";
			cin >> viagemId;
			cout << endl;
			temp = b->getViagem(viagemId);
			if (temp->devolveBilhete(false) == -1){
				cout << "Nao existem bilhetes sem registo para esta viagem" << endl;
				break;
			}
			cout << endl << "Bilhete devolvido" << endl;




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
