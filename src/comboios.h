/*#ifndef _COMBOIOS_H
#define _COMBOIOS_H

#include "geral.h"
#include <string>
#include <vector>
using namespace std;

class Comboio {//outras caracteristicas?
protected:
	int lotacao;
	int NumMax; //capacidade do comboio
	bool ocupado;//se ja tem uma viagem atribuida
	hora horario;
public:
	Comboio(int horas, int minutos,int NumPasseiros);
	int getlotacao();
	virtual string getInformacao();
	bool getOcupado();
	bool getMeioCheio();
	bool cheio();
	virtual ~Comboio(){};

};

class AlfaPendular: public Comboio {
public:
	AlfaPendular( int horas, int minutos, int NumPasseiros);
	string getInformacao();
};

class Intercidades: public Comboio {
public:
	Intercidades(int HORAS, int MINUTOS,int NumeroPasseiros);
	string getInformacao();
};

class Frota{ //Esta classe vai ser usada para mostrar todos os comboios que existem
	vector <AlfaPendular *> alfas;
	vector <Intercidades *> inters;
public:
	void adicionaAlfa(AlfaPendular *a1);
	void adicionaInter(Intercidades *I1);
	string getInformacao();
};


#endif


