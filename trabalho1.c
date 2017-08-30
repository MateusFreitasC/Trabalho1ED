/* 	Mateus Freitas Cavalcanti	16/0137519
	Rodrigo Naves Rios			16/0144094
   	Estruturas de Dados - Turma C
  	Trabalho 1 -> Calculadora Polonesa */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct character{
	char dado;
	struct character* prox;
}t_character;

typedef struct pilhac{
	t_character* inicio;
	t_character* fim;
}t_pilhac;

t_pilhac* cria_pilhac() {
	t_pilhac* pc = (t_pilhac*)malloc(sizeof(t_pilhac));
	pc->inicio = NULL;
	pc->fim = NULL;
	printf("\n -> PILHA DE CHARACTER CRIADA !\n\n");
	return pc;
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

void mostra_pilhac(t_pilhac* pc) {
	int count=1;
	t_character* aux = pc->inicio;
	printf("\n -> Pilha de character :\n");
	while(aux != NULL) {								/* Percorre a lista e mostra cada elemento */
		printf("%dº elemento -> %c\n", count, aux->dado);
		aux = aux->prox;
		count++;
	}
}

char desempilha_1(t_pilhac* pc) {
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

int main() {
char digito;
t_pilhac* pc = cria_pilhac();
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
	printf("\n\n aperte ENTER para calcular outra expressão\n")
	getchar();
}
return 0;
}
