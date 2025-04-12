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
	char clue[51];
	int value;
}TREASURE;

void create_directory(char pathname[])
{
	int status = mkdir(pathname, 0755);
	
	if (status != 0 && errno != EEXIST)
	{
		perror("Error creating directory");
		exit(-1);
	}
}

int open_file_write(char filename[])
{
	int f_out = 0;
	if ((f_out = open(filename, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
	{
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

TREASURE read_treasure()
{
	TREASURE tr;

	printf("Username (cannot contain whitespaces) (34 characters max): ");
	scanf("%34s", tr.username);
	printf("Treasure id (must contain at least one number) (10 characters max): ");
	scanf("%10s", tr.treasure_id);
	int id_format = 1;
	for (int i = 0; i < strlen(tr.treasure_id); i++)
	{
		if (strchr("0123456789", tr.treasure_id[i]))
			id_format = 0;
	}
	if (id_format)
	{
		printf("Invalid treasure_id format\n");
		exit(-1);
	}
	printf("X (must be between -500 and 500): ");
	getchar();
	scanf("%f", &tr.coord.x);
	if (tr.coord.x < -500 || tr.coord.x > 500)
	{
		printf("Invalid X coordinate\n");
		exit(-1);
	}
	printf("Y (must be between -500 and 500): ");
	getchar();
	scanf("%f", &tr.coord.y);
	if (tr.coord.y < -500 || tr.coord.y > 500)
	{
		printf("Invalid Y coordinate\n");
		exit(-1);
	}
	printf("Clue (50 characters max): ");
	getchar();
	fgets(tr.clue, sizeof(tr.clue), stdin);
	tr.clue[strcspn(tr.clue, "\n")] = '\0';
	printf("Value (must be between 5 and 12000): ");
	scanf("%d", &tr.value);
	if (tr.value < 5 || tr.value > 12000)
	{
		printf("Invalid treasure value\n");
		exit(-1);
	}

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

void write_log(char* pathname, char* username, char* id, char action[])
{
	char logpath[100];
	strcpy(logpath, pathname);
	strcat(logpath, "/logged_hunt.txt");

	int f_log = 0;

	f_log = open_file_write(logpath);

	time_t now = time(NULL);
	struct tm *local_time = localtime(&now);
	char final_time[50];

	get_time(local_time, final_time);
	char log_entry[200];

	snprintf(log_entry, sizeof(log_entry), "%s %s: %s %s\n", final_time, username, action, id);

	if (write(f_log, log_entry, strlen(log_entry)) == -1)
	{
		perror("Error writing in log file\n");
		exit(-1);
	}
	close_file(f_log);

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
	concat_path(pathname, hunt_id);
	create_directory(pathname);

	char filepath[100];
	char logpath[100];
	strcpy(filepath, pathname);
	strcat(filepath, "/treasures.bin");

	strcpy(logpath, pathname);
	strcat(logpath, "/logged_hunt.txt");

	int f_out = 0;

	f_out = open_file_write(filepath);

	TREASURE tr;
	tr = read_treasure();

	write_treasure(f_out, tr);
	write_log(pathname, tr.username, tr.treasure_id, "add");

	create_symlink(logpath, hunt_id);
	close_file(f_out);
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
		close_file(f_out);
		return;
	}
	print_treasure(tr);
	close_file(f_out);

}

void remove_tr(char* hunt_id, char* tr_id, char* pathname)
{
	char username[35];
	printf("Username: ");
	scanf("%s", username);
	int f_out = 0, f_temp = 0;
	concat_path(pathname, hunt_id);
	char filepath[100], temppath[100];
	strcpy(filepath, pathname);
	strcat(filepath, "/treasures.bin");
	strcpy(temppath, filepath);
	strcat(temppath, ".bak");
	f_out = open_file_read(filepath);
	f_temp = open_file_write(temppath);
	TREASURE tr;
	int found = 0;

	while (read(f_out, &tr, sizeof(TREASURE)) == sizeof(TREASURE))
	{
		if (strcmp(tr_id, tr.treasure_id) != 0)
		{
			write_treasure(f_temp, tr);
		}
		else found = 1;
	}

	close_file(f_temp);
	close_file(f_out);


	if (found == 0)
	{
		printf("Treasure id could not be found\n");

		if (remove(temppath) != 0)
		{
			perror("Could not remove file\n");
			exit(-1);
		}
		return;
	}
	f_temp = open_file_read(temppath);

	if ((f_out = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
	{
		perror("Error opening file");
		exit(-1);
	}

	while (read(f_temp, &tr, sizeof(TREASURE)) == sizeof(TREASURE))
	{
		write_treasure(f_out, tr);
	}
	close_file(f_out);
	close_file(f_temp);

	if (remove(temppath) != 0)
	{
		perror("Could not remove file\n");
		exit(-1);
	}
	char action[35];
	strcpy(action, "remove from ");
	strcat(action, hunt_id);

	write_log(pathname, username, tr_id, action);
}

void remove_in_dir(char* dirpath, char* pathname)
{
	DIR *dir = opendir(dirpath);
	if (dir == NULL)
	{
		perror("Could not open directory");
		exit(-1);
	}

	char filepath[100];
	
	struct dirent* entry;
	errno = 0;

	while ((entry = readdir(dir)) != NULL)
	{
		//printf("%s\n", entry->d_name);
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
		continue;
		
		strcpy(filepath, dirpath);
		concat_path(filepath, entry->d_name);
		//printf("%s\n", filepath);
		if (remove(filepath) != 0)
		{
			perror("Could not remove file inside hunt directory");
			if (closedir(dir) != 0)
			{
				perror("Error closing directory\n");
				exit(-1);
			}
			exit(-1);
		}
	}

		if (closedir(dir) != 0)
	{
		perror("Error closing directory\n");
		exit(-1);
	}

}

void remove_hunt(char* hunt_id, char* pathname)
{
	char dirpath[100], sympath[100], symname[50];
	strcpy(dirpath, pathname);
	strcpy(sympath, pathname);
	strcpy(symname, "logged_hunt-");
	strcat(symname, hunt_id);
	concat_path(dirpath, hunt_id);

	remove_in_dir(dirpath, pathname);

	concat_path(sympath, symname);
	if (remove(dirpath) != 0)
	{
		perror("Could not remove directory");
		exit(-1);
	}

	if (unlink(sympath) != 0)
	{
		perror("Error remove symlink");
		exit(-1);
	}

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
		if (argc != 3)
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
		if (argc != 3)
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
		if (argc != 4)
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

	else if (strcmp(argv[1], "--remove_treasure") == 0)
	{
		if (argc != 4)
		{
			printf("Format should be ./exec --remove_treasure <hunt_id> <id>\n");
			return 0;
		}

		char hunt_id[35];
		char tr_id[11];
		strcpy(hunt_id, argv[2]);
		strcpy(tr_id, argv[3]);

		remove_tr(hunt_id, tr_id, pathname);
	}

		else if (strcmp(argv[1], "--remove_hunt") == 0)
	{
		if (argc != 3)
		{
			printf("Format should be ./exec --remove_hunt <hunt_id>\n");
			return 0;
		}

		char hunt_id[35];
		strcpy(hunt_id, argv[2]);

		remove_hunt(hunt_id, pathname);
	}

	//!!!! basic data validation
	return 0;
}
