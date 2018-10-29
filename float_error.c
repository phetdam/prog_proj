/**
 * float_error.c
 *
 * some background as to why i ended up here: while reading about R, as i had 
 * to learn it for a club, i ended up finding on the great web a document 
 * titled The R Inferno, by Patrick Burns. link:
 *
 * http://www.burns-stat.com/pages/Tutor/R_inferno.pdf
 *
 * one of the first examples was on floating point precision, where the author
 * stated that the test .1 == .3 / 3 evaluates to FALSE. i did not believe it
 * until i tried it for myself, where lo and behold, it did evaluate to false.
 * since i do understand how floats are represented in the machine, i decided
 * to write a C program to see if that is just a representation issue or if R
 * is doing some funky stuff behind my back...
 *
 * Changelog:
 *
 * 10-29-2018
 *
 * added the floating-point representation of 0.3 / 3 to make the numerical
 * representation issue that causes 0.1 == 0.3 / 3 to evaluate to false more
 * clear, and finished the rest of HELP_STR (that was tedious!)
 *
 * 10-28-2018
 *
 * initial commit. looks like i got played real hard.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROGNAME "float_error"
#define HELP_FLAG "--help"
#define HELP_STR "Usage: "PROGNAME" [ "HELP_FLAG" ]\n" \
    "some background as to why i ended up here: while reading about R, as i had\n" \
    "to learn it for a club, i ended up finding on the great web a document\n" \
    "titled The R Inferno, by Patrick Burns. link:\n\n" \
    "http://www.burns-stat.com/pages/Tutor/R_inferno.pdf\n\n" \
    "one of the first examples was on floating point precision, where the author\n" \
    "stated that the test .1 == .3 / 3 evaluates to FALSE. i did not believe it\n" \
    "until i tried it for myself, where lo and behold, it did evaluate to false.\n" \
    "since i do understand how floats are represented in the machine, i decided\n" \
    "to write a C program to see if that is just a representation issue or if R\n" \
    "is doing some funky stuff behind my back...see for yourself what happens"

int main(int argc, char **argv) {
    // if there are no arguments
    if (argc == 1) {
	// run normally
    }
    // else if there is one argument
    else if (argc == 2) {
	// if the argument is the help flag, print HELP_STR
	if (strcmp(argv[1], HELP_FLAG) == 0) {
	    printf("%s\n", HELP_STR);
	    return 0;
	}
	// else print error and exit
	printf("%s: error: unknown flag \'%s\'. type \'%s %s\' for usage.\n",
	       PROGNAME, argv[1], PROGNAME, HELP_FLAG);
	return 1;
    }
    // else too many arguments
    else {
	printf("%s: too many arguments. type \'%s %s\' for usage.\n",
	       PROGNAME, PROGNAME, HELP_FLAG);
	return 1;
    }
    // main program logic
    // number of floating points to print
    int fpn = 20;
    // print the statement to the screen
    printf("what happens when we try to test the expression (0.1 == 0.3 / 3)?\n\n"
	   "\t0.1 is %.*lf\n\t0.3 is %.*lf\n\t3 is %d\n\n"
	   "(0.1 == 0.3 / 3) should evaluate to true (1), right?\n"
	   "(0.1 == 0.3 / 3) -> %d as 0.3 / 3 is %.*lf\n\nJOKE'S ON ME FOOL\n",
	   fpn, 0.1, fpn, 0.3, 3, (0.1 == 0.3 / 3), fpn, 0.3 / 3);
    // looks like i just got tricked
    return 0;
}
