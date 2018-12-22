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
	*  Se se esta a adicionar um maquinista atual, não é necessario indicar o boleano se 
	*  este é ou não um membro ativo, porque será um maquinista novo
	*
	* @param primeiro nome do maquinistas
	* @param apelidos do maquinistas serados por espaço
	* @param identificacao do maquinistas
	*/
	Maquinista(string nome, string apelido, int id, bool atual);
	/**
	* Se queremos adicionar um maquinista que já não se encontra ao serviço, o 4 parametro deverá ser
	* false, dado este não ser um maquinista atual
	*
	* @param primeiro nome do maquinistas
	* @param apelidos do maquinistas
	* @param identificacao do maquinistas
	* @param se o maqinista está atualmente ao serviço ou não
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
	*	@return o número de identificação do maquinista
	*/
	unsigned getId() const { return id; } ;

	/**
	*	@return o estado ativo ou não do maquinista
	*/
	bool getAtivo() const { return ativo; };
	
	/*
	* Altera o estado (atual ou não) do maquinista.
	* 
	*/
	void alteraEstado();

	/**
	 * Faz overload ao operador de saida para dar output da informacao do maquinista como parâmetro
	 * na forma de tabela
	 *
	 * @param os Referencia para ofstream onde guardar a informacao
	 * @param M referência para o maquinista
	 * @return o estado, o número de identificação, o primeiro nome e todos os apelidos do maquinista.
	 */
	friend ostream & operator << (ostream &out, const Maquinista & M);

	bool adicionaViagem(Viagem *v);
};

/**
*	redefiniçao do operador de igualdade\n
*  sendo a identificaçao de cada mquinistas única, dois maquinistas com o mesmo número de identificaçao
*   são o mesmo maquinista, se não forem este não deverá de ser aceite para a tabela de dispersão
*/
struct eqMaquinista {
	bool operator() (const Maquinista& M1, const Maquinista M2) const{
		return M1.getId()  == M2.getId();
	}
};

/**
*	Função hash \n
* utiliza o primeiro nome do maquinista, isto é, o valor na tabela é  a somo dos valores ascii de cada caracter.
* Sendo que há nomes mais vulgares e nomes com iguais letras, que provocam bastantes colisões, 
* diminuindo a alta eficiência da tabela de dispersão ,
* a função multiplica o código ASCII pela respectiva posição na string e soma o id do maquinista,
* provocando menos colisões.
* @return o valor que define o lugar na tabela de dispersão
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
* Cria a tabela de dipersão
*/
typedef unordered_set<Maquinista, hstr , eqMaquinista> tabHMaq;

/**
*	CLASS MAQUINISTAS \n
*   Classe associada a tabela de dispersão
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
	*  Elimina todos os maquinistas da tabela de dispersão
	*
	*/
	void clearMaquinistas();
	/**
	*
	* @return um booleano com o estados vazio ou não da tabela de dispersão
	*/
	bool emptyMaquinistas();
	
	/*
	* extrai do ficheiro com os maquinistas os registos dos maquinistas guardados,
	* tanto os maquinista em serviço como os os antigos
	* @return se foi possível adicionar todos os maquinistas
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
	* @param maquinistas a adicionar a tabela de dispersão
	* @return o sucesso ou não da operaçao de inserção
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
	*  Mosta todos os maquinistas que se encontram na tabela de dispersão. \n
	*  Na respetiva ordem, número de identificação, nome
	*/
	void showMaquinistas();
};


#endif /*MAQUINISTAS_H_*/
