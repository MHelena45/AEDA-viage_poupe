#ifndef _VIAGENS_H
#define _VIAGENS_H

#include "comboios.h"
#include "cartao.h"
#include "datashoras.h"

/*
 * CLASS Viagem
 * Esta Classe cria uma viagem e controla as vagas de essa viagem
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
	/**
	 * Construtor de viagem
	 * @param ori -> origem
	 * @param dest -> destino
	 * @param dist -> distancia
	 * @param c -> apontador para comboio que fara a viagem
	 * @param dp -> apontador para data da viagem
	 * @param hp -> apontador para horas da viagem
	 */
	Viagem(std::string ori, std::string dest, double dist, Comboio *c, Datas *dp, Horas *hp);
	/**
	 * Construtor de viagem
	 * @param ori -> origem
	 * @param dest -> destino
	 * @param dp -> apontador para data da viagem
	 * @param hp -> apontador para horas da viagem
	 * @param precoBase -> preco base da viagem
	 */
	Viagem(std::string ori, std::string dest, Datas *dp, Horas *hp,  double precoBase);
	/**
	 * Construtor de viagem
	 * @param ori -> origem
	 * @param dest -> destino
	 * @param dist -> distancia
	 * @param c -> apontador para comboio que fara a viagem
	 * @param dp -> apontador para data da viagem
	 * @param hp -> apontador para horas da viagem
	 * @param vagas -> numero de lugares disponiveis para essa viagem
	 * @param comprasAnon -> numero de lugares comprados anonimamente (por clientes sem cartao)
	 */
	Viagem(std::string ori, std::string dest, double dist, Comboio *c, Datas *dp, Horas *hp, int vagas, int comprasAnon);
	/**
	 * Destrutor \n
	 * Elimina todos os dados de viagem
	 */
	~Viagem();

	/**
	 * @return apontador para a data (ano-mes-dia) de partida da viagem
	 */
	Datas* getDataPartida() const;
	/**
	 * @return apontador para a hora (horas:minutos) de partida da viagem
	 */
	Horas* getHorasPartida() const;
	/**
	 * @return preco base (sem desconto) da viagem
	 */
	double getPrecoBase () const;
	/**
	 * @return origem da viagem
	 */
	std::string getOrigem() const;
	/**
	 * @return destino da viagem
	 */
	std::string getDestino() const;
	/**
	 * @return distancia da viagem
	 */
	double getDistancia() const;
	/**
	 * @return apontador para o comboio que faz a viagem
	 */
	Comboio* getComboio() const;
	/**
	 * @return numero de vagas da viagem
	 */
	unsigned int getVagas() const;
	/**
	 * @return numero de compras anonimas (feitas por clientes sem cartao)
	 */
	unsigned int getComprasAnonimas() const;
	/**
	 * @return informacao sobre a viagem
	 */
	std::string getInfo() const;

	/**
	 * @param reg -> indica se o cliente tem cartao ou nao
	 * @return 1 se ja nao da para reservar mais bilhetes
	 */
	int reservaBilhete(bool reg);
	/**
	 * @param reg -> indica se o cliente tem cartao ou nao
	 * @return 1 se ja nao da para devolver mais bilhetes
	 */
	int devolveBilhete(bool reg);
	/**
	 * @return preco final (preco base ou 30% desse valor se faltarem menos de 48 h e a lotacao estiver a menos de metade)
	 */
	double getPrecoFinal();
	/**
	 * @param c -> apontador para o comboio
	 * @return preco final em relacao a subscricao feita
	 */
	double getPrecoFinal(Cartao *c);
	/**
	 * Redefinicao do operador comparacao
	 * @param v2 -> referencia para a viagem com a qual se vai comparar
	 * @return true se as duas viagens sao iguais
	 */
	bool operator == (const Viagem &v2);
	/**
	 * @return true se ainda se podem efetuar compras nesta viagem, false se a lotacao maxima ja foi atingida
	 */
	bool compraRegisto() const;

};


#endif
