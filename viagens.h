#ifndef _VIAGENS_H
#define _VIAGENS_H

#include "geral.h"
#include "comboios.h"
#include "cartao.h"

/*
 * CLASS Viagem
 * Esta Class cria uma viagem e controla as vagas de essa viagem
 *
 */

class Viagem{
	std::string origem, destino;
	double distancia;
	Comboio *c1;
	Datas *dPartida;
	Horas *hPartida;
	double precoBase;
	unsigned int vagas;
	unsigned int comprasAnonimas;
public:

	Viagem(std::string ori, std::string dest, double dist, Comboio *c, Datas *dp, Horas *hp);

	Viagem(std::string ori, std::string dest, Datas *dp, Horas *hp,  double precoBase);

	Viagem(std::string ori, std::string dest, double dist, Comboio *c, Datas *dp, Horas *hp, int vagas, int comprasAnon);


	Datas* getDataPartida() const;

	Horas* getHorasPartida() const;

	double getPrecoBase () const;

	std::string getOrigem() const;

	std::string getDestino() const;

	double getDistancia() const;

	Comboio* getComboio() const;

	unsigned int getVagas() const;

	unsigned int getComprasAnonimas() const;

	std::string getInfo() const;


	int reservaBilhete(bool reg);

	int devolveBilhete(bool reg);

	double getPrecoFinal();

	double getPrecoFinal(Cartao *c);

	bool operator == (const Viagem &v2);

	bool compraRegisto() const;

};


#endif
