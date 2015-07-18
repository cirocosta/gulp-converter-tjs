#ifndef TRACKER__CLI_HH
#define TRACKER__CLI_HH

#include <map>
#include <string>
#include <vector>

#define STDOUT 1
#define STDERR 2

namespace tracker {

typedef std::map<std::string, std::vector<std::string> > CliArgs;

class Cli
{
protected:
	Cli() {}
	virtual ~Cli() {}
public:
	CliArgs args;
	virtual void show_help() const = 0;
	virtual void parse(const int& argc, char **argv) = 0;
};

} // !ns

#endif
