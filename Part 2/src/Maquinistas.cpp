#include "Maquinistas.h"
#include <iostream>

/**
 *  se se esta a adicionar um maquinista atual, nao e necessario indicar o boleano se 
 *	este é ou não um membro ativo, porque será
 */
Maquinista::Maquinista(string nome, string apelido, int id) {
	nome = nome;
	apelido = apelido;
	id = id;
	ativo = true;
}

/**
 * se queremos adicionar um maquinista que já nao se encontra ao serviço, o 4 parametro deverá ser
 * false, dado este não ser um maquinista atual
*/
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

/**
 *  adiciona um maquinista a tabelaa de dispersao
 *  designada se maquinistas
 */
bool Maquinistas::adicionaMaquinista(Maquinista trabalhador) {
	pair<unordered_set<Maquinista, hstr, eqMaquinista >::iterator,bool> res = maquinistas.insert(trabalhador);
	if (res.second == true)
		return true;
	else return false;
}

/**
 *  Se nos enganarmos a colocar um maquinista na 
 *  tabela podemos editar o erro
 */
void Maquinistas::editaMaquinista(Maquinista trabalhador1, Maquinista trabalhador2) {
	eliminaMaquinista(trabalhador1);
	adicionaMaquinista(trabalhador2);
}

/**
 *  Se quisermos eliminar um maquinas, porque por exemplo faleceu,
 *  nao podendo ser reconstratado, podemos elimna-lo da nossa tabela
 */
void Maquinistas::eliminaMaquinista(Maquinista trabalhador) {
	unordered_set<Maquinista, hstr, eqMaquinista >::const_iterator it;
	it = maquinistas.find(trabalhador);
	maquinistas.erase(it);

}
