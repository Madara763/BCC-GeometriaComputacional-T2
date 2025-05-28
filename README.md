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

### Solução  
//descrever a logica da coisa

# Desenho/
Contem 2 scripts em python.
```
drawtrab2.py 
plota_entrada_dcel.py
```
o drawtrab2.py eh o que foi disponibilizado para plotar a saida do trabalho.
o plota_entrada_dcel.py recebe a mesma entrada do trabalho e plota a entrada recebida.
