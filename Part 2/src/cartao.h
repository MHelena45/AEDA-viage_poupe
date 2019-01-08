#ifndef _CARTAO_H
#define _CARTAO_H

#include "datashoras.h"
using namespace std;
	/**
	 * CLASS CARTAO\n
	 * Esta Classe e usada para criar cartoes com modalidades de desconto diferentes
	 *
	 */
class Cartao {
	string nome;
	double precoMensal;
	int desconto;

public:
	/**
	 * @brief Construtor de cartao
	 * @param nome  Nome do cartao
	 * @param prc  Preco mensal da subscricao do cartao
	 * @param desc Valor a pagar depois do desconto, ex: 25% de desconto = 75
	 */
	Cartao(string n, double prc, int desc) : nome(n), precoMensal(prc), desconto(desc) { };

	/**
	 * @return Preco mensal do cartao
	 */
	float getPreco() const;
	/**
	 * @return Desconto em todas as viagens dado pelo cartao
	 */
	int getDesconto() const;
	/**
	 * @return Nome do cartao usado
	 */
	string getNome() const;
	/**
	 * @return toda a informacao relacionada com o cartao
	 */
	string getInformacao() const;
	/**
	 * @brief atribui nome ao cartao
	 * @nome novo nome do cartao
	 */
	void setNome(string nome);
	/**
	 * @brief atribui preco ao cartao
	 * @nome prc preco do cartao
	 */
	void setPreco(double prc);
	/**
	 * @brief atribui preco ao cartao
	 * @nome prc preco do cartao
	 */
	void setDesconto (int dsc);
	/**
	 * Redefinicao do operador comparacao
	 * @param ct1 Referencia para o cartao com o qual se vai comparar
	 * @return se o cartao e igual ao outro ou nao
	 */
	bool operator == (const Cartao &ct1);

};


/**
 * CLASS REGISTO\n
 * Esta Classe e usada para criar cartoes com modalidades de desconto diferentes
 *
 */
class Registo {
	Cartao *c1;
	string nome;
	string profissao;
	Datas datanascimento;
	bool ativo;
	vector <Compra *> historico;
public:
	/**
	 * @brief Construtor do registo, esta ativo por predefinicao
	 * @param *c Apontador para objeto da class Cartao, tipo de subscricao
	 * @param nome Nome do passageiro
	 * @param profissao Profissao do passageiro
	 * @param datanasc Apontador para struct (int dia, int mes, int ano), recebe a data de nascimento
	 */
	Registo(Cartao *c, string nome, string profissao, Datas datanasc);

	/**
	 * @brief Construtor do registo, pode estar ativo ou nao
	 * @param *c Apontador para objeto da class Cartao, tipo de subscricao
	 * @param nome Nome do passageiro
	 * @param profissao Profissao do passageiro
	 * @param datanasc Apontador para struct (int dia, int mes, int ano), recebe a data de nascimento
	 * @param ativo Bool indica se o registo esta ativo
	 */
	Registo(Cartao *c, string nome, string profissao, Datas datanasc, bool ativo);

	/**
	 * @brief Destrutor \n
	 * Destroi todos os objectos de compra do vector historico.\n
	 * Destroi tambem o objecto com a data de nascimento.
	 */
	~Registo();
	/**
	 * @return Nome do passageiro
	 */
	string getNome() const;
	/**
	 * @return Apontador para cartao que esta a ser usado por este passageiro
	 */
	Cartao* getCartao() const;
	/**
	 * @return Profissao do passageiro
	 */
	string getProfissao() const;
	/**
	 * @return Data de nascimento do passageiro
	 */
	string getDatanascimento() const;
	/**
	 * @return Se o cartao esta activo ou nao
	 */
	bool getEstado() const;
	/**
	 * @return Numero de compras feitas
	 */
	int getNumCompras() const;
	/**
	 * @param id ID da compra
	 * @return Apontador para compra com esse id
	 */
	Compra* getCompra (int id) const;
	/**
	 * @return String com historico de compras
	 */
	std::string getHistorico() const;

	/**
	 * @brief Activa ou desactiva a subscricao
	 * @param at escolhe ativar ou desativar cartao
	 */
	void alterarEstado(bool at);
	/**
	 * @brief Altera o cartao do passageiro
	 * @param c Apontador para cartao a alterar
	 */
	void alterarCartao(Cartao *c);
	/**
	 * @brief Adiciona uma compra ao historico do passageiro
	 * @param c1 Apontador para compra a adicionar
	 */
	void adicionaCompra(Compra *c1);
	/**
	 * @brief Elimina uma compra do historico do passageiro
	 * @param c1 Apontador para compra a remover
	 */
	void eliminaCompra(Compra *c1);
	/**
	 * @return Vector com apontadores para as compras ativas, isto e compras em que a viagem ainda nao partiu
	 */
	vector <Compra *> getCompraAtiva();
	/**
	 * @return Informacao sobre as viagens activas numa string em forma de tabela
	 */
	string listCompraActiva ();


};

/**
 * CLASS BaseClientes\n
 * Esta Class guarda os apontadores para todos os cartoes e passageiros
 *
 */
class BaseClientes {
	vector <Cartao *> cartoes;
	vector<Registo *> regs;
	int id;
public:

	/**
	 * @briefConstrutor de baseclientes, inicializa id do registo no vetor que vai ser usado
	 * para aceder a dados do registo
	 */
	BaseClientes(){id = 0;};
	/**
	 * @brief Destructor\n
	 * Destroi todos os objectos de Registos e Cartoes guardados
	 */
	~BaseClientes();

	/**
	 * @return Apontador para registo de um passageiro especifico
	 */
	Registo* getRegisto() const;
	/**
	 * @return Informacao de um passageiro especifico numa string em forma de tabela
	 */
	string getInformacao () const;
	/**
	 * @return informacao sobre o cartao
	 */
	string getInfoCartao() const;
	/**
	 * @param id ID do cartao
	 * @return Apontador para cartao do vector cartoes com esse id
	 */
	Cartao* getCartao(unsigned int id) const;
	/**
	 * @return Numero de cartoes
	 */
	int getNumCartoes() const;
	/**
	 * @return Numero de clientes na base de dados
	 */
	int getNumRegistos() const;
	/**
	 * @param ct1 -Apontador para cartao
	 * @return Indice do cartao inserido
	 */
	int getCartaoIndex (Cartao *ct1) const;
	/**
	 * @param c1 Apontador para cartao a adicionar ao vetor cartoes
	 */
	void adicionaCartao(Cartao *c1);
	/**
	 * Adiciona registos ao vector(regs) de clientes \n
	 * @param r1 Registo a adicionar a base de clientes
	 */
	void adicionaRegisto(Registo *r1);
	/**
	 * @brief Remove registos do vector(regs) de clientes
	 */
	void removeRegisto ();
	/**
	 * @brief Remove Cartoes do vector(cratoes)
	 */
	void removeCartao (int id);
	/**
	 * @param id ID do cliente a aceder dados
	 */
	void setId(int id);
	/**
	 * @brief Abre "cartoes.txt" e adiciona os cartoes contidos a base de clientes
	 */
	void loadCartoes();
	/**
	 * @brief Guarda os cartoes da base de clientes em "cartoes.txt"
	 */
	void saveCartoes()const;
	/**
	 * @brief Abre "registos.txt" e adiciona os registos contidos a base de clientes
	 */
	void loadRegistos();
	/**
	 * @brief Guarda os registos da base de clientes em "registos.txt"
	 */
	void saveRegistos();
};


#endif
