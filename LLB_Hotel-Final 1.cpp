/*
LLB_Exp-Hotel
Lucas Lombardi de Brito 10/06/22
MAMM_Exp-Hotel
Mateus Araujo de Melo Morais
BBPG_Exp-Hotel
Beatriz Bellini Prado Garcia
*/
#include <stdio.h>
#include <string.h>

void fcancela(int andar, int quarto, struct hotel mapa[20][14]);
void fcheckin(struct hotel mapa[20][14]);
void fcheckout(struct hotel mapa[20][14]);
void fmapa(struct hotel mapa[20][14]);
void freserva(struct hotel mapa [20][14]);
void fcancelareserva(struct hotel mapa[20][14]);
void fpegadados(int Andar, int Quarto, struct hotel mapa[20][14]);
void fmostradados(struct hotel mapa[20][14]);
void ftaxa(struct hotel mapa[20][14]);
void fclear();
int testaformatoCPF(char cpf[]);
int medetamanhoCPF(char cpf[]);
int calculoCPF(int n[]);
int validadeCPF(char CPF[13]);
int testaTelefone(char tel[10]);
int comparaDados(int andar, int quarto, struct hotel mapa[20][14]);

struct hotel
	{
	char status;
	char nome[50];
	char cel[10]; // nao foi considerado o DDD
	char cpf[13]; // por estar no formato XXXXXXXXX-XX
	char endereco[100];
	char email[60];
	};
	
