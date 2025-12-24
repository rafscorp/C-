# Calculadora Dinâmica em C

Uma **calculadora interativa em linguagem C**, executada no terminal, com foco em **interface visual avançada**, **validação robusta de entradas** e **múltiplos modos de cálculo**. O projeto foi desenvolvido com fins **didáticos e práticos**, explorando lógica de programação, controle de fluxo, modularização e uso de códigos ANSI para estilização.

---

## 📌 Visão Geral

A **Calculadora Dinâmica** oferece dois modos principais:

* **Calculadora Científica**
* **Calculadora Uni-Funcional**

Ambas compartilham um núcleo comum de utilidades (entrada segura, limpeza de tela, delays, estilização), garantindo uma experiência consistente e organizada.

---

## ✨ Funcionalidades

### 🔬 Calculadora Científica

* Adição
* Subtração
* Multiplicação
* Divisão (com tratamento de divisão por zero)
* Porcentagem
* Raiz quadrada
* Potenciação
* Encadeamento de operações
* Exibição destacada do resultado

### 🧮 Calculadora Uni-Funcional

* Operações aritméticas básicas
* Geração da **Sequência de Fibonacci**
* Cálculo e exibição de **Progressão Aritmética (PA)**

  * Validação automática da razão
  * Suporte a PA crescente e decrescente
  * Interação para correção de dados inválidos

---

## 🎨 Interface no Terminal

O projeto utiliza **códigos ANSI** para criar uma interface rica no terminal:

* Cores de texto e fundo
* Texto em negrito, itálico e sublinhado
* Cabeçalhos e divisórias estilizadas
* Feedback visual para erros e resultados

Compatível com **Linux, macOS e Windows** (com suporte a ANSI habilitado).

---

## 🧱 Estrutura do Projeto

* **Utilitários de sistema**

  * Limpeza de tela (`clear / cls`)
  * Delay multiplataforma (`sleep / usleep`)

* **Entrada segura de dados**

  * Inteiros, `float`, `double`
  * Opções controladas (`S/N`, menus)

* **Módulos matemáticos**

  * Operações científicas
  * Fibonacci
  * Progressão Aritmética

* **Controladores (controllers)**

  * Lógica isolada para cada modo da calculadora

---

## ⚙️ Requisitos

* Compilador **GCC** ou compatível
* Sistema operacional:

  * Linux / macOS
  * Windows (Prompt, PowerShell ou terminal com ANSI)

---

## ▶️ Compilação e Execução

```bash
gcc calculadora.c -o calculadora -lm
./calculadora
```

> O parâmetro `-lm` é necessário para funções matemáticas (`sqrt`, `pow`).

---

## 📚 Objetivos do Projeto

* Praticar **programação estruturada em C**
* Trabalhar com **validação de entrada do usuário**
* Implementar **interfaces de terminal mais avançadas**
* Organizar código em **funções reutilizáveis**
* Simular um projeto real com múltiplos fluxos de execução

---

## 🚧 Melhorias Futuras

* Sistema de **logs** da calculadora
* Histórico de operações
* Modularização em arquivos `.h` e `.c`
* Detecção automática de suporte ANSI no terminal
* Suporte a números complexos

---

## 👨‍💻 Autor

Desenvolvido por **Rafael Costa**
Projeto educacional em **Linguagem C**, focado em lógica, terminal UI e boas práticas.

---

## 📄 Licença

Este projeto é de uso **livre para fins educacionais**. Modificações e melhorias são bem-vindas.
