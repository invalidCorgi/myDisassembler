#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include "decoder.c"

int main(int argc, char* argv[])
{
    int fd, row=0, blocks=0;
    unsigned char buf, text[1024][64];
    memset(&text,32,1024*64); //fill with spaces
    
    if(argc != 2){
        puts("Usage: disasm <filename>");
        exit(0);
    }
    
    fd = open(argv[1], O_RDONLY);
    if(fd == -1){
        perror("An error occured");
        exit(0);
    }
    
    while(read(fd,&buf,1)>0){
        decodeOneInstruction(buf, text, &row, fd, &blocks);
    }
    
    for(int i=0; i<row; i++)
        for(int j=0; 1; j++){
            printf("%c",text[i][j]);
            if(text[i][j]=='\n')
                break;
        }
    close(fd);
    
    return 0;
}
