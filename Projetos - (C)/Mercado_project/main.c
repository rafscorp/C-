#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>
#define LinhaBox "─"
#define LinhaNormal "-"
#ifdef _WIN32
#include <windows.h>
#endif
#define TamanhoLinha 60
void limpartela()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void slep(int tempo)
{
#ifdef _WIN32
    Sleep(tempo * 1000);
#else
    sleep(tempo);
#endif
}

void linha(int tamanho, const char *tipo)
{
    for (int i = 0; i < tamanho; i++)
    {
        printf("%s", tipo);
    }
    printf("\n");
}

void cabecalho(const char *nome)
{
    int espacos = (TamanhoLinha - (int)strlen(nome)) / 2;
    if (espacos < 0) {
        espacos = 0;
    }

    linha(TamanhoLinha, LinhaBox);
    printf("%*s%s\n", espacos, "", nome);
    linha(TamanhoLinha, LinhaBox);
    printf("\n");
}

int lerInteiro(const char *impressao)
{
    char buffer[50];

    printf("%s", impressao);
    fgets(buffer, sizeof(buffer), stdin);

    return (int) strtol(buffer, NULL, 10);
}

char* lerChar(const char *impressao)
{
    char buffer[50];

    printf("%s", impressao);
    fgets(buffer, sizeof(buffer), stdin);

    buffer[strcspn(buffer, "\n")] = '\0';

    char *str = malloc(strlen(buffer) + 1);
    if (!str) {
        printf("Erro de memoria\n");
        slep(1);
        exit(1);
    }
    strcpy(str, buffer);

    return str;
}

