#include "pmochila.h"

/******************************************************************************************/
/*										MAIN											  */
/******************************************************************************************/
int main(int argc, char **argv)
{
	int n;              // numero de objetos
	double b;           // capacidade da mochila
	int *s;             // vetor solucao corrente
	int *s_star;        // vetor melhor solucao
	double *w;          // vetor de peso de cada objeto
	double *p;          // vetor de utilidade de cada objeto
	double fo;          // funcao objetivo corrente
	double fo_star;     // melhor funcao objetivo
	
	int choice;
	
	n = atoi(argv[1]); // numero de objetos
	const char *file_b = argv[2]; // arquivo de capacidade
	const char *file_w = argv[3]; // arquivo de pesos
	const char *file_p = argv[4]; // arquivo de utilidades
	
	srand((unsigned) time(NULL)); // pega a hora do relogio como semente
	
	// Cria os vetores
	s = (int *) malloc(n * sizeof(int));
	s_star = (int *) malloc(n * sizeof(int));
	w = (double *) malloc(n * sizeof(double));
	p = (double *) malloc(n * sizeof(double));
	
	// Le os arquivos da instancia a ser testada
	le_arquivo(file_b, &b); // capacidade
	le_arquivo(file_w, w); // peso
	le_arquivo(file_p, p); // utilidade
	fo_star = - DBL_MAX; // inicializa FO da melhor solucao
	
	do {
		choice = menu_principal();
		switch (choice) {
			case 1: /* Geracao de uma solucao inicial */
				switch(menu_construtivo()) {
					case 1: /* Geracao gulosa de uma solucao inicial */
						constroi_solucao(n,s,p,w,b,0);
						printf("Solucao construida de forma gulosa:\n");
						imprime_solucao(s,n,p,w,b);
						break;
					case 2: /* Geracao parcialmente gulosa de uma solucao inicial */
						constroi_solucao(n,s,p,w,b,0.50);
						printf("Solucao construida de forma parcialmente gulosa:\n");
						imprime_solucao(s,n,p,w,b);
						break;
					case 3: /* Geracao aleatoria de uma solucao inicial viavel */
						constroi_solucao(n,s,p,w,b,1);
						printf("Solucao viavel construida de forma aleatoria:\n");
						imprime_solucao(s,n,p,w,b);
						break;
					case 4: /* Geracao aleatoria de uma solucao inicial */
						constroi_solucao_aleatoria(n,s,p,w,b);
						printf("Solucao construida de forma aleatoria:\n");
						imprime_solucao(s,n,p,w,b);
						break;
				}
				break;
			case 2: /* Busca Local */
				switch (menu_busca_local()) {
					case 1: /* Primeiro aprimorante */
						busca_local_primeiro_aprimorante(n,s,p,w,b);
						printf("Solucao refinada pela busca local do Primeiro Aprimorante:\n");
						imprime_solucao(s,n,p,w,b);
						break;
					case 2: /* Melhor aprimorante */
						busca_local_melhor_aprimorante(n,s,p,w,b);
						printf("Solucao refinada pela busca local do Melhor Aprimorante:\n");
						imprime_solucao(s,n,p,w,b);
						break;
					case 3: /* Randomica */
						busca_local_randomica(n,s,p,w,b,10);
						printf("Solucao refinada pela busca local Randomica:\n");
						imprime_solucao(s,n,p,w,b);
						break;
					default:
						break;
				}
				break;
			case 3: /* Metaheuristicas */
				switch (menu_metaheuristicas()) {
					case 1: /* VND */
						VND(n,s,p,w,b);
						printf("Solucao do VND:\n");
						imprime_solucao(s,n,p,w,b);
						break;
					case 2: /* VNS */
						VNS(n,s,p,w,b, 100);
						printf("Solucao do VNS:\n");
						imprime_solucao(s,n,p,w,b);
						break;
                    			case 3: /* Multi Start */
						MultiStart(n,s,p,w,b,100);
						printf("Solucao do Multi Start:\n");
						imprime_solucao(s,n,p,w,b);
						break;
					case 4: /* ILS */
						ILS(n,s,p,w,b,50);
						printf("Solucao do ILS:\n");
						imprime_solucao(s,n,p,w,b);
						break;
					case 5: /* GRASP */
						grasp(n,s,p,w,b,50,0.7);
						printf("Solucao do GRASP:\n");
						imprime_solucao(s,n,p,w,b);
						break;
                    case 6: /* Simulated Annealing */
						SA(n,s,p,w,b,0.97,calcula_temperatura_inicial(n,s,p,w,b,0.8,n*(n-1)/2),0.01,n*(n-1)/2);
						printf("Solucao do Simulated Annealing:\n");
						imprime_solucao(s,n,p,w,b);
						break;
					case 7: /* BT */
						BT(n,s,p,w,b,0.4,100);
						printf("Solucao da Busca Tabu:\n");
						imprime_solucao(s,n,p,w,b);
						break;
                    case 8: /* AG */
						AG(n,s,p,w,b,30,100,0.6,0.1);
						printf("Solucao do AG:\n");
						imprime_solucao(s,n,p,w,b);
						break;
                    case 9: /* AC */
						AC(n,s,p,w,b,10,10,10,0.5,0.5,0.95,10);
						printf("Solucao do AC:\n");
						imprime_solucao(s,n,p,w,b);  
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}
	} while (choice != 0);
	
	// Libera memoria
	free(s);
	free(s_star);
	free(w);
	free(p);
	return 0;
	
}

/******************************************************************************************/
/*				MENUS							  */
/******************************************************************************************/

// Menu principal
int menu_principal(void)
{
	int escolha;
	
	do {
		printf("\n************************************************* \n");
		printf("         1. Gere solucao inicial \n");
		printf("         2. Busca Local \n");
		printf("         3. Metaheuristicas \n");
		printf("         0. Sair \n");
		printf("         Escolha: ");
		if (!scanf("%d",&escolha)) printf("Falha na leitura!\n");
	} while (escolha < 0 || escolha > 3);
	return escolha;
}

// Menu de geracao de uma solucao inicial
int menu_construtivo(void)
{
    int escolha;
    
    do {
        printf("\nGERACAO DA SOLUCAO INICIAL: \n");
        printf("                  1. Gulosa \n");
        printf("                  2. Parcialmente gulosa\n");
        printf("                  3. Aleatoria viavel\n");
        printf("                  4. Aleatoria\n");
        printf("                  escolha: ");
        if (!scanf("%d",&escolha)) printf("Falha na leitura!\n");
    } while (escolha < 1 || escolha > 4);
    return escolha;
}

// Menu de busca local
int menu_busca_local(void)
{
	int escolha;
	
	do {
		printf("\nBUSCA LOCAL: \n");
		printf("                  1. Primeiro Aprimorante \n");
		printf("                  2. Melhor Aprimorante\n");
		printf("                  3. Randomica\n");
		printf("                  escolha: ");
		if (!scanf("%d",&escolha)) printf("Falha na leitura!\n");
	} while (escolha < 1 || escolha > 3);
	return escolha;
}

// Menu de metaheuristicas
int menu_metaheuristicas(void)
{
	int escolha;
	
	do {
		printf("\nMETAHEURISTICAS: \n");
		printf("                  1. VND \n");
		printf("                  2. VNS\n");
		printf("                  3. Multi Start\n");
		printf("                  4. ILS\n");
		printf("                  5. GRASP\n");
        printf("                  6. Simulated Annealing\n");
		printf("                  7. Busca Tabu\n");
		printf("                  8. Algoritmo Genetico\n");
		printf("                  9. Colonia de Formigas\n");
		printf("                  escolha: ");
		if (!scanf("%d",&escolha)) printf("Falha na leitura!\n");
	} while (escolha < 1 || escolha > 9);
	return escolha;
}


/******************************************************************************************/
/*				UTIL							  */
/******************************************************************************************/

// Leitura do arquivo
void le_arquivo(const char *nomearq, double *vetor)
{
	int j;
	double valor;
	FILE *arquivo;
	
	arquivo = fopen(nomearq,"r");
	if (!arquivo) {
		printf("O Arquivo %s nao pode ser aberto.\n", nomearq);
		getchar();
		exit(1);
	}
	j = 0;
	while (!feof(arquivo)){
		if (!fscanf(arquivo, "%lf\n", &valor)) {
			printf("Falha na leitura!\n");
			exit(1);
		}
		vetor[j] = valor;
		j++;
	}
	fclose(arquivo);
}

// Calcula fo
double calcula_fo(int *s, int num_objetos, double *p, double *w, double b)
{
	double fo;
	double utilidade = 0, peso = 0, penalidade = 0;
	
	for (int i = 0; i < num_objetos; i++) {
		if (s[i]) {
			utilidade += p[i];
			peso += w[i];
		}
		penalidade += w[i];
	}
	
	// FO e a soma das utilidades dos objetos na mochila
	// menos o excesso de peso na mochila x penalidade
	fo = utilidade - penalidade * MAX(0, peso - b);
	
	return fo;
}


// Imprime solucao
void imprime_solucao(int *s, int num_objetos, double *p, double *w, double b)
{
	double fo;
	double utilidade = 0, peso = 0, penalidade = 0;
	
	for (int i = 0; i < num_objetos; i++) {
		if (s[i]) {
			utilidade += p[i];
			peso += w[i];
		}
		penalidade += w[i];
	}
	
	// FO e a soma das utilidades dos objetos na mochila
	// menos o excesso de peso na mochila x penalidade
	fo = utilidade - penalidade * MAX(0, peso - b);
	
	
	printf("FO = %.2lf\n", fo);
    printf("Peso = %.2lf\n", peso);
    printf("Utilidade = %.2lf\n", utilidade);
    for (int j=0; j<num_objetos; j++) printf("s[%2d]=%d \n",j,s[j]);
}

// Verifica se objetos sao iguais
const Boolean obj_equals(const Object object_1, const Object object_2){
	
	Objeto *o1 = (Objeto*)object_1;
	Objeto *o2 = (Objeto*)object_2;
	
	if (o1->id == o2->id) return TRUE;
	else return FALSE;
}

// Cria lista dos objetos 
Arraylist cria_lista_objetos(int n, int *s, double *p, double *w)
{
	Objeto* o;
	Arraylist objetos;
	objetos = arraylist_create(obj_equals);
	   
	// Cria lista de objetos
	for (int i = 0; i < n; i++) {
		o = (Objeto*)malloc(sizeof(Objeto));
		o->id = i;
		o->peso = w[i];
		o->utilidade = p[i];
		o->profit = p[i]/w[i];
		arraylist_add(objetos, o);
	}
	return objetos;
}

// Criar lista dos objetos ordenada
Arraylist cria_lista_objetos_ordenada(int n, int *s, double *p, double *w)
{
	int pos;
	double maior;
	Objeto* o;
	
	Arraylist objetos = cria_lista_objetos(n,s,p,w);
	Arraylist objetosOrd = arraylist_create(obj_equals);
	   
	// Cria lista de objetos ordenada
	while (arraylist_size(objetos) > 0) {
		
		// Busca objeto com maior profit
        maior = -1;
		for (int i = 0; i < arraylist_size(objetos); i++) {
			if ( ((Objeto*)arraylist_get(objetos, i))->profit > maior) {
                maior = ((Objeto*)arraylist_get(objetos, i))->profit;
                pos = i;
			}
		}
        
		// Insere objeto na lista ordenada
		o = (Objeto*) arraylist_remove_index(objetos, pos);
		arraylist_add(objetosOrd, o);
	}
	return objetosOrd;
}

// Imprime lista
void imprime_lista(Arraylist lista){
	
	int size;
	Objeto *o;
	
	if(lista != NULL){
		//printf("[ID]\tUtilidade\tPeso\tProfit\n");
		size = arraylist_size(lista);
		for (int i = 0; i < size; i++)
		{
			o = (Objeto*)arraylist_get(lista, i);
			//printf("[%d]\t%lf\t%lf\t%lf\n", o->id, o->utilidade, o->peso, o->profit);
		}
		//printf("\n");
	}
}

// Insere ou retira o objeto j da mochila
void troca_bit(int *s, int j)
{
    if (s[j])
	s[j] = 0;
    else
	s[j] = 1;
}

/* aplica busca local pela estrategia do melhor aprimorante */
void melhor_vizinho_N1(int n, int *s, double *p, double *w, double b)
{
    double fo_original;
    double fo_max;
    double fo_vizinho;
    int melhor_bit;
    
    fo_original = calcula_fo(s, n, p, w, b);
    
    fo_max = -DBL_MAX;
        
    for (int j = 0; j < n; j++) {
            
        // cria vizinho
        troca_bit(s, j);
            
        fo_vizinho = calcula_fo(s,n,p,w,b);
            
        // armazena melhor vizinho
        if (fo_vizinho > fo_max) {
            melhor_bit = j;
            fo_max = fo_vizinho;
        }
            
        // volta a solucao inicial
        troca_bit(s,j);
    }
        
    // se encontrou algum vizinho melhor
    if (fo_max > fo_original) {
        troca_bit(s,melhor_bit);
        printf("Vizinho melhor em N1! FO = %lf\n", fo_max);
    }

}

/* aplica busca local pela estrategia do melhor aprimorante */
void melhor_vizinho_N2(int n, int *s, double *p, double *w, double b)
{
    double fo_max, fo_vizinho;
    int melhor_bit_1, melhor_bit_2;
    
    double fo_original = calcula_fo(s, n, p, w, b);
    
    fo_max = -DBL_MAX;
        
        // para cada par de posicoes do vetor
        for (int i = 0; i < n; i++) {
            
            // troca primeiro bit
            troca_bit(s, i);
            
            for (int j = i+1; j < n; j++) {
                
                
                // troca segundo bit
                troca_bit(s, j);
                
                // fo vizinho
                fo_vizinho = calcula_fo(s,n,p,w,b);
                
                // armazena melhor vizinho
                if (fo_vizinho > fo_max) {
                    melhor_bit_1 = i;
                    melhor_bit_2 = j;
                    fo_max = fo_vizinho;
                }
                
                // volta segundo bit
                troca_bit(s,j);
                
            }
            // volta a solucao inicial
            troca_bit(s,i);	
        }
        
        // se encontrou algum vizinho melhor
        if (fo_max > fo_original) {
            troca_bit(s,melhor_bit_1);
            troca_bit(s,melhor_bit_2);			
            printf("Vizinho melhor em N2! FO = %lf\n", fo_max);
        }
}

void vizqqN1(int n, int *s, double *p, double *w, double b)
{
    	int pos;

    	pos = ((float)rand()/RAND_MAX) * n;
	troca_bit(s,pos);

	printf("Vizinho qq N1 - FO = %lf\n", calcula_fo(s, n, p, w, b));
}

void vizqqN2(int n, int *s, double *p, double *w, double b)
{
    int p1, p2;
	
    p1 = ((float)rand()/RAND_MAX) * n;
    p2 = ((float)rand()/RAND_MAX) * n;
    while (p1 == p2) p2 = ((float)rand()/RAND_MAX) * n;
	
    troca_bit(s, p1);
    troca_bit(s, p2);

	printf("Vizinho qq N2 - FO = %lf\n", calcula_fo(s, n, p, w, b));
}


void perturbacao(int n, int *s, double *p, double *w, double b, double pert)
{
    // altera x %  dos bits, a partir de uma posicao aleatoria
    int pos, j, bits;

    // numero de bits a ser alterado
    bits = n * pert;

    // sorteia uma posicao para iniciar a inversao
    pos = ((float)rand()/RAND_MAX) * n;

    for(int i = 0; i < bits; i++){
        j = (pos+i)%n;
        troca_bit(s, j);
    }
}

double calcula_temperatura_inicial(int n, int *s, double *p, double *w, double b, double alfa, int SAmax)
{
    double r;              // numero aleatorio entre ZERO e UM
    double temperatura;    // temperatura corrente
    int iter;              // numero de iteracoes na temperatura corrente
    int posicao_escolhida; // objeto escolhido
    double delta;             // variacao de energia
    int aceitos, min_aceitos;
	double fo, fo_viz;
	
    temperatura = 2;
	constroi_solucao(n,s,p,w,b,1);
    printf("Solucao inicial:\n");
	imprime_solucao(s,n,p,w,b);
		   
    aceitos = 0;
    min_aceitos = (int) (alfa*SAmax);
    while (aceitos < min_aceitos){
		iter = 0;
		//printf("temperatura inicial = %f \n",temperatura);
		while (iter < SAmax){
            iter++;
			
			fo = calcula_fo(s, n, p, w, b);

            int p1, p2;
	
            p1 = ((float)rand()/RAND_MAX) * n;
            p2 = ((float)rand()/RAND_MAX) * n;
            while (p1 == p2) p2 = ((float)rand()/RAND_MAX) * n;
	        troca_bit(s, p1);
            troca_bit(s, p2);
			
	  	    /* calcule a variacao de energia */
            fo_viz = calcula_fo(s, n, p, w, b);
			delta = fo_viz - fo;
			
	  	    /* se houver melhora, aceite o vizinho */
	        if (delta > 0){
                aceitos++;
        	}
	        else {
				/* se houver piora, aceite o vizinho com uma determinada
                 probabilidade */
	            r = ((float)rand()/RAND_MAX);
                if (r < exp(delta/temperatura)){
                    aceitos++;
                }
	        }
            //troca_bit(s, posicao_escolhida);
            troca_bit(s, p1);
            troca_bit(s, p2);
		}
		//printf("aceitos = %d   min_aceitos = %d\n",aceitos, min_aceitos);
		if (aceitos < min_aceitos){
            aceitos = 0;
            temperatura = temperatura * 1.1;
        }
    }
    printf("temperatura inicial = %f \n",temperatura);
    
    return temperatura;
}

// Imprime lista tabu
void imprime_lista_tabu(Arraylist lista){
	
	int size;
	Elemento *e;
	
	if(lista != NULL){
		printf("Posicoes proibidas da Lista Tabu:");
		size = arraylist_size(lista);
		for (int i = 0; i < size; i++)
		{
			e = (Elemento*)arraylist_get(lista, i);
			printf("[%d] ", e->bit);
		}
		printf("\n");
	}
}

// Melhor vizinho
int melhor_vizinho_BT(int n, int *s, double *p, double *w, double b, double fo_star, int *melhor_posicao, int *valor_bit, Arraylist listaTabu)
{
    double fo;
    bool estanalistatabu;
    double melhorViz = -DBL_MAX;
    
    for (int j = 0; j < n; j++){
        troca_bit(s, j);
        fo = calcula_fo(s,n,p,w,b);
        estanalistatabu = false;
        
        // Verifica se esta na lista tabu
        for (int i = 0; i < arraylist_size(listaTabu); i++) {
            if (((Elemento *)arraylist_get(listaTabu, i))->bit == j){
                estanalistatabu = true;
            }
        }
        
        if (!estanalistatabu || (estanalistatabu && fo > fo_star)){
            if (fo > melhorViz) {
                melhorViz = fo;
                *melhor_posicao = j;
                *valor_bit = (w[j]*s[j] > 0);
            }
        }
        troca_bit(s, j);
    }
    return melhorViz;
}

// Roleta
int roleta(int nind, double *fo_pop)
{
	int j;
	double aux;
	double *escala, *fracao;
	int escolhido;
	
	fracao = (double *) malloc(nind * sizeof(double));
	escala = (double *) malloc(nind * sizeof(double));
	
	int soma = 0;
	
	for (int j=0; j < nind; j++){
		soma += fo_pop[j];
		//printf("fo_pop[%d] = %d \n",j,fo_pop[j]);
	}
	for (int j=0; j < nind; j++){
		fracao[j] = (double) fo_pop[j]/soma;
		//printf("fracao[%2d] = %f \n",j,fracao[j]);
	}
	escala[0] = fracao[0];
	//printf("escala[%2d] = %f \n",0,escala[0]);
	for (int j=1; j < nind; j++){
		escala[j] = escala[j-1] + fracao[j];
		//printf("escala[%2d] = %f \n",j,escala[j]);
	}
	aux = (float)rand()/RAND_MAX;
	j = 0;
	while (escala[j] <= aux) j++;
	escolhido = j;
	free(fracao);
	free(escala);
	return escolhido;
}


/******************************************************************************************/
/*				CONSTRUTIVOS						  */
/******************************************************************************************/

// Constroi uma solucao inicial
void constroi_solucao(int n, int *s, double *p, double *w, double b, double percentual)
{
	double peso = 0;
	double capacidade = 0;
	int j, tamRestrito;
	Objeto *o;
	
	// Limpa solucao
	for (int j=0; j<n; j++) s[j] = 0;
	
	// Cria lista de objetos ordenados
	Arraylist objetosOrd = cria_lista_objetos_ordenada(n,s,p,w);
	imprime_lista(objetosOrd);

	//printf("C: %lf\n", b);
	
	// Constroi solucao elemento a elemento, verificando se cada objeto cabe na capacidade residual da mochila
	while (arraylist_size(objetosOrd) > 0 && peso < b) {
		
		
		// Define o tamanho da lista restrita, ou seja, o percentual mais interessantes
		tamRestrito = percentual * arraylist_size(objetosOrd);
		
		// Sorteia posicao aleatoria da lista residual
		j = (int)((float)rand()/RAND_MAX * tamRestrito);
				
		// Recupera objeto
		o = (Objeto*)arraylist_get(objetosOrd, j);
		
		// Se objeto ainda nao esta na mochila e cabe nela, adiciona objeto a mochila
		if (s[o->id] != 1 && peso + o->peso <= b) {
			s[o->id] = 1;
			peso += o->peso;
		}
		
		// Remove objeto da lista, pois ja foi testado
		arraylist_remove_index(objetosOrd, j);
	}
}

// Constroi uma solucao inicial aleatoria
void constroi_solucao_aleatoria(int n, int *s, double *p, double *w, double b)
{	
	// Limpa solucao
	for (int j=0; j<n; j++) s[j] = 0;
	
	// Insere objetos aleatoriamente
	for (int j=0; j<n; j++) s[j] = ((float)rand()/RAND_MAX) * 2;
	
}

// Constroi uma solucao inicial
void constroi_solucao_grasp(int n, int *s, double *p, double *w, double b, double alfa)
{
	double peso = 0;
	double capacidade = 0;
	int j, tamRestrito;
    	double value;
	Objeto *o, *o1, *o2;
	
	// Limpa solucao
	for (int j=0; j<n; j++) s[j] = 0;
	
	// Cria lista de objetos ordenados
	Arraylist objetosOrd = cria_lista_objetos_ordenada(n,s,p,w);
	//imprime_lista(objetosOrd);
	
	// Constroi solucao elemento a elemento, verificando se cada objeto cabe na capacidade residual da mochila
	while (arraylist_size(objetosOrd) > 0 && peso < b) {
		
        	// Zera tam restrito
        	tamRestrito = 0;
		
		    // Define o tamanho da lista restrita, ou seja, os alfa % mais interessantes
        
        	// Recupera objeto
		    o1 = (Objeto*)arraylist_get(objetosOrd, 0);
        	o2 = (Objeto*)arraylist_get(objetosOrd, arraylist_size(objetosOrd)-1);
        	//printf("cmax: %.2lf   cmin: %.2lf\n", );
        	value = o1->profit - alfa * (o1->profit - o2->profit);
        	//printf("Valor referencia: %.2lf\n", value);
        
        	for (int i = 0; i < arraylist_size(objetosOrd); i++) {
            		o = (Objeto*)arraylist_get(objetosOrd, i);
            		if (o->profit >= value) tamRestrito++;
            		else break;
        	}
        	//printf("Tam restrito: %d\n", tamRestrito);
		
		// Sorteia posicao aleatoria da lista residual
		j = (int)((float)rand()/RAND_MAX * tamRestrito);
        
		// Recupera objeto
		o = (Objeto*)arraylist_get(objetosOrd, j);
		
		// Se objeto ainda nao esta na mochila e cabe nela, adiciona objeto a mochila
		if (s[o->id] != 1 && peso + o->peso <= b) {
			s[o->id] = 1;
			peso += o->peso;
		}
		
		// Remove objeto da lista, pois ja foi testado
		arraylist_remove_index(objetosOrd, j);
	}
}

/******************************************************************************************/
/*				BUSCA LOCAL						  */
/******************************************************************************************/

/* aplica busca local pela estrategia do primeiro aprimorante */
void busca_local_primeiro_aprimorante(int n, int *s, double *p, double *w, double b)
{
	int melhoria = 1;
	double fo_original;
    double fo_vizinho;
    
    fo_original = calcula_fo(s, n, p, w, b);
	
	// Enquanto melhoria
	while (melhoria) {
		melhoria = 0;
				
		for (int j = 0; j < n; j++) {
			
			// cria vizinho
			troca_bit(s, j);
            
            fo_vizinho = calcula_fo(s,n,p,w,b);
			
			// se vizinho > melhor, migra para ele
			if (fo_vizinho > fo_original) {
				melhoria = 1;
                fo_original = fo_vizinho;
				printf("Vizinho melhor! FO = %lf\n", calcula_fo(s,n,p,w,b));
				break;
			}
			else {
				troca_bit(s,j);
			}
		}
	}	
}

/* aplica busca local pela estrategia do melhor aprimorante */
void busca_local_melhor_aprimorante(int n, int *s, double *p, double *w, double b)
{

	printf("\n\n***************** VIZINHANCA N1 *****************\n\n");

	int melhoria = 1;
	double fo_original;
	double fo_max;
    double fo_vizinho;
	int melhor_bit;
    
    fo_original = calcula_fo(s, n, p, w, b);
	
	// Enquanto melhoria
	while (melhoria) {
		melhoria = 0;
		fo_max = -DBL_MAX;
				
		for (int j = 0; j < n; j++) {
			
			// cria vizinho
			troca_bit(s, j);
            
            fo_vizinho = calcula_fo(s,n,p,w,b);
	
			// armazena melhor vizinho
			if (fo_vizinho > fo_max) {
				melhor_bit = j;
                fo_max = fo_vizinho;
           	}
			
			// volta a solucao inicial
			troca_bit(s,j);
		}
		
		// se encontrou algum vizinho melhor
		if (fo_max > fo_original) {
			troca_bit(s,melhor_bit);
			melhoria = 1;
            		fo_original = fo_max;
			printf("Vizinho melhor! FO = %lf\n", fo_max);
		}
	}	
}

/* aplica busca local pela estrategia randomica */
void busca_local_randomica(int n, int *s, double *p, double *w, double b, int iter_max)
{
	int pos;
	double fo_original, fo_vizinho;
	int iter = 0;
    
    fo_original = calcula_fo(s, n, p, w, b);
	
	while (iter < iter_max) {
		
		// incrementa numero de iteracoes
		iter = iter + 1;
		
		// gera vizinho aleatorio
		pos = ((float)rand()/RAND_MAX) * n;
		troca_bit(s,pos);
		
        	// calcula fo vizinho
        	fo_vizinho = calcula_fo(s,n,p,w,b);

		// se vizinho e melhor
		if (fo_vizinho > fo_original) {
			// zera o contador de iteracoes
			iter = 0;
            		fo_original = fo_vizinho;
			printf("Vizinho melhor! FO = %lf\n", fo_vizinho);
		}
		else {
			troca_bit(s,pos);
		}
	}
}

/* aplica busca local pela estrategia do melhor aprimorante */
void busca_local_melhor_aprimorante_N2(int n, int *s, double *p, double *w, double b)
{
	
	printf("\n\n***************** VIZINHANCA N2 *****************\n\n");
	
	int melhoria = 1;
	double fo_original;
	double fo_max, fo_vizinho;
	int melhor_bit_1, melhor_bit_2;

	fo_original = calcula_fo(s, n, p, w, b);
	
	// Enquanto melhoria
	while (melhoria) {
		melhoria = 0;
		fo_max = -DBL_MAX;		
		
		// para cada par de posicoes do vetor
		for (int i = 0; i < n; i++) {

			// troca primeiro bit
			troca_bit(s, i);
			
			for (int j = i+1; j < n; j++) {		
				
				
				// troca segundo bit
				troca_bit(s, j);

				// fo vizinho
				fo_vizinho = calcula_fo(s,n,p,w,b);
				
				// armazena melhor vizinho
				if (fo_vizinho > fo_max) {
					melhor_bit_1 = i;
					melhor_bit_2 = j;
					fo_max = fo_vizinho;
				}
				
				// volta segundo bit
				troca_bit(s,j);
							
			}
			// volta a solucao inicial
			troca_bit(s,i);	
		}
		
		// se encontrou algum vizinho melhor
		if (fo_max > fo_original) {
			troca_bit(s,melhor_bit_1);
			troca_bit(s,melhor_bit_2);			
			melhoria = 1;
			fo_original = fo_max;
			printf("Vizinho melhor! FO = %lf\n", fo_max);
		}
	}
}

/******************************************************************************************/
/*				METAHEURISTICAS						  */
/******************************************************************************************/

/* aplica metaheuristica VND */
void VND(int n, int *s, double *p, double *w, double b)
{
	int k;
	double fo_s;
	
    	k = 1;
	
	while(k <= 2) //while 1
    	{
		// calcula o valor da fo
		fo_s = calcula_fo(s,n,p,w,b);
		
		switch(k){
			case 1: melhor_vizinho_N1(n, s, p, w, b);
				break;
			case 2: melhor_vizinho_N2(n, s, p, w, b);
				break;
			default:
				break;
		}
		if (calcula_fo(s,n,p,w,b) > fo_s)
		{
			k = 1;
		}
		else k++;
    }
}

/* aplica metaheuristica VNS */
void VNS(int n, int *s, double *p, double *w, double b, int iter_max)
{
	int iter = 0;
	int k;
	double fo, fosl;
	int *sl = (int *)malloc(n * sizeof(int));
	
	fo = calcula_fo(s,n,p,w,b);
	
	while (iter < iter_max) {
		k = 1;
		while(k <= 2)
		{
			for (int i = 0; i < n; i++) sl[i] = s[i];
			
			switch(k){ //Gere um vizinho qualquer na vizinhanca corrente
				case 1: vizqqN1(n, sl, p, w, b);
					break;

				case 2: vizqqN2(n, sl, p, w, b);
					break;
			}
			busca_local_melhor_aprimorante(n,sl,p,w,b);
			
			fosl = calcula_fo(sl,n,p,w,b);
			
			if (fosl > fo)
			{
				printf("Vizinho s'' melhor! FO = %lf\n", fosl);
				iter = 0;
				for (int i = 0; i < n; i++) s[i] = sl[i];
				fo = fosl;
				k = 1;
			}
			else k++;
		}
		iter++;
	}
}

/* aplica metaheuristica Multi Start */
void MultiStart(int n, int *s, double *p, double *w, double b, int iter_max)
{
	double fo_star = - DBL_MAX;
	int iter = 0;
	int *s_star = (int *)malloc(n * sizeof(int));
	
	while (iter < iter_max) {
		
		// incrementa contador
		iter++;
		
		// Constroi solucao aleatoria
		constroi_solucao_aleatoria(n,s,p,w,b); 
		
		// Refina solucao
		busca_local_melhor_aprimorante(n, s, p, w, b);

		if(calcula_fo(s,n,p,w,b) > fo_star){
			for (int i = 0; i < n; i++) s_star[i] = s[i];
			fo_star = calcula_fo(s,n,p,w,b);
			iter = 0;
		}
	}
	for (int i = 0; i < n; i++) s[i] = s_star[i];
}

/* aplica metaheuristica ILS */
void ILS(int n, int *s, double *p, double *w, double b, int iter_max)
{
    double pert = 0.3;
    int iter = 0;
    double fo = 0;
    int *s_linha = (int *)malloc(n * sizeof(int));
    
    fo = calcula_fo(s,n,p,w,b);
    
    // Busca Local
    busca_local_melhor_aprimorante(n, s, p, w, b);
    
    // copia
    for (int i = 0; i < n; i++) s_linha[i] = s[i];
    
    while (iter < iter_max) {
        iter++;
        // perturbacao
        perturbacao(n, s_linha, p, w, b, pert);
        // busca local
        busca_local_melhor_aprimorante_N2(n, s_linha, p, w, b);
        // condicao
        if (calcula_fo(s_linha, n, p, w, b) > fo){
            iter = 0;
            fo = calcula_fo(s_linha, n, p, w, b);
            // copia
            for (int i = 0; i < n; i++) s[i] = s_linha[i];
            printf("Melhoria: %lf\n", fo);
        }
    }
}


/* aplica metaheuristica GRASP */
void grasp(int n, int *s, double *p, double *w, double b, int iter_max, double alfa)
{
	int *sl;
	double fo_star = -DBL_MAX;
	
	// cria solucao auxiliar
	sl = (int *) malloc(n * sizeof(int));
	
	// Enquanto melhoria
	for (int i = 0; i < iter_max; i++) {
		
		// Limpa solucao
		for (int j=0; j<n; j++) sl[j] = 0;
		
		// Constroi solucao parcialmente gulosa
		constroi_solucao_grasp(n,sl,p,w,b,alfa);
		printf("solucao construida: %lf\t", calcula_fo(sl,n,p,w,b));
		
		// Aplica busca local na solucao construida
		VND(n,sl,p,w,b);
		printf("solucao refinada: %lf\n", calcula_fo(sl,n,p,w,b));
		
		// Atualiza melhor solucao
		if (calcula_fo(sl,n,p,w,b) > fo_star) {
			
			// copia em s a melhor solucao
			for (int i = 0; i < n; i++) s[i] = sl[i];
			
			// atualiza fo
			fo_star = calcula_fo(sl,n,p,w,b);
		}
	}
}

/* aplica metaheuristica Simulated Annealing */
void SA(int n, int *s, double *p, double *w, double b, double alfa, double temperatura_inicial, double temperatura_final, int SAmax)
{
    double r;              // numero aleatorio entre ZERO e UM
    double temperatura;    // temperatura corrente
    int iter;              // numero de iteracoes na temperatura corrente
    int num_mudancas_temp; // numero de mudancas de temperatura
    int posicao_escolhida; // objeto escolhido
    double delta;             // variacao de energia
    double fo_star, fo, fo_viz;
    int *s_star;
    
	s_star = (int *)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) s_star[i] = s[i];
    
	fo = calcula_fo(s, n, p, w, b);
	fo_star = fo;
    temperatura = temperatura_inicial;
    num_mudancas_temp = 0;
	
	
	/* enquanto o sistema nao congelar faca */
    while (temperatura > temperatura_final) {
		iter = 0;
		/* enquanto o equilibrio termico nao for atingido faca */
		while (iter < SAmax){
			iter++;
			
			/* escolha um vizinho qualquer */
			//posicao_escolhida = ((float)rand()/RAND_MAX) * n;
			//troca_bit(s, posicao_escolhida);
            int p1, p2;
	
            p1 = ((float)rand()/RAND_MAX) * n;
            p2 = ((float)rand()/RAND_MAX) * n;
            while (p1 == p2) p2 = ((float)rand()/RAND_MAX) * n;
	        troca_bit(s, p1);
            troca_bit(s, p2);
			
			/* calcule a variacao de energia */
			fo_viz = calcula_fo(s, n, p, w, b);
			delta = fo_viz - fo;
			
			/* se houver melhora, aceite o vizinho */
			if (delta > 0){
				fo = fo_viz;
				//printf("Solucao de melhora: fo corrente = %.2lf\n",fo);
				
				if (fo > fo_star){
					for (int i = 0; i < n; i++) s_star[i] = s[i];
					fo_star = fo;
					printf("********** fo_star = %.2lf \n",fo_star);
				}
			}
			else {
				/* se houver piora, aceite o vizinho com uma determinada
                 probabilidade */
				r = ((float)rand()/RAND_MAX);
                //printf("delta: %.2lf, prob: %lf\n", delta, exp(delta/temperatura));

                if (r < exp(delta/temperatura)){
                    fo = fo_viz;
					//printf("Solucao de piora: fo corrente = %.2lf\n",fo);
				}
				else {
					/* Se o vizinho nao foi aceito, desfaca o movimento */
					//troca_bit(s, posicao_escolhida);
                    troca_bit(s, p1);
                    troca_bit(s, p2);
				}
			}
        }
		/* decresca a temperatura */
        temperatura *= alfa;
        printf("Temperatura atual = %10.3f\n", temperatura);
        num_mudancas_temp += 1;
    }
	
	/* atualiza melhor solucao */
	for (int i = 0; i < n; i++) s[i] = s_star[i];
}

