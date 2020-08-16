// Desenvolvedor: Rafael Antunes Vieira.
// Profissão: Estudante de Ciência da Computação na Universidade Federal de Itajubá-UNIFEI.
// Idioma: Portugues-Brazil.
// E-mail: rafaelantunesvieira@outlook.com.br
/* Descrição: Este repositório contém um algoritmo para solucionar o seguinte problema: 
			  Desenvolver uma estrutura de árvore binária de busca em que o usuário deve preenchê-la 
			  com valores numéricos de sua escolha. Logo em seguida, o mesmo usuário, 
			  deve escolher um elemento desta árvore para ser removido.                              */
// Data: 20/02/2019
// Código livre para utilização e modificação :D

/*Bibliotecas necessárias*/
#include <stdio.h>
#include <stdlib.h>

/*Estruturas*/
struct t_no
{
	int chave;
	struct t_no *esq;
	struct t_no *dir;
};

typedef struct t_no No;
typedef No *p_arvore;

/*Prototipos das funções*/
No *criar(int k);
p_arvore remover(No *atual);
p_arvore inserir(p_arvore r, No *novo);
p_arvore remover_elemento(p_arvore r, int k);
int verifica_arvore_vazia(p_arvore r);
p_arvore busca(p_arvore r, int k);
void imprimir(p_arvore r);
void liberar(p_arvore r);

/*MAIN*/
int main()
{
	p_arvore raiz = NULL;
	int TAM;
	int numeros[TAM], i, descarte, resposta = 0;

	/* O ( DO WHILE ) foi implementado com o intuito de evitar que o programa feche após finalizar a execução. 
 	 * Só irá ser fechado após o usuário confirmar apertando o enter.
     * No Windows o programa pode ser executado fora da tela do terminal, por isso, quando a execução termina 
     * a tela do programa é fechada automaticamente.    */
	char exit = '\n'; /*Variável para de controle do DO WHILE*/
	do
	{
		printf("***ARVORE BINARIA DE BUSCA!***\n\nDigite quanto elementos deseja inserir na arvore:");
		scanf("%d", &TAM);
		for (i = 0; i < TAM; i++)
		{
			printf("Numero %d :", i + 1);
			scanf("%d", &numeros[i]);
			raiz = inserir(raiz, criar(numeros[i]));
		}
		printf("\n");
		imprimir(raiz);
		do
		{
			printf("\n\nQual dos numeros contidos na arvore voce deseja remover?\n");
			scanf("%d", &descarte);
			while (busca(raiz, descarte) == NULL)
			{
				printf("\n\nNumero informado não existe na arvore, digite outro que esteja na arvore\n");
				printf("Arvore: ");
				imprimir(raiz);
				printf("\n\nQual dos numeros contidos na arvore voce deseja remover?\n");
				scanf("%d", &descarte);
			}
			printf("\nRemovendo o numero.............\n\n");
			raiz = remover_elemento(raiz, descarte);
			printf("Elemento removido foi: %d\n\nIMPRIMIRNDO A ARVORE NOVAMENTE PARA VERIFICAR SE FOI REMOVIDO\n\n", descarte);
			printf("Arvore depois da remocao: ");
			imprimir(raiz);

			if (verifica_arvore_vazia(raiz) == 0)
			{
				printf("\n\n|Deseja remover mais algum elemento?\n| 1 para SIM\n| 0 para NÃO\nResposta:");
				scanf("%d", &resposta);
			}
			else
			{
				printf("\nArvore Vazia!\n");
			}

		} while (resposta == 1);

		liberar(raiz);
		printf("\n\nAperte ENTER para sair!");
		scanf("%c", &exit);

	} while (exit != '\n');

	return 0;
}

/*Função responsável por criar e inicializar a arvore*/
No *criar(int k)
{
	p_arvore novo = (p_arvore)malloc(sizeof(No));
	novo->chave = k;
	novo->esq = NULL;
	novo->dir = NULL;
	return novo;
}

/*Função responsável por imprimir o conteudo da arvore*/
void imprimir(p_arvore r)
{
	if (r == NULL)
		return;
	printf("%d,", r->chave);
	imprimir(r->esq);
	imprimir(r->dir);
}

p_arvore busca(p_arvore r, int k)
{
	if (r == NULL)
		return NULL;
	else if (r->chave > k)
		return busca(r->esq, k);
	else if (r->chave < k)
		return busca(r->dir, k);
	else
		return r;
}

/*Função responsável por inserir elementos na arvore*/
p_arvore inserir(p_arvore r, No *novo)
{
	if (r == NULL)
		return novo;
	if (r->chave > novo->chave)
		r->esq = inserir(r->esq, novo);
	else
		r->dir = inserir(r->dir, novo);
	return r;
}
/*Função responsável por remover elementos na arvore*/
p_arvore remover_elemento(p_arvore r, int k)
{
	// Procura o nó na arvore
	// Se o valor porcurado for maior que a chave
	// move-se para a esquerda da arvore
	if (r->chave > k)
	{
		r->esq = remover_elemento(r->esq, k);
	}
	// Se o valor porcurado for menor que a chave
	// move-se para a direita da arvore
	else if (r->chave < k)
	{
		r->dir = remover_elemento(r->dir, k);
	}
	// Final da arvore
	else if (r == NULL)
	{
		return r;
	}
	// Achou onde está o nó que será removido
	else
	{
		// Se não tiver filhos, só remove
		if (r->esq == NULL && r->dir == NULL)
		{
			free(r);
			r = NULL;
		}
		// Filhos a direita
		else if (r->esq == NULL)
		{
			p_arvore aux = r;
			r = r->dir;
			free(aux);
		}
		// Filhos a esquerda
		else if (r->dir == NULL)
		{
			p_arvore aux = r;
			r = r->esq;
			free(aux);
		}
		// Filhos a direita e a esquerda
		else
		{
			p_arvore aux = r->esq;
			while (aux->dir != NULL)
			{
				aux = aux->dir;
			}
			r->chave = aux->chave;
			aux->chave = k;
			r->esq = remover_elemento(r->esq, k);
		}
	}
	return r;
}

int verifica_arvore_vazia(p_arvore r)
{
	if (r == NULL)
	{
		return 1;
	}
	return 0;
}

/*Função responsável por desalocar a memoria da arvore */
void liberar(p_arvore r)
{
	if (r == NULL)
		return;
	liberar(r->esq);
	liberar(r->dir);
	free(r);
}