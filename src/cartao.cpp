#include "cartao.h"
using namespace std;

//CLASS CARTAO

Cartao::Cartao(string nome, float prc, int desc){
	this->precoMensal = prc;
	this->desconto = desc;
	this->nome = nome;
}

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


//CLASS REGISTO

//PIN?
Registo::Registo(Cartao *c, std::string nome, std::string profissao, datas datanasc){
	c1 = c;
	this->nome = nome;
	this->profissao = profissao;
	this->datanascimento = datanasc;
	this->ativo = true;
}




Cartao* Registo::getCartao() const {
	return c1;
}

bool Registo::getEstado() const{
	return ativo;
}

string Registo::getNome() const{
	return nome;
}
string Registo::getProfissao() const{
	return profissao;
}
datas Registo::getDatanascimento() const{
	return datanascimento;
}

void Registo::alterarCartao(Cartao *c){
	c1=c;
}

void Registo::alterarEstado(bool at){
	ativo = at;
}

//CLASS PASSAGEIROS REGISTADOS

BaseClientes::~BaseClientes(){

	for (unsigned int i = 0; i < regs.size(); i++)
		delete regs.at(i);
}

void BaseClientes::adicionaCartao(Cartao *c1){
	this->cartoes.push_back(c1);
}

string BaseClientes::getInfoCartao() const{
	stringstream ss;
	for (unsigned int i=0; i < cartoes.size(); i++){
		ss << i << " - " << cartoes.at(i)->getInformacao() << "\n\n";
	}
	return ss.str();
}

Cartao* BaseClientes::getCartao(int id) const {
	return cartoes.at(id);
}

void BaseClientes::alterarCartao(Cartao *c){
	regs.at(id)->alterarCartao(c);
}

bool BaseClientes::getEstado() const{
	return regs.at(id)->getEstado();

}

void BaseClientes::alterarEstado(bool est){
	regs.at(id)->alterarEstado(est);
}
unsigned int BaseClientes::getNumCartoes () const {
	return cartoes.size();
}


void BaseClientes::adicionaRegisto(Registo *r1){
	regs.push_back(r1);
}

void BaseClientes::removeRegisto (){
	regs.at(id)->alterarEstado(false);
}

unsigned int BaseClientes::getNumRegistos() const{
	return this->regs.size();
}

void BaseClientes::setId(int id){
	this->id = id;
}


string BaseClientes::getNome() const{
	return regs.at(id)->getNome();
}

string BaseClientes::getProfissao() const {
	return regs.at(id)->getProfissao();

}

string BaseClientes::getInformacao () const {
	datas datan = regs.at(id)->getDatanascimento();
	return  "Nome: " + regs.at(id)->getNome() + " -- Cartao: " + "\""+  regs.at(id)->getCartao()->getNome() + "\"" + " -- Profissao: " + regs.at(id)->getProfissao() + " -- Data de Nascimento: " + to_string(datan.dia) + "-" + to_string(datan.mes) + "-" + to_string(datan.ano) + "\n";
}

datas BaseClientes::getDataNascimento() const{
	return regs.at(id)->getDatanascimento();
}



