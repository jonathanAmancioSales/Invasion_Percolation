//============================================================================================
// Name        : P_Inv_2018_Priority_Heap.cpp
// Author      : Jonathan Amancio [24.09.2018]
// Description : Percolacao Invasiva Sem Aprisionamento com algoritmo Priority Heap;
//				 Percolacao de sitios em rede quadrada com primeiros vizinhos de Von Neuman.
//		 		 (Com e Sem condicoes de contorno periodico em X e Y);
//============================================================================================

#include <iostream>
#include <vector>
#include <cmath>
#include <random>	//C++11
#include <fstream>
#include <stdio.h>
#include <math.h>

using namespace std;

#define N 128
//Fronteira [0,1]
#define def 2	//Defensor  [def,def+1]
#define inv 4

bool percola;
int Massa_inv, Massa_front;
int const W=pow(10,1+int(log10(N)));
int const W2=pow(W,2);

float M[N][N][N] = {0};
vector<unsigned int> Heap;	//unsigned int->[0:4.294.967.295];

void Exibir() {
	for(int k=1; k<N; k++)
	{	for(int i=0; i<N; i++)
		{	for(int j=0; j<N; j++)
			{ cout << M[i][j][k] <<" "; }
			cout << endl;
		}	cout << "\n\n";
	}
}
void XYZ(int i, int j, int k) {
	FILE *r;
	char str[20];
	sprintf(str,"XYZ_%03d.txt",N);
	r = fopen(str,"a");
	fprintf(r,"%d %d %d\n",j,i,k);
	fclose(r);
}
struct pt { int x; int y; int z; };
struct pt V[6];
void Vizinhos(int i, int j, int k) {
	V[0].x=i-1; V[0].y=j;   V[0].z=k;	//bottom
	V[1].x=i;   V[1].y=j-1; V[1].z=k;	//left
	V[2].x=i;   V[2].y=j+1; V[2].z=k;	//rigth
	V[3].x=i+1; V[3].y=j;   V[3].z=k;	//top
	V[4].x=i;   V[4].y=j;   V[4].z=k-1;	//bottom_Z
	V[5].x=i;   V[5].y=j;   V[5].z=k+1;	//top_Z

	//Com periodicidade em X;
	if(V[0].x==-1){V[0].x=N-1;}			//bottom
	if(V[3].x== N){V[3].x=0;}			//top

	//Sem periodicidade em X;
/*	if(V[0].x==-1){V[0].x=0;}			//bottom
	if(V[3].x== N){V[3].x=N-1;}			//top
*/
	//Com periodicidade em Y;
	if(V[1].y==-1){V[1].y=N-1;}			//left
	if(V[2].y== N){V[2].y=0;}			//rigth

	//Sem periodicidade em Y;
/*	if(V[1].y==-1){V[1].y=0;}			//left
	if(V[2].y== N){V[2].y=N-1;}			//rigth
*/
	//Sem periodicidade em Z;
	if(V[4].z==-1){V[4].z=0;}			//bottom_Z
	if(V[5].z== N){V[5].z=N-1;}			//top_Z
}
struct pt IJK(int e){
	int H=Heap[e];
	struct pt ijk;
	ijk.z = H/W2;
	int aux = (H-ijk.z*W2);
	ijk.x = aux/W;
	ijk.y = aux - ijk.x*W;
	return ijk;
}
void Corrige_Subindo(int m) {
	int i=m, aux;
	struct pt ijk;
	int I,J,K, I2,J2,K2;

	bool go=1;
	while(go==1) {
		ijk=IJK(int(0.5*i)); I=ijk.x;  J=ijk.y;  K=ijk.z;
		ijk=IJK(i);			 I2=ijk.x; J2=ijk.y; K2=ijk.z;
		//Enquanto nao for o 1° item & o pai for maior...;
		if((i>=1) & (M[I][J][K]>M[I2][J2][K2]))
		{	//Trocar: Heap[int(i/2)]->Heap[i];
			aux=Heap[int(0.5*i)];
			Heap[int(0.5*i)]=Heap[i];
			Heap[i]=aux; i=int(0.5*i);
		} else{ go=0; }
	}
}
void Corrige_Descendo(int i) {
	int f;		//filhos;
	int j=i;	//pai;
	int aux;
	struct pt ijk;
	int I,J,K, I2,J2,K2;

	int q=Heap.size();
	while(2*j < q) {
		f = 2*j;
		if(f<q-1) {
			ijk=IJK(f);   I=ijk.x;  J=ijk.y;  K=ijk.z;
			ijk=IJK(f+1); I2=ijk.x; J2=ijk.y; K2=ijk.z;
			if(M[I][J][K]>M[I2][J2][K2]) {f++;}
		}
		ijk=IJK(j); I=ijk.x;  J=ijk.y;  K=ijk.z;
		ijk=IJK(f); I2=ijk.x; J2=ijk.y; K2=ijk.z;
		if(M[I][J][K]<=M[I2][J2][K2]) {j=q;} //Sair do loop;
		else {	//Trocar: Heap[j]->Heap[f];
			aux=Heap[j]; Heap[j]=Heap[f];
			Heap[f]=aux; j=f;
		}
	}
}
void Remover() {
		Heap[0]=Heap[Heap.size()-1];
		Heap.pop_back();	//Remove o ultimo elemento do vetor;
		Corrige_Descendo(0);
}
void Inserir(int I) {
	if(Heap.size()<N*N*N){
		Heap.push_back(I);	//Inserir no ultimo elemento do vetor;
		Corrige_Subindo(Heap.size()-1);
	} else{cout<<"\n\tERRO!\n";}

/*	//Verificar...
	for(int g=0; g<Heap.size(); g++)
	{	int I=IJK(g).x; int J=IJK(g).y; int K=IJK(g).z;
		cout <<g<<"  "<<Heap[g]<<"\t"<<I<<","<<J<<","<<K<<"\t"<<M[I][J][K]<<endl;
	}
*/
}
void Invadir() {
	int x,y,z;
	int I=IJK(0).x; int J=IJK(0).y; int K=IJK(0).z;

	M[I][J][K]=inv; //XYZ(I,J,K);
	Massa_inv++;
	Massa_front--;
	Remover();
	if(K==N-1){percola=true;}
	Vizinhos(I,J,K);	//Atualiza V[6] recebendo os vizinhos de M[I][J][K];
	for(int h=0; h<6; h++)
	{	x=V[h].x; y=V[h].y; z=V[h].z;
		if( (M[x][y][z]>=def) & (M[x][y][z]<=def+1) )				//Defensor;
		{ M[x][y][z]-=def; Inserir(z*W2+x*W+y); Massa_front++; }	//Fronteira;
	}
}
void Analisar() {
	int x, y, z;
	bool stop = 0;	//limita a analise [p/ cond.inicial na 1ª linha];

	for(int k=0; k<N; k++)
	{	stop = 1;
		for(int i=0; i<N; i++)
		{	for(int j=0; j<N; j++)
			{	if(M[i][j][k]==inv)
				{	stop = 0; Massa_inv++;
					Vizinhos(i,j,k);	//Atualiza V[6] recebendo os vizinhos de M[I][J][K];
					for(int h=0; h<6; h++)
					{	x=V[h].x; y=V[h].y; z=V[h].z;
						if( (M[x][y][z]>=def) & (M[x][y][z]<=def+1) )				//Defensor;
						{ M[x][y][z]-=def; Inserir(z*W2+x*W+y); Massa_front++; }	//Fronteira;
					}
				}
			}
		}	if(stop==1){k=N;}
	}
}
void Inicializar(int seed) {
	std::mt19937 generator (seed);
	std::uniform_real_distribution<double> dis(0.0, 1.0);

	for(int i=0; i<N; i++)
	{	for(int j=0; j<N; j++)
		{	for(int k=0; k<N; k++)
			{ M[i][j][k] = def + dis(generator); }	//Defensor;
		}
	}

	//Cond. Inicial (M): 1ª Linha;
	for(int i=0; i<N; i++)
	{	for(int j=0; j<N; j++)
		{	M[i][j][0]=inv; Massa_inv++; //XYZ(i,j,0);
			M[i][j][1]-=def; Inserir(1*W2+i*W+j);	//Invasor e Fronteira;
		}
	}//*/

	//Cond. Inicial (M): 1 Celula;
	/*M[int(N/2)][int(N/2)][0]=inv;
	XYZ(int(N/2),int(N/2),0);
	Analisar();//*/
}
int main(int argc, char* argv[]){
	int seed = atoi(argv[1]);

	Massa_inv=0;
	Massa_front=0;

	Inicializar(seed);	//Preencher Matriz com defensores e definir invasores;
	//Analisar();			//Definir a Fronteira -> [colocar na Heap;]
	//Exibir();
	percola=false;
	do{ Invadir(); }while(percola==false);
	
	cout <<Massa_inv<<"\t"<<Massa_front<<"\t"<<seed<<"\n";
	return 0;
}
