#include "Maquinistas.h"


/**
 *  Se se esta a adicionar um maquinista atual, não é necessario indicar o boleano se 
 *  este é ou não um membro ativo, porque será um maquinista novo
 *
 * @param primeiro nome do maquinistas
 * @param apelidos do maquinistas serados por espaço
 * @param identificacao do maquinistas
 */
Maquinista::Maquinista(string n, string a, int i) : nome(n), apelido(a), id(i) {
	ativo = true;
}

/**
 * Se queremos adicionar um maquinista que já não se encontra ao serviço, o 4 parametro deverá ser
 * false, dado este não ser um maquinista atual
 *
 * @param primeiro nome do maquinistas
 * @param apelidos do maquinistas
 * @param identificacao do maquinistas
 * @param se o maqinista está atualmente ao serviço ou não
 *
 */
Maquinista::Maquinista(string n, string a, int i, bool atual) : nome(n), apelido(a), id(i) {

	ativo = atual;
}
/**
 * Faz load dos maquinistas que se encontram num fihceiro com os seu nomes
 *
 */

bool Maquinistas::loadMaquinistas() {

	ifstream maqfile;

	maqfile.open("maquinistas.txt");
	
	while (!maqfile.eof()) {
		
		string Pnome;
		string apelidos;
		maqfile >> Pnome;
		getline(maqfile, apelidos);
		if (Pnome == "")
			break;
		Maquinista M1(Pnome, apelidos, 1);
		if (!adicionaMaquinista(M1))
			return false;		
	}
	maqfile.close();
	return true;
}

/** 
* Guarda um novo maquinistas no ficheiro com os maquinistas
* @param maquinistas a adicionar ao ficheiro
*/

void Maquinistas::saveMaquinista(Maquinista maq) {
	ofstream maqfile;

	maqfile.open("maquinistas.txt");
	
	maqfile << maq.getId() << " " << maq.getNome() << endl << maq.getApelido() << endl;
	
	maqfile.close();
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


bool Maquinistas::emptyMaquinistas() {
	tabHMaq::const_iterator it;
	for (it = maquinistas.begin(); it != maquinistas.end(); it++) {
		if (it->getNome() != "") {
			return false;
		}
	}
	
	return true;
}

/**
 *  Adiciona um maquinista a tabela de dispersao
 *  designada de maquinistas
 * @param maquinistas a adicionar a tabela de dispersão
 */
bool Maquinistas::adicionaMaquinista(Maquinista trabalhador) {
	pair<tabHMaq::iterator,bool> res = maquinistas.insert(trabalhador);
	if (res.second == true)
		return true;
	else return false;
}

/**
 *  Se nos enganarmos a colocar um maquinista na 
 *  tabela podemos editar o erro
 *  @param maquinista enrado
 *  @param maquinista com o nome correto 
 */
void Maquinistas::editaMaquinista(Maquinista trabalhador1, Maquinista trabalhador2) {
	eliminaMaquinista(trabalhador1);
	adicionaMaquinista(trabalhador2);
}

/**
 *  Se quisermos eliminar um maquinas, porque por exemplo faleceu,
 *  nao podendo ser reconstratado, podemos elimna-lo da nossa tabela
 *  @param maquinista que quermos eliminar da tabela
 *
 */
void Maquinistas::eliminaMaquinista(Maquinista trabalhador) {
	tabHMaq::const_iterator it;
	it = maquinistas.find(trabalhador);
	maquinistas.erase(it);

}

void Maquinistas::showMaquinistas() {
	for (auto it : this->maquinistas  ) {
		cout << it.getId() << setw(15) << it.getNome()<< setw(15) << it.getApelido() << endl;
	}
	
	return;
}
