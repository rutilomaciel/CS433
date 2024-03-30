/**
 * Assignment 2: Simple UNIX Shell
 * @file pcbtable.h
 * @author Rutilo Maciel
 * @brief This is the main function of a simple UNIX Shell. You may add additional functions in this file for your implementation
 * @version 0.1
 */

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

#define MAX_LINE 80 // The maximum length command

/**
 * @brief parse out the command and arguments from the input command separated by spaces
 *
 * @param command
 * @param args
 * @return int
 */

//Declarations
void inputFunc(char *file);
void outputFunc(char *file);
int parse_command(char command[], char *args[]);
void execArgs(char command[], char *args[]);
bool hasAmpersand = false; // Keep track of ampersand

//Input redirection
void inputFunc(char *file) {
    int input = open(file, O_RDONLY);
    dup2(input, 0);
    close(input);
}

//Output redirection
void outputFunc(char *file) {
    int output = open(file, O_WRONLY | O_APPEND | O_TRUNC | O_CREAT, 0200);
    dup2(output, 1);
    close(output);
}

int parse_command(char command[], char *args[])
{
    int numCount = 0; // Argument counter
    char *token = strtok(command, " "); // Stops at first whitespace
    while (token != NULL) {
        if (*token == '<') { // First test case, checking for character
            inputFunc(strtok(NULL, " ")); // Input redirect
        } else if (*token == '>') { // Next test case, Checking for character
            outputFunc(strtok(NULL, " ")); // Output redirect
        } else if (*token == '|') { // Checking for pipe
            args[numCount - 1] = NULL;
            execArgs(command, args); // Run the pipe
            numCount = 1; // One when complete
        } else { //default
            args[numCount] = token; // Stored in args
            numCount++;
        }
        token = strtok(NULL, " "); // Separate spaces and set to null
    }

    // Checking for ampersand
    if (strcmp(args[numCount - 1], "&") == 0) // Found ampersand, comparing strings
    {
        args[numCount - 1] = NULL; // Ampersand replaced with null
        hasAmpersand = true;
    }
    else // Regular command w/o ampersand
    {
        args[numCount] = NULL;
        hasAmpersand = false;
    }
    return numCount; // Index of array
}
void execArgs(char command[], char *args[]) {
    pid_t pid;
    int fd[2]; //File descriptor
    pid = fork(); // Fork call

    if (pipe(fd)) { //Check for pipe
        perror("Error:\tAbort\n");
        abort();
    }

    if (pid == 0) { //Child process
        execvp(args[0], args);

        if (execvp(args[0], args) < 0) { // Error check
            cout << "Command not found" << endl;
            exit(1);
        }
    } else { //Parent process
        if (!hasAmpersand) { // Not concurrent
            wait(NULL); // Parent waits
        }
    }
}

/**
 * @brief The main function of a simple UNIX Shell. You may add additional functions in this file for your implementation
 * @param argc The number of arguments
 * @param argv The array of arguments
 * @return The exit status of the program
 */

int main(int argc, char *argv[]) {
    char command[MAX_LINE];        //Command entered
    char *args[MAX_LINE / 2 + 1];  //Parsed command
    int should_run = 1;            //Running while true / 1
    char history[MAX_LINE];        // History storage

    while (should_run)
    {
        printf("osh> ");
        fflush(stdout);
        // Read the input command
        fgets(command, MAX_LINE, stdin);
        command[strlen(command) - 1] = '\0'; // Replace end of char array to null

        if (strncmp(command, "exit", 4) == 0) {// Exit command
            should_run = 0;
        }else if (strcmp(command, "!!") == 0){ // Execute last command entered
            if (strlen(history) == 0) {  // No previous commands stored
                cout << "No command history found." << endl;
            }else {
                cout << history << endl;
                strcpy(command, history); // Copy command to history
                int num_args = parse_command(command, args); // Command parsing
                execArgs(command, args); // Command execution
            }
        } else { // Default case
            strcpy(history, command); // copy to history

            // Error checking when ampersand is typed together with command
            for (int i = 0; i < strlen(command); i++) {
                if ((command[i] == '&') && (command[i - 1] != ' ')) { // Add space in between
                    command[i] = ' '; // Replaced with space
                    command[i + 1] = '&'; // & added to correct index
                    command[i + 2] = '\0'; // Null at end
                }
            }
            int num_args = parse_command(command, args); // Parse input
            execArgs(command, args); // Command execution
        }
    }
    return 0;
}

