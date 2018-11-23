#ifndef _CARTAO_H
#define _CARTAO_H

#include "datashoras.h"

	/**
	 * CLASS CARTAO
	 * Esta Classe e usada para criar cartoes com modalidades de desconto diferentes
	 *
	 */

class Cartao {
	double precoMensal;
	int desconto;
	std::string nome;
public:
	/**
	 * Construtor de cartao
	 * @param nome -> Nome do cartao 
	 * @param prc -> Preco mensal da subscricao do cartao 
	 * @param desc -> Discount dado pelo cartao em todas as viagens
	 */
	Cartao(std::string nome, double prc, int desc);
	/**
	 * @return preco mensal do cartao
	 */
	float getPreco() const;
	/**
	 * @return desconto em todas as viagens dado pelo cartao
	 */
	int getDesconto() const;
	/**
	 * @return nome do cartao usado
	 */
	std::string getNome() const;
	/**
	 * @return toda a informacao relacionada com o cartao
	 */
	std::string getInformacao() const;
	/**
	 * Redefiniçao do operador comparaçao
	 * @param ct1 -> referencia para o cartao com o qual se vai comparar
	 * @return se o cartao e igual ao outro ou nao
	 */
	bool operator == (const Cartao &ct1);

};


/*
 * CLASS REGISTO
 * Esta Classe e usada para criar cartoes com modalidades de desconto diferentes
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
	 * Construtor do registo, esta ativo por predefiniçao
	 * @param *c -> apontador para objeto da class Cartao, tipo de subscricao
	 * @param nome -> nome do passageiro
	 * @param profissao -> profissao do passageiro
	 * @param datanasc -> apontador para struct (int dia, int mes, int ano), recebe a data de nascimento
	 */
	Registo(Cartao *c, std::string nome, std::string profissao, Datas *datanasc);

	/**
	 * Construtor do registo, pode estar ativo ou nao
	 * @param *c -> apontador para objeto da class Cartao, tipo de subscricao
	 * @param nome -> nome do passageiro
	 * @param profissao -> profissao do passageiro
	 * @param datanasc -> apontador para struct (int dia, int mes, int ano), recebe a data de nascimento
	 * @param ativo -> bool indica se o registo esta ativo
	 */
	Registo(Cartao *c, std::string nome, std::string profissao, Datas *datanasc, bool ativo);

	/**
	 * Destrutor \n
	 * Elimina todos os dados de registo
	 */
	~Registo();
	/**
	 * @return nome do passageiro
	 */
	std::string getNome() const;
	/*
	 * @return apontador para cartao que esta a ser usado por este passageiro
	 */
	Cartao* getCartao() const;
	/**
	 * @return profissao do passageiro
	 */
	std::string getProfissao() const;
	/**
	 * @return data de nascimento do passageiro
	 */
	std::string getDatanascimento() const;
	/**
	 * @return se o cartao esta activo ou nao
	 */
	bool getEstado() const;
	/**
	 * @return numero de compras feitas
	 */
	int getNumCompras() const;
	/**
	 * @param id -> id da compra
	 * @return apontador para compra com esse id 
	 */
	Compra* getCompra (int id) const;
	/**
	 * @return string com historico de compras
	 */
	std::string getHistorico() const;

	/*
	 * Activa ou desactiva a subscricao
	 * @param at -> estado atual da subscriÃ§ao
	 */
	void alterarEstado(bool at);
	/*
	 * Altera o cartao do passageiro
	 * @param c -> apontador para cartao a alterar
	 */
	void alterarCartao(Cartao *c);
	/*
	 * Adiciona uma compra ao historico do passageiro
	 * @param c1 -> apontador para compra a adicionar
	 */
	void adicionaCompra(Compra *c1);
	/*
	 * Elimina uma compra do historico do passageiro
	 * @param c1 -> apontador para compra a remover
	 */
	void eliminaCompra(Compra *c1);
	/*
	 * @return vector com apontadores para as compras ativas
	 */
	std::vector <Compra *> getCompraAtiva();
	/*
	 * @return string com as compras ativas
	 */
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
	 * Construtor de baseclientes, inicializa id
	 */
	BaseClientes(){id = 0;};
	/**
	 * Destructor\n
	 * Remove os registos da memoria
	 */
	~BaseClientes();

	/**
	 * @return apontador para registo de um passageiro especifico
	 */
	Registo* getRegisto() const;
	/**
	 * @return informaçao de um passageiro especifico
	 */
	std::string getInformacao () const;
	/**
	 * @return informaçao sobre o cartao
	 */
	std::string getInfoCartao() const;
	/**
	 * @param id -> id do cartao
	 * @return apontador para cartao do vector cartoes com esse id
	 */
	Cartao* getCartao(int id) const;
	/*
	 * @return numero de cartoes
	 */
	int getNumCartoes() const;
	/**
	 * @return numero de clientes na base de dados
	 */
	int getNumRegistos() const;
	/**
	 * @param ct1 -> apontador para cartao
	 * @return indice do cartao inserido
	 */
	int getCartaoIndex (Cartao *ct1) const;
	/**
	 * @param c1 -> apontador para cartao a adicionar ao vetor cartoes
	 */
	void adicionaCartao(Cartao *c1);
	/**
	 * Adiciona registos ao vector(regs) de clientes \n
	 * @param r1 -> apontador para objecto temporario da class registo, registo a adicionar a base de clientes
	 */
	void adicionaRegisto(Registo *r1);
	/*
	 * Remove registos do vector(regs) de clientes
	 */
	void removeRegisto ();
	/**
	 * @param id -> novo id
	 */
	void setId(int id);
	/**
	 * Abre "cartoes.txt" e adiciona os cartoes contidos a base de clientes
	 */
	void loadCartoes();
	/**
	 * Guarda os cartoes da base de clientes em "cartoes.txt"
	 */
	void saveCartoes()const;
	/**
	 * Abre "registos.txt" e adiciona os registos contidos a base de clientes
	 */
	void loadRegistos();
	/**
	 * Guarda os registos da base de clientes em "registos.txt"
	 */
	void saveRegistos();
};


#endif
