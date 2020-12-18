#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include "bmp_struct.h"
#include "sepia_c.h"
#include "sepia_sse.h"
#include "image_utils.h"

void time_function(void (*function)(struct image* img, struct image* res), struct image* image, struct image* result){
    struct rusage r;
    struct timeval start;
    long res;
    struct timeval end;
    getrusage(RUSAGE_SELF, &r);
    start = r.ru_utime;
    function(image, result);
    getrusage(RUSAGE_SELF, &r);
    end = r.ru_utime;
    res = ((end.tv_sec - start.tv_sec) * 1000000L) + end.tv_usec - start.tv_usec;
    printf( "Time elapsed in microseconds: %ld\n", res);
}
int main(){
    FILE* in, * out;
    struct image source_img;
    struct image result1;
    struct image result2;
    enum read_status statusRead;
    enum write_status statusWrite;

    in = fopen("build/1.bmp", "rb");
    if(in == NULL) {
        puts("Can't open file");
        return 0;
    }
    else{
        statusRead = from_bmp(in, &source_img);
        time_function(sepia_c, &source_img, &result1);
        time_function(sepia_sse, &source_img, &result2);
        if(statusRead == READ_OK){
            if(in == NULL) {
                puts("Can't open file");
                return 0;
            }
            out = fopen("build/result1.bmp", "wb");
            statusWrite = write_bmp(out, &result1);
            print_error_write(statusWrite);
            fclose(out);
            out = fopen("build/result2.bmp", "wb");
            statusWrite = write_bmp(out, &source_img);
            print_error_write(statusWrite);
        } else{
            print_error_read(statusRead);
        }
    }
    fclose(in);
    fclose(out);
    return 0;
}
