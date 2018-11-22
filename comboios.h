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

	Comboio(int numPasseiros, int velocidade, double precoKM, std::string nome);

	//acessors
	virtual std::string getTipo() const;

	unsigned int getLotacao() const;

	int getVelocidade() const;

	double getPrecoKM() const;

	std::string getNome() const;

	unsigned int getId() const;

	virtual ~Comboio(){};

	void setId(int id);

	friend std::ostream& operator << (std::ostream &os, const Comboio &c1){
		os << c1.getNome() << "-" << c1.getTipo();
		return os;
	}

};

class AlfaPendular: public Comboio {
public:

	AlfaPendular(int numPasseiros, int velocidade, double precoKM, std::string nome);

	std::string getTipo() const;

	virtual ~AlfaPendular(){};
};

class Intercidades: public Comboio {
public:

	Intercidades(int numPasseiros, int velocidade, double precoKMs, std::string nome);

	std::string getTipo() const;

	virtual ~Intercidades(){};
};

class Frota{

public:

	~Frota();

	std::vector <Comboio *> comboios;

	std::string getInformacao() const;

	Comboio* getComboio(int id) const;

	int getNumComboios() const;

	void adicionaComboio(Comboio *c1);

	void loadComboios();

	void saveComboios() const;
};


#endif


