#ifndef _VIAGENS_H
#define _VIAGENS_H

#include "geral.h"
#include "comboios.h"
#include "cartao.h"

/*
 * CLASS Viagem
 * Esta Class cria uma viagem e controla as vagas de essa viagem
 *
 */

class Viagem{
	std::string origem, destino;
	double distancia;
	Comboio *c1;
	Datas *dPartida;
	Horas *hPartida;
	double precoBase;
	unsigned int vagas;
	unsigned int comprasAnonimas;
public:

	Viagem(std::string ori, std::string dest, double dist, Comboio *c, Datas *dp, Horas *hp);

	Viagem(std::string ori, std::string dest, Datas *dp, Horas *hp,  double precoBase);

	Viagem(std::string ori, std::string dest, double dist, Comboio *c, Datas *dp, Horas *hp, int vagas, int comprasAnon);

	~Viagem();

	/* retorna o apontador para a data de partida */
	Datas* getDataPartida() const;
	
	/* retorna o apontador para a hora de partida */
	Horas* getHorasPartida() const;
	
	/* retorna o preco base */
	double getPrecoBase () const;
	
	/* retorna a origem da viagem */
	std::string getOrigem() const;
	
	/* retorna o destino da viagem */
	std::string getDestino() const;
	
	/* retorna a distancia da viagem */
	double getDistancia() const;
	
	/* retorna um apontador para comboios */
	Comboio* getComboio() const;
	
	/* retorna o numero de vagas */
	unsigned int getVagas() const;
	
	/* retorna o numero de compras feitas sem cartao associado */
	unsigned int getComprasAnonimas() const;
	
	/* retorna a informacao respetiva a viagem */
	std::string getInfo() const;

	
	int reservaBilhete(bool reg);

	int devolveBilhete(bool reg);
	
	/* ou devolve o preco final que pode ser o preco base ou apenas 30 por centro desse valor
	se faltarem menos de 48 h e a lotacao estiver a menos de metade */
	double getPrecoFinal();
	
	/* devolve o preco final em relacao a subscricao efutuada */
	double getPrecoFinal(Cartao *c);
	
	/* redefinicao do operador comparacao */
	bool operator == (const Viagem &v2);
	
	/* verifica se ainda se podem efetuar compras desta viegem ou se a lotacao maxima ja foi 
	atingida */
	bool compraRegisto() const;

};


#endif
