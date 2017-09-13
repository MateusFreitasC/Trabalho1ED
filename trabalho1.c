/*	Rodrigo Naves Rios			16/0144094
    Mateus Freitas Cavalcanti	16/0137519
    Estruturas de Dados - Turma C
  	Trabalho 1 -> Calculadora Polonesa */

#include <stdio.h>
#include <stdlib.h>

typedef struct character{ 
	char dado;
	struct character* prox;
}t_character;
/* ---- Pilha de character ---- */
typedef struct pilhachar{
	t_character* inicio;
	t_character* fim;
}t_pilhachar;
/* ---- Lista de character ---- */
typedef struct listachar{
	t_character* inicio;
	t_character* fim;
}t_listachar;
/* ---------------------------- */
typedef struct numero{ 
	float dado;
	struct numero* prox;
}t_numero;
/* ------ Pilha de numero ----- */
typedef struct pilhaf{
	t_numero* inicio;
	t_numero* fim;
}t_pilhaf;
/* ----------------------------- */
/* --------------- Funções do programa --------------- */
t_listachar* cria_listachar() {
	t_listachar* l = (t_listachar*)malloc(sizeof(t_listachar));
	l->inicio = NULL;
	l->fim = NULL;
	printf("\n -> LISTA DE CHARACTER CRIADA !\n\n");
	return l;
}


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

void empilha_lista_char(char digito, t_listachar* l) {
	t_character* novo = (t_character*)malloc(sizeof(t_character));
	novo->dado = digito;
	novo->prox = NULL;
	if(l->inicio == NULL) {		/* se lista vazia => o novofim ja vai ser o primeiro */
		l->inicio = novo;
	}
	else {						/* se não, fim aponta pro novofim */
		l->fim->prox = novo;
	}
	l->fim = novo;
}

