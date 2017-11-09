int numberLength(unsigned int number){
    int length=1;
    while(number>=10){
        length++;
        number/=10;
    }
    return length;
}

void decodeOneInstruction(unsigned char instr, unsigned char text[1024][64], int* row, int fd, int* blocks){
    unsigned char buf;
    unsigned int col=8, number=0;
    //printf("%0x ",instr);
    switch(instr){
        case 0x01:
            text[*row][col++]='v';
            text[*row][col++]='s';
            text[*row][col++]='e';
            text[*row][col++]='t';
            col++;
            text[*row][col++]='r';
            read(fd,&buf,1);
            text[*row][col++]=buf+0x30;
            text[*row][col++]=',';
            col++;
            read(fd,&buf,1);
            number=buf;
            read(fd,&buf,1);
            number+=buf<<8;
            read(fd,&buf,1);
            number+=buf<<16;
            read(fd,&buf,1);
            number+=buf<<24;
            int length = numberLength(number);
            if(length>=9)text[*row][col++]=(number/100000000)-(number/1000000000)*10+0x30;
            if(length>=8)text[*row][col++]=(number/10000000)-(number/100000000)*10+0x30;
            if(length>=7)text[*row][col++]=(number/1000000)-(number/10000000)*10+0x30;
            if(length>=6)text[*row][col++]=(number/100000)-(number/1000000)*10+0x30;
            if(length>=5)text[*row][col++]=(number/10000)-(number/100000)*10+0x30;
            if(length>=4)text[*row][col++]=(number/1000)-(number/10000)*10+0x30;
            if(length>=3)text[*row][col++]=(number/100)-(number/1000)*10+0x30;
            if(length>=2)text[*row][col++]=(number/10)-(number/100)*10+0x30;
            if(length>=1)text[*row][col++]=(number/1)-(number/10)*10+0x30;
            text[*row][col++]='\n';
            (*row)++;
            break;
        case 0x17:
            text[*row][col++]='v';
            text[*row][col++]='x';
            text[*row][col++]='o';
            text[*row][col++]='r';
            col++;
            text[*row][col++]='r';
            read(fd,&buf,1);
            text[*row][col++]=buf+0x30;
            text[*row][col++]=',';
            col++;
            text[*row][col++]='r';
            read(fd,&buf,1);
            text[*row][col++]=buf+0x30;
            text[*row][col++]='\n';
            (*row)++;
            break;
        case 0x04:
            text[*row][col++]='v';
            text[*row][col++]='l';
            text[*row][col++]='d';
            text[*row][col++]='b';
            col++;
            text[*row][col++]='r';
            read(fd,&buf,1);
            text[*row][col++]=buf+0x30;
            text[*row][col++]=',';
            col++;
            text[*row][col++]='r';
            read(fd,&buf,1);
            text[*row][col++]=buf+0x30;
            text[*row][col++]='\n';
            (*row)++;
            break;
        case 0x20:
            text[*row][col++]='v';
            text[*row][col++]='c';
            text[*row][col++]='m';
            text[*row][col++]='p';
            col++;
            text[*row][col++]='r';
            read(fd,&buf,1);
            text[*row][col++]=buf+0x30;
            text[*row][col++]=',';
            col++;
            text[*row][col++]='r';
            read(fd,&buf,1);
            text[*row][col++]=buf+0x30;
            text[*row][col++]='\n';
            (*row)++;
            break;
        case 0x21:
            text[*row][col++]='v';
            text[*row][col++]='j';
            text[*row][col++]='z';
            col++;
            text[*row][col++]='b';
            text[*row][col++]='l';
            text[*row][col++]=(*blocks)+65;
            read(fd,&buf,1);
            text[*row][col++]=buf+0x30;
            text[*row][col++]=',';
            col++;
            text[*row][col++]='r';
            read(fd,&buf,1);
            text[*row][col++]=buf+0x30;
            text[*row][col++]='\n';
            (*row)++;
            break;
    }
}
