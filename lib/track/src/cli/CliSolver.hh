#ifndef TRACKER__CLI_SOLVER_HH
#define TRACKER__CLI_SOLVER_HH

#include "Cli.hh"

#include <unistd.h>
#include <ctype.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace tracker { namespace solver {

class CliSolver : public Cli
{
public:
	CliSolver();
	~CliSolver();

public:
	void show_help() const override;
	void parse(const int& argc, char **argv) override;
};

static const std::string CLASSIFIER = "classifier";
static const std::string EXPECTED = "expected";
static const std::string FILENAME = "filename";

static const char *HELP_TEXT =
	"Usage: ./solver -e EXP_FNAME -c CLASSIFIER -f IMG_FILENAME\n"
	"\n"
	"Options:\n"
	"  -c\ta haarcascade classifier filename\n"
	"  -e\tan expected objects filename\n"
	"  -f\tan image filename\n"
	"	 -h\tshow this message\n"
	"\n"
	"Examples:\n"
	"  Prepare expected data using info-gen utility\n"
	"\t$ ./info-gen -f myface.png > expected.txt"
	"  Feed the solver with the generated file\n"
	"\t$ ./solver -e expected.txt -c faces.xml -f myface.png\n"
	"\n";

static const char *ARGS_ERR_TEXT =
	"Error:\t"
	"Not enough arguments specified.\n";

}}; // !ns tracker solver

#endif //
