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
#define BOLD "\x1b[1m"       // Negrito
#define ITA "\x1b[3m"        // Itálico
#define UDL "\x1b[4m"        // Sublinhado
#define REV "\x1b[7m"        // Reverso

#define BLK "\x1b[30m"       // Texto preto
#define RED "\x1b[31m"       // Texto vermelho
#define GRN "\x1b[32m"       // Texto verde
#define YEL "\x1b[33m"       // Texto amarelo
#define BLU "\x1b[34m"       // Texto azul
#define MAG "\x1b[35m"       // Texto magenta
#define CYN "\x1b[36m"       // Texto ciano
#define WHT "\x1b[37m"       // Texto branco / cinza claro
#define GRY "\x1b[90m"       // Texto cinza escuro

#define BLK_B "\x1b[90m"     // Texto preto brilhante (cinza escuro)
#define RED_B "\x1b[91m"     // Texto vermelho brilhante
#define GRN_B "\x1b[92m"     // Texto verde brilhante
#define YEL_B "\x1b[93m"     // Texto amarelo brilhante
#define BLU_B "\x1b[94m"     // Texto azul brilhante
#define MAG_B "\x1b[95m"     // Texto magenta brilhante
#define CYN_B "\x1b[96m"     // Texto ciano brilhante
#define WHT_B "\x1b[97m"     // Texto branco brilhante
#define GRY_B "\x1b[37m"     // Texto cinza claro

#define BLK_BK "\x1b[40m"    // Fundo preto
#define RED_BK "\x1b[41m"    // Fundo vermelho
#define GRN_BK "\x1b[42m"    // Fundo verde
#define YEL_BK "\x1b[43m"    // Fundo amarelo
#define BLU_BK "\x1b[44m"    // Fundo azul
#define MAG_BK "\x1b[45m"    // Fundo magenta
#define CYN_BK "\x1b[46m"    // Fundo ciano
#define WHT_BK "\x1b[47m"    // Fundo branco / cinza claro
#define GRY_BK "\x1b[100m"   // Fundo cinza escuro

#define BLK_B_BK "\x1b[100m" // Fundo preto brilhante (cinza escuro)
#define RED_B_BK "\x1b[101m" // Fundo vermelho brilhante
#define GRN_B_BK "\x1b[102m" // Fundo verde brilhante
#define YEL_B_BK "\x1b[103m" // Fundo amarelo brilhante
#define BLU_B_BK "\x1b[104m" // Fundo azul brilhante
#define MAG_B_BK "\x1b[105m" // Fundo magenta brilhante
#define CYN_B_BK "\x1b[106m" // Fundo ciano brilhante
#define WHT_B_BK "\x1b[107m" // Fundo branco brilhante
#define GRY_B_BK "\x1b[47m"  // Fundo cinza claro


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
    usleep((unsigned int)(tempo * 1000000));
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

void EspacoPrint(int tam) { for (int i = 0; i < tam; i++) printf(" "); }  //Usar dps

void Cabecalho(const char *title, int tipo) {

    if (tipo == 0) {
        Linha(39, 0, 1);
        printf(BOLD ITA GRN_B BLK_B_BK "%s\n" RST, title);
        Linha(39, 0, 1);
    } else if (tipo == 1) {
        Linha(39, 0, 1);
        printf(BOLD ITA CYN "            %s\n" RST, title);
    }
}

void Resposta(float valor) {
    printf("\n      " BOLD BLK_B_BK " < RESPOSTA > " RST BOLD BLU_B_BK "  %.1f  " RST "\n" RST, valor);
}

