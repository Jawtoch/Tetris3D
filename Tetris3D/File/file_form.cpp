#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#define TAILLE_MAX 10

void file_to_array(char* name_file){

	FILE* file = fopen(name_file,"r") ;
	int*** array = NULL;
	array = new int**[TAILLE_MAX] ;
	for(int i=0;i<TAILLE_MAX;i++){
		array[i] = new int*[TAILLE_MAX] ;
		for(int j=0;j<TAILLE_MAX;j++){
			array[i][j] = new int[TAILLE_MAX] ;
			for(int k=0;k<TAILLE_MAX;k++){
				array[i][j][k] = 0 ; 
			}
		}
	}

	int x, y, z ; // coordonnees cubes

	if(file == NULL){
		fprintf(stderr,"fopen() failed in file %s at line # %d", __FILE__,__LINE__) ;
    	exit(EXIT_FAILURE) ;
	}
	else{
		char* chaine = new char[7];
		while (fgets(chaine,7,file) != NULL){
			for(int i=0;i<7;i++){
				switch(chaine[i]){
					case 'x':
						x = (int)(chaine[i+1]-'0');
						break;
					case 'y':
						y = (int)(chaine[i+1]-'0');
						break;
					case 'z':
						z = (int)(chaine[i+1]-'0');
						break;
				}
			}
			array[x][y][z] = 1 ;
			printf("%d\n", array[x][y][z]) ;
			delete chaine ;
		}
		fclose(file) ;
	}
}


int main(){
	file_to_array((char*)"form1.txt") ;
	return 0 ;
}