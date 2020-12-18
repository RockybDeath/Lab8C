#ifndef SEPIA_C_H
#define SEPIA_C_H

#include <stdlib.h>
#include "image_utils.h"
#include "bmp_struct.h"

void sepia_c( struct image* img, struct image* res );
void sepia_one_asm(struct pixel* pixel);

#endif
