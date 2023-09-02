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

void subtraiMaiorPeso(Grafo G, int n) // Subtrai dos pesos de todas as arestas o valor máximo de peso 
{                                     // encontrado
    for(int i = 0 ; i < G->n ; i++)
        for(Noh *p = G->A[i]; p != NULL ; p = p->prox)
            p->peso -= n;
}

void MaxDijkstra(Grafo G, int origem, int *dist, int *pred) // Dijkstra adaptado para o maior caminho
{
    int i, *R;
    int v, w, peso, tam_R, max_dist;
    Noh *p;
    
    // inicializando distâncias e predecessores
    for(i = 0 ; i < G->n ; i++) 
    {
        dist[i] = INT_MIN;
        pred[i] = - 1;
    }
    dist[origem] = 0;
    
    // inicializando conjunto de vértices "resolvidos" R
    R = malloc(G->n * sizeof(int));
    for (i = 0; i < G->n; i++)
        R[i] = 0;
    tam_R = 0;

    // enquanto não encontrar o caminho máximo para todo vértice
    while (tam_R < G->n) {
        // buscando vértice v em V \ R que maximiza dist[v]
        max_dist = INT_MIN;
        v = -1;
        for(i = 0 ; i <= G->n; i++)
            if(R[i] == 0 && dist[i] > max_dist) 
            {
                v = i;
                max_dist = dist[i];
            }
        if(DEBUG)
            printf("v: %d\n", v);
        // adicionando v a R e atualizando o conjunto R
        R[v] = 1; tam_R++;
        if(DEBUG && v == 0)
            printf("aresta: %d-%d, peso: %d\n", 0, G->A[v]->rotulo, G->A[v]->peso);
        // percorrendo lista com vizinhos de v
        for(p = G->A[v]; p != NULL; p = p->prox) {
            w = p->rotulo;
            peso = p->peso;
            if(DEBUG)
                printf("rotulo: %d; peso: %d\n", w, peso);

        // e atualizando as distâncias e predecessores quando for o caso
            if(R[w] == 0 && dist[w] < dist[v] + peso) 
            {
                dist[w] = dist[v] + peso;
                pred[w] = v;
            }
        }
    }
    free(R);
} 

int qntdArestasPercorridas(int *pred, int n) // Calcula quantidade de arestas percorridas do vértice
{                                            // 0 até n-1 pelo caminho de velocidade máxima
    int qntd_arestas = 0, vertice = n - 1;

    while(pred[vertice] != -1)
    {
        vertice = pred[vertice];
        qntd_arestas++;
    }

    return qntd_arestas;
}

void imprime(int *dist, int *pred, int n)
{
    printf("dist: ");
    for(int i = 0; i < n; i++)
        printf("%d ", dist[i]);

    printf("\npred:");

    for(int i = 0; i < n; i++)
        printf("%d ", pred[i]);
    printf("\n");
}

int main()
{
    int n, m, vel_ini;
    int u, v, c;
    int maiorPeso = INT_MIN;
    int result;

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
        if(maiorPeso < c) // Guarda o valor do maior peso encontrado
            maiorPeso = c;
    }

    if(DEBUG)
        printf("aresta: %d-%d, peso: %d\n", 0, G->A[0]->rotulo, G->A[0]->peso);

    if(DEBUG)
        printf("maiorPeso: %d\n", maiorPeso);

    if(DEBUG)
        printf("Inseriu todas as arestas\n");

    subtraiMaiorPeso(G, maiorPeso);

    if(DEBUG)
        printf("Subtraiu os pesos\n");

    int *dist = (int*) malloc(sizeof(int) * n);
    int *pred = (int*) malloc(sizeof(int) * n);

    Dijkstra(G, 0, dist, pred);

    if(DEBUG)
        printf("Passou pelo Dijkstra\n");

    if(DEBUG)
        printf("aresta: %d-%d, peso: %d\n", 0, G->A[0]->rotulo, G->A[0]->peso);

    if(DEBUG)
        imprime(dist, pred, n);

    int qntArestasPercorridas = qntdArestasPercorridas(pred, n);

    if(DEBUG)
        printf("quantidade de arestas percorridas: %d\n", qntArestasPercorridas);

    // Para compensar as subtrações feitas nos pesos, soma-se o valor do maior peso em
    // cada uma das arestas percorridas nesse caminho de maior velocidade
    result = qntArestasPercorridas * maiorPeso + dist[n - 1] + vel_ini;

    printf("%d\n", result);

    return 0;
}