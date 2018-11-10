#include "cartao.h"
#include "viagens.h"
#include "geral.h"
using namespace std;

/*
 * Metodos class Cartao
 *
 *
 */

// Construtor

Cartao::Cartao(string nome, float prc, int desc){
	this->precoMensal = prc;
	this->desconto = desc;
	this->nome = nome;
}

// Acessors

float Cartao::getPreco() const{
	return precoMensal;
}

int Cartao::getDesconto() const {
	return desconto;
}

string Cartao::getNome() const{
	return nome;
}

string Cartao::getInformacao() const{
	return this->nome + " - Preço: " + to_string(this->precoMensal).substr(0, 6) + "€/mês - Desconto: " + to_string(100 - this->desconto) + "% por Viagem";
}


/*
 * Metodos class Registo
 *
 *
 */

// Construtor

Registo::Registo(Cartao *c, std::string nome, std::string profissao, Datas *datanasc){
	c1 = c;
	this->nome = nome;
	this->profissao = profissao;
	this->datanascimento = datanasc;
	this->ativo = true;
}

// Acessors

Cartao* Registo::getCartao() const {return c1;}

bool Registo::getEstado() const{return ativo;}

string Registo::getNome() const{return nome;}

string Registo::getProfissao() const{return profissao;}

string Registo::getDatanascimento() const{
	stringstream ss;
	ss << *datanascimento;

	return ss.str();
}

std::string Registo::getHistorico() const{
	stringstream ss;

	ss << left << setw(16) <<"Data da compra" << setw(16)  <<"Hora da Compra"
			<< setw(9) << "Origem" << setw(9) << "Destino" << setw(16)
			<< "Data da viagem" << setw(16) <<"Hora da viagem" << setw(16)
			<< "Preco Base(€)" << setw(10) <<"Total(€)" << endl;

	for (unsigned int i = 0; i < historico.size(); i++){
		ss << historico.at(i)->getInfo();
	}


	return ss.str();
}

string Registo::listCompraActiva(){

	vector <Compra *> c = getCompraAtiva();

	stringstream ss;

	ss <<"ID  " <<left << setw(16) <<"Data da compra" << setw(16)  <<"Hora da Compra"
			<< setw(9) << "Origem" << setw(9) << "Destino" << setw(16)
			<< "Data da viagem" << setw(16) <<"Hora da viagem" << setw(16)
			<< "Preco Base(€)" << setw(10) <<"Total(€)" << endl;

	for (unsigned int i = 0; i < c.size(); i++){
		ss << i << "   " << c.at(i)->getInfo();
	}


	return ss.str();

}

vector <Compra *> Registo::getCompraAtiva(){
	vector <Compra *> temp;

	Horas *tempHora = getHoraActual();
	Datas *tempData = getDataActual();
	float horasActual = tempData->getHoursFormat() + tempHora->getHoursFormat();


	for (unsigned int i = 0; i < historico.size(); i++){
		Viagem *v =	historico.at(i)->getViagem();
		float horasViagem = v->getDataPartida()->getHoursFormat() + v->getHorasPartida()->getHoursFormat();
		if (horasViagem > horasActual)
			temp.push_back(historico.at(i));
	}


	return temp;

}

// Mutators

void Registo::alterarCartao(Cartao *c){c1=c;}

void Registo::alterarEstado(bool at){ativo = at;}

void Registo::adicionaCompra(Compra *c1){historico.push_back(c1);}

void Registo::eliminaCompra(Compra *c1){

	for (unsigned int i = 0; i < historico.size();i++){
		if (*historico.at(i) == *c1){
			historico.erase(historico.begin()+i);
			delete c1;
			break;
		}
	}
}

/*
 * Metodos class BaseClientes
 *
 *
 */

// Destructor
BaseClientes::~BaseClientes(){
	for (unsigned int i = 0; i < regs.size(); i++)
		delete regs.at(i);
}

// Acessors

Registo* BaseClientes::getRegisto() const{
	return regs.at(id);
}


string BaseClientes::getInfoCartao() const{
	stringstream ss;
	for (unsigned int i=0; i < cartoes.size(); i++){
		ss << i << " - " << cartoes.at(i)->getInformacao() << "\n\n";
	}
	return ss.str();
}

Cartao* BaseClientes::getCartao(int id) const {return cartoes.at(id);}


unsigned int BaseClientes::getNumCartoes () const {return cartoes.size();}

unsigned int BaseClientes::getNumRegistos() const{return this->regs.size();}

void BaseClientes::adicionaCartao(Cartao *c1){this->cartoes.push_back(c1);}




string BaseClientes::getInformacao () const {
	stringstream ss;
	ss << "Nome: " << regs.at(id)->getNome() << " -- Cartao: " << "\"" <<  regs.at(id)->getCartao()->getNome()
			<< "\"" << " -- Profissao: " << regs.at(id)->getProfissao() << " -- Data de Nascimento: "
			<< regs.at(id)->getDatanascimento();

	return ss.str();
}


// Mutators


void BaseClientes::adicionaRegisto(Registo *r1){regs.push_back(r1);}

void BaseClientes::removeRegisto (){regs.at(id)->alterarEstado(false);}

void BaseClientes::setId(int id){this->id = id;}

void BaseClientes::loadCartoes(){

	ifstream mfile;

	mfile.open ("cartoes.txt");

	while (!mfile.eof()) {
		float precoMensal;
		int desconto;
		string nome;

		getline(mfile, nome);
		if (nome == "")
			break;

		mfile >> precoMensal;
		mfile.ignore(1);
		mfile >> desconto;
		mfile.ignore(1);
		Cartao *c1 = new Cartao(nome, precoMensal, desconto);
		adicionaCartao(c1);
	}
	mfile.close();


}
void BaseClientes::saveCartoes()const{

	ofstream mfile;

	mfile.open ("cartoes.txt");

	for (unsigned int i= 0; i < cartoes.size(); i++){
		mfile << cartoes.at(i)->getNome() << endl << cartoes.at(i)->getPreco() << " " << cartoes.at(i)->getDesconto() << endl;
	}

	mfile.close();



}


