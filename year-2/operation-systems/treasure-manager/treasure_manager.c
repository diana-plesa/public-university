#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>

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

void create_directory(char pathname[])
{
	int status = mkdir(pathname, 0755);
	
	if (status != 0 && errno != EEXIST)
	{
		printf("Error creating directory\n");
		exit(-1);
	}
}

int open_file(char filename[])
{
	int f_out = 0;
	if ((f_out = open(filename, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
	{
		printf("Error opening file\n");
		exit(-1);
	}

	return f_out;
}

TREASURE read_treasure()
{
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
	//getchar();
	printf("Value: ");
	scanf("%d", &tr.value);

	return tr;
}

void write_treasure(int f_out, TREASURE tr)
{

	if (write(f_out, &tr, sizeof(tr)) == -1)
	{
		printf("Error writing in file\n");
		exit(-1);
	}
}

void write_log(int f_out, TREASURE tr)
{
	time_t now = time(NULL);
	struct tm *local_time = localtime(&now);
	char final_time[50];
	strcpy(final_time, asctime(local_time));
	final_time[strcspn(final_time, "\n")] = '\0';

	char log_entry[200];

	snprintf(log_entry, sizeof(log_entry), "User: %s - Date: %s - Treasure ID: %s\n", tr.username, final_time, tr.treasure_id);

	if (write(f_out, log_entry, strlen(log_entry)) == -1)
	{
		printf("Error writing in log file\n");
		exit(-1);
	}
}

void create_symlink(char logpath[], char pathname[])
{
	
}

void close_file(int f_out)
{
	if (close(f_out) != 0)
	{
		printf("Error closing file\n");
		exit(-1);
	}
}

void add_hunt(char hunt_id[])
{
	char pathname[100];
	strcpy(pathname, "/home/vboxuser/FACULTATE/An2/TreasureManager/");
	strcat(pathname, hunt_id);
	
	create_directory(pathname);

	char filepath[100];
	char logpath[100];
	strcpy(filepath, pathname);
	strcat(filepath, "/treasures.bin");

	strcpy(logpath, pathname);
	strcat(logpath, "/logged_hunt.txt");

	int f_out = 0, f_log = 0;

	f_out = open_file(filepath);
	f_log = open_file(logpath);

	TREASURE tr;
	tr = read_treasure();

	write_treasure(f_out, tr);
	write_log(f_log, tr);

	close_file(f_out);
	close_file(f_log);

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

	}


	return 0;
}
