// Alunos: Gustavo Hidalgo Salinas (USP: 17894628)
//         Gael (USP: COLOCAR AQUI)
//         João (USP: COLOCAR AQUI)
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
// Função para processar o dano do monstro.
//rcebe a vida atual e o valor do monstro, retorna a nova vida.

int processar_monstro(int vida_atual, int carta_monstro) {
    int nova_vida = vida_atual - carta_monstro;
    return nova_vida;
}

// Função para processar a cura da poção.
//garantirque a vida não ultrapasse o limite máximo de 20.

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
    srand(time(NULL));//aleatoriedade
    int baralho[44];  
    int descarte[44];
    int i;
    int pulo = 0; // Marcador para saber se o jogador pulou aa Sala
    
    int vida = 20; // Vida inicial
    int arma_equipada = 0; // Começa sem arma 0 de dano
    int ultimo_monstro_da_arma = 0; // variável para deixar o teto da arma 
    int posicao=0;
   
    //após declaração das variávei seu pensei sobre os naipes, as 26 primeiras cartas
    // serão monstro, ta na ordem de força do baralho ein
   
   
    //// colocamos  os 26 Monstros (Valores positivos: 2 a 14, duas vezes)
    for (int naipe = 0; naipe < 2; naipe++) {
        for (int valor = 2; valor <= 14; valor++) {
            baralho[posicao] = valor; 
            posicao++;
        }
    }
    //vammos colocar as 9 armas agr dos 26-34
    // Usamos um loop que vai direto de 26 até 34 nas posições
    int valor_carta = 2;//2 é o menor valor posível
    for (posicao = 26; posicao <= 34; posicao++) {
        baralho[posicao] = -valor_carta; 
        valor_carta++;
    }
    //poções vão ser as cartass restantes
    valor_carta = 2;
    for (posicao = 37; posicao <= 45; posicao++) {
        baralho[posicao] = -(valor_carta + 100); 
        valor_carta++;
    }
    //promto agr posto o baralho devemos embaralhar JA DECLAREI O SRAND(TIME(NULL))
    for(int i=44-1; i>0; i--){
        int j=rand()%(i+1);
        int temp=baralho[i];
        baralho[i]=baralho[j];
        baralho[j]=temp;
    }
    
    return 0;
}
