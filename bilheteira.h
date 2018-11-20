#ifndef _BILHETEIRA_H
#define _BILHETEIRA_H

#include "viagens.h"
#include "comboios.h"
#include "cartao.h"
#include "geral.h"


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
	~Compra();
	std::string getInfo() const;
	Viagem* getViagem() const;
	Cartao* getCartao() const;
	Datas* getDataCompra() const;
	Horas* getHoraCompra() const;
	double getPrecoFinal() const;


	bool operator == (const Compra &c2);
};

/*
 * CLASS Bilheteira
 * Esta Class guarda todas as viagens ativas e remove quando ja tiverem acontecido
 *
 */

class Bilheteira {
	std::vector<Viagem *> viagens;
	Frota *f;
public:
	Bilheteira(Frota *frt);
	~Bilheteira();
	int getNumViagens() const;
	Viagem* getViagem(int id);
	std::string getInfo();

	void adicionaViagem(Viagem *v1);
	void updateViagens();
	void loadViagens();
	void saveViagens();
};



































#endif
