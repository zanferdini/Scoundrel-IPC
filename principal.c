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

int calcular_dano_arma(int carta_monstro, int valor_arma, int vida_atual, int ultimo_monstro) {
    if (ultimo_monstro > 0 && carta_monstro >= ultimo_monstro) {
        printf("\n>>> Monstro muito forte para a sequencia da arma! Lutou desarmado e tomou dano inteiro! <<<\n");
        vida_atual = vida_atual - carta_monstro;
    } else {
        if (valor_arma >= carta_monstro) {
            return vida_atual; 
        } else {
            vida_atual = vida_atual - (carta_monstro - valor_arma); 
            return vida_atual; 
        }
    }
    return vida_atual;
}

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
    
    int cartas_restantes_no_total = 44; // Termômetro para o fim da Fila Circular
   
    j = 0;
    for (i=0; i < 52; i++){
        int valor_carta = (i % 13) + 1;
        
        switch (i/13){
            case 0:
                if (valor_carta >= 2 && valor_carta <= 10){
                    baralho[j].numero = valor_carta;
                    baralho[j].naipe = 'o';
                    baralho[j].dentro =  valor_carta;
                    j++;
                }
                break;
            case 1: 
                if (valor_carta >= 2 && valor_carta <= 10){
                    baralho[j].numero = valor_carta;
                    baralho[j].naipe = 'e'; // Ajustado: Case 1 gera Espadas (Armas)
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
                baralho[j].naipe = 'c'; // Ajustado: Case 2 gera Copas (Monstros)
                baralho[j].dentro = baralho[j].numero;
                j++;
                break;
           default:
                if (valor_carta == 1) {
                    baralho[j].numero = 14;
                } else {
                    baralho[j].numero = valor_carta;
                }
                baralho[j].naipe = 'p';
                baralho[j].dentro = baralho[j].numero;
                j++;
                break;
        }
    }

    for(int i=43; i>0; i--){
        int j=rand()%(i+1);
        carta temp = baralho[i];
        baralho[i] = baralho[j];
        baralho[j] = temp;
    }

    // Inicialização da primeira mesa tem que fazer manualmente- depois vai ajustando conforme passa
    int topo_baralho = 0;
    for (int k = 0; k < 4; k++) {
        mesa[k] = baralho[topo_baralho];
        topo_baralho++;
    }

    int jogo = 1;
    while (jogo == 1 && vida > 0) { 
        //aqui vamos mostrar a sala toda a rodada, primeiro de tudo!
        printf("\n=========================================\n");
        printf("SALA ATUAL: %d | Vida: %d/20 | Arma: %d (Teto: %d)\n", sala, vida, arma_equipada, ultimo_monstro_da_arma);
        
        if (pulo == 0) {
            printf("Fuga da Sala: DISPONIVEL (Digite 5 para pular)\n");
        } else {
            printf("Fuga da Sala: BLOQUEADA (Disponivel apenas após limpar uma sala)\n");
        }
        
        printf("Cartas ja descartadas: %d | Restantes no Jogo: %d\n", topo_descarte, cartas_restantes_no_total);
        printf("-----------------------------------------\n");
        printf("MESA ATUAL:\n");
        int cartas_restantes_na_mesa = 0;
        for (int k = 0; k < 4; k++) {
            if (mesa[k].numero == 0) {
                printf("[%d] [Espaco Vazio]\n", k + 1);
            } else {
                cartas_restantes_na_mesa++;
                if (mesa[k].naipe == 'e') printf("[%d] Arma (Espadas): Forca %d\n", k + 1, mesa[k].numero);
                if (mesa[k].naipe == 'p') printf("[%d] Monstro (Paus): Forca %d\n", k + 1, mesa[k].numero);
                if (mesa[k].naipe == 'c') printf("[%d] Monstro (Copas): Forca %d\n", k + 1, mesa[k].numero);
                if (mesa[k].naipe == 'o') printf("[%d] Pocao (Ouros): Cura %d\n", k + 1, mesa[k].numero);
            }
        }
        printf("======================================\n");
        
        printf("\nEscolha uma carta (1 a 4), 5 para usar o pulo, ou 0 para sair: ");
        //guardamos a escolha
        int escolha;
        scanf("%d", &escolha);

        if (escolha == 0) {
            jogo = 0; //pediu para sair
        } 
        else if (escolha == 5) {
            if (cartas_restantes_na_mesa < 4) {
                printf("\n[Erro] Voce nao pode pular! Ja interagiu com cartas desta sala.\n");//tentou pular depois de mexer em algo
            }
            else if (pulo == 1) {
                printf("\n[Erro] Voce nao pode pular duas salas seguidas!\n");//tentou pular duas vezes
            } 
            else {
                printf("\n>>> PULO ATIVADO! Mudando para a proxima sala... <<<\n");
                pulo = 1; 
                sala++;//muda a sala 
                
                for (int k = 0; k < 4; k++) {
                    mesa[k] = baralho[topo_baralho % 44];
                    topo_baralho++;
                }
            }
        }
        else if (escolha >= 1 && escolha <= 4) {
            int indice = escolha - 1;

            if (mesa[indice].numero != 0) {
                
                //processar as cartas- utilizamos as funções criadas para melhor organização0
                
                // 1. Caso seja Poção (Ouros)
                if (mesa[indice].naipe == 'o') {
                    vida = processarpocao(vida, mesa[indice].numero);
                }
                // 2. Caso seja Arma (Espadas)
                else if (mesa[indice].naipe == 'e') {
                    arma_equipada = mesa[indice].numero;
                    ultimo_monstro_da_arma = 0; // Equipar nova arma zera o teto de sequência
                }
                // 3. Caso seja Monstro (Copas ou Paus)
                else if (mesa[indice].naipe == 'c' || mesa[indice].naipe == 'p') {
                    if (arma_equipada > 0) {
                        vida = calcular_dano_arma(mesa[indice].numero, arma_equipada, vida, ultimo_monstro_da_arma);
                        ultimo_monstro_da_arma = mesa[indice].numero;
                    } else {
                        vida = processar_monstro(vida, mesa[indice].numero);
                    }
                }

                //sistema de limpesa- aqui utilizamos a ideia de lista circular para facilitar a mecânica "pulo"
                descarte[topo_descarte] = mesa[indice];
                topo_descarte++;
                mesa[indice].numero = 0; // libera o espaço na mesa
                cartas_restantes_na_mesa--;
                
                cartas_restantes_no_total--; // controle lista circula diminuindo- vai acabar qnd chegar  azero as cartas

                // condição de parada (vitoria)
                if (cartas_restantes_no_total <= 0) {
                    jogo = 2; 
                }
                // avanço de sala (quando resta 1 ou 0 cartas na mesa)
                else if (cartas_restantes_na_mesa <= 1) {
                    printf("\n>>> Sala limpa! Avançando para a proxima sala. <<<\n");
                    sala++;
                    pulo = 0; // Restaura o direito de usar a fuga
                    
                    for (int k = 0; k < 4; k++) {
                        // Só puxa se houver cartas inéditas disponíveis em jogo
                        if (cartas_restantes_no_total > cartas_restantes_na_mesa) {
                            mesa[k] = baralho[topo_baralho % 44];
                            topo_baralho++;
                        } else {
                            mesa[k].numero = 0; // Deixa o slot vazio se o baralho real zerar
                        }
                    }
                }

            } else {
                printf("\n[Erro] Esse espaco ja esta vazio! Escolha outro.\n");
            }
        } else {
            printf("\nOpcao invalida!\n");
        }
    }

    // m,ensagens de encerramento do jogo fora do loop- as opções de sair
    if (vida <= 0) {
        printf("\nDERROTA- sua vida zero :(\n");
    } 
    else if (jogo == 2) {
        printf("\nPARABENS! voce acabou o baralho e VENCEU!\n");
    } else {
        printf("\njogo encerrado voluntariamente, até a proxima.\n");
    }
        
    return 0;
}
