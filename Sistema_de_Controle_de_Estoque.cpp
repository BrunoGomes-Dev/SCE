#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>

//Pausa a tela por alguns segundos
void pause(int a){	
	time_t x, y;
	time(&x);
	time(&y);
	
	while(y - x < a) time(&y);
}

//Limpa a tela em Windows, Linux ou Mac
void limpa(){
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

//Teste se o arquivo foi aberto e se o programa poderá ser executado
void teste(FILE *arquivo){
	if(arquivo == NULL){
		fclose(arquivo);
		printf("Falha na execucao do programa. Saia e tente novamente\n");
		pause(5);
		exit(0);
	}
}

//Retorna qual operacao o usuario deseja
int operacao(){
	printf("\n");
	FILE *arquivo = fopen("operacoes.txt", "r");
	int escolha;	
	teste(arquivo);
	
	//Exibe as operacoes disponiveis
	while(feof(arquivo) == 0){
		char c = fgetc(arquivo);
		printf("%c", c);
	}
	
	//Retorna a operacao que o usuario deseja
	printf("\n");
	scanf("%d", &escolha);
	
	limpa();
	
	return escolha;
}

//Operacao 1
void lista(){
	FILE *arquivo = fopen("estoque.txt", "r");
	teste(arquivo);
	int k = 50, i = 0; 
	char s[] = "						       ";
	printf("Nome %s Quantidade\n\n", s);
	while(feof(arquivo) == 0){
		char c = fgetc(arquivo);
		if(c == ' ') {
			for(int j = 0; j < 56 - i; j++){
				printf(" ");
			}	
			i = 0;
		} else { 
			printf("%c", c);
			i++;
			if(c == '\n') i = 0;
		}
	}
	fclose(arquivo);
}

//Operacao 2
void adiciona(){
	FILE *arquivo = fopen("estoque.txt", "a");
	teste(arquivo);
	int quan;
	printf("Quantos produtos deseja inserir? ");
	scanf("%d", &quan);
	for(int i = 0; i < quan; i++){
		char a[53], b[53];
		printf("\nInsira o nome do produto(no maximo 52 caracteres, sem espaco e sem acento. Nao coloque numero no inicio do nome): ");
		scanf("%s", &a);
		printf("Insira a quantidade do produto: ");
		scanf("%s", &b);
		fprintf(arquivo, "%s %s\n", a, b);
	}
	fclose(arquivo);
}

//Operacao 3
void remover(){
	FILE *arquivo = fopen("estoque.txt", "r");
	teste(arquivo);
	
	int i = 1, removido;
	bool tesk = false;
	std::string a = "", b(1, '\0');
	
	while(true){
		b[0] = fgetc(arquivo);
		if(feof(arquivo)) break;
		if(i == 1 || tesk){
		 	printf("%d. ", i);
			tesk = false;
			i++;
		}
		if(b[0] != ' '){
			printf("%c", b[0]);
		} else {
			while(b[0] != '\n'){
				b[0] = fgetc(arquivo);
			}
			printf("%c", b[0]);
			tesk = true;
		}
	}
	printf("%d. Anular operacao!", i);
	printf("\n\nInsira o numero do item que deseja remover: ");
	scanf("%d", &removido);
	i = 1;
	
	fclose(arquivo);
	arquivo = fopen("estoque.txt", "r");
	
	//Buscando o elemento que a pessoa deseja remover;
	while(true){
		b[0] = fgetc(arquivo);
		if(feof(arquivo)) break;
		if(i == removido){
			while(b[0] != '\n' && !feof(arquivo)){
				b[0] = fgetc(arquivo);
			}
			i++;
		} else {
			if(b[0] == '\n') i++;
			a += b[0];
		}
	}
	fclose(arquivo);
	
	arquivo = fopen("estoque.txt", "w");
	fprintf(arquivo, "%s", a.c_str());
	
	fclose(arquivo);
}

//Operacao 4
void instrucao(){
	FILE *arquivo = fopen("instrucoes.txt", "r");
	teste(arquivo);
	char x[10000];
	
	while(feof(arquivo) == 0){
		char c = fgetc(arquivo);
		printf("%c", c);
	}
	
	pause(3);
	printf("\n\nInsira um numero e aperte enter para continuar\n");
	scanf("%s", &x);
	limpa();
}

//Codigo principal para executar o programa
int main(){
	instrucao();
	printf("Bem vindo ao sistema de controle de estoque");
		
	int x = operacao();
	
	//Execucao do programa
	while(x != 5){
		if(x == 1) lista();
		else if(x == 2) adiciona();
		else if(x == 3) remover();
		else if(x == 4) instrucao();
		else printf("Escolha uma operacao valida!\n");
		x = operacao();
	}
	
	printf("\nObrigado por usar!\n");
	pause(3);
	
	return 0;
}
