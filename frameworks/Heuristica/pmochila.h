#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <iostream>
#include <limits.h>
#include <float.h>
#include "arraylist.h"

#define MAX(x,y) ((x)<(y) ? (y) : (x))

typedef struct{
	int id;
	double peso;        // peso do objeto
	double utilidade;   // utilidade do objeto
	double profit;      // profit do objeto (utilidade/peso)
} Objeto;

typedef struct{
	int bit;
} Elemento;

// Menus
int menu_principal(void);
int menu_construtivo(void);
int menu_busca_local(void);
int menu_metaheuristicas(void);

// Util
void le_arquivo(const char *nomearq, double *vetor);
double calcula_fo(int *s, int num_objetos, double *p, double *w, double b);
void imprime_solucao(int *s, int num_objetos, double *p, double *w, double b);
const Boolean obj_equals(const Object object_1, const Object object_2);
void troca_bit(int *s, int j);
void vizqqN1(int n, int *s, double *p, double *w, double b);
void vizqqN2(int n, int *s, double *p, double *w, double b);
void perturbacao(int n, int *s, double *p, double *w, double b, double pert);
double calcula_temperatura_inicial(int n, int *s, double *p, double *w, double b, double alfa, int SAmax);
void imprime_lista_tabu(Arraylist lista);
int melhor_vizinho_BT(int n, int *s, double *p, double *w, double b, double fo_star, int *melhor_posicao, int *valor_bit, Arraylist listaTabu);
int roleta(int nind, double *fo_pop);

// Lista encadeada
Arraylist cria_lista_objetos(int n, int *s, double *p, double *w);
Arraylist cria_lista_objetos_ordenada(int n, int *s, double *p, double *w);
void imprime_lista(Arraylist lista);

// Contrutivos
void constroi_solucao(int n, int *s, double *p, double *w, double b, double percentual);
void constroi_solucao_aleatoria(int n, int *s, double *p, double *w, double b);
void constroi_solucao_grasp(int n, int *s, double *p, double *w, double b, double alfa);

// Busca Local
void busca_local_primeiro_aprimorante(int n, int *s, double *p, double *w, double b);
void busca_local_melhor_aprimorante(int n, int *s, double *p, double *w, double b);
void busca_local_randomica(int n, int *s, double *p, double *w, double b, int iter_max);

// Metaheuristicas
void VND(int n, int *s, double *p, double *w, double b);
void VNS(int n, int *s, double *p, double *w, double b, int iter_max);
void MultiStart(int n, int *s, double *p, double *w, double b, int iter_max);
void ILS(int n, int *s, double *p, double *w, double b, int iter_max);
void grasp(int n, int *s, double *p, double *w, double b, int iter_max, double alfa);
void SA(int n, int *s, double *p, double *w, double b, double alfa, double temperatura_inicial, double temperatura_final, int SAmax);
void BT(int n, int *s, double *p, double *w, double b, double tamLT, int BTmax);
void AG(int n, int *s, double *p, double *w, double b, int nind, int max_geracoes, double prob_crossover, double prob_mutacao);
void AC(int n, int *s, double *p, double *w, double b, int numF, double Q, double F0, double alfa, double beta, double fator_evap, int iter_max);