/* aplica metaheuristica busca tabu */
void BT(int n, int *s, double *p, double *w, double b, double tam, int BTmax)
{
    int tamLT = ceil(tam * n);
    int melhor_posicao, valor_bit = -1;
    double fo_melhor_viz;
    
    int iterBT = 0;  // numero corrente de iteracoes da Busca Tabu
    int melhorIter = 0; // Iteracao em que ocorreu a melhor solucao
    int *s_star;   // vetor que contem a melhor solucao gerada
    double fo_star;   // valor da melhor solucao gerada
    
    // cria sol inicial
    constroi_solucao_aleatoria(n,s,p,w,b);
    
    // cria solucao estrela
    s_star = (int *) malloc(n * sizeof(int));
    fo_star = calcula_fo(s,n,p,w,b);
    
    // Copia melhor solucao para s
    for (int k = 0; k < n; k++){
        s_star[k] = s[k];
    }
    
    // Lista Tabu
    Arraylist LT;
    LT = arraylist_create(NULL);
    
    printf("\nIniciando a Busca Tabu com fo = %.2lf\n", fo_star);
    
    while (iterBT - melhorIter < BTmax) {
        iterBT++;
        
        fo_melhor_viz = melhor_vizinho_BT(n,s,p,w,b,fo_star,&melhor_posicao,&valor_bit,LT);
        
        printf("\nFO do melhor vizinho = %.2lf melhor posicao = %d valor bit = %d\n", fo_melhor_viz, melhor_posicao, valor_bit);
        
        // insere um registro na lista tabu
        if (fo_melhor_viz < calcula_fo(s,n,p,w,b)){
            Elemento* e = (Elemento *)malloc(sizeof(Elemento));
            e->bit = melhor_posicao;
            arraylist_add(LT, e);
        }
        
        // calcula o tamanho da lista tabu e imprime */
        printf("Tamanho da lista tabu = %2d\n", arraylist_size(LT));
   	    imprime_lista_tabu(LT);
        
        // LT tem tamanho maximo tamLT; se a lista tiver mais que essa
        // quantidade de elementos, apagar o primeiro registro da lista
        
        if (arraylist_size(LT) > tamLT){
            // apaga primeiro registro da LT
            arraylist_remove_index(LT, 0);
            printf("novo tamanho da lista tabu = %2d\n", arraylist_size(LT));
            imprime_lista_tabu(LT);
        }
        s[melhor_posicao] = valor_bit;
        
        if (calcula_fo(s,n,p,w,b) > fo_star){
            melhorIter = iterBT;
            // atualiza melhor solucao
            for (int k = 0; k < n; k++){
                s_star[k] = s[k];
            }
            fo_star = calcula_fo(s,n,p,w,b);
            
            printf("\n****** fo_star = %.2lf **********\n",fo_star);  getchar();
        }
        printf("\n------ Iteracoes sem melhora = %d\n",iterBT - melhorIter);
    }
    
    // Copia melhor solucao para s
    for (int k = 0; k < n; k++){
        s[k] = s_star[k];
    }
}

