#include <iostream>
#include <cstring>
// program name
#define PROGNAME "hello"

using namespace std;

int main(int argc, char **argv) {
    // normal runtime
    if (argc == 1) {
	cout << "Hello World!\n";
    }
    // else if there are two arguments and the second is "--help"
    else if (argc == 2 && strcmp(*(argv + 1), "--help") == 0) {
	cout << "Usage: " << PROGNAME << "[ --help ]\nprints hello world\n";
    }
    // else if there are too many arguments
    else {
	cerr << PROGNAME << ": too many arguments. type \'" << PROGNAME << " --help \' " \
	    "for usage\n";
	return 1;
    }
    return 0;
}
