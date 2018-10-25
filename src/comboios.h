#ifndef _COMBOIOS_H
#define _COMBOIOS_H

#include "geral.h"
#include <string>
#include <vector>
using namespace std;

class Comboio {
protected:
	int lotacao; //capacidade do comboio
	//bool ocupado;
	int velocidade;
	double precoKM;
	string nome;
public:
	Comboio(int numPasseiros, int velocidade, double precoKM, string nome);

	virtual string getTipo() const;

	//acessors
	int getLotacao() const;
	int getVelocidade() const;
	double getPrecoKM() const;
	string getNome() const;



	bool getOcupado();
	bool getMeioCheio();
	bool cheio();
	virtual ~Comboio(){};
};

class AlfaPendular: public Comboio {
public:
	AlfaPendular(int numPasseiros, int velocidade, double precoKM, string nome);
	string getTipo() const;
	virtual ~AlfaPendular(){};
};

class Intercidades: public Comboio {
public:
	Intercidades(int numPasseiros, int velocidade, double precoKMs, string nome);
	string getTipo() const;
	virtual ~Intercidades(){};
};

class Frota{ //Esta classe vai ser usada para mostrar todos os comboios que existem

public:
	vector <Comboio *> Comboios;
	void adicionaComboio(Comboio *c1);
	string getInformacao();
};


#endif


