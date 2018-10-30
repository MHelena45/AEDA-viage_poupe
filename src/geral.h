#ifndef GERAL_H_
#define GERAL_H_
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <iomanip>

class Registo;
class Compra;

class Datas {
	unsigned int ano;
	unsigned int mes;
	unsigned int dia;
public:

	Datas(unsigned int a, unsigned int m, unsigned int d){
		ano= a; mes = m; dia = d;
	}

	friend std::ostream& operator << (std::ostream &os, const Datas &d1){
		os << std::setw(2) << std::setfill('0') << d1.dia << "-"
				<< std::setw(2) << std::setfill('0') << d1.mes << "-" << d1.ano;
		return os;
	}

	bool operator > (const Datas &d1){

		if (this->ano > d1.ano)
			return true;
		if (this->ano == d1.ano){
			if (this->mes > d1.mes)
				return true;
			if (this->mes == d1.mes){
				if (this->dia > d1.dia)
					return true;
			}
		}
	return false;
	}


	bool operator == (const Datas &d1){
		if ( this->ano == d1.ano && this->mes == d1.mes && this->dia == d1.dia)
			return true;

	return false;
	}

	bool operator < (const Datas &d1){

		if (this->ano < d1.ano)
			return true;
		if (this->ano == d1.ano){
			if (this->mes < d1.mes)
				return true;
			if (this->mes == d1.mes){
				if (this->dia < d1.dia)
					return true;
			}
		}
	return false;
	}
};


class Horas {
	unsigned int hora;
	unsigned int min;
public:
	Horas(unsigned int h, unsigned int m){
		hora = h; min = m;
	}

	friend std::ostream& operator << (std::ostream &os, const Horas &h1){
		os << h1.hora << ":" << h1.min;
		return os;
	}

	bool operator > (const Horas &h1){
		if (this->hora > h1.hora)
			return true;
		if (this->hora == h1.hora){
			if (this->min > h1.min)
				return true;
		}
	return false;
	}

	bool operator == (const Horas &h1){
		if ( this->hora == h1.hora && this->min == h1.min )
			return true;

	return false;
	}

	bool operator < (const Horas &h1){
		if (this->hora < h1.hora)
			return true;
		if (this->hora == h1.hora){
			if (this->min < h1.min)
				return true;
		}
	return false;
	}

};



#endif
