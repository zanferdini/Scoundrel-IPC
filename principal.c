#include <stdio.h>

// uma função é <tipo><nome>(>tipo 1><par1>;... <TIPON><parn>){
// <decalração de variávei>
//<comand 1>;
//return<valor>); o valor tem que ser o mesmo do tipo da função 
//}
//argc, argv curiosidade 
int fatorial(int x){
    int i,resultado=1;
    for(i=0;i<=x;i++){
        resultado=(x-i)*resultado;

    }
    return(resultado);    
}
int main(){
    int n1,combinacao,n2;
    do{
    printf("digite dois numeros inteiros para calcular a combinaão de n k a k");
    scanf("%d %d", &n1,&n2);
    combinacao=fatorial(n1)/fatorial(n2)*fatorial(n1-n2);
    }while(n1<0 || n2<0);
    printf("teu valor é %d", combinacao);
    return 0;
}
