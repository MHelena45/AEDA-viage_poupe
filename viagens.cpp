#include "viagens.h"
using namespace std;




Viagem::Viagem(std::string ori, std::string dest, double dist, Comboio *c, Datas *dp, Horas *hp){
	origem = ori;
	destino = dest;
	distancia = dist;
	c1 = c;
	dPartida = dp;
	hPartida = hp;
	vagas = c->getLotacao();
	precoBase = c1->getPrecoKM() * distancia;
	comprasAnonimas = 0;
}

std::string Viagem::getInfo() const{
	stringstream ss;
	ss << left << setw(10) << origem << setw(10) << destino << setw(15) << distancia
			<< *c1 << "    "  << *dPartida << "   "	<< *hPartida << "   " << left << setfill(' ')
			<< setw(16) << precoBase  <<  setfill(' ') << setw(5) << vagas <<"\n";
	return ss.str();
}

int Viagem::reservaBilhete(bool reg){
	if (vagas <= 0)
		return -1;
	vagas--;
	if (!reg)
		comprasAnonimas++;
	return 0;
}

int Viagem::devolveBilhete(bool reg){
	if (vagas >= c1->getLotacao())
		return -1;
	if (!reg){
		if (comprasAnonimas == 0)
			return -1;
		else comprasAnonimas--;
	}
	vagas++;
	return 0;
}

Datas* Viagem::getDataPartida() const{ return dPartida;}

Horas* Viagem::getHorasPartida() const{return hPartida;}

double Viagem::getPrecoBase () const{return precoBase;}

std::string Viagem::getOrigem() const {return origem;}

std::string Viagem::getDestino() const{return destino;}


double Viagem::getPrecoFinal(){

	Horas *tempHora = getHoraActual();
	Datas *tempData = getDataActual();

	float horasActual = tempData->getHoursFormat() + tempHora->getHoursFormat();
	float horasViagem = getDataPartida()->getHoursFormat() + getHorasPartida()->getHoursFormat();

	if ( ( horasViagem - horasActual ) <= 48 && ( horasViagem - horasActual ) > 0
			&& vagas > (c1->getLotacao() / 2))
		return precoBase * 0.30;

	return precoBase;
}

double Viagem::getPrecoFinal(Cartao *c){
	Horas *tempHora = getHoraActual();
	Datas *tempData = getDataActual();

	float horasActual = tempData->getHoursFormat() + tempHora->getHoursFormat();
	float horasViagem = getDataPartida()->getHoursFormat() + getHorasPartida()->getHoursFormat();

	if ( ( horasViagem - horasActual ) <= 48 && ( horasViagem - horasActual ) > 0
			&& vagas > (c1->getLotacao() / 2))
		if (c->getDesconto() < 70)
			return precoBase * 0.30;

	return precoBase * ((double)c->getDesconto() / 100);
}

bool Viagem::operator == (const Viagem &v2){
	float v1hf = this->dPartida->getHoursFormat()+this->hPartida->getHoursFormat();
	float v2hf = v2.dPartida->getHoursFormat() + v2.hPartida->getHoursFormat();
	if ( (v1hf == v2hf) && (this->destino == v2.destino) && (this->origem == v2.origem) && (this->distancia == v2.distancia)
			&& this->precoBase == v2.precoBase)
		return true;
	return false;

}

bool Viagem::compraRegisto() const{
	if ( (vagas + comprasAnonimas) == c1->getLotacao())
		return false;
	return true;
}


Compra::Compra(Viagem *v, Cartao *c, double pf, Datas *dc, Horas *hc){
	v1 = v;
	c1 = c;
	precoFinal = pf;
	dCompra = dc;
	hCompra = hc;
}

bool Compra::operator == (const Compra &c2){
	float c1hf = this->dCompra->getHoursFormat() + this->hCompra->getHoursFormat();
	float c2hf = c2.dCompra->getHoursFormat() + c2.hCompra->getHoursFormat();

	if ( (c1hf == c2hf) && (*this->v1 == *c2.v1) && (this->precoFinal == c2.precoFinal))
		return true;

	return false;
}

Viagem* Compra::getViagem() const {return v1;}

std::string Compra::getInfo() const{
	stringstream ss;

	ss << *dCompra << "      " << *hCompra << "           " << left <<setfill(' ') <<setw(9)
		<< v1->getOrigem() << setw(9) << v1->getDestino() << *v1->getDataPartida() << "      "
		<< *v1->getHorasPartida()<< "           " << left <<setw(16) << setfill(' ')
		<<v1->getPrecoBase() << setw(6) << precoFinal << endl;

	return ss.str();
}


void Bilheteira::adicionaViagem(Viagem *v1){
	viagens.push_back(v1);
}

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

Viagem* Bilheteira::getViagem(int id) {
	return viagens.at(id);
}

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
