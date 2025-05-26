/*
  Biblioteca define funcoes para utilizacao do algoritmo Ray Casting
  Criado por Davi Garcia Lazzarin  e Matheus Telles Batista
  Data: 07/04/25
*/

#ifndef _RAYCASTING_
#define _RAYCASTING_

#include <cstdlib>
#include <vector>
#include <list>
#include <iostream>

#include "poligono.hpp"

//Defines
#define VERTICE_ALINHADO 1
#define VERTICE_AGUDO 2

// ============================= Funcoes usadas no RayCasting =============================

// Recebe um ponto, um poligono(vector de vertices) e um i, que e o numero do vertice analisado
// Ve se a reta passa em cima do vertice V, calcula se conta ou nao com base nos vizinhos de V
// Caso especial, V eh o fim de uma aresta horizontal (quando e origem ignora)
// Sejam as retas TU, UV, VX. V e o vertice analisado no momento, se UV for horizontal considera
// que UV nao existe e que T e o vertice anterior a V, ficando com as retas TV e VX
template <typename T> int ponto_no_vertice(const ponto<T>& p, const poligono<T>& pol, int i){
  int meio = i;
  
  if( (std::abs(p.y - pol.vertices[meio].y) < EPS) && (p.x < pol.vertices[meio].x - EPS) ){ //linha horizontal cruza o vertice do meio
    
    int fim = ((i+1)% pol.vertices.size());
    int ini;
    
    if (meio == 0 )
      ini = pol.vertices.size() - 1;
    else
      ini = meio - 1;
    
    // Caso especial
    // meio e fim de aresta horizontal 
    // define inicio como um ponto diferente
    while( (std::abs(pol.vertices[ini].y - pol.vertices[meio].y) < EPS) ){
      if(ini == 0)
        ini = pol.vertices.size() - 1;
      else
        ini--;
    }  

    // Definidos os 3 pontos que formam as 2 arestas
    #ifdef DEBUG
    std::cout<<"\nPonto no Vertice()\n";
    std::cout<<"Ponto -> "<<p<<"\n";
    std::cout<<"INI  -> "<<pol.vertices[ini]<<"\n";
    std::cout<<"MEIO -> "<<pol.vertices[meio]<<"\n";
    std::cout<<"FIM  -> "<<pol.vertices[fim]<<"\n";
    #endif

    // meio abaixo de ini e fim
    if ((pol.vertices[ini].y > pol.vertices[meio].y + EPS ) && (pol.vertices[fim].y > pol.vertices[meio].y + EPS ))
      return VERTICE_AGUDO;

    // meio acima de ini e fim
    if ((pol.vertices[ini].y < pol.vertices[meio].y - EPS ) && (pol.vertices[fim].y < pol.vertices[meio].y - EPS ))
      return VERTICE_AGUDO;
    
    // meio acima de ini e abaixo fim
    if ((pol.vertices[ini].y < pol.vertices[meio].y - EPS ) && (pol.vertices[fim].y > pol.vertices[meio].y + EPS ))
      return VERTICE_ALINHADO;

    // meio acima de fim e abaixo ini
    if ((pol.vertices[ini].y > pol.vertices[meio].y + EPS ) && (pol.vertices[fim].y < pol.vertices[meio].y - EPS ))
      return VERTICE_ALINHADO;

  }
  
  return 0;
}

// Verifica se o ponto esta entre as pontas da aresta 
template <typename T> bool ponto_na_aresta(const ponto<T>& p, const aresta<T>& sr) {
  
  // Verifica se e colinear 
  T aux = (sr.fim.x - sr.ini.x)*(p.y - sr.ini.y) - (sr.fim.y - sr.ini.y)*(p.x - sr.ini.x);
  
  // Se nao for colinear retorna falso
  if (std::abs(aux) > EPS) return false; 

  // Testa se está entre os extremos, ja que nesse caso nao pode ser paralelo 
  // Verifica se o ponto esta dentro do "quadrado" do qual a aresta eh diagonal principal
  return std::min(sr.ini.x, sr.fim.x) - EPS <= p.x && p.x <= std::max(sr.ini.x, sr.fim.x) + EPS &&
         std::min(sr.ini.y, sr.fim.y) - EPS <= p.y && p.y <= std::max(sr.ini.y, sr.fim.y) + EPS;
}

// Funcao principal do raycasting
// Recebe o poligono e o ponto, retorna se esta dentro do poligono ou nao
template <typename T> bool raycast(const ponto<T>& p, const poligono<T>& pol) {
  
  int n = pol.vertices.size(); //tamanho do poligono
  int cruzamentos = 0;         //contagem de cruzamentos

  for (int i = 0; i < n; i++) {
    aresta<T> sr;
    sr.ini = pol.vertices[i];
    sr.fim = pol.vertices[(i + 1) % n];
    
    // Ponto sobre a aresta
    if (ponto_na_aresta(p, sr)) return true;

    // Ignora arestas horizontais
    if (std::abs(sr.ini.y - sr.fim.y) < EPS) continue;

    // Ponto passa pelo vertice
    switch( ponto_no_vertice(p, pol, i) )
    {
    case VERTICE_ALINHADO: //Conta uma interseccao
      cruzamentos++;
      break;
      
    case VERTICE_AGUDO: // ignora a intersecsao
      break;

    default: // Nao passa sobre um vertice, pode intersectar o meio de uma aresta

      // Garante que o inicio da semireta esta sempre "abaixo" do fim
      if (sr.ini.y > sr.fim.y) std::swap(sr.ini, sr.fim);
      
      // Verifica se a semi reta cruza a aresta
      // ponto esta entre os limites sup e inf da sr no eixo y 
      // ignora caso passe em cima das pontas
      if ( (p.y > sr.ini.y - EPS && p.y < sr.fim.y - EPS) && (!(std::abs(sr.ini.y - p.y) < EPS ) && !(std::abs(sr.fim.y - p.y) < EPS)) ) { 
        
        // Acha o ponto x em que a reta horizontal do ponto cruza a sr
        double x_intersecao = (double)(sr.fim.x - sr.ini.x) * (p.y - sr.ini.y) / (sr.fim.y - sr.ini.y) + sr.ini.x; 

        //Como a reta vai do ponto para a direita, se tiver a esqueda nao conta, estar em cima ja foi tratado
        if (x_intersecao > p.x + EPS)
          cruzamentos++;
        
      }
      break;
    };//switch

  }//for

  // Retorna true se impar, false se par
  return cruzamentos % 2 == 1; 
}

#endif 