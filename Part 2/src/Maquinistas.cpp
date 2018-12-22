#include "Maquinistas.h"

Maquinista::Maquinista(string n, string a, int i) : nome(n), apelido(a), id(i) {
	ativo = true;
}

Maquinista::Maquinista(string n, string a, int i, bool atual) : nome(n), apelido(a), id(i) {
	ativo = atual;
}


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

void Maquinistas::saveMaquinista(Maquinista &maq) {
	ofstream maqfile;

	maqfile.open("maquinistas.txt");
	
	maqfile << maq.getId() << " " << maq.getNome() << endl << maq.getApelido() << endl;
	
	maqfile.close();
}

ostream & operator << (ostream &out, const Maquinista & M) {
	out << M.getId() << " : " << M.getNome() << " " << M.getApelido() << endl;
	return out;
}

void Maquinistas::clearMaquinistas() {
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

bool Maquinistas::adicionaMaquinista(Maquinista trabalhador) {
	pair<tabHMaq::iterator,bool> res = maquinistas.insert(trabalhador);
	if (res.second == true)
		return true;
	else return false;
}


void Maquinistas::editaMaquinista(Maquinista trabalhador1, Maquinista trabalhador2) {
	eliminaMaquinista(trabalhador1);
	adicionaMaquinista(trabalhador2);
}

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
