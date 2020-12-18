#include "sepia_sse.h"
#include "sepia_c.h"

extern void sepia_asm(float source[12], float result[12]);

void sepia_sse(struct image* image, struct image* res){
	size_t pixel_size = image->width * image->height;
	size_t pixel_floor = (pixel_size / 4)*4;
	struct pixel pixel;
	float source[12];
	float result[12];
	size_t i;
	size_t j;
	size_t cycle;
	for (i = 0; i < pixel_floor; i += 4){
		for (j = 0; j < 4; j ++) {
			pixel = image->data[i + j];
			source[j*3] = pixel.r;
			source[j*3 + 1] = pixel.g;
			source[j*3 + 2] = pixel.b;
		}
		sepia_asm(source, result);
		for (j = 0; j < 4; j ++) {
			pixel.r = result[j*3];
		    pixel.g = result[j*3 + 1];
		    pixel.b = result[j*3 + 2];
			image->data[i + j] = pixel;
		}
	}
	cycle = pixel_size - pixel_floor;
	for (i = 0; i < cycle; i ++) {
		pixel = image->data[i + pixel_floor];
		sepia_one_asm(&pixel);
	}
}


