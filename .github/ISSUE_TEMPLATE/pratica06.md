---
name: "Prática 06"
about: "Template para criar a issue da pratica06"
title: "[Prática 06] – Menor Caminho: Dijkstra"
labels: ["pratica06"]
assignees: ''
---

## 🎯 Objetivo
Nesta prática, você irá:
- Implementar o **algoritmo de Dijkstra** com **Min-Heap** (fila de prioridade);
- Reconstruir o caminho mínimo entre dois vértices.

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
   git checkout -b pratica-06
   ```

### 2️⃣ Implementação do código
1. No painel esquerdo do VS Code, localize a pasta `praticas`.
2. Crie uma nova pasta chamada `pratica06`.
3. Dentro dela, desenvolva os arquivos solicitados:
   - `dijkstra.h`
   - `dijkstra.c`
   - `main.c`
   - `Makefile`
4. Estruturas obrigatórias:
   ```c
   typedef struct {
       int vertice;
       int distancia;
   } NoHeap;

   typedef struct {
       NoHeap *dados;
       int capacidade, tamanho;
       int *posicao; // mapeia vértice -> índice no heap
   } MinHeap;
   ```   
5. Funções a implementar:
   - `criar_min_heap`, `extrair_minimo`, `diminuir_chave`
   - `dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred)`
   - `reconstruir_caminho(int origem, int destino, int *pred)`

### 3️⃣ Compilação e execução local
1. No terminal, acesse a pasta da prática:
   ```bash
   cd praticas/pratica06
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
   git add praticas/pratica06/
   git commit -m "feat: entrega da pratica 06. Refs #ID"
   git push origin pratica-06
   ```
   > Substitua `#ID` pelo número desta Issue (ex: `Refs #3`).

### 5️⃣ Abrir o Pull Request
1. No GitHub, acesse seu repositório.
2. Clique em **"Compare & pull request"**.
3. **Base:** `main` ← **Compare:** `pratica-06`.
4. Título: `[Entrega] [Prática 06] – Menor Caminho: Dijkstra`.
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
└── pratica06/
    ├── dijkstra.c
    ├── dijkstra.h
    ├── main.c
    └── Makefile    
```

## ✅ Critérios de Conclusão
- [ ] Arquivos criados em `praticas/pratica06/`.
- [ ] Min-Heap implementado com `insert`, `extract_min`, `decrease_key`.
- [ ] Mapeamento `posicao[vertice]` para `decrease_key` em $O(\log V)$.
- [ ] Dijkstra funcional para custos não-negativos.
- [ ] Reconstrução do caminho mínimo.
- [ ] Código enviado para o GitHub com `git push origin pratica-06`.
- [ ] Pull Request aberto apontando para `main`.
- [ ] GitHub Actions exibiu o check verde (✅).
- [ ] Issue vinculada ao Pull Request.