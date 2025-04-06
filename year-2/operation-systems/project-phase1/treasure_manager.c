#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

typedef struct
{
	float x;
	float y;
}GPS;

typedef struct
{
	char treasure_id[11];
	char username[35];
	GPS coord;
	char clue[50];
	int value;
}TREASURE;

void add_hunt(char hunt_id[])
{
	char pathname[70];
	strcpy(pathname, "/home/vboxuser/FACULTATE/An2/TreasureManager/");
	strcat(pathname, hunt_id);
	int status = mkdir(pathname, 0755);
	
	if (status != 0 && errno != EEXIST)
	{
		printf("Error creating directory\n");
		exit(-1);
	}
	strcat(pathname, "/treasures.bin");

	int f_out = 0;

	if ((f_out = open(pathname, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
	{
		printf("Error opening file\n");
		exit(-1);
	}

	TREASURE tr;

	printf("Treasure id: ");
	scanf("%s", tr.treasure_id);
	printf("Username: ");
	scanf("%s", tr.username);
	printf("X: ");
	scanf("%f", &tr.coord.x);
	printf("Y: ");
	scanf("%f", &tr.coord.y);
	printf("Clue: ");
	scanf("%s", tr.clue);
	printf("Value: ");
	scanf("%d", &tr.value);

	if (write(f_out, &tr, sizeof(tr)) == -1)
	{
		printf("Error writing in file\n");
		exit(-1);
	}


	if (close(f_out) != 0)
	{
		printf("Error closing file\n");
		exit(-1);
	}

}

int main(int argc, char** argv)
{
	if (argc == 1)
	{
		printf("Invalid count of arguments - format should be:\n");
		printf("./exec --add <hunt_id>\n");
		printf("./exec --list <hunt_id>\n");
		printf("./exec --view <hunt_id> <id>\n");
		printf("./exec --remove_treasure <hunt_id> <id>\n");
		printf("./texec --remove_hunt <hunt_id>\n");
		printf("Note: <hunt_id> has format huntnumber, eg. 'hunt1, and <treasure_id> has format treasurenumber, eg. 'treasure2'\n");

		return 0;
	}
	if (strcmp(argv[1], "--add") == 0)
	{
		if (argc == 2)
		{
			printf("Format should be ./exec --add <hunt_id>\n");
			return 0;
		}

		char hunt_id[35];
		strcpy(hunt_id, argv[2]);
		add_hunt(hunt_id);

		//log file!!
	}


	return 0;
}
