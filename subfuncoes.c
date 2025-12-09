
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funcoes.h"
#include "subfuncoes.h"

int fibonacci(int termo){
    int ant=0,atual=1,prox=0;

    if(termo <= 0){
        return 0;
    }else if(termo == 1){
        return atual;
    }else if(termo == 2){
        return atual;
    }
    
    for(int i=3;i<=termo;i++){
        prox = atual + ant;
        ant = atual;
        atual = prox;
    }
    return atual;
}

int tabuada(int valor){
    if(valor <= 0){ //não avaliarei como NULL porque a função de converter strings em int já faz isso jkkk
        return 0; //Deu errado
    }

    for(int i=1;i<=10;i++){
        printf("%d X %d = %d\n",valor,i,valor*i);
    }
    return 1; //Deu certo!
}
int contadorP(int menor, int num2){
    //o primeiro paramêtro é melhor que seja menor
    while(menor <= num2){
        if(menor % 2 == 0){
            printf("%d\n",menor);
        }
        menor++;
    }
    return 1; //Deu certo!
}
int cont_par(int num, int num2){
    
    if(num == num2){
        printf("Os números são iguais, não existe uma contagem\n");
        return -1; //Sucesso na execução do programa, mas falha na entrada
    }
    contadorP(num,num2);
    return 1;/*Sucesso*/
}

int contadorI(int menor, int num2){
    while(menor < num2){
       if(menor % 2 != 0){
            printf("%d\n",menor);
       }
       menor++;
    }
    return 1; //Deu certo
}
int cont_impar(int num, int num2){
    if(num == num2){
        printf("Os números são iguais, não existe uma contagem\n");
        return -1;
    }  
    contadorI(num,num2);
    return 1;/*Sucesso*/
}

int controlador(int num, int num2, int tipo){
    if(tipo == 1){
        cont_impar(num,num2);
        return 1; /*Sucesso*/
    }else if(tipo == 0){
        cont_par(num,num2);
        return 1; /*Sucesso*/
    }else{
        printf("Você inseriu um tipo inválido, tente [0 - par] e [1 - impar]\n");
        return -1;/*Dado recebido pelo usuário tinha algum erro, tratar esse erro*/
    }
    return 0; /*Erro da função*/
}

int leitura(){
    char num[10];
    int comp = sizeof(num); /*sizeof == me dê um valor inteiro com base no tamanho disso entre ().*/
    int control = 0;
    int num1;

    num1 = converter_string_int(num,comp);

    return num1;
}

int ordenando(int *valor, int *valor2){ /*Aqui recebemos o endereço de cada elemento, ao receber o endereço, começamos
    a modificar ele a partir de uma função local, sim, um escopo local afetando o global.*/
    if(valor == NULL || valor2 == NULL){
        printf("Acesso indevido a memória\n");
        return -1; /*Algo deu errado nos dados recebidos*/
    }
    if(*valor2 < *valor){  /*O motivo do operador (*) é para que a função acesse o conteúdo lá no escopo global
        atráves do endereço da memória.*/
        int temp = *valor2;
        *valor2 = *valor;
        *valor = temp;
    }
    return 1;/*Sucesso*/
}



int cadastro_discentes(alunos *n, int qtd){
    if(n == NULL){
        printf("Acesso indevido a memória\n");
        return -1; /*Erro no dado recebido*/
    }

    for(int i=0;i<qtd;i++){
        printf("\nInsira o nome do %d Aluno:",i+1);
        char nomes[40];
        fgets(nomes,40,stdin);
        limpeza(nomes);
        strcpy(n[i].nome,nomes);

        printf("Qual a nota do aluno %s\n",n[i].nome);
        char nota[10];
        int comp = sizeof(nota);
        float nota_f;
        do{
            nota_f = converter_string_float(nota,comp);

            if(nota_f < 0 || nota_f > 10){
                printf("Insira uma nota entre 0 e 10 pontos\n");
                limpatela();
                printf("Nota do %s:\n",n[i].nome);
            }
            
        }while(nota_f < 0 || nota_f > 10);

        n[i].nota = nota_f;
    }
    return 1; /*Sucesso*/
}
void mostrar_discentes(alunos *n, int qtd){
    printf("--------------------------\n");
    for(int i=0;i<qtd;i++){
        printf("Aluno: %s\n",n[i].nome);
        printf("Nota: %.2f\n",n[i].nota);
        
    }
}

