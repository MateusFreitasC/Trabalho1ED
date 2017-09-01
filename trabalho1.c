/*	Rodrigo Naves Rios			16/0144094
    Mateus Freitas Cavalcanti	16/0137519
    Estruturas de Dados - Turma C
  	Trabalho 1 -> Calculadora Polonesa */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/* --- Pilha de entrada --- */
typedef struct character{ 
	char dado;
	struct character* prox;
}t_character;

typedef struct pilhac{
	t_character* inicio;
	t_character* fim;
}t_pilhac;
/* ------------------------- */
/* - Pilha de validação () - */
typedef struct validacao{
	char dado;
	struct validacao* prox;
}t_validacao;

typedef struct pilhav{
	t_validacao* inicio;
	t_validacao* fim;
}t_pilhav;
/* ------------------------ */
/* Pilha polonesa */
typedef struct polonesa{
	char dado;
	struct polonesa* prox;
}t_polonesa;

typedef struct pilhap{
	t_polonesa* inicio;
	t_polonesa* fim;
}t_pilhap;
/* ------------------------ */
/* --------------- Funções do programa --------------- */
t_pilhac* cria_pilhac() {
	t_pilhac* pc = (t_pilhac*)malloc(sizeof(t_pilhac));
	pc->inicio = NULL;
	pc->fim = NULL;
	printf("\n -> PILHA DE CHARACTER CRIADA !\n\n");
	return pc;
}
t_pilhav* cria_pilhav() {
	t_pilhav* pv = (t_pilhav*)malloc(sizeof(t_pilhav));
	pv->inicio = NULL;
	pv->fim = NULL;
	printf("\n -> PILHA DE VALIDAÇÃO/CONVERSÃO CRIADA !\n\n");
	return pv;
}

t_pilhap* cria_pilhap() {
	t_pilhap* pp = (t_pilhap*)malloc(sizeof(t_pilhap));
	pp->inicio = NULL;
	pp->fim = NULL;
	printf("\n -> PILHA POLONESA CRIADA !\n\n");
	return pp;
}

void empilha_pc(char digito, t_pilhac* pc) {
	t_character* novo = (t_character*)malloc(sizeof(t_character));
	novo->dado = digito;
	novo->prox = NULL;
	if(pc->inicio == NULL) {	/* se lista vazia => o novofim ja vai ser o primeiro */
		pc->inicio = novo;
	}
	else {						/* se não, fim aponta pro novofim */
		pc->fim->prox = novo;
	}
	pc->fim = novo;
}
void empilha_pv(char digito, t_pilhav* pv) {
	t_validacao* novo = (t_validacao*)malloc(sizeof(t_validacao));
	novo->dado = digito;
	novo->prox = NULL;
	if(pv->inicio == NULL) {	/* se lista vazia => o novofim ja vai ser o primeiro */
		pv->inicio = novo;
	}
	else {						/* se não, fim aponta pro novofim */
		pv->fim->prox = novo;
	}
	pv->fim = novo;
}

void empilha_pp(char digito, t_pilhap* pp) {
	t_polonesa* novo = (t_polonesa*)malloc(sizeof(t_polonesa));
	novo->dado = digito;
	novo->prox = NULL;
	if(pp->inicio == NULL) {	/* se lista vazia => o novofim ja vai ser o primeiro */
		pp->inicio = novo;
	}
	else {						/* se não, fim aponta pro novofim */
		pp->fim->prox = novo;
	}
	pp->fim = novo;
}

void mostra_pilhac(t_pilhac* pc) {
	t_character* aux = pc->inicio;
	printf("\n -> Pilha de character\t: ");
	while(aux != NULL) {						/* Percorre a lista e mostra cada elemento */
		printf("%c", aux->dado);
		aux = aux->prox;
	}
	printf("\n");
}

void mostra_pilhap(t_pilhap* pp) {
	t_polonesa* aux = pp->inicio;
	printf("\n -> Pilha polonesa\t: ");
	while(aux != NULL) {						/* Percorre a lista e mostra cada elemento */
		printf("%c", aux->dado);
		aux = aux->prox;
	}
	printf("\n\n");
}

