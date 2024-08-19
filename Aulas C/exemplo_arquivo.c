#include<stdio.h>
#include<stdlib.h>

typedef struct aluno
{
	int id;
	float nota;
}aluno;

void aloca(aluno **p, int tam);

int main()
{
	int opcao;
	aluno *p = NULL;
	FILE *fptr = NULL;
	aloca(&p,1); // só um aluno
	do{
		printf("\n\n[1] Cadastrar aluno\n[2] Ver aluno\n[3] FIM");
		printf("\nDigite sua opção: ");
		scanf("%d", &opcao);
		switch(opcao)
		{
			case 1:
				printf("\nCadastro do aluno");
				printf("\nDigite o identificador: ");
				scanf("%d", &(p->id));
				printf("\nDigite a nota: ");
				scanf("%f",&(p->nota));
				if((fptr = fopen("aluno.bin", "wb")) == NULL)
					printf("\nNão foi possível abrir o arquivo");
				else
					fwrite(p,sizeof(aluno),1,fptr);
				fclose(fptr); //fecha fora do else
				break;
			case 2:
				if((fptr = fopen("aluno.bin", "rb")) == NULL)
					printf("\nAinda não existe o arquivo");
				else
				{
					fread(p,sizeof(aluno),1,fptr);
					fclose(fptr);//só se abrir
					printf("\nSó tem 1 aluno:");
					printf("\nID: %d\nNota: %.2f", p->id, p->nota);
				}

				break;
			case 3:
				printf("Até a próxima!");
		}

	}while(opcao != 3);
	return 0;
}

void aloca(aluno **p, int tam)
{
	if((*p = (aluno *) realloc(*p, sizeof(aluno)*tam)) == NULL)
		exit(1);
}




