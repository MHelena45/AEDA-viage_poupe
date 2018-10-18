#include "comboios.h"

Comboio::Comboio(int horas, int minutos,int NumPasseiros) : NumMax (NumPasseiros) {
	hora HORAS;
	horario.hora =horas;
	horario.min = minutos;
	lotacao = 0;
	ocupado = false;
}
int Comboio::getlotacao(){
	return lotacao;
}
bool Comboio::getOcupado(){
	if(NumMax == lotacao)
		return true;
	else return false;
}
bool Comboio::getMeioOcupado(){
	if(lotacao > (NumMax /2))
		return true;
	else return false;
}
AlfaPendular::AlfaPendular(int horas, int minutos,int NumPasseiros) : Comboio(lotacao, horas, minutos){}
string AlfaPendular::getInformacao(){
	string Tipo = "AP";
	return Tipo;
}
Intercidades::Intercidades(int HORAS, int MINUTOS,int NumeroPasseiros) : Comboio(HORAS,MINUTOS, NumeroPasseiros){}
string Intercidades::getInformacao(){
	string Tipo = "IC";
	return Tipo;
}


