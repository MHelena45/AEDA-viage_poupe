#include "bilheteira.h"
#include "viagens.h"
#include "cartao.h"
#include "comboios.h"


using namespace std;

/*
 * Metodos class compra
 *
 */


//Construtor

Compra::Compra(Viagem *v, Cartao *c, double pf, Datas *dc, Horas *hc){
	v1 = v;
	c1 = c;
	precoFinal = pf;
	dCompra = dc;
	hCompra = hc;
}

//Acessors

std::string Compra::getInfo() const{
	stringstream ss;

	ss << *dCompra << "      " << *hCompra << "           " << left <<setfill(' ') <<setw(9)
		<< v1->getOrigem() << setw(9) << v1->getDestino() << *v1->getDataPartida() << "      "
		<< *v1->getHorasPartida()<< "           " << left <<setw(16) << setfill(' ')
		<<v1->getPrecoBase() << setw(6) << precoFinal << endl;

	return ss.str();
}

Viagem* Compra::getViagem() const {return v1;}

Cartao* Compra::getCartao() const{return this->c1;}

Datas* Compra::getDataCompra() const {return dCompra;}

Horas* Compra::getHoraCompra() const {return hCompra;}

double Compra::getPrecoFinal() const {return precoFinal;}


//Outros

bool Compra::operator == (const Compra &c2){
	float c1hf = this->dCompra->getHoursFormat() + this->hCompra->getHoursFormat();
	float c2hf = c2.dCompra->getHoursFormat() + c2.hCompra->getHoursFormat();

	if ( (c1hf == c2hf) && (*this->v1 == *c2.v1) && (this->precoFinal == c2.precoFinal))
		return true;

	return false;
}

/*
 * Metodos class Bilheteira
 *
 */

//Construtor

Bilheteira::Bilheteira(Frota *frt){
	f = frt;
}

//Acessors

int Bilheteira::getNumViagens() const {return viagens.size();}

Viagem* Bilheteira::getViagem(int id) {return viagens.at(id);}

string Bilheteira::getInfo(){
	updateViagens();
	stringstream ss;

	ss << left <<"id  " << setw(10) << "Origem" << setw(10) << "Destino" << setw(15)
			<< "Distancia(KM)" << setw(9) << "Comboio" << setw(13) << "Data"
			<< setw(8) <<  "Hora" << setw(16) << "Preco base(€)"<< setw(7) << "Vagas" << "\n";

	for (unsigned int i = 0; i < viagens.size(); i++){
		ss << i << "   " << viagens.at(i)->getInfo();
	}

	return ss.str();
}

//Outros

void Bilheteira::adicionaViagem(Viagem *v1){viagens.push_back(v1);}

void Bilheteira::updateViagens(){
	Horas *tempHora = getHoraActual();
	Datas *tempData = getDataActual();
	float horasActual = tempData->getHoursFormat() + tempHora->getHoursFormat();
	for (unsigned int i = 0; i < viagens.size(); i++){
		float horasViagem = viagens.at(i)->getDataPartida()->getHoursFormat() + viagens.at(i)->getHorasPartida()->getHoursFormat();
		if (horasActual > horasViagem){
			if ( !(viagens.at(i)->compraRegisto()) ){
				delete viagens.at(i);
				viagens.erase(viagens.begin()+i);


			}
			else{
				viagens.erase(viagens.begin()+i);
			}
		}
	}
}

void Bilheteira::loadViagens(){
	ifstream mfile;

	mfile.open ("viagens.txt");

	string statline;

	getline(mfile, statline);

	while (!mfile.eof() && !statline.empty()) {

		string origem, destino;
		double distancia;
		int comboioId;
		string datavgm, horavgm;
		int vagas, comprasAnonimas;

		getline (mfile, origem);
		getline (mfile, destino);
		mfile >> distancia;
		mfile >> comboioId;
		mfile.ignore(1);

		getline(mfile, datavgm);
		Datas *dvgm = new Datas (datavgm);
		getline(mfile, horavgm);
		Horas *hvgm = new Horas (horavgm);


		mfile >> vagas;



		mfile >> comprasAnonimas;

		Viagem *temp = new Viagem(origem, destino, distancia, f->getComboio(comboioId),
				dvgm, hvgm, vagas, comprasAnonimas);

		adicionaViagem(temp);
		mfile.ignore(1);
		getline(mfile, statline);
	}

	mfile.close();
	updateViagens();
}

void Bilheteira::saveViagens(){
	updateViagens();
	ofstream mfile;

	mfile.open ("viagens.txt");

	for (unsigned int i= 0; i < viagens.size(); i++){
		mfile << "Viagem" << endl << viagens.at(i)->getOrigem() << endl
				<< viagens.at(i)->getDestino() << endl << viagens.at(i)->getDistancia()
				<< endl << viagens.at(i)->getComboio()->getId()<< endl	<< *viagens.at(i)->getDataPartida()
				<< endl << *viagens.at(i)->getHorasPartida() << endl << viagens.at(i)->getVagas()
				<< endl << viagens.at(i)->getComprasAnonimas() << endl;
	}

	mfile.close();
}
