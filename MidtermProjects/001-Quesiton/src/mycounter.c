#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errorutil.h"
#include "mycounter.h"

int get_count(char *p, size_t size, char c)
{
    int count = 0;
    size_t i;

    for (i = 0; i < size; ++i)
        if (p[i] == c)
            ++count;
        
    return count;
}

void count_characters(int argc, char **argv, char c)
{
    FILE *f;
    int i, n, count;
    char buf[BUFSIZE];    
    
    for (i = 1; i < argc; ++i) {
        count = 0;
        if ((f = fopen(argv[i], "r")) == NULL)
            exit_fail("Can not open file");
        
        while ((n = fread(buf, 1, BUFSIZE, f)) > 0)
            count += get_count(buf, n, c);        
        
        
        if (ferror(f))
            exit_fail("Error in read");
        
        printf("Number of \'%c\' character in \'%s\' file is %d\n", c, argv[i], count);
        
        fclose(f);            
    }    
}


void run_count_characters_application(int argc, char **argv)
{    
    char c;    
    
    if (argc < 3)
        exit_fail("usage: ./mycounter file character");
    
    if (strlen(argv[argc - 1]) != 1)
        exit_fail("You have to give just one character");
    
    c = argv[argc - 1][0];
    
    count_characters(argc - 1, argv, c);    
    
}

int main(int argc, char **argv)
{
    run_count_characters_application(argc, argv);
    
    return 0;
}
