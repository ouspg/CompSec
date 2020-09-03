#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_SIZE 10
#define MAX_BUFF_SIZE 20
#define MAX_file_COUNT 10

void read_data(char* buff, size_t buff_size) {

  int c;
  int idx = 0;

  while (c = fgetc(stdin)) {
    if (idx == buff_size) {
      break;
    }
    buff[idx++] = c;
  }

  printf("Read %d bytes\n", idx);
}

void read_line(char* buff) {

  int c;
  int idx = 0;

  while (c = fgetc(stdin)) {
    if (c == '\n') {
      break;
    }
    buff[idx++] = c;
  }
}

char *files[MAX_file_COUNT] = { 0 };

void create_file(size_t size) {
  for (int i = 0; i < MAX_file_COUNT; i++) {
    if (files[i] == NULL) {
      files[i] = malloc(size);
      read_data(files[i], size);
      printf("file id: %d\n", i);
      return;
    }
  }

  printf("Database is full, you must delete a file before creating a new one!");
}

void delete_file(int file_id) {
  if (files[file_id] != NULL) {
    free(files[file_id]);
    printf("file deleted\n");
  } else {
    printf("file does not exist\n");
  }
}

char* get_file(int file_id) {
  return files[file_id];
}

void print_help() {
  printf("\nCommands:\n");
  printf("create [file_size] - create a new file\n");
  printf("read [file_id] - get file contents\n");
  printf("delete [file_id] - delete a file\n");
  printf("exit\n\n");
}

void cmd_handler() {
  char buff[MAX_BUFF_SIZE];
  char *file_data;
  
  while(1) {
    read_line(buff);
    if (strncmp(buff, "read", 4) == 0) {
      int file_id = atoi(&buff[5]);
      file_data = get_file(file_id);
      if (file_data != NULL) {
        printf("FILEDATA:");
        puts(file_data);
      }
    } else if (strncmp(buff, "create", 6) == 0) {
      int file_size = atoi(&buff[7]);
      if (file_size == 0) {
        printf("File cannot be empty\n");
        continue;
      }
      if (file_size >= MAX_FILE_SIZE) {
        printf("file size is too large! :(\n");
        continue;
      }
      create_file(file_size);
    } else if (strncmp(buff, "delete", 6) == 0) {
      int file_id = atoi(&buff[7]);
      delete_file(file_id);
    } else if (strncmp(buff, "exit", 4) == 0) {
      printf("Good bye!\n");
      break;
    } else {
      printf("\n404 - COMMAND NOT FOUND\n");
    }
  }

}

int main(int argc, const char* argv[]) {
  printf("Welcome to ultra fast and HACKER-PROOF in-memory file database version 1337!\n");
  print_help();

  cmd_handler();
}

