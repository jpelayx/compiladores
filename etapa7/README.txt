OTIMIZAÇÕES IMPLEMENTADAS:

- avaliação de operações com constantes 
	loadI c1 => r1   --->  
	op r1, r2 => r3       opI r2, c1 => r3

	loadI c1 => r1   --->
	opI r1, c2 => r2      loadI (c1 op c2) => r2

	Otimização com uma janela de tamanho 3. 
	E.g.:
	loadI c1 => r1   --->
	loadI c2 => r2        loadI c2 => r2  
	op r1, r2 => r3       opI r2, c1 => r3

- remoção de instruções inúteis do tipo 
	- addI r1, 0 => r2
	- subI r1, 0 => r2 
	- rsubI r1, 0 => r2 
	- multI r1, 1 => r2
	- divI r1, 1 => r2

- uso de instruções assembly 
	- addl reg, $1 --> inc reg
	- subl reg, $1 --> dec reg

- simplificação de expressões aritméticas do tipo 
	- s1 = s2 * 2 --> s1 = s2 + s2
    - s1 = s2 / s2 --> s1 = 1
    - s1 = s2 - s2  --> s1 = 0
    - s1 = s2 * 0 --> s1 = 0

- remoção de jumps inúteis do tipo 
	jumpI L1  ---> 
	L1: [...]      L1: [...]

EXEMPLOS 

NUMERO 1 

int main()
{
	int i, j;
	j = 1;
	for(i = 0: i <= 9 : i = i + 1)
	{
		j = j + 1;  // vira inc 
		j = j * (1*1*1*8*0 + 1); // operacao vai ser resolvida para j * 1 e eliminada
		                         // se tornando j = j
		j = 0 + 0 - 0 + j *1;    // tambem eh simplificado para j = j
		j = j * (j/j);           // tambem eh simplificado para j = j
	};
	return j;
}

Nesse exemplo o código assembly sem otimização tem 94 linhas,
o código com otimização tem 65 linhas.


NUMERO 2

int main ()
{
	int i, n;
	bool b;
	b = 1 < 2;
	for(i = 0: i < 10 || i == 2 : i = i + 1)
	{
		b = true || false;
	};
	return b;
}

Nesse exemplo o código sem otimização tem 83 linhas,
o código otimizado tem 80 linhas.

NUMERO 3

int main(){
	int x;
	x = 33;
	int i;
	for(i = 0: i <= 99999: i = i + 1)
	{
		x = x + 1;
	};
	return x;
}

Nesse exemplo, a versão sem otimização do código conta com duas operações addl
que são executadas diversas vezes, devido às expressões que incrementam 
o valor de x e o valor de i em 1 dentro do loop.

Na versão otimizada, esses comandos são substituidos por incl para 
melhor desempenho devido à maior velocidade de execução 
do comando incl comparado com addl.

