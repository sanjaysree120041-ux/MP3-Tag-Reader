#include <stdio.h>
#include "type.h"
#include "view.h"
#include "edit.h"
#include<string.h>
int main(int argc,char *argv[]) 
{
  
    if(check_operation_type(argv)==e_view)
    {
        printf(BLUE"\n⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝ VIEW  ⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝\n"RESET);
        if(read_and_validate_view_args(argv) == e_success)
        {
           // printf(GREEN"Read and Validate is successfull\n"RESET);
            do_view_operation(argv);
        }
        else
        {
            printf(RED"Read and Validate is un-successfull\n"RESET);
            return e_failure;
        }
    }
    else if(check_operation_type(argv)==e_edit)
    {
        printf(BLUE"\n⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝ EDITING  ⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝⁝\n"RESET);
        if(read_and_validate_edit_args(argv) == e_success)
        {
            //printf(GREEN"Read and Validate is successfull\n"RESET);
            do_edit_operation(argv[2],argv[3],argv[4]);
        }
        else
        {
            printf(RED"Read and Validate failed\n"RESET);
            return e_failure;
        }
    }
    else if(check_operation_type(argv)==e_help)
    {
        printf("1. -v=> To view mp3 file contents\n");
        printf("2. -e=> To edit mp3 file contents\n");
        printf("\t2.1 -t=>To edit song title\n");
        printf("\t2.2 -a=>To edit artist name\n");
        printf("\t2.3 -A=>To edit album name\n");
        printf("\t2.4 -y=>To edit song year\n");
        printf("\t2.5 -g=>To edit song genre\n");
        printf("\t2.6 -c=>To edit comment\n");
    } 
    else
    {
        printf(RED"Pass correct arguments\n"RESET);
        printf(CYAN"To view please pass like : ./a.out -v mp3_file_name\n"RESET);
        printf(CYAN"To edit please pass like : ./a.out -e -t/-a/-A/-g/-y/-c New_data MP3_file_name\n"RESET);
        printf(CYAN"To get help pass like : ./a.out -h\n"RESET);
    }
    return e_success;
}
OperationType check_operation_type(char *argv[])
{
    if(argv[1]==NULL)
        return e_unsupported;
    if(strcmp(argv[1],"-v")==0)
        return e_view;
    else if(strcmp(argv[1],"-e")==0)
        return e_edit;
    else if(strcmp(argv[1],"-h")==0)
        return e_help;
    else
        return e_unsupported;
}

