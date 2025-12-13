#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif


//IMPLEMENTAR SISTEMA DE LOGS DA CALCULADORA




#define RST "\x1b[0m"        // Reseta tudo
#define BOLD "\x1b[1m"       // "negrito"
#define ITA "\x1b[3m"        // itálico
#define UDL "\x1b[4m"        // sublinhado
#define REV "\x1b[7m"        // reverso (inverte as cores fg/bg)


#define BLK "\x1b[30m"       //  1 - texto preto
#define RED "\x1b[31m"       //  2 - Texto vermelho
#define GRN "\x1b[32m"       //  3 - Texto verde
#define YEL "\x1b[33m"       //  4 - Texto amarelo
#define BLU "\x1b[34m"       //  5 - Texto azul
#define MAG "\x1b[35m"       //  6 - Texto magenta
#define CYN "\x1b[36m"       //  7 - Texto ciano
#define WHT "\x1b[37m"       //  8 - Texto branco / cinza claro

#define BLK_B "\x1b[90m"     //  9 - Texto preto brilhante (cinza escuro)
#define RED_B "\x1b[91m"     // 10 - Texto vermelho brilhante
#define GRN_B "\x1b[92m"     // 11 - Texto verde brilhante
#define YEL_B "\x1b[93m"     // 12 - Texto amarelo brilhante
#define BLU_B "\x1b[94m"     // 13 - Texto azul brilhante
#define MAG_B "\x1b[95m"     // 14 - Texto magenta brilhante
#define CYN_B "\x1b[96m"     // 15 - Texto ciano brilhante
#define WHT_B "\x1b[97m"     // 16 - Texto branco brilhante

#define BLK_BK "\x1b[40m"    // 17 - Fundo preto
#define RED_BK "\x1b[41m"    // 18 - Fundo vermelho
#define GRN_BK "\x1b[42m"    // 19 - Fundo verde
#define YEL_BK "\x1b[43m"    // 20 - Fundo amarelo
#define BLU_BK "\x1b[44m"    // 21 - Fundo azul
#define MAG_BK "\x1b[45m"    // 22 - Fundo magenta
#define CYN_BK "\x1b[46m"    // 23 - Fundo ciano
#define WHT_BK "\x1b[47m"    // 24 - Fundo branco

#define BLK_B_BK "\x1b[100m" // 25 - Fundo preto brilhante (cinza escuro)
#define RED_B_BK "\x1b[101m" // 26 - Fundo vermelho brilhante
#define GRN_B_BK "\x1b[102m" // 27 - Fundo verde brilhante
#define YEL_B_BK "\x1b[103m" // 28 - Fundo amarelo brilhante
#define BLU_B_BK "\x1b[104m" // 29 - Fundo azul brilhante
#define MAG_B_BK "\x1b[105m" // 30 - Fundo magenta brilhante
#define CYN_B_BK "\x1b[106m" // 31 - Fundo ciano brilhante
#define WHT_B_BK "\x1b[107m" // 32 - Fundo branco brilhante


