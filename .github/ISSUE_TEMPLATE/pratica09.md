---
name: "Prática 09"
about: "Template para criar a issue da pratica09"
title: "[Prática 09] – Cobertura de Vértices"
labels: ["pratica09"]
assignees: ''
---

## 🎯 Objetivo
Nesta prática, você irá:
- Implementar **força bruta com backtracking** para Cobertura de Vértices;
- Implementar uma **heurística gulosa** (maior grau primeiro).

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
   git checkout -b pratica-09
   ```

### 2️⃣ Implementação do código
1. No painel esquerdo do VS Code, localize a pasta `praticas`.
2. Crie uma nova pasta chamada `pratica09`.
3. Dentro dela, desenvolva os arquivos solicitados:
   - `cobertura.h`
   - `cobertura.c`
   - `main.c`
   - `Makefile`
4. Funções a implementar:
   - `cobertura_minima_bt(...)` — backtracking com poda por limite.
   - `cobertura_gulosa(...)` — seleciona vértice de maior grau restante.
   - `eh_cobertura(...)` — verifica se todas as arestas estão cobertas.
5. Experimento: para $n = 5, 8, 10, 12, 15$, meça o tempo de força bruta e compare com a heurística.

### 3️⃣ Compilação e execução local
1. No terminal, acesse a pasta da prática:
   ```bash
   cd praticas/pratica09
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
   git add praticas/pratica09/
   git commit -m "feat: entrega da pratica 09. Refs #ID"
   git push origin pratica-09
   ```
   > Substitua `#ID` pelo número desta Issue (ex: `Refs #3`).

### 5️⃣ Abrir o Pull Request
1. No GitHub, acesse seu repositório.
2. Clique em **"Compare & pull request"**.
3. **Base:** `main` ← **Compare:** `pratica-09`.
4. Título: `[Entrega] [Prática 09] – Cobertura de Vértices`.
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
└── pratica09/
    ├── cobertura.c
    ├── cobertura.h
    ├── main.c
    └── Makefile
```

## ✅ Critérios de Conclusão
- [ ] Arquivos criados em `praticas/pratica09/`.
- [ ] Backtracking para Cobertura de Vértices com poda.
- [ ] Heurística gulosa (maior grau primeiro).
- [ ] Código enviado para o GitHub com `git push origin pratica-09`.
- [ ] Pull Request aberto apontando para `main`.
- [ ] GitHub Actions exibiu o check verde (✅).
- [ ] Issue vinculada ao Pull Request.