char desempilha_pc(t_pilhac* pc) {
	if(pc->inicio == NULL) {
		return -1; /* PILHA VAZIA */
	}
	int removido = pc->fim->dado;
	t_character* ultimo = pc->inicio;
	t_character* penultimo = NULL;
	while(ultimo->prox != NULL) { 	/* percorre pilha até encontrar o penúltimo elemento */
		penultimo = ultimo;
		ultimo = ultimo->prox;
	}
	if(penultimo == NULL){ 			/* se ultimo e penultimo não andaram => pilha vazia */
       pc->inicio = NULL;
       pc->fim = NULL;
    }
    else {							/* se não, penultimo vira o último */
		penultimo->prox = NULL;
		pc->fim = penultimo;
	}
	free(ultimo);
	return removido;
}

char desempilha_pv(t_pilhav* pv) {
	if(pv->inicio == NULL) {
		return -1; /* PILHA VAZIA */
	}
	int removido = pv->fim->dado;
	t_validacao* ultimo = pv->inicio;
	t_validacao* penultimo = NULL;
	while(ultimo->prox != NULL) { 	/* percorre pilha até encontrar o penúltimo elemento */
		penultimo = ultimo;
		ultimo = ultimo->prox;
	}
	if(penultimo == NULL){ 			/* se ultimo e penultimo não andaram => pilha vazia */
       pv->inicio = NULL;
       pv->fim = NULL;
    }
    else {							/* se não, penultimo vira o último */
		penultimo->prox = NULL;
		pv->fim = penultimo;
	}
	free(ultimo);
	return removido;
}

int valida_pc(t_pilhac* pc, t_pilhav* pv) { /* valida a pilha dos caracteres em relação aos ()	 */
	t_character* olho = pc->inicio;
	if(olho == NULL) return 0;
	char c, comp;
	while(olho != NULL) {
		c = olho->dado;
		if(c == '(') empilha_pv(c,pv);
		if(c == ')') {
			if(pv->inicio == NULL) {
				return -1;
			} else {
				comp = desempilha_pv(pv);
				if(comp == c) return -1;
			}
		}
		olho = olho->prox;
	}
	if(pv->inicio != NULL) {
		return -1;
	} else {
		return 1; 
	}
}

void converte(t_pilhac* pc, t_pilhap* pp, t_pilhav* pv) { /* Converte da forma infixa (PILHAc) para a forma posfixa (PILHAp) */
	t_character* olho = pc->inicio;
	char c, comp;
	while(olho != NULL) {
		c = olho->dado;
		if(c =='+' || c =='-' || c =='*' || c =='/') {
			while(pv->inicio != NULL && ((pv->fim->dado == '*' && (c == '+' || c== '-')) || (pv->fim->dado == '/' && (c == '+' || c== '-')) || (pv->fim->dado == '*' && (c == '/' || c == '*')) || (pv->fim->dado == '/' && (c == '/' || c == '*')) || (pv->fim->dado == '+' && (c == '+' || c == '-')) || (pv->fim->dado == '-' && (c == '+' || c == '-')))) {
				comp = desempilha_pv(pv);
				empilha_pp(comp,pp);
			}
			empilha_pv(c,pv);
		} else {
			if(c == '(' || c == ')') {
				if(c == '(') {
					empilha_pv(c,pv);
				}
				if(c == ')') {
					while(pv->fim->dado != '(') {
						comp = desempilha_pv(pv);
						empilha_pp(comp,pp);
					}
					desempilha_pv(pv);
				}
			} else {
				empilha_pp(c,pp);
			}
		}
	olho = olho->prox;
	}
	while(pv->fim != NULL) {
		c = desempilha_pv(pv);
		empilha_pp(c,pp);
	}
}
/* ---------------------------------------- */
int main() {
int valid;
char digito;
t_pilhac* pc = cria_pilhac();
t_pilhav* pv = cria_pilhav();
t_pilhap* pp = cria_pilhap();
while(1) {
	printf("\e[H\e[2J");
	printf("\n\n\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("\t\t\t[   CALCULADORA POLONESA   ]\n");
	printf("\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("\n -> Expressão que deseja Calcular : ");
	while(scanf("%c", &digito)==1 && digito!='\n') {
		empilha_pc(digito,pc);
	}
	mostra_pilhac(pc);
	valid = valida_pc(pc,pv);
	if(valid == -1 || valid == 0) {
		printf("\n -> EXPRESSÃO INVÁLIDA !\n");
		sleep(3);
	} else {
		converte(pc,pp,pv);
		mostra_pilhap(pp);
	}
	break;
	printf("\n aperte ENTER para calcular outra expressão\n");
	getchar();
}
return 0;
}
