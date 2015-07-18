#include "CliInfoGen.hh"

namespace tracker { namespace infogen {

CliInfoGen::CliInfoGen()
{
	args = CliArgs {{FILENAME, std::vector<std::string> ()}};
}

CliInfoGen::~CliInfoGen()
{}

void CliInfoGen::show_help() const
{
	write(STDOUT, HELP_TEXT, strlen(HELP_TEXT));
}

void CliInfoGen::parse (const int& argc, char **argv)
{
	int c;
  opterr = 0;

  while ((c = getopt (argc, argv, "f:h")) != -1) {
    switch (c) {
      case 'f':
				args[FILENAME].push_back(std::string(argv[--optind]));
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

	if (!(args[FILENAME].size())) {
		show_help();
		write(STDERR, ARGS_ERR_TEXT, strlen(ARGS_ERR_TEXT));
		exit(EXIT_FAILURE);
	}
}

}}; // ! ns tracker infogen

