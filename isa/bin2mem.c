/*
 * for BenRISC-V
 *
 * bin文件转成32位16进制数据
 */

#include "stdio.h"
#include "stdlib.h"

static long get_file_len(FILE *file) {
	long len;

	fseek(file, 0, SEEK_END);
	len = ftell(file);
	fseek(file, 0, SEEK_SET);

	return len;
}

static void
output_bin(FILE *file, unsigned char *buffer, int count)
{
	for (int i = 0; i < count; i+=4) {
		fprintf(file, "%02x", buffer[i+3]);
		fprintf(file, "%02x", buffer[i+2]);
		fprintf(file, "%02x", buffer[i+1]);
		fprintf(file, "%02x", buffer[i]);
		fprintf(file, "\n");
	}
}

int main(int argc, char *argv[]) {
	FILE *bin_file;
	FILE *target_file;
	int bin_file_size;
	unsigned char *bytes_buffer;
	size_t readsize;

	bin_file = fopen(argv[1], "rb");
	if (!bin_file) {
		printf("open %s fail\n", argv[1]);
		return 0;
	}

	target_file = fopen(argv[2], "w");
	if (!target_file) {
		printf("open %s fail\n", argv[2]);
		return 0;
	}

	bin_file_size = get_file_len(bin_file);
	if (bin_file_size <= 0) {
		printf("get bin file size fail\n");
		return 0;
	}

	printf("bin_file_size %d\n", bin_file_size);

	bytes_buffer = malloc(bin_file_size);
	if (!bytes_buffer) {
		printf("canot alloc memory\n");
		return 0;
	} 

	readsize = fread(bytes_buffer, sizeof(char), bin_file_size, bin_file);
	if (readsize != bin_file_size) {
		printf("read bin file fail\n");
		goto out;
	}

	output_bin(target_file, bytes_buffer, bin_file_size);

	printf("bin2mem done\n");

out:
	free(bytes_buffer);
	return 0;
}
