#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define NAME_OFFSET 0x76171
int main(int argc,char** argv){
	const char* hbname = argv[1];
	if (strlen(hbname) == 8){
		FILE* tmp = fopen("launcher.elf", "rb");
		fseek(tmp, 0, SEEK_END);
		uint64_t size = ftell(tmp);
		printf("Read %llu bytes.\n", size);
		fseek(tmp, 0, SEEK_SET);
		uint8_t* content = (uint8_t*)malloc(size);
		fread(content, 1, size, tmp);
		fclose(tmp);
		FILE* output = fopen("launcher2.elf", "wb+");
		memcpy(&content[NAME_OFFSET], hbname, 8);
		printf("Writing %llu bytes.\n", size);
		fwrite(content, 1, size, output);
		fclose(output);
	}
}