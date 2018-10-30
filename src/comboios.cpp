#include "comboios.h"

using namespace std;

Comboio::Comboio(int numPassageiros, int velocidade, double precoKM, string nome) {
	this->lotacao = numPassageiros;
	this->velocidade = velocidade;
	this->precoKM = precoKM;
	this->nome = nome;
}


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
	comboios.push_back(c1);
}

string Frota::getInformacao() const{
	stringstream ss;
	ss << "Nome" << setw(7) << "Tipo" << setw(9) << "Lotacao" << setw(12) << "Velocidade"
			<< setw(15) << "Preco por Km" << "\n";
				for (unsigned int i = 0; i < comboios.size();i++){
					ss << comboios.at(i)->getNome() << setw(7) << comboios.at(i)->getTipo()
							<< setw(9) << comboios.at(i)->getLotacao() << setw(8);
					ss << comboios.at(i)->getVelocidade() << " km/h" << setw(12)
							<< comboios.at(i)->getPrecoKM() << "€" << "\n";
				}

	return ss.str();

}
