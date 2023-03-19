#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

//Variavel global que faz referencia ao total de aulas
int maxClass = 36;

//Variavel global que será utilizada com auto incremento para gerar a matricula dos novos alunos cadastrados
int matricula = 202200;

//Variável que representa a quantidade de vagas disponíveis
int vagas = 30;

//Declaração global dos vetores que armazenarão os dados dos alunos
//Tabela de alunos
int aluno[30];
//Tabela das notas
float notas[30][4];
//Tabela de faltas
int faltas[30];
//Tabela de turmas
int turma[30];

//Declaração das funções que serão implementadas
// Funcionalidades de cadastro, atualização e remoção
void cadastrarAluno();
void atualizarAluno(int mat);
void removerAluno();
int selecionarAluno();

//Funcionalidades de listagem
// o parâmetro std é utilizado para informar a função qual o numero de alunos do filtro em questão
void funcLista();
void listarAlunos(int std);
void listarAprovados(int std, int apr);
void listarReprovadosMedia(int std, int rep);
void listarReprovadosFaltas(int std, int rep);
int alunosAprovados(int std);
int reprovadosMedia(int std);
int reprovadosFaltas(int std);

//Função cabeçalho
// void titleRow(int std);

//Funções auxiliares, aln faz referência a posição do vetor do aluno em questão
float calculaMedia(int aln);
float calculaFrequencia(int aln);
void mostraAluno(int aln, int mat);
bool buscaAluno(int aln);
void organizaAlunos(int aln);

int main(){

  //Variáveis diversas para funcionamento do algoritmo
  int option, i, mat;

  //Inicializando vetor de alunos
  for(i = 0;i<30;i++){
    aluno[i] = 0;
  }
  
  //Menu de ações do sistema
  do{
    printf("|------ SISTEMA ACADEMICO ------|\n");
    printf("\n");
    printf("| 1 - Cadastrar aluno           |\n");
    printf("\n");
    printf("| 2 - Atualizar dados de aluno  |\n");
    printf("\n");
    printf("| 3 - Remover aluno             |\n");
    printf("\n");
    printf("| 4 - Listar alunos             |\n");
    printf("\n");
    printf("Selecione uma opção: ");
    scanf("%d", &option);
    printf("\n");

    switch(option) {
      case 1:
        //Condicional que verifica se há vagas disponíveis
        if(vagas > 0){
          cadastrarAluno();
        }else{
          printf("\nNão é possível cadastrar novos alunos, não há vagas disponíveis no momento!\n");
          printf("\n");
        }
        break;
      case 2:
        
        printf("\nInforme a matrícula do aluno: ");
        scanf("%d", &mat);

        if(buscaAluno(mat)){
          atualizarAluno(mat);
        }else{
          printf("\nNão foi encontrado nenhum aluno com a matrícula informada!\n");
          printf("\n");
        }
        
        break;
      case 3:

        printf("\nInforme a matrícula do aluno: ");
        scanf("%d", &mat);

        if(buscaAluno(mat)){
          removerAluno(mat);
        }else{
          printf("\nNão foi encontrado nenhum aluno com a matrícula informada!\n");
          printf("\n");
        }
       
        break;
      case 4:
        funcLista();
        break;
      case 0: //caso para encerrar sessão
        break;
      default: //caso para quando usuário selecionar uma opção que não consta no menu
        printf("\nOpção inválida, selecione um número correspondente a uma das opções do menu\n");
        printf("\n");
        break;
    }
    
  }while(option != 0);
  
}


