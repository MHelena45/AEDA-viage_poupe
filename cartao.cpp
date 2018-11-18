#include "cartao.h"
#include "bilheteira.h"

using namespace std;

/*
 * Metodos class Cartao
 *
 *
 */

// Construtor

Cartao::Cartao(string nome, float prc, int desc){
	this->precoMensal = prc;
	this->desconto = desc;
	this->nome = nome;
}

// Acessors

float Cartao::getPreco() const{
	return precoMensal;
}

int Cartao::getDesconto() const {
	return desconto;
}

string Cartao::getNome() const{
	return nome;
}

string Cartao::getInformacao() const{
	return this->nome + " - Pre�o: " + to_string(this->precoMensal).substr(0, 6) + "�/m�s - Desconto: " + to_string(100 - this->desconto) + "% por Viagem";
}

//Outros

bool Cartao::operator == (const Cartao &ct1){
	if (this->getNome() == ct1.getNome())
		return true;
	return false;
}


/*
 * Metodos class Registo
 *
 *
 */

// Construtors

Registo::Registo(Cartao *c, std::string nome, std::string profissao, Datas *datanasc){
	c1 = c;
	this->nome = nome;
	this->profissao = profissao;
	this->datanascimento = datanasc;
	this->ativo = true;
}

Registo::Registo(Cartao *c, std::string nome, std::string profissao, Datas *datanasc, bool ativo){
	c1 = c;
	this->nome = nome;
	this->profissao = profissao;
	this->datanascimento = datanasc;
	this->ativo = ativo;

}

// Acessors

string Registo::getNome() const{return nome;}

Cartao* Registo::getCartao() const {return c1;}

string Registo::getProfissao() const{return profissao;}

string Registo::getDatanascimento() const{
	stringstream ss;
	ss << *datanascimento;

	return ss.str();
}

bool Registo::getEstado() const{return ativo;}

int Registo::getNumCompras() const {return historico.size();}

Compra* Registo::getCompra (int id) const {return historico.at(id);}

std::string Registo::getHistorico() const{
	stringstream ss;

	ss << left << setw(16) <<"Data da compra" << setw(16)  <<"Hora da Compra"
			<< setw(9) << "Origem" << setw(9) << "Destino" << setw(16)
			<< "Data da viagem" << setw(16) <<"Hora da viagem" << setw(16)
			<< "Preco Base(�)" << setw(10) <<"Total(�)" << endl;

	for (unsigned int i = 0; i < historico.size(); i++){
		ss << historico.at(i)->getInfo();
	}


	return ss.str();
}

//Outros

void Registo::alterarEstado(bool at){ativo = at;}

void Registo::alterarCartao(Cartao *c){c1=c;}

void Registo::adicionaCompra(Compra *c1){historico.push_back(c1);}

void Registo::eliminaCompra(Compra *c1){

	for (unsigned int i = 0; i < historico.size();i++){
		if (*historico.at(i) == *c1){
			historico.erase(historico.begin()+i);
			delete c1;
			break;
		}
	}
}

vector <Compra *> Registo::getCompraAtiva(){
	vector <Compra *> temp;

	Horas *tempHora = getHoraActual();
	Datas *tempData = getDataActual();
	float horasActual = tempData->getHoursFormat() + tempHora->getHoursFormat();


	for (unsigned int i = 0; i < historico.size(); i++){
		Viagem *v =	historico.at(i)->getViagem();
		float horasViagem = v->getDataPartida()->getHoursFormat() + v->getHorasPartida()->getHoursFormat();
		if (horasViagem > horasActual)
			temp.push_back(historico.at(i));
	}


	return temp;

}

string Registo::listCompraActiva(){

	vector <Compra *> c = getCompraAtiva();

	stringstream ss;

	ss <<"ID  " <<left << setw(16) <<"Data da compra" << setw(16)  <<"Hora da Compra"
			<< setw(9) << "Origem" << setw(9) << "Destino" << setw(16)
			<< "Data da viagem" << setw(16) <<"Hora da viagem" << setw(16)
			<< "Preco Base(�)" << setw(10) <<"Total(�)" << endl;

	for (unsigned int i = 0; i < c.size(); i++){
		ss << i << "   " << c.at(i)->getInfo();
	}


	return ss.str();

}

/*
 * Metodos class BaseClientes
 *
 *
 */

// Destructor
BaseClientes::~BaseClientes(){
	for (unsigned int i = 0; i < regs.size(); i++)
		delete regs.at(i);
}

// Acessors

Registo* BaseClientes::getRegisto() const{
	return regs.at(id);
}

string BaseClientes::getInformacao () const {
	stringstream ss;
	ss << "Nome: " << regs.at(id)->getNome() << " -- Cartao: " << "\"" <<  regs.at(id)->getCartao()->getNome()
			<< "\"" << " -- Profissao: " << regs.at(id)->getProfissao() << " -- Data de Nascimento: "
			<< regs.at(id)->getDatanascimento();

	return ss.str();
}

string BaseClientes::getInfoCartao() const{
	stringstream ss;
	for (unsigned int i=0; i < cartoes.size(); i++){
		ss << i << " - " << cartoes.at(i)->getInformacao() << "\n\n";
	}
	return ss.str();
}

