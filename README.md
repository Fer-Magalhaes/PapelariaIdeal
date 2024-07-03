
# Papelaria Ideal

Este projeto simula um sistema de gerenciamento de estoque e carrinho de compras para uma papelaria. Ele lê os dados de um arquivo CSV, permite ao usuário adicionar itens ao carrinho, atualizar o estoque e salvar as mudanças de volta no arquivo CSV.

## Funcionalidades

- Leitura de dados de um arquivo CSV.
- Exibição do estoque atual.
- Adição de itens ao carrinho de compras.
- Exibição do carrinho de compras e do total da compra.
- Atualização do arquivo CSV com o estoque restante após a compra.
- Cadastro automático de 10 itens fictícios se o arquivo CSV não existir.

## Como Executar

### Pré-requisitos

- Compilador C++ (g++ ou similar)

### Passo a Passo

1. Clone este repositório:
   ```bash
   git clone https://github.com/Fer-Magalhaes/PapelariaIdeal.git
   ```

2. Navegue até o diretório do projeto:
   ```bash
   cd PapelariaIdeal
   ```

3. Compile o código:
   ```bash
   g++ -o controle_estoque controle_estoque_com_cadastro.cpp
   ```

4. Execute o programa:
   ```bash
   ./controle_estoque
   ```

Se o arquivo `estoque.csv` não existir, ele será criado automaticamente com 10 itens fictícios.

## Estrutura do Código

### Estruturas

- **Item**: Representa um item no estoque.
  ```cpp
  struct Item {
      int id;
      string nome;
      double valor;
      int estoque;
  };
  ```

- **CarrinhoItem**: Representa um item no carrinho de compras.
  ```cpp
  struct CarrinhoItem {
      Item item;
      int quantidade;
  };
  ```

### Funções

- **LeArquivo**: Lê o arquivo CSV e preenche um vetor de itens.
- **ExibirEstoque**: Exibe o estoque atual.
- **ExibirCompra**: Exibe os detalhes de uma compra.
- **ExibirCarrinho**: Exibe o conteúdo do carrinho de compras e o total.
- **AtualizaItens**: Atualiza o arquivo CSV com os itens comprados.
- **CadastrarDados**: Cadastra automaticamente 10 itens fictícios se o arquivo CSV não existir.

### Fluxo do Programa

1. Verificação da existência do arquivo `estoque.csv`.
2. Se o arquivo não existir, cadastro de 10 itens fictícios.
3. Leitura do arquivo `estoque.csv`.
4. Exibição do estoque atual.
5. Adição de itens ao carrinho de compras.
6. Exibição do carrinho e confirmação da compra.
7. Atualização do arquivo CSV com o estoque restante.

## Exemplo de Arquivo `estoque.csv`

```
id,nome,valor,estoque
1,Caneta,1.50,100
2,Lápis,0.75,200
3,Borracha,0.50,150
4,Caderno,5.00,80
5,Marcador,2.00,60
6,Tesoura,3.50,50
7,Cola,1.00,120
8,Papel A4,20.00,40
9,Grampeador,15.00,30
10,Calculadora,25.00,20
```

## Contribuição

Sinta-se à vontade para contribuir com melhorias para este projeto. Abra uma issue ou envie um pull request com suas sugestões e melhorias.

## Licença

Este projeto está licenciado sob a Licença MIT. Consulte o arquivo [LICENSE](LICENSE) para obter mais informações.
