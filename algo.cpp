#include "algo.h"

Algo::Algo(int8_t* database,vector<int8_t> q,int size_score, int32_t* psq_offset, int** arg, int open_pen, int ext_pen){ //constructeur de la classe
	query = q;
	db = database;
	n=query.size();
	size=size_score;
	int init[size]={0};
	score=init;
	offset=psq_offset;
	arg_blosum=arg;
	open=open_pen;
	ext=ext_pen;
}

void Algo::sw(){	
	int Hdiag=0;
	int Hv, E,currentH,m,res1,res2,res3;
	int8_t b;
	// defines the penalties
	int Q=open+ext;
	int R=ext;

	// parse the whole database
	for (int ind =0; ind<(size-1) ;ind++){
		
		// m is the size of the protein we are analyzing in the database
		m=offset[ind+1]-offset[ind]-1;
		
		// we save one column of H and E
		int* H = nullptr;
		int* F = nullptr;
		H=new int[m+1];
		F=new int[m+1];
		
		
		/*tmp is the sequence we are analyzing
		int* tmp;
		tmp=new int[m]; 
		for(int tmpi = 0 ; (tmpi)<m ; (tmpi)++){
			tmp[tmpi] = db[offset[ind]+tmpi];
		}*/

		// search for the highest score
		for(int i = 1; i < n+1 ; i++){
			// for every new column, we set E to 0 and H vertical to 0
			E=0;
			Hv=0;
			for(int j = 1; j < m+1 ; j++){
				int8_t b = db[offset[ind]+j-1];
				//int8_t q = query[i-1];
				Hdiag=H[j-1]; // the value of the diagonal is the value of the array of the previous column, one line higher
				if((E+R)>(Hv+Q)){
					E=E+R;
				} 
				else{
				 	E=Hv+Q; 
				}
				if ((F[j-1]+R)>(H[j]+Q)){
					F[j]= F[j-1]+R;
				}
				else{
					F[j]=H[j]+Q;
				}
				// we create a coord type, which will give us the score between two proteins
				Coord* coord = new Coord(query[i-1],b,arg_blosum);
				res2=Hdiag+coord->score();
				res1=E;
				res3=F[j];
				
				if(res1<0 && res2<0 && res3<0){// if it is not a gap, we reinitialize the gap penalties
					currentH=0;
				}
				else if (res1>res2 && res1>res3){
					currentH=res1;
				}
				else if (res3>res2 && res3>res1){
					currentH=res3;
				}
				else { // if it is not a gap, we reinitialize the gap penalties
					currentH=res2;
				}
				// we update everything for the next iteration
				Hv=currentH;
				H[j]=currentH;
				if (currentH>score[ind]){
					score[ind]=currentH;
				}
				delete(coord);
			}
		}
		//cout << "Algo est a calculé " << ind <<"avec comme score " << score[ind]<< endl;
		delete(H);
		delete(F);
		//delete(tmp);
	
}
	
	/*int index,m,res1,res2,res3;
	int8_t b;

	// parse the whole database
	for (int ind =0; ind<(size) ;ind++){
		index=ind;
		
		// donne la taille de la sequence qu'on regarde dans la db
		m=offset[index+1]-offset[index]-1;

		//on stocke la sequence qu'on regarde dans tmp
		int* tmp;
		tmp=new int[m]; 
		for(int tmpi = 0 ; (tmpi)<m ; (tmpi)++){
			tmp[tmpi] = db[offset[index]+tmpi];
		}

		
		// initialize matrix to 0
		int** H = new int*[n+1];
		for(int i = 0; i < n+1; ++i){
			H[i] = new int[m+1];
		}
		//initialise les données pour le penalty
		int length_h=1;
		int length_v=1;
		int penalty_gaph=open+(length_h*ext);
		int penalty_gapv=open+(length_v*ext);
		for (int i = 1; i < n+1 ; i++){
			for (int j = 1; j < m+1 ; j++){
				//cout << "dans double for"<<endl;
				//int8_t q = query[i-1]; // regarde la lettre dans la query
				//cout << "queryrok"<<endl;
				//int8_t t = tmp[j-1]; // regarde la lettre dans la sequence
				//b = db[offset[index]+j-1];
				// on cree un Coord qui va prendre les 2 int8_t dans les sequences pour en renvoyesssr le score
				Coord* coord = new Coord(query[i-1],tmp[j-1],arg_blosum);
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
			}
		}
		delete(H);
		
		cout << "Algo est a calculé " << index <<"avec comme score " << score[index]<< endl;
	}*/
	return;

}
