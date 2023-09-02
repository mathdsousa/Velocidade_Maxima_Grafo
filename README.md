# Velocidade Máxima em um Grafo Ponderado

Este repositório é destinado para o segundo trabalho da matéria Algoritmos e Estruturas de Dados 2.

## Introdução
No segundo Trabalho Prático (TP02), será solicitada a entrega de um programa que solucione o problema apresentado na próxima seção. O arquivo entregue deve seguir os itens abaixo:

O TP02 deverá ser feito individualmente, e plágio não será tolerado;
O TP02 deve ser feito em linguagem C, com um cabeçalho contendo as informações do estudante (nome, curso, RA);
Compile o seu TP02 usando o compilador GCC com as flags -Wall -pedantic -O2 -Wno-unused-result.
Velocidade Máxima
Considere um jogo de corrida futurista cujo objetivo é cruzar a linha de chegada com a maior velocidade possível. O competidor começa do ponto de partida com uma velocidade inicial (V), e ao passar por cada trecho da pista recebe um bônus ou uma penalidade (advindos de eletroimãs) sobre sua velocidade, que deve ser somado ou subtraída da mesma. Em cada encruzilhada, o competidor tem de decidir qual caminho seguir, dentre as várias opções disponíveis. Como um subcaminho pode começar com um bônus tentador, mas ser seguido por inúmeras penalidades, é muito difícil resolver esse problema sem conhecimento global sobre o trajeto. Felizmente, antes de cada corrida, você pode ver toda a pista para planejar suas decisões. Importante, embora a pista possa ter inúmeras encruzilhadas em que a partir de um caminho surgem vários, os trechos da mesma sempre vão em frente, te aproximando da linha de chegada.

## Entrada
Cada caso de teste é iniciado por uma linha contendo um inteiro N (2 ≤ N ≤ 10^9), um inteiro M (N - 1 ≤ M ≤ N(N - 1)/2), e um inteiro positivo V. Vamos usar um grafo orientado ponderado com N vértices e M arcos para representar a pista de corrida, sendo que o vértice 0 é o ponto de partida e o vértice N - 1 é a linha de chegada. Assim, após a primeira linha da entrada temos M outras linhas, cada uma delas contendo três valores (U, V, P) separados por espaços e correspondendo a um arco (U, V) com peso P. A ideia é que um caminho que passe pelo arco (U, V) soma o valor P à velocidade atual do competidor, com P sendo um inteiro que pode ser negativo ou positivo.

## Saída
A saída de um caso de teste contém apenas uma linha (terminada em '\n') contendo um inteiro, que indica a maior velocidade que um competidor pode alcançar ao cruzar a linha de chegada.
