C_FLAGS = -ansi -pedantic -Wall -Werror -lm -g -c
ASM_FLAGS = -felf64 -o
compile: 
	gcc $(C_FLAGS) bmp_struct.c -o build/bmp_struct.o
	gcc $(C_FLAGS) image_utils.c -o build/image_utils.o
	gcc -O2 $(C_FLAGS) sepia_c.c -o build/sepia_c.o
	nasm $(ASM_FLAGS) build/sse.o sse.asm
	gcc $(C_FLAGS) sepia_sse.c -o build/sepia_sse.o
	gcc $(C_FLAGS) main.c -o build/main.o
	gcc -g -lm build/*.o -o build/main
remove:
	rm -f main
