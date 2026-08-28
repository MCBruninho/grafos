---
name: "Prática 03"
about: "Template para criar a issue da pratica03"
title: "[Prática 03] – Ordenação Topológica"
labels: ["pratica03"]
assignees: ''
---

## 🎯 Objetivo
Nesta prática, você irá:
- Implementar **ordenação topológica** em DAGs usando o algoritmo de **Kahn** (BFS com grau de entrada) e a variante **DFS**;
- Detectar ciclos em digrafos (se não for DAG, a ordenação é impossível).

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
   git checkout -b pratica-03
   ```

### 2️⃣ Implementação do código
1. No painel esquerdo do VS Code, localize a pasta `praticas`.
2. Crie uma nova pasta chamada `pratica03`.
3. Dentro dela, desenvolva os arquivos solicitados:
   - `dag.h`
   - `dag.c`
   - `main.c`
   - `Makefile`
4. Funções a implementar:
   - `ordenacao_topologica_kahn(GrafoLista *g, int *tamanho)` — retorna array com a ordenação ou NULL se houver ciclo.
   - `ordenacao_topologica_dfs(GrafoLista *g, int *tamanho)` — empilha na saída da DFS.
   - `eh_dag(GrafoLista *g)` — verifica se o grafo é acíclico.

### 3️⃣ Compilação e execução local
1. No terminal, acesse a pasta da prática:
   ```bash
   cd praticas/pratica03
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
   git add praticas/pratica03/
   git commit -m "feat: entrega da pratica 03. Refs #ID"
   git push origin pratica-03
   ```
   > Substitua `#ID` pelo número desta Issue (ex: `Refs #3`).

### 5️⃣ Abrir o Pull Request
1. No GitHub, acesse seu repositório.
2. Clique em **"Compare & pull request"**.
3. **Base:** `main` ← **Compare:** `pratica-03`.
4. Título: `[Entrega] [Prática 03] – Ordenação Topológica`.
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
└── pratica03/
    ├── dag.c
    ├── dag.4
    ├── main.c
    └── Makefile    
```

## ✅ Critérios de Conclusão
- [ ] Arquivos criados em `praticas/pratica03/`.
- [ ] Algoritmo de Kahn implementado (fila + grau de entrada).
- [ ] Algoritmo DFS topológica implementado (empilhamento na saída).
- [ ] Detecção de ciclos (retorna erro se não for DAG).
- [ ] Código enviado para o GitHub com `git push origin pratica-03`.
- [ ] Pull Request aberto apontando para `main`.
- [ ] GitHub Actions exibiu o check verde (✅).
- [ ] Issue vinculada ao Pull Request.