main()
{
	int j; //j e o seletor
	int Andar,Quarto;
	struct hotel mapa[20][14];
	for(Andar=0; Andar < 20; Andar++)	//preenche todos os espacos do mapa (matriz) com '.'
		for(Quarto=0; Quarto < 14; Quarto++)
				mapa[Andar][Quarto].status ='.';
	do
	{
		printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-Menu-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
		printf("O que deseja fazer ?\n");
		printf("(1) - Realizar Check-in\n");
		printf("(2) - Realizar Check-out\n");
		printf("(3) - Reservar um quarto\n");
		printf("(4) - Cancelar uma reserva\n");
		printf("(5) - Mapa de ocupacao e reservas do hotel\n");
		printf("(6) - Informacoes do hospede\n");
		printf("(7) - Mostrar a taxa de ocupacao e reservas do hotel\n");
		printf("(8) - Sair do Programa\n");
		printf("Digite o numero: ");
		scanf("%d",&j);
		printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
		if(j == 8)
			break;
		switch(j)
		{
			case 1: 
				fcheckin(mapa);
				break;
			case 2:
				fcheckout(mapa);
				break;
			case 3:	
				freserva(mapa);
				break;
			case 4:
				fcancelareserva(mapa);
				break;
			case 5:
				fmapa(mapa);
				break;
			case 6:
				fmostradados(mapa);
				break;
			case 7:
				ftaxa(mapa);
				break;
			default:	
				break;
		}
			
	}
	while(1);
}
// funcao criada para colocar um '.' no local onde sera feito o cancelamento
// essa funcao sera utilizada em todas as funcoes que serao efetuadas algum cancelamento
void fcancela(int andar, int quarto, struct hotel mapa[20][14])
{
	mapa[andar-1][quarto-1].status = '.';
}
//permite o usuario fazer check-in no hotel
void fcheckin(struct hotel mapa[20][14])
{
	printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-Check-in-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
	int Andar,Quarto;
	//coloca o 'O' de Ocupado no mapa de acordo com o quarto escolhido pelo usuario
	printf("Digite o Andar e o Quarto que deseja ocupar (formato: Andar,Quarto): ");
	scanf("%d,%d",&Andar,&Quarto);
	if ( Andar < 1 || Andar > 20 || Quarto < 1 || Quarto > 14)
	{
		printf("\nEsse quarto nao existe, por favor escolha outro\n\n");
		printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
	}
	else if(mapa[Andar-1][Quarto-1].status == 'O')
	{
		printf("\n\nQuarto ocupado, por favor escolha outro\n\n");
		printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
	}
	else if (mapa[Andar-1][Quarto-1].status == 'R')
		{
			if(comparaDados(Andar,Quarto,mapa) != 1)
				{
					printf("\nO dado fornecido nao e igual ao fornecido anteriormente na reserva\n");
					printf("Nao sera possivel realizar o Check-in\n");
					printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
				}
			else
				{
					mapa[Andar-1][Quarto-1].status = 'O';
					printf("\nQuarto ocupado com sucesso\n\n");
					printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
				}
		}
	else
		{
		mapa[Andar-1][Quarto-1].status = 'O';
		fpegadados(Andar,Quarto,mapa);
		printf("\nQuarto ocupado com sucesso\n\n");
		printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
		}
}
// permite o usuario fazer check-out do hotel
// coloca um '.' no local escolhido pelo usuario
void fcheckout(struct hotel mapa[20][14])
{
	printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-Check-out-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
	int Andar,Quarto;
	printf("Vai realizar Check-out de qual quarto (formato: Andar,Quarto)?");
	scanf("%d,%d",&Andar,&Quarto);
	if ( Andar < 1 || Andar > 20 || Quarto < 1 || Quarto > 14)
	{
		printf("Esse quarto nao existe, por favor escolha outro\n\n");
		printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
	}
	else if(mapa[Andar-1][Quarto-1].status == 'R')
	{
		printf("\n\nNao e possivel realizar Check-out de um quarto reservado, por favor escolha outro\n\n");
		printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
	}
	else if(mapa[Andar-1][Quarto-1].status == '.')
	{
		printf("\n\nNao e possivel realizar Check-out de um quarto que nao foi ocupado, por favor escolha outro\n\n");
		printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
	}
	else
	{
		fcancela(Andar,Quarto,mapa);
		printf("\nCheck-out realizado com sucesso\n\n");
		printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
	}
}
// apresenta a matriz do hotel, no caso o mapa
void fmapa(struct hotel mapa[20][14])
{
	printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-Mapa Atual de Ocupacao-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
	int Andar, Quarto;
	printf("Os simbolos do mapa significam:\n");
	printf("Quarto ocupado : O\n");
	printf("Quarto reservado : R\n");
	printf("Quarto livre : .\n");
	//Numero da Coluna
	printf("quartos -->    \t");
	for(int Quarto = 0; Quarto < 14; Quarto++)
		printf("%2d ",Quarto+1);
	printf("\n\n");
	//resto da matriz
	for(Andar=19; Andar >= 0 ; Andar--) //foi feito dessa forma para inverter a apresentacao da matriz verticalmente
	{	
	printf("Andar %2d :\t",Andar+1); //Numero da linha
	for(Quarto=0; Quarto < 14; Quarto++)
		printf(" %c ",mapa[Andar][Quarto].status);
	printf("\n");
	}
	printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
}
//permite o usuario fazer uma reserva
void freserva(struct hotel mapa [20][14])
{
	printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-Reserva de Quarto-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
	int Andar, Quarto;
	//coloca o 'R' de reservado no mapa de acordo com os quartos escolhidos pelo usuario
	printf("Digite o Andar e o Quarto que deseja reservar (formato: Andar,Quarto): ");
	scanf("%d,%d",&Andar,&Quarto);
	if ( Andar < 1 || Andar > 20 || Quarto < 1 || Quarto > 14)
	{
		printf("\nEsse quarto nao existe, por favor escolha outro\n\n");
		printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
	}
	else if(mapa[Andar-1][Quarto-1].status == 'O')
	{
		printf("\n\nQuarto ja ocupado, por favor escolha outro\n\n");
		printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
	}
	else if(mapa[Andar-1][Quarto-1].status == 'R')
	{
		printf("\n\nQuarto ja reservado, por favor escolha outro\n\n");
		printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
	}
	else
	{
		mapa[Andar-1][Quarto-1].status = 'R';
		fpegadados(Andar,Quarto, mapa);
		printf("\nQuarto reservado com sucesso\n\n");
		printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
	}
}
//cancela uma reserva de acordo com o local indicado pelo usuario
void fcancelareserva(struct hotel mapa[20][14])
{
	printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-Cancelamento de Reserva-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
	int Andar, Quarto;
	printf("Deseja cancelar a reserva de qual quarto (formato: Andar,Quarto)?");
	scanf("%d,%d",&Andar,&Quarto);
	if ( Andar < 1 || Andar > 20 || Quarto < 1 || Quarto > 14)
	{
		printf("\nEsse quarto nao existe, por favor escolha outro\n\n");
		printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
	}
	else if(mapa[Andar-1][Quarto-1].status == 'O')
	{
		printf("\n\nNao e possivel cancelar a reserva de um quarto ocupado, por favor escolha outro\n\n");
		printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
	}
	else if(mapa[Andar-1][Quarto-1].status == '.')
	{
		printf("\n\nNao e possive cancelar a reserva de um quarto que nao foi reservado, por favor escolha outro\n\n");
		printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
	}
	else
	{
		fcancela(Andar,Quarto,mapa);
		printf("\nReserva cancelada com sucesso\n\n");
		printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
	}
}
//limpeza de Buffer do teclado
void fclear()
{
	char carac;
    while( (carac = fgetc(stdin)) != EOF && carac != '\n') {}
}
//mostra os dados de um hospede de acordo com o quarto escolido pelo usuario
void fmostradados(struct hotel mapa[20][14])
{
	printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-Dados do Hospede-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
	int Andar,Quarto;
	printf("\nDigite o andar e o quarto para obter as informacoes do hopede (formato: Andar,Quarto): ");
	scanf("%d,%d",&Andar,&Quarto);
	if ( Andar < 1 || Andar > 20 || Quarto < 1 || Quarto > 14)
	{
		printf("\nEsse quarto nao existe, por favor escolha outro\n\n");
		printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
	}
	else if(mapa[Andar-1][Quarto-1].status == '.')
	{
		printf("\nQuarto nao ocupado\n");
		printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
	}
	else if(mapa[Andar-1][Quarto-1].status == 'O')
	{
		printf("\nDADOS DE QUEM ESTA OCUPANDO O QUARTO: ");
		printf("\nNome :%s",mapa[Andar-1][Quarto-1].nome);
		printf("\nTelefone: %s",mapa[Andar-1][Quarto-1].cel);
		printf("\nCPF: %s",mapa[Andar-1][Quarto-1].cpf);
		printf("\nEndereco: %s",mapa[Andar-1][Quarto-1].endereco);
		printf("\ne-mail: %s\n\n",mapa[Andar-1][Quarto-1].email);
		printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
	}
	else
	{
		printf("\nDADOS DE QUEM RESERVOU O QUARTO");
		printf("\nNome :%s",mapa[Andar-1][Quarto-1].nome);
		printf("\nTelefone: %s",mapa[Andar-1][Quarto-1].cel);
		printf("\nCPF: %s",mapa[Andar-1][Quarto-1].cpf);
		printf("\nEndereco: %s",mapa[Andar-1][Quarto-1].endereco);
		printf("\ne-mail: %s\n\n",mapa[Andar-1][Quarto-1].email);
		printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
	}
}
//pega os dados do usuario que esta reservando ou ocupando um quarto
void fpegadados(int Andar, int Quarto, struct hotel mapa[20][14])
{
		fclear();
		printf("\nDigite seu nome completo: ");
		gets(mapa[Andar-1][Quarto-1].nome);
		
		do
		{
			printf("\nDigite seu telefone (sem DDD): ");
			gets(mapa[Andar-1][Quarto-1].cel);
			if(testaTelefone(mapa[Andar-1][Quarto-1].cel) != 1) // Foi necessario fazer esse teste duas vezes
				printf("Telefone Invalido");                    // para que o usuario seja notificado de que o telefone
		}while(testaTelefone(mapa[Andar-1][Quarto-1].cel) != 1);// estava errado
	
		do
		{
			printf("\nDigite seu CPF (formato: XXXXXXXXX-XX): ");
			gets(mapa[Andar-1][Quarto-1].cpf);
			if(validadeCPF(mapa[Andar-1][Quarto-1].cpf) != 1) // A situacao e a mesma que a de cima
				printf("CPF invalido");                       // o usuario precisa ser notificado de que o cpf nao e valido
		}while(validadeCPF(mapa[Andar-1][Quarto-1].cpf) != 1);

		printf("\nDigite seu endereco: ");
		gets(mapa[Andar-1][Quarto-1].endereco);
		
		printf("\nDigite seu e-mail: ");
		gets(mapa[Andar-1][Quarto-1].email);
}
//calcula a taxa de ocupacao e a taxa de reserva do hotel
void ftaxa(struct hotel mapa[20][14])
{
	printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-Taxa de ocupacao e reserva-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
	int contadorR, contadorO;
	contadorR = 0; // contador de quartos reservados
	contadorO = 0; // contador de quartos ocupados
	for(int Andar=0; Andar < 20; Andar++)
		for(int Quarto=0; Quarto < 14; Quarto++)
		{
			switch (mapa[Andar][Quarto].status)
			{
				case 'O':
					contadorO++;
					break;
				case 'R':
					contadorR++;
					break;
				default:
					break;
			}
		}
	printf("\nA taxa de ocupacao do hotel e: %5.2f %%\n",(contadorO*100.0)/(20*14));
	printf("\nA taxa de reserva do hotel e: %5.2f %%\n",(contadorR*100.0)/(20*14));
	printf("\nTotal: %5.2f %%\n\n",((contadorO*100.0)/(20*14))+((contadorR*100.0)/(20*14)));
	printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
}

