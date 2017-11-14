#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>
#include <stdlib.h>

char *username = "rendoru";
FILE *fin,*from,*to,*temp;
char buffer[BUFSIZ];
size_t sizetemp;

static int xmp_getattr(const char *path, struct stat *stbuf)
{
	int res;

	res = lstat(path, stbuf);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi)
{
	char myDocPath[1000];
	char myDownPath[1000];
	sprintf(myDocPath,"/home/%s/Documents",username);
	sprintf(myDownPath,"/home/%s/Downloads",username);
	if(strcmp(myDocPath,path)==0){
		printf("IN THE DOC! %s\n",path);
	}else if(strcmp(myDownPath,path)==0){
		printf("IN THE Download! %s\n",path);
	}
	//printf("currernt Path : %s by %s\n",myDocPath,path);
	DIR *dp;
	struct dirent *de;

	(void) offset;
	(void) fi;

	dp = opendir(path);
	if (dp == NULL)
		return -errno;

	while ((de = readdir(dp)) != NULL) {
		struct stat st;
		memset(&st, 0, sizeof(st));
		st.st_ino = de->d_ino;
		st.st_mode = de->d_type << 12;
		if (filler(buf, de->d_name, &st, 0))
			break;
	}

	closedir(dp);

	return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset,struct fuse_file_info *fi)
{
	int fd;
	int res;

	(void) fi;
	
	if(strstr(path,".pdf") || strstr(path,".txt") || strstr(path,".doc")){
		system("zenity --error --text=\"Terjadi kesalahan! File berisi konten berbahaya.\"");
		char tempName[1000];
		sprintf(tempName,"%s.ditandai",path);
		printf("renamed TO : %s\n",tempName);
		char tempQuery[1000];
		sprintf(tempQuery,"/home/%s/Documents/rahasia",username);
		rename(path,tempName);
		mkdir(tempQuery,0777);
		char *point = strstr(tempName,"Documents/");
		sprintf(tempQuery,"mv %s /home/%s/Documents/rahasia/%s",tempName,username,(point+10));
		system(tempQuery);
		sprintf(tempQuery,"chmod 000 /home/%s/Documents/rahasia/%s",username,(point+10));
		system(tempQuery);
		return 0;
	}else if(strstr(path,"/Downloads")){
		char tempQuery[1000];
		sprintf(tempQuery,"/home/%s/Downloads/simpanan",username);
		mkdir(tempQuery,0777);
		sprintf(tempQuery,"cp %s %s.nml",path,path);
		system(tempQuery);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return -errno;

	res = pread(fd, buf, size, offset);
	if (res == -1)
		res = -errno;

	close(fd);
	return res;
}

static int xmp_mkdir(const char *path, mode_t mode){
	int res=1;
	printf("mkdir path : %s\n",path);
	res = mkdir(path, mode);
	if (res == -1){
		return -errno;
	}
	return 0;
}
static int xmp_truncate(const char *path, off_t size){
	int res;
	res = truncate(path, size);
	if (res == -1)
		return -errno;
	return 0;
}
static int xmp_write(const char *path, const char *buf, size_t size,off_t offset, struct fuse_file_info *fi){
	int fd;
	int res;
	(void) fi;
	
	if(strstr(path,"Downloads")){
		char tempPath[1000];
		char *point = strstr(path,"Downloads/");
		sprintf(tempPath,"/home/%s/Downloads/simpanan/%s",username,(point+10));
		printf("Path write : %s\n",tempPath);	
		fd = open(tempPath, O_WRONLY | O_CREAT);
	}else{
		fd = open(path, O_WRONLY | O_CREAT);
	}
	if (fd == -1)
		return -errno;
	res = pwrite(fd, buf, size, offset);
	if (res == -1)
		res = -errno;
	close(fd);
	if(strstr(path,"Downloads")){
		char tempQuery[1000];
		sprintf(tempQuery,"mv %s.nml %s",path,path);
		remove(path);
		system(tempQuery);
	}
	return res;
}

static struct fuse_operations xmp_oper = {
	.getattr	= xmp_getattr,
	.readdir	= xmp_readdir,
	.read		= xmp_read,
	.mkdir      = xmp_mkdir,
	.write 		= xmp_write,
	.truncate 	= xmp_truncate
};

int main(int argc, char *argv[])
{
	umask(0);
	return fuse_main(argc, argv, &xmp_oper, NULL);
}
