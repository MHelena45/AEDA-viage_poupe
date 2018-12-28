#ifndef GERAL_H_
#define GERAL_H_

#include "datashoras.h"
#include "cartao.h"
#include "viagens.h"
#include "comboios.h"
#include "bilheteira.h"
#include "Maquinistas.h"

Datas* getDataActual();
Horas* getHoraActual();

void menuInformacao(BaseClientes *r, Frota *f, Bilheteira *b, Maquinistas *M);
void menuComCartao(BaseClientes *r, Bilheteira *b);
void menuSemCartao(BaseClientes *r, Bilheteira *b);
void menuAdministracao(BaseClientes *r, Frota *f, Bilheteira *b, Maquinistas *M);
void menuMaquinista(Frota *f, Bilheteira *b, Maquinistas *M);

int menuInput(int nOptions);
int userIntInput();
double userDoubleInput();
Maquinista criaMaquinista();
Viagem * adicionaViagem(Bilheteira *b, Frota *f);
bool LetrasInvalidas(string nome);
string nomeValido();
string apelidoValido();
bool adicionaViagensAMaquinista(Frota *f, Bilheteira *b, Maquinista *M1);

#endif
