#ifndef TRACKER__CLI_HH
#define TRACKER__CLI_HH

#include <unistd.h>
#include <ctype.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <map>
#include <string>
#include <vector>

#define STDOUT 1
#define STDERR 2

namespace tracker {

static const std::string CLASSIFIERS = "classifiers";
static const std::string FILENAMES = "filenames";
static const std::string DIRECTORY = "directory";

typedef std::map<std::string, std::vector<std::string> > CliArgs;

static const char *TRACKER_HELP_TEXT =
	"Usage: ./tracker -f FILENAMES -c CLASSIFIERS [-d DIRECTORY]\n"
	"\n"
	"Options:\n"
	"  -c\thaarcascade classifier filename\n"
	"  -f\tone (or several) input filename(s)\n"
	"  -d\tdirectory containing classifiers and images\n"
	"\n"
	"Examples:\n"
	"\t$ ./tracking -f myface.png -c faces.xml\n"
	"\t$ ./tracking -d photos/summer/ -c smiles.xml faces.xml\n"
	"\n";

static const char *ARGS_ERR_TEXT =
	"Error:\t"
	"At least one classifier and one directory or filename specified.\n"
	"";

void show_help(void);
CliArgs parse (const int& argc, char **argv);

}; // !ns tracker

#endif // !TRACKER__CLI_HH
