---
name: "Prática 08"
about: "Template para criar a issue da pratica08"
title: "[Prática 08] – Árvore Geradora Mínima"
labels: ["pratica08"]
assignees: ''
---

## 🎯 Objetivo
Nesta prática, você irá:
- Implementar **Kruskal** com **Union-Find** (compressão de caminho + união por rank);
- Implementar **Prim** com **Min-Heap**.

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
   git checkout -b pratica-08
   ```

### 2️⃣ Implementação do código
1. No painel esquerdo do VS Code, localize a pasta `praticas`.
2. Crie uma nova pasta chamada `pratica08`.
3. Dentro dela, desenvolva os arquivos solicitados:
   - `agm.h`
   - `agm.c`
   - `main.c`
   - `Makefile`
4. Estruturas obrigatórias:
   ```c
   typedef struct {
       int *pai, *rank;
       int n;
   } DSU;

   typedef struct {
       int u, v, peso;
   } Aresta;
   ```
5. Funções a implementar:
   - `find(DSU *d, int x)` com compressão de caminho.
   - `unir(DSU *d, int x, int y)` com união por rank.
   - `kruskal(...)` — ordenação + seleção, complexidade $O(E \log E)$.
   - `prim(...)` — heap + atualização de chaves, complexidade $O((V+E)\log V)$.

### 3️⃣ Compilação e execução local
1. No terminal, acesse a pasta da prática:
   ```bash
   cd praticas/pratica08
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
   git add praticas/pratica08/
   git commit -m "feat: entrega da pratica 08. Refs #ID"
   git push origin pratica-08
   ```
   > Substitua `#ID` pelo número desta Issue (ex: `Refs #3`).

### 5️⃣ Abrir o Pull Request
1. No GitHub, acesse seu repositório.
2. Clique em **"Compare & pull request"**.
3. **Base:** `main` ← **Compare:** `pratica-08`.
4. Título: `[Entrega] [Prática 08] – Árvore Geradora Mínima`.
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
└── pratica08/
    ├── agm.c
    ├── agm.h
    ├── main.c
    └── Makefile
```

## ✅ Critérios de Conclusão
- [ ] Arquivos criados em `praticas/pratica08/`.
- [ ] Union-Find com compressão de caminho e união por rank.
- [ ] Kruskal implementado ($O(E \log E)$).
- [ ] Prim implementado ($O((V+E)\log V)$).
- [ ] Código enviado para o GitHub com `git push origin pratica-08`.
- [ ] Pull Request aberto apontando para `main`.
- [ ] GitHub Actions exibiu o check verde (✅).
- [ ] Issue vinculada ao Pull Request.