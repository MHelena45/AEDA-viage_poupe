#include "cartao.h"

using namespace std;

//CLASS CARTAO

Cartao::Cartao(string nome, float prc, float desc){
	this->precoMensal = prc;
	this->desconto = desc;
	this->nome = nome;
}

float Cartao::getPreco() const{
	return precoMensal;
}

float Cartao::getDesconto() const {
	return desconto;
}

string Cartao::getNome() const{
	return nome;
}

string Cartao::getInformacao() const{
	return this->nome + " Pre�o: " + to_string(this->precoMensal) + "�/m�s  Desconto: " + to_string(this->desconto) + "�/m�s";
}

//CLASS REGISTO

//PIN?
Registo::Registo(Cartao *c, std::string nome, std::string profissao, datas datanasc){
	c1 = c;
	this->nome = nome;
	this->profissao = profissao;
	this->datanascimento = datanasc;
}


void Registo::alterarCartao(Cartao *c){
	c1=c;
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
string Registo::getInformacao () const{
	return "Nome: " + nome + " Cartao: " + c1->getNome() + " Profissao: " + profissao;
}

//CLASS PASSAGEIROS REGISTADOS


void BaseClientes::adicionaRegisto(Registo r1){
	regs.push_back(r1);
}

int BaseClientes::getNumRegistos(){
	return this->regs.size();
}

void BaseClientes::setId(int id){
	this->id = id;
}


string BaseClientes::getNome() const{
	return regs.at(id).getNome();
}

string BaseClientes::getProfissao() const {
	return regs.at(id).getProfissao();

}

string BaseClientes::getInformacao () const {
	return regs.at(id).getInformacao();
}

datas BaseClientes::getDataNascimento() const{
	return regs.at(id).getDatanascimento();
}



