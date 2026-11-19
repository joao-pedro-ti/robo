#include <iostream>
#include <string>
#include <thread>
#include <chrono>

class RoboHumano {
private:
    std::string nome;
    bool emMovimento;
    bool carregandoObjeto;
    std::string objetoAtual;
    int nivelBateria;
    float velocidadeAtual;

public:
    RoboHumano(std::string n) : nome(n), emMovimento(false), 
                                carregandoObjeto(false), objetoAtual(""),
                                nivelBateria(100), velocidadeAtual(0.0f) {}

    // Função auxiliar para simular tempo de execução
    void aguardar(int milissegundos) {
        std::this_thread::sleep_for(std::chrono::milliseconds(milissegundos));
    }

    // Verifica se há bateria suficiente
    bool verificarBateria(int consumo) {
        if (nivelBateria < consumo) {
            std::cout << "[ALERTA] Bateria insuficiente! Nível: " 
                      << nivelBateria << "%\n";
            return false;
        }
        return true;
    }

    // ANDAR - movimento lento e controlado
    void andar(int passos) {
        if (!verificarBateria(passos * 1)) return;
        
        std::cout << "\n=== " << nome << " iniciando caminhada ===\n";
        emMovimento = true;
        velocidadeAtual = 2.0f; // km/h
        
        for (int i = 1; i <= passos; i++) {
            std::cout << "Passo " << i << "/" << passos 
                      << " | Velocidade: " << velocidadeAtual << " km/h\n";
            aguardar(300);
            nivelBateria -= 1;
        }
        
        emMovimento = false;
        velocidadeAtual = 0.0f;
        std::cout << "Caminhada concluída. Bateria: " << nivelBateria << "%\n";
    }

    // CORRER - movimento rápido
    void correr(int passos) {
        if (!verificarBateria(passos * 3)) return;
        
        std::cout << "\n=== " << nome << " iniciando corrida ===\n";
        emMovimento = true;
        velocidadeAtual = 10.0f; // km/h
        
        for (int i = 1; i <= passos; i++) {
            std::cout << "Corrida " << i << "/" << passos 
                      << " | Velocidade: " << velocidadeAtual << " km/h\n";
            aguardar(150);
            nivelBateria -= 3;
        }
        
        emMovimento = false;
        velocidadeAtual = 0.0f;
        std::cout << "Corrida concluída. Bateria: " << nivelBateria << "%\n";
    }

    // PEGAR ALGO
    void pegar(std::string objeto) {
        if (!verificarBateria(2)) return;
        
        if (carregandoObjeto) {
            std::cout << "[ERRO] Já estou carregando: " << objetoAtual << "\n";
            return;
        }
        
        std::cout << "\n=== " << nome << " pegando objeto ===\n";
        std::cout << "Abrindo mão...\n";
        aguardar(400);
        std::cout << "Aproximando do objeto: " << objeto << "\n";
        aguardar(400);
        std::cout << "Fechando dedos...\n";
        aguardar(400);
        
        carregandoObjeto = true;
        objetoAtual = objeto;
        nivelBateria -= 2;
        
        std::cout << "Objeto '" << objeto << "' pego com sucesso!\n";
    }

    // SOLTAR ALGO
    void soltar() {
        if (!verificarBateria(1)) return;
        
        if (!carregandoObjeto) {
            std::cout << "[ERRO] Não estou carregando nenhum objeto.\n";
            return;
        }
        
        std::cout << "\n=== " << nome << " soltando objeto ===\n";
        std::cout << "Abrindo dedos...\n";
        aguardar(400);
        std::cout << "Liberando: " << objetoAtual << "\n";
        aguardar(400);
        
        carregandoObjeto = false;
        objetoAtual = "";
        nivelBateria -= 1;
        
        std::cout << "Objeto solto com sucesso!\n";
    }

    // Mostrar status
    void status() {
        std::cout << "\n--- STATUS DO ROBÔ ---\n";
        std::cout << "Nome: " << nome << "\n";
        std::cout << "Bateria: " << nivelBateria << "%\n";
        std::cout << "Movimento: " << (emMovimento ? "Sim" : "Não") << "\n";
        std::cout << "Carregando: " << (carregandoObjeto ? objetoAtual : "Nada") << "\n";
        std::cout << "Velocidade: " << velocidadeAtual << " km/h\n";
        std::cout << "----------------------\n";
    }
};

int main() {
    RoboHumano robo("Atlas");
    
    robo.status();
    
    // Sequência de tarefas básicas
    robo.andar(3);
    robo.correr(2);
    robo.pegar("caixa");
    robo.andar(2);
    robo.soltar();
    
    robo.status();
    
    return 0;
}