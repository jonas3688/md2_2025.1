#include <stdio.h>
#define PULA_LINHA printf("\n");

//protpotipos funcoes
int mdc(int a,int b);
int verificaPrimo(int a);
int inversoDivisoesSucessivas(int G, int n);
int calculaTotiente(int n);
int exponenciacaoModular(int base, int expoente, int modulo);

int main(){

	int H,G,n,x,n1;

	printf("Digite o valor de H:\n");
	scanf("%d",&H);
	
	printf("Digite o valor de G:\n");
	scanf("%d",&G);

	printf("Digite o valor de n:\n");
	scanf("%d",&n);

	printf("Digite o valor de x:\n");
	scanf("%d",&x);

	printf("Digite o valor de n1H:\n");
	scanf("%d",&n1);

	printf("Verificando se G e n são primos...");
	PULA_LINHA
	if (mdc(G,n) != 1){
		printf("G e n não são coprimos...");
		PULA_LINHA
		return -1;
	}
	printf("G e nn são coprimos...");
	PULA_LINHA

	printf("Calculando inverso de G em Zn");
	PULA_LINHA
	int inverso = inversoDivisoesSucessivas(G,n);
	//verficiar se o inverso esta dentro de Zn
	while(inverso<0){
		inverso = inverso + n;
	}
	printf("O inverso de G em n é : %d",inverso);
	PULA_LINHA

	printf("Dividino H por G para encontrar a...");
	int a = (H*inverso)%n;

	printf("Verificando se a e n1 são coprimos...");
	PULA_LINHA
	if (mdc(a,n1) != 1){
		printf("a e n1 não são coprimos...");
		PULA_LINHA
	}
	else {
		printf("a e n1 são coprimos...");
		PULA_LINHA
	}

	int n1totiente,expoente_reduzido,modulo_reducao;
	printf("Verificando se n1 é primo...");
	if (verificaPrimo(n1) == 0){
		printf("n1 não é primo...");
		PULA_LINHA
		n1totiente = calculaTotiente(n1);
        printf("φ(%d) = %d", n1, n1totiente);
        PULA_LINHA
        expoente_reduzido = x % n1totiente;
        printf("Expoente reduzido: x mod φ(n1) = %d mod %d = %d", x, n1totiente, expoente_reduzido);
        PULA_LINHA

	}
	else{
		printf("n1 é um número primo...");
		PULA_LINHA
		modulo_reducao = n1 - 1;
        expoente_reduzido = x % modulo_reducao;
        printf("Expoente reduzido: x mod (n1-1) = %d mod %d = %d", x, modulo_reducao, expoente_reduzido);
        PULA_LINHA
	}

	int parte_inteira, resto_divisao, divisor_q;
	if(verificaPrimo(n1) == 1) {
		divisor_q = n1 - 1; // aplica Fermat
	} else {
		divisor_q = n1totiente; // aplica Euler
	}

	parte_inteira = expoente_reduzido / divisor_q;
	resto_divisao = expoente_reduzido % divisor_q;
	printf("Decompondo o expoente...");
	PULA_LINHA
	printf("%d = %d * %d + %d", expoente_reduzido, parte_inteira, divisor_q, resto_divisao);
	PULA_LINHA

	printf("Expressão reescrita: ");
	PULA_LINHA
	printf("(%d^%d mod %d) = ((%d^%d)^%d mod %d) * (%d^%d mod %d) mod %d", a, expoente_reduzido, n1, a, parte_inteira, divisor_q, n1, a, resto_divisao, n1, n1);
	PULA_LINHA

	int base_elevada_parteInteira = exponenciacaoModular(a, parte_inteira, n1);
	int base_elevadaQ = exponenciacaoModular(base_elevada_parteInteira, divisor_q, n1);
	int base_elevada_resto = exponenciacaoModular(a, resto_divisao, n1);
	printf("Calculando valores intermediarios...");
	PULA_LINHA
	printf("a^parte_inteira mod n1 = %d^%d mod %d = %d", a, parte_inteira, n1, base_elevada_parteInteira);
	PULA_LINHA
	printf("(a^parte_inteira)^q mod n1 = %d^%d mod %d = %d", base_elevada_parteInteira, divisor_q, n1, base_elevadaQ);
	PULA_LINHA
	printf("a^resto mod n1 = %d^%d mod %d = %d", a, resto_divisao, n1, base_elevada_resto);	
	
	int resultado_final = (base_elevadaQ * base_elevada_resto) % n1;
	printf("Resultado final:");
	printf("(%d * %d) mod %d = %d", base_elevadaQ, base_elevada_resto, n1, resultado_final);
	printf("Valor final: %d^%d mod %d ≡ %d", a, x, n1, resultado_final);
	
	return 0;
}

int exponenciacaoModular(int base, int expoente, int modulo) {
    int resultado = 1;
    base = base % modulo; 
    
    while(expoente > 0) {
        
        if(expoente % 2 == 1) {
            resultado = (resultado * base) % modulo;
        }
        
        expoente = expoente / 2;
        
        base = (base * base) % modulo;
    }
    return resultado;
}

int calculaTotiente(int n) {
    int resultado = n;
    
    
    if(n % 2 == 0) {
        resultado -= resultado / 2;
        while(n % 2 == 0) n /= 2;
    }
    
   
    for(int p = 3; p*p <= n; p += 2) {
        if(n % p == 0) {
            resultado -= resultado / p;
            while(n % p == 0) n /= p;
        }
    }
    
    //fator primo final
    if(n > 1) resultado -= resultado / n;
    
    return resultado;
}

int inversoDivisoesSucessivas(int G, int n) {
		int t = 0, t2 = 1;
		int r = n, r2 = G;
		int q;
	
		while (r2 != 0) {
			q = r / r2;
	
			int temp = t2;
			t2 = t - q * t2;
			t = temp;
	
			temp = r2;
			r2 = r - q * r2;
			r = temp;
		}
	
		if (t < 0)
			t += n;
	
		return t;
	}

int mdc(int a,int b){
	int resto;
	// o maior numero tem que estar na posicao do a
	if (b>a){
		int temp = a;
		b = a;
		a = temp;
	}

	//algoritmo de euclides
	do{
		resto = a%b;
		if (resto==0)
			return b;
		a = b;
		b = resto;
	}while(1);

}

int verificaPrimo(int a){

	if(a<=1) return 0; 

	for(int i = 2; i<=a; i++){
		if(mdc(a,i) > 1)
			return 0; // não é primo
	}

	return 1; // é primo
}
