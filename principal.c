// Alunos: Gustavo Hidalgo Salinas (USP: 17894628)
//         Gael (USP: COLOCAR AQUI)
//         João (USP: 13783075)
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

struct carta{
    int numero;
    char naipe; //Os naipes possíveis são: 'o' (ouros), 'e' (espadas), 'c' (copas) e 'p' (paus) .
    int dentro; //Será utilizado apenas para cartas da categoria arma, caso contrário será sempre idêntico ao número.
};
typedef struct carta carta;

int processar_monstro(int vida_atual, int carta_monstro) {
    int nova_vida = vida_atual - carta_monstro;
    return nova_vida;
}

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
    carta baralho[44];  
    carta descarte[44]; // Vetor para guardar as cartas usadas
    carta mesa[4];     // Vetor que representa os 4 espaços da mesa
    
    int i, j;
    int pulo = 0; // Marcador para saber se o jogador pulou aa Sala (0 = Pode pular, 1 = Pulo bloqueado)
    int sala = 1; // Controla o número da sala atual
    
    int vida = 20; // Vida inicial
    int arma_equipada = 0; // Começa sem arma 0 de dano
    int ultimo_monstro_da_arma = 0; // variável para deixar o teto da arma 
    int posicao = 0;
    int topo_descarte = 0; // Contador de quantas cartas já foram para o descarte- meio que um índice
   
    j = 0;
    for (i=0; i < 52; i++){
        int valor_carta = (i % 13) + 1;
        
        switch (i/13){
            case 0:
                if (valor_carta >= 2 && valor_carta <= 10){
                    baralho[j].numero = valor_carta;
                    baralho[j].naipe = 'o'; // Ouros -> Poção
                    baralho[j].dentro =  valor_carta;
                    j++;
                }
                break;
            case 1: 
                if (valor_carta >= 2 && valor_carta <= 10){
                    baralho[j].numero = valor_carta;
                    baralho[j].naipe = 'e'; // Espadas -> Arma (Corrigido para a regra real!)
                    baralho[j].dentro = valor_carta;
                    j++;
                }
                break;
           case 2:
                if (valor_carta == 1) {
                    baralho[j].numero = 14;
                } else {
                    baralho[j].numero = valor_carta;
                }
                baralho[j].naipe = 'c'; // Copas -> Monstro
                baralho[j].dentro = baralho[j].numero;
                j++;
                break;
           default:
                if (valor_carta == 1) {
                    baralho[j].numero = 14;
                } else {
                    baralho[j].numero = valor_carta;
                }
                baralho[j].naipe = 'p'; // Paus -> Monstro
                baralho[j].dentro = baralho[j].numero;
                j++;
                break;
        }
    }

    //promto agr posto o baralho devemos embaralhar JA DECLAREI O SRAND(TIME(NULL))
    for(int i=43; i>0; i--){
        int j=rand()%(i+1);
        struct carta temp = baralho[i];
        baralho[i] = baralho[j];
        baralho[j] = temp;
    }

//GAEL-vulgo claude- nao esquece de criar o for inicial- para cada jogada

    // AJUSTE: A primeira mesa é puxada aqui fora, para não resetar a mesa toda rodada!
    int topo_baralho = 0;
    for (int k = 0; k < 4; k++) {
        mesa[k] = baralho[topo_baralho];
        topo_baralho++;
    }

    int jogo = 1;
    while (jogo == 1 && vida > 0) {

//GUSTAVO    
        printf("\n=========================================\n");
        printf("SALA ATUAL: %d | Vida: %d/20 | Arma: %d\n", sala, vida, arma_equipada);
        //PULO=0 pode pular 
        if (pulo == 0) {
            printf("Fuga da Sala: DISPONIVEL (Digite 5 para pular)\n");
        } else {
            //pulou a passada
            printf("Fuga da Sala: BLOQUEADA (Disponivel apenas após limpar uma sala)\n");
        }
        
        printf("Cartas ja descartadas: %d\n", topo_descarte);
        printf("-----------------------------------------\n");
        printf("MESA ATUAL:\n");
        int cartas_restantes = 0;
        for (int k = 0; k < 4; k++) {
            if (mesa[k].numero == 0) {
                printf("[%d] [Espaco Vazio]\n", k + 1);
            } else {
                cartas_restantes++;
                if (mesa[k].naipe == 'c') printf("[%d] Monstro (Copas): Forca %d\n", k + 1, mesa[k].numero);
                if (mesa[k].naipe == 'p') printf("[%d] Monstro (Paus): Forca %d\n", k + 1, mesa[k].numero);
                if (mesa[k].naipe == 'e') printf("[%d] Arma (Espadas): Forca %d\n", k + 1, mesa[k].numero);
                if (mesa[k].naipe == 'o') printf("[%d] Pocao (Ouros): Cura %d\n", k + 1, mesa[k].numero);
            }
        }
        printf("======================================\n");
        printf("\nEscolha uma carta (1 a 4), 5 para usar o pulo, ou 0 para sair: ");
        int escolha;
        scanf("%d", &escolha);

        if (escolha == 0) {
            jogo = 0; 
        } 
        else if (escolha == 5) {
            if (pulo == 1) {
                printf("\n[Erro] Voce nao pode pular duas salas seguidas!\n");
            } 
            else {
                printf("\n>>> PULO ATIVADO! Mudando para a proxima sala... <<<\n");
                pulo = 1; // Trava o pulo porque o jogador JÁ PULOU NA PASSADA
                sala++; 
                
                // FILA CIRCULAR AQUI: O '% 44' faz o baralho dar a volta caso passe de 43!
                for (int k = 0; k < 4; k++) {
                    mesa[k] = baralho[topo_baralho % 44];
                    topo_baralho++;
                }
            }
        }
        
        // O João deve continuar desenvolvendo a lógica das escolhas 1 a 4 a partir daqui!
    } // Fechamento do While que estava faltando no seu código original
        
    return 0;
}