/* aplica metaheuristica AG */
void AG(int n, int *s, double *p, double *w, double b, int nind, int max_geracoes, double prob_crossover, double prob_mutacao)
{
	
	int **pop; // populacao
    double *fo_pop; // funcao objetivo corrente de um dado individuo da populacao
    int **pop_sobrev; // populacao sobrevivente
    double *fo_pop_sobrev; // funcao objetivo corrente de um dado individuo da populacao sobrevivente
    int *s_star;   // vetor que contem a melhor solucao gerada
    double fo_star;   // valor da melhor solucao gerada
	
	// cria solucao estrela
	s_star = (int *) malloc(n * sizeof(int));
    fo_star = -DBL_MAX;
	
	// dobra populacao
    nind = nind * 2;
	
	// cria matriz da populacao
    pop = (int **) malloc(nind*sizeof(int *));
	for (int i=0; i < nind; i++) {
		pop[i] = (int *) malloc(n*sizeof(int));
	}
	
	// cria vetor de fo da populacao
	fo_pop = (double *) malloc(nind * sizeof(double));
	
	// cria matriz da populacao sobrevivente
	pop_sobrev = (int **) malloc(nind/2 *sizeof(int *));
	for (int i=0; i < nind/2; i++) {
		pop_sobrev[i] = (int *) malloc(n*sizeof(int));
	}
	
	// cria vetor de fo da populacao sobrevivente
    fo_pop_sobrev =  (double *) malloc(nind/2 * sizeof(double));
	
	// Geracao da populacao inicial
    for (int j=0; j< nind/2; j++){
		
		// constroi solucoes
		constroi_solucao(n, pop[j], p, w, b, 1);
		
		// calcula fo das solucoes e preenche vetor fo_pop
		fo_pop[j] = calcula_fo(pop[j],n,p,w,b);
		printf("Ind %d: %lf\n", j, fo_pop[j]);
		
        // atualiza melhor solucao
        if (fo_pop[j] > fo_star){
			fo_star = fo_pop[j];
			for (int k = 0; k < n; k++){
				s_star[k] = pop[j][k];
			}
		}
    }
    printf("Melhor individuo da populacao inicial = %lf\n",fo_star);
	
	// Numero de geracoes corrente
	int ngeracoes = 0;
	
	// Enquanto criterio de parada nao satisfeito
    while (ngeracoes < max_geracoes){
		
		ngeracoes++;
		
		// Aplicar crossover
		int quant_filhos = 0;
		while (quant_filhos < nind/2){
			
			// Selecao aleatoria de pais
			int jpai1, jpai2;
			do{
				//jpai1 = ((float)rand()/RAND_MAX) * (nind/2);
				//jpai2 = ((float)rand()/RAND_MAX) * (nind/2);
				jpai1 = roleta(nind/2, fo_pop);
				jpai2 = roleta(nind/2, fo_pop);
			}while (jpai1 == jpai2);
			
			// Probabilidade desse casal de pais reproduzir
			if ((float)rand()/RAND_MAX < prob_crossover){
				int ponto_de_corte = ((float)rand()/RAND_MAX) * n;
				//int ponto_de_corte = n/2;
				
				//printf("ponto_de_corte: %d\n", ponto_de_corte);
				
				// Constroi filhos
				for (int j=0; j<ponto_de_corte; j++){
					pop[quant_filhos+nind/2][j] = pop[jpai1][j];
					pop[quant_filhos+nind/2+1][j] = pop[jpai2][j];
				}
				for (int j=ponto_de_corte; j<n; j++){
					pop[quant_filhos+nind/2][j] = pop[jpai2][j];
					pop[quant_filhos+nind/2+1][j] = pop[jpai1][j];
				}
				quant_filhos+=2;
			}
            else{
                   // copias dos pais
                for (int j=0; j<n; j++){
                    pop[quant_filhos+nind/2][j] = pop[jpai1][j];
                    pop[quant_filhos+nind/2+1][j] = pop[jpai2][j];
                }
            }
		}
		
		// Aplicar mutacao
		for (int j=0; j < nind; j++){
			
			if ((float)rand()/RAND_MAX < prob_mutacao){
				int p1 = ((float)rand()/RAND_MAX) * n;
                int p2 = ((float)rand()/RAND_MAX) * n;
                while (p1 == p2) p2 = ((float)rand()/RAND_MAX) * n;
	            troca_bit(pop[j], p1);
                troca_bit(pop[j], p2);
			}
		}

        double fo_ger = 0;
		
		// Avaliar a populacao inteira (pais e filhos)
		for (int j=0; j<nind; j++){
			
			fo_pop[j] = calcula_fo(pop[j], n, p, w, b);
			//printf("Individuo %d : fo = %lf\n", j, fo_pop[j]);
			
			// Repara inviabilidades
			if (fo_pop[j] < 0) {
				
				int posicao_escolhida;
				int fo = fo_pop[j];
				
				do{
					// Escolhe um objeto que esta na mochila
					do{
						posicao_escolhida = ((float)rand()/RAND_MAX) * n;
					}while (pop[j][posicao_escolhida] == 0);
					
					pop[j][posicao_escolhida] = 0;
					fo = calcula_fo(pop[j], n, p, w, b);
				}while (fo < 0);
				
				fo_pop[j] = fo;
			}
			
			// Atualiza melhor solucao
			if (fo_pop[j] > fo_star){
				fo_star = fo_pop[j];
				for (int k = 0; k < n; k++){
					s_star[k] = pop[j][k];
				}
			}

            if (fo_pop[j] > fo_ger) fo_ger = fo_pop[j];
			
			//printf("Individuo %d : fo = %lf\n", j, fo_pop[j]);
		}
		
		printf("Melhor individuo da geracao %d = %lf\n", ngeracoes, fo_ger);
		
		// Definir a populacao sobrevivente 
		
		for (int j=0; j<nind/2; j++){
			
			// escolha dos individuos sobreviventes pelo mecanismo da roleta
			int individuo_escolhido = roleta(nind, fo_pop);
			//printf("%d Individuo escolhido para proxima geracao = %d\n",j,individuo_escolhido);
			
			for (int i=0; i<n; i++) 
				pop_sobrev[j][i] = pop[individuo_escolhido][i];
			
			fo_pop_sobrev[j] = fo_pop[individuo_escolhido];
			fo_pop[j] = 0;
		}        
		
		// Zerar a populacao e seus dados
		for (int j=0; j<nind; j++){
			fo_pop[j] = 0;
			
			for (int k = 0; k < n; k++) {
				pop[j][k] = 0;
			}
		}
		
		// Copia populacao sobrevivente na primeira metade da matriz de populacao
		for (int j=0; j<nind/2; j++){
			for (int i=0; i<n; i++){
				pop[j][i] = pop_sobrev[j][i];
			}
			fo_pop[j] = fo_pop_sobrev[j];
		}
		
		// Zerar a populacao sobrevivente e seus dados
		for (int j=0; j<nind/2; j++){
			fo_pop_sobrev[j] = 0;
			
			for (int k = 0; k < n; k++) {
				pop_sobrev[j][k] = 0;
			}
		}
	}
	
	// Copia melhor solucao para s
	for (int k = 0; k < n; k++){
		s[k] = s_star[k];
	}
}

