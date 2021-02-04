#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <queue>
#include <sstream>
#include <vector>
#include <time.h>
#include <string>
#include "Kart.h"

using namespace std;

//To help build better array
string itos(int i){
    stringstream s;
    s << i;
    return s.str();
}

void CGrupo::criaGrupo()
{
    float cilindradas[4]  = {134,250,450,600};
    bool avariados[3]  = {true,false,false};

    srand (1);   //Criar Pistas e Karts de Teste
    for(int i=1;i<=50;i++){
        vector<CKart> frota;
        for(int j=1;j<=50;j++){
            frota.push_back(CKart(avariados[rand()% 3],
                                  ("KART - "+itos(i))+itos(j),(i-1)*50+j,cilindradas[(rand() % 4)]));
        }
        adicionaPista(CPista("Pista - "+itos(i),frota));
    }
}


vector <CKart> CPista::getKartsAvariados()
{
    vector<CKart> aux;
    for (vector<CKart>::iterator it = frotaKartsPista.begin() ; it != frotaKartsPista.end(); ++it) {
        if ((it)->getAvariado()) aux.push_back((*it));
    }
    return aux;
}
 
//Exercicio 1 a)     
vector<CKart> CGrupo::ordenaKarts() {
	vector<CKart> vord;
	for (CPista &pista : pistasG) {
	    for (const CKart &kart : pista.getFrotaActual()) {
	        vord.push_back(kart);
	    }
	}
	sort(vord.begin(), vord.end(), numeroOrdena);
	return vord;
    
}

//Exercicio 1 b)  
int CGrupo::numAvariados(int cilind)
{
    int counter = 0;
    for (CPista &pista : pistasG) {
        for (CKart &kart : pista.getKartsAvariados()) {
            if (kart.getCilindrada() == cilind)
                counter++;
        }
    }
    return counter;
}

//Exercicio 1 c)   
bool CPista::prepararCorrida(int numeroKarts, int cilind) {
    int cars_available = count_if(frotaKartsPista.begin(), frotaKartsPista.end(), [cilind](CKart &k){
        return k.getCilindrada() == cilind && !k.getAvariado();
    });
    int n = cars_available < numeroKarts ? cars_available : numeroKarts;
    auto it = frotaKartsPista.begin();
    while(n){
        if((*it).getCilindrada() == cilind && (*it).getAvariado()){
            n--;
            kartsLinhaPartida.push((*it));
        }
        it++;
    }
    return cars_available < numeroKarts;
}

//Exercicio 1 d) 
int CPista::inicioCorrida() {
    kartsEmProva.clear();
    while (!kartsLinhaPartida.empty()) {
        kartsEmProva.push_back(kartsLinhaPartida.front());
        kartsLinhaPartida.pop();
    }
    reverse(kartsEmProva.begin(), kartsEmProva.end());
    return kartsEmProva.size();
}

bool numeroOrdena(CKart &kart1, CKart &kart2) {return kart1.getNumero() < kart2.getNumero();}