#ifndef _CARTAO_H
#define _CARTAO_H

#include <iostream>
#include <string>
//#include "viagens.h"
#include <vector>
#include <sstream>
#include <stdlib.h>
#include "geral.h"


class Cartao {
	float precoMensal;
	int desconto;
	std::string nome;
public:
	/**
	 * Construtor: \n
	 * nome -> Nome do cartao \n
	 * prc  -> Preco mensal da subscricao do cartao \n
	 * desc -> Discount dado pelo cartao em todas as viagens \n
	 */
	Cartao(std::string nome, float prc, int desc);
	/**
	 * Retorna o preco mensal do cartao
	 */
	float getPreco() const;
	/**
	 * Retorna o desconto em todas as viagens dado pelo cartao
	 */
	int getDesconto() const;
	/**
	 * Retorna o nome do cartao usado
	 */
	std::string getNome() const;
	/**
	 * Retorna toda a informacao relacionada com o cartao
	 */
	std::string getInformacao() const;
};


class Registo {
	Cartao *c1;
	std::string nome;
	std::string profissao;
	datas datanascimento;
	//std::vector <Viagem *> viagens;
public:
	/**
	 * Construtor: \n
	 * *c -> Objeto da class Cartao, tipo de subscricao \n
	 * nome -> Nome do passageiro \n
	 * profissao -> Profissao do passageiro \n
	 * datanasc -> struct (int dia, int mes, int ano), recebe a data de nascimento \n
	 */
	Registo(Cartao *c, std::string nome, std::string profissao, datas datanasc);
	/**
	 * Retorna o nome do passageiro
	 */
	std::string getNome() const;

	Cartao* getCartao() const;
	/**
	 * Retorna a profissao do passageiro
	 */
	std::string getProfissao() const;
	/**
	 * Retorna a data de nascimento do passageiro
	 */
	datas getDatanascimento() const;
	/**
	 * Retorna toda a informacao do passageiro
	 */
	std::string getInformacao () const;
	/**
	 * Altera o tipo de subscricao do passageiro \n
	 * *c -> Objeto da class Cartao, tipo de subscricao para qual alterar
	 */
	void alterarCartao(Cartao *c);
	//void adicionaViagem(Viagem *v1);
};


class BaseClientes {
	std::vector <Cartao *> cartoes;
	std::vector<Registo *> regs;
	static int id;
public:

	/**
	 * Construtor vazio
	 */
	BaseClientes(){};
	/**
	 * Destructor
	 * Remove os registos da memoria
	 */
	~BaseClientes();


	void adicionaCartao(Cartao *c1);

	std::string getInfoCartao() const;

	Cartao *getCartao(int id) const;

	void alterarCartao(Cartao *c);

	/**
	 * Adiciona registos ao vector(regs) de clientes \n
	 * r1 -> objecto temporario da class registo, registo a adicionar a base de clientes
	 */
	void adicionaRegisto(Registo *r1);

	/**
	 * Retorna o nome de um passageiro especifico
	 */

	std::string getNome() const;
	/**
	 * Retorna a profissao de um passageiro especifico
	 */
	std::string getProfissao() const;
	/**
	 * Retorna toda a informacao de um passageiro especifico
	 */
	std::string getInformacao () const;
	/**
	 * Retorna a data de nascimento de um passageiro especifico
	 */
	datas getDataNascimento() const;
	/**
	 * Altera o valor da int estatica "id", esta variavel seleciona um registo do vector(regs) de clientes para utilizar \n
	 * id -> ID do passageiro
	 */
	void setId(int id);
	/**
	 * retorna o numero de clientes na base de dados
	 */
	int getNumRegistos() const;
};


#endif
