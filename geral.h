#ifndef GERAL_H_
#define GERAL_H_
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <fstream>

class Registo;
class Compra;
class Datas;
class Horas;

Datas* getDataActual();
Horas* getHoraActual();

class Datas {
	unsigned int ano;
	unsigned int mes;
	unsigned int dia;
public:

	Datas(unsigned int a, unsigned int m, unsigned int d){
		ano= a; mes = m; dia = d;
	}

	unsigned int getAno(){return ano;}

	unsigned int getMes() {return mes;}

	unsigned int getDia() {return dia;}

	double getHoursFormat(){

		double hours = (ano - 2000) * 365.2425;

		switch(mes){
		case 2:
			hours += 31;
			break;
		case 3:
			hours += 59;
			break;
		case 4:
			hours += 90;
			break;
		case 5:
			hours += 120;
			break;
		case 6:
			hours += 151;
			break;
		case 7:
			hours += 181;
			break;
		case 8:
			hours += 212;
			break;
		case 9:
			hours += 243;
			break;
		case 10:
			hours += 273;
			break;
		case 11:
			hours+= 304;
			break;
		case 12:
			hours += 334;
			break;
		}

		hours += dia;


		return hours * 24;
	}

	friend std::ostream& operator << (std::ostream &os, const Datas &d1){
		os << std::right << std::setw(2) << std::setfill('0') << d1.dia << "-"
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

	unsigned int getHora(){return hora;}

	unsigned int getMin() {return min;}

	double getHoursFormat(){
		double hmin = (double)min/60;
		return (double)hora + hmin;
	}

	friend std::ostream& operator << (std::ostream &os, const Horas &h1){
		os << std::right << std::setfill('0') << std::setw(2) << h1.hora << ":"
				<< std::setfill('0') << std::setw(2) <<h1.min;
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
