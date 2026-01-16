# 🛒 Sistema de Cadastro de Produtos e Clientes (C)

## Visão Geral

Este projeto é um **sistema de gerenciamento de produtos e clientes em C**, executado inteiramente em **modo console**, com foco em **organização, validação de dados, controle manual de memória e portabilidade entre sistemas operacionais** (Linux e Windows).

O código foi escrito com uma abordagem **didática, robusta e profissional**, simulando um pequeno sistema real de mercado (ex.: cadastro de produtos e clientes), aplicando boas práticas clássicas da linguagem C.

> 🎯 **Objetivo principal**: Demonstrar domínio de C estruturado, validação rigorosa de entradas, uso correto de `malloc`, `realloc` e `free`, além de formatação avançada de saída no terminal.

---

## ✨ Principais Funcionalidades

### 📦 Produtos

* Cadastro de produtos
* Validação de nome (somente letras e espaços)
* Validação de preço no padrão brasileiro (`1.234,56`)
* Listagem formatada em tabela
* Remoção segura por ID
* Prevenção de produtos duplicados

### 👤 Clientes

* Cadastro de clientes
* Validação de nome
* Validação de CPF (formato numérico com 11 dígitos)
* Detecção de CPF duplicado
* Normalização de nomes (case-insensitive e múltiplos espaços)
* Listagem formatada em tabela
* Remoção segura por ID

### 🧠 Sistema

* Menu interativo
* Interface de terminal organizada (estilo software legado/enterprise)
* Compatível com **Linux** e **Windows**
* Uso seguro de memória dinâmica

---

## 🖥️ Compatibilidade

| Sistema Operacional | Status      |
| ------------------- | ----------- |
| Linux               | ✅ Suportado |
| Windows             | ✅ Suportado |

A compatibilidade é garantida por:

* Uso de `#ifdef _WIN32`
* Abstração de `sleep` / `Sleep`
* Abstração de limpeza de tela (`clear` / `cls`)

---

## 🧱 Estrutura do Projeto

```text
.
├── main.c        # Código-fonte principal
└── README.md     # Documentação
```

O projeto foi mantido propositalmente em **arquivo único**, para facilitar leitura, estudo e manutenção inicial.

---

## ⚙️ Compilação

### Linux / macOS

```bash
gcc main.c -o mercado
./mercado
```

### Windows (MinGW)

```bash
gcc main.c -o mercado.exe
mercado.exe
```

> ⚠️ Não são necessárias bibliotecas externas.

---

## 📋 Menu do Sistema

```text
1 - Listar Produtos
2 - Listar Clientes
3 - Adicionar Produto
4 - Cadastrar Cliente
5 - Remover Produto
6 - Remover Cliente
7 - Sair
```

Cada opção executa validações completas antes de alterar qualquer dado.

---

## 🧩 Validações Implementadas

### ✔️ Nome (Produto / Cliente)

* Deve conter ao menos **uma letra**
* Aceita apenas letras e espaços
* Espaços duplicados são normalizados

### ✔️ Preço

* Formato brasileiro obrigatório
* Exemplos válidos:

  * `10,00`
  * `1.234,99`
  * `12.000,50`

### ✔️ CPF

* Exatamente **11 dígitos numéricos**
* Não aceita letras ou símbolos
* Não permite duplicação

---

## 🧠 Gerenciamento de Memória

O projeto faz uso explícito e seguro de:

* `malloc`
* `realloc`
* `free`

Boas práticas aplicadas:

* Reallocação incremental
* Liberação total de memória ao sair
* Proteção contra `NULL`
* Evita memory leaks

---

## 📐 Organização da Saída (UI de Terminal)

* Cabeçalhos centralizados
* Tabelas com colunas alinhadas
* Bordas usando caracteres Unicode
* Interface inspirada em sistemas corporativos clássicos

Exemplo:

```text
────────────────────────────────────────────────────────────
           Mercado Assaí Produtos
────────────────────────────────────────────────────────────
│ Nome do Produto            │  Preço do Produto  │
────────────────────────────────────────────────────────────
│ ID 1 Arroz 5kg             │  25,99             │
│ ID 2 Feijão Preto          │  8,50              │
────────────────────────────────────────────────────────────
```

---

## 🛡️ Robustez

* Proteção contra IDs inválidos
* Mensagens claras de erro
* Sistema não trava com entradas incorretas
* Fluxo previsível e controlado

---

## 📚 Conceitos Demonstrados

* Programação estruturada em C
* Ponteiros e memória dinâmica
* Validação de entrada do usuário
* Portabilidade entre sistemas
* Manipulação de strings
* Interface de texto avançada

---

## 🚀 Possíveis Melhorias Futuras

* Persistência em arquivo (`.txt` ou `.bin`)
* Ordenação de listas
* Busca por nome / CPF
* Validação real de CPF (dígitos verificadores)
* Modularização (`.h` / `.c`)
* Testes automatizados

---

## 👨‍💻 Autor

Projeto desenvolvido para **aprendizado avançado em C**, com foco em qualidade, organização e boas práticas de baixo nível.

> Este código reflete padrões clássicos usados em sistemas reais legados, bancos, automação comercial e softwares embarcados.

---

## 📄 Licença

Uso livre para estudo, modificação e evolução.

---

🔥 **Código simples por fora. Profissional por dentro.**
