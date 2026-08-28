---
name: "Prática 05"
about: "Template para criar a issue da pratica05"
title: "[Prática 05] – Coloração de Grafos"
labels: ["pratica05"]
assignees: ''
---

## 🎯 Objetivo
Nesta prática, você irá:
- Implementar o **algoritmo guloso** (greedy coloring) para coloração de vértices;
- Implementar a heurística **Welsh-Powell** (ordenar por grau decrescente antes de colorir).

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
   git checkout -b pratica-05
   ```

### 2️⃣ Implementação do código
1. No painel esquerdo do VS Code, localize a pasta `praticas`.
2. Crie uma nova pasta chamada `pratica05`.
3. Dentro dela, desenvolva os arquivos solicitados:
   - `coloracao.h`
   - `coloracao.c`
   - `main.c`
   - `Makefile`
4. Funções a implementar:
   - `coloracao_gulosa(GrafoLista *g, int *num_cores)` — ordenação arbitrária.
   - `coloracao_welsh_powell(GrafoLista *g, int *num_cores)` — ordena por grau decrescente.
   - `eh_bipartido(GrafoLista *g)` — caso especial (2-coloração = número cromático 2).

### 3️⃣ Compilação e execução local
1. No terminal, acesse a pasta da prática:
   ```bash
   cd praticas/pratica05
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
   git add praticas/pratica05/
   git commit -m "feat: entrega da pratica 05. Refs #ID"
   git push origin pratica-05
   ```
   > Substitua `#ID` pelo número desta Issue (ex: `Refs #3`).

### 5️⃣ Abrir o Pull Request
1. No GitHub, acesse seu repositório.
2. Clique em **"Compare & pull request"**.
3. **Base:** `main` ← **Compare:** `pratica-05`.
4. Título: `[Entrega] [Prática 05] – Coloração de Grafos`.
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
└── pratica05/
    ├── coloracao.c
    ├── coloracao.h
    ├── main.c
    └── Makefile    
```

## ✅ Critérios de Conclusão
- [ ] Arquivos criados em `praticas/pratica05/`.
- [ ] Algoritmo guloso básico implementado.
- [ ] Heurística Welsh-Powell (ordenação por grau decrescente).
- [ ] Verificação de bipartição (BFS 2-coloração).
- [ ] Código enviado para o GitHub com `git push origin pratica-05`.
- [ ] Pull Request aberto apontando para `main`.
- [ ] GitHub Actions exibiu o check verde (✅).
- [ ] Issue vinculada ao Pull Request.