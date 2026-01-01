#include <stdio.h>
#include "view.h"
#include "edit.h"
#include "type.h"
#include<string.h>

Status read_and_validate_edit_args(char *argv[])
{
    if (strstr(argv[2], "-t") != NULL || strstr(argv[2], "-a") != NULL || strstr(argv[2], "-A") != NULL ||
        strstr(argv[2], "-g") != NULL || strstr(argv[2], "-y") != NULL || strstr(argv[2], "-c") != NULL)
    {
        //printf("successful\n");
        return e_success;
    }
    else
    {
        printf(RED".mp3 is not present\n"RESET);
        return e_failure;
    }
}

Status do_edit_operation(char *option,char *new_value,char *filename)
{
    char frame_id[5]={0};
    if(strcmp(option,"-t")==0)
        strcpy(frame_id,"TIT2");
    else if(strcmp(option,"-a")==0)
        strcpy(frame_id,"TPE1");
    else if(strcmp(option,"-A")==0)
        strcpy(frame_id,"TALB");
    else if(strcmp(option,"-y")==0)
        strcpy(frame_id,"TYER");
    else if(strcmp(option,"-c")==0)
        strcpy(frame_id,"COMM");
    else if(strcmp(option,"-g")==0)
        strcpy(frame_id,"TCON");
    else
    {
        printf("Invalid option\n");
        return e_failure;
    }
    FILE *fp=fopen(filename,"r");          
    if(fp==NULL)
    {
        printf("mp3 file not present\n");
        return e_failure;
    }
    FILE *temp_fp=fopen("temp.mp3","w");
    if(temp_fp==NULL)
    {
        printf("temporary mp3 file not present\n");
        fclose(fp);
        return e_failure;
    }
    char buffer[10];
    if (fread(buffer, 1, 10, fp) != 10)
    {
        printf("Failed to read MP3 header\n");              // Read ID3 header
        fclose(fp);
        fclose(temp_fp);
        return e_failure;
    }             
    fwrite(buffer,10,1,temp_fp);           //write same header into temp    
    while(1)
    {
        char tag[5]={0};
        if(fread(tag,1,4,fp) !=4)               //read tag
            break; 
        tag[4] = '\0';           
        int size;
        unsigned char flag[2];
        int real_size;
        if (fread(&real_size,4,1,fp) != 1) 
            break;
        if(fread(flag,2,1,fp)!=1)
             break;
        size= endiness_convert(real_size);
        //printf("tag: %s\n",tag);
        if(strcmp(tag,frame_id)==0)
        {
            //printf("tag: %s\n",tag);
            fwrite(tag,1,4,temp_fp);                    //store tag in the temp 
            int new_size=strlen(new_value)+1;
            int new_siz=endiness_convert(new_size);  
    
            fwrite(&new_siz,4,1, temp_fp);
            fwrite(flag,1,2,temp_fp);

            unsigned char enc;
            fread(&enc, 1, 1, fp);       // FIX 4: Read encoding byte
            fwrite(&enc, 1, 1, temp_fp); // FIX 5: Write encoding byte

            fwrite(new_value,1,new_size-1,temp_fp);
            fseek(fp,size-1,SEEK_CUR);    //skip old content 
            int ch;
            while((ch=fgetc(fp))!=EOF) //one by noe copy the remaining content
                fputc(ch,temp_fp);
            printf(GREEN"SUCCESSFULLY EDITED\n"RESET);
            break;
        }
        else
        { 
            fwrite(tag, 1, 4, temp_fp);
            fwrite(&real_size, 4,1, temp_fp);
            fwrite(flag,1,2,temp_fp);
            //fwrite(new_value,size-1,1,temp_fp);
           for(int j=0;j<size;j++)
           {
                int c=fgetc(fp);
                if(c==EOF)
                    break;
                fputc(c,temp_fp);
           }
        }
    }
    fclose(fp);
    fclose(temp_fp);
    remove(filename);      //remove the original file
    rename("temp.mp3",filename);            //remove temp file as original file
    return e_success;
}
