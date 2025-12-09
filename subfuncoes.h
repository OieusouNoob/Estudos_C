#ifndef SUB_FUNCOES_H
#define SUB_FUNCOES_H
typedef struct alunos{
    char nome[40];
    float nota;
} alunos;

typedef struct req{
    int id;
    char req[40];

}req;

typedef struct pessoas{
    char nome[40];
    req *requisitos_obrigatorios;
    int quantidade_requisitos;
} pessoas;

int fibonacci(int termo);
int tabuada(int num);
int contadorP(int num, int num2);
int contadorI(int num, int num2);
int cont_par(int num, int num2);
int cont_impar(int num, int num2);
int controlador(int num, int num2, int tipo); /*preferencia de tipo 0 para par e 1 para impar*/
int leitura();
int ordenando(int *num, int *num2);

int cadastro_pessoas(pessoas *n, int qtd);
int requisitos(pessoas *n,int qtd);
int limpar_memoria(pessoas *n, int qtd);
int mostrar_pessoas(pessoas *n, int qtd);
int sys_comp_pessoas(pessoas *n, int qtd);

int cadastro_discentes(alunos *n, int qtd);
void mostrar_discentes(alunos *n, int qtd);
int classificando(alunos *n, int qtd);

#endif