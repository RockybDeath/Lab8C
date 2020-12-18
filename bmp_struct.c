#include <stdint.h>
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include "bmp_struct.h"

void print_error_write(enum write_status status){
    switch (status) {
        case WRITE_OK:
            printf("The file was written successfully\n");
            break;
        case WRITE_ERR:
            printf("Cant write in file\n");
            break;
    }
}

void print_error_read(enum read_status status){
    switch(status){
        case READ_OK:
            printf("The file was read successfully\n");
            break;
        case READ_ERR:
            printf("Read IO error\n");
            break;
        case READ_INVALID_HEADER:
            printf("Header of that bmp file is incorrect\n");
            break;
        case READ_INVALID_BITS:
            printf("Cant read the pixel data. The image is damaged");
            break;
    }
}

struct bmp_header create_bmp_header(struct image *img){
    struct bmp_header header;
    size_t offset= calculate_offset(img -> width);
    header.bfType = 0x4D42;
    header.bfileSize = ((img -> width + offset)*(img -> height)) + sizeof(struct bmp_header);
    header.bfReserved = 0;
    header.bOffBits = 54;
    header.biSize = 40;
    header.biPlanes = 1;
    header.biBitCount = 24;
    header.biCompression = 0;
    header.biSizeImage = ((img -> height)*((img -> width)*sizeof(struct pixel)+offset));
    header.biXPelsPerMeter = 0; 
    header.biYPelsPerMeter = 0;
    header.biClrUsed = 0;
    header.biClrImportant = 0;
    header.biWidth = img -> width;
    header.biHeight = img -> height;
    return header;
}
enum write_status write_bmp(FILE* out, struct image *write){
    size_t i;
    uint8_t spare[4] = {0};
    struct bmp_header header;
    size_t offset= calculate_offset(write -> width);

    header = create_bmp_header(write);
    if(!fwrite(&header, sizeof(struct bmp_header), 1, out)) return WRITE_ERR;
    for(i=0; i < write->height; i++){
        if(!fwrite(&write -> data[write->width*i], sizeof(struct pixel), write -> width, out)) return WRITE_ERR;
        if(offset != 0) fwrite(spare, sizeof(uint8_t), offset, out);
    }
    return WRITE_OK;
}
uint64_t calculate_offset(uint64_t img_width) {
    uint64_t offset = 4 - (img_width * sizeof(struct pixel)) % 4;
    return offset == 4 ? 0 : offset;
}
enum read_status from_bmp(FILE* in, struct image *read){
    uint8_t spare[4];
    uint64_t offset;
    struct pixel* bitSet;
    size_t i;
    struct bmp_header* header = malloc(sizeof(struct bmp_header));

    if (!fread(header, sizeof(struct bmp_header), 1, in)) return READ_ERR;
    fseek(in, header -> bOffBits, SEEK_SET);
    if(header -> bfType != 0x4D42) return READ_INVALID_HEADER;
    if (header->biBitCount != 24) return READ_INVALID_BITS;
    read->width = header->biWidth;
    read->height = header->biHeight;
    offset= calculate_offset(read -> width);
    bitSet = malloc(read->height * read->width * sizeof(struct pixel));
    for(i=0; i < read -> height; i++){
        if(!fread(bitSet+i*read->width, sizeof(struct pixel), read->width , in)) return READ_ERR;
        if(offset != 0) fread(spare, offset, 1, in);
    }
    read -> data = bitSet;
    free(header);
    return READ_OK;
}






