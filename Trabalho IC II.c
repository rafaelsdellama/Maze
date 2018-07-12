///============================================================================================================
///Nome: Labirinto(NxM)
///Autores: Rafael Silva Del Lama 
///Descrição: Labirinto recursivo em C
///============================================================================================================

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>


///Tamanho da matriz
#define MAX_LINHA 10 ///Quantas linhas tem o labirinto
#define MAX_COLUNA 10 ///Quantas colunas tem o labirinto

///Definições
#define CAMINHO_LIVRE 0 ///Numero que ira representar o caminho livre para passar
///PAREDE 1
#define CAMINHO 2 ///Numero que ira representar o caminho da saida

///Declaração de funções
void imprime_maze(int maze[][MAX_COLUNA]); ///Imprime a matriz;
void gera_maze(int maze[][MAX_COLUNA]); ///Gera a Matriz;
int procura_caminho(int maze[][MAX_COLUNA], int i, int j, int lado, int *recursiva, char pass[], int *passos); ///Procura um caminho no labirinto
int menu(); ///Mostra menu de opcao da matriz
void imprime_legenda(); ///Imprime a legenda do labirinto
void ler_matriz(int maze[][MAX_COLUNA]); ///le matriz do arquivo matriz.txt
void imprime_caminho(char pass[], int passos); ///Imprime o caminho salvo na string pass (se houver caminho)
void cabecalho(); ///Imprime cabeçalho

///Função principal
void main(){
    int maze[MAX_LINHA][MAX_COLUNA]; ///Cria a matriz maze
    int recursiva = 0; ///Conta quantas vezes foi chamada a função recursiva
    int passos=0;   ///Conta quantos passos ele deu para achar o caminho
    char pass[MAX_COLUNA*MAX_LINHA]; ///Salva o caminho de saida
    cabecalho();

    switch(menu()){
        case 1: gera_maze(maze);break;
        case 2: ler_matriz(maze);break;
    }

    imprime_maze(maze); ///Imprime a matriz (labirinto)

    if(procura_caminho(maze,0,0,0,&recursiva,pass,&passos)==1){
        printf("\n\tCaminho encontrado!\n");
        imprime_caminho(pass,passos); ///Imprime o caminho
        imprime_maze(maze); ///imprime a matriz com o caminho
        printf("\n\tRecursivas: %d\n",recursiva); ///Mostra quantas chamadas recursivas foram necessarias
    }
    else
        printf("\n\tCaminho nao encontrado!\n");
    system("pause");
}

///Funções:

///Imprime a matriz;
void imprime_maze(int maze[][MAX_COLUNA]){
    ///Maze é a matriz com o labirinto
    int i,j;
    for(i=0;i<MAX_LINHA;i++){
        for(j=0;j<MAX_COLUNA;j++){
            printf("%d ",maze[i][j]);
        }
        printf("\n");
    }
   imprime_legenda(); ///Imprime a legenda da matriz
}

///Gera a Matriz;
void gera_maze(int maze[][MAX_COLUNA]){
    ///Maze é a matriz com o labirinto
    int i,j,aux;
    srand( (unsigned)time(NULL) ); ///Gerar numeros diferentes

     ///Preenche a matriz com números aleatórios.
     for(i=0;i<MAX_LINHA;i++){
        for(j=0;j<MAX_COLUNA;j++){
            ///Geramos numeros aleatórios, porem controlamos a porcentagem de 0's.
            aux=rand()%10;
            if(aux<7) ///Altere o valor para alterar a porcentagem de 0's
                maze[i][j]= 0;
            else
                maze[i][j]= 1;
        }
    }
    ///Por padrão, as duas posições devem ser 0;
    maze[0][0]=maze[MAX_LINHA-1][MAX_COLUNA-1]=CAMINHO_LIVRE;
}

