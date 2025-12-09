#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "funcoes.h"
#include "subfuncoes.h"

void limpatela(){
    printf("\033c");
}
void limpeza(char *a){ /*Essa eu peguei do gemini. Pelo menos agora eu entendo como ela funciona,
    ela faz o ponteiro de char *p_lf apontar para o caractere '\n' e o modifica desde que não seja nulo*/
    if (a == NULL) return;
    char *p_lf = strchr(a, '\n');
    if (p_lf != NULL) {
        *p_lf = '\0';
    } else {

        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    char *p_cr = strchr(a, '\r');
    if (p_cr != NULL) {
        *p_cr = '\0';
    }

}

int converter_string_int(char *a, int comprimento){
    long temp;
    int convertido;
    char *end = NULL;

    while(1){
        
        if(fgets(a,comprimento,stdin) == NULL){ //Primerios vericamos se não é um ponteiro nulo
            printf("Insira algo:\n");
            limpeza(a); //Limpamos o '\n' caso tenha dado um erro e pedimos para o usuário inserir algo
        }
        limpeza(a); // Limpamos de novo, porque aquele limpeza acima está dentro do escopo do if() apenas

        temp = strtol(a,&end,10); /*Interessante, não é? Então, usamos uma variável long mais como cuidado, 
        já que não saberemos o comprimento da string*/
        /*resumindo, essa função strtol(); pega a variavel em string, e procura números inteiros,
         se encontrar um, ela joga dentro do temp e o mesmo para os próximo, se o inverso ocorrer
         ela faz o ponteiro end, apontar onde começou o primeiro caractere, encerrando ai. 
         Se houver algum caractere antes de um número não será lido*/

        if(a[0] == '\0' || end[0] != '\0'){ //Bom, usamos o a[0] para verifica se realmente houve uma transformação completa
            /*ao dizermos a[0] == '\0' estamos querendo saber se o primeiro caractere é o finalizador
            se sim, é porque a conversão deu errado, a string está vazia e subtitiuiu o '\n' pelo '\0'
            A avaliação do end[0] é para ter uma noção do tipo de dado que o usuário inseriu, se ele
            digitar 123abc, o end começa a apontar para o 'a', porque é o primeiro caractere.
            portanto se o ponteiro end[0] for diferente do terminador '\0' ele se torna verdadeiro, porque não leu
            nenhum caractere.    */
            printf("Isso não é um número, por favor insira um valor númerico\n");
            printf("Digite um número:\n");
         
            continue;
        }else{
            //Se chegou aqui é porque deu tudo certo.
            convertido = (int)temp;
            break;
        }
        //Edit - 25/10/25 é louco que em 2 meses eu entenda que está função --> strtol(); apenas faz o caractere 
        //ser apontado pelo seu segundo parametro? 
    }
    return convertido;

}
int  escolha(){
    limpatela();
    printf("Digite [1] para ver UM termo da fibonacci\n");
    printf("Digite [2] para ver UMA tabuada até 10\n");
    printf("Digite [3] para ver os pares de uma contagem\n");
    printf("Digite [4] para ver os ímpares de uma contagem\n");
    printf("Digite [5] para ver o melhor e o pior aluno\n");
    printf("Digite [6] para selecionar pessoas\n");
    printf("Digite [7] para ver o aproveitamento de algum aluno\n");
    printf("Digite [8] para sair\n");

    char escolha_pergunta[10];
    int comprimento = sizeof(escolha_pergunta);
    int selecionado;
    int cont = 0;

    printf("Digite o número: \n");

    do{
        selecionado = converter_string_int(escolha_pergunta,comprimento);
        if(cont >= 1){
            printf("Digite um número:\n");
        }
        cont += 1;
    }while(selecionado < 1 || selecionado > 8);

    casos(selecionado);
    char continua[10];
    int comp = sizeof(continua);

    printf("Deseja continuar?\n");
    int saidaf = sim_nao(continua,comp);
    return saidaf;

}
int casos(int a){
    switch (a)
    {
        case 1: //FIBONACCI
        {
            char termo[10];
            int comprimento = sizeof(termo);
            int fibo = 0;
            printf("Até que termo de fibonacci deseja ver?\n");
            do{
                fibo = converter_string_int(termo,comprimento);
            }while(fibo <= 0);
            printf("Nesse termo o valor é: %d\n",fibonacci(fibo));
            printf("Pressione uma tecla para continuar\n");
            break;
            
        }
        case 2: //TABUADA DE QUALQUER VALOR ATÉ 10
        {
            char num[10];
            int comp = sizeof(num);
            int valor = 0;

            do{
                valor = converter_string_int(num,comp);
            }while(valor <= 0);
            printf("---------------------------\n");
            if(tabuada(valor) == 1){
                return 1; //Deu certo!
            }else{
                return 0; //Deu errado
            }
            break;
            
        }
        case 3: //CONTADOR PAR
        {
            printf("Insira onde vai começar a contagem:\n");
            int valor = leitura();
            printf("Insira o final da contagem:\n");
            int valor2 = leitura();

            ordenando(&valor,&valor2);
            if(controlador(valor,valor2,0) == 1){
                return 1; //Sucesso
            }else{
                return 0; //Necessita depurar
            }
           /*Nada chega aqui, o else acima não permite*/
           break;
        }
        case 4: //CONTADOR IMPAR
        {
            printf("Insira onde vai começar a contagem:\n");
            int valor = leitura();

            printf("Insira o final da contagem:\n");
            int valor2 = leitura();

            ordenando(&valor,&valor2);
            if(controlador(valor,valor2,1) == 1){
                return 1; //Sucesso
            }else{
                return 0; //Necessita depurar
            }
            /*Nada chega aqui, o else acima não permite*/
            break;
           
        }
        case 5: //Melhor e pior aluno
        {
            printf("Quantos alunos tem na classe:\n");
            int qtd;
            do{
                qtd = leitura();
            }while(qtd <= 0);

            alunos *discente = (alunos*) malloc(qtd * sizeof(*discente));

            if(discente == NULL){
                printf("Erro ao alocar memória, encerrando\n");
                return -1; /*Erro de dado*/
            }

            cadastro_discentes(discente,qtd);
            mostrar_discentes(discente,qtd);
            classificando(discente,qtd);

            free(discente);
            discente = NULL;
            break;
        }
        case 6:
        {
            printf("Quantas pessoas serão selecionadas?\n");
            int qtd;
            do{
                qtd = leitura(); 
            }while(qtd <= 0);

            pessoas *person = (pessoas*) malloc(qtd * sizeof(*person)); /*A isso vai ficar complexo...*/
            if(person == NULL){
                return -1;/*erro na leitura de dado*/
            }   
            /*AAaaaa, como eu cheguei aqui hoje (08/08/2025)? Estou morrendo de cansaço, porém,sem sono*/
            sys_comp_pessoas(person,qtd);
            limpar_memoria(person,qtd);
            person = NULL;
            break;
        }
    }
    return 0; //Falhou
 
}

int sim_nao(char *a, int comprimento){
    int resposta;
    while(1){
        
        while(1){
            if(fgets(a,comprimento,stdin) == NULL){
                limpatela();
                limpeza(a);
                printf("Insira sim ou nao\n");
                continue;
            }else{
                break;
            }
        }
        limpeza(a);
        int tamanho = strlen(a);
        for(int i=0;i<tamanho;i++){
            a[i] = tolower(a[i]);
        }

    
        
        if(strcmp(a,"sim") == 0 || a[0] == 's'){    
            return 0; //Retornar 0 se a entrada for sim
            break;
        }else if((strcmp(a,"não") == 0) || (strcmp(a,"nao") == 0) || a[0] == 'n'){
            return 1; //Retorna 1 se a entrada for não
            break;
        }else{
            printf("Resposta inválida. Tente com ['sim'] ou ['não']\n");
        }
    }

}

float converter_string_float(char *a, int comprimento){
    float num;
    char *end;
    float fim;
    while(1){
        if(fgets(a,comprimento,stdin) == NULL){
            limpatela();
            printf("Insira um número com casas decimais:\n");
            limpeza(a);
        }
        limpeza(a);

        fim = strtof(a,&end);

        if(a[0] == '\0' || end[0] != '\0'){
            printf("Isso não é um número com casas decimais, por favor, insira um:\n");
        }else{
            break;
        }
    } /*Sim, eu quis fazer isso mesmo, me deu vontade de usar break; Então usei*/
    return fim;

}