Cartao* BaseClientes::getCartao(int id) const {return cartoes.at(id);}

unsigned int BaseClientes::getNumCartoes () const {return cartoes.size();}

unsigned int BaseClientes::getNumRegistos() const{return this->regs.size();}

int BaseClientes::getCartaoIndex (Cartao *ct1) const{
	for (unsigned int i = 0; i < cartoes.size(); i++){
		if (ct1 == cartoes.at(i))
			return i;
	}
	return -1;
}

// Outros

void BaseClientes::adicionaCartao(Cartao *c1){this->cartoes.push_back(c1);}

void BaseClientes::adicionaRegisto(Registo *r1){regs.push_back(r1);}

void BaseClientes::removeRegisto (){regs.at(id)->alterarEstado(false);}

void BaseClientes::setId(int id){this->id = id;}

void BaseClientes::loadCartoes(){

	ifstream mfile;

	mfile.open ("cartoes.txt");

	while (!mfile.eof()) {
		float precoMensal;
		int desconto;
		string nome;

		getline(mfile, nome);
		if (nome == "")
			break;

		mfile >> precoMensal;
		mfile.ignore(1);
		mfile >> desconto;
		mfile.ignore(1);
		Cartao *c1 = new Cartao(nome, precoMensal, desconto);
		adicionaCartao(c1);
	}
	mfile.close();


}

void BaseClientes::saveCartoes()const{

	ofstream mfile;

	mfile.open ("cartoes.txt");

	for (unsigned int i= 0; i < cartoes.size(); i++){
		mfile << cartoes.at(i)->getNome() << endl << cartoes.at(i)->getPreco() << " "
				<< cartoes.at(i)->getDesconto() << endl;
	}

	mfile.close();

}

void BaseClientes::loadRegistos(){
	ifstream mfile;

	mfile.open ("Registos.txt");

		while (!mfile.eof()) {
			string nome;
			int cIndex;
			string origem, destino;
			string profissao;
			string datanasc, datavgm, datacomp, horacomp, horavgm;
			bool ativo;
			string at;
			string statline;
			double precoBase, precoFinal;

			getline(mfile, nome);

			if (nome == "Cliente:")
				continue;


			mfile >> cIndex;
			Cartao *temp = getCartao(cIndex);

			mfile >> profissao;
			mfile.ignore(1);

			getline(mfile, datanasc);
			Datas *nasc = new Datas (datanasc);
			getline (mfile, at);
			if (at == "Ativo")
				ativo = true;
			else ativo = false;

			Registo *tReg = new Registo (temp, nome, profissao, nasc, ativo);
			adicionaRegisto(tReg);

			getline (mfile, statline);
			if (statline.empty())
				break;
			if (statline == "Cliente:")
				continue;

			//Carregar Historico
			while (statline != "Cliente:" && !statline.empty()){

				mfile >> cIndex;
				Cartao *tempH = getCartao(cIndex);
				mfile.ignore(1);

				getline(mfile, datacomp);
				Datas *dcmp = new Datas (datacomp);
				getline (mfile, horacomp);
				Horas *hcomp = new Horas (horacomp);

				getline(mfile, origem);
				getline(mfile, destino);

				getline(mfile, datavgm);
				Datas *vgm = new Datas (datavgm);
				getline (mfile, horavgm);
				Horas *hvgm = new Horas (horavgm);

				mfile >> precoBase;
				mfile >> precoFinal;
				mfile.ignore(1);
				Viagem *tv = new Viagem(origem, destino, vgm,hvgm, precoBase);
				Compra *tmpCompra = new Compra(tv, tempH, precoFinal, dcmp, hcomp);
				tReg->adicionaCompra(tmpCompra);

				getline(mfile, statline);
			}

			if (statline.empty())
				break;
			if (statline == "Cliente:")
				continue;
		}

		mfile.close();
}

void BaseClientes::saveRegistos(){

	ofstream mfile;

	mfile.open ("Registos.txt");

	for (unsigned int i = 0; i < regs.size(); i++){
		mfile << "Cliente:" << endl;

		mfile << regs.at(i)->getNome() << endl << getCartaoIndex(getCartao(id)) << " " << endl << regs.at(i)->getProfissao() << endl
				<< regs.at(i)->getDatanascimento() << endl;
		if (regs.at(i)->getEstado())
			mfile << "Ativo" << endl;
		else mfile << "Desactivado" << endl;

		if (regs.at(i)->getNumCompras() > 0){

			for (int j = 0; j < regs.at(i)->getNumCompras(); j++){
				Viagem *temp = regs.at(i)->getCompra(j)->getViagem();
				mfile << "Compra:" << endl <<getCartaoIndex(regs.at(i)->getCartao()) << endl
						<< *regs.at(i)->getCompra(j)->getDataCompra() << endl
						<< *regs.at(i)->getCompra(j)->getHoraCompra() << endl
						<<temp->getOrigem() << endl	<< temp->getDestino() << endl
						<< *temp->getDataPartida() << endl <<*temp->getHorasPartida()
						<< endl << temp->getPrecoBase() << endl
						<< regs.at(i)->getCompra(j)->getPrecoFinal() << endl;
			}
		}
	}



	mfile.close();

}


