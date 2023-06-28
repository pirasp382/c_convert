#include "flood_fill.h"

#include <stdbool.h>
#include <stdlib.h>

#include "util.h"

void flood(image_t *img, int x, int y, pixel_t *target_color) {
    // DONE
    if(x <0 || y <0 || x >=img->w || y >= img->h){ // nicht im Bild
        return;
    }
    int r = img->img[img->w*y+x].r;
    int g = img->img[img->w*y+x].g;
    int b = img->img[img->w*y+x].b;  //zwischenspeichern fuer kontrolle bei nachbarn
    img->img[img->w*y+x] = *target_color;  // aendere farbe bei aktuellem pixel
    if(x-1>=0 && img->img[img->w*y+x-1].r == r && img->img[img->w*y+x-1].g == g && img->img[img->w*y+x-1].b == b){ // nach westen
        flood(img, x-1,y, target_color);
    }
    if(x+1<img->w && img->img[img->w*y+x+1].r == r && img->img[img->w*y+x+1].g == g && img->img[img->w*y+x+1].b == b){ // nach osten
        flood(img, x+1,y, target_color);
    }
    if(y+1<img->h && img->img[img->w*(y+1)+x].r == r && img->img[img->w*(y+1)+x].g == g && img->img[img->w*(y+1)+x].b == b){ // nach sueden
        flood(img, x,y+1, target_color);
    }
    if(y-1>=0 && img->img[img->w*(y-1)+x].r == r && img->img[img->w*(y-1)+x].g == g && img->img[img->w*(y-1)+x].b == b){ // nach norden
        flood(img, x,y-1, target_color);
    }
    return;
}
