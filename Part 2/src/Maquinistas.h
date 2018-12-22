#ifndef MAQUINISTAS_H_
#define MAQUINISTAS_H_

#include <unordered_set>
#include "datashoras.h"
#include "viagens.h"

using namespace std;
/**
* CLASS MAQUINISTA \n
* cria um novo maquinita
*
*/

class Maquinista
{
	const string nome, apelido;
	bool ativo;
	unsigned id;
	vector<Viagem *> viagens;
public:
	/**
	* Construtor:
	*  Se se esta a adicionar um maquinista atual, n�o � necessario indicar o boleano se 
	*  este � ou n�o um membro ativo, porque ser� um maquinista novo
	*
	* @param primeiro nome do maquinistas
	* @param apelidos do maquinistas serados por espa�o
	* @param identificacao do maquinistas
	*/
	Maquinista(string nome, string apelido, int id, bool atual);
	/**
	* Se queremos adicionar um maquinista que j� n�o se encontra ao servi�o, o 4 parametro dever� ser
	* false, dado este n�o ser um maquinista atual
	*
	* @param primeiro nome do maquinistas
	* @param apelidos do maquinistas
	* @param identificacao do maquinistas
	* @param se o maqinista est� atualmente ao servi�o ou n�o
	*
	*/
	Maquinista(string nome, string apelido, int id) ;

	/**
	*	@return o primeiro nome do maquinista
	*/
	string getNome() const { return nome; } ;

	/**
	*	@return uma string com todos os apelidos do maquinista
	*/
	string getApelido() const { return apelido; } ;

	/**
	*	@return o n�mero de identifica��o do maquinista
	*/
	unsigned getId() const { return id; } ;

	/**
	*	@return o estado ativo ou n�o do maquinista
	*/
	bool getAtivo() const { return ativo; };
	
	/*
	* Altera o estado (atual ou n�o) do maquinista.
	* 
	*/
	void alteraEstado();

	/**
	 * Faz overload ao operador de saida para dar output da informacao do maquinista como par�metro
	 * na forma de tabela
	 *
	 * @param os Referencia para ofstream onde guardar a informacao
	 * @param M refer�ncia para o maquinista
	 * @return o estado, o n�mero de identifica��o, o primeiro nome e todos os apelidos do maquinista.
	 */
	friend ostream & operator << (ostream &out, const Maquinista & M);

	bool adicionaViagem(Viagem *v);
};

/**
*	redefini�ao do operador de igualdade\n
*  sendo a identifica�ao de cada mquinistas �nica, dois maquinistas com o mesmo n�mero de identifica�ao
*   s�o o mesmo maquinista, se n�o forem este n�o dever� de ser aceite para a tabela de dispers�o
*/
struct eqMaquinista {
	bool operator() (const Maquinista& M1, const Maquinista M2) const{
		return M1.getId()  == M2.getId();
	}
};

/**
*	Fun��o hash \n
* utiliza o primeiro nome do maquinista, isto �, o valor na tabela �  a somo dos valores ascii de cada caracter.
* Sendo que h� nomes mais vulgares e nomes com iguais letras, que provocam bastantes colis�es, 
* diminuindo a alta efici�ncia da tabela de dispers�o ,
* a fun��o multiplica o c�digo ASCII pela respectiva posi��o na string e soma o id do maquinista,
* provocando menos colis�es.
* @return o valor que define o lugar na tabela de dispers�o
*/
struct hstr {
	int operator() (const Maquinista &maquinista) const {
	
		int value = maquinista.getId();
		string nome = maquinista.getNome();
		for (unsigned int i = 0; i < nome.size(); i++)
		value += nome[i] * i;
		return value;

	}
};

/**
* Cria a tabela de dipers�o
*/
typedef unordered_set<Maquinista, hstr , eqMaquinista> tabHMaq;

/**
*	CLASS MAQUINISTAS \n
*   Classe associada a tabela de dispers�o
*
*/
class Maquinistas
{
	tabHMaq maquinistas;
public:
	/**
	* Construtor:
	* Inicia a tabela de dispersao vazia
	*
	*/
	Maquinistas() {};
	/**
	*  Elimina todos os maquinistas da tabela de dispers�o
	*
	*/
	void clearMaquinistas();
	/**
	*
	* @return um booleano com o estados vazio ou n�o da tabela de dispers�o
	*/
	bool emptyMaquinistas();
	
	/*
	* extrai do ficheiro com os maquinistas os registos dos maquinistas guardados,
	* tanto os maquinista em servi�o como os os antigos
	* @return se foi poss�vel adicionar todos os maquinistas
	*/
	bool loadMaquinistas();
	/** 
	* Guarda um novo maquinistas no ficheiro com os maquinistas
	* @param maquinistas a adicionar ao ficheiro
	*/
	void saveMaquinista(Maquinista & maq);

	/**
	*  Adiciona um maquinista a tabela de dispersao
	*  designada de maquinistas
	* @param maquinistas a adicionar a tabela de dispers�o
	* @return o sucesso ou n�o da opera�ao de inser��o
	*/
	bool adicionaMaquinista(Maquinista trabalhador);
	/**
	*  Se nos enganarmos a colocar um maquinista na 
	*  tabela podemos editar o erro
	*  @param maquinista enrado
	*  @param maquinista com o nome correto 
	*/
	void editaMaquinista(Maquinista trabalhador1, Maquinista trabalhador2);

	/**
	 *  Se quisermos eliminar um maquinas, porque por exemplo faleceu,
	 *  nao podendo ser reconstratado, podemos elimna-lo da nossa tabela
	 *  @param maquinista que quermos eliminar da tabela
	*
	*/
	void eliminaMaquinista(Maquinista trabalhador);

	/**
	*  Mosta todos os maquinistas que se encontram na tabela de dispers�o. \n
	*  Na respetiva ordem, n�mero de identifica��o, nome
	*/
	void showMaquinistas();
};


#endif /*MAQUINISTAS_H_*/