void ClearInputUntilNewline(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int LerInt(const char *msg) {
    int v;
    while (1) {
        if (msg) { printf(BOLD CYN_B_BK "%s" RST, msg); printf(" "); } //colocar em todos estilos legais
        if (scanf("%d", &v) == 1) { ClearInputUntilNewline(); return v; }
        printf("Entrada invalida! Digite um numero inteiro: ");
        ClearInputUntilNewline();
    }
}

double LerDouble(const char *msg) {
    double v;
    while (1) {
        if (msg) {
            printf(BOLD BLU_B_BK "%s" RST, msg); printf(" ");
            fflush(stdout);
        }

        if (scanf("%lf", &v) == 1) {
            ClearInputUntilNewline();
            return v;
        }

        printf(RED "Entrada invalida! Digite um numero: " RST);
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

      BOLD "     <  " CYN_BK " -- " BLU_BK " Adição          " BOLD MAG_BK " [  +  ]" BOLD GRN_BK "    --ID = 1",
      BOLD "     <  " CYN_BK " -- " BLU_BK " Subtração       " BOLD MAG_BK " [  -  ]" BOLD GRN_BK "    --ID = 2",
      BOLD "     <  " CYN_BK " -- " BLU_BK " Multiplicação   " BOLD MAG_BK " [  x  ]" BOLD GRN_BK "    --ID = 3", 
      BOLD "     <  " CYN_BK " -- " BLU_BK " Divisão         " BOLD MAG_BK " [  ÷  ]" BOLD GRN_BK "    --ID = 4",
      BOLD "     <  " CYN_BK " -- " BLU_BK " Porcentagem     " BOLD MAG_BK " [  %  ]" BOLD GRN_BK "    --ID = 5",         
      BOLD "     <  " CYN_BK " -- " BLU_BK " Raiz Quadrada   " BOLD MAG_BK " [  2√ ]" BOLD GRN_BK "    --ID = 6",
      BOLD "     <  " CYN_BK " -- " BLU_BK " Potenciação     " BOLD MAG_BK " [  3² ]" BOLD GRN_BK "    --ID = 7",
      BOLD "     <  " CYN_BK " -- " BLU_BK " Saída           " BOLD MAG_BK " [ ExT ]" BOLD GRN_BK "    --ID = 8",

    }; 

    while (1) {
        if (estado == 0) {
            Cabecalho("Calculadora Científica", 0);
            printf("\n");  num1 = LerDouble(" < Número > ");
            printf("\n" BLK_B_BK " < Operações Permitidas > " RST "\n");
            Linha(30, 1, 0);
            for (int i = 0; i < 8; ++i) {
                // Primeira função Negrito para o sinal "<" e para as demais ate o RST = reset, depois Ciano para o "--" depois reset depois Azul para os valores do vetor  
                printf(" %s " RST BOLD "  >  " "\n" RST , OP[i]);
                slep(0.05f);
            }
            Linha(30, 1, 0);
            printf("\n");  op = LerInt(" < Operador > ");
            if (op == 6) { estado = 1; resposta = CalcularOperacaoC(op, num1, 0); }
            else if ((op >= 1 && op <= 5) || op == 7) {
                printf("\n");  num2 = LerDouble(" < Número > ");
                estado = 1;
                resposta = CalcularOperacaoC(op, num1, num2);
            } else if (op == 8) { return; } 
            else {
                LimpaTela();
                Linha(39, 1, 0);
                printf(RED_B_BK " < ERRO > " RST BOLD RED_B "        ÍNDICE DE OPERADOR INVÁLIDO " RST "\n"); fflush(stdout);
                Linha(39, 1, 0);
            }
        } else if (estado == 1) {
            LimpaTela();
            Cabecalho("Calculadora - Científica", 0);
            printf("\n" BLK_B_BK " < Operações Permitidas > " RST "\n");
            Linha(39, 1, 0);
            for (int i = 0; i < 8; ++i) printf(" %s " RST BOLD "  >  " RST "\n", OP[i]);
            Linha(39, 1, 0);
            printf("\t\t\n");
            Resposta((float)resposta);
            printf("\n\n");
            op = LerInt("    < Operador >   ");
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
            num2 = LerDouble("      < Número >   ");
            resposta = CalcularOperacaoC(op, resposta, num2);
        }
    }
}

void GerarFibonacci(float *vet, int tamanho) {
    float t1 = 0.0f, t2 = 1.0f, t3 = 0.0f;
    for (int i = 0; i < tamanho; ++i) {
        vet[i] = t1;
        printf(BLK_B_BK " %.0f " RST, t1);
        if (i < tamanho - 1) printf(" - ");
        else printf(" >> \n" RST );
        t3 = t1 + t2;
        t1 = t2;
        t2 = t3;
    }
}

void Contador(int cont) {
    for (int i = 1; i <= cont; i++) {
        printf(BLU_B_BK "\r < Contador Para Reinício > " BLK_B_BK "  %d  " RST, i);
        fflush(stdout);
        sleep(1);
    }
    printf("\n");
}

void Fibonacci(int n) {
    if (n <= 0) return;
    float *vet = malloc((size_t)n * sizeof(float));
    if (!vet) { printf(RED_B_BK" Erro ao alocar memória! " RST "\n"); return; }
    printf(BLU_B_BK " Sequencia > " BLK_B_BK ITA " FIBONACCI " RST ); printf("\n\n");
    GerarFibonacci(vet, n);
    Linha(39, 2, 7);
    Contador(5);

}

/* PA: Lógica de Verificação Restabelecida */
int VerificaPA_Logica(float a1, float a2, float razao) {
    if (razao == 0.0f) return 1;
    if (a1 < a2 && razao < 0.0f) return 2;
    if (a1 > a2 && razao > 0.0f) return 3;
    // Nova regra: se o passo pula o fim
    if (a1 < a2 && (a1 + razao) > a2) return 4;
    if (a1 > a2 && (a1 + razao) < a2) return 5;
    return 0;
}

bool VerificaPA_Interativo(float *a1, float *a2, float *razao) {
    while (1) {
        int code = VerificaPA_Logica(*a1, *a2, *razao);
        if (code == 0) return true;
        if (code == 1) printf("\n\n" RED_B_BK " A razão não pode ser 0! " RST "\n\n");
        if (code == 2) printf("\n\n" RED_B_BK " A razão de uma PA Crescente deve ser Positiva! " RST "\n\n");
        if (code == 3) printf("\n\n" RED_B_BK " A razão de uma PA Decrescente deve ser Negativa! " RST "\n\n");
        if (code == 4 || code == 5) printf("\n\n" RED_B_BK " A razão é maior que a diferença total! " RST "\n\n");
        
        char esc = LerCharSN(BOLD CYN ITA "Deseja trocar algum dado para êxito? [S/N] " RST );
        if (esc == 'N') return false;
        char sel = LerCharOpcao(BOLD BLU ITA "Qual dado deseja mudar? [R=razao/I=inicio/F=fim]: " RST, "RIF");
        if (sel == 'R' || sel == 'r') { *razao = LerFloat(BOLD BLU_B_BK "Digite a nova Razão: " RST " "); continue; }
        if (sel == 'I' || sel == 'i') { *a1 = LerFloat(BOLD BLK_B_BK "Digite o novo Início:" RST " "); continue; }
        if (sel == 'F' || sel == 'f') { *a2 = LerFloat(BOLD MAG_B_BK "Digite o novo Fim:" RST " "); continue; }
    }
}

void ImprimirPA(float a1, float a2, float razao) {
    LimpaTela();
    printf("\n" BLU_B_BK " Progressão > " BLK_B_BK ITA " ARITMÉTICA " RST ); printf("\n\n");
    if (a1 == a2) { printf("\n" BLK_B_BK " %.0f " RST "\n", a1); return; }
    if (a1 < a2) {
        for (float i = a1; i <= a2; i += razao) {
            printf(BLK_B_BK " %.0f " RST, i);
            if (i < a2) printf(" - ");
            else printf(" > ");
        }
    } else {
        for (float i = a1; i >= a2; i += razao) {
            printf(BLK_B_BK " %.0f " RST, i);
            if (i < a2) printf(" - ");
            else printf(" >  -  FIM");
        }
    }
    printf("\n");
}

int ProgressaoArTm(float a1, float a2, float razao) {
    while (1) {
        if (!VerificaPA_Interativo(&a1, &a2, &razao)) return 1;
        ImprimirPA(a1, a2, razao);
        char cont = LerCharSN("\n" BOLD YEL_B "Deseja calcular outra PA? [S/N]:" RST " ");
        if (cont == 'N') { return 1; }
        else if (cont == 'S') { return 0;}
    }
}

/* Calculadora UNI (controller) */
void CalculadoraU(void) {
    double num1 = 0.0, num2 = 0.0, resultado = 0.0;
    float Fb = 0.0f;
    int choice = 0;
    const char *OP[] = {

        BOLD "     <  " CYN_BK " -- " BLU_BK " Adição          " BOLD MAG_BK " [  +  ] " BOLD GRN_BK "    --ID = 1 ",
        BOLD "     <  " CYN_BK " -- " BLU_BK " Subtração       " BOLD MAG_BK " [  -  ] " BOLD GRN_BK "    --ID = 2 ",
        BOLD "     <  " CYN_BK " -- " BLU_BK " Multiplicação   " BOLD MAG_BK " [  x  ] " BOLD GRN_BK "    --ID = 3 ", 
        BOLD "     <  " CYN_BK " -- " BLU_BK " Divisão         " BOLD MAG_BK " [  ÷  ] " BOLD GRN_BK "    --ID = 4 ",
        BOLD "     <  " CYN_BK " -- " BLU_BK " Fibonacci       " BOLD MAG_BK " [ 1-5 ] " BOLD GRN_BK "    --ID = 5 ",         
        BOLD "     <  " CYN_BK " -- " BLU_BK " Progressão      " BOLD MAG_BK " [ 2x5 ] " BOLD GRN_BK "    --ID = 6 ",
        BOLD "     <  " CYN_BK " -- " BLU_BK " Saída           " BOLD MAG_BK " [ ExT ] " BOLD GRN_BK "    --ID = 7 ",
    };

    Cabecalho("Calculadora - UNI", 0);
    while (1) {
        printf("\n");
        printf("\n" BOLD BLK_B_BK " < Operações Permitidas > " RST "\n");
        Linha(39, 1, 0);

        for (int i = 0; i < 7; ++i) {
            printf(" %s " RST BOLD "  >  " "\n" RST , OP[i]);
            slep(0.02f);
            if (i == 6) { Linha(39, 1, 0); }
        }

        choice = LerInt(" < Escolha > "); printf("\n");
        Linha(39, 1, 0);
        if (choice == 7) break;
        if (choice < 1 || choice > 7) { printf("Dado Invalido\n"); slep(1); continue; }
        
        switch (choice) {
            case 1:
                num1 = LerDouble("  < Número >   ");
                num2 = LerDouble("\n  < Número >   ");
                resultado = AdiU(num1, num2);
                LimpaTela();
                break;
            case 2:
                num1 = LerDouble("  < Número >   ");
                num2 = LerDouble("\n  < Número >   ");
                resultado = SubU(num1, num2);
                LimpaTela();
                break;
            case 3:
                num1 = LerDouble("  < Número >  ");
                num2 = LerDouble("\n  < Número >  ");
                resultado = MultiU(num1, num2);
                LimpaTela();
                break;
            case 4:
                num1 = LerDouble("  < Número >   ");
                num2 = LerDouble("\n  < Número >   ");
                resultado = DiviU(num1, num2);
                LimpaTela();
                break;
            case 5:
                Fb = (float)LerInt("  < Número de Termos > ");
                LimpaTela();
                Fibonacci((int)Fb);
                slep(0.5f);
                continue;
            case 6: {
                int fluxo = 0;
                while (fluxo == 0) {
                    float a1 = LerFloat(BOLD MAG_B " Digite o início da PA > " RST " ");
                    float a2 = LerFloat(BOLD BLU_B " Digite o Número final da PA > " RST " ");
                    float a3 = LerFloat(BOLD MAG_B " Digite a razão da PA > " RST " ");
                    fluxo = ProgressaoArTm(a1, a2, a3);
                    LimpaTela(); Cabecalho("Calculadora - UNI", 0);
                }
                continue;
            }
        }
        Resposta((float)resultado);
    }
}

int main(void) {
    int choice = 0;
    while (1) {
        LimpaTela();
        Cabecalho("Calculadora - Dinâmica", 0);
        puts(BOLD CYN_B_BK "\n\n     < OPÇÕES DE CALCULADORA >     "RST);
        Linha(39, 1, 0);
        puts("");
        puts(BOLD MAG_B_BK " < 1 > " RST BOLD " - Calculadora Ciêntífica \n");
        puts(BOLD MAG_B_BK " < 2 > " RST BOLD " - Calculadora Uni-Funcional \n");
        Linha(39, 1, 0);
        choice = LerInt(" < ESCOLHA >  ");

        if (choice == 1) {
            puts("\n" BOLD GRN "Entrando na calculadora ciêntífica..aguarde");
            slep(1.0f);
            puts("validando Cálculos e valores..." RST );
            slep(1.0f);
            LimpaTela();
            CalculadoraC();

        } else if (choice == 2) {
            puts("\n" BOLD GRN "Entrando na calculadora - UNI..aguarde");
            slep(1.0f);
            puts("validando Cálculos e valores..." RST );
            slep(1.0f);
            LimpaTela();
            CalculadoraU();

        } else {
            LimpaTela();
            printf("\n\n< ESCOLHA INVÁLIDA TENTE NOVAMENTE >\n\n\n\n");
            slep(1.5f);
        }
    }
    return 0;
}