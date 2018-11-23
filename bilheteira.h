#ifndef _BILHETEIRA_H
#define _BILHETEIRA_H


#include "viagens.h"
#include "comboios.h"
#include "cartao.h"
#include "datashoras.h"

/**
 * CLASS Compra
 * Esta Classe cria os objectos que vao ficar no historico dos passageiros
 *
 */


class Compra {
	Viagem *v1;
	Cartao *c1;
	double precoFinal;
	Datas *dCompra;
	Horas *hCompra;
public:
	/**
	 * Construtor de compra
	 * @param v -> apontador para a viagem que se vai comprar
	 * @param c -> apontador para cartao co cliente que faz a compra
	 * pf -> preco final
	 * dc -> apontador para data da compra
	 * hc ->apontador para horas da compra
	 */
	Compra(Viagem *v, Cartao *c, double pf, Datas *dc, Horas *hc);
	/**
	 * Destrutor \n
	 * Elimina todos os dados de compra
	 */
	~Compra();
	/**
	 * @return informacao sobre a compra
	 */
	std::string getInfo() const;
	/**
	 * @return apontador para viagem comprada
	 */
	Viagem* getViagem() const;
	/**
	 * @return apontador para cartao usado para a compra
	 */
	Cartao* getCartao() const;
	/**
	 * @return apontador para data (ano-mes-dia) da compra
	 */
	Datas* getDataCompra() const;
	/**
	 * @return apontador para hora (horas:minutos) da compra
	 */
	Horas* getHoraCompra() const;
	/**
	 * @return preco final (ja depois do desconto) da compra
	 */
	double getPrecoFinal() const;

	/**
	 * Redefinicao do operador comparaa§ao
	 * @param c2 -> referencia para a compra com a qual se vai comparar
	 * @return se as duas compras sao iguais
	 */
	bool operator == (const Compra &c2);
};


/*
 * CLASS Bilheteira
 * Esta Classe guarda todas as viagens ativas e remove quando ja tiverem acontecido
 *
 */

class Bilheteira {
	std::vector<Viagem *> viagens;
	Frota *f;
public:
	/**
	 * Construtor de bilheteira
	 * @param frt -> apontador para frota de comboios
	 */
	Bilheteira(Frota *frt);
	/**
	 * Destrutor \n
	 * Elimina todos os dados de bilheteira
	 */
	~Bilheteira();
	/**
	 * @return numero de v fiagens
	 */
	int getNumViagens() const;
	/**
	 * @param id -> id da viagem
	 * @return apontador para viagem com esse id
	 */
	Viagem* getViagem(int id);
	/**
	 * @return informacao sobre a bilheteira
	 */
	std::string getInfo();

	/**
	 * @param v1 -> apontador para viagem a adicionar
	 */
	void adicionaViagem(Viagem *v1);
	/**
	 * Atualiza as viagens e elimina as viagens que ja decorreram
	 */
	void updateViagens();
	/**
	 * Abre "viagens.txt" e adiciona as viagens a bilheteira
	 */
	void loadViagens();
	/**
	 * Guarda as viagens da bilheteira em "viagens.txt"
	 */
	void saveViagens();
};


#endif
