//alunos: Gustavo Hidalgo Salinas 17894628
//Gael 
//João 
//ideias e se fizermos uma função para cada carta, ai fica mais facil eu acho
#include<stdio.h>
int vida, cartam, cartav;
int monstro ( cartam, vida , cartaa){
    //cartam vai ser definidio depois
    vida= vida-cartam;
    return(vida);
}
int poção( cartav, vida ){
    vida=vida+cartav;//carta v vai ser definido depois 
    return(vida);
}
int arma(cartam,cartaa, vida){
    if(cartaa>=cartam){
        vida= vida;
        cartaa=cartam;//vira o valor
        return(vida, cartam);
    }
    if(cartaa<cartam){//vida do monstro maior que o da arma
        vida= vida-(cartam-cartaa);
        return(vida);
    }
}


int main()
{
    printf("----SCOUNDREL GAME----");

    //primeiro me preocupo apenas com o baralho 
    int baralho[38];
    int descarte[38];
    int i, pulo;// criamos a pulo caso o jogador decida pular 
    //COLOCAR SORTEIO 
    //vamos criar varáveis para a vida 
    int vida, vmax=20;//criamos uma vida máxima para a vida nao ultrapassar ela
    for(i=0; i<32; i++){
        printf("%d", baralho[i]);

    }
    return 0;
}
