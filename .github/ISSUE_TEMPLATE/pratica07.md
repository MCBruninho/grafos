---
name: "Prática 07"
about: "Template para criar a issue da pratica07"
title: "[Prática 07] – Menor Caminho: Bellman-Ford"
labels: ["pratica07"]
assignees: ''
---

## 🎯 Objetivo
Nesta prática, você irá:
- Implementar o **algoritmo de Bellman-Ford** com relaxação de arestas;
- Detectar e reconstruir **ciclos de custo negativo**.

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
   git checkout -b pratica-07
   ```

### 2️⃣ Implementação do código
1. No painel esquerdo do VS Code, localize a pasta `praticas`.
2. Crie uma nova pasta chamada `pratica07`.
3. Dentro dela, desenvolva os arquivos solicitados:
   - `bellman_ford.h`
   - `bellman_ford.c`
   - `main.c`
   - `Makefile`
4. Funções a implementar:
   - `bellman_ford(GrafoListaPonderado *g, int origem, int *dist, int *pred)` — retorna 1 (sucesso) ou 0 (ciclo negativo).
   - `reconstruir_ciclo_negativo(...)` — retrocede `n` vezes pelo `pred[]` e imprime o ciclo.

### 3️⃣ Compilação e execução local
1. No terminal, acesse a pasta da prática:
   ```bash
   cd praticas/pratica07
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
   git add praticas/pratica07/
   git commit -m "feat: entrega da pratica 07. Refs #ID"
   git push origin pratica-07
   ```
   > Substitua `#ID` pelo número desta Issue (ex: `Fixes #3`).

### 5️⃣ Abrir o Pull Request
1. No GitHub, acesse seu repositório.
2. Clique em **"Compare & pull request"**.
3. **Base:** `main` ← **Compare:** `pratica-07`.
4. Título: `[Entrega] [Prática 07] – Menor Caminho: Bellman-Ford`.
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
└── pratica07/
    ├── bellman_ford.c
    ├── bellman_ford.h
    ├── main.c
    └── Makefile    
```

## ✅ Critérios de Conclusão
- [ ] Arquivos criados em `praticas/pratica07/`.
- [ ] Bellman-Ford com $n-1$ iterações de relaxação.
- [ ] Detecção de ciclos negativos na $n$-ésima iteração.
- [ ] Reconstrução do ciclo negativo (se existir).
- [ ] Código enviado para o GitHub com `git push origin pratica-07`.
- [ ] Pull Request aberto apontando para `main`.
- [ ] GitHub Actions exibiu o check verde (✅).
- [ ] Issue vinculada ao Pull Request.