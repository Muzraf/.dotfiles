#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

struct {char *major,*minor,*micro;} version = {
	"0","9","alpha"
};

int main(int argc, char **argv) {
	if (argc != 2) return 1;
	if (strcmp(argv[1], "--version") == 0) {
		printf("%s.%s.%s\n", version.major, version.minor, version.micro);
		return 0;
	}
	if (strcmp(argv[1], "--help") == 0) {
    printf("Usage: %s PATH\n--help\tto print this message\n--version\tto print version\n", argv[0]);
		return 0;
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

	envs[];
	size_t max_i=0;
	int found=0;
	for (i=0;i<sizeof(envs)/sizeof(envs[0]);++i) {
		if (strncmp(argv[1],envs[i].value,envs[i].len) == 0)
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

	if (found)
	{
		printf("%s%s\n",envs[max_i].shrunk_value, argv[1] + envs[max_i].len);
	} else {
		printf("%s\n", argv[1]);
	}
	return !found;
}
