#include "../include/shell.h"

FILE * shell_init(char * batchfile){

    FILE * fp;
    if(strcmp(batchfile, "stdin") == 0){
        fp = stdin;
    }else{
        fp = fopen(batchfile, "r");
        if(fp == NULL){
            display_error();
            exit(1);
        }
    }
    // Initialize the environment variable with the "/bin" directory
    initialize_path();
    return fp;
}

void shell_start(FILE * stream){

    char * input_string = NULL;
    int char_count = 0;
    if((char_count = read_input_line(&input_string, stream)) == EOF){ exit(0); }

    int token_count = count_tokens(input_string, char_count);
    if(token_count){
        char ** cmd_tokens = (char **) malloc(sizeof(char *) * (token_count +1));
        // Extract tokens from source (input_string) to destination (cmd_tokens)
        extract_token(input_string, cmd_tokens, " \n");
        free(input_string);
        command_select(cmd_tokens, token_count);
        free_token_array(cmd_tokens, token_count+1);
    }else{
        free(input_string);
    }
}