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
} GPS;

typedef struct
{
	char treasure_id[11];
	char username[35];
	GPS coord;
	char clue[51];
	int value;
} TREASURE;

void create_directory(char pathname[])
{
	int status = mkdir(pathname, 0755); //read and execute permissions for everyone, plus write permission to user
	
	if (status != 0 && errno != EEXIST) //ignores error if directory already exists
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

void read_line(char* str, size_t size)
{
	fgets(str, size, stdin);
	str[strcspn(str, "\n")] = '\0';
}

int check_format(char* critical_chars, char* str, int include)
{
	//this function checks the format of a given string by checking if
	//if it contains a character from the critical_chars string. The
	//validation result of the format depends on the 'include' 
	//parameter - if it's 0, at least one of the critical_chars must be
	//included in the original string. If it's 1, it must not contain
	//any of the characters from critical_chars.

	int format = 0;
	for (int i = 0; i < strlen(str); i++)
	{
		if (strchr(critical_chars, str[i]))
			format = 1;
	}

	if (include == 1) //critical_chars characters are not allowed to be in the string
		if (format)
		{
			printf("Invalid format - try again\n");	
			return 1;
		}
		else return 0;
	else   //at least one critical_chars character must be in the string
		if (format == 0)
		{
			printf("Invalid format - try again\n");	
			return 1;
		}
		else return 0;
}


TREASURE read_treasure(char* filepath)
{
	//reads treasure details from keyboard
	TREASURE tr;
	int format = 1; //variable to allow user to retry writing data if the given value has wrong format

	while (format)
	{
		printf("Username (cannot contain whitespaces or any of the following symbols /:*?<>|): ");
		read_line(tr.username, sizeof(tr.username));
		format = check_format("	 /:*?<>|", tr.username, 1);	
	}

	format = 1; //reset variable for the next value

	while (format)
	{
		printf("Treasure id (must contain at least one number): ");
		read_line(tr.treasure_id, sizeof(tr.treasure_id));
		format = check_format("0123456789", tr.treasure_id, 0);	

		int f_out = 0;
		f_out = open_file_read(filepath);
		TREASURE existing_treasure; //check for any treasure_id duplicates

		while (read(f_out, &existing_treasure, sizeof(TREASURE)) == sizeof(TREASURE))
		{
			if (strcmp(existing_treasure.treasure_id, tr.treasure_id) == 0)
			{
				printf("A treasure with this id already exists - try again\n");
				format = 1;
			}
		}
	}

	format = 1;
	while (format)
	{
		printf("X (must be between -500 and 500): ");
		scanf("%f", &tr.coord.x);
		if (tr.coord.x < -500 || tr.coord.x > 500)
		{
			printf("Invalid X coordinate - try again\n");
		}
		else format = 0;
	}

	format = 1;
	while (format)
	{
		printf("Y (must be between -500 and 500): ");
		scanf("%f", &tr.coord.y);
		if (tr.coord.y < -500 || tr.coord.y > 500)
		{
			printf("Invalid Y coordinate - try again\n");
		}
		else format = 0;
	}

	printf("Clue (50 characters max): ");
	getchar();
	read_line(tr.clue, sizeof(tr.clue));

	format = 1;
	while (format)
	{
		printf("Value (must be between 5 and 12000): ");
		scanf("%d", &tr.value);
		if (tr.value < 5 || tr.value > 12000)
		{
			printf("Invalid treasure value - try again\n");
		}
		else format = 0;
	}

	return tr;
}

void write_treasure(int f_out, TREASURE tr)
{
	//writes treasure to a file

	if (write(f_out, &tr, sizeof(tr)) == -1)
	{
		perror("Error writing in file\n");
		exit(-1);
	}
}

void get_time(struct tm *local_time, char* final_time)
{
	//gets time format to a string
	strftime(final_time, 26, "%Y-%m-%d %H:%M:%S", local_time);
}

void write_log(char* pathname, char* username, char *hunt_id, char* treasure_id, char action[])
{
	//writes content to the log file
	char logpath[100];
	strcpy(logpath, pathname);
	strcat(logpath, "/logged_hunt.txt");

	int f_log = 0;

	f_log = open_file_write(logpath);

	time_t now = time(NULL);
	struct tm *local_time = localtime(&now);
	char final_time[50];

	get_time(local_time, final_time); //final_time will now contain wanted format
	char log_entry[200];

	snprintf(log_entry, sizeof(log_entry), "%s %s: %s %s in %s\n", final_time, username, action, treasure_id, hunt_id);

	if (write(f_log, log_entry, strlen(log_entry)) == -1)
	{
		perror("Error writing in log file\n");
		exit(-1);
	}
	close_file(f_log);

}

void create_symlink(char logpath[], char hunt_id[])
{
	//creates symlink to log file
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
	//more efficient to concatenate strings directly in one strcat
	//than use concat_path, which uses two strcat

	strcpy(logpath, pathname);
	strcat(logpath, "/logged_hunt.txt");

	int f_out = 0;

	f_out = open_file_write(filepath);

	if ((f_out = open(filepath, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
	{
		perror("Error opening file");
		exit(-1);
	}


	TREASURE tr;
	tr = read_treasure(filepath);

	if (lseek(f_out, 0, SEEK_END) == -1) //move cursor to end of file; same functionality as if O_APPEND was used
	{
		perror("Error lseek\n");
		exit(-1);
	}

	write_treasure(f_out, tr);
	write_log(pathname, tr.username, hunt_id, tr.treasure_id, "added");

	create_symlink(logpath, hunt_id);
	close_file(f_out);
	printf("Successfully added treasure in hunt\n");
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
		print_treasure(tr);
		printf("\n");
	}
	printf("\n");
}

void list_hunt(char hunt_id[], char pathname[])
{
	concat_path(pathname, hunt_id);
	char filepath[100];
	strcpy(filepath, pathname);
	strcat(filepath, "/treasures.bin");

	int f_out = open_file_read(filepath);
	printf("Hunt name: %s\n", hunt_id);

	struct stat statbuf;
	int status = stat(filepath, &statbuf); //get status of file

	if (status != 0)
	{
		perror("Error stat\n");
		exit(-1);
	}

	printf("File size: %ld\n", statbuf.st_size); //get size of file
	
	struct tm *local_time = localtime(&statbuf.st_mtime);
	char final_time[50];
	get_time(local_time, final_time); //get time of last edit

	printf("File last modification: %s\n", final_time);
	print_treasures(f_out);
	close_file(f_out);
	printf("Succesfully listed hunt\n");
}

void view_treasure(char* hunt_id, char* tr_id, char* pathname)
{
	int f_out = 0;
	concat_path(pathname, hunt_id);
	char filepath[100];
	strcpy(filepath, pathname);
	strcat(filepath, "/treasures.bin");
	f_out = open_file_read(filepath);

	TREASURE tr;
	int read_out = 0;
	do 
	{
		read_out = read(f_out, &tr, sizeof(TREASURE));

	}while ((strcmp(tr.treasure_id, tr_id) != 0) && read_out == sizeof(TREASURE)); //reads treasures until found or end of file

	if (strcmp(tr.treasure_id, tr_id) != 0)
	{
		printf("Treasure id could not be found\n");
		close_file(f_out);
		return;
	}
	print_treasure(tr);
	close_file(f_out);
	printf("Successfully viewed treasure\n");

}

void remove_treasure(char* hunt_id, char* tr_id, char* pathname)
{
	//this function copies the content from the original file
	//into a temporary .bak file except the treasure to be removed
	//if it exists. The original file is then truncated and the content from
	//the temporary file is re-written, and then the temporary file is removed. 
	//It wasn't necessary to use lseek to implement the intended functionality.
	//Another potential way to implement this function is to remove the original file
	//once the content has been copied, and the temporary file to be renamed to 'treasures.bin'
	//using the 'rename' function. 

	char username[35];

	int format = 1; //variable to allow user to retry writing data if the given value has wrong format

	while (format)
	{
		printf("Username (cannot contain whitespaces or any of the following symbols /:*?<>|): ");
		read_line(username, sizeof(username));
		format = check_format("	 /:*?<>|", username, 1);	
	}

	int f_out = 0, f_temp = 0;
	concat_path(pathname, hunt_id);
	char filepath[100], temppath[100];
	strcpy(filepath, pathname);
	strcat(filepath, "/treasures.bin");
	strcpy(temppath, filepath);
	strcat(temppath, ".bak"); //create temporary file treasures.bin.bak
	f_out = open_file_read(filepath);
	f_temp = open_file_write(temppath);
	TREASURE tr;
	int found = 0;

	while (read(f_out, &tr, sizeof(TREASURE)) == sizeof(TREASURE))
	{
		if (strcmp(tr_id, tr.treasure_id) != 0)
		{
			write_treasure(f_temp, tr); //write treasures in temporary file as long as they're not the treasure to be removed
		}
		else found = 1; //wanted treasure is found
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

	if ((f_out = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1) //truncated the original file
	{
		perror("Error opening file");
		exit(-1);
	}

	while (read(f_temp, &tr, sizeof(TREASURE)) == sizeof(TREASURE))
	{
		write_treasure(f_out, tr); //copy contents from temporary file in original file
	}
	close_file(f_out);
	close_file(f_temp);

	if (remove(temppath) != 0) //delete temporary file
	{
		perror("Could not remove file\n");
		exit(-1);
	}

	write_log(pathname, username, hunt_id, tr_id, "removed"); //add to log
	printf("Successfully removed treasure\n");
}

void empty_directory(char* dirpath)
{
	//this function empties given directory
	DIR *dir = opendir(dirpath);
	if (dir == NULL)
	{
		perror("Could not open directory");
		exit(-1);
	}

	char filepath[100];
	
	struct dirent* entry;
	errno = 0; //set to 0 to distinguish end of stream from an error

	while ((entry = readdir(dir)) != NULL)
	{
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
		continue; //skips . and .. from directory
		
		strcpy(filepath, dirpath);
		concat_path(filepath, entry->d_name);
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

	if (errno != 0)
	{
		perror("Error reading directory\n");
		exit(-1);
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

	empty_directory(dirpath); //empty the content of the directory

	concat_path(sympath, symname);
	if (remove(dirpath) != 0)
	{
		perror("Could not remove directory");
		exit(-1);
	}

	if (unlink(sympath) != 0) //remove symlink
	{
		perror("Error remove symlink");
		exit(-1);
	}
	printf("Successfully removed hunt\n");
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

		view_treasure(hunt_id, tr_id, pathname);
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

		remove_treasure(hunt_id, tr_id, pathname);
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

	return 0;
}
