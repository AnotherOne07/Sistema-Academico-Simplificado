#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX 100

//Variavel global que faz referencia ao total de aulas
int maxClass = 36;

//Variável global que será utilizada para gerar a matrícula dos alunos automáticamente
int matricula = 2022000;

//Estrutura de dados para armazenar dados dos alunos
typedef struct{
  int matricula;
  char nome[50];
  float notas[4];
  int turma;
  int faltas;
}student;

student aluno[MAX];
int qtde;

//Funcionalidades de cadastro, atualização e remoção de alunos
// o parâmetro mat é utilizado para informar à função qual a matrícula do aluno
void cadastrarAluno();
void atualizarAluno(int mat);
void removerAluno(int mat);

//Funcionalidades de listagem
// o parâmetro std é utilizado para informar à função qual o numero de alunos do filtro em questão
// o parâmetro trm é utilizado para informar à função qual a turma 
void funcLista();
void listarAlunos(int std, int trm);
void listarAlunosGeral(int std);
void listarAprovados(int std, int apr, int trm);
void listarReprovadosMedia(int std, int rep, int trm);
void listarReprovadosFaltas(int std, int rep, int trm);
int alunosAprovados(int std, int trm);
int reprovadosMedia(int std, int trm);
int reprovadosFaltas(int std, int trm);

//Funcionalidades de ordenação
//Lembrando que o padrão adotado para o sistema é ordenar de forma crescente e a ordem
//padrão adotada é em função da matrícula, ou seja, dos mais antigos aos mais novos
void ordenaMatricula();
void ordenaAlunos(int ord);

//Funções de interação com o arquivo
void lerAlunos();
void gravarAlunos();

//Funções auxiliares
int alunosTurma(int trm);
float calculaMedia(int aln);
float calculaFrequencia(int aln);
void mostraAluno(int aln, int mat);
bool buscaAluno(int aln);
void organizaAlunos(int aln);

int main(){

  int option, mat;

  //Leitura dos dados de aluno
  lerAlunos();
  
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
        if(qtde < MAX){
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
        ordenaMatricula();
        gravarAlunos();
        break;
      default: //caso para quando usuário selecionar uma opção que não consta no menu
        printf("\nOpção inválida, selecione um número correspondente a uma das opções do menu\n");
        printf("\n");
        break;
    }
    
  }while(option != 0);
  
}

