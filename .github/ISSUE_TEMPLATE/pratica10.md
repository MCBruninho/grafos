---
name: "Prática 10"
about: "Template para criar a issue da pratica10"
title: "[Prática 10] – Caminho Hamiltoniano e TSP"
labels: ["pratica10"]
assignees: ''
---

## 🎯 Objetivo
Nesta prática, você irá:
- Implementar **força bruta** para Caminho Hamiltoniano e Ciclo Hamiltoniano;
- Implementar o **TSP** com força bruta e duas heurísticas (Vizinho Mais Próximo e Inserção).

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
   git checkout -b pratica-10
   ```

### 2️⃣ Implementação do código
1. No painel esquerdo do VS Code, localize a pasta `praticas`.
2. Crie uma nova pasta chamada `pratica10`.
3. Dentro dela, desenvolva os arquivos solicitados:
   - `hamiltoniano.h`
   - `hamiltoniano.c`
   - `tps.h`
   - `tps.c`
   - `main.c`
   - `Makefile`
4. Funções a implementar:
   - `encontrar_caminho_hamiltoniano_bt(...)` — backtracking com permutações.
   - `tsp_forca_bruta(...)` — fixa origem, gera $(n-1)!$ permutações.
   - `tsp_vizinho_mais_proximo(...)` — heurística construtiva.
   - `tsp_insercao(...)` — heurística de inserção do mais próximo.
   - `grafo_para_tsp(...)` — redução: peso 1 para arestas existentes, 2 para inexistentes.
5. Experimento: para $n = 5, 8, 10, 12$, meça tempo e custo.

### 3️⃣ Compilação e execução local
1. No terminal, acesse a pasta da prática:
   ```bash
   cd praticas/pratica10
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
   git add praticas/pratica10/
   git commit -m "feat: entrega da pratica 10. Refs #ID"
   git push origin pratica-10
   ```
   > Substitua `#ID` pelo número desta Issue (ex: `Refs #3`).

### 5️⃣ Abrir o Pull Request
1. No GitHub, acesse seu repositório.
2. Clique em **"Compare & pull request"**.
3. **Base:** `main` ← **Compare:** `pratica-10`.
4. Título: `[Entrega] [Prática 10] – Caminho Hamiltoniano e TSP`.
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
└── pratica10/
    ├── hamiltoniano.c
    ├── hamiltoniano.h
    ├── tps.c
    ├── tps.h
    ├── main.c
    └── Makefile
```

## ✅ Critérios de Conclusão
- [ ] Arquivos criados em `praticas/pratica10/`.
- [ ] Backtracking para Caminho/Ciclo Hamiltoniano.
- [ ] TSP força bruta com permutações (origem fixa).
- [ ] Código enviado para o GitHub com `git push origin pratica-10`.
- [ ] Pull Request aberto apontando para `main`.
- [ ] GitHub Actions exibiu o check verde (✅).
- [ ] Issue vinculada ao Pull Request.