#include "shader_reader.h"
#include <stdio.h>
#include <stdlib.h>

char* load_file(const char* file) {
    FILE* pfile = fopen(file, "rb"); 
    
    if (pfile == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo de shader: %s\n", file);
        return NULL;
    }

    fseek(pfile, 0, SEEK_END);
    long length = ftell(pfile);
    fseek(pfile, 0, SEEK_SET);

    char* buffer = (char*)malloc(length + 1);
    
    if (buffer == NULL) {
        fclose(pfile);
        return NULL;
    }

    size_t read_bytes = fread(buffer, 1, length, pfile);
    
    buffer[read_bytes] = '\0';

    fclose(pfile);
    return buffer;
}