//Funcionalidade para cadastrar novos alunos no sistema
void cadastrarAluno(){
  int i = 0, j;
  
  //Variável que será utilizada para "confirmar" quando uma vaga for encontrada
  int findPos = 0;

  //Variável que será utilizada para "confirmar" um cadastro
  int isOk = 0;
  
  //Variáveis que armazenarão os dados informados "temporariamente"
  float notes[4];
  int fault, trm = 0;
  char name[50];
  
  do{
    if(aluno[i].matricula == 0){
      //Confirmação de que foi encontrada uma vaga
      findPos = 1;

      //Loop que permitirá ao usuário corrigir informações inseridas de um aluno
      while(isOk == 0){

        //Informar nome do aluno
        getchar();
        printf("\nInsira o nome do aluno: \n");
        fgets(name,50,stdin);

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

        //Validação da turma inserida
        do{  
          printf("\nInforme a turma do aluno: ");
          scanf("%d", &trm);

          if(trm == 0)
            printf("\nTurma inserida é inválida, digite novamente. \n");
        }while(trm == 0);

        //"Check-in" de informações inseridas pelo usuário
        printf("\n|  Confirmação  |\n");
        printf("\nNova matrícula: %d", (matricula+1));
        printf("\nNome: %s", name);
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
        qtde++;

        //Atribuição de dados
        strcpy(aluno[i].nome, name);
        aluno[i].matricula = matricula;
        for(j=0;j<4;j++){
          aluno[i].notas[j] = notes[j];
        }
        aluno[i].faltas = fault;
        aluno[i].turma = trm;
        
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

void atualizarAluno(int mat){
  
  //Variável aln irá armazenar a posição correspondente ao aluno no vetor
  int i, aln, option, option2;
  float newNotes[4];
  int newFault;
  student a;
  a.matricula = mat;
  
  //Loop para encontrar a posição do aluno no vetor
  for(i=0;i<30;i++){
    if(aluno[i].matricula == mat){
      aln = i;
    }
  }
  
  //Chamando função que irá apresentar os dados atuais do aluno que deseja-se atualizar os dados
  mostraAluno(aln, mat);

  do{
    //Bloco para inserção de novos dados de aluno
    printf("\n| Inserir novos dados |\n");
  
    for(i=0;i<4;i++){
       do{
        printf("\nNota %d: ",(i+1));
        scanf("%f", &a.notas[i]);
  
        if(a.notas[i]<0 || a.notas[i]>10){
          printf("Nota inserida é inválida. Digite uma nota maior que 0 e menor que 10");
        }
        }while(a.notas[i]<0 || a.notas[i]>10);
    }
  
    printf("\nFaltas: ");
    scanf("%d", &a.faltas);
  
  
    //Bloco para check-in de novos dados de aluno
    printf("\n| Confirmando novos dados |");
    for(i=0;i<4;i++){
      printf("\nNota %d: %.1f",(i+1), a.notas[i]);
    }
    printf("\nFaltas: %d", a.faltas);
  
    printf("\n\nDigite uma das opções abaixo:");
    printf("\n1 - Confirmar");
    printf("\n2 - Inserir novamente");
    printf("\n");
    scanf("%d", &option);
  }while(option !=1);

  //Atribuição de dados ao vetor aluno
  for(i=0;i<4;i++){
    aluno[aln].notas[i] = a.notas[i];
  }
  aluno[aln].faltas = a.faltas;

  printf("\nAluno atualizado com sucesso!\n");
}

//Função para mostrar dados atuais de aluno
void mostraAluno(int aln, int mat){
  int i;
  
  printf("\n|  Dados atuais de aluno  |");
  printf("\n Nome: %s", aluno[aln].nome);
  printf("\n Matricula: %d", mat);
  
  for(i=0;i<4;i++){
    printf("\n Nota %d: %.1f", (i+1), aluno[aln].notas[i]);
  }
  printf("\n Faltas: %d", aluno[aln].faltas);
  printf("\n Turma: %d", aluno[aln].turma);
  printf("\n");
}

//Função para verificar se existe no vetor, um aluno com a matricula informada
bool buscaAluno(int mat){
  int i;
  bool findAln = false;

  for(i=0;i<30;i++){
    if(mat == aluno[i].matricula)
      findAln = true;
  }

  return findAln;
}

//Função para exibir o menu com as opções de listas
void funcLista(){
  int option, i, j, option2;
  
  do{
  printf("\nSelecione uma das opções a seguir: \n");
  printf("\n");
  printf("1 - Listar todos os alunos cadastrados\n");
  printf("2 - Listar alunos aprovados\n");
  printf("3 - Listar alunos reprovados por media\n");
  printf("4 - Listar alunos reprovados por faltas\n");
  printf("5 - Ordenar dados de alunos\n");
  printf("0 - Retornar ao menu principal\n");
  scanf("%d", &option);
  
  if(qtde > 0 || option == 0){

    //Variáveis que poderão ser usadas durante os casos
    int aprovados, reprovadosM, reprovadosF, trm, alnTurma, askOrd;
    
    if(option != 0 && option != 1 && option != 5){
      printf("\nInforme a turma: ");
      scanf("%d", &trm);
    }

    // printf("\nDeseja definir uma regra ordenação para os dados?");
    // printf("\n1 - SIM  // 2 - NÃO\n");
    // scanf("%d", &askOrd);
    
    switch(option){
      case 1:
        printf("\nSelecione uma opção abaixo: ");
        printf("\n1 - Filtrar por turma");
        printf("\n2 - Exibir todos\n");
        scanf("%d", &option2);

        if(option2 == 1){
          printf("\nInforme a turma: ");
          scanf("%d", &trm);
          
          alnTurma = alunosTurma(trm);
          
          if(alnTurma > 0)
            listarAlunos(qtde, trm);
          else
            printf("\nNão há nenhum aluno cadastrado na turma informada");
          
        }else{
          listarAlunosGeral(qtde);
        }
        //ordenaMatricula();
        break;
      case 2:
        aprovados = alunosAprovados(qtde, trm);
        if(aprovados>0)
          listarAprovados(qtde, aprovados, trm);
        else{
          printf("\nNão há nenhum aluno aprovado!\n");
        }
        //ordenaMatricula();
        break;
      case 3: 
        reprovadosM = reprovadosMedia(qtde, trm);
        if(reprovadosM>0)
          listarReprovadosMedia(qtde, reprovadosM, trm);
        else{
          printf("\nNão há nenhuma aluno reprovado por media!\n");
        }
        //ordenaMatricula();
        break;
      case 4:
        reprovadosF = reprovadosFaltas(qtde, trm);
        if(reprovadosF>0)
          listarReprovadosFaltas(qtde,reprovadosF,trm);
        else{
          printf("\nNão há nenhum aluno reprovado por faltas!\n");
          printf("\n");
        }
        //ordenaMatricula();
        break;
      case 5:
        printf("\nInforme o critério de ordenação que deve ser aplicado");
        printf("\n0 - Matrícula");
        printf("\n1 - Nome");
        printf("\n2 - Média");
        printf("\n3 - Faltas\n");
        scanf("%d", &askOrd);

        if(askOrd == 0)
          ordenaMatricula();
        else
          ordenaAlunos(askOrd);
        
        break;
    }
  }else{
          printf("\nNão há nenhum aluno cadastrado!\n");
          printf("\n");
  }
    
  }while(option != 0);
  
}

//Função para listar todos os alunos cadastrados em uma turma
void listarAlunos(int std, int trm){
  int i, j;
  int alnTurma;
  alnTurma = alunosTurma(trm);
  printf("\nAlunos encontrados: %d", alnTurma);
  printf("\n|                Lista de alunos                |\n");
  printf("|Matrícula - Turma - N1 / N2 / N3 / N4 - Faltas - Nome |\n");
  
  for(i=0;i<std;i++){

    if(aluno[i].turma == trm)
      printf("|%d   - %d  - %.1f / %.1f / %.1f / %.1f - %d - %s  \n", aluno[i].matricula, aluno[i].turma ,aluno[i].notas[0], aluno[i].notas[1], aluno[i].notas[2], aluno[i].notas[3],  aluno[i].faltas,  aluno[i].nome);
    
    }
}

void listarAlunosGeral(int std){
  int i, j;
  
  printf("\nAlunos encontrados: %d", std);
  printf("\n|                Lista de alunos                |\n");
  printf("|Matrícula - Turma - N1 / N2 / N3 / N4 - Faltas - Nome |\n");
  
  for(i=0;i<std;i++){

      printf("|%d   - %d  - %.1f / %.1f / %.1f / %.1f - %d - %s  \n", aluno[i].matricula, aluno[i].turma ,aluno[i].notas[0], aluno[i].notas[1], aluno[i].notas[2], aluno[i].notas[3],  aluno[i].faltas,  aluno[i].nome);
    
    }
}

//Função para listar alunos aprovados
void listarAprovados(int std, int apr, int trm){
  int i, j;
  float media, frequencia;

  printf("\nTurma %d", trm);
  printf("\nAlunos aprovados: %d", apr);
  printf("\n|        Lista de alunos          |\n");
  printf("|Matrícula - Media - Frequencia |\n");

  for(i=0;i<std;i++){
    media = calculaMedia(i);
    frequencia = calculaFrequencia(i);
    if(media >= 7 && frequencia >= 60 && aluno[i].turma == trm)
      printf(" %d    - %.1f - %.2f \n",aluno[i].matricula, media, frequencia);
  }
}

//Função para calcular a quantidade de alunos aprovados
int alunosAprovados(int std, int trm){
  int i, j; 
  float soma = 0, media, freq;
  int total = 0;

  for(i=0;i<std;i++){
    
    freq = calculaFrequencia(i);
    media = calculaMedia(i);
    
    if(media >= 7 && freq >= 60 && aluno[i].turma == trm)
      total++;
  }

  return total;
}

//Função para listar alunos reprovados por media
void listarReprovadosMedia(int std, int rep, int trm){

  int i;
  float media;

  printf("\nTurma: %d", trm);
  printf("\nAlunos reprovados por média: %d\n", rep);
  printf("\n| Lista de alunos  |\n");
  printf("|Matrícula - Media |\n");

  for(i=0;i<std;i++){
    media = calculaMedia(i);
    if(media < 7 && aluno[i].turma == trm)
      printf(" %d    - %.1f\n", aluno[i].matricula, media);
  }
  
}

//Função para calcular a quantidade de alunos reprovados por média, ou seja média < 7
int reprovadosMedia(int std, int trm){
  int i, j, total = 0;
  float media;

  for(i=0;i<std;i++){
    media = calculaMedia(i);
    if(media < 7 && aluno[i].turma == trm)
      total++;
  }

  return total;
}

//Função para listar os alunos reprovados por falta
void listarReprovadosFaltas(int std, int rep, int trm){
  int i, j;
  float freq;

  printf("\nTurma: %d", trm);
  printf("\nAlunos reprovados por falta: %d", rep);
  printf("\n|    Lista de alunos    |\n");
  printf("|Matrícula - Frequência |\n");

  for(i=0;i<std;i++){
    freq = calculaFrequencia(i);

    if(freq<60 && aluno[i].turma == trm){
      printf(" %d    - %.2f", aluno[i].matricula, freq);
    }
  }
}

//Função para calcular a quantidade de alunos reprovados por faltas
int reprovadosFaltas(int std, int trm){
  int i, j, total = 0;
  float freq;

  for(i=0;i<std;i++){
    freq = calculaFrequencia(i);
    if(freq < 60 && aluno[i].turma == trm)
      total++;
  }

  return total;
}

//Função para ordenar alunos em função da sua matrícula
void ordenaMatricula(){
  int i, j;
  student a;
  
  for(i=0;i<(qtde-1);i++){
    for(j=0;j<(qtde-i);j++){
      if(aluno[j].matricula > aluno[j+1].matricula && (aluno[j].matricula != 0 && aluno[j+1].matricula != 0)){
        a = aluno[j+1];
        aluno[j+1] = aluno[j];
        aluno[j] = a;
      }
    }
  }
}

//Função para ordenar alunos em função do critério de ordem informado
void ordenaAlunos(int ord){
  int i, j;
  student a;
  float media1, media2;

  //Em função do nome
  if(ord == 1){
    for(i=0;i<(qtde);i++){
      for(j=0;j<(qtde-i);j++){
        if(strcmp(aluno[j].nome, aluno[j+1].nome) > 0 && (aluno[j].matricula != 0 && aluno[j+1].matricula != 0)){
          a = aluno[j+1];
          aluno[j+1] = aluno[j];
          aluno[j] = a;
        }
      }
    }
  }//em função da média
  else if (ord == 2){
    for(i=0;i<(qtde);i++){
      for(j=0;j<(qtde-i);j++){
        media1 = calculaMedia(j);
        media2 = calculaMedia(j+1);
        if(media1>media2 && (aluno[j].matricula != 0 && aluno[j+1].matricula != 0)){
          a = aluno[j+1];
          aluno[j+1] = aluno[j];
          aluno[j] = a;
        }
      }
    }
  }//em função da quantidade de faltas
  else if (ord == 3){
    for(i=0;i<(qtde);i++){
      for(j=0;j<(qtde-i);j++){
        if(aluno[j].faltas > aluno[j+1].faltas && (aluno[j].matricula != 0 && aluno[j+1].matricula != 0)){
          a = aluno[j+1];
          aluno[j+1] = aluno[j];
          aluno[j] = a;
        }
      }
    }
  }
}

//Função para excluir dados de aluno do vetor
void removerAluno(int mat){
  int i, aln, check;

  //Loop para identificar qual a posição do aluno no vetor
  for(i=0;i<30;i++){
    if(aluno[i].matricula == mat){
      aln = i;
    }
  }

  mostraAluno(aln,mat);

  printf("\nDeseja realmente excluir o registro do aluno?\n");
  printf("1 - Confirmar\n");
  printf("2 - Cancelar\n");
  scanf("%d", &check);

  if(check == 1){
    aluno[aln].matricula = 0;
    for(i=0;i<4;i++){  
      aluno[aln].notas[i] = 0;
    }
    aluno[aln].faltas = 0;
    aluno[aln].turma = 0;
    qtde--;

    organizaAlunos(aln);
    
    printf("\nAluno excluído do registro com sucesso!\n\n");
  }
}

//Função para contar a quantidade de alunos por turma
int alunosTurma(int trm){
  int i, j, alunos = 0;

  for(i=0;i<MAX;i++){
    if(aluno[i].turma == trm)
      alunos++;
  }

  return alunos;
}

//Função para ler dados salvos no arquivo de alunos
void lerAlunos(){
  
  FILE *arch;
  int i = 0;
  arch = fopen("alunos.txt","r");

  if(arch == NULL)
    printf("\nERRO! Não foi possível abrir o arquivo.\n");
  else{
    while(fscanf(arch,"%d %d %f %f %f %f %d %s\n", &aluno[i].matricula, &aluno[i].turma , &aluno[i].notas[0], &aluno[i].notas[1], &aluno[i].notas[2], &aluno[i].notas[3], &aluno[i].faltas, aluno[i].nome) != EOF)
      i++;
    fclose(arch);
  }
  qtde = i;
  if(qtde>0)
    matricula = aluno[qtde-1].matricula;
}

//Função de encerramento de sessão, que irá gravar os dados atualizados de alunos
void gravarAlunos(){

  FILE *arch;
  arch = fopen("alunos.txt", "w");

  for(int i = 0;i<qtde;i++)
    fprintf(arch, "%d %d %f %f %f %f %d %s \n", aluno[i].matricula, aluno[i].turma , aluno[i].notas[0], aluno[i].notas[1], aluno[i].notas[2], aluno[i].notas[3], aluno[i].faltas , aluno[i].nome);

  fclose(arch);
}

//Função auxiliar para calcular a media
float calculaMedia(int aln){
  int j;
  float media, soma = 0;
  
  for(j=0;j<4;j++){
    soma += aluno[aln].notas[j];
  }
  media = soma/4;

  return media;
}

//Função auxiliar para calcular a frequência
float calculaFrequencia(int aln){
  float freq;
  freq = ((maxClass - aluno[aln].faltas)/(float)maxClass)*100;
  
  return freq;
}

//Função para organizar vetor de modo que posições vazias ocupem o final do vetor
void organizaAlunos(int aln){
  int i, j;
 
  //Loop que a partir da posição atual compara se o próximo vetor está "vazio", ou seja, a matrícula é igual a 0, se for o caso, então ocorrerá uma permuta. Esse processo será repetido até a última posição do vetor aluno, para garantir que as posições vazias sempre estarão após as posições com cadastro de aluno
  for(i = aln;i<MAX;i++){
    if(aluno[i].matricula == 0 && aluno[i+1].matricula != 0){
      aluno[i] = aluno[i+1];

      //"Limpando" a próxima posição do vetor
      aluno[i+1].matricula = 0;
      aluno[i+1].faltas = 0;
      aluno[i+1].turma = 0;
      for(j=0;j<4;j++){
        aluno[i+1].notas[j] = 0;
      }
    }
  }  
}