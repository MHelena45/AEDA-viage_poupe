#include "geral.h"
#include "bilheteira.h"
#include "cartao.h"
#include "viagens.h"
#include "comboios.h"
#include <limits>

using namespace std;


void menuInformacao(BaseClientes *r, Frota *f, Bilheteira *b);
void menuComCartao(BaseClientes *r, Bilheteira *b);
void menuSemCartao(BaseClientes *r, Bilheteira *b);
void menuAdministracao(BaseClientes *r, Frota *f, Bilheteira *b);


/*
 * TODO: Relatorio, Doxygen, adicionar comboios/cartoes/viagens
 *
 *
 */


int main(){

	unsigned int menu = 5;

	BaseClientes r;
	Frota f;
	Bilheteira b(&f);

	while (menu != 4){
		while (cin.fail() || menu > 4){

			if (cin.fail()){
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Input Invalido tente outra vez" << endl;
			}
			cout << endl << "---MENU INICIAL---" << endl << endl;
			cout << "0 - Informacao" << endl;
			cout << "1 - Passageiro sem cartao" << endl;
			cout << "2 - Passageiro com cartao" << endl;
			cout << "3 - Administracao" << endl;
			cout << "4 - Sair" << endl;

		cin >> menu;
		if (menu > 4)
			cout << "Menu nao existe, tente outra vez" << endl;
		}

		switch (menu){
		case 0:
			menuInformacao(&r, &f, &b);
			menu = 5;
			break;
		case 1:
			menuSemCartao(&r, &b);
			menu = 5;
			break;
		case 2:
			menuComCartao(&r, &b);
			menu = 5;
			break;
		case 3:
			menuAdministracao(&r, &f, &b);
			menu = 5;
			break;
		case 4:
			return 0;
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

	unsigned int menu = 6;

		while (menu != 5){
			while (cin.fail() || menu > 5){
				if (cin.fail()){
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Input Invalido tente outra vez" << endl;
				}
			cout << endl << "---Administracao---" << endl << endl;

			cout << endl << "0 - Guardar Dados" << endl;
			cout << "1 - Carregar Dados" << endl;
			cout << "2 - Adicionar Comboios" << endl;
			cout << "3 - Adicionar Cartoes" << endl;
			cout << "4 - Adicionar Viagens" << endl;

			cout << "5 - Sair" << endl;

			cin >> menu;
			if (menu > 5)
				cout << "Menu nao existe, tente outra vez" << endl;
			}

			switch (menu){
			case 0:{

				f->saveComboios();
				r->saveCartoes();
				r->saveRegistos();
				b->saveViagens();
				cout << endl <<"Dados Gravados" << endl;
				return;
			}
			case 1:{
				f->loadComboios();
				r->loadCartoes();
				r->loadRegistos();
				b->loadViagens();
				cout << endl <<"Dados Carregados" << endl;
				return;

				}

			case 2: {//verificacao de erros nao funciona muito bem quando tentas por string
				int lotacao, velocidade;
				double precoKM;
				string nome, tipo;
				bool existe;
				Comboio *c;
				while (true){
					existe=false;
					cout<<endl<<"Introduza a informacao do comboio (lotacao, velocidade, precoKM, nome, tipo):"<<endl;
					cin>>lotacao>> velocidade>> precoKM>> nome>> tipo;
					if (cin.fail()){
						cin.clear();
						cin.ignore('\n',100);
						cout<<"Invalid input."<<endl;}
					else if (lotacao<0 || velocidade<0 || precoKM<0 || (tipo!="IC" && tipo!= "AP"))
						cout<<"Invalid input."<<endl;
					else {
						for (int i=0;i<f->getNumComboios();i++)
							if (f->getComboio(i)->getNome()==nome)
								existe=true;
					
						if (!existe) break;
						else cout<<"Ja existe um comboio com esse nome."<<endl;}
				}
				if (tipo == "IC")
					c = new Intercidades (lotacao, velocidade, precoKM, nome);
				else c = new AlfaPendular (lotacao, velocidade, precoKM, nome);
				f->adicionaComboio(c);


			break;
			}
			case 3: {//verificacao de erros nao funciona muito bem quando tentas por string para pre√ßo ou desconto
				float precoMensal;
				int desconto;
				string nome;
				while (true){
					cout <<endl<< "Introduza a informacao do cartao(nome, preco mensal, desconto):"<<endl;
					cin>>nome>>precoMensal>>desconto;
					if (cin.fail()){
						cin.clear();
						cin.ignore('\n',100);
						cout<<"Invalid input."<<endl;}
					else if (precoMensal<0||desconto<0)
						cout<<"Invalid input."<<endl;
					else break;
				}
				Cartao *c1 = new Cartao(nome, precoMensal, desconto);
				r->adicionaCartao(c1);
				break;
			}

			case 4:{//verificacao de erros nao funciona muito bem quando tentas por string
				string origem,destino;
				double distancia;
				int ano, mes, dia, horas, minutos, id_comboio;
				while (true){
					cout<<endl<<f->getInformacao()<<endl;
					cout<<endl<<"Introduza a informacao da viagem(origem, destino, distancia, id comboio, ano, mes, dia, horas, minutos):"<<endl;
					cin>>origem>>destino>>distancia>>id_comboio>>ano>>mes>>dia>>horas>>minutos;
					if (cin.fail()){
						cin.clear();
						cin.ignore('\n',100);
						cout<<"Invalid input."<<endl;}
					else if (id_comboio < 0 || id_comboio >= f->getNumComboios()||distancia<0||ano<0||mes<0||dia<0||horas<0||minutos<0)
						cout<<"Invalid input."<<endl;
					else break;
				}
				Comboio *c = f->getComboio(id_comboio);
				Datas *dp=new Datas(ano,mes,dia);
				Horas *hp=new Horas(horas, minutos);
				Viagem *v=new Viagem(origem, destino, distancia, c,dp,hp);
				b->adicionaViagem(v);

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

	unsigned int menu = 3;

	while (menu != 2){
		while (cin.fail() || menu > 2){

			if (cin.fail()){
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Input Invalido tente outra vez" << endl;
			}

			cout << endl << "---Informacao---" << endl << endl;

			cout << endl << "0 - Lista de Comboios" << endl;
			cout << "1 - Lista de Viagens" << endl;
			cout << "2 - Sair" << endl;

			cin >> menu;
			if (menu > 2)
				cout << "Menu nao existe, tente outra vez" << endl;
		}

		switch (menu){
		case 0:

			menu = 3;

			if (f->getNumComboios() == 0){
				cout << endl << "Nao existem comboios" << endl;
				break;
			}

			cout << endl << "Lista de Comboios" << endl << endl;
			cout << f->getInformacao();

			break;
		case 1:
			menu = 3;

			if (b->getNumViagens() == 0){
				cout << endl << "Nao existem viagens" << endl;
				break;
			}
			cout << endl << "Lista de Viagens" << endl << endl;
			cout << b->getInfo();

			break;

		case 2:
			return;
		default:
			return;
		}
	}
}

//				MENU UTILIZADORES REGISTADOS

void menuComCartao(BaseClientes *r, Bilheteira *b){
	unsigned int numRegs = r->getNumRegistos();
	unsigned int id = numRegs + 1;
	unsigned int menu = 0;
	bool skip = false;

	if (numRegs == 0) {
		cout << endl << "Nao existem registos." << endl;
		return;
	}



		while (cin.fail() || id >= numRegs ){
			if (cin.fail()){
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "ID Invalido, tente outra vez" << endl;
			}
			cout << "ID do seu cartao: ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> id;
			if (id >= numRegs)
				cout << "ID nao existe, tente outra vez" << endl;
		}

	r->setId(id);



	while (menu != 5){

		cout << endl << "---Passageiro Com Cartao---" << endl << endl;

		cout << "ID: " << id << endl << endl;
		cout << r->getInformacao();

		if (!r->getRegisto()->getEstado()){ //RE-ATIVAR SUBSCRICAO
			string ans;
			cout << endl << "Subscricao desativada. Deseja re-ativar? (s/n)" << endl;
			cin.clear();
			cin.ignore();
			getline(cin, ans);
			if (ans == "s"){
				cout << endl << "Cartao re-ativado" << endl << endl;
				cout << "Escolha o tipo de cartao da nova subscricao" << endl;
				r->getRegisto()->alterarEstado(true);
				menu = 2;
				skip = true;
			}
			else{
				cout << "Subscricao nao foi re-ativada" << endl;
				return;
			}
		}

		while (true){
			if (!skip){
				cout << endl << "0 - Comprar Bilhete" << endl;
				cout << "1 - Devolver Bilhete" << endl;
				cout << "2 - Alterar cartao subscrito" << endl;
				cout << "3 - Remover subscricao" << endl;
				cout << "4 - Historico de Viagens" << endl;
				cout << "5 - Sair" << endl << endl;

				cin >> menu;
				if (cin.fail()){
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Input invalido, tente outra vez" << endl;
					continue;
				}

				if (menu > 5){
					cout << "Menu nao existe, tente outra vez" << endl;
					continue;
				}
				break;
			}
			else break;
		}
	switch (menu){
		case 0:{ // 0 - COMPRAR BILHETE

			if (b->getNumViagens() == 0){
				cout << endl << "Nao existem viagens" << endl;
				break;
			}

			int viagemId =  b->getNumViagens() + 1;
			double precoFinal;
			Viagem *temp;
			cout << "Lista de Viagens" << endl << endl;
			cout << endl << b->getInfo();
			while (cin.fail() || viagemId >= b->getNumViagens() || viagemId < -1){
				if (cin.fail()){
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Input invalido, tente outra vez (-1 para cancelar)" << endl;
				}
				cout << endl << "Escolha o id da viagem a reservar:";
				cin >> viagemId;
				cout << endl;
				if (viagemId == -1)
					return;

				if (viagemId >= b->getNumViagens() || viagemId < -1){
					cout<< endl <<"Esta viagem nao existe, tente outra vez (-1 para cancelar)"<< endl;
				}
		}

			temp = b->getViagem(viagemId);
			if (temp->reservaBilhete(true) == -1){
				cout << endl << "Este comboio ja esta cheio" << endl;
				break;
			}
			precoFinal = temp->getPrecoFinal(r->getRegisto()->getCartao());
			Compra *tempC = new Compra( temp, r->getRegisto()->getCartao(), precoFinal, getDataActual(), getHoraActual() );
			r->getRegisto()->adicionaCompra(tempC);
			cout << "Compra efectuada" << endl << endl;
			cout << "Preco Base = " << temp->getPrecoBase() << "Ä" << endl;
			cout << "Desconto = " <<temp->getPrecoBase() - precoFinal << "Ä"
					<< " (" << 100 - (precoFinal/temp->getPrecoBase() * 100) << "%)"<< endl;
			cout << "Preco Final = " << precoFinal << "Ä" << endl << endl;

			break;
		}
		case 1:{ // 1 - DEVOLVER BILHETE

			if (b->getNumViagens() == 0){
				cout << endl <<"Nao existem viagens ativas" << endl;
				break;
			}


			vector <Compra *> cmps = r->getRegisto()->getCompraAtiva();
			if (cmps.size() == 0){
				cout << "Ainda nao existem compras" << endl;
				break;
			}

			int compraId = cmps.size() + 1;

			cout << "Bilhetes nao usados" << endl << endl;
			cout << r->getRegisto()->listCompraActiva() << endl;

			while (cin.fail() || compraId >= (int)cmps.size() || compraId < -1){
				if (cin.fail()){
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Input invalido, tente outra vez (-1 para cancelar)" << endl;
				}

			cout << "Escolha o bilhete a devolver:";
			cin >> compraId;
			cout << endl;

			if (compraId >= (int)cmps.size() || compraId < -1)
				cout<<"Esse bilhete nao existe."<<endl<<endl;

			}

			cmps.at(compraId)->getViagem()->devolveBilhete(true);
			r->getRegisto()->eliminaCompra(cmps.at(compraId));

			cout << "Bilhete devolvido" << endl << endl;

			break;
		}
		case 2:{ // 2 - ALTERAR CARTAO SUBSCRITO

			if (r->getNumCartoes() == 0){
				cout << "Nao existem cartoes para subscrever" << endl;
				return;
			}

			int cart = r->getNumCartoes() + 1;
			cout << "Tipo de Cartao: " << endl << endl;
			cout << r->getInfoCartao() << endl;;

			while (cin.fail() || cart >= r->getNumCartoes() || cart < -1){
				if (cin.fail()){
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Input invalido, tente outra vez (-1 para cancelar)" << endl;
				}
				cout << endl << "Escolha o cartao a subscrever:";
				cin >> cart;
				cout << endl;
				if (cart == -1)
					return;

				if (cart >= r->getNumCartoes() || cart < -1){
					cout<< endl <<"Este cartao nao existe, tente outra vez (-1 para cancelar)"<< endl;
				}
			}

			r->getRegisto()->alterarCartao(r->getCartao(cart));
			cout << endl << "Cartao alterado para \"" << r->getCartao(cart)->getNome() << "\"" << endl;
			return;
		}

			break;
		case 3:{ // 3 - REMOVER SUBSCRICAO
			r->removeRegisto();
			cout << endl << "Subscricao removida, ao usar o id no futuro tem a possibilidade de re-ativar" << endl;
			return;
		}

		case 4: { // 4 - HISTORICO DE VIAGENS
			if (r->getRegisto()->getNumCompras() == 0){
				cout << "Ainda nao existe historico de compras" << endl;
				break;
			}

			cout << endl <<"Historico de Viagens" << endl << endl;
			cout << r->getRegisto()->getHistorico() << endl;
			break;
		}
		default:
			return;
		}

	}
}

//					MENU UTILIZADORES ANONIMOS

void menuSemCartao(BaseClientes *r, Bilheteira *b){//TODO: PROPER INPUT VAL
	unsigned int menu = 4;

	while (menu != 3){

		while (cin.fail() || menu > 3){
			if (cin.fail()){
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Input invalido, tente outra vez" << endl;
			}
		cout << endl << "---Passageiro sem Cartao---" << endl << endl;

		cout << endl << "0 - Comprar Bilhete" << endl;
		cout << "1 - Devolver Bilhete" << endl;
		cout << "2 - Subscrever a um cartao" << endl;
		cout << "3 - Sair" << endl;

		cin >> menu;

		if (menu > 3)
			cout << "Menu nao existe, tente outra vez" << endl;
		}

		switch (menu){
		case 0:{ // 0 - COMPRAR BILHETE

			if (b->getNumViagens() == 0){
				cout << endl << "Nao existem viagens" << endl;
				return;
			}

			int viagemId =  b->getNumViagens() + 1;
			double precoFinal;
			Viagem *temp;
			cout << "Lista de Viagens" << endl << endl;
			cout << endl << b->getInfo();
			while (cin.fail() || viagemId >= b->getNumViagens() || viagemId < -1){
				if (cin.fail()){
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Input invalido, tente outra vez (-1 para cancelar)" << endl;
				}
				cout << endl << "Escolha o id da viagem a reservar:";
				cin >> viagemId;
				cout << endl;
				if (viagemId == -1)
					return;

				if (viagemId >= b->getNumViagens() || viagemId < -1){
					cout<< endl <<"Esta viagem nao existe, tente outra vez (-1 para cancelar)"<< endl;
				}
			}

			temp = b->getViagem(viagemId);
			if (temp->reservaBilhete(false) == -1){
				cout << endl << "Este comboio ja esta cheio" << endl;
				break;
			}
			precoFinal = temp->getPrecoFinal();
			cout << "Compra efectuada" << endl << endl;
			cout << "Preco Base = " << temp->getPrecoBase() << "Ä" << endl;
			cout << "Desconto = " <<temp->getPrecoBase() - precoFinal << "Ä"
					<< " (" << 100 - (precoFinal/temp->getPrecoBase() * 100) << "%)"<< endl;
			cout << "Preco Final = " << precoFinal << "Ä" << endl;


			return;
		}
		case 1:{ // 1 - DEVOLVER BILHETE

			if (b->getNumViagens() == 0){
				cout << endl << "Nao existem viagens" << endl;
				return;
			}

			int viagemId =  b->getNumViagens() + 1;
			Viagem *temp;
			cout << "Lista de Viagens" << endl << endl;
			cout << endl << b->getInfo();
			while (cin.fail() || viagemId >= b->getNumViagens() || viagemId < -1){
				if (cin.fail()){
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Input invalido, tente outra vez (-1 para cancelar)" << endl;
				}
				cout << endl << "Escolha o id da viagem a reservar:";
				cin >> viagemId;
				cout << endl;
				if (viagemId == -1)
					return;

				if (viagemId >= b->getNumViagens() || viagemId < -1){
					cout<< endl <<"Esta viagem nao existe, tente outra vez (-1 para cancelar)"<< endl;
				}
			}


			temp = b->getViagem(viagemId);
			if (temp->devolveBilhete(false) == -1){
				cout << "Nao existem bilhetes sem registo para esta viagem" << endl;
				return;
			}
			cout << endl << "Bilhete devolvido" << endl;

			break;
		}
		case 2:{ // 2 - SUBSCREVER A UM CARTAO
			string datans;
			int cart = r->getNumCartoes() + 1;
			string nome;
			string profissao;
			Datas *datanasc;

			if (r->getNumCartoes() == 0){
				cout << "Nao existem cartoes para subscrever" << endl;
				return;
			}

			cin.ignore();
			cin.clear();

			cout << endl << "---Subscricao de cartao---" << endl << endl;

			cout << "Nome: ";
			getline(cin, nome);

			cout << endl << "Profissao: ";
			getline(cin,profissao);

			try {
			cout << endl << "Data de Nascimento(DD-MM-AAAA): ";
			getline(cin, datans);
			cout << endl;
			datanasc = new Datas(datans);
			}
			catch (Datas::DataInvalida){
				cout << "Data Invalida - Dia(1-31), Mes (1-12), tente outra vez" << endl;
				return;
			}
			catch (Datas::FormatoStringInvalido){
				cout << "Formato invalido - (DD-MM-AAAA), tente outra vez" << endl;
				return;
			}

			cout << "Tipo de Cartao: " << endl << endl;
			cout << r->getInfoCartao() << endl;;

			while (cin.fail() || cart >= r->getNumCartoes() || cart < -1){
				if (cin.fail()){
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Input invalido, tente outra vez (-1 para cancelar)" << endl;
				}
				cout << endl << "Escolha o cartao a subscrever:";
				cin >> cart;
				cout << endl;
				if (cart == -1)
					return;

				if (cart >= r->getNumCartoes() || cart < -1){
					cout<< endl <<"Este cartao nao existe, tente outra vez (-1 para cancelar)"<< endl;
				}
			}


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