/* aplica metaheuristica AC */
void AC(int n, int *s, double *p, double *w, double b, int numF, double Q, double F0, double alfa, double beta, double fator_evap, int iter_max)
{
    int **pop; // populacao
    double *fo_pop; // funcao objetivo corrente de um dado individuo da populacao
    int *s_star;   // vetor que contem a melhor solucao gerada
    double fo_star;   // valor da melhor solucao gerada
    double *feromonio, *deltaF;
    double *probabilidades;
    double *profit;
    double capResidual, sum;
    int iter = 0;
    int *escolhido;
	
	// cria solucao estrela
	s_star = (int *) malloc(n * sizeof(int));
    fo_star = -DBL_MAX;
	
	// cria matriz da populacao
    pop = (int **) malloc(numF*sizeof(int *));
	for (int i=0; i < numF; i++) {
		pop[i] = (int *) malloc(n*sizeof(int));
	}

    // cria vetor de fo da populacao
	fo_pop = (double *) malloc(numF * sizeof(double));

    // cria vetor feromonio
    feromonio = (double *) malloc(n * sizeof(double));
    deltaF = (double *) malloc(n * sizeof(double));

    // cria vetor probabilidades
    probabilidades = (double *) malloc(n * sizeof(double));

    // cria vetor profit
    profit = (double *) malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) profit[i] = p[i]/w[i];

    // objetos escolhidos
    escolhido = (int *) malloc(n * sizeof(int));

    	
    // inicializa todos os objetos com mesma probabilidade
    // TO DO

    // criterio parada
    while (iter < iter_max){

        iter++;

        for (int i = 0; i < n; i++) deltaF[i] = 0;

        // Zerar a populacao e seus dados
	// TO DO

        // para cada formiga
        for (int k = 0; k < numF; k++){

            capResidual = b;
            for (int i = 0; i < n; i++) escolhido[i] = 0;

            // obtenha uma solucao baseado na informacao heuristica e no feromonio
            while(capResidual > 0){  

                

                // calcula probabilidades dos objetos
                // TO DO

                // cria escala para sorteio de objeto
		// TO DO

                // tenta colocar na mochila
                // TO DO

            }
	    // calcula fo
            // TO DO

            // atualiza star
            // TO DO

            // calcula feromonio
            // TO DO
        }
        
        // Atualiza feromonio - rastro e evaporacao
	// TO DO
    }  

    // Copia melhor solucao para s
	for (int k = 0; k < n; k++){
		s[k] = s_star[k];
	} 
}

