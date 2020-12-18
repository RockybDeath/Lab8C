#include "image_utils.h"

void set_pixel(const struct image* img, uint64_t x, uint64_t y, struct pixel p) {
    img->data[y * img->width + x] = p;
}

struct pixel get_pixel(const struct image img, uint64_t x, uint64_t y) {
    return img.data[y * img.width + x];
}

