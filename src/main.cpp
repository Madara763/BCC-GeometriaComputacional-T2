#include <iostream>
#include <sstream>
#include "poligono.hpp"
#include "raycast.hpp"

using namespace std;


int main(){

  //Leitura dos dados
  int nVertices, nFaces; //Quantidade de vertices e faces respectivamente
  
  cin>>nVertices>>nFaces;
  
  vector<ponto<double>> vetor_vertices;

  //Le os vertices 
  ponto<double> p;
  for(int i=0; i<nVertices; i++){
  
    cin>>p.x>>p.y;
    vetor_vertices.push_back(p);
  
  }//for i

  //descarta o fim da ultima linha, vamos ver linha inteiras daqui pra frente
  cin.ignore(); 


  list<face<double>> lista_faces;
  aresta<double> a;

  int v, v_ante, inicial;
  string linha;
  for(int i=0; i<nFaces; i++){ //Le a face
    face<double> f;
    getline(cin, linha);       // lê a linha inteira
    istringstream ss(linha);   // cria um stream da linha

    //le cada indice
    ss >> v_ante;
    inicial = v_ante;
    while (ss >> v) { 
      
      //Monta as faces
      a.ini = vetor_vertices[v_ante-1];
      a.fim = vetor_vertices[v-1];

      f.lados.push_back(a);
      f.quant_lados++;

      v_ante=v;
    }
    //Conecta com o primeiro vertice
    a.ini = vetor_vertices[v_ante-1];
    a.fim = vetor_vertices[inicial-1];

    f.lados.push_back(a);
    f.quant_lados++;

    lista_faces.push_back(f);

  }//for i

  //#ifdef DEBUG
  cout<<"Lista de vertices.\n";
  for(int i=0; i< static_cast<int> (vetor_vertices.size()); i++){
    cout<<"Vertice["<<i<<"] -> "<< vetor_vertices[i]<<"\n";
  }

  cout<<"\nLista de faces.\n";
  for(auto it{lista_faces.begin()}; it != lista_faces.end(); ++it){
    
    cout<<"Face["<<it->quant_lados<<"]: ";
    for(int i = 0; i < static_cast<int> (it->quant_lados); i++)
      cout<<it->lados[i]<<"  ";
    
    cout<<"\n";
  }
  //#endif

  return 0;
}