void cadastrarAluno(){
  int i = 0, j;
  
  //Variável que será utilizada para "confirmar" quando uma vaga for encontrada
  int findPos = 0;

  //Variável que será utilizada para "confirmar" um cadastro
  int isOk = 0;
  
  //Variáveis que armazenarão os dados informados "temporariamente"
  float notes[4];
  int fault, trm;
  
  do{
    if(aluno[i] == 0){
      //Confirmação de que foi encontrada uma vaga
      findPos = 1;

      //Loop que permitirá ao usuário corrigir informações inseridas de um aluno
      while(isOk == 0){
  
        //Loop para inserir as 4 notas
        for(j=0;j<4;j++){
          do{
            
          printf("\nInsira a nota %d: ", (j+1));
          scanf("%f", &notes[j]);

          if(notes[j]<0 || notes[j]>10){
            printf("Nota inserida é inválida. Digite uma nota maior que 0 e menor que 10");
          }
          }while(notes[j]<0 || notes[j]>10);
        }
        //Informar quantidade de faltas e turma
        printf("\nInforme a quantidade de faltas do aluno: ");
        scanf("%d", &fault);
        printf("\nInforme a turma do aluno: ");
        scanf("%d", &trm);

        //"Check-in" de informações inseridas pelo usuário
        printf("\n|  Confirmação  |\n");
        printf("\nNova matrícula: %d", (matricula+1));
        for(j=0;j<4;j++){
          printf("\nNota %d: %.1f", (j+1), notes[j]);
        }
        printf("\nFaltas: %d", fault);
        printf("\nTurma: %d", trm);
        printf("\n");
        printf("\nSelecione uma das opções a seguir:\n");
        printf("0 - Corrigir informações de cadastro de novo aluno\n");
        printf("1 - Confirmar cadastro de novo aluno\n");
        printf("2 - Cancelar cadastro de novo aluno\n");
        scanf("%d", &isOk);
      }

      //Confirmado pelo usuário, os dados temporários serão salvos nos respectivos vetores
      if(isOk == 1){
        //Auto-incremento para gerar automaticamente a matrícula
        matricula++;
        //"Dar baixa" na quantidade de vagas disponíveis
        vagas--;

        //Atribuição de dados
        aluno[i] = matricula;
        for(j=0;j<4;j++){
          notas[i][j] = notes[j];
        }
        faltas[i] = fault;
        turma[i] = trm;
        
        printf("\nCadastro realizado com sucesso!\n");
        printf("\n");
      }else if(isOk != 1 && isOk != 0){
        printf("\nCadastro de aluno cancelado!\n");
        printf("\n");
      }      
    }
    i++;
  }while(findPos != 1);
}

//Função para exibir o menu com as opções de listas
void funcLista(){
  int option, i, j;
  
  //Contador de alunos cadastrados
  int qtdAlunos;

  qtdAlunos = 30 - vagas;
  
  do{
  printf("\nSelecione uma das opções a seguir: \n");
  printf("\n");
  printf("1 - Listar todos os alunos cadastrados\n");
  printf("2 - Listar alunos aprovados\n");
  printf("3 - Listar alunos reprovados por media\n");
  printf("4 - Listar alunos reprovados por faltas\n");
  printf("0 - Retornar ao menu principal\n");
  scanf("%d", &option);

  if(qtdAlunos > 0 || option == 0){

    //Variáveis que poderão ser usadas durante os casos
    int aprovados, reprovadosM, reprovadosF;
    
    switch(option){
      case 1:
        if(qtdAlunos > 0)
          listarAlunos(qtdAlunos);
        break;
      case 2:
        aprovados = alunosAprovados(qtdAlunos);
        if(aprovados>0)
          listarAprovados(qtdAlunos, aprovados);
        else{
          printf("\nNão há nenhum aluno aprovado!\n");
        }
        break;
      case 3: 
        reprovadosM = reprovadosMedia(qtdAlunos);
        if(reprovadosM>0)
          listarReprovadosMedia(qtdAlunos, reprovadosM);
        else{
          printf("\nNão há nenhuma aluno reprovado por media!\n");
        }
        break;
      case 4:
        reprovadosF = reprovadosFaltas(qtdAlunos);
        if(reprovadosF>0)
          listarReprovadosFaltas(qtdAlunos,reprovadosF);
        else{
          printf("\nNão há nenhum aluno reprovado por faltas!\n");
          printf("\n");
        }
        break;
    }
  }else{
          printf("\nNão há nenhum aluno cadastrado!\n");
          printf("\n");
  }
    
  }while(option != 0);
  
}

