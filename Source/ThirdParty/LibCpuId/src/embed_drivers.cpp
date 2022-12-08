// A simple utility to read and embed the MSR drivers for X86

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <string>
using namespace std;

const char* drivers_root = "..\\contrib\\MSR Driver\\";
const char* sourcefile = "msrdriver.c";

char* images[2];
int sizes[2];
const char* filenames[] = { "TmpRdr.sys", "TmpRdr64.sys" };
vector<string> source;

bool read_image(const char* filename, char*& image, int& isize)
{
	char fn[512];
	sprintf(fn, "%s%s", drivers_root, filename);
	FILE* f = fopen(fn, "rb");
	if (!f) return false;
	fseek(f, 0, SEEK_END);
	long size = ftell(f);
	isize = (int) size;
	rewind(f);
	image = new char[size];
	fread(image, 1, size, f);
	fclose(f);
	return true;
}

bool read_source(const char* filename)
{
	source.clear();
	FILE* f = fopen(filename, "rt");
	if (!f) return false;
	char line[200];
	while (fgets(line, sizeof(line), f)) {
		int i = (int) strlen(line);
		if (i && line[i - 1] == '\n') line[--i] = 0;
		source.push_back(string(line));
	}
	fclose(f);
	return true;
}

void print_image(FILE* f, const char* arch, const char* image, int size)
{
	fprintf(f, "int cc_%sdriver_code_size = %d;\n", arch, size);
	fprintf(f, "uint8_t cc_%sdriver_code[%d] = {", arch, size);
	for (int i = 0; i < size; i++) {
		if (i % 18 == 0) fprintf(f, "\n\t");
		fprintf(f, "0x%02x,", (unsigned) (unsigned char) image[i]);
	}
	fprintf(f, "\n};\n");
}

int main(void)
{
	for (int i = 0; i < 2; i++)
		if (!read_image(filenames[i], images[i], sizes[i])) {
			printf("Cannot read image `%s' from `%s'!\n", filenames[i], drivers_root);
			return -1;
		}
	if (!read_source(sourcefile)) {
		printf("Cannot read source `%s'\n", sourcefile);
		return -2;
	}
	FILE* f = fopen(sourcefile, "wt");
	bool on = true;
	for (unsigned i = 0; i < source.size(); i++) {
		if (source[i] == "//} end")
			on = true;
		if (on) fprintf(f, "%s\n", source[i].c_str());
		if (source[i] == "//begin {") {
			on = false;
			print_image(f, "x86", images[0], sizes[0]);
			print_image(f, "x64", images[1], sizes[1]);
		}
	}
	return 0;
}
