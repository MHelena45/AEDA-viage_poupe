#ifndef _CARTAO_H
#define _CARTAO_H

#include "datashoras.h"

	/*
	 * CLASS CARTAO
	 * Esta Class e usada para criar cartoes com modalidades de desconto diferentes
	 *
	 */

class Cartao {
	double precoMensal;
	int desconto;
	std::string nome;
public:
	/**
	 * Construtor: \n
	 * nome -> Nome do cartao \n
	 * prc  -> Preco mensal da subscricao do cartao \n
	 * desc -> Discount dado pelo cartao em todas as viagens \n
	 */
	Cartao(std::string nome, double prc, int desc);
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
	bool operator == (const Cartao &ct1);
};


/*
 * CLASS REGISTO
 * Esta Class e usada para criar cartoes com modalidades de desconto diferentes
 *
 */


class Registo {
	Cartao *c1;
	std::string nome;
	std::string profissao;
	Datas *datanascimento;
	bool ativo;
	std::vector <Compra *> historico;
public:
	/**
	 * Construtor: \n
	 * *c -> Objeto da class Cartao, tipo de subscricao \n
	 * nome -> Nome do passageiro \n
	 * profissao -> Profissao do passageiro \n
	 * datanasc -> struct (int dia, int mes, int ano), recebe a data de nascimento \n
	 */
	Registo(Cartao *c, std::string nome, std::string profissao, Datas *datanasc);

	Registo(Cartao *c, std::string nome, std::string profissao, Datas *datanasc, bool ativo);

	~Registo();
	/**
	 * Retorna o nome do passageiro
	 */
	std::string getNome() const;
	/*
	 * Retorna o cartao que estar a ser usado por este passageiro
	 */
	Cartao* getCartao() const;
	/**
	 * Retorna a profissao do passageiro
	 */
	std::string getProfissao() const;
	/**
	 * Retorna a data de nascimento do passageiro
	 */
	std::string getDatanascimento() const;
	/*
	 * Retorna se o cartao esta activo ou nao
	 */
	bool getEstado() const;

	int getNumCompras() const;

	Compra* getCompra (int id) const;

	std::string getHistorico() const;

	/*
	 * Activa ou desactiva a subscricao
	 */
	void alterarEstado(bool at);
	/*
	 * Altera o cartao do passageiro
	 */
	void alterarCartao(Cartao *c);
	/*
	 * Adiciona uma compra ao historico do passageiro
	 */
	void adicionaCompra(Compra *c1);

	void eliminaCompra(Compra *c1);

	std::vector <Compra *> getCompraAtiva();

	std::string listCompraActiva ();


};

/*
 * CLASS BaseClientes
 * Esta Class guarda os apontadores para todos os cartoes e passageiros
 *
 */


class BaseClientes {
	std::vector <Cartao *> cartoes;
	std::vector<Registo *> regs;
	int id;
public:

	/**
	 * Construtor, inicializa id
	 */
	BaseClientes(){id = 0;};
	/**
	 * Destructor
	 * Remove os registos da memoria
	 */
	~BaseClientes();


	Registo* getRegisto() const;
	/**
	 * Retorna toda a informacao de um passageiro especifico
	 */
	std::string getInformacao () const;

	std::string getInfoCartao() const;
	/**
	 * retorna um cartao do vector cartoes
	 */
	Cartao* getCartao(int id) const;
	/*
	 * retorna o numero de cartoes
	 */
	int getNumCartoes() const;
	/**
	 * retorna o numero de clientes na base de dados
	 */
	int getNumRegistos() const;

	int getCartaoIndex (Cartao *ct1) const;
	/**
	 * Adiciona um cartao ao vector de cartoes
	 */
	void adicionaCartao(Cartao *c1);
	/**
	 * Adiciona registos ao vector(regs) de clientes \n
	 * r1 -> objecto temporario da class registo, registo a adicionar a base de clientes
	 */
	void adicionaRegisto(Registo *r1);
	/*
	 *Remove registos do vector(regs) de clientes
	 */
	void removeRegisto ();

	void setId(int id);

	void loadCartoes();

	void saveCartoes()const;

	void loadRegistos();

	void saveRegistos();
};


#endif
