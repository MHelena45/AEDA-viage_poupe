#ifndef MAQUINISTAS_H_
#define MAQUINISTAS_H_

#include <unordered_set>
#include "datashoras.h"

using namespace std;

class Maquinista
{
	string nome, apelido;
	bool ativo;
	unsigned id;
public:
	Maquinista(string nome, string apelido, int id, bool atual);
	Maquinista(string nome, string apelido, int id);
	string getNome() const { return nome; } ;
	string getApelido() const { return apelido; } ;
	unsigned getId() const { return id; } ;
	friend ostream & operator << (ostream &out, const Maquinista & M);
};

struct eqMaquinista {
	bool operator() (const Maquinista& M1, const Maquinista M2) const{
		return M1.getId()  == M2.getId();
	}
};

struct hstr {
	int operator() (const Maquinista &maquinista) const {
	
		int value = 0;
		string nome = maquinista.getNome();
		for (unsigned int i = 0; i < nome.size(); i++)
		value += nome[i] * i;
		return value;

	}
};



typedef unordered_set<Maquinista, hstr , eqMaquinista> tabHMaq;
class Maquinistas
{
	tabHMaq maquinistas;
public:
	Maquinistas();
	bool loadMaquinistas();
	void saveMaquinista(Maquinista maq);
	bool adicionaMaquinista(Maquinista trabalhador);
	void editaMaquinista(Maquinista trabalhador1, Maquinista trabalhador2);
	void eliminaMaquinista(Maquinista trabalhador);
	void showMaquinista();
};


#endif /*MAQUINISTAS_H_*/
