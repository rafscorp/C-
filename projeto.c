#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define RESET "\033[0m"      // Reset
#define NEGRITO "\033[1m"    // Negrito
#define SUBLINHADO "\033[4m" // Sublinhado
#define PISCAR "\033[5m"     // Piscar
#define INVERTIDO "\033[7m"  // Inverter cores
#define OCULTO "\033[8m"     // Oculto
// Cores do texto
#define PRETO "\033[30m"
#define VERMELHO "\033[31m"
#define VERDE "\033[32m"
#define AMARELO "\033[33m"
#define AZUL "\033[34m"
#define MAGENTA "\033[35m"
#define CIANO "\033[36m"
#define BRANCO "\033[37m"
// Cores claras
#define PRETO_C "\033[90m"
#define VERMELHO_C "\033[91m"
#define VERDE_C "\033[92m"
#define AMARELO_C "\033[93m"
#define AZUL_C "\033[94m"
#define MAGENTA_C "\033[95m"
#define CIANO_C "\033[96m"
#define BRANCO_C "\033[97m"
// Cores de fundo
#define FUNDO_P "\033[40m"
#define FUNDO_VM "\033[41m"
#define FUNDO_VD "\033[42m"
#define FUNDO_AM "\033[43m"
#define FUNDO_AZ "\033[44m"
#define FUNDO_M "\033[45m"
#define FUNDO_C "\033[46m"
#define FUNDO_B "\033[47m"
// Cores de fundo claras
#define FUNDO_P_C "\033[100m"
#define FUNDO_VM_C "\033[101m"
#define FUNDO_VD_C "\033[102m"
#define FUNDO_AM_C "\033[103m"
#define FUNDO_AZ_C "\033[104m"
#define FUNDO_M_C "\033[105m"
#define FUNDO_C_C "\033[106m"
#define FUNDO_B_C "\033[107m"

void CleanTela()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Linha()
{
    for (int i = 0; i < 50; i++)
    {
        printf("==");
    }
    printf("\n");
}

void Cabecalho(char *nome)
{
    int TamTexto = strlen(nome);
    int Espacos = (100 - TamTexto) / 2;

    Linha();
    for (int i = 0; i < Espacos; i++)
    {
        printf(" ");
    }
    printf("%s\n", nome);
    Linha();
}

// FUNÇÕES DO PROJETO
void AdicionarProduto() {

}
void RemoverProduto() {

}
void ListarProdutos() { 

}                   

int main()
{
    int opcao_menu;
    Cabecalho("<<----- Mercado do Zé do DF ----->>");

    printf(NEGRITO AZUL "1 - " RESET "Adicionar Produto\n");
    printf(NEGRITO AZUL "2 - " RESET "Remover Produto\n");
    printf(NEGRITO AZUL "3 - " RESET "Listar Produtos\n");
    printf(NEGRITO AZUL "4 - " RESET "Sair\n");
    printf(NEGRITO AMARELO "\nEscolha uma opção: " RESET);
    scanf("%d", &opcao_menu);

    if (opcao_menu == 4)
    {
        CleanTela();
        Cabecalho("<<----- " NEGRITO AMARELO "Obrigado por Usar nosso Sistema" RESET " ----->>");
        printf(NEGRITO VERMELHO "Saindo...\n" RESET);
        sleep(1);
    } else if (opcao_menu == 1) {
        CleanTela();
        Cabecalho("<<----- " NEGRITO VERDE "Adicionar Produto" RESET " ----->>");
        AdicionarProduto();
    } else if (opcao_menu == 2) {
        CleanTela();
        Cabecalho("<<----- " NEGRITO VERDE "Remover Produto" RESET " ----->>");
        RemoverProduto();
    } else if (opcao_menu == 3) {
        CleanTela();
        Cabecalho("<<----- " NEGRITO VERDE "Listar Produtos" RESET " ----->>");
        ListarProdutos();
    } else {
        CleanTela();
        Cabecalho("<<----- " NEGRITO VERMELHO "Opção Inválida" RESET " ----->>");
    }
    return 0;
}