//Função para listar todos os alunos cadastrados
void listarAlunos(int std){
  int i, j;
  
  printf("\nAlunos encontrados: %d", std);
  printf("\n|                Lista de alunos                |\n");
  printf("|Matrícula - N1 / N2 / N3 / N4 - Faltas - Turma |\n");
  
  for(i=0;i<std;i++){
    
    printf("|%d    - %.1f / %.1f / %.1f / %.1f - %d - %d  \n", aluno[i], notas[i][0],notas[i][1],notas[i][2],notas[i][3], faltas[i], turma[i]);
    
    }
};

//Função para listar alunos aprovados
void listarAprovados(int std, int apr){
  int i, j;
  float media, frequencia;
  
  printf("\nAlunos aprovados: %d", apr);
  printf("\n|        Lista de alunos          |\n");
  printf("|Matrícula - Media - Frequencia - Turma |\n");

  for(i=0;i<std;i++){
    media = calculaMedia(i);
    frequencia = calculaFrequencia(i);
    if(media >= 7 && frequencia >= 60)
      printf(" %d    - %.1f - %.2f - %d\n",aluno[i], media, frequencia, turma[i]);
  }
}

//Função para calcular a quantidade de alunos aprovados
int alunosAprovados(int std){
  int i, j; 
  float soma = 0, media, freq;
  int total = 0;

  for(i=0;i<std;i++){
    
    freq = calculaFrequencia(i);
    media = calculaMedia(i);
    
    if(media >= 7 && freq >= 60)
      total++;
  }

  return total;
}

//Função para listar alunos reprovados por media
void listarReprovadosMedia(int std, int rep){

  int i;
  float media;
  
  printf("\nAlunos reprovados por média: %d\n", rep);
  printf("\n| Lista de alunos  |\n");
  printf("|Matrícula - Media |\n");

  for(i=0;i<std;i++){
    media = calculaMedia(i);
    if(media < 7)
      printf(" %d    - %.1f\n", aluno[i], media);
  }
  
}

//Função para calcular a quantidade de alunos reprovados por média, ou seja média < 7
int reprovadosMedia(int std){
  int i, j, total = 0;
  float media;

  for(i=0;i<std;i++){
    media = calculaMedia(i);
    if(media < 7)
      total++;
  }

  return total;
}

//Função para listar os alunos reprovados por falta
void listarReprovadosFaltas(int std, int rep){
  int i, j;
  float freq;

  printf("\nAlunos reprovados por falta: %d", rep);
  printf("\n|    Lista de alunos    |\n");
  printf("|Matrícula - Frequência |\n");

  for(i=0;i<std;i++){
    freq = calculaFrequencia(i);

    if(freq<60){
      printf(" %d    - %.2f", aluno[i], freq);
    }
  }
}

//Função para calcular a quantidade de alunos reprovados por faltas
int reprovadosFaltas(int std){
  int i, j, total = 0;
  float freq;

  for(i=0;i<std;i++){
    freq = calculaFrequencia(i);
    if(freq < 60)
      total++;
  }

  return total;
}

//Função para excluir dados de aluno do vetor
void removerAluno(int mat){
  int i, aln, check;

  //Loop para identificar qual a posição do aluno no vetor
  for(i=0;i<30;i++){
    if(aluno[i] == mat){
      aln = i;
    }
  }

  mostraAluno(aln,mat);

  printf("\nDeseja realmente excluir o registro do aluno?\n");
  printf("1 - Confirmar\n");
  printf("2 - Cancelar\n");
  scanf("%d", &check);

  if(check == 1){
    aluno[aln] = 0;
    for(i=0;i<4;i++){  
      notas[aln][i] = 0;
    }
    faltas[aln] = 0;
    turma[aln] = 0;
    vagas++;

    organizaAlunos(aln);
    
    printf("\nAluno excluído do registro com sucesso!\n\n");
  }
}

