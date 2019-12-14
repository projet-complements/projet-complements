#include "algo.h"

Algo::Algo(int8_t* database,int8_t* q,int size_score, int32_t* psq_offset, int** arg, int open_pen, int ext_pen){ //constructeur de la classe
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

	// parse the whole database
	for (int ind =0; ind<(size-1) ;ind++){
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
		
		cout <<"m = " << m << " indice = " << index << endl;
		//cout <<"taille de la seq " << sizeof(tmp) << endl;
		// initialize matrix to 0
		//int H[n+1][m+1] = {0};
		vector<vector<int>> H(n+1, vector<int>(m+1,0));
		int length_h=1;
		int length_v=1;
		int penalty_gaph=open+(length_h*ext);
		int penalty_gapv=open+(length_v*ext);

		for (int i = 1; i < n+1 ; i++){
			for (int j = 1; j < m+1 ; j++){
				cout <<"m = " << m << " indice = " << index << "j= " << j << endl;
				b = db[offset[index]+j-1];
				cout << "offset " << offset[index] << endl;
				//cout << " lettre num = " << j-1 << endl;
				// on cree un Coord qui va prendre les 2 int8_t dans les sequences pour en renvoyesssr le score
				Coord* coord = new Coord(query[i-1],b,arg_blosum);
				res1=H[i][j-1]-penalty_gapv;
				res2=H[i-1][j-1]+coord->score();
				res3=H[i-1][j]-penalty_gaph;
				
				if(res1<0 && res2<0 && res3<0){// if it is not a gap, we reinitialize the gap penalties
					H[i][j]=0;
					length_v=1;
					length_h=1;
					penalty_gaph=open+(length_h*ext);
					penalty_gapv=open+(length_v*ext);
				}
				else if (res1>res2 && res1>res3){
					H[i][j]=res1;
					length_v+=1;
					penalty_gapv=(length_v*ext);
					length_h=1;
					penalty_gaph=open+(length_h*ext);
				}
				else if (res3>res2 && res3>res1){
					H[i][j]=res3;
					length_h+=1;
					penalty_gapv=(length_h*ext);
					length_v=1;
					penalty_gapv=open+(length_v*ext);
				}
				else { // if it is not a gap, we reinitialize the gap penalties
					H[i][j]=res2;
					length_v=1;
					length_h=1;
					penalty_gaph=open+(length_h*ext);
					penalty_gapv=open+(length_v*ext);
				}
				
				if (H[i][j]>score[index]){
					score[index]=H[i][j];
				}
				cout << "score index " << score[index] << endl;
			}
		}
	
		cout << "Algo est a calculé " << index <<"avec comme score" << score[index]<< endl;
		//continue;

	}
			
	return;
}
