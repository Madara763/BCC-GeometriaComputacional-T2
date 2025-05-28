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
//Parametros:
//Ini e fim sao indices dos pontos iniciais e finais da SA em vv
//Face eh um ponteiro para a face que tem essa SA nova
//sa_anterior eh a Semi-Aresta anterio a essa nova na face
//Mapa_sa eh um map que usa (ini, fim) como chaves para identificar as arestas com hashing
//mapa_sa[ini,fim] eh pra ser diferente de mapa_sa[fim,ini]
//nsp eh um inteiro que quando == 1 indica que estou criando uma SA pela segunda vez, ou seja, existe uma face usando a mesma regiao do espaco que outra, faz parte do retorno
//E quando == 2 indica superposicao
//Retorno: ponteiro para a sa criada e preenchida ou null em caso de erro
template <typename T>
semi_aresta<T>* cria_semiaresta(int ini, int fim, face<t_ponto>* face, semi_aresta<t_ponto>* sa_anterior,
                                std::unordered_map<std::pair<int, int>, semi_aresta<t_ponto>*, pair_hash>& mapa_sa,
                                const std::vector<ponto<t_ponto>>& vv, int* nsp, std::vector<int>& vetor_vertices_sa){
  
  //Par dos vertices
  ini--; fim--; //ajusta de ordem de vertice para indice no vetor
  std::pair<int, int> par_ah{ini, fim}; //Anti-horario, as faces sao criadas assim 
  std::pair<int, int> par_ho{fim, ini}; //Horario, verifica o twin nesse sentido
  
  // Verifica se ja esxite uma SA identica a essa nova
  // Se ja existe, duas faces estao usando a mesma semi-aresta
  // A verificacao nos poligonos deve evitar isso
  if (mapa_sa.find(par_ah) != mapa_sa.end()){  
    //erro no bagulho, n devia estar aqui
    //Tentendo usar a mesma SA em outra face
    //Ativa a flag de que caiu em uma NSP
    *nsp = 1; 
    return NULL;
  }

  semi_aresta<t_ponto>* sa = new semi_aresta<t_ponto> ; //Semi-Aresta
  if(!sa){
    perror("Erro de alocacao em cria_semiaresta()\n");
    return NULL;
  }

  sa->index = ini;
  sa->ini = vv[ini];          //Indice em vv do ponto inicial dessa sa
  sa->ante = sa_anterior;     //Semi-Aresta anterior a essa nova
  sa->face_incidente = face;  //Ponteiro para a face a qual essa SA pertence
  mapa_sa[par_ah] = sa;       //Adiciona no mapa de Semi_Aresta p/ quando criar o twin dessa poder achar essa

  //Se existe um anterior, adiciona esse como proximo do anterior 
  //Se for o primeiro sa_anterior eh nullptr
  if(sa_anterior) 
    sa_anterior->prox = sa;

  //Existe um twin  
  //Verifica se existe uma no lado oposto a essa, atualiza os dois lados
  if (mapa_sa.find(par_ho) != mapa_sa.end()) {
    sa->par = mapa_sa[par_ho];
    mapa_sa[par_ho]->par = sa;

    //Caiu aqui pq a aresta vai e vem na mesma face
    //retorna superposta
    if(mapa_sa[par_ho]->face_incidente == sa->face_incidente){
      *nsp = 2;    //retorna superposta
      return NULL; //nao cria a aresta
    }

  }
  
  #ifdef DEBUG
  std::cout<<"Criando uma SA em cria_semiaresta(): "<<*sa<<"\n";
  #endif

  //Se nao tem nenhuma SA registrada como inicio nesse vertice, adiciona a primeira
  if(!vetor_vertices_sa[ini]){ vetor_vertices_sa[ini] = sa->id; } //ok
  
  return sa; //Retorna a SA nova
}

template <typename T> bool todas_tem_twin(const std::list<face<T>*>& lista_faces) {
  for (const face<T>* f : lista_faces) {
    if (!f || !f->semi_aresta_inicial) continue;

    const semi_aresta<T>* sa = f->semi_aresta_inicial;
    const semi_aresta<T>* atual = sa;

    do {
      if (!atual->par) { return false; }
      atual = atual->prox;
    } while (atual != sa); // ciclo circular
  }

  return true; // todas têm twin
}

template <typename T> void imprime_saida_trabalho(int nv, int nf, const std::vector<ponto<t_ponto>>& vv, std::vector<int>& vetor_vertices_sa, const std::list<face<T>*>& lista_faces){
  u_int64_t quant_arestas{0};
  //imprime o ind da primeira SA das lista de faces
  for (const face<T>* f : lista_faces) {
    if (!f || !f->semi_aresta_inicial) continue;
    quant_arestas += f->quant_lados;
  }
  quant_arestas = quant_arestas/2;

  std::cout<<nv<<" "<<quant_arestas<<" "<<nf<<"\n";
  
  //Imprime o vetor de vertices e o ind da SA que inicia nele
  for (size_t i = 0;  i != vv.size(); i++) {
    std::cout<<vv[i]<<" "<<vetor_vertices_sa[i]<<"\n";
  }

  //imprime o ind da primeira SA das lista de faces
  for (const face<T>* f : lista_faces) {
    if (!f || !f->semi_aresta_inicial) continue;
    std::cout<<f->semi_aresta_inicial->id<<"\n"; 
  }

  //imprime as SA das lista de faces
  for (const face<T>* f : lista_faces) {
    if (!f || !f->semi_aresta_inicial) continue;

    const semi_aresta<T>* sa = f->semi_aresta_inicial;
    const semi_aresta<T>* atual = sa;

    do {
      std::cout<<*atual<<"\n";
      atual = atual->prox;
    } while (atual != sa); // ciclo circular
  }
}

#endif