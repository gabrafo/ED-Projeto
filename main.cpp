#include <iostream>
#include <fstream>
#include <sstream>

#include "header.hpp"
#include "sequence_set.hpp"
#include "trade.hpp"

using namespace std;

void displayMenu() {
    cout << "\n--- Menu ---\n";
    cout << "1. Importar dados do CSV\n";
    cout << "2. Inserir novo elemento\n";
    cout << "3. Buscar elemento\n";
    cout << "4. Sair\n";
}

void importDataFromCSV(const std::string& filename, SequenceSet& sequenceSet) {
    std::ifstream file(filename);
    std::string line;
    bool firstLine = true;
    int count = 1;

    while (std::getline(file, line)) {
        if (firstLine) {
            // Ignorar a primeira linha do CSV
            firstLine = false;
            continue;
        }

        std::istringstream ss(line);
        std::string field;
        long timeref;
        std::string account, code, countryCode, productType, status;
        float value = 0.0; // Valor padrão caso a conversão falhe

        // Ler cada campo do CSV
        std::getline(ss, field, ','); timeref = std::stol(field);  // Converte para long
        std::getline(ss, account, ',');
        std::getline(ss, code, ',');
        std::getline(ss, countryCode, ',');
        std::getline(ss, productType, ',');
        
        // Para o campo value, tentamos fazer a conversão para float
        std::getline(ss, field, ',');
        try {
            value = std::stof(field); // Tenta converter para float
        } catch (const std::invalid_argument& e) { // Intenção é de tratar valores vazios
            std::cout << "Não foi possível ler o valor float" << std::endl;
            value = 0.0f;  // Se falhar, atribui 0.0
        }
        
        std::getline(ss, status, ',');

        // Cria o objeto Trade
        Trade trade(timeref, account, code, countryCode, productType, value, status);
        
        // Insere o elemento no conjunto
        sequenceSet.insert(trade);
        cout << "Linha " << count << " inserida com sucesso!" << endl;
        cout << "Elemento " << trade.getCountryCode() << " inserido." << endl;
        cout << "---" << endl;
        count++;
    }
}

// Função para a interface com o usuário
void userInterface(SequenceSet& sequenceSet) {
    bool dataImported = false;  // Flag para garantir que a importação seja feita primeiro

    int option;
    bool exit = false;

    while (!exit) {
        displayMenu();
        cout << "Escolha uma opção: ";
        cin >> option;

        switch (option) {
            case 1: {
                // Importação de dados via CSV
                if (dataImported) {
                    cout << "Dados já importados! Você pode inserir ou buscar elementos." << endl;
                } else {
                    string filename;
                    cout << "Digite o caminho do arquivo CSV para importação: ";
                    cin >> filename;
                    importDataFromCSV(filename, sequenceSet);
                    dataImported = true;
                }
                sequenceSet.debugPrintAllElements();
                break;
            }
            case 2: {
                // Inserção de elemento
                if (!dataImported) {
                    cout << "Você precisa importar os dados primeiro!" << endl;
                } else {
                    long timeref;
                    string account, code, countryCode, productType, status;
                    float value;

                    cout << "Digite os dados do novo Trade (timeref, account, code, countryCode, productType, value, status):\n";
                    cout << "Timeref: ";
                    cin >> timeref;
                    cout << "Account: ";
                    cin >> account;
                    cout << "Code: ";
                    cin >> code;
                    cout << "CountryCode: ";
                    cin >> countryCode;
                    cout << "ProductType: ";
                    cin >> productType;
                    cout << "Value: ";
                    cin >> value;
                    cout << "Status: ";
                    cin >> status;

                    // Cria o objeto Trade e insere
                    Trade newTrade(timeref, account, code, countryCode, productType, value, status);
                    sequenceSet.insert(newTrade);
                    cout << "Elemento inserido com sucesso!" << endl;
                }
                break;
            }
            case 3: {
                // Busca de elemento
                if (!dataImported) {
                    cout << "Você precisa importar os dados primeiro!" << endl;
                } else {
                    long timeref;
                    string account, code, countryCode, productType, status;
                    float value;

                    cout << "Digite os dados do Trade para busca (timeref, account, code, countryCode, productType, value, status):\n";
                    cout << "Timeref: ";
                    cin >> timeref;
                    cout << "Account: ";
                    cin >> account;
                    cout << "Code: ";
                    cin >> code;
                    cout << "CountryCode: ";
                    cin >> countryCode;
                    cout << "ProductType: ";
                    cin >> productType;
                    cout << "Value: ";
                    cin >> value;
                    cout << "Status: ";
                    cin >> status;

                    // Criação do Trade para busca
                    Trade searchTrade(timeref, account, code, countryCode, productType, value, status);

                    std::cout << searchTrade.toString() << std::endl;

                    try {
                        Trade foundTrade = sequenceSet.search(searchTrade);
                        cout << "Trade encontrado:\n";
                        cout << foundTrade.toString() << endl;  // Mostra os detalhes do Trade
                    } catch (const exception& e) {
                        cout << "Erro: " << e.what() << endl;
                    }
                }
                break;
            }
            case 4: {
                // Sair
                cout << "Saindo...\n";
                exit = true;
                break;
            }
            default: {
                cout << "Opção inválida, tente novamente.\n";
                break;
            }
        }
    }
}

int main() {
    SequenceSet sequenceSet;
    
    // Chama a interface do usuário
    userInterface(sequenceSet);

    return 0;
}