// testa se o formato do CPF esta correto
// 0 e falso e 1 verdadeiro
int testaformatoCPF(char cpf[])
{
	for(int j = 0; cpf[j] != '\0'; j++)
		{
		if(j==9) //testa se o decimo digito colocado pelo usuario e '-'
			{
				if(cpf[j] != '-')
					return 0;
			}
		else if(cpf[j] < '0' || cpf[j] > '9') //testa se todos os digitos (com excecao do decimo) sao numeros
			return 0;
		}
	return 1;
}

// a funcao mede o tamanho do cpf que o usuario colocou
// 0 para excesso de caracteres
// 2 para falta de caracteres
// 1 para o tamanho correto
int medetamanhoCPF(char cpf[])
{
	int i=0;
	while(cpf[i] != '\0')
		i++;
	if(i > 12)
		return 0;
	else if(i < 12)
		return 2;
	else
		return 1;
}

// calcula os ultimos digitos do CPF de acordo com a forma correta
// e depois compara com os ultimos digitos colocados pelo usuario
// 0 --> CPF invalido
// 1 --> CPF valido
int calculoCPF(int n[])
{
	int i,valor,soma1,resto,digito9,digito10,soma2,soma3;
	// calculo do digito 9
	valor = 10;
	i = 0;
	soma1 = 0;
	while(valor >= 2)
		{
			soma1 = valor*n[i] + soma1;
			valor--;
			i++;
		}
	
	resto = soma1%11;
	if(resto < 2)
		digito9 = 0;
	else
		digito9 = 11-resto;
	// valores redefinidos para calcular a soma 2 usada para calcular o digito 10
	i = 0;
	valor = 11;
	soma2 = 0;
	while(valor >= 3)
		{
			soma2 = valor*n[i] + soma2;
			valor--;
			i++;
		}
	soma3 = 2*n[9] + soma2;
	resto = soma3%11;
	if(resto < 2 )
		digito10 = 0;
	else
		digito10 = 11-resto;
	
	// comparacao dos valores calculados com os valores fornecidos pelo usuario

	if(digito9 == n[9] && digito10 == n[10])
		return 1;
	else
		return 0;
}

