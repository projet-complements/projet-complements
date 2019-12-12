#include "algo.h"

Algo::Algo(int8_t* database,int8_t* q,int size_score, int32_t* psq_offset, string arg, int open_pen, int ext_pen){ //constructeur de la classe
	query = q;
	db = database;
	
	n=sizeof(query);
	size=size_score;
	int init[size]={0};
	score=init;
	offset=psq_offset;
	arg_blosum=arg;
	open=open_pen;
	ext=ext_pen;
}

void Algo::sw(){
	
	int index,m,res1,res2,res3;
	int8_t b;
	
	// pour l'instant on prend un penalty gap au hasard
	// parse the whole database
	for (int ind =0; ind<(size) ;ind++){
		index=ind;
		m=offset[index+1]-offset[index];
		/*b = 10; //donne une valeur différente de 0
		//on stocke la sequence qu'on regarde dans tmp
		int tmp[m]; 
		for(int tmpi = 0 ; (tmpi)<m ; (tmpi)++){
			tmp[tmpi] = db[offset[index]+tmpi];
			//cout << "lettre" << int(b)<< endl;
			//cout << tmpi << endl;
		}*/
		
		cout <<"m = " << m << endl;
		//cout <<"taille de la seq " << sizeof(tmp) << endl;
		int H[n+1][m+1] = {0};

		int length_h=1;
		int length_v=1;
		int penalty_gaph=open+(length_h*ext);
		int penalty_gapv=open+(length_v*ext);
		//donne la valeur pour le reste de la matrice
		for (int i = 1; i < n+1 ; i++){
			for (int j = 1; j < m+1 ; j++){
				//b = db[offset[index]+j-1];
				// on cree un Coord qui va prendre les 2 int8_t dans les sequences pour en renvoyer le score
				Coord* coord = new Coord(query[i],b,arg_blosum);
				res1=H[i][j-1]-penalty_gapv;
				res2=H[i-1][j-1]+coord->score();
				res3=H[i-1][j]-penalty_gaph;
				if(res1<0 && res2<0 && res3<0){
					H[i][j]=0;
				}
				else if (res1>res2 && res1>res3){
					H[i][j]=res1;
				}
				else if (res3>res2 && res3>res1){
					H[i][j]=res3;
				}
				else {
					H[i][j]=res2;
				}
				/*else {
					int interm = std::max(res1,res2);
					H[i][j]=std::max(interm, res3);
					//on verifie si on a pris un penalty_gap horizontal, si oui on update la longueur du gap horizontal
					if(H[i][j]==res1){
						length_v+=1;
						penalty_gapv=(length_v*ext);
						length_h=1;
						penalty_gaph=open+(length_h*ext);
					}
					//on verifie si on a pris un penalty_gap vertical, si oui on update la longueur du gap vertical
					else if(H[i][j]==res2){
						length_h+=1;
						penalty_gapv=(length_h*ext);
						length_v=1;
						penalty_gapv=open+(length_v*ext);
					}
					//si on a pas pris un gap, on reinitialise à 0
					else {
						length_v=1;
						length_h=1;
						penalty_gaph=open+(length_h*ext);
						penalty_gapv=open+(length_v*ext);
					}*/
					if(H[i][j]>score[index]){ //calcul du score final
					score[index]=H[i][j];	
				}
			}
		}
	
		cout << "Algo est a calculé " << index <<"avec comme score" << score[index]<< endl;
		continue;

	}
			
		
		//score de tmp=max dans toute la matrice (pas sure que la condition marche)
		//on doit faire un vecteur avec tous les scores, et on doit retrouver la matrice correspondante avec offset.
		//pour lier avec offset, l'indice dans score sera le mm indice que dans offset
		//score a donc la taille nbseq+1
	return;
}
	
	
		