void LimpaTela(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void slep(float tempo) {
#ifdef _WIN32
    Sleep((int)(tempo * 1000));
#else
    if (tempo <= 0.0f) return;
    unsigned int t = (unsigned int) tempo;
    sleep(t);
#endif
}


const char* getCor(int cor) {
    switch (cor) {
        case 1:  return BLK;       case 2:  return RED;
        case 3:  return GRN;       case 4:  return YEL;
        case 5:  return BLU;       case 6:  return MAG;
        case 7:  return CYN;       case 8:  return WHT;

        case 9:  return BLK_B;     case 10: return RED_B;
        case 11: return GRN_B;     case 12: return YEL_B;
        case 13: return BLU_B;     case 14: return MAG_B;
        case 15: return CYN_B;     case 16: return WHT_B;

        case 17: return BLK_BK;    case 18: return RED_BK;
        case 19: return GRN_BK;    case 20: return YEL_BK;
        case 21: return BLU_BK;    case 22: return MAG_BK;
        case 23: return CYN_BK;    case 24: return WHT_BK;

        case 25: return BLK_B_BK;  case 26: return RED_B_BK;
        case 27: return GRN_B_BK;  case 28: return YEL_B_BK;
        case 29: return BLU_B_BK;  case 30: return MAG_B_BK;
        case 31: return CYN_B_BK;  case 32: return WHT_B_BK;

        default: return ""; // Sem cor
    }
}

void Linha(int tam, int tipo, int cor) {
    const char *corStr = getCor(cor);

    const char *simbolo = (tipo == 0 ? "==" : "──");

    for (int i = 0; i < tam; i++) {
        printf("%s" BOLD "%s" RST, corStr, simbolo);
    }
    printf("\n");
}

void EspacoPrint(int tam) { for (int i = 0; i < tam; i++) printf(" "); }

void Cabecalho(const char *title, int tipo) {

    if (tipo == 0) {
        Linha(39, 0, 1);
        printf(BOLD ITA GRN_B BLK_B_BK "%s\n" RST, title);
        Linha(39, 0, 1);
    } else if (tipo == 1) {
        Linha(39, 0, 1);
        printf(BOLD CYN "                        %s\n" RST, title);
    }
}

void Resposta(int tipoP, float valor) {
    if (tipoP == 0) printf("      < RESPOSTA >   %.1f\n", valor);
    else printf("\n< RESPOSTA >  %.1f\n", valor);
}

void ClearInputUntilNewline(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int LerInt(const char *msg) {
    int v;
    while (1) {
        if (msg) { printf(BOLD CYN_B_BK "%s" RST, msg); printf(" > "); } //colocar em todos estilos legais
        if (scanf("%d", &v) == 1) { ClearInputUntilNewline(); return v; }
        printf("Entrada invalida! Digite um numero inteiro: ");
        ClearInputUntilNewline();
    }
}

double LerDouble(const char *msg) {
    double v;
    while (1) {
        if (msg) { printf(BOLD BLU_B_BK "%s" RST, msg); printf(" > "); }
        if (scanf("%lf", &v) == 1) { ClearInputUntilNewline(); return v; }
        printf("Entrada invalida! Digite um numero: ");
        ClearInputUntilNewline();
    }
}

float LerFloat(const char *msg) {
    float v;
    while (1) {
        if (msg) printf("%s", msg);
        if (scanf("%f", &v) == 1) { ClearInputUntilNewline(); return v; }
        printf("Entrada invalida! Digite um numero: ");
        ClearInputUntilNewline();
    }
}

float LerFloatNaoZero(const char *msg, const char *erroMsg) {
    float v;
    while (1) {
        v = LerFloat(msg);
        if (v != 0.0f) return v;
        if (erroMsg) printf("%s\n", erroMsg);
        else printf("Valor nao pode ser 0. Tente novamente.\n");
    }
}

char LerCharSN(const char *msg) {
    char c;
    while (1) {
        if (msg) printf("%s", msg);
        if (scanf(" %c", &c) == 1) {
            ClearInputUntilNewline();
            if (c == 'S' || c == 's') return 'S';
            if (c == 'N' || c == 'n') return 'N';
        } else ClearInputUntilNewline();
        printf("Valor invalido. Digite apenas S ou N.\n");
    }
}

char LerCharOpcao(const char *msg, const char *opcoes) {
    char c;
    while (1) {
        if (msg) printf("%s", msg);
        if (scanf(" %c", &c) == 1) {
            ClearInputUntilNewline();
            for (size_t i = 0; opcoes[i] != '\0'; ++i) {
                if (c == opcoes[i] || c == (opcoes[i] >= 'a' && opcoes[i] <= 'z' ? opcoes[i]-32 : opcoes[i]+32)) {
                    return c;
                }
            }
        } else ClearInputUntilNewline();
        printf("Entrada invalida. Opcoes validas: %s\n", opcoes);
    }
}

/* Lógica matemática (módulo de operações) */
double AdiC(double a, double b) { return a + b; }
double SubC(double a, double b) { return a - b; }
double MultC(double a, double b) { return a * b; }
double DivC(double a, double b) { return (b == 0.0) ? 0.0 : a / b; }
double PorC(double a, double b) { return (a * b) / 100.0; }
double RaizC(double a) { return (a < 0.0) ? 0.0 : sqrt(a); }
double PotC(double a, double b) { return pow(a, b); }

double AdiU(double a, double b) { return a + b; }
double SubU(double a, double b) { return a - b; }
double MultiU(double a, double b) { return a * b; }
double DiviU(double a, double b) { return (b == 0.0) ? 0.0 : a / b; }

/* Controller para Computação Científica */
double CalcularOperacaoC(int op, double n1, double n2) {
    double res = n1;
    if (op == 1) res = AdiC(n1, n2);
    else if (op == 2) res = SubC(n1, n2);
    else if (op == 3) res = MultC(n1, n2);
    else if (op == 4) res = DivC(n1, n2);
    else if (op == 5) res = PorC(n1, n2);
    else if (op == 6) res = RaizC(n1);
    else if (op == 7) res = PotC(n1, n2);
    return res;
}

void CalculadoraC(void) {
    double num1 = 0.0, num2 = 0.0, resposta = 0.0;
    int op = 0;
    int estado = 0;
    const char *OP[] = {

      BOLD "     <  " CYN_BK "  -- " BLU_BK " Adição          " BOLD MAG_BK " [  +  ]" BOLD GRN_BK "    --ID = ",
      BOLD "     <  " CYN_BK "  -- " BLU_BK " Subtração       " BOLD MAG_BK " [  -  ]" BOLD GRN_BK "    --ID = ",
      BOLD "     <  " CYN_BK "  -- " BLU_BK " Multiplicação   " BOLD MAG_BK " [  x  ]" BOLD GRN_BK "    --ID = ", 
      BOLD "     <  " CYN_BK "  -- " BLU_BK " Divisão         " BOLD MAG_BK " [  ÷  ]" BOLD GRN_BK "    --ID = ",
      BOLD "     <  " CYN_BK "  -- " BLU_BK " Porcentagem     " BOLD MAG_BK " [  %  ]" BOLD GRN_BK "    --ID = ",         
      BOLD "     <  " CYN_BK "  -- " BLU_BK " Raiz Quadrada   " BOLD MAG_BK " [  2√ ]" BOLD GRN_BK "    --ID = ",
      BOLD "     <  " CYN_BK "  -- " BLU_BK " Potenciação     " BOLD MAG_BK " [  3² ]" BOLD GRN_BK "    --ID = ",
      BOLD "     <  " CYN_BK "  -- " BLU_BK " Saída           " BOLD MAG_BK " [ ExT ]" BOLD GRN_BK "    --ID = ",

    }; 

    while (1) {
        if (estado == 0) {
            Cabecalho("Calculadora Científica", 0);
            printf("\n");  num1 = LerDouble(" < Número > ");
            printf("\n" BOLD BLK_B_BK " < Operações Permitidas > " RST "\n");
            Linha(30, 1, 0);
            for (int i = 0; i < 8; ++i) {
                // Primeira função Negrito para o sinal "<" e para as demais ate o RST = reset, depois Ciano para o "--" depois reset depois Azul para os valores do vetor  
                printf(" %s  %d  " RST BOLD "  >  " "\n" RST , OP[i], i + 1);
                slep(0.05f);
            }
            Linha(30, 1, 0);
            printf("\n");  op = LerInt(" < Operador > ");
            if (op == 6) { estado = 1; resposta = CalcularOperacaoC(op, num1, 0); }
            else if ((op >= 1 && op <= 5) || op == 7) {
                printf("\n");  num2 = LerDouble(" < Número > ");
                estado = 1;
                resposta = CalcularOperacaoC(op, num1, num2);
            } else {
                LimpaTela();
                Linha(39, 1, 0);
                printf(BOLD RED_B_BK " < ERRO > " RST BOLD RED_B "        ÍNDICE DE OPERADOR INVÁLIDO " RST "\n"); fflush(stdout);
                Linha(39, 1, 0);
            }
        } else if (estado == 1) {
            LimpaTela();
            Cabecalho("Calculadora - Científica", 0);
            printf("\n");
            Resposta(0, (float)resposta);
            printf("\n\n< Operações Permitidas >\n");
            Linha(39, 1, 0);
            for (int i = 0; i < 8; ++i) printf(" %s  %d  " RST BOLD "  >  " "\n" RST , OP[i], i + 1);
            Linha(39, 1, 0);
            op = LerInt("\n     < Operador >   ");
            if (op < 1 || op > 8) {
                LimpaTela();
                Linha(39, 1, 0);
                printf("ÍNDICE DE OPERADOR INVÁLIDO\n");
                Linha(39, 1, 0);
                printf("\nNúmero Anterior [  %.0f  ]\n", resposta);
                continue;
            }
            if (op == 8) return;
            if (op == 6) { resposta = RaizC(resposta); continue; }
            num2 = LerDouble("\n      < Número >   ");
            resposta = CalcularOperacaoC(op, resposta, num2);
        }
    }
}

// Fibonacci e vetor  |  OBS > Falta a logia de guardar...
void GuardarVetor(const float *vetor, int tamanho) {
    printf("\nValores armazenados: ");
    for (int i = 0; i < tamanho; ++i) printf("%.0f ", vetor[i]);
    printf("\n");
}

void GerarFibonacci(float *vet, int tamanho) {
    float t1 = 0.0f, t2 = 1.0f, t3 = 0.0f;
    for (int i = 0; i < tamanho; ++i) {
        vet[i] = t1;
        printf("%.0f", t1);
        if (i < tamanho - 1) printf(" - ");
        else printf(" >> ");
        t3 = t1 + t2;
        t1 = t2;
        t2 = t3;
    }
}

void Fibonacci(int n) {
    if (n <= 0) return;
    float *vet = malloc((size_t)n * sizeof(float));
    if (!vet) { printf("Erro ao alocar memória!\n"); return; }
    GerarFibonacci(vet, n);
    char opc = LerCharSN("   << Deseja Guardar o Vetor Para Alguma Operação? (S/N) > ");
    if (opc == 'S' || opc == 's') GuardarVetor(vet, n);
    else if (opc == 'n' || opc == 'N') { LimpaTela(); Cabecalho("Calculadora - UNI", 0); }
    free(vet);
}

/* PA: lógica e interação separadas */
int VerificaPA_Logica(float a1, float a2, float razao) {
    if (razao == 0.0f) return 1;
    if (a1 < a2 && razao < 0.0f) return 2;
    if (a1 > a2 && razao > 0.0f) return 3;
    return 0;
}

bool VerificaPA_Interativo(float *a1, float *a2, float *razao) {
    while (1) {
        int code = VerificaPA_Logica(*a1, *a2, *razao);
        if (code == 0) return true;
        if (code == 1) printf("A razão não pode ser 0!\n");
        if (code == 2) printf("A razão de uma PA Crescente deve ser Positiva!\n");
        if (code == 3) printf("A razão de uma PA Decrescente deve ser Negativa!\n");
        char esc = LerCharSN("Deseja trocar algum dado para êxito? [S/N] ");
        if (esc == 'N') return false;
        char sel = LerCharOpcao("Qual dado deseja mudar? [R=razao/I=inicio/F=fim]: ", "RIF");
        if (sel == 'R' || sel == 'r') { *razao = LerFloat("Digite a nova Razão: "); continue; }
        if (sel == 'I' || sel == 'i') { *a1 = LerFloat("Digite o novo Início: "); continue; }
        if (sel == 'F' || sel == 'f') { *a2 = LerFloat("Digite o novo Fim: "); continue; }
    }
}

void ImprimirPA(float a1, float a2, float razao) {
    if (a1 == a2) { printf("%.0f - \n", a1); return; }
    if (a1 < a2 && razao > 0.0f) {
        if (a1 + razao > a2) { printf("A razão é muito grande! A PA nao alcanca o valor final.\n"); return; }
        for (float i = a1; i <= a2; i += razao) printf("%.0f - ", i);
        printf("\n"); return;
    }
    if (a1 > a2 && razao < 0.0f) {
        if (a1 + razao < a2) { printf("A razão é muito pequena! A PA nao alcanca o valor final.\n"); return; }
        for (float i = a1; i >= a2; i += razao) printf("%.0f - ", i);
        printf("\n"); return;
    }
    printf("Configuração inválida para imprimir PA.\n");
}

void ProgressaoArTm(float a1, float a2, float razao) {
    while (1) {
        if (!VerificaPA_Interativo(&a1, &a2, &razao)) break;
        ImprimirPA(a1, a2, razao);
        char cont = LerCharSN("\nDeseja calcular outra PA? [S/N]: ");
        if (cont == 'N') { LimpaTela(); Cabecalho("Calculadora - UNI", 0); break; }
        a1 = LerFloat("Digite o início da PA: ");
        a2 = LerFloat("Digite o Número final da PA: ");
        razao = LerFloatNaoZero("Digite a razão da PA: ", "A razão não pode valer 0:");
    }
}

/* Calculadora UNI (controller) */
void CalculadoraU(void) {
    double num1 = 0.0, num2 = 0.0, resultado = 0.0;
    float Fb = 0.0f;
    int choice = 0;
    const char *OP[] = {
        "Adição\t\t[  +  ]",
        "Subtração\t\t[  -  ]",
        "Multiplicação\t[  x  ]",
        "Divisão\t\t[  ÷  ]",
        "Fibonacci\t\t[ 1-5 ]",
        "Progressão Artm\t[ T-R ]",
        "Saída     \t\t[ ExT ]"
    };

    Cabecalho("Calculadora - UNI", 0);

    while (1) {
        printf("\n");
        printf("\n< Operações Permitidas >\n");
        Linha(39, 1, 0);

        for (int i = 0; i < 7; ++i) {
            printf("-- %s     --ID = %d\n", OP[i], i + 1);
            slep(0.05f);
            if (i == 6) { Linha(39, 1, 0); }
        }

        choice = LerInt("\n< Escolha >  ");
        if (choice < 1 || choice > 7) { printf("Dado Invalido\n"); continue; }
        if (choice == 1) {
            num1 = LerDouble("< Número >   ");
            num2 = LerDouble("< Número >   ");
            LimpaTela(); Cabecalho("Calculadora - UNI", 0);
            resultado = AdiU(num1, num2); Resposta(1, (float)resultado);
        } else if (choice == 2) {
            num1 = LerDouble("< Número >   ");
            num2 = LerDouble("< Número >   ");
            LimpaTela(); Cabecalho("Calculadora - UNI", 0);
            resultado = SubU(num1, num2); Resposta(1, (float)resultado);
        } else if (choice == 3) {
            num1 = LerDouble("< Número >  ");
            num2 = LerDouble("< Número >  ");
            LimpaTela(); Cabecalho("Calculadora - UNI", 0);
            resultado = MultiU(num1, num2); Resposta(1, (float)resultado);
        } else if (choice == 4) {
            num1 = LerDouble("< Número >   ");
            num2 = LerDouble("< Número >   ");
            LimpaTela(); Cabecalho("Calculadora - UNI", 0);
            resultado = DiviU(num1, num2); Resposta(1, (float)resultado);
        } else if (choice == 5) {
            Fb = (float)LerInt("Número de Termos: ");
            Fibonacci((int)Fb);
        } else if (choice == 6) {
            float a1 = LerFloat("Digite o início da PA: ");
            float a2 = LerFloat("Digite o Número final da PA: ");
            float a3 = LerFloatNaoZero("Digite a razão da PA: ", "A razão não pode valer 0:");
            ProgressaoArTm(a1, a2, a3);
        } else if (choice == 7) {
            LimpaTela(); break;
        }
    }
}

int main(void) {
    int choice = 0;

    while (1) {
        Cabecalho("Calculadora - Dinâmica", 0);
        puts(BOLD CYN_B_BK "\n\n     < OPÇÕES DE CALCULADORA >     "RST);
        Linha(39, 1, 0);
        puts("");
        puts(BOLD MAG_B_BK " < 1 > " RST " - Calculadora Ciêntífica \n");
        puts(BOLD MAG_B_BK " < 2 > " RST " - Calculadora Uni-Funcional \n");
        Linha(39, 1, 0);
        choice = LerInt(" < ESCOLHA >   ");
        if (choice == 1) {
            puts("\n" BOLD GRN "Entrando na calculadora ciêntífica..aguarde");
            slep(1.0f);
            puts("validando Cálculos e valores..." RST );
            slep(1.0f);
            LimpaTela();
            CalculadoraC();
        } else if (choice == 2) {
            puts("Entrando na calculadora - UNI..aguarde");
            slep(1.0f);
            puts("validando Cálculos e valores...");
            slep(1.0f);
            LimpaTela();
            CalculadoraU();
        } else {
            LimpaTela();
            printf("\n\n< ESCOLHA INVÁLIDA TENTE NOVAMENTE >\n\n\n\n");
        }
    }
    return 0;
}