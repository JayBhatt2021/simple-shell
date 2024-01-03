/**
 * @file SimpleShell.cpp
 * @author Jay Bhatt (jay.bhatt98@gmail.com)
 * @brief Simple shell program.
 * @version 1.0
 * @date 2024-01-03
 *
 * @copyright Copyright (c) 2024 Jay Bhatt
 *
 */

#include <cstring>
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>

/**
 * @brief Maximum number of characters allowed in a single shell line.
 */
#define MAXLINE 80

/**
 * @brief Converts the user-inputted command to an array of arguments.
 *
 * @param commandHolder The user-inputted command.
 * @param args The array to store individual arguments.
 */
void convertInputToArgs(char *commandHolder, char **args)
{
   // Iterates through commandHolder until the null terminator is reached
   while (*commandHolder != '\0')
   {
      // Skips the leading spaces
      while (*commandHolder == ' ')
      {
         // Replaces each space with a null terminator
         *commandHolder++ = '\0';
      }

      // Saves the current argument
      *args++ = commandHolder;

      // Moves to the end of the current argument
      while (!(*commandHolder == ' ' || *commandHolder == '\0'))
      {
         // Moves to the next character
         commandHolder++;
      }
   }

   // Sets the last argument to nullptr
   *args = nullptr;
}

/**
 * @brief Main function of SimpleShell.cpp.
 *
 * @return int The exit code.
 */
int main(void)
{
   // Holds the command entered by the user
   char commandHolder[MAXLINE];

   // Contains the command line arguments
   char *args[MAXLINE / 2 + 1];

   // Continuously listens for user inputs
   while (1)
   {
      // Displays the shell prompt to the user
      std::cout << "simple-shell> ";

      // Clears the output buffer of streams
      fflush(stdout);

      // Stores the user input in commandHolder and performs a carriage return
      // in the console
      std::cin.getline(commandHolder, MAXLINE);
      std::cout << "\r";

      // Converts the user-inputted command to an array of arguments
      convertInputToArgs(commandHolder, args);

      // Successfully exits if the user entered "exit" in the console
      if (strcmp(args[0], "exit") == 0)
      {
         exit(0);
      }

      // Forks a child process and stores its process ID
      int childPid = fork();

      if (childPid < 0) /* fork() failed. */
      {
         // Displays an error message and exits the program with an error code
         std::cerr << "Error: A child process could not be created.\n";
         exit(1);
      }
      else if (childPid == 0) /* New child process created. */
      {
         // Executes the command with its arguments
         if (execvp(args[0], args) < 0)
         {
            // Displays an error message and exits the program with an error
            // code
            std::cerr << "Error: execvp() could not execute properly.\n";
            exit(1);
         }
      }
      else /* Parent process is waiting for the child process to finish. */
      {
         // Determines if the parent process is waiting for the child process
         // to finish
         int waitingForChildProcess;

         // Suspends the calling process until the system gets status
         // information on the child
         while (waitpid(childPid, &waitingForChildProcess, 0) != childPid)
         {
         }
      }
   }

   // Successfully exits the program
   exit(0);
}
