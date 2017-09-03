/*	Rodrigo Naves Rios			16/0144094
    Mateus Freitas Cavalcanti	16/0137519
    Estruturas de Dados - Turma C
  	Trabalho 1 -> Calculadora Polonesa */

#include <stdio.h>
#include <stdlib.h>

/* --- Pilha de character --- */
typedef struct character{ 
	char dado;
	struct character* prox;
}t_character;

typedef struct pilhachar{
	t_character* inicio;
	t_character* fim;
}t_pilhachar;
/* -------------------------- */
/* ---- Pilha de numero ---- */
typedef struct numero{ 
	float dado;
	struct numero* prox;
}t_numero;

typedef struct pilhaint{
	t_numero* inicio;
	t_numero* fim;
}t_pilhaint;
/* -------------------------- */
/* --------------- Funções do programa --------------- */
t_pilhachar* cria_pilhachar() {
	t_pilhachar* p = (t_pilhachar*)malloc(sizeof(t_pilhachar));
	p->inicio = NULL;
	p->fim = NULL;
	printf("\n -> PILHA DE CHARACTER CRIADA !\n\n");
	return p;
}

t_pilhaint* cria_pilhaint() {
	t_pilhaint* p = (t_pilhaint*)malloc(sizeof(t_pilhaint));
	p->inicio = NULL;
	p->fim = NULL;
	printf("\n -> PILHA DE INTEIRO CRIADA !\n\n");
	return p;
}

void empilhachar(char digito, t_pilhachar* p) {
	t_character* novo = (t_character*)malloc(sizeof(t_character));
	novo->dado = digito;
	novo->prox = NULL;
	if(p->inicio == NULL) {		/* se lista vazia => o novofim ja vai ser o primeiro */
		p->inicio = novo;
	}
	else {						/* se não, fim aponta pro novofim */
		p->fim->prox = novo;
	}
	p->fim = novo;
}

void empilhanum(int digito, t_pilhaint* p) {
	t_numero* novo = (t_numero*)malloc(sizeof(t_numero));
	novo->dado = digito;
	novo->prox = NULL;
	if(p->inicio == NULL) {		/* se lista vazia => o novofim ja vai ser o primeiro */
		p->inicio = novo;
	}
	else {						/* se não, fim aponta pro novofim */
		p->fim->prox = novo;
	}
	p->fim = novo;
}

void mostra_pilha(t_pilhachar* p) {
	t_character* aux = p->inicio;
	while(aux != NULL) {						/* Percorre a lista e mostra cada elemento */
		printf("%c", aux->dado);
		aux = aux->prox;
	}
}

