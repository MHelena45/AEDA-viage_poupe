#ifndef _COMBOIOS_H
#define _COMBOIOS_H

#include "datashoras.h"

class Comboio {
protected:
	unsigned int lotacao; //capacidade do comboio
	int velocidade;
	double precoKM;
	std::string nome;
	unsigned int id;
public:
	/**
	 * Construtor de comboio
	 * @param numPassageiros -> numero de passageiros maximo do comboio
	 * @param velocidade -> velocidade do comboio
	 * @param precoKM -> preco por km do comboio
	 * @param nome -> nome do comboio
	 */
	Comboio(int numPassageiros, int velocidade, double precoKM, std::string nome);

	//acessors
	/**
	 * @return tipo do comboio
	 */
	virtual std::string getTipo() const;
	/**
	 * @return lotacao do comboio
	 */
	unsigned int getLotacao() const;
	/**
	 * @return velocidade do comboio
	 */
	int getVelocidade() const;
	/**
	 * @return preco por km do comboio
	 */
	double getPrecoKM() const;
	/**
	 * @return nome do comboio
	 */
	std::string getNome() const;
	/**
	 * @return id do comboio
	 */
	unsigned int getId() const;
	/**
	 * Destrutor \n
	 * Elimina todos os dados de comboio
	 */
	virtual ~Comboio(){};
	/**
	 * @param id -> novo id
	 */
	void setId(int id);
	/**
	 * @param os -> referencia para ofstream onde guardar a informacao
	 * @param c1 -> referencia para o comboio
	 */
	friend std::ostream& operator << (std::ostream &os, const Comboio &c1){
		os << c1.getNome() << "-" << c1.getTipo();
		return os;
	}

};

class AlfaPendular: public Comboio {
public:
	/**
	 * Construtor de alfapendular
	 * @param numPassageiros -> numero de passageiros maximo do comboio
	 * @param velocidade -> velocidade do comboio
	 * @param precoKM -> preco por km do comboio
	 * @param nome -> nome do comboio
	 */
	AlfaPendular(int numPassageiros, int velocidade, double precoKM, std::string nome);
	/**
	 * @return tipo do comboio ("AP")
	 */
	std::string getTipo() const;
	/**
	 * Destrutor \n
	 * Elimina todos os dados de alfapendular
	 */
	virtual ~AlfaPendular(){};
};

class Intercidades: public Comboio {
public:
	/**
	 * Construtor de intercidades
	 * @param numPassageiros -> numero de passageiros maximo do comboio
	 * @param velocidade -> velocidade do comboio
	 * @param precoKM -> preco por km do comboio
	 * @param nome -> nome do comboio
	 */
	Intercidades(int numPasseiros, int velocidade, double precoKMs, std::string nome);
	/**
	 * @return tipo do comboio ("IC")
	 */
	std::string getTipo() const;
	/**
	 * Destrutor \n
	 * Elimina todos os dados de intercidades
	 */
	virtual ~Intercidades(){};
};

class Frota{

public:
	/**
	 * Destrutor \n
	 * Elimina todos os dados de frota
	 */
	~Frota();

	std::vector <Comboio *> comboios;
	/**
	 * @return informacao de frota
	 */
	std::string getInformacao() const;
	/**
	 * @param id ->id do comboio
	 * @return apontador para comboio com esse id
	 */
	Comboio* getComboio(int id) const;
	/**
	 * @return numero de comboios da frota
	 */
	int getNumComboios() const;
	/**
	 * @param c1 -> apontador para comboio a adicionar a frota
	 */
	void adicionaComboio(Comboio *c1);
	/**
	 * Abre "comboios.txt" e adiciona os comboios a frota
	 */
	void loadComboios();
	/**
	 * Guarda os comboios da frota em "comboios.txt"
	 */
	void saveComboios() const;
};


#endif


