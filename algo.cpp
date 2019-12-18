#include "algo.h"

Algo::Algo(int8_t* database,vector<int8_t> q,int size_score, int32_t* psq_offset, int** arg, int open_pen, int ext_pen){ //constructeur de la classe
	query = q;
	db = database;
	n=query.size();
	size=size_score;
	offset=psq_offset;
	arg_blosum=arg;
	open=open_pen;
	ext=ext_pen;
}

int* Algo::sw(){	
	//initialize the values that we need
	int* score;
	score=new int[size]();
	int Hdiag=0;
	int E,currentH,m,res1,res2,res3;
	int8_t b;
	
	// defines the penalties
	int Q=open+ext;
	int R=ext;

	// parse the whole database
	for (int ind =0; ind<(size) ;ind++){
		// m is the size of the protein we are analyzing in the database
		m=offset[ind+1]-offset[ind]-1;
		
		// we save one column of H and F, which are both initialize to 0
		int* H = nullptr;
		int* F = nullptr;
		H=new int[n+1]();
		F=new int[n+1]();
		
		// search for the highest score
		for(int i = 0; i < m ; i++){
			// for every new column, we set E, H diagonal and H vertical to 0
			E=0;
			Hdiag=0;
			for(int j = 1; j < n+1 ; j++){
				b = db[offset[ind]+i];
				// we create a coord type, which will give us the score between two proteins
				Coord* coord = new Coord(query[j-1],b,arg_blosum);
				res2=Hdiag+coord->score();
				
				
				// updates the value of E by choosing the maximum between E-R and H[j-1]-Q (H[j-1] being the value of the previous iteration)
				if((E-R)>(H[j-1]-Q)){
					E=E-R;
				} 
				else{
				 	E=H[j-1]-Q; 
				}
				res1=E;
				
				if ((F[j]-R)>(H[j]-Q)){
					F[j]=F[j]-R;
				}
				else{
					F[j]=H[j]-Q;
				}
				res3=F[j];
				
				// search for the max between res1,2 and 3
				currentH=0;
				if (res1>currentH){
					currentH=res1;
				}
				if (res3>currentH){
					currentH=res3;
				}
				if (res2>currentH){
					currentH=res2;
				}

				if (currentH>score[ind]){
					score[ind]=currentH;
				}
				// we update everything for the next iteration
				// the future diagonal H is the current H[j] we are looking
				Hdiag=H[j];
				H[j]=currentH;

				
				delete(coord);
			}
		}
		//cout << "Algo est a calculé " << ind <<"avec comme score " << score[ind]<< endl;
		delete(H);
		delete(F);

	}		
	return score;
}
