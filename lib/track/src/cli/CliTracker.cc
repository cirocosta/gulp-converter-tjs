#include "CliTracker.hh"

namespace tracker { namespace tracker {

CliTracker::CliTracker()
{
	args = CliArgs {
		{CLASSIFIER, std::vector<std::string> ()},
		{FILENAMES,		std::vector<std::string> ()},
		{SHOW, std::vector<std::string> ()}
	};
}

CliTracker::~CliTracker()
{}

void CliTracker::show_help() const
{
	write(STDOUT, HELP_TEXT, strlen(HELP_TEXT));
}

void CliTracker::parse (const int& argc, char **argv)
{
	int c;
  opterr = 0;

  while ((c = getopt (argc, argv, "c:f:sh")) != -1) {
    switch (c) {
      case 's':
				args[SHOW].push_back("yes");
        break;

      case 'c':
				args[CLASSIFIER].push_back(argv[--optind]);
        break;

      case 'f':
				for(optind--; optind < argc && *argv[optind] != '-'; optind++)
					args[FILENAMES].push_back(argv[optind]);
        break;

			case 'h':
				show_help();
				exit(EXIT_SUCCESS);

      case '?':
				show_help();
        if (isprint (optopt))
          fprintf(stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);

        exit(EXIT_FAILURE);

      default:
				fprintf(stderr, "Unknown case for `\\x%x'.\n", optopt);
				exit(EXIT_FAILURE);
      }
	}

	if (!(args[CLASSIFIER].size() && args[FILENAMES].size())) {
		show_help();
		write(STDERR, ARGS_ERR_TEXT, strlen(ARGS_ERR_TEXT));
		exit(EXIT_FAILURE);
	}
}

}}; // !ns tracker tracker
