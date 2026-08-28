---
name: "Prática 01"
about: "Template para criar a issue da pratica01"
title: "[Prática 01] – Representação de Grafos"
labels: ["pratica01"]
assignees: ''
---

## 🎯 Objetivo
Nesta prática, você irá:
- Implementar um grafo simples usando **matriz de adjacência** e **lista de adjacência**;
- Criar operações básicas: inserir/remover arestas, consultar grau, verificar adjacência;
- Praticar o fluxo de versionamento com **branch → commit → PR**.

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
   git checkout -b pratica-01
   ```

### 2️⃣ Implementação do código
1. No painel esquerdo do VS Code, localize a pasta `praticas`.
2. Crie uma nova pasta chamada `pratica01`.
3. Dentro dela, desenvolva os arquivos solicitados:
   - `grafo_matriz.h`
   - `grafo_matriz.c`
   - `grafo_lista.h`
   - `grafo_lista.c`
   - `main.c`
   - `Makefile`
4. Estruturas obrigatórias:
   ```c
   // Matriz de adjacência
   typedef struct {
       int n;
       int **adj;
   } GrafoMatriz;

   // Lista de adjacência
   typedef struct No {
       int destino;
       struct No *prox;
   } No;

   typedef struct {
       int n;
       No **adj;
   } GrafoLista;
   ```
5. Operações a implementar:
   - `criar_grafo_matriz(int n)` e `criar_grafo_lista(int n)`
   - `inserir_aresta_*` e `remover_aresta_*`
   - `grau_*` e `sao_adjacentes_*`
   - `liberar_grafo_*` (liberar toda a memória alocada)

### 3️⃣ Compilação e execução local
1. No terminal, acesse a pasta da prática:
   ```bash
   cd praticas/pratica01
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
   git add praticas/pratica01/
   git commit -m "feat: entrega da pratica 01. Refs #ID"
   git push origin pratica-01
   ```
   > Substitua `#ID` pelo número desta Issue (ex: `Refs #3`).

### 5️⃣ Abrir o Pull Request
1. No GitHub, acesse seu repositório.
2. Clique em **"Compare & pull request"**.
3. **Base:** `main` ← **Compare:** `pratica-01`.
4. Título: `[Entrega] Prática 01 — Representação de Grafos`.
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
└── pratica01/
    ├── grafo_lista.c
    ├── grafo_lista.h
    ├── grafo_matriz.c
    ├── grafo_matriz.h
    ├── main.c
    └── Makefile    
```

## ✅ Critérios de Conclusão
- [ ] Arquivos criados em `praticas/pratica01/`.
- [ ] Matriz de adjacência implementada com alocação dinâmica.
- [ ] Lista de adjacência implementada com structs encadeadas.
- [ ] Operações de inserção, remoção, grau e adjacência funcionando.
- [ ] Código enviado para o GitHub com `git push origin pratica-01`.
- [ ] Pull Request aberto apontando para `main`.
- [ ] GitHub Actions exibiu o check verde (✅).
- [ ] Issue vinculada ao Pull Request.
