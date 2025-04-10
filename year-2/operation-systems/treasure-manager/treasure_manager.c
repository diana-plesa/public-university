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
		//printf("Error creating directory\n");
		perror("Error creating directory");
		exit(-1);
	}
}

int open_file_write(char filename[])
{
	int f_out = 0;
	if ((f_out = open(filename, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
	{
		//printf("Error opening file\n");
		perror("Error opening file");
		exit(-1);
	}

	return f_out;
}

int open_file_read(char filename[])
{
	int f_out = 0;
	if ((f_out = open(filename, O_RDONLY)) == -1)
	{
		//printf("Error opening file\n");
		perror("Error opening file");
		exit(-1);
	}

	return f_out;
}

void close_file(int f_out)
{
	if (close(f_out) != 0)
	{
		perror("Error closing file");
		exit(-1);
	}
}

void file_exists(char* filepath)
{
	if (access(filepath, F_OK) == 0) return;
	else 
	{
		printf("File does not exist\n");
		exit(-1);
	}
}

// void dir_exists(char *dirpath)
// {
// 	DIR* dir = opendir(dirpath);
// 	if (dir == NULL)
// 	{
// 		// if (errno == ENOENT)
// 		// {
// 		// 	printf("Directory does not exist\n");
// 		// 	exit(-1);
// 		// }

// 		perror("Error opening directory\n");
// 		exit(-1);
// 	}

// }

TREASURE read_treasure()
{
	TREASURE tr;

	printf("Username: ");
	scanf("%s", tr.username);
	printf("Treasure id: ");
	scanf("%s", tr.treasure_id);
	printf("X: ");
	scanf("%f", &tr.coord.x);
	printf("Y: ");
	scanf("%f", &tr.coord.y);
	printf("Clue: ");
	getchar();
	fgets(tr.clue, sizeof(tr.clue), stdin);
	tr.clue[strcspn(tr.clue, "\n")] = '\0';
	printf("Value: ");
	scanf("%d", &tr.value);

	return tr;
}

void write_treasure(int f_out, TREASURE tr)
{

	if (write(f_out, &tr, sizeof(tr)) == -1)
	{
		perror("Error writing in file\n");
		exit(-1);
	}
}

void get_time(struct tm *local_time, char* final_time)
{
	strftime(final_time, 26, "%Y-%m-%d %H:%M:%S", local_time);
}

void write_log(int f_out, TREASURE tr, char action[])
{
	time_t now = time(NULL);
	struct tm *local_time = localtime(&now);
	char final_time[50];

	get_time(local_time, final_time);
	char log_entry[200];

	snprintf(log_entry, sizeof(log_entry), "%s %s: %s %s\n", final_time, tr.username, action, tr.treasure_id);

	if (write(f_out, log_entry, strlen(log_entry)) == -1)
	{
		perror("Error writing in log file\n");
		exit(-1);
	}
}

void create_symlink(char logpath[], char hunt_id[])
{
	char sym_path[100];
	strcpy(sym_path, "logged_hunt-");
	strcat(sym_path, hunt_id);

	if (symlink(logpath, sym_path) != 0 && errno != EEXIST)
	{
		perror("Error creating symlink");
		exit(-1);
	}
}

void concat_path(char* path1, char *path2)
{
	strcat(path1, "/");
	strcat(path1, path2);
}

void add_hunt(char hunt_id[], char pathname[])
{
	//strcat(pathname, hunt_id);
	concat_path(pathname, hunt_id);
	create_directory(pathname);

	char filepath[100];
	char logpath[100];
	strcpy(filepath, pathname);
	strcat(filepath, "/treasures.bin");

	strcpy(logpath, pathname);
	strcat(logpath, "/logged_hunt.txt");

	int f_out = 0, f_log = 0;

	f_out = open_file_write(filepath);
	f_log = open_file_write(logpath);

	TREASURE tr;
	tr = read_treasure();

	write_treasure(f_out, tr);
	write_log(f_log, tr, "add");

	create_symlink(logpath, hunt_id);
	close_file(f_out);
	close_file(f_log);

}

void print_treasure(TREASURE tr)
{
	printf("Treasure id: %s\n", tr.treasure_id);
	printf("Username: %s\n", tr.username);
	printf("X: %.3f\n", tr.coord.x);
	printf("Y: %.3f\n", tr.coord.y);
	printf("Clue: %s\n", tr.clue);
	printf("Value: %d\n", tr.value);
}

void print_treasures(int file_out)
{
	printf("TREASURES IN HUNT\n-----------------\n");
	TREASURE tr;
	while (read(file_out, &tr, sizeof(TREASURE)) == sizeof(TREASURE))
	{
		//printf("%s ", tr.treasure_id);
		print_treasure(tr);
		printf("\n");
	}
	printf("\n");
}

void list_hunt(char hunt_id[], char pathname[])
{
	//strcat(pathname, hunt_id);
	concat_path(pathname, hunt_id);
	//dir_exists(pathname);
	char filepath[100];
	strcpy(filepath, pathname);
	strcat(filepath, "/treasures.bin");

	int f_out = open_file_read(filepath);
	printf("Hunt name: %s\n", hunt_id);

	struct stat statbuf;
	int status = stat(filepath, &statbuf);

	if (status != 0)
	{
		perror("Error stat\n");
		exit(-1);
	}

	printf("File size: %ld\n", statbuf.st_size);
	
	struct tm *local_time = localtime(&statbuf.st_mtime);
	char final_time[50];
	get_time(local_time, final_time);

	printf("File last modification: %s\n", final_time);
	print_treasures(f_out);


	close_file(f_out);
}

void view_tr(char* hunt_id, char* tr_id, char* pathname)
{
	int f_out = 0;
	concat_path(pathname, hunt_id);
	//dir_exists(pathname);
	char filepath[100];
	strcpy(filepath, pathname);
	strcat(filepath, "/treasures.bin");
	f_out = open_file_read(filepath);

	TREASURE tr;
	int read_out = 0;
	do 
	{
		read_out = read(f_out, &tr, sizeof(TREASURE));

	}while ((strcmp(tr.treasure_id, tr_id) != 0) && read_out == sizeof(TREASURE));

	if (strcmp(tr.treasure_id, tr_id) != 0)
	{
		printf("Treasure id could not be found\n");
		return;
	}
	print_treasure(tr);
	
}

int main(int argc, char** argv)
{
	char pathname[100];
	strcpy(pathname, "/home/vboxuser/FACULTATE/An2/TreasureManager/");
	
	if (argc == 1)
	{
		printf("Invalid count of arguments - format should be:\n");
		printf("./exec --add <hunt_id>\n");
		printf("./exec --list <hunt_id>\n");
		printf("./exec --view <hunt_id> <id>\n");
		printf("./exec --remove_treasure <hunt_id> <id>\n");
		printf("./texec --remove_hunt <hunt_id>\n");
		printf("Note: <hunt_id> has format huntnumber, eg. 'hunt1', and <treasure_id> has format treasurenumber, eg. 'treasure2'\n");

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
		add_hunt(hunt_id, pathname);
	}
	else if (strcmp(argv[1], "--list") == 0)
	{
		if (argc == 2)
		{
			printf("Format should be ./exec --list <hunt_id>\n");
			return 0;
		}

		char hunt_id[35];
		strcpy(hunt_id, argv[2]);
		list_hunt(hunt_id, pathname);
	}

	else if (strcmp(argv[1], "--view") == 0)
	{
		if (argc == 2 || argc == 3)
		{
			printf("Format should be ./exec --view <hunt_id> <id>\n");
			return 0;
		}

		char hunt_id[35];
		char tr_id[11];
		strcpy(hunt_id, argv[2]);
		strcpy(tr_id, argv[3]);

		view_tr(hunt_id, tr_id, pathname);
	}

	//!!!! basic data validation
	return 0;
}
