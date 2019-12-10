#include "algo.h"

Algo::Algo(int8_t database[],vector<int8_t> q,int size_score, int psq_offset[], string arg){ //constructeur de la classe
	query = q;
	db = database;
	score = new int[size_score];
	n=sizeof(query);
	size=size_score;
	offset=psq_offset;
	arg_blosum=arg;
}

void Algo::sw(){
	
	int index,m,res1,res2,res3;
	int8_t b;
	
	// pour l'instant on prend un penalty gap au hasard
	int penalty_gap = -5;
   // parse the whole database
	for (int ind =0; ind<(size) ;ind++){
		index=ind;
		int increment = 0;
		b = db[offset[ind]+increment];
		
	   // on stocke la sequence qu'on regarde dans tmp
	   /*std::vector<int8_t> tmp; 
	   while(b!=0){	
			int increment = 0;
			b = db[offset[ind]+increment];
			tmp.push_back(b);
			increment++;
		}*/
		if(b!=0){
			m=offset[ind+1]-offset[ind]; // taille de la seconde sequence
			//utiliser offset pour connaitre la taille de tmp!!!!!!!!!!!!!!!!!!!!!!!!!!!
			//du coup si b!=0 on applique l'algo, sinon on continue!!
			// on initialise la matrice de l'algorithme qui a une taille (n+1)x(m+1)
			int H[n+1][m+1];
			
			//initialise premiere colonne/ligne a 0
			for (int ii = 0; ii<n+1; ii++){
				H[ii][0]=0;
			}
			for (int jj = 0; jj<m+1; jj++){
				H[0][jj]=0;
			}
			
			//donne la valeur pour le reste de la matrice
			for (int i = 1; i < n+1 ; i++){
				for (int j = 1; j < m+1 ; j++){
					// on cree un Coord qui va prendre les 2 int8_t dans les sequences pour en renvoyer le score
					Coord* coord = new Coord(query[i],b,arg_blosum);
					res1=H[i][j-1]+penalty_gap;
					res2=H[i-1][j-1]+coord->score();
					res3=H[i-1][j]+penalty_gap;
					if(res1<0 && res2<0 && res3<0){
						H[i][j]=0;
						}
					else {
						int interm = std::max(res1,res2);
						H[i][j]=std::max(interm, res3);
					}
					if(H[i][j]>H[i][j-1]){
						score[index];
					}
				}
			}
		}
		
		//score de tmp=max dans toute la matrice (pas sure que la condition marche)
		//on doit faire un vecteur avec tous les scores, et on doit retrouver la matrice correspondante avec offset.
		//pour lier avec offset, l'indice dans score sera le mm indice que dans offset
		//score a donc la taille nbseq+1
	}
	
	
		return;
}
