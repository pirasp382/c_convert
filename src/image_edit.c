#include "image_edit.h"
#include "file_io.h"

#include <stdlib.h>

#include "util.h"

#define max(x, y) (((x) > (y)) ? (x) : (y)) // max berrechnen

void rotate_counterclockwise(image_t *img) {
    // aehnliches spiel wie rotate_clockwise
    image_t *temp;
    temp = malloc(sizeof(image_t));
    temp->w =img->h;
    temp->h = img->w;
    temp->img = malloc(sizeof(pixel_t)*temp->h*temp->w);
    if(temp->img == NULL){
        printf("error\n"); // prüfen ob fehler beim speicher
        return;
    }
    for(int i = 0; i < img->h; i++){
        for (int j = 0; j < img->w;j++){
            int rotated_i = img->w - j - 1;
            int rotated_j = i;
            temp->img[rotated_i * temp->w + rotated_j] = img->img[i * img->w + j];
        }
    }
    image_free(img);
    img->h = temp->h;
    img->w =temp->w;
    img->img = malloc(sizeof(pixel_t)*img->h*img->w);
    for(int i = 0; i <img->h*img->w; i++){
        img->img[i] = temp->img[i];
    }
    free(temp->img);
    free(temp);
}

void rotate_clockwise(image_t *img) {
    
    image_t *temp;
    temp = malloc(sizeof(image_t)); // erstelle speicher
    temp->w =img->h;
    temp->h = img->w;
    temp->img = malloc(sizeof(pixel_t)*temp->h*temp->w);
    if(temp->img == NULL){   // prüfen ob fehler beim speicher
        return;
    }
    for(int i = 0; i < img->h; i++){  // in der schleife werden pixel gedraht
        for (int j = 0; j < img->w;j++){
            int rotated_j = img->h - i - 1;
            int rotated_i = j;
            temp->img[rotated_i * temp->w + rotated_j] = img->img[i * img->w + j];
        }
    }
    image_free(img);  // img wird geleert
    img->h = temp->h;
    img->w =temp->w;
    img->img = malloc(sizeof(pixel_t)*img->h*img->w);
    for(int i = 0; i <img->h*img->w; i++){
        img->img[i] = temp->img[i]; // pixel aus temp werden nach img kopiert
    }

    free(temp->img); // speicher wird frei gemacht
    free(temp);
    
}

void mirror_horizontal(image_t *img) {
    // DONE
    int r,g,b;   //zwischenspeicher fuer rgb
    for(int i = 0; i < img->h; i++){
        int c = img->w*i;  // fuer unkomplizierter
        for(int j = 0; j < (int)img->w/2; j++){
            r = img->img[c+j].r;
            g = img->img[c+j].g;
            b = img->img[c+j].b;
            img->img[c+j].b = img->img[c+(img->w-j-1)].b;  // tausche die werte fuer spiegelung
            img->img[c+(img->w-j-1)].b = b;
            img->img[c+j].r = img->img[c+(img->w-j-1)].r;
            img->img[c+(img->w-j-1)].r = r;
            img->img[c+j].g = img->img[c+(img->w-j-1)].g;
            img->img[c+(img->w-j-1)].g = g;
        }
    }
}

void mirror_vertical(image_t *img) {
    // DONE
    // gleiches Spiel wie horizontal nur anderes
    int r,g,b;
    for(int i = 0; i <(int)img->h/2;i++){
        for(int j = 0; j<img->w;j++){
            r = img->img[i*img->w+j].r;
            g = img->img[i*img->w+j].g;
            b = img->img[i*img->w+j].b;
            img->img[i*img->w+j].r = img->img[img->w*(img->h-i-1)+j].r;
            img->img[i*img->w+j].g = img->img[img->w*(img->h-i-1)+j].g;
            img->img[i*img->w+j].b = img->img[img->w*(img->h-i-1)+j].b;
            img->img[img->w*(img->h-i-1)+j].r = r;
            img->img[img->w*(img->h-i-1)+j].g = g;
            img->img[img->w*(img->h-i-1)+j].b = b;
        }
    }
}

void resize(image_t *img, int new_width, int new_height) {
   // DONE
    image_t *temp = malloc(sizeof(image_t));  // kopie vom original
    temp->h = new_height;
    temp->w = new_width;
    temp->img = malloc(sizeof(pixel_t)*temp->h*temp->w);
    int max_w = max(temp->w, img->w); //max wert fuer breite
    int max_h = max(temp->h, img->h); //max wert fuer hoehe
    for(int i = 0; i < max_h; i++){
        if(i >= temp->h) break; // original ist hoeher als kopie
        for(int j = 0; j < max_w; j++){
            if(j>= temp->w) break; // original ist breit als kopie
            if(j>= img->w || i>= img->h){  // kopie ist breiter als original oder groesser als original
                temp->img[temp->w*i+j].r = 0;
                temp->img[temp->w*i+j].g = 0;
                temp->img[temp->w*i+j].b = 0;
            }
            else{
                temp->img[temp->w*i+j] = img->img[img->w*i+j];  // wenn passt wird nur kopiert
            }
        }
    }

    image_free(img);  // speicher bereinigen
    img->h = temp->h;
    img->w =temp->w;
    img->img = malloc(sizeof(pixel_t)*img->h*img->w);  // neu erstellen
    for(int i = 0; i <img->h*img->w; i++){
        img->img[i] = temp->img[i]; // bild auf img kopoieren
    }

    free(temp->img);
    free(temp);
    
}


