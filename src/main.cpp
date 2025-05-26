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
  vector<ponto<double>> vetor_vertices;
  vector<semi_aresta<double>*> vetor_vertices_sa(nVertices, NULL);

  //Le os vertices 
  ponto<double> p;
  for(int i=0; i<nVertices; i++){
  
    cin>>p.x>>p.y;
    vetor_vertices.push_back(p);
  
  }//for i

  //descarta o fim da ultima linha, vamos ver linha inteiras daqui pra frente
  cin.ignore(); 


  //Criamos poligonos e faces
  list<poligono<double>> lista_poligonos;
  semi_aresta<double> semi_aresta_anterior;
  
  int v, v_ante, inicial;
  string linha;
  for(int i=0; i<nFaces; i++){ // Le a face

    poligono<double> p;        // Cria o poligono
    getline(cin, linha);       // Le a linha inteira
    istringstream ss(linha);   // Cria um stream da linha

    //le cada indice
    ss >> v_ante;
    inicial = v_ante;
    while (ss >> v) { 
      
      //Monta os poligonos 
      //Descreve um poli. como a sequencia dos vertices em setido anti horario
      p.vertices.push_back(vetor_vertices[v_ante-1]);

      // a.ini = vetor_vertices[v_ante-1];
      // a.fim = vetor_vertices[v-1];

      // f.lados.push_back(a);
      // f.quant_lados++;

      v_ante=v;
    }
    //Conecta com o primeiro vertice
    // a.ini = vetor_vertices[v_ante-1];
    // a.fim = vetor_vertices[inicial-1];

    // f.lados.push_back(a);
    // f.quant_lados++;

    lista_poligonos.push_back(p);

  }//for i

  //#ifdef DEBUG
  cout<<"Lista de vertices.\n";
  for(int i=0; i< static_cast<int> (vetor_vertices.size()); i++){
    cout<<"Vertice["<<i<<"] -> "<< vetor_vertices[i]<<"\n";
  }

  cout<<"\nLista de Poligonos.\n";
  for(auto it{lista_poligonos.begin()}; it != lista_poligonos.end(); ++it){
    cout<<*(it)<<"\n";
  }
  
  

  // cout<<"\nLista de faces.\n";
  // for(auto it{lista_faces.begin()}; it != lista_faces.end(); ++it){
    
  //   cout<<"Face["<<it->quant_lados<<"]: ";
  //   for(int i = 0; i < static_cast<int> (it->quant_lados); i++)
  //     cout<<it->lados[i]<<"  ";
    
  //   cout<<"\n";
  // }
  //#endif

  return 0;
}