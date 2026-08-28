# 🎓 Teoria dos Grafos

Repositório destinado às aulas teóricas e às atividades práticas da disciplina Teoria dos Grafos.

## 🛠️ Ambiente de Desenvolvimento

Para acompanhar a disciplina, você precisará das seguintes ferramentas:

| Ferramenta | O que faz? | Recomendação |
| :--- | :--- | :--- |
| Editor de código | Ambiente onde você escreve o código. | **Visual Studio Code** (VS Code) |
| Compilador | Transforma o código em um programa. | **GNU Compiler Collection** (GCC) |
| Versionador | Guarda o histórico de alterações do código. | **Git** |

### 1️⃣ Instalando o VS Code

O VS Code é um editor de código da Microsoft que suporta diversas linguagens de programação.

1. Baixe em [code.visualstudio.com](https://code.visualstudio.com/) de acordo com o seu sistema operacional e instale com as opções padrão.
2. Abra o VS Code e escolha o ícone de quadradinhos no menu lateral (Extensões).
3. Instale as extensões essenciais para C:
   - Procure por **"C/C++"** da Microsoft e instale.
   - Procure por **"C/C++ Extension Pack"** e instale.
   - Procure por **"Graphviz Interactive Preview"** e instale.

### 2️⃣ Instalando o GCC

O compilador GCC transforma o texto que você escreve na linguagem C em um programa que o computador entende.

#### Windows

1. Baixe o [w64devkit](https://github.com/skeeto/w64devkit/releases) (escolha o arquivo `.7z.exe`).
2. Extraia para uma pasta, por exemplo `C:\w64devkit`.
3. Adicione a pasta `bin` ao PATH do Windows:
   - Pressione `Win + R`, digite `sysdm.cpl` e pressione `Enter`.
   - Vá em **Avançado** → **Variáveis de Ambiente**.
   - Em **Path**, clique em **Editar** → **Novo**.
   - Adicione `C:\w64devkit\bin` (ou o caminho onde extraiu).
   - Clique em OK em todas as janelas.
4. Pressione `Win + R`, digite `cmd` e pressione `Enter`.
5. No Prompt de Comando, execute:
```bash
gcc --version
```
6. Se aparecer a versão, está tudo certo.

#### macOS

1. Pressione `Command + Espaço`, digite `Terminal` e pressione `Enter`.
2. No Terminal, execute:
```bash
xcode-select --install
```
3. Será exibida uma janela solicitando a instalação das **Command Line Tools**. Clique em `Instalar` e aguarde a conclusão do processo.
4. Após a instalação, feche e abra novamente o Terminal.
5. Verifique se o compilador está disponível executando:
```bash
gcc --version
```
6. Se aparecer a versão, está tudo certo.

#### Linux (Debian/Ubuntu)

1. Pressione `Ctrl + Alt + T` para abrir o terminal.
2. No terminal, execute: 
```bash
sudo apt update
sudo apt install build-essential
```
3. Verifique se o compilador está disponível executando:
```bash
gcc --version
```
4. Se aparecer a versão, está tudo certo.

### 3️⃣ Instalando o Git

O Git é um sistema de controle de versão. Ele registra cada alteração que você faz no código, permitindo voltar no tempo se algo der errado.

#### Windows

1. Baixe em [git-scm.com](https://git-scm.com/install/windows) e instale com as opções padrão.
2. Pressione `Win + R`, digite `cmd` e pressione `Enter`.
3. No Prompt de Comando, execute:
```bash
git --version
```
4. Se aparecer a versão, está tudo certo.

#### macOS

1. Pressione `Command + Espaço`, digite `Terminal` e pressione `Enter`.
2. No Terminal, execute:
```bash
git --version
```
3. Se não estiver instalado, o macOS perguntará se deseja instalar.
4. Se aparecer a versão, está tudo certo.

#### Linux (Debian/Ubuntu)

1. Pressione `Ctrl + Alt + T` para abrir o terminal.
2. No terminal, execute: 
```bash
sudo apt update
sudo apt install git
```
3. Verifique se o versionador está disponível executando:
```bash
git --version
```
4. Se aparecer a versão, está tudo certo.

## 📂 Estrutura de Pastas do Repositório

Este repositório está organizado da seguinte forma:
```
apc-i-template/
├── .github/         # Template das issues e validador de compilação
│   ├── ISSUE_TEMPLATE/
│   │   ├── pratica01.md
│   │   ├── pratica02.md
│   │   ├── ...
│   │   └── pratica10.md
│   └── workflows/
│       └── validar-compilacao.yml
│
├── aulas/           # Códigos trabalhados em sala de aula
│   ├── aula01/
│   │   └── arquivo.c
│   ├── aula02/
│   │   └── arquivo.c
│   ├── ...
│   └── .gitkeep
│
├── praticas/        # Códigos das atividades práticas
│   ├── pratica01/
│   │   └── arquivo.c
│   ├── pratica02/
│   │   └── arquivo.c
│   ├── ...
│   └── .gitkeep
│
├── .gitignore
└── README.md
```

## 🔧 Configuração Inicial (realizar apenas uma vez)

Execute estes passos para preparar seu ambiente.

1. Clique no botão `Use this template`, no topo da página, para criar uma cópia deste repositório na sua conta GitHub.
2. No GitHub, clique no botão verde **"<> Code"**, copie a URL (começa com `https://`).
3. Faça o clone do seu repositorio para a sua máquina local executando no terminal:
```bash
git clone https://github.com/SEU_USUARIO/nome-do-seu-repositorio.git
```
> Substitua `SEU_USUARIO` e `nome-do-seu-repositorio` pelos dados corretos.
4. O Git precisa saber quem você é. Execute no terminal (substitua pelos seus dados):
```bash
git config --global user.name "Seu Nome Completo"
git config --global user.email "seu-email@exemplo.com"
```

## 🔄 Fluxo de Trabalho Acadêmico

Siga estes passos para **cada** atividade:

### 1️⃣ Abrir a Issue da prática

1. No GitHub, vá na aba **Issues** do seu repositório.
2. Clique em **New issue**.
3. Escolha o template da prática (ex: "Prática 01").
4. Clique em **Submit new issue**.
5. **Anote o número da Issue** (aparece como `#3`, `#4`, etc.). Você vai usar ele no commit.

> 💡 A Issue é como um "cartão de tarefa" com as instruções da atividade.

### 2️⃣ Criar a branch da prática

No terminal, na **pasta raiz** do repositório:

```bash
git checkout -b pratica-01
```

> ⚠️ **Importante:** O nome da branch deve ser exatamente `pratica-XX` (com dois dígitos).  
> Exemplos válidos: `pratica-01`, `pratica-02`, ..., `pratica-10`.  
> Exemplos inválidos: `pratica1`, `p01`, `pratica_01`, `feature/pratica-01`.

### 3️⃣ Criar o arquivo da prática

1. No VS Code, dentro da pasta `praticas/`, crie uma nova pasta (ex: `pratica01`).
2. Dentro dela, crie os arquivos `.c` com o código solicitado e o arquivo `Makefile`.
3. **Teste localmente** antes de enviar:
   ```bash
   cd praticas/pratica01
   make
   ./main          # Linux/macOS
   main.exe        # Windows
   ```

### 4️⃣ Enviar para o GitHub

No terminal, na **pasta raiz** do repositório:

```bash
git add praticas/pratica01/
git commit -m "feat: entrega da pratica 01. Refs #3"
git push origin pratica-01
```

> Substitua `pratica01` pelo nome da sua prática e `#3` pelo número da Issue que você abriu.

**Pronto!** Seu código foi enviado para a branch.

### 5️⃣ Abrir o Pull Request

1. No GitHub, acesse seu repositório.
2. Clique em **"Compare & pull request"** (vai aparecer um banner amarelo).
3. **Base:** `main` ← **Compare:** `pratica-01`.
4. Título: `[Entrega] Prática 01 — Representação de Grafos`.
5. Descrição: preencha o template e vincule a Issue (ex: `Closes #3`).
6. Clique em **"Create pull request"**.

> ⚠️ **A entrega só é válida quando:**
> - O Pull Request está aberto apontando para `main`.
> - O GitHub Actions fica **verde** (✅) — compilação e testes passaram.
> - A Issue de entrega está preenchida e vinculada ao PR.

### 6️⃣ Verificar se passou no teste automático

1. No GitHub, vá na aba **Actions** do seu repositório.
2. Você verá um item com o nome do seu último commit.
3. Clique nele para ver o resultado:
   - ✅ **Verde:** Seu código compilou com sucesso! A entrega é válida.
   - ❌ **Vermelho:** Houve erro. Clique no workflow quebrado para ver detalhes. Corrija no VS Code e envie novamente para o GitHub.

## ❓ Problemas Comuns

### "'gcc' não é reconhecido como comando"
O compilador não está no PATH. Reinstale o w64devkit (Windows) ou `build-essential` (Linux) e **reinicie o VS Code**.

### "fatal: not a git repository"
Você está fora da pasta do projeto. Certifique-se de estar na raiz do repositório (`cd nome-do-repositorio`).

### "Everything up-to-date" mas não enviou
Você esqueceu de fazer `git commit` antes do `git push`. Execute:
```bash
git add .
git commit -m "feat: praticaXX. Refs #ID"
git push origin pratica-XX
```

### O Actions ficou vermelho
Clique na aba **Actions**, depois no workflow vermelho, depois em **"Compilar arquivos .c"**. Leia a mensagem de erro (geralmente está nas últimas linhas). Erros comuns:
- Esqueceu o ponto e vírgula `;`
- Nome da variável escrito errado
- Usou `printf` sem `#include <stdio.h>`

### Criei a pasta errada (ex: `Praticas/` com P maiúsculo)
O Actions procura `praticas/` com **p** minúsculo. Renomeie a pasta:
```bash
mv Praticas praticas
```