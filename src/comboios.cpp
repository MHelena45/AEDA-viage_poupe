#include "comboios.h"

Comboio::Comboio(int numPassageiros, int velocidade, double precoKM, string nome) {
	this->lotacao = numPassageiros;
	this->velocidade = velocidade;
	this->precoKM = precoKM;
	this->nome = nome;
}


/*bool Comboio::getOcupado(){
	return ocupado;
}*/

/*bool Comboio::cheio(){
	if(NumMax == lotacao)
		return true;
	else return false;
}
bool Comboio::getMeioCheio(){	
	if(lotacao > (NumMax /2))
		return true;
	else return false;
}*/

AlfaPendular::AlfaPendular(int numPassageiros, int velocidade, double precoKM, string nome) : Comboio(numPassageiros, velocidade, precoKM, nome){}

string AlfaPendular::getTipo() const{
	return "AP";
}

Intercidades::Intercidades(int numPassageiros, int velocidade, double precoKM, string nome) : Comboio(numPassageiros, velocidade, precoKM, nome){}

string Intercidades::getTipo() const{
	return "IC";
}
/*
 * Comboio acessors
 */

int Comboio::getLotacao() const{
	return lotacao;
}
int Comboio::getVelocidade() const{
	return velocidade;
}
double Comboio::getPrecoKM() const{
	return precoKM;
}
string Comboio::getNome() const{
	return nome;
}
string Comboio::getTipo() const{
	return "OT";
}



void Frota::adicionaComboio(Comboio *c1) {
	Comboios.push_back(c1);
}