//Função para atualizar dados de aluno no vetor
void atualizarAluno(int mat){
  
  //Variável aln irá armazenar a posição correspondente ao aluno no vetor
  int i, aln, option, option2;
  float newNotes[4];
  int newFault;
  //Loop para encontrar a posição do aluno no vetor
  for(i=0;i<30;i++){
    if(aluno[i] == mat){
      aln = i;
    }
  }
  
  //Chamando função que irá apresentar os dados atuais do aluno que deseja-se atualizar os dados
  mostraAluno(aln, mat);

  
  do{
  //Bloco para inserção de novos dados de aluno
  printf("\n| Inserir novos dados |\n");

  for(i=0;i<4;i++){
    printf("\nNota %d: ",(i+1));
    scanf("%f", &newNotes[i]);
    }

  printf("\nFaltas: ");
  scanf("%d", &newFault);


  //Bloco para check-in de novos dados de aluno
  printf("\n| Confirmando novos dados |");
  for(i=0;i<4;i++){
    printf("\nNota %d: %.1f",(i+1), newNotes[i]);
  }
  printf("\nFaltas: %d", newFault);

  printf("\n\nDigite uma das opções abaixo:");
  printf("\n1 - Confirmar");
  printf("\n2 - Inserir novamente");
  printf("\n");
  scanf("%d", &option);
  }while(option !=1);

  for(i=0;i<4;i++){
    notas[aln][i] = newNotes[i];
  }
  faltas[aln] = newFault;

  printf("\nAluno atualizado com sucesso!\n");
}

//Função auxiliar para calcular a media
float calculaMedia(int aln){
  int j;
  float media, soma = 0;
  
  for(j=0;j<4;j++){
    soma += notas[aln][j];
  }
  media = soma/4;

  return media;
}

//Função auxiliar para calcular a frequência
float calculaFrequencia(int aln){
  float freq;
  freq = ((maxClass - faltas[aln])/(float)maxClass)*100;
  
  return freq;
}

//Função para mostrar dados atuais de aluno
void mostraAluno(int aln, int mat){
  int i;
  
  printf("\n|  Dados atuais de aluno  |");
  printf("\n Matricula: %d", mat);
  
  for(i=0;i<4;i++){
    printf("\n Nota %d: %.1f", (i+1), notas[aln][i]);
  }
  printf("\n Faltas: %d", faltas[aln]);
  printf("\n Turma: %d", turma[aln]);
  printf("\n");
}

//Função para verificar se existe no vetor, um aluno com a matricula informada
bool buscaAluno(int aln){
  int i;
  bool findAln = false;

  for(i=0;i<30;i++){
    if(aln == aluno[i])
      findAln = true;
  }

  return findAln;
}

//Função para organizar vetor de modo que posições vazias ocupem o final do vetor
void organizaAlunos(int aln){
  int i, j;

  //Loop que a partir da posição atual compara se o próximo vetor está "vazio", ou seja, a matrícula é igual a 0, se for o caso, então ocorrerá uma permuta. Esse processo será repetido até a última posição do vetor aluno, para garantir que as posições vazias sempre estarão após as posições com cadastro de aluno
  for(i = aln;i<29;i++){
    if(aluno[i] == 0 && aluno[i+1] != 0){
      aluno[i] = aluno[i+1];
      faltas[i] = faltas[i+1];
      turma[i] = turma[i+1];
      for(j=0;j<4;j++){
        notas[i][j] = notas[i+1][j];
      }

      aluno[i+1] = 0;
      faltas[i+1] = 0;
      turma[i+1] = 0;
      for(j=0;j<4;j++){
        notas[i+1][j] = 0;
      }
    }
  }  
}