int classificando(alunos *n, int qtd){
    float Mnota = n[0].nota;
    float mnota = n[0].nota;
    char Mnome[40];
    char mnome[40];
    strcpy(Mnome,n[0].nome);/*Podia usar a ->, mas ainda não entendo exatamente quando usar, mesmo já tendo visto*/
    strcpy(mnome,n[0].nome);
    for(int i=0;i<qtd;i++){

        if(Mnota < n[i].nota){
            Mnota = n[i].nota;
            strcpy(Mnome,n[i].nome);
        }
        if(mnota > n[i].nota){
            mnota = n[i].nota;
            strcpy(mnome,n[i].nome);
        }
    }

    printf("O melhor aluno foi: %s com a nota %.2f\n",Mnome,Mnota);
    printf("O pior aluno foi: %s com a nota %.2f\n",mnome,mnota);

    return 1; /*Sucesso!*/
}
int limpar_memoria(pessoas *n, int qtd){

    if(!n){return -1; /*Ponteiro nulo*/}

    for(int i=0;i<qtd;i++){
        free(n[i].requisitos_obrigatorios); /*Limpando cada elemento do vetor para que não haja problemas
        como vazamento de memória*/
    }

    free(n); /*Limpamos completamente toda a estrutura*/

    return 1;/*Sucesso na limpeza*/
}

int requisitos(pessoas *n,int qtd){
   if(!n){
    return -1; /*Ponteiro Nulo*/
   }

   for(int i=0;i<qtd;i++){
        printf("\t\tDefinindo os requisitos para %s\n",n[i].nome);
        char temp[10];
        int comprimento = sizeof(temp);
        int qtd_req=0;

        printf("Quantos requisitos essa pessoa terá?\n");

        do{
            qtd_req = converter_string_int(temp,comprimento); /*O de sempre, convertendo um char em int*/
            if(qtd_req <= 0){
                printf("Insira pelo menos um requisito\n");
            }
        }while(qtd_req <= 0); /*Enquanto for menor ou igual a zero, pelo menos um requisito por pessoa*/
        n[i].quantidade_requisitos = qtd_req; /*Aqui passamos o id da pessoa cadastrada, como um id do
        MySQL, assim: id INT PRIMARY KEY AUTO_INCREMENT, assim nunca havera repetições de id*/
        n[i].requisitos_obrigatorios = malloc(qtd_req * sizeof(req)); /*Pedimos a quantidade de mémoria de acordo
        com a quantia de requisitos de casa pessoa*/
        for(int j=0;j<qtd_req;j++){
            printf("\nInsira o %d requisito:",j+1);
            char temp[40];
            if(fgets(temp,sizeof(temp),stdin) == NULL){
                printf("Insira pelo menos uma palavra chave\n");
                j--;/*Não precisa de limpeza aqui dentro, já que a variavel não existira se o laço
                for resetado*/
                continue;
            }
            limpeza(temp);
            strcpy(n[i].requisitos_obrigatorios[j].req,temp); /*Perai eu estou abrindo uma boneca russsa? Matrisoka?
            Eu estou apontando para essa estrutura que aponta para outra e a modificando? 
            é isso mesmo?*/
            n[i].requisitos_obrigatorios[j].id = j + 1; /*Mesma lógica do MySQL, apenas não
            existir pessoas com o mesmo 'id', fazemos assim*/
        }
        
        /*Precisa liberar a memória no outro arquivo*/

        
   }
   return 1; /*Deu tudo certo aqui.*/
}

int mostrar_pessoas(pessoas *n, int qtd){
    if(!n){return -1; /*Ponteiro Nulo*/}
    printf("-------------------Pessoas cadastradas-------------------\n");

    for(int i=0;i<qtd;i++){
        printf("Quantidade de Requisitos: %d - NOME: %s \n",n[i].quantidade_requisitos,n[i].nome);
    }
    printf("Deseja ver os requisitos de cada pessoa?\n");
    char temp[40];
    int comp = sizeof(temp);
    int ver = sim_nao(temp,comp);
    if(!ver){
        for(int i=0;i<qtd;i++){
            int qtd_req = n[i].quantidade_requisitos;
            printf("-------------------Requisitos-------------------\n");
            printf("Pessoa: %s\n",n[i].nome);
            for(int j=0;j<qtd_req;j++){
                printf("%s\n",n[i].requisitos_obrigatorios[j].req); /*Toda vez eu esqueço de usar o 
                operador (.) para acessar os dados dentros da struct*/
                /*Quandor for acesar outra struct, não esqueca de usar os indices (i e j), geralmente são esses
                para acessar um de cada vez e modificar los, se houver mais structs, mais laços deverão existir*/
            }
        }
        printf("Pressione uma tecla para sair\n");
        getchar();
    }

    return 1;/*Deu tudo certo*/
}

int sys_comp_pessoas(pessoas *n, int qtd){
    if(!n){return -1; /*Ponteiro Nulo*/}
    cadastro_pessoas(n,qtd);
    requisitos(n,qtd);
    mostrar_pessoas(n,qtd);

    return 1;/*Sucesso, eu acho que funciona, pelo menos*/
}