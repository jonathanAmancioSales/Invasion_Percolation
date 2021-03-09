//============================================================================================
// Name        : Perc_Invasiva_Priority_Heap.cpp
// Author      : Jonathan Amancio
// Description : Percolacao Invasiva Sem Aprisionamento com algoritmo Priority Heap;
//				 Percolacao de sitios em rede quadrada com primeiros vizinhos de Von Neuman.
//		 		 (com ou sem condicoes de contorno periodico);
//============================================================================================

#include <iostream>
#include <vector>
#include <math.h>
#include <random>	//C++11

using namespace std;

#define N 1024
//Fronteira [0,1]
#define def 2	//Defensor  [def,def+1]
#define inv 4

bool percola;
int Massa_inv, Massa_front;
int const W=pow(10,1+int(log10(N)));

vector< vector<float> > M(N, vector<float>(N));
vector<unsigned int> Heap;

void Inicializar(int seed) {
	std::mt19937 generator (seed);
	std::uniform_real_distribution<double> dis(0.0, 1.0);

	for(int i=0; i<N; i++)
	{	for(int j=0; j<N; j++)
		{ M[i][j] = def + dis(generator); }	//Defensor;
	}

	//Cond. Inicial (M): 1ª Linha;
	for(int j=0; j<N; j++)
	{ M[0][j] = inv; }	//Invasor;
}
struct pt {
	int x;
	int y;
};
struct pt V[4];
void Vizinhos(int i, int j) {
	V[0].x = i-1; V[0].y = j;		//bottom
	V[1].x = i;   V[1].y = j-1;		//left
	V[2].x = i;   V[2].y = j+1;		//rigth
	V[3].x = i+1; V[3].y = j;		//top

	//Sem periodicidade na vertical;
	if(V[0].x==-1){V[0].x=0;}		//bottom
	if(V[3].x== N){V[3].x=N-1;}		//top

	//Com periodicidade na horizontal;
	if(V[1].y==-1){V[1].y=N-1;}		//left
	if(V[2].y== N){V[2].y=0;}		//rigth
}
int I(int i) {
	return int(Heap[i]/W);
}
int J(int i) {
	return (Heap[i]-W*I(i));
}
void Corrige_Subindo(int m) {
	int i=m;
	int aux;
	//Enquanto nao for o 1° item & o pai for maior...;
	while((i>=1) & (M[I(int(0.5*i))][J(int(0.5*i))]>M[I(i)][J(i)])) {
		//Trocar: Heap[int(i/2)]->Heap[i];
		aux=Heap[int(0.5*i)];
		Heap[int(0.5*i)]=Heap[i];
		Heap[i]=aux;
		i=int(0.5*i);
	}
}
void Corrige_Descendo(int i) {
	int f;		//filhos;
	int j=i;	//pai;
	int aux;

	int q=Heap.size();
	while(2*j < q) {
		f = 2*j;
		if(f<q-1) {
			if(M[I(f)][J(f)]>M[I(f+1)][J(f+1)])
			{f++;}
		}
		if(M[I(j)][J(j)]<=M[I(f)][J(f)]) {j=q;} //Sair do loop;
		else {	//Trocar: Heap[j]->Heap[f];
			aux=Heap[j];
			Heap[j]=Heap[f];
			Heap[f]=aux;
			j=f;
		}
	}
}
void Remover() {
		Heap[0]=Heap[Heap.size()-1];
		Heap.pop_back();	//Remove o ultimo elemento do vetor;
		Corrige_Descendo(0);
}
void Inserir(int I) {
	if(Heap.size()<N*N){
		Heap.push_back(I);	//Inserir no ultimo elemento do vetor;
		Corrige_Subindo(Heap.size()-1);
	} else{cout<<"\n\tERRO!\n";}
}
void Invadir() {
	int x, y, I, J;

	I=int(Heap[0]/W);
	J=Heap[0] - W*I;
	M[I][J]=inv;
	Massa_inv++;
	Massa_front--;
	Remover();
	if(I==N-1){percola=true;}
	Vizinhos(I,J);	//Atualiza V[4] recebendo os vizinhos de M[I][J];
	for(int k=0; k<4; k++)
	{	x = V[k].x; y = V[k].y;
		if( (M[x][y]>=def) & (M[x][y]<=def+1) )				//Defensor;
		{ M[x][y]-=def; Inserir(x*W + y); Massa_front++; }	//Fronteira;
	}
}
void Analisar() {
	int x, y;
	bool stop = 0;	//limita a analise [p/ cond.inicial na 1ª linha];

	for(int i=0; i<N; i++)
	{	stop = 1;
		for(int j=0; j<N; j++)
		{	if(M[i][j]==inv)
			{	stop = 0; Massa_inv++;
				Vizinhos(i,j);	//Atualiza V[4] recebendo os vizinhos de M[I][J];
				for(int k=0; k<4; k++)
				{	x = V[k].x; y = V[k].y;
					if( (M[x][y]>=def) & (M[x][y]<=def+1) )				//Defensor;
					{ M[x][y]-=def; Inserir(x*W + y); Massa_front++; }	//Fronteira;
				}
			}
		}	if(stop==1){i=N;}
	}
}
int main(int argc, char* argv[]){
	int seed = atoi(argv[1]);

	Massa_inv=0;
	Massa_front=0;

	Inicializar(seed);	//Preencher Matriz com defensores e definir invasores;
	Analisar();			//Definir a Fronteira -> [colocar na Heap;]

	percola=false;
	do{ Invadir(); }while(percola==false);

	cout <<Massa_inv<<"\t"<<Massa_front<<"\t"<<seed<<"\n";

	return 0;
}
