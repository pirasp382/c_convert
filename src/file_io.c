#include "file_io.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "util.h"


#define BUFFER 256


// fin ist bereits die richtige Datei
int image_read(image_t *img, FILE *fin) {
   
    if(fin == NULL){    // Fehler wenn falscher file path
        return -1;
    }
    char buffer[BUFFER];
    
    fgets(buffer, sizeof(buffer), fin);
    if(buffer[0] != 'P' || buffer[1] != '3'){  // Fehler bei falschem Dateiformat
        return -1;
    }


    fgets(buffer, sizeof(buffer), fin); // hier speichern wir die Zeile mit h und w in buffer
    sscanf(buffer, "%d %d", &img->w, &img->h); // hier lesen wir die laenge und breite ein
    fgets(buffer, sizeof(buffer), fin);
    img->img = malloc(sizeof(pixel_t) * img->w * img->h); // hier wird platz gemacht

    if(!img){
       // printf("Probleme mit dem Speicher\n"); // img konnte nicht angelegt werden
        return -1;
    }

    int c =0;
    for(int i = 0; i < img->h; i++){ // hier gehen wir durch die Zeilen
        unsigned int r,g,b;
        for(int j = 0; j < img->w; j++){

            if(fscanf(fin, "%u %u %u ", &r, &g, &b)==EOF){ // hier lesen wir die einzelnen rgb ein
                return -1; // Fehler beim lesen der einzelnen Werte
            }
            
            img->img[c].r = r;
            img->img[c].g = g;
            img->img[c].b = b;
            c++;
            
        }
       
    }
    return 0;
}

void image_write(const image_t *img, FILE *fout) {
    // DONE
    if(fout ==NULL){
        printf("file not found\n"); // datei konnte nicht gefunden werden
        return ;
    }
    //printf("P3\n", fout); // dateiformat
    fputs("P3\n", fout);
    printf("%d %d\n", img->w, img->h); // laenge und breite
    printf("%d\n", 255);
    for(int i = 1; i < img->h*img->w+1; i++){
        printf("%u %u %u ", img->img[i-1].r, img->img[i-1].g, img->img[i-1].b); // pixel wird gespeichert
        if(i%img->w==0 ) printf("\n"); // neue zeile
    }
    fclose(fout); // schliesse die datei
}

void image_free(image_t *img) {
    if (img->img != NULL) {
        free(img->img);
    }
    img->w = img->h = 0;
    img->img = NULL;
}
