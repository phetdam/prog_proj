#include <stdio.h>
#include <string.h>
#include <dirent.h>

// counts number of files in a given  directory
// 
// parameters:
// char *dn - char pointer to directory name
//
// returns:
// int - number of files in directory. returns -1 if failed to open directory. 
int dirfs(char *dn) {
  // int number of files in directory
  int nf = 0;
  // pointer towards a directory entry (i.e. a file in the directory)
  struct dirent *de;
  // open current directory
  DIR *cdir = opendir(dn);
  // if *cdir is NULL, current directory failed to open or doesn't exist
  if (cdir == NULL) {
    return -1;
  }
  // else we good
  else {
    // return pointer towards directory entry from readdir(DIR *d)
    // while loop executes while directory entry pointer is nonnull
    while ((de = readdir(cdir)) != NULL) {
      // increment number of files found in directory
      nf++;
    }
    // return number of files in directory
    return nf;
  }
}

// main program
//
// parameters:
//   int argc - number of arguments
//   char *args[] - pointer array to collection of strings
int main(int argc, char *args[]) {
  // number of files in dir
  int nf;
  args[0] = "fct";
  // if no arguments are given (argc == 1), then operate on current directory
  if (argc <= 1) {
    // get number of files in current dir
    nf = dirfs(".");
  }
  // else if one argument passed
  else if (argc == 2) {
    // if  argument is --help
    if (strcmp(args[1], "--help") == 0) {
      printf("Usage: %s [ --help ] [ dirname ]\nCounts number of files in specified directory\n", args[0]);
      printf("Invoking %s without arguments is equivalent to \'%s .\'\n", args[0], args[0]);
      printf("  --help\tdisplay this help information.\n");
      return 0;
    }
    // else
    else {
      // get number of files in specified dir
      nf = dirfs(args[1]);
    }
  }
  // else too many arguments
  else {
    printf("%s: too many arguments.\n", args[0]);
  }
  // if nf == -1; failed to open current dir
  if (nf == -1) {
    printf("%s: failed to open directory %s.\n", args[0], args[1]);
    return 2;
  }
  // else print number of files in directory
  else {
    // if no arguments/current dir was passed, set args[1] to string "current directory"
    if (args[1] == NULL || strcmp(args[1], ".") == 0) {
      args[1] = "current directory";
    }
    printf("%d files in %s\n", nf, args[1]);
    return 0;
  }
}
