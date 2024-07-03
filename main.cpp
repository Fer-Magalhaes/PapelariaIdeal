#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// Definicão da estrutura Item
struct Item {
    int id;
    string nome;
    double valor;
    int estoque;
};

// Definicão da estrutura CarrinhoItem
struct CarrinhoItem {
    Item item;
    int quantidade;
};

// Funcão para ler o arquivo CSV e adicionar os dados à estrutura
void LeArquivo(const string& caminhoArquivo, vector<Item>& itens) {
    ifstream arquivo(caminhoArquivo);
    string linha;

    // Ignorar a primeira linha (cabecalhos)
    getline(arquivo, linha);

    // Ler o arquivo linha por linha
    while (getline(arquivo, linha)) {
        istringstream stream(linha);
        string campo;
        Item item;

        // Ler o id
        getline(stream, campo, ',');
        item.id = stoi(campo);

        // Ler o nome
        getline(stream, campo, ',');
        item.nome = campo;

        // Ler o valor
        getline(stream, campo, ',');
        item.valor = stod(campo);

        // Ler o estoque
        getline(stream, campo, ',');
        item.estoque = stoi(campo);

        // Adicionar o item ao vetor
        itens.push_back(item);
    }
}

// Funcão para exibir o estoque
void ExibirEstoque(const vector<Item>& itens) {
    cout << "Bem-vindo(a) a Papelaria Ideal!\n========== Estoque ==========" << endl;
    for (const Item& item : itens) {
        cout << item.id << ". " << item.nome << ": Preco R$ " << item.valor << " | Estoque: " << item.estoque << endl;
    }
}

// Funcão para exibir os detalhes de uma compra
void ExibirCompra(const CarrinhoItem& carrinhoItem) {
    cout << "Item: " << carrinhoItem.item.nome << " | Quantidade: " << carrinhoItem.quantidade 
         << " | Preco unitario: R$ " << carrinhoItem.item.valor << " | Subtotal: R$ " << carrinhoItem.item.valor * carrinhoItem.quantidade << endl;
}

// Funcão para exibir o carrinho
void ExibirCarrinho(const vector<CarrinhoItem>& carrinho) {
    cout << "\n========== Cupom Fiscal ==========\n";
    double total = 0.0;
    for (const CarrinhoItem& carrinhoItem : carrinho) {
        cout << "Item: " << carrinhoItem.item.nome << " | Quantidade: " << carrinhoItem.quantidade 
             << " | Preco unitario: R$ " << carrinhoItem.item.valor << " | Subtotal: R$ " << carrinhoItem.item.valor * carrinhoItem.quantidade << endl;
        total += carrinhoItem.item.valor * carrinhoItem.quantidade;
    }
    cout << "\nTotal da compra: R$ " << total << endl;
}

// Funcão para atualizar o arquivo CSV com os itens comprados
void AtualizaItens(const string& caminhoArquivo, const vector<Item>& itens) {
    ofstream arquivo(caminhoArquivo);

    // Escrever os cabecalhos
    arquivo << "id,nome,valor,estoque\n";

    // Escrever cada item no arquivo
    for (const Item& item : itens) {
        arquivo << item.id << "," << item.nome << "," << item.valor << "," << item.estoque << "\n";
    }

    arquivo.close();
}

// Funcão para cadastrar novos itens se o arquivo não existir
void CadastrarDados(const string& caminhoArquivo) {
    vector<Item> itens = {
        {1, "Caneta", 1.50, 100},
        {2, "Lapis", 0.75, 200},
        {3, "Borracha", 0.50, 150},
        {4, "Caderno", 5.00, 80},
        {5, "Marcador", 2.00, 60},
        {6, "Tesoura", 3.50, 50},
        {7, "Cola", 1.00, 120},
        {8, "Papel A4", 20.00, 40},
        {9, "Grampeador", 15.00, 30},
        {10, "Calculadora", 25.00, 20}
    };

    ofstream arquivo(caminhoArquivo);

    // Escrever os cabecalhos
    arquivo << "id,nome,valor,estoque\n";

    // Escrever cada item no arquivo
    for (const Item& item : itens) {
        arquivo << item.id << "," << item.nome << "," << item.valor << "," << item.estoque << "\n";
    }

    arquivo.close();
}

int main() {
    vector<Item> itens;
    vector<CarrinhoItem> carrinho;
    string caminhoArquivo = "estoque.csv";
    int i = 0;

    // Verificar se o arquivo existe
    ifstream arquivo(caminhoArquivo);
    if (!arquivo.good()) {
        cout << "Arquivo nao encontrado. Cadastrando novos dados...\n";
        CadastrarDados(caminhoArquivo);
    }
    arquivo.close();

    // Ler o arquivo e preencher o vetor de itens
    LeArquivo(caminhoArquivo, itens);

    ExibirEstoque(itens);

    cout << "\nIniciando compra...\n";

    // Loop para adicionar itens ao carrinho
    while (true) {
        char saida;
        int idItem;
        int quantidade;

        if (i != 0) {
            ExibirEstoque(itens);
        }

        cout << "\nEscolha o numero do item que deseja comprar (1-10): ";
        cin >> idItem;

        cout << "\nDigite a quantidade que deseja comprar: ";
        cin >> quantidade;

        bool itemEncontrado = false;
        for (Item& item : itens) {
            if (item.id == idItem) {
                itemEncontrado = true;
                if (item.estoque >= quantidade) {
                    item.estoque -= quantidade;
                    cout << "\nItem adicionado ao carrinho com sucesso!\n";
                    CarrinhoItem carrinhoItem = {item, quantidade};
                    carrinho.push_back(carrinhoItem);
                    ExibirCompra(carrinhoItem);  // Exibir os detalhes da compra
                } else {
                    cout << "\nEstoque insuficiente. Quantidade disponivel: " << item.estoque << endl;
                }
                break;
            }
        }

        if (!itemEncontrado) {
            cout << "\nItem não encontrado.\n";
        }

        cout << "\nDeseja adicionar mais itens ao carrinho? (S/N): ";
        cin >> saida;

        if (saida == 'N' || saida == 'n') {
            break;
        } else if (saida != 'S' && saida != 's') {
            cout << "\nOpcão invalida. Finalizando compra...\n";
            break;
        }
        i++;
    }

    // Exibir o carrinho final e detalhes das compras
    ExibirCarrinho(carrinho);

    cout << "\nDeseja Realizar a compra? (S/N): ";
    char confirmacao;
    cin >> confirmacao;
    if (confirmacao != 'S' && confirmacao != 's') {
        cout << "\nCompra cancelada. Volte sempre!\n";
        return 0;
    }

    // Atualizar o arquivo CSV com os itens comprados
    AtualizaItens(caminhoArquivo, itens);

    cout << "\nObrigado por comprar na Papelaria Ideal. Volte sempre!\n";

    return 0;
}
