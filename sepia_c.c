#include "sepia_c.h"

static unsigned char sat( uint64_t x) {
    if (x < 256) {
            return x; 
    }
    return 255;
}

static struct pixel sepia_one( struct pixel const source_pixel ) {
    static const float c[3][3] = {
            {.393f, .769f, .189f},
            {.349f, .686f, .168f},
            {.272f, .543f, .131f}};
    struct pixel result_pixel;
    result_pixel.r = sat(
            source_pixel.r * c[0][0] + source_pixel.g * c[0][1] + source_pixel.b * c[0][2]
    );
    result_pixel.g = sat(
            source_pixel.r * c[1][0] + source_pixel.g * c[1][1] + source_pixel.b * c[1][2]
    );
    result_pixel.b = sat(
            source_pixel.r * c[2][0] + source_pixel.g * c[2][1] + source_pixel.b * c[2][2]
    );
    return result_pixel;
}
void sepia_one_asm(struct pixel* pixel) {	
	static const float c[3][3] = {
		{ 0.393f, 0.769f, 0.189f },
		{ 0.349f, 0.686f, 0.168f },
		{ 0.272f, 0.534f, 0.131f }
	};
	struct pixel const old = *pixel;
	pixel->r = sat(old.r * c[0][0] + old.g * c[1][0] + old.b * c[2][0]);
	pixel->g = sat(old.r * c[0][1] + old.g * c[1][1] + old.b * c[2][1]);
	pixel->b = sat(old.r * c[0][2] + old.g * c[1][2] + old.b * c[2][2]);
}
void sepia_c( struct image* image, struct image* result ) {
    uint32_t x,y;
    struct pixel result_pixel;
    result->width = image->width;
    result->height = image->height;
    result->data = malloc(sizeof(struct pixel) * result->width * result->height);
    for( y = 0; y < image->height; y++ )
        for( x = 0; x < image->width; x++ ) {
            result_pixel = sepia_one(get_pixel(*image, x, y));
            set_pixel(result, x, y, result_pixel);
        }
}
