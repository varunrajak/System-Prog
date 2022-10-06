#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

void root_hirarchy(char *dr, const int root, const int root_show_value,const int root_show_check, const int root_show_Size, const int root_size_Limit, const char *root_find_Str);

int main(int argc, char *argv[]) // to pass the command line arguements (directory name,inputs options(-s,-f,-S)
{
    // Directory path to list files
    char root_dr_path[100];
    int root_show_Size = 0,root_show_check=0,root_show_value=0;
    int root_size_Limit = 0;
    char *root_find_Str;

    int root_opt;
    if (argv[1] != NULL)
    {
        root_hirarchy(root_dr_path, 0, root_show_value,root_show_check,root_show_Size, root_size_Limit, root_find_Str);
    }

    while ((root_opt = getopt(argc, argv, "s:f:S")) != -1) //To display according to the input option given accrdingly
    {
        switch (root_opt)
        {
        case 's':                       
            root_show_check =1;
            root_size_Limit = atoi(optarg);
            printf("Show files above [%d] kbs\n", root_size_Limit);

            break;
        case 'S':
            root_show_Size = 1;
            printf("Show file sizes fileName(size)\n");
            break;
        case 'f':
            root_show_value=1;
            root_find_Str = optarg;
            printf("option (f) find[%s]\n", root_find_Str);
            break;
        default:
            printf("Usage: [directory] [-S] [-s] [limit in kb] [-f] [string to find]\n");
            return -1;
        }
    }

    root_hirarchy(".", 0, root_show_value,root_show_check,root_show_Size, root_size_Limit, root_find_Str);

    return 0;
}

/**
 * prints all the directories, subdirectory and files.

*/
int root_F_check_Size(char *root_check_s)
{
    struct stat value;
    if (stat(root_check_s, &value) == -1)
    {
        perror("stat");
        exit(EXIT_FAILURE);
    }
    return value.st_size;
}
void root_hirarchy(char *dr, const int root, const int root_show_value,const int root_show_check,const int root_show_Size, const int root_size_Limit, const char *root_find_Str)
{
    int i;
    char root_dr_path[1000];
    struct dirent *root_dp_s;
    struct stat filestats;

    DIR *dir = opendir(dr);

    if (!dir)
        return;

   
    while ((root_dp_s = readdir(dir)) != NULL)
    {
        if (strcmp(root_dp_s->d_name, ".") != 0 && strcmp(root_dp_s->d_name, "..") != 0)
        {
            // for (i = 0; i < root; i++)
            // {
            //     if (i % 2 == 0 || i == 0)
            //         printf("|");
            //     else
            //         printf("--");
            // }
          
            strcpy(root_dr_path, dr);
            strcat(root_dr_path, "/");
            strcat(root_dr_path, root_dp_s->d_name);

            if (root_show_Size != 0)
            {
                printf(" ->%s ( %lld )\n", root_dp_s->d_name, filestats.st_size);
            }
            else if(root_show_check !=0)
            {
                if(root_F_check_Size(root_dr_path) >= root_size_Limit)
                {
                    printf(" ->%s\n", root_dp_s->d_name);
                }
            }
            else if(root_show_value !=0)
            {
                if(strstr(root_dp_s->d_name,root_find_Str))
                {
                    printf(" ->%s\n", root_dp_s->d_name);
                }
            }
            else
            {
                printf(" ->%s\n", root_dp_s->d_name);
            }

            if (S_ISDIR(filestats.st_mode))
            {

                root_hirarchy(root_dr_path, root + 2,root_show_value,root_show_check, root_show_Size, root_size_Limit, root_find_Str);
            }
        }
    }

    closedir(dir);
}