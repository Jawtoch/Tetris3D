#include "file_form.hpp"

void freeArrayInteger(int*** cTab, int xSize, int ySize, int zSize) {
    for(int i = 0; i < xSize; i++) {
        for(int j = 0; j < ySize; j++) {
            delete[] cTab[i][j];
        }
        delete[] cTab[i];
    }
    delete[] cTab;
}

int*** file_to_array(char* name_file, int formMaxSize){
    
    FILE* file = fopen(name_file,"r") ;
    int*** array = NULL;
    int*** verif = NULL ;
    
    if(file == NULL){
        fprintf(stderr,"fopen() failed in file %s at line # %d", __FILE__,__LINE__) ;
        exit(EXIT_FAILURE) ;
    }
    else{
        array = new int**[formMaxSize] ;
        verif = new int**[formMaxSize] ;
        for(int i=0;i<formMaxSize;i++){
            array[i] = new int*[formMaxSize] ;
            verif[i] = new int*[formMaxSize] ;
            for(int j=0;j<formMaxSize;j++){
                array[i][j] = new int[formMaxSize] ;
                verif[i][j] = new int[formMaxSize] ;
                for(int k=0;k<formMaxSize;k++){
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
                freeArrayInteger(array, formMaxSize, formMaxSize, formMaxSize) ;
                freeArrayInteger(verif, formMaxSize, formMaxSize, formMaxSize) ;
                return NULL ;
            }
            
            if(a=='x'&& b=='y' && c=='z'){
                if(ligne>1){
                    if(!verif[x][y][z]){
                        fprintf(stderr,"La structure de la forme est impossible, voir ligne fichier %d et ligne code %d\n", ligne, __LINE__);
                        freeArrayInteger(array, formMaxSize, formMaxSize, formMaxSize) ;
                        freeArrayInteger(verif, formMaxSize, formMaxSize, formMaxSize) ;
                        return NULL ;
                    }
                }
                
                if(x<formMaxSize && y<formMaxSize && z<formMaxSize){
                    array[x][y][z] = 1 ;
                    if((x-1)>=0 && (y-1)>=0 && (z-1)>=0){
                        verif[x-1][y-1][z-1] = 1 ;
                    }
                    if((x-1)>=0 && (y-1)>=0){
                        verif[x-1][y-1][z] = 1 ;
                    }
                    if((x-1)>=0 && (z-1)>=0){
                        verif[x-1][y][z-1] = 1 ;
                    }
                    if((y-1)>=0 && (z-1)>=0){
                        verif[x][y-1][z-1] = 1 ;
                    }
                    if((y-1)>=0){
                        verif[x][y-1][z] = 1 ;
                    }
                    if((z-1)>=0){
                        verif[x][y][z-1] = 1 ;
                    }
                    if((x-1)>=0){
                        verif[x-1][y][z] = 1 ;
                    }
                    // 7 cas sur 26 pour l'instant
                    
                    if((x+1)<formMaxSize && (y+1)<formMaxSize && (z+1)<formMaxSize){
                        verif[x+1][y+1][z+1] = 1 ;
                    }
                    if((x+1)<formMaxSize && (y+1)<formMaxSize){
                        verif[x+1][y+1][z] = 1 ;
                    }
                    if((x+1)<formMaxSize && (z+1)<formMaxSize){
                        verif[x+1][y][z+1] = 1 ;
                    }
                    if((y+1)<formMaxSize && (z+1)<formMaxSize){
                        verif[x][y+1][z+1] = 1 ;
                    }
                    if((y+1)<formMaxSize){
                        verif[x][y+1][z] = 1 ;
                    }
                    if((z+1)<formMaxSize){
                        verif[x][y][z+1] = 1 ;
                    }
                    if((x+1)<formMaxSize){
                        verif[x+1][y][z] = 1 ;
                    }
                    // 14 cas sur 26 pour l'instant
                    
                    if((x-1)>=0 && (y-1)>=0 && (z+1)<formMaxSize){
                        verif[x-1][y-1][z+1] = 1 ;
                    }
                    if((x-1)>=0 && (y+1)<formMaxSize && (z-1)>=0){
                        verif[x-1][y+1][z-1] = 1 ;
                    }
                    if((x+1)<formMaxSize && (y-1)>=0 && (z-1)>=0){
                        verif[x+1][y-1][z-1] = 1 ;
                    }
                    // 17 cas sur 26
                    
                    if((x-1)>=0 && (y+1)<formMaxSize && (z+1)<formMaxSize){
                        verif[x-1][y+1][z+1] = 1 ;
                    }
                    if((x+1)<formMaxSize && (y+1)<formMaxSize && (z-1)>=0){
                        verif[x+1][y+1][z-1] = 1 ;
                    }
                    if((x+1)<formMaxSize && (y-1)>=0 && (z+1)<formMaxSize){
                        verif[x+1][y-1][z+1] = 1 ;
                    }
                    // 20 cas sur 26 pour l'instant
                    
                    if((x-1)>=0 && (y+1)<formMaxSize){
                        verif[x-1][y+1][z] = 1 ;
                    }
                    if((x+1)<formMaxSize && (z-1)>=0){
                        verif[x+1][y][z-1] = 1 ;
                    }
                    if((x-1)>=0 && (z+1)<formMaxSize){
                        verif[x-1][y][z+1] = 1 ;
                    }
                    if((x+1)<formMaxSize && (z-1)>=0){
                        verif[x+1][y][z-1] = 1 ;
                    }
                    if((y-1)>=0 && (z+1)<formMaxSize){
                        verif[x][y-1][z+1] = 1 ;
                    }
                    if((y+1)<formMaxSize && (z-1)>=0){
                        verif[x][y+1][z-1] = 1 ;
                    }
                    // 26 cas sur 26 :)
                }
            }
            else if(a=='x' && b=='z'&& c=='y'){
                if(ligne>1){
                    if(!verif[x][z][y]){
                        fprintf(stderr,"La structure de la forme est impossible, voir ligne fichier %d et ligne code %d\n", ligne, __LINE__);
                        freeArrayInteger(array, formMaxSize, formMaxSize, formMaxSize) ;
                        freeArrayInteger(verif, formMaxSize, formMaxSize, formMaxSize) ;
                        return NULL ;
                    }
                }
                
                if(x<formMaxSize && z<formMaxSize && y<formMaxSize){
                    array[x][z][y] = 1 ;
                    if((x-1)>=0 && (z-1)>= 0 && (y-1)>= 0){
                        verif[x-1][z-1][y-1] = 1 ;
                    }
                    if((x-1)>=0 && (z-1)>=0){
                        verif[x-1][z-1][y] = 1 ;
                    }
                    if((x-1)>=0 && (y-1)>=0){
                        verif[x-1][z][y-1] = 1 ;
                    }
                    if((z-1)>=0 && (y-1)>=0){
                        verif[x][z-1][y-1] = 1 ;
                    }
                    if((z-1)>=0){
                        verif[x][z-1][y] = 1 ;
                    }
                    if((y-1)>=0){
                        verif[x][z][y-1] = 1 ;
                    }
                    if((x-1)>=0){
                        verif[x-1][z][y] = 1 ;
                    }
                    // 7 cas sur 26 pour l'instant
                    
                    if((x+1)<formMaxSize && (z+1)<formMaxSize && (y+1)<formMaxSize){
                        verif[x+1][z+1][y+1] = 1 ;
                    }
                    if((x+1)<formMaxSize && (z+1)<formMaxSize){
                        verif[x+1][z+1][y] = 1 ;
                    }
                    if((x+1)<formMaxSize && (y+1)<formMaxSize){
                        verif[x+1][z][y+1] = 1 ;
                    }
                    if((z+1)<formMaxSize && (y+1)<formMaxSize){
                        verif[x][z+1][y+1] = 1 ;
                    }
                    if((z+1)<formMaxSize){
                        verif[x][z+1][y] = 1 ;
                    }
                    if((y+1)<formMaxSize){
                        verif[x][z][y+1] = 1 ;
                    }
                    if((x+1)<formMaxSize){
                        verif[x+1][z][y] = 1 ;
                    }
                    // 14 cas sur 26 pour l'instant
                    
                    if((x-1)>=0 && (z-1)>=0 && (y+1)<formMaxSize){
                        verif[x-1][z-1][y+1] = 1 ;
                    }
                    if((x-1)>=0 && (z+1)<formMaxSize && (y-1)>=0){
                        verif[x-1][z+1][y-1] = 1 ;
                    }
                    if((x+1)<formMaxSize && (z-1)>=0 && (y-1)>=0){
                        verif[x+1][z-1][y-1] = 1 ;
                    }
                    // 17 cas sur 26
                    
                    if((x-1)>=0 && (z+1)<formMaxSize && (y+1)<formMaxSize){
                        verif[x-1][z+1][y+1] = 1 ;
                    }
                    if((x+1)<formMaxSize && (z+1)<formMaxSize && (y-1)>=0){
                        verif[x+1][z+1][y-1] = 1 ;
                    }
                    if((x+1)<formMaxSize && (z-1)>=0 && (y+1)<formMaxSize){
                        verif[x+1][z-1][y+1] = 1 ;
                    }
                    // 20 cas sur 26 pour l'instant
                    
                    if((x-1)>=0 && (z+1)<formMaxSize){
                        verif[x-1][z+1][y] = 1 ;
                    }
                    if((x+1)<formMaxSize && (y-1)>=0){
                        verif[x+1][z][y-1] = 1 ;
                    }
                    if((x-1)>=0 && (y+1)<formMaxSize){
                        verif[x-1][z][y+1] = 1 ;
                    }
                    if((x+1)<formMaxSize && (y-1)>=0){
                        verif[x+1][z][y-1] = 1 ;
                    }
                    if((z-1)>=0 && (y+1)<formMaxSize){
                        verif[x][z-1][y+1] = 1 ;
                    }
                    if((z+1)<formMaxSize && (y-1)>=0){
                        verif[x][z+1][y-1] = 1 ;
                    }
                    // 26 cas sur 26 :)
                }
                
            }
            else if(a=='y'&& b=='x' && c=='z'){
                if(ligne>1){
                    if(!verif[y][x][z]){
                        fprintf(stderr,"La structure de la forme est impossible, voir ligne fichier %d et ligne code %d\n", ligne, __LINE__);
                        freeArrayInteger(array, formMaxSize, formMaxSize, formMaxSize) ;
                        freeArrayInteger(verif, formMaxSize, formMaxSize, formMaxSize) ;
                        return NULL ;
                    }
                }
                
                if(y<formMaxSize && x<formMaxSize && z<formMaxSize){
                    array[y][x][z] = 1 ;
                    if((y-1)>=0 && (x-1)>= 0 && (z-1)>= 0){
                        verif[y-1][x-1][z-1] = 1 ;
                    }
                    if((y-1)>=0 && (x-1)>=0){
                        verif[y-1][x-1][z] = 1 ;
                    }
                    if((y-1)>=0 && (z-1)>=0){
                        verif[y-1][x][z-1] = 1 ;
                    }
                    if((x-1)>=0 && (z-1)>=0){
                        verif[y][x-1][z-1] = 1 ;
                    }
                    if((x-1)>=0){
                        verif[y][x-1][z] = 1 ;
                    }
                    if((z-1)>=0){
                        verif[y][x][z-1] = 1 ;
                    }
                    if((y-1)>=0){
                        verif[y-1][x][z] = 1 ;
                    }
                    // 7 cas sur 26 pour l'instant
                    
                    if((y+1)<formMaxSize && (x+1)<formMaxSize && (z+1)<formMaxSize){
                        verif[y+1][x+1][z+1] = 1 ;
                    }
                    if((y+1)<formMaxSize && (x+1)<formMaxSize){
                        verif[y+1][x+1][z] = 1 ;
                    }
                    if((y+1)<formMaxSize && (z+1)<formMaxSize){
                        verif[y+1][x][z+1] = 1 ;
                    }
                    if((x+1)<formMaxSize && (z+1)<formMaxSize){
                        verif[y][x+1][z+1] = 1 ;
                    }
                    if((x+1)<formMaxSize){
                        verif[y][x+1][z] = 1 ;
                    }
                    if((z+1)<formMaxSize){
                        verif[y][x][z+1] = 1 ;
                    }
                    if((y+1)<formMaxSize){
                        verif[y+1][x][z] = 1 ;
                    }
                    // 14 cas sur 26 pour l'instant
                    
                    if((y-1)>=0 && (x-1)>=0 && (z+1)<formMaxSize){
                        verif[y-1][x-1][z+1] = 1 ;
                    }
                    if((y-1)>=0 && (x+1)<formMaxSize && (z-1)>=0){
                        verif[y-1][x+1][z-1] = 1 ;
                    }
                    if((y+1)<formMaxSize && (x-1)>=0 && (z-1)>=0){
                        verif[y+1][x-1][z-1] = 1 ;
                    }
                    // 17 cas sur 26
                    
                    if((y-1)>=0 && (x+1)<formMaxSize && (z+1)<formMaxSize){
                        verif[y-1][x+1][z+1] = 1 ;
                    }
                    if((y+1)<formMaxSize && (x+1)<formMaxSize && (z-1)>=0){
                        verif[y+1][x+1][z-1] = 1 ;
                    }
                    if((y+1)<formMaxSize && (x-1)>=0 && (z+1)<formMaxSize){
                        verif[y+1][x-1][z+1] = 1 ;
                    }
                    // 20 cas sur 26 pour l'instant
                    
                    if((y-1)>=0 && (x+1)<formMaxSize){
                        verif[y-1][x+1][z] = 1 ;
                    }
                    if((y+1)<formMaxSize && (z-1)>=0){
                        verif[y+1][x][z-1] = 1 ;
                    }
                    if((y-1)>=0 && (z+1)<formMaxSize){
                        verif[y-1][x][z+1] = 1 ;
                    }
                    if((y+1)<formMaxSize && (z-1)>=0){
                        verif[y+1][x][z-1] = 1 ;
                    }
                    if((x-1)>=0 && (z+1)<formMaxSize){
                        verif[y][x-1][z+1] = 1 ;
                    }
                    if((x+1)<formMaxSize && (z-1)>=0){
                        verif[y][x+1][z-1] = 1 ;
                    }
                    // 26 cas sur 26 :)
                }
                
            }
            else if(a=='y'&& b=='z' && c=='x'){
                if(ligne>1){
                    if(!verif[y][z][x]){
                        fprintf(stderr,"La structure de la forme est impossible, voir ligne fichier %d et ligne code %d\n", ligne, __LINE__);
                        freeArrayInteger(array, formMaxSize, formMaxSize, formMaxSize) ;
                        freeArrayInteger(verif, formMaxSize, formMaxSize, formMaxSize) ;
                        return NULL ;
                    }
                }
                
                if(y<formMaxSize && z<formMaxSize && x<formMaxSize){
                    array[y][z][x] = 1 ;
                    if((y-1)>=0 && (z-1)>= 0 && (x-1)>= 0){
                        verif[y-1][z-1][x-1] = 1 ;
                    }
                    if((y-1)>=0 && (z-1)>=0){
                        verif[y-1][z-1][x] = 1 ;
                    }
                    if((y-1)>=0 && (x-1)>=0){
                        verif[y-1][z][x-1] = 1 ;
                    }
                    if((z-1)>=0 && (x-1)>=0){
                        verif[y][z-1][x-1] = 1 ;
                    }
                    if((z-1)>=0){
                        verif[y][z-1][x] = 1 ;
                    }
                    if((x-1)>=0){
                        verif[y][z][x-1] = 1 ;
                    }
                    if((y-1)>=0){
                        verif[y-1][z][x] = 1 ;
                    }
                    // 7 cas sur 26 pour l'instant
                    
                    if((y+1)<formMaxSize && (z+1)<formMaxSize && (x+1)<formMaxSize){
                        verif[y+1][z+1][x+1] = 1 ;
                    }
                    if((y+1)<formMaxSize && (z+1)<formMaxSize){
                        verif[y+1][z+1][x] = 1 ;
                    }
                    if((y+1)<formMaxSize && (x+1)<formMaxSize){
                        verif[y+1][z][x+1] = 1 ;
                    }
                    if((z+1)<formMaxSize && (x+1)<formMaxSize){
                        verif[y][z+1][x+1] = 1 ;
                    }
                    if((z+1)<formMaxSize){
                        verif[y][z+1][x] = 1 ;
                    }
                    if((x+1)<formMaxSize){
                        verif[y][z][x+1] = 1 ;
                    }
                    if((y+1)<formMaxSize){
                        verif[y+1][z][x] = 1 ;
                    }
                    // 14 cas sur 26 pour l'instant
                    
                    if((y-1)>=0 && (z-1)>=0 && (x+1)<formMaxSize){
                        verif[y-1][z-1][x+1] = 1 ;
                    }
                    if((y-1)>=0 && (z+1)<formMaxSize && (x-1)>=0){
                        verif[y-1][z+1][x-1] = 1 ;
                    }
                    if((y+1)<formMaxSize && (z-1)>=0 && (x-1)>=0){
                        verif[y+1][z-1][x-1] = 1 ;
                    }
                    // 17 cas sur 26
                    
                    if((y-1)>=0 && (z+1)<formMaxSize && (x+1)<formMaxSize){
                        verif[y-1][z+1][x+1] = 1 ;
                    }
                    if((y+1)<formMaxSize && (z+1)<formMaxSize && (x-1)>=0){
                        verif[y+1][z+1][x-1] = 1 ;
                    }
                    if((y+1)<formMaxSize && (z-1)>=0 && (x+1)<formMaxSize){
                        verif[y+1][z-1][x+1] = 1 ;
                    }
                    // 20 cas sur 26 pour l'instant
                    
                    if((y-1)>=0 && (z+1)<formMaxSize){
                        verif[y-1][z+1][x] = 1 ;
                    }
                    if((y+1)<formMaxSize && (x-1)>=0){
                        verif[y+1][z][x-1] = 1 ;
                    }
                    if((y-1)>=0 && (x+1)<formMaxSize){
                        verif[y-1][z][x+1] = 1 ;
                    }
                    if((y+1)<formMaxSize && (x-1)>=0){
                        verif[y+1][z][x-1] = 1 ;
                    }
                    if((z-1)>=0 && (x+1)<formMaxSize){
                        verif[y][z-1][x+1] = 1 ;
                    }
                    if((z+1)<formMaxSize && (x-1)>=0){
                        verif[y][z+1][x-1] = 1 ;
                    }
                    // 26 cas sur 26 :)
                }
                
            }
            else if(a=='z'&& b=='y' && c=='x'){
                if(ligne>1){
                    if(!verif[z][y][x]){
                        fprintf(stderr,"La structure de la forme est impossible, voir ligne fichier %d et ligne code %d\n", ligne, __LINE__);
                        freeArrayInteger(array, formMaxSize, formMaxSize, formMaxSize) ;
                        freeArrayInteger(verif, formMaxSize, formMaxSize, formMaxSize) ;
                        return NULL ;
                    }
                    
                }
                
                if(z<formMaxSize && y<formMaxSize && x<formMaxSize){
                    array[z][y][x] = 1 ;
                    if((z-1)>=0 && (y-1)>= 0 && (x-1)>= 0){
                        verif[z-1][y-1][x-1] = 1 ;
                    }
                    if((z-1)>=0 && (y-1)>=0){
                        verif[z-1][y-1][x] = 1 ;
                    }
                    if((z-1)>=0 && (x-1)>=0){
                        verif[z-1][y][x-1] = 1 ;
                    }
                    if((y-1)>=0 && (x-1)>=0){
                        verif[z][y-1][x-1] = 1 ;
                    }
                    if((y-1)>=0){
                        verif[z][y-1][x] = 1 ;
                    }
                    if((x-1)>=0){
                        verif[z][y][x-1] = 1 ;
                    }
                    if((z-1)>=0){
                        verif[z-1][y][x] = 1 ;
                    }
                    // 7 cas sur 26 pour l'instant
                    
                    if((z+1)<formMaxSize && (y+1)<formMaxSize && (x+1)<formMaxSize){
                        verif[z+1][y+1][x+1] = 1 ;
                    }
                    if((z+1)<formMaxSize && (y+1)<formMaxSize){
                        verif[z+1][y+1][x] = 1 ;
                    }
                    if((z+1)<formMaxSize && (x+1)<formMaxSize){
                        verif[z+1][y][x+1] = 1 ;
                    }
                    if((y+1)<formMaxSize && (x+1)<formMaxSize){
                        verif[z][y+1][x+1] = 1 ;
                    }
                    if((y+1)<formMaxSize){
                        verif[z][y+1][x] = 1 ;
                    }
                    if((x+1)<formMaxSize){
                        verif[z][y][x+1] = 1 ;
                    }
                    if((z+1)<formMaxSize){
                        verif[z+1][y][x] = 1 ;
                    }
                    // 14 cas sur 26 pour l'instant
                    
                    if((z-1)>=0 && (y-1)>=0 && (x+1)<formMaxSize){
                        verif[z-1][y-1][x+1] = 1 ;
                    }
                    if((z-1)>=0 && (y+1)<formMaxSize && (x-1)>=0){
                        verif[z-1][y+1][x-1] = 1 ;
                    }
                    if((z+1)<formMaxSize && (y-1)>=0 && (x-1)>=0){
                        verif[z+1][y-1][x-1] = 1 ;
                    }
                    // 17 cas sur 26
                    
                    if((z-1)>=0 && (y+1)<formMaxSize && (x+1)<formMaxSize){
                        verif[z-1][y+1][x+1] = 1 ;
                    }
                    if((z+1)<formMaxSize && (y+1)<formMaxSize && (x-1)>=0){
                        verif[z+1][y+1][x-1] = 1 ;
                    }
                    if((z+1)<formMaxSize && (y-1)>=0 && (x+1)<formMaxSize){
                        verif[z+1][y-1][x+1] = 1 ;
                    }
                    // 20 cas sur 26 pour l'instant
                    
                    if((z-1)>=0 && (y+1)<formMaxSize){
                        verif[z-1][y+1][x] = 1 ;
                    }
                    if((z+1)<formMaxSize && (x-1)>=0){
                        verif[z+1][y][x-1] = 1 ;
                    }
                    if((z-1)>=0 && (x+1)<formMaxSize){
                        verif[z-1][y][x+1] = 1 ;
                    }
                    if((z+1)<formMaxSize && (x-1)>=0){
                        verif[z+1][y][x-1] = 1 ;
                    }
                    if((y-1)>=0 && (x+1)<formMaxSize){
                        verif[z][y-1][x+1] = 1 ;
                    }
                    if((y+1)<formMaxSize && (x-1)>=0){
                        verif[z][y+1][x-1] = 1 ;
                    }
                    // 26 cas sur 26 :)
                }
            }
            else if(a=='z'&& b=='x' && c=='y'){
                if(ligne>1){
                    if(!verif[z][x][y]){
                        fprintf(stderr,"La structure de la forme est impossible, voir ligne fichier %d et ligne code %d\n", ligne, __LINE__);
                        freeArrayInteger(array, formMaxSize, formMaxSize, formMaxSize) ;
                        freeArrayInteger(verif, formMaxSize, formMaxSize, formMaxSize) ;
                        return NULL ;
                    }
                }
                
                if(z<formMaxSize && x<formMaxSize && y<formMaxSize){
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
                    
                    if((z+1)<formMaxSize && (x+1)<formMaxSize && (y+1)<formMaxSize){
                        verif[z+1][x+1][y+1] = 1 ;
                    }
                    if((z+1)<formMaxSize && (x+1)<formMaxSize){
                        verif[z+1][x+1][y] = 1 ;
                    }
                    if((z+1)<formMaxSize && (y+1)<formMaxSize){
                        verif[z+1][x][y+1] = 1 ;
                    }
                    if((x+1)<formMaxSize && (y+1)<formMaxSize){
                        verif[z][x+1][y+1] = 1 ;
                    }
                    if((x+1)<formMaxSize){
                        verif[z][x+1][y] = 1 ;
                    }
                    if((y+1)<formMaxSize){
                        verif[z][x][y+1] = 1 ;
                    }
                    if((z+1)<formMaxSize){
                        verif[z+1][x][y] = 1 ;
                    }
                    // 14 cas sur 26 pour l'instant
                    
                    if((z-1)>=0 && (x-1)>=0 && (y+1)<formMaxSize){
                        verif[z-1][x-1][y+1] = 1 ;
                    }
                    if((z-1)>=0 && (x+1)<formMaxSize && (y-1)>=0){
                        verif[z-1][x+1][y-1] = 1 ;
                    }
                    if((z+1)<formMaxSize && (x-1)>=0 && (y-1)>=0){
                        verif[z+1][x-1][y-1] = 1 ;
                    }
                    // 17 cas sur 26
                    
                    if((z-1)>=0 && (x+1)<formMaxSize && (y+1)<formMaxSize){
                        verif[z-1][x+1][y+1] = 1 ;
                    }
                    if((z+1)<formMaxSize && (x+1)<formMaxSize && (y-1)>=0){
                        verif[z+1][x+1][y-1] = 1 ;
                    }
                    if((z+1)<formMaxSize && (x-1)>=0 && (y+1)<formMaxSize){
                        verif[z+1][x-1][y+1] = 1 ;
                    }
                    // 20 cas sur 26 pour l'instant
                    
                    if((z-1)>=0 && (x+1)<formMaxSize){
                        verif[z-1][x+1][y] = 1 ;
                    }
                    if((z+1)<formMaxSize && (x-1)>=0){
                        verif[z+1][x-1][y] = 1 ;
                    }
                    if((z-1)>=0 && (y+1)<formMaxSize){
                        verif[z-1][x][y+1] = 1 ;
                    }
                    if((z+1)<formMaxSize && (y-1)>=0){
                        verif[z+1][x][y-1] = 1 ;
                    }
                    if((x-1)>=0 && (y+1)<formMaxSize){
                        verif[z][x-1][y+1] = 1 ;
                    }
                    if((x+1)<formMaxSize && (y-1)>=0){
                        verif[z][x+1][y-1] = 1 ;
                    }
                    // 26 cas sur 26 :)
                }
                
            }
            else{
                fprintf(stderr,"Le format de la ligne %d est incorrecte\n", ligne);
                freeArrayInteger(array, formMaxSize, formMaxSize, formMaxSize) ;
                freeArrayInteger(verif, formMaxSize, formMaxSize, formMaxSize) ;
                return NULL ;
            }
            ligne++ ;
        }
        delete[] chaine ;
        fclose(file) ;
        freeArrayInteger(verif, formMaxSize, formMaxSize, formMaxSize) ;
    }
    return array ;
}

Form array_to_form(int*** arr, int formMaxSize) {
    
    Cube*** T = createArray(formMaxSize, formMaxSize, formMaxSize);
    
    for(int i = 0; i < formMaxSize; i++) {
        for(int j = 0; j < formMaxSize; j++) {
            for(int k = 0; k < formMaxSize; k++) {
                if (arr[i][j][k] == 1)
                    T[i][j][k] = Cube(20);
            }
        }
    }
    
    return Form(T, 10, formMaxSize);
}

int*** choose_form(int nbForm, int formMaxSize){
    char chaine[10] = "form0.txt" ;
    chaine[4] = (char)(nbForm +'0') ;
    int*** array = file_to_array(chaine, formMaxSize) ;
    return array ;
}
