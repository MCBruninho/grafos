---
name: "Prática 04"
about: "Template para criar a issue da pratica04"
title: "[Prática 04] – Conectividade e Planaridade"
labels: ["pratica04"]
assignees: ''
---

## 🎯 Objetivo
Nesta prática, você irá:
- Implementar a detecção de **vértices de corte** (articulações) e **pontes** (arestas de corte) via algoritmo de Tarjan;
- Verificar **planaridade** usando a fórmula de Euler e heurística de Kuratowski.

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
   git checkout -b pratica-04
   ```

### 2️⃣ Implementação do código
1. No painel esquerdo do VS Code, localize a pasta `praticas`.
2. Crie uma nova pasta chamada `pratica04`.
3. Dentro dela, desenvolva os arquivos solicitados:
   - `conectividade.h`
   - `conectividade.c`
   - `planaridade.h`
   - `planaridade.c`
   - `main.c`
   - `Makefile`
4. Funções a implementar:
   - `dfs_articulacoes(...)` — algoritmo de Tarjan com arrays `descoberta[]` e `low[]`.
   - `detectar_pontes(...)` — `low[v] > descoberta[u]`.
   - `eh_planar_euler(GrafoLista *g)` — verifica $m \leq 3n - 6$.
   - Para $n \leq 10$: teste de subdivisões de $K_5$ e $K_{3,3}$ (força bruta).

### 3️⃣ Compilação e execução local
1. No terminal, acesse a pasta da prática:
   ```bash
   cd praticas/pratica04
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
   git add praticas/pratica04/
   git commit -m "feat: entrega da pratica 04. Refs #ID"
   git push origin pratica-04
   ```
   > Substitua `#ID` pelo número desta Issue (ex: `Refs #3`).

### 5️⃣ Abrir o Pull Request
1. No GitHub, acesse seu repositório.
2. Clique em **"Compare & pull request"**.
3. **Base:** `main` ← **Compare:** `pratica-04`.
4. Título: `[Entrega] [Prática 04] – Conectividade e Planaridade`.
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
└── pratica04/
    ├── conectividade.c
    ├── conectividade.h
    ├── planaridade.c
    ├── planaridade.h
    ├── main.c
    └── Makefile    
```

## ✅ Critérios de Conclusão
- [ ] Arquivos criados em `praticas/pratica04/`.
- [ ] Algoritmo de Tarjan para articulações implementado.
- [ ] Detecção de pontes (`low[v] > descoberta[u]`).
- [ ] Heurística de planaridade (Euler + Kuratowski para $n \leq 10$).
- [ ] Código enviado para o GitHub com `git push origin pratica-04`.
- [ ] Pull Request aberto apontando para `main`.
- [ ] GitHub Actions exibiu o check verde (✅).
- [ ] Issue vinculada ao Pull Request.