#include "locais.h"
#include "math.h"
#include <iostream>
#include <iomanip>

using namespace std;


Paragem::Paragem(string nome, double latitude, double longitude){
	this->nome = nome;
	this->latitude = latitude;
	this->longitude = longitude;
}


string Paragem::getNome() const { return this->nome; }

double Paragem::getLatitude() const {return this->latitude;}

double Paragem::getLongitude() const{ return this->longitude; }

void Paragem::setNome(std::string nome) { this->nome = nome; }

void Paragem::setLatitude(double latitude) { this->latitude = latitude; }

void Paragem::setLongitude(double longitude) { this->longitude = longitude; }

double Paragem::distancia(double latitude, double longitude){

	//Formula de haversine
	double gpr = 3.14159265358979323846264338327950288 / 180;
	double raioTerra = 6371;

	double distLat = (latitude - this->getLatitude()) * gpr;
	double distLong = (longitude - this->getLongitude()) * gpr;

	double p1lat = this->getLatitude() * gpr;
	double p2lat = latitude * gpr;

	double a = sin(distLat/2) * sin(distLat/2) + sin(distLong/2) * sin(distLong/2) *
			cos(p1lat) * cos(p2lat);
	double c = 2 * atan2(sqrt(a), sqrt(1-a));

	return c * raioTerra;
}




void Paragens::addParagem(Paragem &p1){paragens.push_back(p1);}
Paragem Paragens::getParagem(int id){return paragens.at(id);}

void Paragens::printParagens() const{
	for (unsigned int i = 0; i < paragens.size(); i++)
		cout << i << " - " << paragens.at(i).getNome() << endl;
}

bool Paragens::emptyParagens() const{
	if (paragens.empty())
		return true;
	return false;
}

Paragem Paragens::findParagem (std::string nome) const{
	for (unsigned int i = 0; i < paragens.size(); i++){
		if (paragens.at(i).getNome() == nome)
			return paragens.at(i);
	}

	Paragem temp("Nenhuma", 0 , 0);

	return temp;
}

Oficina::Oficina(string nome, double latitude, double longitude){
	this->nome = nome;
	this->latitude = latitude;
	this->longitude = longitude;
	this->disponibilidade = 0;
}

string Oficina::getNome() const { return nome; }

double Oficina::getLatitude() const { return latitude; }

double Oficina::getLongitude() const { return longitude; }

double Oficina::getDisponibilidade() const { return disponibilidade; }

void  Oficina::setNome(std::string nome) { this->nome = nome; }

void  Oficina::setLatitude(double latitude) { this->latitude = latitude; }

void  Oficina::setLongitude(double longitude) { this->longitude = longitude; }

void  Oficina::setDisponibilidade(int val) { disponibilidade = val; }

bool Oficina::operator < (Oficina &o1) {
	if (this->getDisponibilidade() < o1.getDisponibilidade())
		return true;

	return false;
}

priority_queue <Oficina *> Oficinas::getOficinas() const {return oficinas;}

void Oficinas::addOficina (Oficina *o1){
	oficinas.push(o1);
}

void Oficinas::printOficinas() const{
	priority_queue <Oficina *> temp = oficinas;
	unsigned int size = temp.size();
	cout << "id " << " Disp.(dias)" << "   Nome " << endl << endl;
	for (unsigned int i = 0; i < size; i++){
		cout << i << "   " << left << setw(11) << temp.top()->getDisponibilidade() << "   " << temp.top()->getNome() << endl;
		temp.pop();
	}
}

bool Oficinas::emptyOficinas() const{
	if (oficinas.empty())
		return true;
	return false;
}