void pausar() {
    printf("\nPressione ENTER para continuar...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

bool verifica_nomeclatura(char nome[64])
{
    int temLetra = 0;

    if (strlen(nome) == 0) return false;

    for (int i = 0; i < strlen(nome); i++)
    {
        if (isalpha((unsigned char)nome[i])) {
            temLetra = 1;
        }
        else if (!isspace((unsigned char)nome[i])) {
            return false;
        }
    }
    return temLetra;
}

bool validar_preco(char *entrada) {
    int tam = strlen(entrada);
    if (tam < 4) return false;

    if (entrada[tam - 3] == '.') {
        entrada[tam - 3] = ',';
    }

    if (entrada[tam - 3] != ',' || !isdigit(entrada[tam - 2]) || !isdigit(entrada[tam - 1])) {
        return false;
    }

    int contador_digitos = 0;
    for (int i = tam - 4; i >= 0; i--) {
        if (isdigit(entrada[i])) {
            contador_digitos++;
        } else if (entrada[i] == '.') {
            if (contador_digitos != 3) return false;
            contador_digitos = 0;
        } else {
            return false;
        }
    }
    return (contador_digitos > 0);
}

bool verifica_cpf(char *cpf)
{
    if (strlen(cpf) != 11) return false;
    for (int i = 0; i < 11; i++)
    {
        if (!isdigit(cpf[i])) return false;
    }
    return true;
}

typedef struct
{
    char preco[24];
    char produto[50];
} Produtos;

typedef struct
{
    char nome[64];
    char cpf[24];
} Clientes;

Produtos *produtos = NULL;
int total_produtos = 0;

Clientes *clientes = NULL;
int total_clientes = 0;

void print_centralizado(const char *texto, int largura)
{
    int len = strlen(texto);
    int espacos = (largura - len) / 2;

    if (espacos < 0) espacos = 0;

    printf("%*s%s%*s",
           espacos, "",
           texto,
           largura - len - espacos, "");
}

bool listar_produto()
{
    if (produtos == NULL)
    {
        printf("Erro, nao tem nada na LISTA de Produtos\n");
        sleep(3);
        return false;
    }

    linha(TamanhoLinha, LinhaBox);

    printf("│");
    print_centralizado("Nome do Produto", 30);
    printf("│");
    print_centralizado("  Preço do Produto  ", 20);
    printf("\n");

    linha(TamanhoLinha, LinhaBox);
    for (int i = 0; i < total_produtos; i++)
    {
        printf("│");
        printf("ID %d", i+1);
        print_centralizado(produtos[i].produto, 30);
        printf("│");
        print_centralizado(produtos[i].preco, 20);
        printf("\n");
    }

    linha(TamanhoLinha, LinhaBox);
    return true;
}

bool listar_clientes()
{
    if (clientes == NULL)
    {
        printf("Erro, nao tem nada na LISTA de Produtos\n");
        sleep(3);
        return false;
    }

    linha(TamanhoLinha, LinhaBox);

    printf("│");
    print_centralizado("Nome dos Usuários", 30);
    printf(" │");
    print_centralizado("   CPF dos Usuários  ", 20);
    printf("\n");

    linha(TamanhoLinha, LinhaBox);
    for (int i = 0; i < total_clientes; i++)
    {
        printf("│");
        printf("ID %d", i+1);
        print_centralizado(clientes[i].nome, 30);
        printf("│");
        print_centralizado(clientes[i].cpf, 20);
        printf("\n");
    }

    linha(TamanhoLinha, LinhaBox);
    return true;
}

bool cpf_ja_existe(const char *cpf)
{
    for (int i = 0; i < total_clientes; i++)
    {
        if (strcmp(clientes[i].cpf, cpf) == 0)
        {
            return true;
        }
    }
    return false;
}

bool Nome_existe_cliente(const char *nome)
{
    for (int i = 0; i < total_clientes; i++)
    {
        if (strcmp(clientes[i].nome, nome) == 0)
        {
            return true;
        }
    }
    return false;
}

void normalizar_nome(char *str)
{
    int i = 0, j = 0;
    bool espaco = false;

    while (str[i])
    {
        if (isspace((unsigned char)str[i]))
        {
            if (!espaco)
            {
                str[j++] = ' ';
                espaco = true;
            }
        }
        else
        {
            str[j++] = tolower((unsigned char)str[i]);
            espaco = false;
        }
        i++;
    }

    if (j > 0 && str[j - 1] == ' ')
        j--;

    str[j] = '\0';
}

bool adicionar_Clientes(char *nome, char *cpf)
{
    if (cpf_ja_existe(cpf))
    {
        printf("Erro: CPF ja cadastrado!\n");
        slep(2);
        return false;
    }

    char nome_norm[64];
    strcpy(nome_norm, nome);
    normalizar_nome(nome_norm);

    for (int i = 0; i < total_clientes; i++)
    {
        char existente[64];
        strcpy(existente, clientes[i].nome);
        normalizar_nome(existente);

        if (strcmp(existente, nome_norm) == 0)
        {
            printf("Erro: Cliente com esse nome ja existe!\n");
            slep(2);
            return false;
        }
    }

    Clientes *tmp = realloc(clientes, (total_clientes + 1) * sizeof(Clientes));
    if (!tmp)
    {
        printf("Erro ao alocar memoria!\n");
        slep(2);
        return false;
    }

    clientes = tmp;
    strcpy(clientes[total_clientes].nome, nome);
    strcpy(clientes[total_clientes].cpf, cpf);
    total_clientes++;

    return true;
}

bool adicionar_Produto(char *nome, char *preco)
{
    char nome_norm[50];
    strcpy(nome_norm, nome);
    normalizar_nome(nome_norm);

    for (int i = 0; i < total_produtos; i++)
    {
        char existente[50];
        strcpy(existente, produtos[i].produto);
        normalizar_nome(existente);

        if (strcmp(existente, nome_norm) == 0)
        {
            printf("Erro: Produto ja cadastrado!\n");
            slep(2);
            return false;
        }
    }

    Produtos *tmp = realloc(produtos, (total_produtos + 1) * sizeof(Produtos));
    if (!tmp)
    {
        printf("Erro ao alocar memoria!\n");
        slep(2);
        return false;
    }

    produtos = tmp;
    strcpy(produtos[total_produtos].produto, nome);
    strcpy(produtos[total_produtos].preco, preco);
    total_produtos++;

    return true;
}

void remover_produto(int id)
{
    if (produtos == NULL || total_produtos == 0)
    {
        printf("Lista vazia.\n");
        slep(2);
        return;
    }

    if (id < 0 || id >= total_produtos)
    {
        printf("ID invalido.\n");
        slep(2);
        return;
    }

    for (int i = id; i < total_produtos - 1; i++)
    {
        produtos[i] = produtos[i + 1];
    }

    total_produtos--;

    if (total_produtos == 0)
    {
        free(produtos);
        produtos = NULL;
    }
    else
    {
        Produtos *tmp = realloc(produtos, total_produtos * sizeof(Produtos));
        if (tmp != NULL)
            produtos = tmp;
    }

    printf("Produto removido.\n");
    slep(2);
}

void remover_cliente(int id)
{
    if (clientes == NULL || total_clientes == 0)
    {
        printf("Lista vazia.\n");
        slep(2);
        return;
    }

    if (id < 0 || id >= total_clientes)
    {
        printf("ID invalido.\n");
        slep(2);
        return;
    }

    for (int i = id; i < total_clientes - 1; i++)
    {
        clientes[i] = clientes[i + 1];
    }

    total_clientes--;

    if (total_clientes == 0)
    {
        free(clientes);
        clientes = NULL;
    }
    else
    {
        Clientes *tmp = realloc(clientes, total_clientes * sizeof(Clientes));
        if (tmp != NULL)
            clientes = tmp;
    }

    printf("Cliente removido.\n");
    slep(2);
}

int main()
{
    char *Nomeproduto;
    char *Nomecliente;
    char *preco;
    char *cpf;

    int cont = 1;
    while (cont == 1)
    {
        limpartela();
        cabecalho("Mercado Assaí Produtos");
        printf("  1 - Listar Produtos    \n");
        printf("  2 - Listar Clientes    \n");
        printf("  3 - Adicionar Produto  \n");
        printf("  4 - Cadastrar Cliente  \n");
        printf("  5 - Remover Produto    \n");
        printf("  6 - Remover Cliente    \n");
        printf("  7 - Sair             \n\n");

        int op = lerInteiro("Escolha: ");

        switch (op)
        {
        case 1:
            listar_produto();
            pausar();
            break;

        case 2:
            listar_clientes();
            pausar();
            break;

        case 3:
            {
                bool nome_ok;
                bool preco_ok;

                do
                {
                    Nomeproduto = lerChar("Nome do produto: ");
                    nome_ok = verifica_nomeclatura(Nomeproduto);

                    if (!nome_ok)
                    {
                        printf("Erro no nome do produto\n");
                        free(Nomeproduto);
                        Nomeproduto = NULL;
                    }

                } while (!nome_ok);

                do
                {
                    preco = lerChar("Preco: ");
                    preco_ok = validar_preco(preco);

                    if (!preco_ok)
                    {
                        printf("Preço inválido\n");
                        free(preco);
                        preco = NULL;
                    }

                } while (!preco_ok);

                if (adicionar_Produto(Nomeproduto, preco))
                {
                    printf("Produto adicionado com sucesso! = [%s][R$ %s]\n",
                           Nomeproduto, preco);
                    slep(3);
                }
                else
                {
                    printf("Erro ao adicionar produto\n");
                }

                free(Nomeproduto);
                free(preco);
                break;
            }

        case 4:
            {
                bool nome_ok;
                bool cpf_ok;

                do
                {
                    Nomecliente = lerChar("Nome do cliente: ");
                    nome_ok = verifica_nomeclatura(Nomecliente);

                    if (!nome_ok)
                    {
                        printf("Erro no nome\n");
                        free(Nomecliente);
                        Nomecliente = NULL;
                    }

                } while (!nome_ok);

                do
                {
                    cpf = lerChar("CPF: ");
                    cpf_ok = verifica_cpf(cpf);

                    if (!cpf_ok)
                    {
                        printf("CPF inválido\n");
                        free(cpf);
                        cpf = NULL;
                    }

                } while (!cpf_ok);

                if (adicionar_Clientes(Nomecliente, cpf))
                {
                    printf("Pessoa cadastrada com sucesso! = [%s][%s]\n",
                           Nomecliente, cpf);
                    slep(3);
                }

                free(Nomecliente);
                free(cpf);
                break;
            }

        case 5:
            {
                if (listar_produto())
                {
                    int id = lerInteiro("ID do produto para remover: ") - 1;
                    remover_produto(id);
                    pausar();
                }
                break;
            }

        case 6:
            {
                if (listar_clientes())
                {
                    int id = lerInteiro("ID do cliente para remover: ")-1;
                    remover_cliente(id);
                    pausar();
                }
                break;
            }
        case 7:
            printf("Saindo");
            fflush(stdout);
            slep(3);
            cont = 0;
            break;

        default:
            printf(" [ID][%d] id Inválido \n", op);
            fflush(stdout);
            slep(3);
        }
    }

    free(produtos);
    free(clientes);
    return 0;
}
