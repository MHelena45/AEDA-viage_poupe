#include "Maquinistas.h"
#include <iostream>

Maquinista::Maquinista(string nome, string apelido, int id) {
	nome = nome;
	apelido = apelido;
	id = id;
	ativo = true;
}

Maquinista::Maquinista(string nome, string apelido, int id, bool atual) {
	nome = nome;
	apelido = apelido;
	id = id;
	ativo = atual;
}
ostream & operator << (ostream &out, const Maquinista & M) {
	out << M.getId() << " : " << M.getNome() << " " << M.getApelido() << endl;
	return out;
}
/**
 *  Inicia a tabela de dispersao vazia
 *
 */
Maquinistas::Maquinistas() {
	maquinistas.clear();
}

bool Maquinistas::adicionaMaquinista(Maquinista trabalhador) {
	pair<unordered_set<Maquinista, hstr, eqMaquinista >::iterator,bool> res = maquinistas.insert(trabalhador);
	if (res.second == true)
		return true;
	else return false;
}
void Maquinistas::editaMaquinista(Maquinista trabalhador1, Maquinista trabalhador2) {
	eliminaMaquinista(trabalhador1);
	adicionaMaquinista(trabalhador2);
}

void Maquinistas::eliminaMaquinista(Maquinista trabalhador) {
	unordered_set<Maquinista, hstr, eqMaquinista >::const_iterator it;
	it = maquinistas.find(trabalhador);
	maquinistas.erase(it);

}