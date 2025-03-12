#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

struct {char *major,*minor,*micro;} version = {
	"0","9","alpha"
};

int main(int argc, char **argv) {
	if (argc == 1) return 1;
	if (strcmp(argv[1], "--version") == 0) {
		printf("%s.%s.%s\n", version.major, version.minor, version.micro);
		return 0;
	}
	if (strcmp(argv[1], "--help") == 0) {
    printf("Usage: %s PATH\n--help\tto print this message\n--version\tto print version\n", argv[0]);
		return 0;
  }
  int cols = -1;
	int margi = 1;
	if (strcmp(argv[1], "-c")== 0) {
		if (argc == 4) {
			cols = atoi(argv[2]);
			margi = 3;
		} else {
			return 1;
		}
  }
  
	struct {
		char * name;
		char * value;
		size_t len;
		char * shrunk_value;
	} envs[] = {
	{"HOME", NULL, 0, "~"},
	{"PREFIX", NULL, 0, "~/../usr"},
	{NULL, "", 0, "~/.."},
	};
	int i;
	for (i=0;i<sizeof(envs)/sizeof(envs[0]);++i) {
		if (!envs[i].name) continue;
		envs[i].value = getenv(envs[i].name);
		envs[i].len = strlen(envs[i].value);
	}
	
	size_t max_i=0;
	int found=0;
	for (i=0;i<sizeof(envs)/sizeof(envs[0]);++i) {
		if (strncmp(argv[margi],envs[i].value,envs[i].len) == 0)
		{
			if (found) {
				if (envs[max_i].len < envs[i].len)
				{
					max_i = i;
				}
			} else {
				found = 1;
				max_i = i;
			}
		}
  }

	if (cols >= 0) {
		char s[cols + 1];
		s[cols] = '\0';
		memset(s, '.', cols);
		int el, al, tl;
		el = found ? strlen(envs[max_i].shrunk_value) : 0;
		al = found ? strlen(argv[margi]) - envs[max_i].len : strlen(argv[margi]);
		tl = el + al;
		char ss[tl+1];
		if (cols <= 3) goto there;
		if (found) strcpy(ss, envs[max_i].shrunk_value);
		strcat(ss, found ? argv[margi] + envs[max_i].len : argv[margi]);
		if (tl > cols) {
			for (int i=0; i<(-1+cols/2); ++i)
				s[i] = ss[i];
			for (int i=2+cols/2, j = tl + 2 - cols/2; i<(cols); ++i, ++j)
			{
				s[i] = ss[j];
			}
		} else {
			goto here;
		}
there:
		printf("%s\n", s);
	}else {
here:
		if (found)
		{
			printf("%s%s\n",envs[max_i].shrunk_value,  argv[margi] + envs[max_i].len);
		} else {
			printf("%s\n", argv[margi]);
		}
	}
	return !found;
}
