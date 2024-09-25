// COLOQUE OS NOMES DOS RESPONSÁVEIS AQUI: Gustavo Pompermayer Fulanetti Silva E
// João Gabriel de Senna Lamolha

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

// INFORME O NRO DO GRUPO CONFORME PLANILHA DIVULGADA
int grupo() { return 23; }

// ESCREVA O NROUSP AQUI
int nroUSP1() { return 14760280; }

// E O SEGUNDO NROUSP AQUI, SE HOUVER
int nroUSP2() { return 14777879; }

// elemento da lista de resposta - NAO ALTERE ESTA DEFINICAO
typedef struct estr {
  int adj; // elemento do caminho
  struct estr *prox;
} NO;

// typedef dos nos(cidades)
typedef struct s {
  int adj; // elemento do caminho
  int peso;
  struct s *prox;
} NOH;

// typedef dos vertices
typedef struct {
  NOH *inicio;
  int ganhos;
  int flag;
} VERTICE;

// inicializar grafo:

void zerarFlags(VERTICE *g, int N) {
  int i;
  for (i = 1; i <= N;
       i++) { // enqto i <= numero de vertices, zera o vetor de flags.
    g[i].flag = 0;
  }
}

VERTICE *criaGrafo(int n, int ganhos[]) {
  int i;
  VERTICE *resp = (VERTICE*)malloc(sizeof(VERTICE) * (n + 1));
  for (i = 1; i <= n; i++) {
    resp[i].inicio = NULL;
    resp[i].ganhos = ganhos[i - 1];
  }
  return resp;
}

bool arestaExiste(VERTICE *g, int i, int j, int peso) {
  NOH *p = g[i].inicio;
  while (p) {
    if (p->adj == j)
      return (true);
    p = p->prox;
  }
  return (false);
}

void insereAresta(VERTICE *g, int i, int j, int peso) {
  if (arestaExiste(g, i, j, peso))
    return;
  NOH *novo = (NOH *)malloc(sizeof(NOH));
  novo->adj = j;
  novo->peso = peso;
  novo->prox = g[i].inicio;
  g[i].inicio = novo;
  if(i!=j){
  NOH* novo1 = (NOH*)malloc(sizeof(NOH));
  novo1->adj = i;
  novo1->peso = peso;
  novo1->prox = g[j].inicio;
  g[j].inicio = novo1;
   }
}

bool acabou;
NO* dfs(VERTICE *g, int N, int inicio, int fim, int *dinheiro, NO *resp) {
  g[inicio].flag = 1;
  if (inicio == fim) {
    NO *novo = (NO *)malloc(sizeof(NO));
    novo->adj = inicio;
    novo->prox = NULL;
    resp = novo;
    acabou = true;
    return resp;
  }
  NOH *p = g[inicio].inicio;
  while (p) {
    if (g[p->adj].flag == 0 && *dinheiro >= p->peso) {
      int dinheiro_copia = *dinheiro;
      dinheiro_copia = dinheiro_copia - (p->peso);
      dinheiro_copia += g[p->adj].ganhos;
      resp = dfs(g, N, p->adj, fim, &dinheiro_copia, resp);
      if(acabou){
        NO* novo2 = (NO*)malloc(sizeof(NO));
        novo2->adj = inicio;
        novo2->prox = resp;
        resp = novo2;
        return resp;
      }
    }
    p = p->prox;
  }
  g[inicio].flag = 2;
  if(!acabou){
    resp = NULL;
  }
  return resp;
}


// funcao principal
NO *caminho(int N, int A, int ijpeso[], int ganhos[], int inicio, int fim,
            int *dinheiro) {
  NO *resp = NULL;
  resp = (NO *)malloc(sizeof(NO));
  VERTICE *g = criaGrafo(N, ganhos);
  zerarFlags(g, N);
  acabou = false;
  for (int i = 1; i <= A; i++) {
    insereAresta(g, ijpeso[3 * i - 3], ijpeso[3 * i - 2], ijpeso[3 * i - 1]);
  }
  resp = dfs(g, N, inicio, fim, dinheiro, resp);
  free(g);
  return resp;
}

