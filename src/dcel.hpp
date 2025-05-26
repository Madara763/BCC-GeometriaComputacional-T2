/*
  Biblioteca manipula estrutura de dados para construcao de um Doubly Connected Edge List
  Estruturas declaradas em poligono.hpp
  Criado por Davi Garcia Lazzarin e Matheus Telles Batista  
  Data: 26/05/25
*/

#ifndef __DCEL__
#define __DCEL__

#include <unordered_map>

#include "poligono.hpp"

//Cria um semi aresta e preenche seus valores usando as informacoes dois maps
template <typename T> semi_aresta<T>* cria_semiaresta(int ini, int fim, face<T> face, std::unordered_map<pair<int, int>, semi_aresta<t_ponto>*, pair_hash>& mapa_sa){
  
  if (ini<fim)
    pair<int, int> crescente{ini, fim};
  else
    pair<int, int> decrescente{ini, fim};
  
  
  //Verifica se ja existe uma semiaresta que use o par de vertices
  //Se ja existe, duas faces estao usando a mesma aresta
  //A verificacao nos poligonos deve evitar isso
  if (mapa.find(par_vertices) != mapa.end()){ 
    //erro no bagulho, n devia estar aqui
  }
  else {
    if (mapa.find(par_horario) != mapa.end()){

    }
  }


                                                      

}

#endif