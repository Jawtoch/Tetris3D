#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#define TAILLE_MAX 10

int file_ok(char* name_file){

	int ok = 1;
	FILE* file = fopen(name_file,"r") ;

	if(file == NULL){
		fprintf(stderr,"fopen() failed in file %s at line # %d", __FILE__,__LINE__) ;
    	exit(EXIT_FAILURE) ;
	}
	else{
		int d = 0 ;
		int ligne = 0;
		char pointeur ;
		do{
			while( (d!=1) && (pointeur = (char)fgetc(file)) != '\n' ){
				switch(pointeur){
					case 'x':
						pointeur = (char)fgetc(file) ;
						break ;
					case 'y':
						pointeur = (char)fgetc(file) ;
						break ;
					case 'z':
						pointeur = (char)fgetc(file) ;
						break ;
					default:
						d = 1 ;
						ok = 0 ;
						printf("Il y a un probleme dans le fichier à la ligne %d\n", ligne); // il y a un nombre supérieur à 10
						break ;
				}
			}
			ligne++ ;
		}while( (d!=1) && (pointeur != EOF) ) ;
	}
	fclose(file) ;
	return ok ;
}

int main(){
	int x = file_ok((char*)"form1.txt") ;
	if(x==1){
		printf("Le fichier est ok\n");
	}
	return 0 ;
}