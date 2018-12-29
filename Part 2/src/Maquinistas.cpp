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
bool Maquinista::eliminaViagens() {
	if (!viagens.size())
		return false;
	viagens.clear();
	return true;
}

void Maquinista::alteraEstado() {
	//ativo = !ativo;
	if (ativo) {
		ativo = false;
	}
	else {
		ativo = true;
	}
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

bool Maquinistas::loadMaquinistas(Frota *f, string nome) {
	bool sucedido = true, vazio = true;
	ifstream maqfile;
	
	maqfile.open("maquinistas.txt");
	while (!maqfile.eof()) {
		int estado, id, numViagens= 0;
		string Pnome, apelidos;	
		maqfile >> estado;
		maqfile.ignore(1);
		maqfile >> id;	
		maqfile.ignore(1);
		maqfile >> Pnome;	
		if (Pnome == "" )
			break;
		vazio = false;
		getline(maqfile, apelidos);
		maqfile >> numViagens;
		Maquinista M1(Pnome, apelidos, id, estado);
		maqfile.ignore(1);
		while(numViagens) {
			numViagens--;
			string origem, destino;
			double distancia;
			int comboioId;
			string datavgm, horavgm;
			int vagas, comprasAnonimas;
			
			maqfile >> origem;			
			maqfile.ignore(1);
			maqfile >> destino;
			maqfile.ignore(1);
			maqfile >> distancia;
			maqfile.ignore(1);
			maqfile >> comboioId;
			maqfile.ignore(1);
			maqfile >> vagas;
			maqfile.ignore(1);
			maqfile >> comprasAnonimas;
			maqfile.ignore(1);
			// DATA DA VIAGEM
			Datas *dvgm;
			try {
				getline(maqfile, datavgm);
				dvgm = new Datas(datavgm);
			}
			catch (Datas::DataInvalida) {
				cout << "Em maquinistas exixte uma data Invalida - Dia(1-31), Mes (1-12)" << endl;
				cout << endl << "AVISO - Dados corrompidos / incompletos" << endl;
				return false;
			}
			catch (Datas::FormatoStringInvalido) {
				cout << "Em maquinistas exixte um formato invalido - (DD-MM-AAAA)" << endl;
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
				cout << "Em maquinistas exixte uma hora Invalida - Hora(0-23), Min (0-59)" << endl;
				cout << endl << "AVISO - Dados corrompidos / incompletos" << endl;
				return false;
			}
			catch (Horas::FormatoStringInvalido) {
				cout << "Em maquinistas exixte um formato invalido - (HH-MM)" << endl;
				cout << endl << "AVISO - Dados corrompidos / incompletos" << endl;
				return false;
			}
			
			Viagem *temp = new Viagem(origem, destino, distancia, f->getComboio(comboioId),
				dvgm, hvgm, vagas, comprasAnonimas);
			M1.adicionaViagem(temp);
		}
		
		if (!adicionaMaquinista(&M1))
			sucedido = false;
	}
	if (vazio) {
		cout << "O ficheiro de maquinistas está vazio! " << endl;
	}
	maqfile.close();
	return sucedido;
}

void Maquinistas::saveMaquinistas() {
	ofstream maqfile;

	maqfile.open("maquinistas.txt");
	for (auto it : this->maquinistas) {
		maqfile << it.getAtivo() << " " << it.getId() << " " << it.getNome() << " " << it.getApelido() << endl ;
		vector <Viagem*> viagens = it.getViagens();
		maqfile << viagens.size() << " ";
		for(int i=0; i < viagens.size(); i++) {
			maqfile << viagens.at(i)->getOrigem() << " " << viagens.at(i)->getDestino() << " " << viagens.at(i)->getDistancia()
				<< " " << viagens.at(i)->getComboio()->getId() << " "<< viagens.at(i)->getVagas() << " " << viagens.at(i)->getComprasAnonimas()
				<< " " << *viagens.at(i)->getDataPartida() << endl << *viagens.at(i)->getHorasPartida() << endl;
		}
	}	
	maqfile.close();
}

void Maquinistas::saveMaquinista(Maquinista *maq) {
	ofstream maqfile;

	maqfile.open("maquinistas.txt");

	maqfile << maq->getAtivo() << " " << maq->getId() << " " << maq->getNome() 
		<< " " << maq->getApelido() << endl;

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

unsigned int Maquinistas::numeroDeMaquinistas() {
	return maquinistas.size();
}

void Maquinistas::showMaquinistas() {
	cout << "ESTADO" << setw(10) << "ID" << setw(15) << "Nome" << setw(15) << "Apelidos" << endl;
	for (auto it : this->maquinistas  ) {
		if (it.getAtivo()) {
			cout << "Ativo" << setw(11) << it.getId() << setw(15) << it.getNome() << setw(15) << it.getApelido() << endl;
		}
		else {
			cout << "Reformado" << setw(6)<<  it.getId() << setw(15) << it.getNome()<< setw(15) << it.getApelido() << endl;
		}
	}	
	return;
}

void Maquinistas::showMaquinista(Maquinista *M1) {
	tabHMaq::const_iterator it;
	it = maquinistas.find(*M1);
	if (it != maquinistas.end()) {
		cout << "ESTADO" << setw(9) << "ID" << setw(15) << "Nome" << setw(15) << "Apelidos" << endl;
		if (it->getAtivo()) {
			cout << "Ativo" << setw(10);
		}
		else {
			cout << "Reformado" << setw(6);
		}
		cout << it->getId() << setw(15) << it->getNome() << setw(15) << it->getApelido() << endl;
	}
	return;
}
bool Maquinistas::showViagensMaquinistas( Maquinista* M1 ) const {
	vector <Viagem *> via;
	tabHMaq::const_iterator it;
	it = maquinistas.find(*M1);
	if (it != maquinistas.end()) {	
		via = it->getViagens();
		if (!via.size())
			if (it->getAtivo()) {
				cout << "ERRO: Ainda nao existem viagens associadas !! " << endl;
			}
			else {
				cout << "Um maquinista reformado nao tem viagens associadas ! " << endl;
			}
		else {
			cout << "Viagens atribuidas : " << it->getViagens().size()  << endl << endl;
			cout << left << setw(10) << "Origem" << setw(10) << "Destino" << setw(15)
				<< "Distancia(KM)" << setw(9) << "Comboio" << setw(13) << "Data"
				<< setw(8) << "Hora" << setw(16) << "Preco base(€)" << setw(7) << "Vagas" << "\n";
			for (int i = 0; i < via.size(); i++) {
				cout << via.at(i)->getInfo();
			}
		}
		return true;
	}
	return false;
}
bool Maquinistas::atribuiViagem( Maquinista* M1, Viagem * v) {
	tabHMaq::const_iterator it;
	it = maquinistas.find(*M1);
	Maquinista M2 = *it;
	maquinistas.erase(M2);
	M2.adicionaViagem(v);
	pair<tabHMaq::iterator, bool> res = maquinistas.insert(M2);
	if (res.second == true)
		return true;
	else return false;
	
}

bool Maquinistas::atribuiViagens(Bilheteira *b) {

	cout << endl << "Existem atualmente : "<< b->getNumViagens()  << " viagens"<< endl;
	if (!b->getNumViagens()) return false;
		
	bool primeiraVolta = true;
	int i = 0;
	int numViagens = b->getNumViagens();
	for (; i < numViagens; ){
		//percorre todos os maquinistas
		for (auto it : this->maquinistas) {
			if(it.getId() >= 0 || it.getNome() != "")
				maquinistas.erase(it);
				//se o maquinista ja tiver viagens antigas associadas
				if (primeiraVolta) {
				it.eliminaViagens();
			}
			//adiciona viagens ao maquinista
			if (it.adicionaViagem(b->getViagem(i))) {
				maquinistas.insert(it);
				i++;
			}
			//todoas as viagens ja foram atribuidas
			if (i >= b->getNumViagens())
				break;
		}
		primeiraVolta = false;
	}
	
	
	return true;
}

