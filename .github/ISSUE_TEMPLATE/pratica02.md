---
name: "Prática 02"
about: "Template para criar a issue da pratica02"
title: "[Prática 02] – Busca em Grafos (BFS/DFS)"
labels: ["pratica02"]
assignees: ''
---

## 🎯 Objetivo
Nesta prática, você irá:
- Implementar **BFS (Busca em Largura)** com fila e **DFS (Busca em Profundidade)** com pilha/recursão;
- Aplicar buscas para detectar componentes conexos, ciclos e bipartição.

## 📝 Instruções da Atividade

### 1️⃣ Preparação do ambiente
1. Abra o **Visual Studio Code** na pasta do seu repositório.
2. Abra um terminal e certifique-se de que está na branch `main`.
   ```bash
   git checkout main
   git pull origin main
   ```
3. Crie a branch da prática:
   ```bash
   git checkout -b pratica-02
   ```

### 2️⃣ Implementação do código
1. No painel esquerdo do VS Code, localize a pasta `praticas`.
2. Crie uma nova pasta chamada `pratica02`.
3. Dentro dela, desenvolva os arquivos solicitados:
   - `busca_largura.h`
   - `busca_largura.c`
   - `busca_profundidade.h`
   - `busca_profundidade.c`
   - `main.c`
   - `Makefile`
4. Estruturas auxiliares obrigatórias:
   ```c
   // Fila (FIFO) para BFS
   typedef struct {
       int *dados;
       int capacidade, inicio, fim, tamanho;
   } Fila;

   // Pilha (LIFO) para DFS iterativa
   typedef struct {
       int *dados;
       int topo, capacidade;
   } Pilha;
   ```
5. Funções a implementar:
   - `bfs(GrafoLista *g, int origem, int *dist, int *pred)`
   - `dfs_recursiva(GrafoLista *g, int u, int *visitado, ...)`
   - `eh_bipartido(GrafoLista *g)`
   - `contar_componentes(GrafoLista *g)`
   - `tem_ciclo(GrafoLista *g)`

### 3️⃣ Compilação e execução local
1. No terminal, acesse a pasta da prática:
   ```bash
   cd praticas/pratica02
   ```
2. Compile e execute o programa:
   ```bash
   make
   ./main          # Linux / macOS
   main.exe        # Windows
   ```

### 4️⃣ Enviar para o GitHub
1. Volte para a pasta raiz do repositório:
   ```bash
   cd ../..
   ```
2. Adicione os arquivos, grave as alterações e envie:
   ```bash
   git add praticas/pratica02/
   git commit -m "feat: entrega da pratica 02. Refs #ID"
   git push origin pratica-02
   ```
   > Substitua `#ID` pelo número desta Issue (ex: `Refs #3`).

### 5️⃣ Abrir o Pull Request
1. No GitHub, acesse seu repositório.
2. Clique em **"Compare & pull request"**.
3. **Base:** `main` ← **Compare:** `pratica-02`.
4. Título: `[Entrega] [Prática 02] – Busca em Grafos (BFS/DFS)`.
5. Preencha a descrição e vincule esta Issue (ex: `Closes #ID`).
6. Clique em **"Create pull request"**.

### 6️⃣ Verificar a correção automática
1. No GitHub, acesse a aba **Actions** do seu repositório.
2. Clique no workflow do seu último commit.
3. Verifique o resultado:
   - ✅ **Verde:** Seu código compilou com sucesso.
   - ❌ **Vermelho:** Houve erro de compilação. Clique em **"Compilar práticas"** para ver a mensagem de erro. Corrija no VS Code e envie novamente para o GitHub.

## 📂 Estrutura Final
Seu repositório deve ficar assim:
```text
praticas/
└── pratica02/
    ├── busca_largura.c
    ├── busca_largura.h
    ├── busca_profundidade.c
    ├── busca_profundidade.h
    ├── main.c
    └── Makefile    
```

## ✅ Critérios de Conclusão
- [ ] Arquivos criados em `praticas/pratica02/`.
- [ ] BFS implementada com fila (array circular ou encadeada).
- [ ] DFS recursiva com tempos de entrada/saída.
- [ ] Detecção de componentes conexos.
- [ ] Detecção de ciclos.
- [ ] Teste de bipartição (2-coloração via BFS).
- [ ] Código enviado para o GitHub com `git push origin pratica-02`.
- [ ] Pull Request aberto apontando para `main`.
- [ ] GitHub Actions exibiu o check verde (✅).
- [ ] Issue vinculada ao Pull Request.