///Procura um caminho no labirinto
int procura_caminho(int maze[][MAX_COLUNA],int i, int j, int lado, int *recursiva, char pass[], int *passos){
///Maze é a matriz com o labirinto
///i= linha ; j = coluna
/// recursiva indica a quantidade de chamadas da função q procura o caminho
/// pass[] é um vetor de char onde é salvo o caminho ( se houver)
/// passos corresponde a quantos passos da entrada até a saida ( se houver saida)
///             Lado:
///         1 = foi p/ direita
///         2 = foi p/ esquerda
///         3 = foi p/ cima
///         4 = foi p/ baixo

    *recursiva+=1; ///Conta quantidade de chamada da função!

    ///Verifica se achou a saida( ou seja, verifica se esta na ultima casa)
    if(i== MAX_LINHA-1 && j == MAX_COLUNA-1){
        maze[MAX_LINHA-1][MAX_COLUNA-1]=CAMINHO;  ///Se achou o caminho, preenche a ultima posição
        return 1;
    }
    ///Procura a saida:

    if(maze[i][j+1]==CAMINHO_LIVRE && j<MAX_COLUNA-1 && lado!=2){///Verifica se a direita esta livre
        if(procura_caminho(maze,i,j+1,1,recursiva,pass,passos)==1){ ///Chama novamente a função para procurar o caminho para a direita, e se encontrar, faça:
            pass[*passos]='D'; /// Adiciona 'D' no vetor que salva o caminho
            *passos+=1; ///Incrementa a variavel que conta quantos passos até a saida
            maze[i][j]=CAMINHO; /// Altera a maze indicando o caminho
            return 1;
        }
    }
    if(maze[i][j-1]==CAMINHO_LIVRE && j>0 && lado!=1){///Verifica se a esquerda esta livre
        if(procura_caminho(maze,i,j-1,2,recursiva,pass,passos)==1){ ///Chama novamente a função para procurar o caminho para a esquerda, e se encontrar, faça:
           pass[*passos]='E'; /// Adiciona 'E' no vetor que salva o caminho
            *passos+=1; ///Incrementa a variavel que conta quantos passos até a saida
            maze[i][j]=CAMINHO;/// Altera a maze indicando o caminho
            return 1;
        }
    }
    if(maze[i+1][j]==CAMINHO_LIVRE && i<MAX_LINHA-1 && lado!=3){///Verifica se em baixo esta livre
        if(procura_caminho(maze,i+1,j,4,recursiva,pass,passos)==1){ ///Chama novamente a função para procurar o caminho para baixo, e se encontrar, faça:
            pass[*passos]='B'; /// Adiciona 'B' no vetor que salva o caminho
            *passos+=1; ///Incrementa a variavel que conta quantos passos até a saida
            maze[i][j]=CAMINHO; /// Altera a maze indicando o caminho
            return 1;
        }
    }
    if(maze[i-1][j]==CAMINHO_LIVRE && i>0 && lado!=4){///Verifica se em cima esta livre
        if(procura_caminho(maze,i-1,j,3,recursiva,pass,passos)==1){ ///Chama novamente a função para procurar o caminho para cima, e se encontrar, faça:
            pass[*passos]='C'; /// Adiciona 'C' no vetor que salva o caminho
            *passos+=1;///Incrementa a variavel que conta quantos passos até a saida
            maze[i][j]=CAMINHO; /// Altera a maze indicando o caminho
            return 1;
        }
    }
    return 0;
}

///Mostra menu de opcao da matriz
int menu(){
    int opcao;
    do{
        printf("1-Gerar matriz aleatoria\n");
        printf("2-Ler matriz do arquivo matriz.txt\n");
        scanf("%d",&opcao);
    }while(opcao!=1 && opcao!=2); ///Verifica se a opção escolhida existe
    system("cls"); ///Limpa a tela
    printf("\tOpcao: %d\n\n", opcao); /// Mostra a opção escolhida
    return opcao; /// Retorna a opção escolhida
}

///Imprime a legenda do labirinto
void imprime_legenda(){
    printf("Legenda:\n");
    printf("\t0-Caminho livre\n");
    printf("\t1-Parece\n");
    printf("\t%d-Caminho\n",CAMINHO);
    printf("\n");
}
///le matriz do arquivo matriz.txt
void ler_matriz(int maze[][MAX_COLUNA]){
///Maze é a matriz com o labirinto
    int i,j;

    ///Abre o arquivo;
    FILE *matriz;

    matriz = fopen("matriz.txt", "r");

    ///Verifica se o arquivo foi aberto com exito, se n imprime a msg de erro
     if(matriz == NULL){
        printf("Impossivel abrir o arquivo matriz.txt\n");
        exit(1);
    }

    ///Copia do txt para a matriz
    for(i=0;i<MAX_LINHA;i++){
        for(j=0;j<MAX_COLUNA;j++){
            fscanf(matriz,"%d",&maze[i][j]);
        }
    }
}

///Imprime o caminho salvo na string pass (se houver caminho)
void imprime_caminho(char pass[], int passos){
///Maze é a matriz com o labirinto
/// passos corresponde a quantos passos da entrada até a saida ( se houver saida)
    int i;
    for(i=0;i<passos;i++){
        switch(pass[i]){
            case 'D' : printf("P/ direita\n");break;
            case 'E' : printf("P/ esquerda\n");break;
            case 'C' : printf("P/ cima\n");break;
            case 'B' : printf("P/ baixo\n");
        }
    }
    printf("\n"); ///Pula uma linha antes de imprimir a matriz;
}

///Imprime cabeçalho
void cabecalho()
{
	printf("================================================================================\n");
	printf("                           Universidade de Sao Paulo\n");
	printf("                     Departamento de Computacao e Matematica\n");
	printf("                             Informatica Biomedica\n\n");
	printf("                 Disciplina: IBM1012 - Introducao a Computacao II\n");
	printf("                            Docente: Dr. Zhao Liang\n\n");
	printf("================================================================================\n\n");
}
