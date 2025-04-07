#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

const int PASS_LEN = 20;        // Maximum any password will be
const int HASH_LEN = 33;        // Length of MD5 hash strings

//Nora Van Leer
// Given a target plaintext word, use it to try to find
// a matching hash in the hashFile.
// Get this function working first!
void removeNL(char * string,int length)//removes new line and replaces with string termination
{
    for(int i = 0; i < length; i++)
        if(string[i] == '\n')
        {
            string[i] = '\0';
            return;
        }
    return;
}
char * tryWord(char * plaintext, char * hashFilename)
{
    // Hash the plaintext
    char * hash = md5(plaintext,strlen(plaintext));
    // Open the hash file
    FILE * dict = fopen(hashFilename, "r");
    // Loop through the hash file, one line at a time.
    char line[100];
    while(fgets(line,99,dict) != NULL)
    {
        removeNL(hash,strlen(hash));//ensure both strings dont have a new line marker
       
        removeNL(line,strlen(line));//ensure both strings dont have a new line marker

        if(strcmp(line,hash) == 0)//if the hashes match return the hash
        {
            fclose(dict);
            return hash;
        }
        
    }
    fclose(dict);
    return NULL;
    // Attempt to match the hash from the file to the
    
    // hash of the plaintext.

    // If there is a match, you'll return the hash.
    // If not, return NULL.

    // Before returning, do any needed cleanup:
    //   Close files?
    //   Free memory?

    // Modify this line so it returns the hash
    // that was found, or NULL if not found.
    //return "0123456789abcdef0123456789abcdef";
}


int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        fprintf(stderr, "Usage: %s hash_file dict_file\n", argv[0]);
        exit(1);
    }

    // These two lines exist for testing. When you have
    // tryWord working, it should display the hash for "hello",
    // which is 5d41402abc4b2a76b9719d911017c592.
    // Then you can remove these two lines and complete the rest
    // of the main function below.
    
    //char *found = tryWord("hello", "hashes00.txt");
    //printf("%s %s\n", found, "hello");


    // Open the dictionary file for reading.
    FILE * diction = fopen(argv[2],"r");

    // For each dictionary word, pass it to tryWord, which
    // will attempt to match it against the hashes in the hash_file.
    char word[100];
    int i = 0;
    while(fgets(word,99,diction) != NULL)
    {
        //char * wordI = md5(word,strlen(word));
        removeNL(word, strlen(word));//remove new line
        if(tryWord(word,argv[1]) != NULL)//if not null
        {
            printf("\n%s %s", tryWord(word,argv[1]),word);//print word and hash
            i++;//increment count of cracks
        }

    }
    // If we got a match, display the hash and the word. For example:
    //   5d41402abc4b2a76b9719d911017c592 hello
    
    // Close the dictionary file.
    fclose(diction);
    // Display the number of hashes that were cracked.
    printf("\n%d hashes cracked!\n",i);
    // Free up any malloc'd memory?
}