// a funcao utiliza de outras funcoes para verificar se o CPF e valido
// 0 nao e valido
// 1 e valido
int validadeCPF(char CPF[13])
{
	int retorno;
	int n[11]; // os caracteres serao passados para valores numericos e serao armazenados aqui
	if(testaformatoCPF(CPF) != 1)
		return 0;
	else if(medetamanhoCPF(CPF) == 0)
		return 0;
	else if(medetamanhoCPF(CPF) == 2)
		return 0;
	//transforma os caracteres alfanumericos em valores numericos
	for(int i=0; i <= 12;i++)
	{
		if(i == 9)
			continue; // como o numero 9 e o hifen ele deve ser pulado
		else if(i > 9)  // e para continuar a sequencia sem pular nenhum digito e necessario que a partir daqui
			n[i-1] = CPF[i] - 48; // sejam colocados em n[i-1]
		else
			n[i] = CPF[i] - 48;
		}
	retorno = calculoCPF(n);
	return (retorno);
}

// testa se o formato do telefone colocado pelo usuario esta correto
// 0 = incorreto
// 1 = correto
int testaTelefone(char tel[10])
{
	for(int i = 0; i < 9;i++)
	{
		if(tel[i] < '0' || tel[i] > '9') //testa se todos os digitos sao numeros
		return 0;
	}
	return 1;
}

//compara se os dados colocados pelo usuario sao iguais na reserva e no check-in
// 1 para dados iguais
// 0 para dados diferentes
int comparaDados(int andar, int quarto, struct hotel mapa[20][14])
{
	char NOME[50];
	char CEL[10];
	char CPF[13]; 
	char ENDERECO[100];
	char EMAIL[60];
	int retorno;

	fclear();
	printf("\nDigite seu nome completo: ");
	gets(NOME);
	retorno = strcmp(NOME,mapa[andar-1][quarto-1].nome);
	if(retorno != 0)
		return 0;

	// aqui nao havera teste de validade de CPF ou telefone porque ja se pressupoe que
	// quando a reserva foi realizada o usuario ja passou por esses teste
	// agora os dados serao apenas comparados
	printf("\nDigite seu telefone (sem DDD): ");
	gets(CEL);
	retorno = strcmp(CEL,mapa[andar-1][quarto-1].cel);
	if(retorno != 0)
		return 0;

	printf("\nDigite seu CPF (formato: XXXXXXXXX-XX): ");
	gets(CPF);
	retorno = strcmp(CPF,mapa[andar-1][quarto-1].cpf);
	if(retorno != 0)
		return 0;
	
	printf("\nDigite seu endereco: ");
	gets(ENDERECO);
	retorno = strcmp(ENDERECO,mapa[andar-1][quarto-1].endereco);
	if(retorno != 0)
		return 0;
		
	printf("\nDigite seu e-mail: ");
	gets(EMAIL);
	retorno = strcmp(EMAIL,mapa[andar-1][quarto-1].email);
	if(retorno != 0)
		return 0;
	return 1;
}