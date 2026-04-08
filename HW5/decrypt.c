#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <assert.h>

#define MAX 10240
#define MAX_WORD_COUNT 60000
#define MAX_WORD_LENGTH 80

char words[MAX_WORD_COUNT][MAX_WORD_LENGTH];
int word_count = 0;

//Note the words in the dictionary file are sorted
void read_file_to_array(char *filename)
{
    FILE *fp;

    fp = fopen(filename, "r");
    if(fp==NULL)
    {
        printf("Cannot open file %s.\n", filename);
        exit(-1);
    }

    while(!feof(fp))
        fscanf(fp, "%s\n", words[word_count++]);

    fclose(fp);
}

//Test whether a string word is in the dictionary
//Return 1 if word is in the dictionary
//Return 0 otherwise
int in_dict(char *word)
{
    int left = 0;
    int right = word_count - 1;

    while(left <= right)
    {
        int mid = (left + right) / 2;
        int cmp = strcmp(word, words[mid]);

        if(cmp == 0)
            return 1;
        else if(cmp < 0)
            right = mid - 1;
        else
            left = mid + 1;
    }

    return 0;
}

//Use key and shift to decrypt the encrypted message
void decryption(unsigned char key, unsigned char shift, const int *encrypted, int len, char *decrypted)
{
    for(int i = 0; i < len; i++)
    {
        decrypted[i] = (char)((encrypted[i] ^ key) >> shift);
    }

    decrypted[len] = '\0';
}

//calculate a score for a message msg
int message_score(const char *msg)
{
    int score = 0;

    char temp[MAX];
    strcpy(temp, msg);

    char *token = strtok(temp, " ,.!?;:\n\t");

    while(token != NULL)
    {
        if(in_dict(token))
            score++;

        token = strtok(NULL, " ,.!?;:\n\t");
    }

    return score;
}

//search using all the (key, shift) combinations
//to find the original message
void search(const int *encrypted, int len, char *message)
{
	char decrypted[MAX];

    int max_score = 0;
    strcpy(message, "");
    for(unsigned char k = 0; k < 255; k++)
    {
        for(unsigned char shift = 0; shift <= 24; shift++)
        {
            decryption(k, shift, encrypted, len, decrypted);
			int score = message_score(decrypted);
			if(score > max_score)
			{
				max_score = score;
				strcpy(message, decrypted);
			}
        }
    }
}

//read the encrypted message from the file
int read_encrypted(char *filename, int *encrypted)
{
    int fd = open(filename, O_RDONLY);

    if(fd < 0)
    {
        printf("Cannot open file %s\n", filename);
        exit(-1);
    }

    int bytes = read(fd, encrypted, MAX * sizeof(int));

    close(fd);

    return bytes / sizeof(int);
}

//Do not change the main() function
int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("%s encrypted-message\n", argv[0]);
		return 0;
	}

	read_file_to_array("dict.txt");

	int encrypted[MAX];
	int len = read_encrypted(argv[1], encrypted);

	char message[MAX];
	strcpy(message, "");
	search(encrypted, len, message);
	printf("%s\n", message);
	return 0;
}