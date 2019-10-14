
#pragma once

typedef unsigned int uint;
typedef unsigned char uint8;

void decompressBlockETC2c(uint block_part1, uint block_part2, uint8* img,
	int width, int height, int startx, int starty, int channels);
void decompressBlockETC21BitAlphaC(uint block_part1, uint block_part2, uint8* img, uint8* alphaimg,
	int width, int height, int startx, int starty, int channels);
void decompressBlockAlphaC(uint8* data, uint8* img,
	int width, int height, int startx, int starty, int channels);
void decompressBlockAlpha16bitC(uint8* data, uint8* img,
	int width, int height, int startx, int starty, int channels);