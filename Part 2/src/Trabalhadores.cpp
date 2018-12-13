#include "Trabalhadores.h"
#include <iostream>

Trabalhador::Trabalhador(string nome, int id) {
	this->nome = nome;
	id = id;
}

Trabalhadores::Trabalhadores() {
	trabalhadores.clear();	
}
bool Trabalhadores::adicionaTrabalhador(Trabalhador trabalhador) {
	pair<unordered_set<string, hstr, eqstr>::iterator,bool> res = trabalhadores.insert(trabalhador.getNome());
	if (res.second == true)
		return true;
	else return false;
}
void Trabalhadores::editaTrabalhador(Trabalhador trabalhador1, Trabalhador trabalhador2) {
	eliminaTrabalhador(trabalhador1);
	adicionaTrabalhador(trabalhador2);
}

void Trabalhadores::eliminaTrabalhador(Trabalhador trabalhador) {
	it = trabalhadores.find(trabalhador.getNome());
	trabalhadores.erase(it);

}