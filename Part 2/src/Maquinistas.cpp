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
void Maquinista::eliminaViagens() {
	viagens.clear();
	/*vector<Viagem *> viage;
	viagens = viage;*/
}


void Maquinista::alteraEstado() {
	ativo = !ativo;
}


bool Maquinista::adicionaViagem(Viagem *v) {
	viagens.push_back(v);
	return true;
}

bool Maquinista::operator== (Maquinista M3) {
	return id = M3.getId();
}

bool Maquinistas::encontraMaquinista( Maquinista *M00) {
	tabHMaq::const_iterator it;
	it = maquinistas.find(*M00);
	if (it != maquinistas.end())
		return true;
	return false;
}

bool Maquinistas::alteraEstado(Maquinista *M1) {
	tabHMaq::const_iterator it;
	it = maquinistas.find(*M1);
	if (it == maquinistas.end()) {
		return false;
	}
	maquinistas.erase(it);
	//se se vai reforma, apagar viagens atribuidas
	if (M1->getAtivo()) {
		M1->eliminaViagens();
	}
	M1->alteraEstado();

	pair<tabHMaq::iterator, bool> res = maquinistas.insert(*M1);
	if (res.second == true)
		return true;
}

bool Maquinistas::loadMaquinistas(string nome, Frota *f) {
	bool sucedido = true, vazio = true; int id;
	ifstream maqfile;
	maqfile.open(nome);
	vector <Viagem * > v;
	while (!maqfile.eof()) {		
		string Pnome;
		string apelidos;
		int numero;
		maqfile >> id;	
		maqfile >> Pnome;
		getline(maqfile, apelidos);
		if ( Pnome == "" || apelidos == "")
			break;
		vazio = false;
		maqfile >> numero;
		while (!numero)
		{
			numero--;
			string origem, destino;
			double distancia;
			int comboioId;
			string datavgm, horavgm;
			int vagas, comprasAnonimas;
			maqfile >> origem >> destino >> distancia >> comboioId;
			//maqfile.ignore(1);

			// DATA DA VIAGEM

			Datas *dvgm;
			try {
				getline(maqfile, datavgm);
				dvgm = new Datas(datavgm);
			}
			catch (Datas::DataInvalida) {
				cout << "Data Invalida - Dia(1-31), Mes (1-12)" << endl;
				cout << endl << "AVISO - Dados corrompidos / incompletos" << endl;
				return false;
			}
			catch (Datas::FormatoStringInvalido) {
				cout << "Formato invalido - (DD-MM-AAAA)" << endl;
				cout << endl << "AVISO - Dados corrompidos / incompletos" << endl;
				return false;
			}

			// HORA DA VIAGEM

			Horas *hvgm;
			try {
				getline(maqfile, horavgm);
				hvgm = new Horas(horavgm);
			}
			catch (Horas::HoraInvalida) {
				cout << "No ficheiro de maquinistas:";
				cout << "Hora Invalida - Hora(0-23), Min (0-59)" << endl;
				cout << endl << "AVISO - Dados corrompidos / incompletos" << endl;
				return false;
			}
			catch (Horas::FormatoStringInvalido) {
				cout << "No ficheiro de maquinistas:";
				cout << "Formato invalido - (HH-MM)" << endl;
				cout << endl << "AVISO - Dados corrompidos / incompletos" << endl;
				return false;
			}

			maqfile >> vagas; maqfile >> comprasAnonimas;

			Viagem *temp = new Viagem(origem, destino, distancia, f->getComboio(comboioId),
				dvgm, hvgm, vagas, comprasAnonimas);

			v.push_back(temp);

		}
		Maquinista M1(Pnome, apelidos, 1, v);
		if (!adicionaMaquinista(&M1))
			sucedido = false;		
	}
	if (vazio) {
		cout << "O ficheiro est� vazio! " << endl;
	}
	maqfile.close();
	return sucedido;
}

void Maquinistas::saveMaquinistas() {
	ofstream maqfile;

	maqfile.open("maquinistas.txt");
	for (auto it : this->maquinistas) {
		maqfile << it.getId() << " " << it.getNome() << endl << it.getApelido() << endl;
		maqfile << !it.getViagens().size() << endl;
		if (!it.getViagens().size()) {		
			vector<Viagem *> v = it.getViagens();
			for (int i = 0; i < v.size(); i++) {
				maqfile << v.at(i)->getOrigem() << " " << v.at(i)->getDestino() << " " << v.at(i)->getDistancia() << " " << v.at(i)->getComboio()->getId() << endl;
				maqfile << v.at(i)->getHorasPartida() << endl << v.at(i)->getHorasPartida();
				maqfile << v.at(i)->getVagas() << " " << v.at(i)->getComprasAnonimas() << endl;
			}
		}
	}	
	maqfile.close();
}

void Maquinistas::saveMaquinista(Maquinista *maq) {
	ofstream maqfile;

	maqfile.open("maquinistas.txt");

	maqfile << maq->getId() << " " << maq->getNome() << endl << maq->getApelido() << endl;
	maqfile << maq->getViagens().size();
	if (!maq->getViagens().size()) {
		
		vector<Viagem *> v = maq->getViagens();
		for (int i = 0; i < v.size(); i++) {
			maqfile << v.at(i)->getOrigem() << " " << v.at(i)->getDestino() << " " << v.at(i)->getDistancia() << " " << v.at(i)->getComboio()->getId() << endl;
			maqfile << v.at(i)->getHorasPartida() << endl << v.at(i)->getHorasPartida();
			maqfile << v.at(i)->getVagas() << " " << v.at(i)->getComprasAnonimas();
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

bool Maquinistas::adicionaMaquinista(Maquinista *trabalhador) {
	pair<tabHMaq::iterator,bool> res = maquinistas.insert(*trabalhador);
	if (res.second == true)
		return true;
	else return false;
}


bool Maquinistas::editaMaquinista(Maquinista *trabalhador1, Maquinista* trabalhador2) {
	if (!eliminaMaquinista(trabalhador1))
		return false;
	adicionaMaquinista(trabalhador2);
	return true;
}

bool Maquinistas::eliminaMaquinista(Maquinista *trabalhador) {
	tabHMaq::const_iterator it;
	it = maquinistas.find(*trabalhador);
	if (it != maquinistas.end()) {
		maquinistas.erase(it);
		return true;
	}
	return false;
}

void Maquinistas::showMaquinistas() {
	cout << "ESTADO" << setw(9) << "ID" << setw(15) << "Nome" << setw(15) << "Apelidos" << endl;
	for (auto it : this->maquinistas  ) {
		if (it.getAtivo()) {
			cout << "Ativo" << setw(8);
		}
		else {
			cout << "Reformado" << setw(3);
		}
		cout <<  it.getId() << setw(15) << it.getNome()<< setw(15) << it.getApelido() << endl;
	}	
	return;
}
