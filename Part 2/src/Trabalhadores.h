#ifndef TRABALHADORES_H_
#define TRABALHADORES_H_

#include <unordered_set>
#include <vector>
#include <string>

using namespace std;

struct eqstr {
	bool operator() (const string &s1, const string &s2) const{
		return s1 == s2;
	}
};

struct hstr {
	int operator() (const string &nome) const {
	
		int value = 0;
		for (unsigned int i = 0; i < nome.size(); i++)
		value += nome[i] * i;
		return value;

	}
};

typedef unordered_set<string, hstr , eqstr> tabHInt;
unordered_set<string, hstr, eqstr>::const_iterator it;

class Trabalhador
{
	string nome;
	unsigned id;
public:
	Trabalhador(string nome, int id);
	string getNome() { return nome; };
	unsigned getId() { return id; }
};

class Trabalhadores

{
	tabHInt trabalhadores;
public:
	Trabalhadores() ;
	bool adicionaTrabalhador(Trabalhador trabalhador);
	void editaTrabalhador(Trabalhador trabalhador1, Trabalhador trabalhador2);
	void eliminaTrabalhador(Trabalhador trabalhador);

};


#endif /*TRABALHADORES_H_*/
