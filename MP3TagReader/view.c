#include <stdio.h>
#include "type.h"
#include "view.h"
#include<string.h>

Status read_and_validate_view_args(char *argv[])
{
    if(strstr(argv[2],".mp3") !=NULL)           //check ,mp3 file is present or not
    {
        return e_success; 
    }
    else
    {
        printf(RED".mp3 is not present\n"RESET);
        return e_failure;
    }
}
Status do_view_operation(char *argv[])
{
    if(open_files(argv[2])==e_success)             //check the mp3 file the opening or not
    {
        return e_success;
    }
    else
    {
        printf(RED"Files are not opened\n"RESET);
        return e_failure;
    }
}
Status open_files(char *mp3file)
{
    FILE *fp=fopen("sample.mp3","r");           //read on mp3 file
    if(fp==NULL)
    {
        printf("mp3 file not present\n");
        return e_failure;
    }

    char buffer[4];
    fread(buffer,3,1,fp);               //store id3 in buffer and check
    if(strcmp(buffer,"ID3")==0)
    {
       printf(MAGENTA"\t\t\tMP3 FILE\n"RESET);
       printf(MAGENTA"\t\t      ------------\n"RESET);
    }
    else
    {
        printf("this is not mp3 file\n");
        fclose(fp);
        return e_failure;
    }
    fseek(fp,7,SEEK_CUR);                //skip the after 7 bytes.
    read_and_print_data(fp);
    fclose(fp);
    return e_success;
}
Status read_and_print_data(FILE *fp)
{
    
    while(1)
    {
        char tag[5]={0};
        fread(tag,4,1,fp);
        int size;
        fread(&size,sizeof(int),1,fp);
        size=endiness_convert(size);         //convert big to little endiness
        fseek(fp,2,SEEK_CUR);             //skip 2 bytes -flags          
        char data[size+1];
        fread(data,size,1, fp);
        data[size] = '\0';
        
        if(strcmp(tag,"TIT2")==0)                //compare the tag info
        {
            printf(MAGENTA"TITLE    : %s\n"RESET,data+1);
        }
        else if(strcmp(tag,"TYER")==0)
        {
            printf(MAGENTA"YEAR     : %s\n"RESET,data+1);
        }
        else if(strcmp(tag,"TALB")==0)
        {
            printf(MAGENTA"ALBUM    : %s\n"RESET,data+1);
        }
        else if(strcmp(tag,"TPE1")==0)
        {
            printf(MAGENTA"ARTIST   : %s\n"RESET,data+1);
        }
        else if(strcmp(tag,"COMM")==0)
        {
            printf(MAGENTA"COMMENT  : %s\n"RESET,data+1);
        }
        else if(strcmp(tag,"TCON")==0)
        {
            printf(MAGENTA"GENRE    : %s\n"RESET,data+1);
        }
        else
            return e_failure;
        
    }
    printf(BLUE"⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝\n"RESET);
    return e_success;
}
int endiness_convert(int size)               //convert big endiness to little endianess
{
    unsigned char *ptr = (unsigned char *)&size;
    unsigned char temp;

    temp=ptr[0];
    ptr[0]=ptr[3];
    ptr[3]= temp;

    temp=ptr[1];
    ptr[1]=ptr[2];
    ptr[2]=temp;

    return size;
}
