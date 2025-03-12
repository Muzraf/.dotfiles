#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char **argv) {
  int returnvalue = 0;
  char *buff=NULL;
  size_t buff_size;
  char * tok;
  char *dirs[2];
  int num = 0;
  char *dlfname;
  char *pwd = getenv("PWD");
  char *home = getenv("HOME");
  if (strcmp(pwd, home) == 0) return 0;
  dlfname=malloc(strlen(home)+256);
  strcpy(dlfname, home);
  strcat(dlfname, "/.dir-last");
  FILE *dlfp = fopen(dlfname, "r");
  if (!dlfp) goto writeit;

  fseek(dlfp, 0, SEEK_END);
  buff_size = ftell(dlfp);
  fseek(dlfp, 0, SEEK_SET);
  buff = malloc(buff_size);
  fread(buff, 1, buff_size, dlfp);
  fclose (dlfp);
  for (;;) {
    static int first = 1;
    if (first){tok = strtok(buff, "\n");first=0;}
    else tok=strtok(NULL, "\n");
    if (!tok) break;
    if (strcmp(tok, pwd) == 0) continue;
    for (int i=0; i<num; ++i)
      if (strcmp(tok, dirs[i])==0)continue;
  
    dirs[num] = tok;
    num++;
    if (num > 1) break;
  }

writeit:
  dlfp = fopen(dlfname, "w");
  if (!dlfp)
    goto errorhaha;
  fprintf(dlfp, "%s\n",pwd);
  for (int i=0;i<num;++i)
    fprintf(dlfp, "%s\n", dirs[i]);
  fclose (dlfp);

  goto noerrorhaha;
errorhaha:
  returnvalue=1;
noerrorhaha:
  free(buff);
  free(dlfname);
  return returnvalue;
  
}
