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

typedef struct pilhaf{
	t_numero* inicio;
	t_numero* fim;
}t_pilhaf;
/* -------------------------- */
/* --------------- Funções do programa --------------- */
t_pilhachar* cria_pilhachar() {
	t_pilhachar* p = (t_pilhachar*)malloc(sizeof(t_pilhachar));
	p->inicio = NULL;
	p->fim = NULL;
	printf("\n -> PILHA DE CHARACTER CRIADA !\n\n");
	return p;
}

t_pilhaf* cria_pilhaint() {
	t_pilhaf* p = (t_pilhaf*)malloc(sizeof(t_pilhaf));
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

void empilhanum(float digito, t_pilhaf* p) {
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

void mostra_pilhachar(t_pilhachar* p) {
	t_character* aux = p->inicio;
	while(aux != NULL) {						/* Percorre a lista e mostra cada elemento */
		printf("%c", aux->dado);
		aux = aux->prox;
	}
}

void mostra_pilhanum(t_pilhaf* p) {
	int count = 0;
	t_numero* aux = p->inicio;
	while(aux != NULL) {						/* Percorre a lista e mostra cada elemento */
		printf("%.2f ", aux->dado);
		aux = aux->prox;
		count ++;
	}
	printf(" <- %d elementos", count);
	printf("\n");
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

float desempilhanum(t_pilhaf* p) {
	if(p->inicio == NULL) {
		return -1; /* PILHA VAZIA */
	}
	float removido = p->fim->dado;
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

void insere_0(t_character* antes0, t_character* depois0) {
	t_character* zero = (t_character*)malloc(sizeof(t_character));
	zero->dado = '0';
	antes0->prox = zero;
	zero->prox = depois0;
}

int valida_oper(t_pilhachar* pi) {
	t_character* atual = pi->inicio;
	t_character* antes = NULL;
	while(atual != NULL) {
		if(atual->dado != '0' && atual->dado != '1' && atual->dado != '2' && atual->dado != '3' && atual->dado != '4' && atual->dado != '5' && atual->dado != '6' && atual->dado != '7' && atual->dado != '8' && atual->dado != '9' && atual->dado != '+' && atual->dado != '-' && atual->dado != '*' && atual->dado != '/' && atual->dado != '(' && atual->dado != ')') {
			return 0;	
		}
		if(pi->inicio->dado == '*' || pi->inicio->dado == '/' || pi->inicio->dado == '+' || pi->inicio->dado == '-' || pi->fim->dado == '+' || pi->fim->dado == '-' || pi->fim->dado == '*' || pi->fim->dado == '/') {
			return 0;
		}
		if(antes != NULL && ((antes->dado >= '0' && antes->dado <='9' && atual->dado == '(') || (antes->dado == ')' && atual->dado >='0' && atual->dado <= '9'))) {
			return 0;
		}
		if(antes != NULL && (((antes->dado == '*' || antes->dado == '/' || antes->dado == '+' || antes->dado == '-') && atual->dado == ')') || (antes->dado == '(' && (atual->dado == '*' || atual->dado == '/'	)))) {
			return 0;
		}
		if(antes != NULL && ((antes->dado == '*' && (atual->dado == '*' || atual->dado == '/')) || (antes->dado == '/' && (atual->dado == '*' || atual->dado == '/')) || (antes->dado == '+' && (atual->dado == '+' || atual->dado == '-')) || (antes->dado == '-' && (atual->dado == '+' || atual->dado == '-')))) {
			return 0;
		}
		if(antes != NULL && (antes->dado == '(' && (atual->dado == '+' || atual->dado == '-'))) {
			insere_0(antes,atual);
		}
		antes = atual;
		atual = atual->prox;
	}
	return 1;
}

int valida_parent(t_pilhachar* pi, t_pilhachar* paux) { /* valida a pilha dos caracteres em relação aos ()	e verifica a existência de números com 2 ou mais dígitos */
	t_character* olho = pi->inicio;
	if(olho == NULL) return 0;
	char c, comp;
	while(olho != NULL) {
		c = olho->dado;
		if(c == '(') empilhachar(c,paux);
		if(c == ')') {
			if(paux->inicio == NULL) {
				return 0;
			} else {
				comp = desempilhachar(paux);
				if(comp == c) return 0;
			}
		}
		olho = olho->prox;
	}
	if(paux->inicio != NULL) {
		return 0;
	} else {
		return 1; 
	}
}

int valida_digito(t_pilhachar* pi, t_pilhachar* paux) {
	t_character* olho = pi->inicio;
	char atual, proximo;
	while(olho->prox != NULL) {
		atual = olho->dado;
		proximo = olho->prox->dado;
		if((atual >= '0' && atual <= '9') && (proximo >= '0' && proximo <= '9')) {
			return 0;
		}
		olho = olho->prox;
	}
	return 1;
}

void converte_1_dig(t_pilhachar* pi, t_pilhachar* pp, t_pilhachar* paux) {
	t_character* olho = pi->inicio;
	char c, comp;
	while(olho != NULL) {
		c = olho->dado;
		if(c =='+' || c =='-' || c =='*' || c =='/') {
			while(paux->inicio != NULL && ((paux->fim->dado == '*' && (c == '+' || c== '-')) || (paux->fim->dado == '/' && (c == '+' || c== '-')) || (paux->fim->dado == '*' && (c == '/' || c == '*')) || (paux->fim->dado == '/' && (c == '/' || c == '*')) || (paux->fim->dado == '+' && (c == '+' || c == '-')) || (paux->fim->dado == '-' && (c == '+' || c == '-')))) {
				comp = desempilhachar(paux);
				empilhachar(comp,pp);
			}
			empilhachar(c,paux);
		} else {
			if(c == '(' || c == ')') {
				if(c == '(') {
					empilhachar(c,paux);
				}
				if(c == ')') {
					while(paux->fim->dado != '(') {
						comp = desempilhachar(paux);
						empilhachar(comp,pp);
					}
					desempilhachar(paux);
				}
			} else {
				empilhachar(c,pp);
			}
		}
		olho = olho->prox;
	}
	while(paux->fim != NULL) {
		c = desempilhachar(paux);
		empilhachar(c,pp);
	}
}

void converte_maisdig(t_pilhachar* pi, t_pilhachar* pp, t_pilhachar* paux) {
	t_character* olho = pi->inicio;
	char atual, proximo, comp;
	while(olho != NULL) {
		if(olho->prox == NULL) {
			atual = olho->dado;
		} else {
			atual = olho->dado;
			proximo = olho->prox->dado;
		}
		if(atual >= '0' && atual <= '9') {
			empilhachar('{',pp);
			empilhachar(atual,pp);
			while(olho->prox != NULL && proximo >= '0' && proximo <= '9') {
				olho = olho->prox;
				atual = olho->dado;
				if(olho->prox != NULL) proximo = olho->prox->dado;
				empilhachar(atual,pp);
			}
			empilhachar('}',pp);
		} else {
			if(atual =='+' || atual =='-' || atual =='*' || atual =='/') {
			while(paux->inicio != NULL && ((paux->fim->dado == '*' && (atual == '+' || atual== '-')) || (paux->fim->dado == '/' && (atual == '+' || atual== '-')) || (paux->fim->dado == '*' && (atual == '/' || atual == '*')) || (paux->fim->dado == '/' && (atual == '/' || atual == '*')) || (paux->fim->dado == '+' && (atual == '+' || atual == '-')) || (paux->fim->dado == '-' && (atual == '+' || atual == '-')))) {
				comp = desempilhachar(paux);
				empilhachar(comp,pp);
			}
			empilhachar(atual,paux);
			} else {
				if(atual == '(') {
					empilhachar(atual,paux);
				}
				if(atual == ')') {
					while(paux->fim->dado != '(') {
						comp = desempilhachar(paux);
						empilhachar(comp,pp);
					}
					desempilhachar(paux);
				}
			}
		}
		olho = olho->prox;
	}
	while(paux->fim != NULL) {
		atual = desempilhachar(paux);
		empilhachar(atual,pp);
	}
}

float calcula_posfixa(int valid, t_pilhachar* pp, t_pilhaf* pnum) {
	t_character* olho = pp->inicio;
	char atual;
	float conv,a,b;
	while(olho != NULL) {
		atual = olho->dado;
		if(atual >= '0' && atual <= '9' && valid == 1) {
			empilhanum(atual-'0',pnum);
		} else {
			if(atual == '{' && valid == 0) {
				conv = 0;
				olho = olho->prox;
				atual = olho->dado;
				conv += atual - '0';
				olho = olho->prox;
				atual = olho->dado;
				while(atual != '}') {
					conv *= 10;
					conv += atual - '0';
					olho = olho->prox;
					atual = olho->dado;
				}
				empilhanum(conv,pnum);
			} else {
				if(atual == '+') {
				b = desempilhanum(pnum);
				a = desempilhanum(pnum);
				empilhanum(a+b,pnum);
			}
			if(atual == '-') {
				b = desempilhanum(pnum);
				a = desempilhanum(pnum);
				empilhanum(a-b,pnum);
			}
			if(atual == '/') {
				b = desempilhanum(pnum);
				a = desempilhanum(pnum);
				empilhanum(a/b,pnum);
			}
			if(atual == '*') {
				b = desempilhanum(pnum);
				a = desempilhanum(pnum);
				empilhanum(a*b,pnum);
			}
			}
		}
		mostra_pilhanum(pnum);
		olho = olho->prox;
	}
	return desempilhanum(pnum);
}
/* ---------------------------------------- */
int main() {
int valid_parent, valid_oper, valid_digito;
char digito;
t_pilhachar* pi = cria_pilhachar();
t_pilhachar* paux = cria_pilhachar();
t_pilhachar* pp = cria_pilhachar();
t_pilhaf* pnum = cria_pilhaint();

while(1) {
	printf("\e[H\e[2J");
	printf("\n\n\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("\t\t\t[   CALCULADORA POLONESA   ]\n");
	printf("\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("\n -> Expressão que deseja Calcular : ");
	while(scanf("%c", &digito)==1 && digito!='\n') {
		empilhachar(digito,pi);
	}
	printf("\n -> Pilha de entrada\t: ");
	mostra_pilhachar(pi);
	valid_oper = valida_oper(pi);
	valid_parent = valida_parent(pi,paux);
	if(valid_parent == 0 || valid_oper == 0) {
		printf("   <- EXPRESSÃO INVÁLIDA !\n");
	} else {
		printf("   <- EXPRESSÃO VÁLIDA !\n");
		valid_digito = valida_digito(pi,paux);
		if(valid_digito == 0) {					/* Expressão com pelo menos um número de 2 ou mais dígitos */
		converte_maisdig(pi,pp,paux);
		} else {								/* Expressão com números de 1 dígito */
		converte_1_dig(pi,pp,paux);
		}
		printf("\n -> Pilha polonesa\t: ");
		mostra_pilhachar(pp);
		printf("\n");
		printf("\n\n -> Expressão posfixa calculada = %.2f\n", calcula_posfixa(valid_digito,pp,pnum));
	}
	printf("\n aperte ENTER para calcular outra expressão\n");
	getchar();
	esvaziachar(pi);
	if(valid_parent == 0) {
		esvaziachar(paux);
	}
	esvaziachar(pp);
}
return 0;
}
