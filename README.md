# Malha DCEL
## Trabalho 2 - Geometria Computacional
Este repositório contém a implementação do segundo trabalho da disciplina **Geometria Computacional (CI1338)** da **Universidade Federal do Paraná (UFPR)**, com foco na **construção e verificação de um DCEL**.  

### Descrição  
#### Entrada  
Um conjunto de N pontos/vertices descritos como (x,y).  
Um conjuto de F faces descritas como a sequencia dos vertices em sentido anti-horario.  

#### Problema  
Verificar se a combinação das faces atende aos requisitos de uma **DCEL**:  
A malha deve ser uma subdivisão completa do espaço, ou seja, uma aresta deve ser fronteira de duas faces.  
Cada semi-aresta deve ter um par correspondente a mesma aresta.  
As faces não devem se intersectar e seus interiores devem ser disjuntos dois a dois.  

#### Saida  
Caso a malha descrita na entrada nao atinja os requisitos deve ser classificada como:  
Aberta: Caso alguma Semi-Aresta não tenha uma aresta par correspondente.
Superposta: Caso mais de uma face descreva a mesma região do espaço em seu interior.  
Não Subdivisão Planar: Caso uma aresta faça fronteira com mais de 2 faces (acaba caindo no caso de Superposta).  

### Estruturas de dados DCEL  
Para a DCEL é necessário uma estrutura de semi-aresta, descrita em `poligono.hpp`:  
Versão simplificada da semi-aresta, omite algums atributos usado para construção da DCEL.  
```
template <typename T> struct semi_aresta{
  int id;   // id único da instância
  int index{0};   //ind do ponto no vetor lido na entrada
  semi_aresta<T>* prox;   //ponteiro para a proxima semi-aresta na face
  semi_aresta<T>* ante;   //ponteiro para a semi-aresta anterior na face
  semi_aresta<T>* par;   //ponteiro para a semi-aresta par a essa, par pertence a outra face
  face<T>* face_incidente;   //ponteiro para a face ao qual essa semi-aresta pertence
};
```
Versão simplificada da face, omite algums atributos usado para construção da DCEL.  
```
template <typename T> struct face{
  int id;  // id único da instância
  semi_aresta<T>* semi_aresta_inicial;
  u_int32_t quant_lados{0};
};
```




### Solução  


# Desenho/
Contem 2 scripts em python.
```
drawtrab2.py 
plota_entrada_dcel.py
```
o drawtrab2.py eh o que foi disponibilizado para plotar a saida do trabalho.
o plota_entrada_dcel.py recebe a mesma entrada do trabalho e plota a entrada recebida.
