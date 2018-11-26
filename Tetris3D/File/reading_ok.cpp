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
		char pointeur ;
		while( ((pointeur = (char)fgetc(file)) != '\n') && (pointeur != EOF)){
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
					ok = 0 ;
					printf("Il y a une erreur dans le fichier a la position %lu du curseur\n", ftell(file)); // il y a un nombre supérieur à 10
					pointeur = (char)fgetc(file) ;
					break ;
			}
		}

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