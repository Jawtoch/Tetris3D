#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

#define TAILLE_MAX_PIECE 6

void freeArray(int*** cTab, int xSize, int ySize, int zSize) {
    for(int i = 0; i < xSize; i++) {
        for(int j = 0; j < ySize; j++) {
            delete[] cTab[i][j];
        }
        delete[] cTab[i];
    }
    delete[] cTab;
}

int*** file_to_array(char* name_file){

	FILE* file = fopen(name_file,"r") ;
	int*** array = NULL;
	int*** verif = NULL ;

	if(file == NULL){
		fprintf(stderr,"fopen() failed in file %s at line # %d", __FILE__,__LINE__) ;
    	exit(EXIT_FAILURE) ;
	}
	else{
		array = new int**[TAILLE_MAX_PIECE] ;
		verif = new int**[TAILLE_MAX_PIECE] ;
		for(int i=0;i<TAILLE_MAX_PIECE;i++){
			array[i] = new int*[TAILLE_MAX_PIECE] ;
			verif[i] = new int*[TAILLE_MAX_PIECE] ;
			for(int j=0;j<TAILLE_MAX_PIECE;j++){
				array[i][j] = new int[TAILLE_MAX_PIECE] ;
				verif[i][j] = new int[TAILLE_MAX_PIECE] ;
				for(int k=0;k<TAILLE_MAX_PIECE;k++){
					array[i][j][k] = 0 ;
					verif[i][j][k] = 0 ; 
				}
			}
		}
		int temp1 = 0 ;
		int temp2 = 0;
		int temp3 = 0;
		int ligne = 1 ; // numero de ligne
		char* chaine = new char[7];
		size_t linesize = 7;
		ssize_t nread ;
		char a = 0, b = 0, c = 0;
		int x = 0, y = 0, z = 0;
		while (1) {
			nread = getline(&chaine, &linesize, file);
			if(nread == -1){
				//printf("Le tableau a été correctement chargé\n"); 
				break;
			}
			//printf("%d %d\n",strlen(chaine), nread);
			nread = sscanf(chaine, "%c%d%c%d%c%d", &a, &x, &b, &y, &c, &z);
			//printf("%d %c %d %c %d %c %d\n", nread, a, x, b, y, c, z);
			if (nread!=6 && nread!=0) {
				fprintf(stderr,"Le format de la ligne %d du fichier est incorrecte\n", ligne);
				freeArray(array, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE) ;
				return NULL ;;
			}
			if(a=='x'&& b=='y' && c=='z'){
				if(ligne>1){
					if(fabs(x-temp1)>1){
						fprintf(stderr,"La structure de la forme est impossible, voir ligne fichier %d et ligne code %d\n", ligne, __LINE__);
						freeArray(array, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE) ;
						return NULL ;
					}
					if(fabs(y-temp2)>1){
						fprintf(stderr,"La structure de la forme est impossible, voir ligne fichier %d et ligne code %d\n", ligne, __LINE__);
						freeArray(array, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE) ;
						return NULL ;
					}
					if(fabs(z-temp3)>1){
						fprintf(stderr,"La structure de la forme est impossible, voir ligne fichier %d et ligne code %d\n", ligne, __LINE__);
						freeArray(array, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE) ;
						return NULL ;
					}
				}
				temp1 = x ;
				temp2 = y ;
				temp3 = z ;
				array[x][y][z] = 1 ;
			}
			else if(a=='x' && b=='z'&& c=='y'){
				if(ligne>1){
					if(fabs(x-temp1)>1){
						fprintf(stderr,"La structure de la forme est impossible, voir ligne fichier %d et ligne code %d\n", ligne, __LINE__);
						freeArray(array, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE) ;
						return NULL ;
					}
					if(fabs(z-temp3)>1){
						fprintf(stderr,"La structure de la forme est impossible, voir ligne fichier %d et ligne code %d\n", ligne, __LINE__);
						freeArray(array, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE) ;
						return NULL ;
					}
					if(fabs(y-temp2)>1){
						fprintf(stderr,"La structure de la forme est impossible, voir ligne fichier %d et ligne code %d\n", ligne, __LINE__);
						freeArray(array, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE) ;
						return NULL ;
					}
				}
				temp1 = x ;
				temp2 = z ;
				temp3 = y ;
				array[x][z][y] = 1 ;
			}
			else if(a=='y'&& b=='x' && c=='z'){
				if(ligne>1){
					if(fabs(y-temp2)>1){
						fprintf(stderr,"La structure de la forme est impossible, voir ligne fichier %d et ligne code %d\n", ligne, __LINE__);
						freeArray(array, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE) ;
						return NULL ;
					}
					if(fabs(x-temp1)>1){
						fprintf(stderr,"La structure de la forme est impossible, voir ligne fichier %d et ligne code %d\n", ligne, __LINE__);
						freeArray(array, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE) ;
						return NULL ; 
					}
					if(fabs(z-temp3)>1){
						fprintf(stderr,"La structure de la forme est impossible, voir ligne fichier %d et ligne code %d\n", ligne, __LINE__);
						freeArray(array, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE) ;
						return NULL ; 
					}
				}
				temp1 = y ;
				temp2 = x ;
				temp3 = z ;
				array[y][x][z] = 1 ;
			}
			else if(a=='y'&& b=='z' && c=='x'){
				if(ligne>1){
					if(fabs(y-temp2)>1){
						fprintf(stderr,"La structure de la forme est impossible, voir ligne fichier %d et ligne code %d\n", ligne, __LINE__);
						freeArray(array, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE) ;
						return NULL ;
					}
					if(fabs(z-temp3)>1){
						fprintf(stderr,"La structure de la forme est impossible, voir ligne fichier %d et ligne code %d\n", ligne, __LINE__);
						freeArray(array, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE) ;
						return NULL ;
					}
					if(fabs(x-temp1)>1){
						fprintf(stderr,"La structure de la forme est impossible, voir ligne fichier %d et ligne code %d\n", ligne, __LINE__);
						freeArray(array, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE) ;
						return NULL ;
					}
				}
				temp1 = y ;
				temp2 = z ;
				temp3 = x ;
				array[y][z][x] = 1 ;
			}
			else if(a=='z'&& b=='y' && c=='x'){
				if(ligne>1){
					if(fabs(z-temp3)>1){
						fprintf(stderr,"La structure de la forme est impossible, voir ligne fichier %d et ligne code %d\n", ligne, __LINE__);
						freeArray(array, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE) ;
						return NULL ;
					}
					if(fabs(y-temp2)>1){
						fprintf(stderr,"La structure de la forme est impossible, voir ligne fichier %d et ligne code %d\n", ligne, __LINE__);
						freeArray(array, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE) ;
						return NULL ;
					}
					if(fabs(x-temp1)>1){
						fprintf(stderr,"La structure de la forme est impossible, voir ligne fichier %d et ligne code %d\n", ligne, __LINE__);
						freeArray(array, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE) ;
						return NULL ;
					}
				}
				temp1 = z ;
				temp2 = y ;
				temp3 = x ;
				array[z][y][x] = 1 ;
			}
			else if(a=='z'&& b=='x' && c=='y'){
				if(ligne!=1){
					if(fabs(z-temp3)>1){
						fprintf(stderr,"La structure de la forme est impossible, voir ligne fichier %d et ligne code %d\n", ligne, __LINE__);
						freeArray(array, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE) ;
						return NULL ;
					}
					if(fabs(x-temp1)>1){
						fprintf(stderr,"La structure de la forme est impossible, voir ligne fichier %d et ligne code %d\n", ligne, __LINE__);
						freeArray(array, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE) ;
						return NULL ;
					}
					if(fabs(y-temp2)>1){
						fprintf(stderr,"La structure de la forme est impossible, voir ligne fichier %d et ligne code %d\n", ligne, __LINE__);
						freeArray(array, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE) ;
						return NULL ;
					}
				}
				temp1 = z ;
				temp2 = x ;
				temp3 = y ;
				array[z][x][y] = 1 ;
				if((z-1)>=0 && (x-1)>= 0 && (y-1)>= 0){
					verif[z-1][x-1][y-1] = 1 ;
				}
				if((z-1)>=0 && (x-1)>=0){
					verif[z-1][x-1][y] = 1 ;
				}
				if((z-1)>=0 && (y-1)>=0){
					verif[z-1][x][y-1] = 1 ;
				}
				if((x-1)>=0 && (y-1)>=0){
					verif[z][x-1][y-1] = 1 ;
				}
				if((x-1)>=0){
					verif[z][x-1][y] = 1 ;
				}
				if((y-1)>=0){
					verif[z][x][y-1] = 1 ;
				}
				if((z-1)>=0){
					verif[z-1][x][y] = 1 ;
				}
				// 7 cas sur 26 pour l'instant

				if((z+1)<=TAILLE_MAX_PIECE && (x+1)<=TAILLE_MAX_PIECE && (y+1)<=TAILLE_MAX_PIECE){
					verif[z+1][x+1][y+1] = 1 ;
				}
				if((z+1)<=TAILLE_MAX_PIECE && (x+1)<=TAILLE_MAX_PIECE){
					verif[z+1][x+1][y] = 1 ;
				}
				if((z+1)<=TAILLE_MAX_PIECE && (y+1)<=TAILLE_MAX_PIECE){
					verif[z+1][x][y+1] = 1 ;
				}
				if((x+1)<=TAILLE_MAX_PIECE && (y+1)<=TAILLE_MAX_PIECE){
					verif[z][x+1][y+1] = 1 ;
				}
				if((x+1)<=TAILLE_MAX_PIECE){
					verif[z][x+1][y] = 1 ;
				}
				if((y+1)<=TAILLE_MAX_PIECE){
					verif[z][x][y+1] = 1 ;
				}
				if((z+1)<=TAILLE_MAX_PIECE){
					verif[z+1][x][y] = 1 ;
				}
				// 14 cas sur 26 pour l'instant

				if((z-1)>=0 && (x-1)>=0 && (y+1)<=TAILLE_MAX_PIECE){
					verif[z-1][x-1][y+1] = 1 ;
				}
				if((z-1)>=0 && (x+1)<=TAILLE_MAX_PIECE && (y-1)>=0){
					verif[z-1][x+1][y-1] = 1 ;
				}
				if((z+1)<=TAILLE_MAX_PIECE && (x-1)>=0 && (y-1)>=0){
					verif[z+1][x-1][y-1] = 1 ;
				}
				// 17 cas sur 26 

				if((z-1)>=0 && (x+1)<=TAILLE_MAX_PIECE && (y+1)<=TAILLE_MAX_PIECE){
					verif[z-1][x+1][y+1] = 1 ;
				}
				if((z+1)<=TAILLE_MAX_PIECE && (x+1)<=TAILLE_MAX_PIECE && (y-1)>=0){
					verif[z+1][x+1][y-1] = 1 ;
				}
				if((z+1)<=TAILLE_MAX_PIECE && (x-1)>=0 && (y+1)<=TAILLE_MAX_PIECE){
					verif[z+1][x-1][y+1] = 1 ;
				}
				// 20 cas sur 26 pour l'instant

				if((z-1)>=0 && (x+1)<=TAILLE_MAX_PIECE){
					verif[z-1][x+1][y] = 1 ;
				}
				if((z+1)<=TAILLE_MAX_PIECE && (x-1)>=0){
					verif[z+1][x-1][y] = 1 ;
				}
				if((z-1)>=0 && (y+1)<=TAILLE_MAX_PIECE){
					verif[z-1][x][y+1] = 1 ;
				}
				if((z+1)<=TAILLE_MAX_PIECE && (y-1)>=0){
					verif[z+1][x][y-1] = 1 ;
				}
				if((x-1)>=0 && (y+1)<=TAILLE_MAX_PIECE){
					verif[z][x-1][y+1] = 1 ;
				}
				if((x+1)<=TAILLE_MAX_PIECE && (y-1)>=0){
					verif[z][x+1][y-1] = 1 ;
				}
				// 26 cas sur 26 :)

			}
			else{
				fprintf(stderr,"Le format de la ligne %d est incorrecte\n", ligne);
				return NULL ;
			}
			ligne++ ;
		}
		delete[] chaine ;
		fclose(file) ;
		freeArray(verif, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE, TAILLE_MAX_PIECE) ;
	}
	return array ;
}

/*int main(){
	//file_to_array((char*)"form3.txt") ;
	return 0 ;
}*/