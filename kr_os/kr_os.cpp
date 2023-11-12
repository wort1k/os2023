#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

namespace balance {
    double account1Balance = 1000.0;
    std::vector<std::vector<double>> transactions = { { 200.0, -50.0, 300.0, -150.0 }, { -100.0, 50.0, -200.0, 100.0 } };
    std::vector<double> scenarioBalance(transactions.size(), account1Balance);
}

void processTransaction(const int scenario, double& balance, double amount) {
    if (amount > 0) {
        balance += amount;
        std::cout << "—ценарий: " << scenario << '\t' << " ќпераци€: +" << amount << "\t текущий счет: " << balance << std::endl;
    }
    else {
        if (balance >= -amount) {
            balance += amount;
            std::cout << "—ценарий: " << scenario << '\t' << " ќпераци€: " << amount << "\t текущий счет: " << balance << std::endl;
        }
    }
}
void threadFunction(int id) {

    for (int i = 0; i < balance::transactions[id-1].size(); ++i) {
        processTransaction(id, balance::scenarioBalance[id-1], balance::transactions[id-1][i]);
    }

}

int main() {
    std::setlocale(LC_ALL, "RUSSIAN");
    double account1Balance = 1000.0;
    const int numThreads = balance::transactions.size();
    std::vector<std::thread> threads;
    std::thread get([&]() {
        for (int num = 0; num < 10; ++num) {
            std::cout << "текущий счет: ";
            for (auto i : balance::scenarioBalance) {
                std::cout << i << " ";
            }
            std::cout << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        });
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(threadFunction, i + 1);
    }
    for (std::thread& t : threads) {
        t.join();
    }
    get.join();
    return 0;
}
