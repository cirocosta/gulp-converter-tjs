#ifndef TRACKER__CLI_INFOGEN_HH
#define TRACKER__CLI_INFOGEN_HH

#include <cstring>
#include <unistd.h>
#include "Cli.hh"

namespace tracker { namespace infogen {

class CliInfoGen : public Cli
{
public:
	CliInfoGen();
	~CliInfoGen();
public:
	void show_help() const override;
	void parse(const int& argc, char **argv) override;
};

static const std::string FILENAME = "filename";

static const char *HELP_TEXT =
	"Usage: ./info_gen -f FILENAME\n"
	"\n"
	"CLI Options:\n"
	"  -f\tinput filename\n"
	"	 -h\tshow this message\n"
	"\n"
	"Commands:\n"
	"\n"
	"\td\tdeletes last rectangle\n"
	"\ts\tsaves the rectangles (outputs the result)\n"
	"\n"
	"Examples:\n"
	"  Selecting the face and redirecting output to a file:\n"
	"\t$ ./info_gen -f myface.png > myface.png.expected\n"
	"\n";

static const char *ARGS_ERR_TEXT =
	"Error:\t"
	"InfoGen requires an input filename.\n"
	"";

}}; // !ns tracker infogen

#endif //
