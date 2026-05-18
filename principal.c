/ Alunos: Gustavo Hidalgo Salinas (USP: 17894628)
//         Gael (USP: COLOCAR AQUI)
//         João (USP: COLOCAR AQUI)

#include <stdio.h>

// Função para processar o dano do monstro.
   Recebe a vida atual e o valor do monstro, retorna a nova vida.

int processar_monstro(int vidaatual, int cartamonstro) {
    int nova_vida = vida_atual - carta_monstro;
    return nova_vida;
}

// Função para processar a cura da poção.
  // Garante que a vida não ultrapasse o limite máximo de 20.

int processarpocao(int vida_atual, int carta_pocao) {
    int nova_vida = vida_atual + carta_pocao;
    
    if (nova_vida > 20) {
        nova_vida = 20; // Limite máximo de vida
    }
    
    return nova_vida;
}


int calcular_dano_arma(int carta_monstro, int valor_arma, int vida_atual) {
    if (valor_arma >= carta_monstro) {
        return vida_atual; // Não toma dano, a vida continua igual
    } else {
        vida_atual = vida_atual - (carta_monstro - valor_arma); 
        return vida_atual; // Devolve a nova vida calculad
    }
}
//vamos precisar pegar uma variável para guardar o valor do monstro ultimo, vai virar o teto da arma!
int main() {
    printf("---- SCOUNDREL GAME ----\n");
    int baralho[44];  
    int descarte[44];
    int i;
    int pulo = 0; // Marcador para saber se o jogador pulou aa Sala
    
    int vida = 20; // Vida inicial
    int arma_equipada = 0; // Começa sem arma 0 de dano
    int ultimo_monstro_da_arma = 0; // variável para deixar o teto da arma 

    // Loop temporário de teste para exibir o baralho
    for (i = 0; i < 44; i++) {
        // Por enquanto o baralho está vazio, vai imprimir lixo de memória até nos preenchermos
        printf("%d ", baralho[i]);
    }
    printf("\n");

    return 0;
}
