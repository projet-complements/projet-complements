#include "algo.h"

Algo::Algo(int8_t* database,int8_t* q,int size_score, int32_t* psq_offset, int** arg, int open_pen, int ext_pen){ //constructeur de la classe
	query = q;
	db = database;
	n=sizeof(query);
	size=size_score;
	offset=psq_offset;
	arg_blosum=arg;
	open=open_pen;
	ext=ext_pen;
}

int* Algo::sw(){
	
	int index,m,res1,res2,res3;
	int8_t b;
	int* score = new int[size];
	for(int i=0; i<size; i++){
		score[i]=0;
	}
	// parse the whole database
	for (int ind=0; ind<(size) ;ind++){
		index=ind;
		m=offset[index+1]-offset[index];
		
		// initialize matrix to 0
		int** H = new int*[n+1];
		for(int i=0; i<n+1; i++){
			H[i] = new int[m+1];
			for(int j=0; j<m+1; j++)
				H[i][j] = 0;
		}

		int length_h=1;
		int length_v=1;
		int penalty_gaph=open+(length_h*ext);
		int penalty_gapv=open+(length_v*ext);

		for (int i = 1; i < n+1 ; i++){
			for (int j = 1; j < m+1 ;){
				b = db[offset[index]+j-1];
				if(b==0){
					j++;
				}
				else{
					//we create a Coord that takes the 2 int8_t from the sequences to return the score
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
					delete coord;
				}
				j++;
			}
		}
		delete (H);
	}
	return score;
}
