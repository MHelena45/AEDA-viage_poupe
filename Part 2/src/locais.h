#pragma once

#include <string>
#include <vector>
#include <queue>

/**
 * CLASS Paragem
 * Esta Classe cria paragens de comboio
 *
 */

class Paragem {
	std::string nome;
	double latitude;
	double longitude;
	static int numeroclientes;
public:
	/**
	 * Construtor de Paragem
	 *
	 */
	Paragem(){};
	/**
	 * Construtor de Paragem
	 * @param nome Nome da paragem
	 * @param latitude Latitude da Paragem
	 * @param longitude Longitude da Paragem
	 */
	Paragem(std::string nome, double latitude, double longitude);
	/**
	 * Construtor de Paragem
	 * @param nome Nome da paragem
	 * @param latitude Latitude da Paragem
	 * @param longitude Longitude da Paragem
	 * @param numclientes Numero de clientes da Paragem
	 */
	Paragem(std::string nome, double latitude, double longitude, int numclientes);
	
	/**
	 * Destrutor de Paragem
	 */
	~Paragem(){};
	/**
	 * @return Nome da paragem
	 */
	std::string getNome() const;
	/**
	 * @return Latitude da paragem
	 */
	double getLatitude() const;
	/**
	 * @return Longitude da paragem
	 */
	double getLongitude() const;
	/**
	 * @return Número de clientes que já saiu nessa paragem
	 */
	int getNumClientes() const;
	/**
	 * @brief Aumenta o número de clientes por 1
	 */
	void aumentaNumClientes();
	/**
	 * @brief Diminui o número de clientes por 1
	 */
	void diminuiNumClientes();
	/**
	 * @brief Altera o nome da paragem
	 *
	 * @param nome Nome da paragem
	 */
	void setNome(std::string nome);
	/**
	 * @brief Altera a latitude da paragem
	 *
	 * @param nome Nome da paragem
	 */
	void setLatitude(double latitude);
	/**
	 * @brief Altera a longitude da paragem
	 *
	 * @param nome Nome da paragem
	 */
	void setLongitude(double longitude);
	/**
	 * @brief Devolve a distancia da paragem a outro local
	 *
	 * @param latitude Latitude do local
	 * * @param longitude Longitude do local
	 */
	double distancia(double latitude, double longitude);
};


/**
 * CLASS Paragens
 * Esta Classe guarda todas as paragens de comboio
 *
 */
class Paragens {
	std::vector<Paragem> paragens;
public:
	Paragens(){};
	/**
	 * @brief Adiciona uma paragem
	 *
	 * @param p1 Paragem
	 */
	void addParagem(Paragem &p1);
	/**
	 * @brief Devolve uma paragem
	 *
	 * @param id id da paragem
	 * @return Paragem guardada
	 */
	Paragem* getParagem(int id);
	/**
	 * @brief Imprime no ecra todas as paragens
	 */
	void printParagens() const;
	/**
	 * @brief Verifica vector paragens
	 *
	 * @return Verdade se o vector paragens estiver vazio, falso senao
	 */
	bool emptyParagens() const;
	/**
	 * @brief Verifica numero de paragens
	 *
	 * @return Numero de paragens
	 */
	int sizeParagens() const;
	/**
	 * @brief Imprime no ecra todas as paragens
	 *
	 * @param id id da paragem
	 */
	void deleteParagem(int id);
	/**
	 * @brief Encontra uma paragem
	 *
	 * @param nome Nome da paragem
	 * @return Devolve a paragem se encontrada, Paragem com nome "Nenhuma" senao encontrada
	 */
	Paragem findParagem (std::string nome) const;
};
/**
 * CLASS Oficina
 * Esta Classe cria oficinas de comboios
 *
 */
class Oficina {
	std::string nome;
	double latitude;
	double longitude;
	unsigned int disponibilidade;
public:
	/**
	 * Construtor de Oficina
	 *
	 */
	Oficina(){};
	/**
	 * Construtor de Paragem
	 * @param nome Nome da paragem
	 * @param latitude Latitude da Paragem
	 * @param longitude Longitude da Paragem
	 */
	Oficina(std::string nome, double latitude, double longitude);
	/**
	 * Destrutor de Paragem
	 *
	 */
	~Oficina(){};
	/**
	 * @return nome da oficina
	 */
	std::string getNome() const;
	/**
	 * @return Latitude da oficina
	 */
	double getLatitude() const;
	/**
	 * @return Longitude da oficina
	 */
	double getLongitude() const;
	/**
	 * @return disponibilidade da oficina
	 */
	double getDisponibilidade() const;
	/**
	 * @brief Altera o nome da oficina
	 *
	 * @param nome Nome da oficina
	 */
	void setNome(std::string nome);
	/**
	 * @brief Altera a latitude da oficina
	 *
	 * @param nome Nome da oficina
	 */
	void setLatitude(double latitude);
	/**
	 * @brief Altera a longitude da oficina
	 *
	 * @param nome Nome da oficina
	 */
	void setLongitude(double longitude);
	/**
	 * @brief Altera o disponibilidade da oficina
	 *
	 * @param val valor a ser somar a disponibilidade
	 */
	void setDisponibilidade(int val);
	/**
	 * @return true if object is smaller than 01
	 */
	bool operator < (Oficina &o1);

};

/**
 * CLASS Oficinas
 * Esta Classe guarda e gere oficinas de comboios
 *
 */
class Oficinas {
	std::priority_queue <Oficina *> oficinas;
public:
	/**
	 * Construtor de Oficinas
	 *
	 */
	Oficinas(){};
	/**
	 * @return Fila de prioridade com todas as oficinas
	 */
	std::priority_queue <Oficina *> getOficinas() const;
	/**
	 * @brief Adiciona oficina a fila de prioridade
	 * @param o1 Oficina
	 */
	void addOficina (Oficina *o1);
	/**
	 * @brief Imprime no ecra todas as paragens
	 */
	void printOficinas() const;
	/**
	 * @return Verdade quando nao existem oficinas, falso caso contrario
	 */
	bool emptyOficinas() const;
	/**
	 * @return Numero de oficinas
	 */
	int sizeOficinas() const;
	/**
	 * @brief Apaga uma oficina
	 */
	void deleteOficina(int id);
};