void empilha_pilha_char(char digito, t_pilhachar* p) {
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

void empilha_pilha_num(float digito, t_pilhaf* p) {
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

void mostra_listachar(t_listachar* l) {
	t_character* aux = l->inicio;
	while(aux != NULL) {						/* Percorre a lista e mostra cada elemento */
		printf("%c", aux->dado);
		aux = aux->prox;
	}
}

char desempilha_lista_char(t_listachar* l) {
	if(l->inicio == NULL) {
		return -1; /* PILHA VAZIA */
	}
	int removido = l->fim->dado;
	t_character* ultimo = l->inicio;
	t_character* penultimo = NULL;
	while(ultimo->prox != NULL) { 	/* percorre pilha até encontrar o penúltimo elemento */
		penultimo = ultimo;
		ultimo = ultimo->prox;
	}
	if(penultimo == NULL){ 			/* se ultimo e penultimo não andaram => pilha vazia */
       l->inicio = NULL;
       l->fim = NULL;
    }
    else {							/* se não, penultimo vira o último */
		penultimo->prox = NULL;
		l->fim = penultimo;
	}
	free(ultimo);
	return removido;
}

char desempilha_pilha_char(t_pilhachar* p) {
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

float desempilha_pilha_num(t_pilhaf* p) {
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

void esvazia_pilha(t_pilhachar* p) {
	while(p->fim != NULL) {
		desempilha_pilha_char(p);
	}
}

void esvazia_lista(t_listachar* l) {
	while(l->fim != NULL) {
		desempilha_lista_char(l);
	}
}

void insere_0(t_character* antes0, t_character* depois0) {
	t_character* zero = (t_character*)malloc(sizeof(t_character));
	zero->dado = '0';
	antes0->prox = zero;
	zero->prox = depois0;
}

int valida_oper(t_listachar* l_inf) {
	t_character* atual = l_inf->inicio;
	t_character* antes = NULL;
	while(atual != NULL) {
		if(atual->dado != '0' && atual->dado != '1' && atual->dado != '2' && atual->dado != '3' && atual->dado != '4' && atual->dado != '5' && atual->dado != '6' && atual->dado != '7' && atual->dado != '8' && atual->dado != '9' && atual->dado != '+' && atual->dado != '-' && atual->dado != '*' && atual->dado != '/' && atual->dado != '(' && atual->dado != ')') {
			return 0;	
		}
		if(l_inf->inicio->dado == '*' || l_inf->inicio->dado == '/' || l_inf->inicio->dado == '+' || l_inf->inicio->dado == '-' || l_inf->fim->dado == '+' || l_inf->fim->dado == '-' || l_inf->fim->dado == '*' || l_inf->fim->dado == '/') {
			return 0;
		}
		if(antes != NULL && antes->dado == '/' && atual->dado == '0') {
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

int valida_parent(t_listachar* l_inf, t_pilhachar* p_aux) { /* valida a pilha dos caracteres em relação aos ()	e verifica a existência de números com 2 ou mais dígitos */
	t_character* olho = l_inf->inicio;
	if(olho == NULL) return 0;
	char c, comp;
	while(olho != NULL) {
		c = olho->dado;
		if(c == '(') empilha_pilha_char(c,p_aux);
		if(c == ')') {
			if(p_aux->inicio == NULL) {
				return 0;
			} else {
				comp = desempilha_pilha_char(p_aux);
				if(comp == c) return 0;
			}
		}
		olho = olho->prox;
	}
	if(p_aux->inicio != NULL) {
		return 0;
	} else {
		return 1; 
	}
}

int valida_digito(t_listachar* l_inf, t_pilhachar* p_aux) {
	t_character* olho = l_inf->inicio;
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

void converte_1_dig(t_listachar* l_inf, t_pilhachar* p_pos, t_pilhachar* p_aux) {
	t_character* olho = l_inf->inicio;
	char c, comp;
	while(olho != NULL) {
		c = olho->dado;
		if(c =='+' || c =='-' || c =='*' || c =='/') {
			while(p_aux->inicio != NULL && ((p_aux->fim->dado == '*' && (c == '+' || c== '-')) || (p_aux->fim->dado == '/' && (c == '+' || c== '-')) || (p_aux->fim->dado == '*' && (c == '/' || c == '*')) || (p_aux->fim->dado == '/' && (c == '/' || c == '*')) || (p_aux->fim->dado == '+' && (c == '+' || c == '-')) || (p_aux->fim->dado == '-' && (c == '+' || c == '-')))) {
				comp = desempilha_pilha_char(p_aux);
				empilha_pilha_char(comp,p_pos);
			}
			empilha_pilha_char(c,p_aux);
		} else {
			if(c == '(' || c == ')') {
				if(c == '(') {
					empilha_pilha_char(c,p_aux);
				}
				if(c == ')') {
					while(p_aux->fim->dado != '(') {
						comp = desempilha_pilha_char(p_aux);
						empilha_pilha_char(comp,p_pos);
					}
					desempilha_pilha_char(p_aux);
				}
			} else {
				empilha_pilha_char(c,p_pos);
			}
		}
		olho = olho->prox;
	}
	while(p_aux->fim != NULL) {
		c = desempilha_pilha_char(p_aux);
		empilha_pilha_char(c,p_pos);
	}
}

void converte_maisdig(t_listachar* l_inf, t_pilhachar* p_pos, t_pilhachar* p_aux) {
	t_character* olho = l_inf->inicio;
	char atual, proximo, comp;
	while(olho != NULL) {
		if(olho->prox == NULL) {
			atual = olho->dado;
		} else {
			atual = olho->dado;
			proximo = olho->prox->dado;
		}
		if(atual >= '0' && atual <= '9') {
			empilha_pilha_char('{',p_pos);
			empilha_pilha_char(atual,p_pos);
			while(olho->prox != NULL && proximo >= '0' && proximo <= '9') {
				olho = olho->prox;
				atual = olho->dado;
				if(olho->prox != NULL) proximo = olho->prox->dado;
				empilha_pilha_char(atual,p_pos);
			}
			empilha_pilha_char('}',p_pos);
		} else {
			if(atual =='+' || atual =='-' || atual =='*' || atual =='/') {
			while(p_aux->inicio != NULL && ((p_aux->fim->dado == '*' && (atual == '+' || atual== '-')) || (p_aux->fim->dado == '/' && (atual == '+' || atual== '-')) || (p_aux->fim->dado == '*' && (atual == '/' || atual == '*')) || (p_aux->fim->dado == '/' && (atual == '/' || atual == '*')) || (p_aux->fim->dado == '+' && (atual == '+' || atual == '-')) || (p_aux->fim->dado == '-' && (atual == '+' || atual == '-')))) {
				comp = desempilha_pilha_char(p_aux);
				empilha_pilha_char(comp,p_pos);
			}
			empilha_pilha_char(atual,p_aux);
			} else {
				if(atual == '(') {
					empilha_pilha_char(atual,p_aux);
				}
				if(atual == ')') {
					while(p_aux->fim->dado != '(') {
						comp = desempilha_pilha_char(p_aux);
						empilha_pilha_char(comp,p_pos);
					}
					desempilha_pilha_char(p_aux);
				}
			}
		}
		olho = olho->prox;
	}
	while(p_aux->fim != NULL) {
		atual = desempilha_pilha_char(p_aux);
		empilha_pilha_char(atual,p_pos);
	}
}

float calcula_posfixa(int valid, t_pilhachar* p_pos, t_pilhaf* p_num) {
	t_character* olho = p_pos->inicio;
	char atual;
	float conv,a,b;
	while(olho != NULL) {
		atual = olho->dado;
		if(atual >= '0' && atual <= '9' && valid == 1) {
			empilha_pilha_num(atual-'0',p_num);
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
				empilha_pilha_num(conv,p_num);
			} else {
				if(atual == '+') {
				b = desempilha_pilha_num(p_num);
				a = desempilha_pilha_num(p_num);
				empilha_pilha_num(a+b,p_num);
			}
			if(atual == '-') {
				b = desempilha_pilha_num(p_num);
				a = desempilha_pilha_num(p_num);
				empilha_pilha_num(a-b,p_num);
			}
			if(atual == '/') {
				b = desempilha_pilha_num(p_num);
				a = desempilha_pilha_num(p_num);
				empilha_pilha_num(a/b,p_num);
			}
			if(atual == '*') {
				b = desempilha_pilha_num(p_num);
				a = desempilha_pilha_num(p_num);
				empilha_pilha_num(a*b,p_num);
			}
			}
		}
		olho = olho->prox;
	}
	return desempilha_pilha_num(p_num);
}
/* ---------------------------------------- */
int main() {
int valid_parent, valid_oper, valid_digito;
char digito;
t_listachar* l_inf = cria_listachar();
t_pilhachar* p_aux = cria_pilhachar();
t_pilhachar* p_pos = cria_pilhachar();
t_pilhaf* p_num = cria_pilhaint();
while(1) {
	printf("\e[H\e[2J");
	printf("\n\n\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("\t\t\t[   CALCULADORA POLONESA   ]\n");
	printf("\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("\n -> Expressão que deseja calcular : ");
	while(scanf("%c", &digito)==1 && digito != '\n') {
		empilha_lista_char(digito,l_inf);
	}
	printf("\n -> Pilha de entrada\t: ");
	mostra_listachar(l_inf);
	valid_oper = valida_oper(l_inf);
	valid_parent = valida_parent(l_inf,p_aux);
	if(valid_parent == 0 || valid_oper == 0) {
		printf("   <- EXPRESSÃO INVÁLIDA !\n");
	} else {
		printf("   <- EXPRESSÃO VÁLIDA !\n");
		valid_digito = valida_digito(l_inf,p_aux);
		if(valid_digito == 0) {					/* Expressão com pelo menos um número de 2 ou mais dígitos */
		converte_maisdig(l_inf,p_pos,p_aux);
		} else {								/* Expressão com números de 1 dígito */
		converte_1_dig(l_inf,p_pos,p_aux);
		}
		printf("\n -> Pilha polonesa\t: ");
		mostra_pilhachar(p_pos);
		printf("\n");
		printf("\n -> Expressão posfixa calculada = %.2f\n", calcula_posfixa(valid_digito,p_pos,p_num));
	}
	printf("\n\n\n\n\t\t aperte ENTER para calcular outra expressão\n");
	getchar();
	esvazia_lista(l_inf);
	if(valid_parent == 0) {
		esvazia_pilha(p_aux);
	}
	esvazia_pilha(p_pos);
}
return 0;
}
