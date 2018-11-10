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
	Datas* getDataPartida() const;
	Horas* getHorasPartida() const;
	double getPrecoBase () const;
	std::string getOrigem() const;
	std::string getDestino() const;
	std::string getInfo() const;
	int reservaBilhete(bool reg);
	int devolveBilhete(bool reg);
	double getPrecoFinal();
	double getPrecoFinal(Cartao *c);
	bool operator == (const Viagem &v2);
	bool compraRegisto() const;

};

/*
 * CLASS Compra
 * Esta Class cria os objectos que vao ficar no historico dos passageiros
 *
 */

class Compra {
	Viagem *v1;
	Cartao *c1;
	double precoFinal;
	Datas *dCompra;
	Horas *hCompra;
public:
	Compra(Viagem *v, Cartao *c, double pf, Datas *dc, Horas *hc);
	std::string getInfo() const;
	Viagem* getViagem() const;
	bool operator == (const Compra &c2);
};

/*
 * CLASS Compra
 * Esta Class guarda todas as viagens ativas e remove quando ja nao forem necessarias
 *
 */

class Bilheteira {
	std::vector<Viagem *> viagens;
public:
	void adicionaViagem(Viagem *v1);
	Viagem* getViagem(int id);
	void updateViagens();
	std::string getInfo();
};



#endif
