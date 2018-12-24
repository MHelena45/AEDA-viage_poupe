#include "Maquinistas.h"

Maquinista::Maquinista(string n, string a, int i, vector<Viagem *> v) : nome(n), apelido(a), id(i) {
	ativo = true;
	viagens = v;
}

Maquinista::Maquinista(string n, string a, int i) : nome(n), apelido(a), id(i) {
	ativo = true;
}
Maquinista::Maquinista(string n, string a, int i, bool atual) : nome(n), apelido(a), id(i) {
	ativo = atual;
}

Maquinistas::Maquinistas(string nome) {
	loadMaquinistas(nome);
}

void Maquinista::alteraEstado() {
	ativo = !ativo;
}
void Maquinista::reforma() {
	if (ativo) {
		alteraEstado();
	}
	viagens.clear();
}

bool Maquinista::adicionaViagem(Viagem *v) {
	viagens.push_back(v);
	return true;
}

bool Maquinistas::loadMaquinistas(string nome) {
	bool sucedido = true, vazio = true;
	ifstream maqfile;
	maqfile.open(nome);
	vector <Viagem * > v;
	while (!maqfile.eof()) {		
		string Pnome;
		string apelidos;
		maqfile >> Pnome;
		getline(maqfile, apelidos);
		if (Pnome == "")
			break;
		vazio = false;
		Maquinista M1(Pnome, apelidos, 1, v);
		if (!adicionaMaquinista(M1))
			sucedido = false;		
	}
	if (vazio) {
		cout << "O ficheiro está vazio! " << endl;
	}
	maqfile.close();
	return sucedido;
}

void Maquinistas::saveMaquinista(Maquinista &maq) {
	ofstream maqfile;

	maqfile.open("maquinistas.txt");
	
	maqfile << maq.getId() << " " << maq.getNome() << endl << maq.getApelido() << endl;
	if (!maq.getViagens().size()) {
		maqfile << "Viagens ";
		vector<Viagem *> v = maq.getViagens();
		for(int i = 0; i < v.size(); i++) {
			cout << v.at(i) << " ";
		}
	}
	
	
	maqfile.close();
}

ostream & operator << (ostream &out, const Maquinista & M) {
	out << M.getAtivo() << "  " << M.getId() << " : " << M.getNome() << " " << M.getApelido() << endl;
	
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
		cout << it.getAtivo() << setw(8) <<  it.getId() << setw(15) << it.getNome()<< setw(15) << it.getApelido() << endl;
	}	
	return;
}
