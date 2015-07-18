#include "CliSolver.hh"

namespace tracker { namespace solver {

CliSolver::CliSolver()
{
	args = CliArgs {
		{CLASSIFIER,	std::vector<std::string> ()},
		{FILENAME,		std::vector<std::string> ()},
		{EXPECTED,		std::vector<std::string> ()}
	};
}

CliSolver::~CliSolver()
{}

void CliSolver::show_help() const
{
	write(STDOUT, HELP_TEXT, strlen(HELP_TEXT));
}

void CliSolver::parse (const int& argc, char **argv)
{
	int c;
  opterr = 0;

  while ((c = getopt (argc, argv, "c:f:e:h")) != -1) {
    switch (c) {
      case 'f':
				args[FILENAME].push_back(argv[--optind]);
        break;

      case 'e':
				args[EXPECTED].push_back(argv[--optind]);
        break;

      case 'c':
				args[CLASSIFIER].push_back(argv[--optind]);
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

	if (!(args[FILENAME].size() && args[CLASSIFIER].size() &&
				args[EXPECTED].size())) {
		show_help();
		write(STDERR, ARGS_ERR_TEXT, strlen(ARGS_ERR_TEXT));
		exit(EXIT_FAILURE);
	}
}

}}; // ! ns tracker solver

