#include <iostream>
#include <sstream>

#include "poligono.hpp"
#include "raycast.hpp"
#include "dcel.hpp"

using namespace std;

int main(){

  //Leitura dos dados
  int nVertices, nFaces; //Quantidade de vertices e faces respectivamente
  
  cin>>nVertices>>nFaces;
    
  //Ambos vetores estao vinculados por seus indices
  vector<ponto<t_ponto>> vetor_vertices;
  vector<semi_aresta<t_ponto>*> vetor_vertices_sa(nVertices, NULL);

  //Le os vertices 
  ponto<t_ponto> p;
  for(int i=0; i<nVertices; i++){
    cin>>p.x>>p.y;
    vetor_vertices.push_back(p);
  }//for i

  //descarta o fim da ultima linha, vamos ver linha inteiras daqui pra frente
  cin.ignore(); 

  //Criamos poligonos e faces
  list<poligono<t_ponto>> lista_poligonos;
  list<face<t_ponto>*> lista_faces;

  semi_aresta<t_ponto> *sa_anterior, *sa_inicial, *sa_aux;
  
  //Mapa para vincular indices dos vertices em um ordem a semiaresta 
  //(chave, valor, funcao_hash)
  unordered_map<pair<int, int>, semi_aresta<t_ponto>*, pair_hash> mapa_sa;

  int v, v_ante, v_inicial;
  bool eh_primeira_sa, nsp;
  string linha;
  for(int i=0; i<nFaces; i++){ // Le as faces

    poligono<t_ponto> p;                   // Cria o poligono
    face<t_ponto> *f = new face<t_ponto>;  // Cria a face
    if(!f){perror("Erro aloc main()\n"); return 1;}
    
    eh_primeira_sa = true;

    getline(cin, linha);       // Le a linha inteira
    istringstream ss(linha);   // Cria um stream da linha

    //le cada indice
    //le o primeiro vertice e salva
    ss >> v_ante;
    v_inicial = v_ante;

    while (ss >> v) { 
      
      //Monta os poligonos 
      //Descreve um poli. como a sequencia dos vertices em setido anti horario
      p.vertices.push_back(vetor_vertices[v_ante-1]);
      
      //Monta as SA na face
      if(eh_primeira_sa){

        eh_primeira_sa = false;
        sa_inicial = cria_semiaresta<t_ponto>(v_ante, v, f, nullptr, mapa_sa, vetor_vertices, &nsp, vetor_vertices_sa);
        if(!sa_inicial){
          if(nsp){
            cout<<"não subdivisão planar\n";
            return 0;
          }
          perror("Erro ao montar face no main()\n");
          return 1;
        }
        
        f->semi_aresta_inicial = sa_inicial;
        f->quant_lados ++;
        sa_anterior = sa_inicial;

      }
      else{
        sa_aux = cria_semiaresta<t_ponto>(v_ante, v, f, sa_anterior, mapa_sa, vetor_vertices, &nsp, vetor_vertices_sa);
        if(!sa_aux){
          if(nsp){
            cout<<"não subdivisão planar\n";
            return 0;
          }
          perror("Erro ao montar face no main()\n");
          return 1;
        }
        f->quant_lados ++;
        sa_anterior = sa_aux;
      }

      v_ante=v;
    }//while

    //Fecha os ciclos
    //Conecta com o primeiro vertice da face
    sa_aux = cria_semiaresta<t_ponto>(v_ante, v_inicial, f, sa_anterior, mapa_sa, vetor_vertices, &nsp, vetor_vertices_sa);
    if(!sa_aux){
      if(nsp){
        cout<<"não subdivisão planar\n";
        return 0;
      }
      perror("Erro ao montar face no main()\n");
      return 1;
    }
    
    //Faces
    sa_aux->prox = sa_inicial;         // Última SA aponta para a primeira
    sa_inicial->ante = sa_aux;         // Primeira SA aponta de volta
    f->quant_lados ++;

    //Poligonos
    p.vertices.push_back(vetor_vertices[v_ante - 1]);

    //Adiciona face e poligono nas listas
    lista_faces.push_back(f);  
    lista_poligonos.push_back(p);

  }//for i

  #ifdef DEBUG
  cout<<"Lista de vertices.\n";
  for(int i=0; i< static_cast<int> (vetor_vertices.size()); i++){
    cout<<"Vertice["<<i<<"] -> "<< vetor_vertices[i]<<"\n";
  }
  
  cout<<"\nLista de Poligonos.\n";
  for(auto it{lista_poligonos.begin()}; it != lista_poligonos.end(); ++it){
    cout<<*(it)<<"\n";
  }
  
  cout<<"\nLista de faces.\n";
  for(auto it{lista_faces.begin()}; it != lista_faces.end(); ++it){
    cout<<*(*(it))<<"\n\n";
  }
  #endif

  if(!todas_tem_twin<t_ponto>(lista_faces)){
    cout << "aberta\n";
    return 0;
  }

  // verifica se alguma aresta intersecta a sua ou outras faces
  // if(possuem_Intersecao(lista_poligonos, mapa_sa)) {
  //   cout << "superposta\n";
  //   return 0;
  // }

  // if(ha_faces_sobrepostas<t_ponto>(lista_poligonos)) {
  //   cout << "superposta\n";
  //   return 0;
  // }
  
  return 0;
}