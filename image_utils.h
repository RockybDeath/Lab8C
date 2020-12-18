#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H
#include <inttypes.h>
#include "bmp_struct.h"

void set_pixel(const struct image* img, uint64_t x, uint64_t y, struct pixel p);
struct pixel get_pixel(const struct image img, uint64_t x, uint64_t y);
struct pixel* get_pixel_p(const struct image img, uint64_t x, uint64_t y);

#endif