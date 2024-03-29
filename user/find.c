#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char*
fmtname(char *path){
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

void find(char *path, char *target) {
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    fprintf(2, "ls: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch(st.type){
  case T_FILE:
    fprintf(2, "Should be a directory");
    break;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("ls: path too long\n");
      break;
    }
    strcpy(buf, path); // buf := path
    p = buf+strlen(buf);
    *p++ = '/';
    

    // loop over the current directory
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0 || strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      // DIRSIZ == 14
      if(stat(buf, &st) < 0){
        printf("ls: cannot stat %s\n", buf);
        continue;
      }

      if(st.type == T_DIR){
        find(buf, target);
      }else if(st.type == T_FILE){
        if(strcmp(de.name, target) == 0){
            printf("%s\n", buf);
        }
      }

    }
    break;
  }
  close(fd);
}



int main(int argc, char *argv[]){
    if(argc != 3){
        fprintf(2, "Should pass 2 parameters\n");
        exit(1);
    }

    char *path = argv[1];
    char *target = argv[2];

    find(path, target);

    return 0;
}