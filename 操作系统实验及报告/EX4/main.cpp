#include <sys/types.h>
#include <dirent.h> 
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <grp.h> 
#include <pwd.h>

char *dir = NULL;

void printInfo(const struct stat statbuf, const char *name, int depth){
    int flag = 0;
    printf("%3d ", depth);
    mode_t mod = statbuf.st_mode;//文件类型
    if(S_ISREG(mod)) printf("-");//普通文件
    if(S_ISDIR(mod)) {
        printf("d");//目录文件
        flag = 1;
    }
    if(S_ISCHR(mod)) printf("c");//字符设备文件
    if(S_ISBLK(mod)) printf("b");//块设备文件
    if(S_ISLNK(mod)) printf("l");//管道文件
    if(S_ISSOCK(mod)) printf("s");//符号链接
    if(S_ISFIFO(mod)) printf("p");//套接口
    int i = 9;
    while(i--){//user、group、other权限
        if(mod & 1<<i){
            switch((8-i) % 3){
                case 0: printf("r");//读
                break;
                case 1: printf("w");//写
                break;
                case 2: printf("x");//执行
                break;
            }
        }else{
            printf("-");//无
        }
    }
    printf("%2d ",(int)statbuf.st_nlink);
    printf("%4s ",getpwuid(statbuf.st_uid)->pw_name);//文件属主
    printf("%4s ",getgrgid(statbuf.st_gid)->gr_name);//文件属组
    printf("%6ld ",statbuf.st_size);//文件大小
    const struct tm *tmp;//获取时间信息
    tmp = localtime(&(statbuf.st_mtime));
    printf("%2d月 %2d %2d:%2d ",( 1 + tmp->tm_mon), tmp->tm_mday,
		tmp->tm_hour, tmp->tm_min);
    if(flag == 1) printf("\033[1;40;32m%s\033[0m\n", name);//文件名
    else printf("%s\n",name);
}

void printfdir(char *dir, int depth){
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    if  ((dp = opendir(dir)) == NULL){       //opendir  
        printf("open dir failed!\n");        //打印出错信息
        return ;
    }
    chdir(dir);//将dir设置为当前目录; //chdir      
    while((entry = readdir(dp)) != NULL){
        lstat(entry->d_name, &statbuf);//以该目录项的名字为参数,调用lstat得到该目录项的相关信息;
        if(S_ISDIR(statbuf.st_mode)){
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 ){
				continue;
            }
            //打印目录项的深度、目录名等信息//printf(%*depth)
            printInfo(statbuf, entry->d_name, depth);
            printfdir(entry->d_name, depth + 4);//递归调用printdir,打印子目录的信息,其中的depth+4;
        }
	    else{//打印文件的深度、文件名等信息
            printInfo(statbuf,entry->d_name, depth);
        }
    }
    chdir("..");//返回父目录; //chdir
    closedir(dp);//关闭目录项; //closedir
}

int main(int argc, char *argv[]){
    if (argc >= 2) {
        dir = argv[1];
    }else{
        printf("缺少参数\n");
        return -1;
    }
	printf("%s 目录结构：\n", dir);
	printfdir(dir, 0);
	printf("打印结束\n");
    return 0;
}
