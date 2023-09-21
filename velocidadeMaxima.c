/*
    Aluno: Matheus dos Santos Sousa
    Curso: Ciência da Computação
    Turma: B
    RA: 812051
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define DEBUG 0
#define IMPRIME 1

typedef struct noh Noh ; // Estrutura para representar uma aresta
struct noh 
{
    int rotulo;
    int peso;
    Noh * prox;
}; 

typedef struct grafo *Grafo ; // Estrutra para representar uma lista de adjacência
struct grafo 
{
    Noh ** A;
    int n; // número de vértices
    int m; // número de arestas/arcos
}; 

Grafo inicializaGrafo(int n) 
{
    int i;
    Grafo G = malloc (sizeof * G); // Aloca um vetor de ponteiros para Noh
    G -> n = n;
    G -> m = 0;
    G -> A = malloc (n * sizeof(Noh *));
    for(i = 0 ; i < n ; i++)
        G->A[i] = NULL ;
    return G ;
} 

void insereArcoGrafo(Grafo G, int v, int w, int c) 
{
    Noh *p;
    for(p = G->A[v]; p != NULL ; p = p->prox)
        if(p->rotulo == w) // Verifica se o aresta já está presente
            return;
    p = malloc (sizeof(Noh));
    p->rotulo = w;
    p->peso = c;
    p->prox = G->A[v];
    G->A[v] = p;
    G->m++;

    if(DEBUG)
        printf("Aresta: %d-%d, peso: %d\n", v, w, c);
}

int verificaLista(int *R, int fim, int v)
{
    for(int i = 0; i < fim; i++)
    {
        if(R[i] == v)
            return 0;
    }
    return 1;
}

void percorrePista(Grafo G, int origem, int *dist, int *pred) 
{                                                           
    int i, counter = 0;
    int v, w, peso;
    Noh *p;
    int flag = 1; // Indica até quando será preciso percorre todos os vértices
    int *R = (int*) malloc(sizeof(int) * G->n); // Lista para controlar os vértices procurados
    int inicio, fim;

    // inicializando distâncias e predecessores
    for(i = 0 ; i < G->n ; i++) 
    {
        dist[i] = INT_MIN;
        pred[i] = - 1;
    }
    dist[origem] = 0;


    // Percorremos todas as arestas do grafo (nro. de vértices - 1) vezes
    while (flag == 1) 
    {
        inicio = 0; fim = 0; // Inicializa a lista
        R[fim++] = origem;
        flag = 0;
        while(fim > inicio) // Verificamos cada vértice
        {
            v = R[inicio++];
            if(DEBUG)
                printf("v = %d\n", v); 
            // percorrendo lista com vizinhos de v
            for(p = G->A[v]; p != NULL; p = p->prox) 
            {
                w = p->rotulo;
                peso = p->peso;
                if(DEBUG)
                    printf("rotulo: %d; peso: %d, dist: %d \n", w, peso, dist[v]);

            // e atualizando as distâncias e predecessores quando for o caso
                if(dist[v] != INT_MIN && dist[w] < dist[v] + peso) 
                {
                    dist[w] = dist[v] + peso; 
                    pred[w] = v;              
                    if(DEBUG)
                    {
                        printf("Nova distancia de %d: %d; Novo predecessor: %d\n", w, dist[w], pred[w]);
                    }
                    flag = 1; // Indica que ocorreu mudança
                }
                if(verificaLista(R, fim, w)) // Se um vértice já está na lista
                {
                    R[fim++] = w; // Caso não estaja, ele é adicionado na lista
                }
                counter++;
                if(DEBUG)
                {
                    printf("Counter = %d\n", counter);
                    printf("Inicio = %d, fim = %d \n", inicio, fim);
                }
            }
        }
    }
    if(IMPRIME)
        printf("Counter: %d\n", counter);
} 

void imprime(int *dist, int *pred, int n)
{
    printf("dist:\n");
    for(int i = 0; i < n; i++)
        printf("%d: %d\n", i, dist[i]);

    printf("\npred:\n");

    for(int i = 0; i < n; i++)
        printf("%d: %d\n", i, pred[i]);
    printf("\n");
}

int main()
{
    int n, m, vel_ini;
    int u, v, c;

    scanf("%d %d %d", &n, &m, &vel_ini);

    if(DEBUG)
        printf("Leu o n, m e vel_ini\n");

    Grafo G = inicializaGrafo(n);

    if(DEBUG)
        printf("Inicializou o grafo\n");

    for(int i = 0; i < m; i++)
    {
        scanf("%d %d %d", &u, &v, &c);    
        insereArcoGrafo(G, u, v, c);
    }

    if(DEBUG)
        printf("Inseriu todas as arestas\n");

    int *dist = (int*) malloc(sizeof(int) * n);
    int *pred = (int*) malloc(sizeof(int) * n);

    percorrePista(G, 0, dist, pred);

    if(DEBUG)
        printf("Percorreu a pista \n");

    if(DEBUG)
        imprime(dist, pred, n);

    printf("%d\n", dist[n-1] + vel_ini);

    return 0;
}
