#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

char *reading_line()
{
	char *input = NULL;
	size_t temp = 0;
	getline(&input,&temp,stdin);

	return input;
}

char **split_line(char *line)
{
	char *delim= " \t\n\r\a";
	int num_words = 30,num=0;
	char *token;
	char **tokens = malloc(num_words*sizeof(char *));
	if(!tokens)
		fprintf(stderr,"memory allocation fail");

	token = strtok(line,delim);
	while(token != NULL)
	{
		tokens[num]= token;
		num++;
		if(num >= num_words)
		{
			num_words += num_words;
			tokens = realloc(tokens,num_words*sizeof(char *));
			if(!tokens)
				fprintf(stderr,"memory reallocation fail");
		}
		token = strtok(NULL,delim);
	}
	tokens[num] = NULL;
	return tokens;
}

char non_builtin(char **args)
{
	pid_t pid = fork();
	int status;

	if(pid ==0)
	{
		if(execvp(args[0],args)!=0)
		{
			fprintf(stderr,"execution error");
			exit(EXIT_FAILURE);
		}
	}
	else if(pid <0)
		fprintf(stderr,"fork error");
	else
	{
		do
		{
		waitpid(pid,&status,WUNTRACED);
		}while(!WIFEXITED(status)&&!WIFSIGNALED(status));
	}
	return !status;
}

int shell_cd(char **args);
int shell_exit(char **args);

int shell_cd(char **args)
{
	if(args[1]==NULL)
		fprintf(stderr,"expecting an argument after \"cd\"");
	else
	{
		if(chdir(args[1])!=0)
			perror("dir change error");
	}
	return 1;
}

int shell_exit(char **args)
{
	return 0;
}

char *builtin_list[] = {"cd","exit"};
int (*builtin_func[])(char **args) = {&shell_cd,&shell_exit};

#define num_builtin (sizeof(builtin_list)/sizeof(char *))
int shell_execute(char **args)
{
	if(args[0]==NULL)
		return 1;

	for(int i=0;i<num_builtin;i++)
	{
		if(strcmp(args[0],builtin_list[i])==0)
			return (builtin_func[i])(args);
	}
	return non_builtin(args);
}

int main()
{
	char *line;
	char **args;
	int status;

	do
	{
		printf(">> ");
		line = reading_line();
		args = split_line(line);
		status = shell_execute(args);
		free(line);
		free(args);
	}while(status);
	return 0;
}
