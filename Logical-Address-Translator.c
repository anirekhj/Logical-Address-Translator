#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[]) {
  // Open the input file
  FILE *txt_file = fopen(argv[1], "r");
  FILE *txt_file2 = fopen(argv[2], "r");
  char line[256];
  char line2[256];
  int page_table[4];
  char delim[] = ",\n";
  // Check the number of args
  if (argc != 3) {
    fprintf(txt_file, "Usage: %s, <file_name>\n");
    return 0;
  }
  if (txt_file == NULL) {
    fprintf(txt_file, "Error: can't open the Logical Address file");
  }
  if (txt_file2 == NULL) {
    fprintf(txt_file, "Error: can't open the Page Table file");
  }
  else {
    // create the page_table array
    while (fgets(line2, sizeof(line2), txt_file2)) {
      char *ptr = strtok(line2, delim);
      char *ptr2 = strtok(NULL, delim);
      if ((ptr != NULL) && (ptr2 != NULL)) {
        page_table[atoi(ptr)] = atoi(ptr2);
      }
    }
    txt_file2 = fopen("PhysicalAddresses.txt", "w");
    while (fgets(line, sizeof(line), txt_file)) {
      char *ptr = strtok(line, delim);
      if (ptr != NULL) {
        int logical_address = atoi(ptr);
        // extract page number/offset and calculate physical_address
        int page_number = logical_address>>2;
        int page_offset = logical_address&3;
        int frame_number = page_table[page_number];
        int physical_address = (frame_number << 2) | page_offset;
        fprintf(txt_file2, "%d\n", physical_address);
      }
    }
  }
  fclose(txt_file);
  fclose(txt_file2);
}
