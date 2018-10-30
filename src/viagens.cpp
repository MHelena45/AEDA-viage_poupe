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

std::string Viagem::getInfo(){
	stringstream ss;
	ss << origem << setw(16 - origem.length()) << destino << setw(8) << distancia <<" km" << setw(7)
			<< *c1 << setw(3) << " " << *dPartida << "    " << *hPartida << "       " << precoBase
			<< "€" <<"\n";
	return ss.str();

}


Compra::Compra(Viagem *v, Cartao *c, double pf, Datas *dc, Horas *hc){
	v1 = v;
	c1 = c;
	precoFinal = pf;
	dCompra = dc;
	hCompra = hc;
}

void Bilheteira::adicionaViagem(Viagem *v1){
	viagens.push_back(v1);
}

string Bilheteira::getInfo() const{
	stringstream ss;
	ss <<"id  " << "Origem" << setw(10) << "Destino" << setw(11) << "Distancia" << setw(10)
			<< "Comboios" << setw(9) << " " << "Data" << setw(5) << " " << "Hora"
			<< setw(3)<< " " <<"Preço base"<< "\n";
	for (unsigned int i = 0; i < viagens.size(); i++){
		ss << i << "   " << viagens.at(i)->getInfo();
	}
	return ss.str();
}
