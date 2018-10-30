#ifndef _CARTAO_H
#define _CARTAO_H


#include "geral.h"

	/*
	 * CLASS CARTAO
	 * Esta Class e usada para criar cartoes com modalidades de desconto diferentes
	 *
	 */

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
	/**
	 * Retorna toda a informacao do passageiro
	 */
	std::string getInformacao () const;
	/*
	 * Retorna se o cartao esta activo ou nao
	 */
	bool getEstado() const;
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


};

/*
 * CLASS BaseClientes
 * Esta Class guarda os apontadores para todos os cartoes e passageiros
 *
 */


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
	std::string getDataNascimento() const;
	/*
	 * Retorna a informaçao de um cartao
	 */
	std::string getInfoCartao() const;
	/*
	 * retorna um cartao do vector
	 */
	Cartao *getCartao(int id) const;
	/*
	 * retorna o numero de cartoes
	 */
	unsigned int getNumCartoes() const;
	/**
	 * retorna o numero de clientes na base de dados
	 */
	unsigned int getNumRegistos() const;
	/*
	 * Retorna se um registo esta activo ou nao
	 */
	bool getEstado() const;
	/*
	 * Adiciona um cartao ao vector de cartoes
	 */
	void adicionaCartao(Cartao *c1);
	/*
	 * Altera o cartao de um passageiro
	 */
	void alterarCartao(Cartao *c);
	/*
	 * Activa ou desactiva a subscricao de um passageiro
	 */
	void alterarEstado(bool est);
	/**
	 * Adiciona registos ao vector(regs) de clientes \n
	 * r1 -> objecto temporario da class registo, registo a adicionar a base de clientes
	 */
	void adicionaRegisto(Registo *r1);
	/*
	 *Remove registos do vector(regs) de clientes
	 */
	void removeRegisto ();
	/**
	 * Altera o valor da int estatica "id", esta variavel seleciona um registo do vector(regs) de clientes para utilizar \n
	 * id -> ID do passageiro
	 */
	void setId(int id);

};


#endif