char desempilhachar(t_pilhachar* p) {
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

char desempilhanum(t_pilhaint* p) {
	if(p->inicio == NULL) {
		return -1; /* PILHA VAZIA */
	}
	int removido = p->fim->dado;
	t_numero* ultimo = p->inicio;
	t_numero* penultimo = NULL;
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

void esvaziachar(t_pilhachar* p) {
	while(p->fim != NULL) {
		desempilhachar(p);
	}
}

int valida(t_pilhachar* pc, t_pilhachar* pv) { /* valida a pilha dos caracteres em relação aos ()	 */
	t_character* olho = pc->inicio;
	if(olho == NULL) return 0;
	char c, comp;
	while(olho != NULL) {
		c = olho->dado;
		if(c == '(') empilhachar(c,pv);
		if(c == ')') {
			if(pv->inicio == NULL) {
				return -1;
			} else {
				comp = desempilhachar(pv);
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

void converte(t_pilhachar* pc, t_pilhachar* pp, t_pilhachar* pv) { /* Converte da forma infixa (PILHAc) para a forma posfixa (PILHAp) */
	t_character* olho = pc->inicio;
	char c, comp;
	while(olho != NULL) {
		c = olho->dado;
		if(c =='+' || c =='-' || c =='*' || c =='/') {
			while(pv->inicio != NULL && ((pv->fim->dado == '*' && (c == '+' || c== '-')) || (pv->fim->dado == '/' && (c == '+' || c== '-')) || (pv->fim->dado == '*' && (c == '/' || c == '*')) || (pv->fim->dado == '/' && (c == '/' || c == '*')) || (pv->fim->dado == '+' && (c == '+' || c == '-')) || (pv->fim->dado == '-' && (c == '+' || c == '-')))) {
				comp = desempilhachar(pv);
				empilhachar(comp,pp);
			}
			empilhachar(c,pv);
		} else {
			if(c == '(' || c == ')') {
				if(c == '(') {
					empilhachar(c,pv);
				}
				if(c == ')') {
					while(pv->fim->dado != '(') {
						comp = desempilhachar(pv);
						empilhachar(comp,pp);
					}
					desempilhachar(pv);
				}
			} else {
				empilhachar(c,pp);
			}
		}
		olho = olho->prox;
	}
	while(pv->fim != NULL) {
		c = desempilhachar(pv);
		empilhachar(c,pp);
	}
}

float calcula_posfixa(t_pilhachar* pp, t_pilhaint* pi) {
	t_character* olho = pp->inicio;
	char c;
	float a,b;
	while(olho != NULL) {
		c = olho->dado;
		if(c == '0'  || c == '1'  || c == '2'  || c == '3'  || c == '4'  || c == '5'  || c == '6'  || c == '7'  || c == '8'  || c == '9') {
			if(c == '0') {
				empilhanum(0,pi);
			}
			if(c == '1') {
				empilhanum(1,pi);
			}
			if(c == '2') {
				empilhanum(2,pi);
			}
			if(c == '3') {
				empilhanum(3,pi);
			}
			if(c == '4') {
				empilhanum(4,pi);
			}
			if(c == '5') {
				empilhanum(5,pi);
			}
			if(c == '6') {
				empilhanum(6,pi);
			}
			if(c == '7') {
				empilhanum(7,pi);
			}
			if(c == '8') {
				empilhanum(8,pi);
			}
			if(c == '9') {
				empilhanum(9,pi);
			}
		} else {
			if(c == '+') {
				b = desempilhanum(pi);
				a = desempilhanum(pi);
				empilhanum(a+b,pi);
			}
			if(c == '-') {
				b = desempilhanum(pi);
				a = desempilhanum(pi);
				empilhanum(a-b,pi);
			}
			if(c == '/') {
				b = desempilhanum(pi);
				a = desempilhanum(pi);
				empilhanum(a/b,pi);
			}
			if(c == '*') {
				b = desempilhanum(pi);
				a = desempilhanum(pi);
				empilhanum(a*b,pi);
			}
		}
		olho = olho->prox;
	}
	return desempilhanum(pi);
}
/* ---------------------------------------- */
int main() {
int valid;
char digito;
t_pilhachar* pc = cria_pilhachar();
t_pilhachar* pv = cria_pilhachar();
t_pilhachar* pp = cria_pilhachar();
t_pilhaint* pi = cria_pilhaint();

while(1) {
	printf("\e[H\e[2J");
	printf("\n\n\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("\t\t\t[   CALCULADORA POLONESA   ]\n");
	printf("\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("\n -> Expressão que deseja Calcular : ");
	while(scanf("%c", &digito)==1 && digito!='\n') {
		empilhachar(digito,pc);
	}
	printf("\n -> Pilha de entrada\t: ");
	mostra_pilha(pc);
	valid = valida(pc,pv);
	if(valid == -1 || valid == 0) {
		printf("   <- EXPRESSÃO INVÁLIDA !\n");
	} else {
		printf("   <- EXPRESSÃO VÁLIDA !\n");
		converte(pc,pp,pv);
		printf("\n -> Pilha polonesa\t: ");
		mostra_pilha(pp);
		printf("\n\n -> Expressão posfixa calculada = %.2f\n", calcula_posfixa(pp,pi));
	}
	printf("\n aperte ENTER para calcular outra expressão\n");
	getchar();
	esvaziachar(pc);
	if(valid == -1 || valid == 0) {
		esvaziachar(pv);
	}
	esvaziachar(pp);
}
return 0;
}
