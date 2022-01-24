#include <stdio.h>
#include <stdlib.h>

void abreEntrada(FILE **entrada);
void abreSaida(int opcao, FILE **saida);
void copiaCabecalho(FILE *entrada, FILE *saida);
void limiarizacao(FILE *entrada, FILE *saida);
void negativo(FILE *entrada, FILE *saida);
void histograma(FILE *entrada, FILE *saida);

int main(void)
{
    FILE *entrada, *saida;
    int opcao;

    do
    {
        /************* MENU *************
         * 1) Limiarização
         * 2) Negativo
         * 3) Histograma
         * 0) Sair
         *******************************/
        
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
            case 1:
            {
                abreEntrada(&entrada);
                if(entrada == NULL) 
                {
                    printf("Nao foi possivel abrir o arquivo de entrada!");
                    getchar();
                    break;
                }

                abreSaida(opcao, &saida);
                if(saida == NULL) 
                {
                    printf("Nao foi possivel abrir o arquivo de saida!");
                    getchar();
                    break;
                }

                copiaCabecalho(entrada, saida);
                limiarizacao(entrada, saida);

                fclose(entrada);
                fclose(saida);

                break;
            }

            case 2:
            {
                abreEntrada(&entrada);
                if(entrada == NULL) 
                {
                    printf("Nao foi possivel abrir o arquivo de entrada!");
                    getchar();
                    break;
                }

                abreSaida(opcao, &saida);
                if(saida == NULL) 
                {
                    printf("Nao foi possivel abrir o arquivo de saida!");
                    getchar();
                    break;
                }

                copiaCabecalho(entrada, saida);
                negativo(entrada, saida);
                
                fclose(entrada);
                fclose(saida);

                break;
            }

            case 3:
            {
                abreEntrada(&entrada);
                if(entrada == NULL) 
                {
                    printf("Nao foi possivel abrir o arquivo de entrada!");
                    getchar();
                    break;
                }

                abreSaida(opcao, &saida);
                if(saida == NULL) 
                {
                    printf("Nao foi possivel abrir o arquivo de saida!");
                    getchar();
                    break;
                }

                histograma(entrada, saida);

                fclose(entrada);
                fclose(saida);

                break;
            }
            case 0:
            {
                printf("Finalizando programa...");

                break;
            }
            default:
            {
                printf("ERRO: Opcao invalida\n");

                break;
            }
        }
    } while (opcao != 0);
    
    return 0;
}


void abreEntrada(FILE **entrada)
{
    (*entrada) = fopen("exemplo.pgm", "r");

    return;
}

void abreSaida(int opcao, FILE **saida)
{
    if (opcao == 1)
    {
        (*saida) = fopen("limiarizacao.pgm", "w");
        return;
    }
    if (opcao == 2)
    {
        (*saida) = fopen("negativo.pgm", "w");
        return;
    }
    if (opcao == 3)
    {
        (*saida) = fopen("histograma.txt", "w");
        return;
    }
}

void copiaCabecalho(FILE *entrada, FILE *saida)
{
    int linhas = 0, colunas = 0, max_cinza; //vars p/ passar p/ arquivo de saida
    char control_string[50]; //string p/ passar p/ arquivo de saida

    fgets(control_string, 50, entrada); //le a primeira linha (P2)
    fprintf(saida, "%s", control_string); //printa no arquivo de destino (P2)

    fscanf(entrada, "%d %d", &colunas, &linhas);
    fprintf(saida, "%d %d\n", colunas, linhas);

    fscanf(entrada, "%d", &max_cinza);
    fprintf(saida, "%d\n", max_cinza);

    return;
}

void limiarizacao(FILE *entrada, FILE *saida)
{
    int pixel; //guarda o valor de cada pixel
    int limiar = 150; //limiar p/ trocar valores dos pixels
    
    while (!feof(entrada)) 
    {
        if (!fscanf(entrada, "%d", &pixel))
        {
            return;
        }
        
        if (pixel > limiar)
        {
            pixel = 255;
        }
        else
        {
            pixel = 0;
        }
        fprintf(saida, "%d ", pixel);
        
    }
    return;
}

void negativo(FILE *entrada, FILE *saida)
{
    int pixel; //guarda o valor de cada pixel
    
    while (!feof(entrada)) 
    {
        if (!fscanf(entrada, "%d", &pixel))
        {
            return;
        }

        pixel = 255 - pixel;

        fprintf(saida, "%d ", pixel);
    }

    return;
}

void histograma(FILE *entrada, FILE *saida)
{
    /* SOLUÇÃO PARA ANDAR ATÉ O PRIMEIRO PIXEL */
    int linhas = 0, colunas = 0, max_cinza;
    char control_string[50];
    
    fgets(control_string, 50, entrada);
    fscanf(entrada, "%d %d", &colunas, &linhas);
    fscanf(entrada, "%d", &max_cinza);
    /* --------------------------------------- */

    int i; //contador
    int vet[256] = {0}; //numero max de valor possivel atribuido

    int pixel; //guarda o valor de cada pixel
    
    while (!feof(entrada)) 
    {
        if (!fscanf(entrada, "%d", &pixel))
        {
            return;
        }

        vet[pixel]++;
    }

    for (i = 0; i < 256; i++)
    {
        fprintf(saida, "[%d]: %d", i, vet[i]);
        fputs("\n", saida);
    }

    return;
}
