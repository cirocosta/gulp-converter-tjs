#ifndef TRACKER__CLI_TRACKER_HH
#define TRACKER__CLI_TRACKER_HH

#include <cstring>
#include <unistd.h>
#include "Cli.hh"

namespace tracker { namespace tracker {

class CliTracker : public Cli
{
	const static std::string CDS;
public:
	CliTracker();
	~CliTracker();

public:
	void show_help() const override;
	void parse(const int& argc, char **argv) override;
};

static const std::string CLASSIFIER = "classifier";
static const std::string FILENAMES = "filenames";

static const char *HELP_TEXT =
	"Usage: ./tracker -f FILENAMES -c CLASSIFIER\n"
	"\n"
	"Options:\n"
	"  -c\thaarcascade classifier filename\n"
	"  -f\tone (or several) input filename(s)\n"
	"	 -h\tshow this message\n"
	"\n"
	"Examples:\n"
	"\t$ ./tracking -f myface.png -c faces.xml\n"
	"\n";

static const char *ARGS_ERR_TEXT =
	"Error:\t"
	"At least one classifier and a filename must be specified.\n"
	"";


}}; // !ns tracker tracker

#endif // !TRACKER__CLI_HH
