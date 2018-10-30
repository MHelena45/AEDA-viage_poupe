#ifndef _COMBOIOS_H
#define _COMBOIOS_H

#include "geral.h"

class Comboio {
protected:
	int lotacao; //capacidade do comboio
	//bool ocupado;
	int velocidade;
	double precoKM;
	std::string nome;
public:
	Comboio(int numPasseiros, int velocidade, double precoKM, std::string nome);

	virtual std::string getTipo() const;

	//acessors
	int getLotacao() const;
	int getVelocidade() const;
	double getPrecoKM() const;
	std::string getNome() const;
	virtual ~Comboio(){};

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

	std::vector <Comboio *> comboios;
	void adicionaComboio(Comboio *c1);
	std::string getInformacao() const;
};


#endif


