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

typedef struct pilha{
	t_character* inicio;
	t_character* fim;
}t_pilha;
/* ------------------------- */
/* --------------- Funções do programa --------------- */
t_pilha* cria_pilha() {
	t_pilha* p = (t_pilha*)malloc(sizeof(t_pilha));
	p->inicio = NULL;
	p->fim = NULL;
	printf("\n -> PILHA DE CHARACTER CRIADA !\n\n");
	return p;
}

void empilha(char digito, t_pilha* p) {
	t_character* novo = (t_character*)malloc(sizeof(t_character));
	novo->dado = digito;
	novo->prox = NULL;
	if(p->inicio == NULL) {	/* se lista vazia => o novofim ja vai ser o primeiro */
		p->inicio = novo;
	}
	else {						/* se não, fim aponta pro novofim */
		p->fim->prox = novo;
	}
	p->fim = novo;
}

void mostra_pilha(t_pilha* p) {
	t_character* aux = p->inicio;
	printf("\n -> Pilha polonesa\t: ");
	while(aux != NULL) {						/* Percorre a lista e mostra cada elemento */
		printf("%c", aux->dado);
		aux = aux->prox;
	}
	printf("\n\n");
}

char desempilha(t_pilha* p) {
	if(p->inicio == NULL) {
		return -1; /* PILHA VAZIA */
	}
	int removido = p->fim->dado;
	t_character* ultimo = p->inicio;
	t_character* penultimo = NULL;
	while(ultimo->prox != NULL) { 	/* percorre pilha até encontrar o penúltimo elemento */
		penultimo = ultimo;
		ultimo = ultimo->prox;
	}
	if(penultimo == NULL){ 			/* se ultimo e penultimo não andaram => pilha vazia */
       p->inicio = NULL;
       p->fim = NULL;
    }
    else {							/* se não, penultimo vira o último */
		penultimo->prox = NULL;
		p->fim = penultimo;
	}
	free(ultimo);
	return removido;
}

int valida(t_pilha* pc, t_pilha* pv) { /* valida a pilha dos caracteres em relação aos ()	 */
	t_character* olho = pc->inicio;
	if(olho == NULL) return 0;
	char c, comp;
	while(olho != NULL) {
		c = olho->dado;
		if(c == '(') empilha(c,pv);
		if(c == ')') {
			if(pv->inicio == NULL) {
				return -1;
			} else {
				comp = desempilha(pv);
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

void converte(t_pilha* pc, t_pilha* pp, t_pilha* pv) { /* Converte da forma infixa (PILHAc) para a forma posfixa (PILHAp) */
	t_character* olho = pc->inicio;
	char c, comp;
	while(olho != NULL) {
		c = olho->dado;
		if(c =='+' || c =='-' || c =='*' || c =='/') {
			while(pv->inicio != NULL && ((pv->fim->dado == '*' && (c == '+' || c== '-')) || (pv->fim->dado == '/' && (c == '+' || c== '-')) || (pv->fim->dado == '*' && (c == '/' || c == '*')) || (pv->fim->dado == '/' && (c == '/' || c == '*')) || (pv->fim->dado == '+' && (c == '+' || c == '-')) || (pv->fim->dado == '-' && (c == '+' || c == '-')))) {
				comp = desempilha(pv);
				empilha(comp,pp);
			}
			empilha(c,pv);
		} else {
			if(c == '(' || c == ')') {
				if(c == '(') {
					empilha(c,pv);
				}
				if(c == ')') {
					while(pv->fim->dado != '(') {
						comp = desempilha(pv);
						empilha(comp,pp);
					}
					desempilha(pv);
				}
			} else {
				empilha(c,pp);
			}
		}
	olho = olho->prox;
	}
	while(pv->fim != NULL) {
		c = desempilha(pv);
		empilha(c,pp);
	}
}
/* ---------------------------------------- */
int main() {
int valid;
char digito;
t_pilha* pc = cria_pilha();
t_pilha* pv = cria_pilha();
t_pilha* pp = cria_pilha();
while(1) {
	printf("\e[H\e[2J");
	printf("\n\n\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("\t\t\t[   CALCULADORA POLONESA   ]\n");
	printf("\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("\n -> Expressão que deseja Calcular : ");
	while(scanf("%c", &digito)==1 && digito!='\n') {
		empilha(digito,pc);
	}
	mostra_pilha(pc);
	valid = valida(pc,pv);
	if(valid == -1 || valid == 0) {
		printf("\n -> EXPRESSÃO INVÁLIDA !\n");
		sleep(3);
	} else {
		converte(pc,pp,pv);
		mostra_pilha(pp);
	}
	break;
	printf("\n aperte ENTER para calcular outra expressão\n");
	getchar();
}
return 0;
}
