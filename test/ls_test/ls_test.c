#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


int cmd_ls(char *path, char result[256][32])
{
    if(!path || !result)
        return -1;

     DIR *dir;
    char str[32];
    struct dirent *rent;

    dir = opendir(path);
    int cnt = 0;

    while((rent=readdir(dir)))
    {
        strcpy(str, rent->d_name);
        if(str[0] == '.')
        {
            continue;
        }
        if(!str)
        {
            continue;
        }

        sprintf(result[cnt++], "%s",str);
    }

    puts("");

    closedir(dir);
    return cnt;
}


int main()
{

    char *path = "/dev/rfcomm0";
    char result[256][32] = {0};

 #ifdef Main  
    int cnt = cmd_ls(path, result);
    int i = 0;
    for(i=0; i<cnt; i++)
    {
        printf("result[%d][%s]\n", i,result[i]);
    }  
#endif


    int ret = 0;
    access("./ls_test", F_OK);

    if (ret == 0)
    {
        printf("file exist!\n");
    }

  
   

    return 0;

}
