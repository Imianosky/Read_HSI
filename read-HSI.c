#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define NROWS  5
#define NCOLS  5
#define NBANDS 5


uint8_t read_file_byte(FILE *fp){

  uint8_t data;
  fread(&data, 1, 1, fp);
  return data;

}



int main() {
  int y,x,z;
  FILE *fp = fopen("aviris_sc0_5x5x5.RAW", "rb");
  unsigned short sample, neighbour;
  unsigned short raw_image[NBANDS][NROWS][NCOLS] = { 0x0 };
  for (y = 0; y < NROWS; y++) {
    for (x = 0; x < NCOLS; x++) {
      for (z = 0; z < NBANDS; z++) {
        sample = read_file_byte(fp) << 8;
        sample += read_file_byte(fp);
        raw_image[z][y][x] = sample;
        printf("%d", sample);


        if (y > 0) {
          neighbour = raw_image[z][y - 1][x];
        } else if (x > 0) {
          neighbour = raw_image[z][y][x - 1];
        } else {
          neighbour = raw_image[z - 1][y][x];
        }


      }
    }
  }
  fclose(fp);
}
