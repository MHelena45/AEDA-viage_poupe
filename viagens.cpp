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

}

std::string Viagem::getInfo() const{
	stringstream ss;
	ss << left << setw(10) << origem << setw(10) << destino << setw(15) << distancia
			<< *c1 << "    "  << *dPartida << "   "	<< *hPartida << "   " << left << setfill(' ')
			<< setw(16) << precoBase  <<  setfill(' ') << setw(5) << vagas <<"\n";
	return ss.str();
}

int Viagem::reservaBilhete(){
	if (vagas <= 0)
		return -1;
	vagas--;
	return 0;
}

int Viagem::devolveBilhete(){
	if (vagas < c1->getLotacao())
		return -1;
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
		return precoBase * 0.30 * ((double)c->getDesconto() / 100);

	return precoBase * ((double)c->getDesconto() / 100);


}


Compra::Compra(Viagem *v, Cartao *c, double pf, Datas *dc, Horas *hc){
	v1 = v;
	c1 = c;
	precoFinal = pf;
	dCompra = dc;
	hCompra = hc;
}

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

string Bilheteira::getInfo() const{
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
