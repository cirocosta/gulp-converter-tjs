#include "Cli.hh"

namespace tracker {

void show_help(void)
{
	write(STDOUT, HELP_TEXT, strlen(HELP_TEXT));
}

CliArgs parse (const int& argc, char **argv)
{
	CliArgs cli_args {
		{CLASSIFIERS, std::vector<std::string> ()},
		{FILENAMES,		std::vector<std::string> ()},
		{DIRECTORY,		std::vector<std::string> ()}
	};

	int c;
  opterr = 0;

  while ((c = getopt (argc, argv, "c:f:d:h")) != -1) {
    switch (c) {
      case 'c':
				for(optind--; optind < argc && *argv[optind] != '-'; optind++)
					cli_args[CLASSIFIERS].push_back(argv[optind]);

        break;
      case 'f':
				for(optind--; optind < argc && *argv[optind] != '-'; optind++)
					cli_args[FILENAMES].push_back(argv[optind]);

        break;
      case 'd':
				cli_args[DIRECTORY].push_back(optarg);
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

	if (!(cli_args[CLASSIFIERS].size() &&
			 (cli_args[FILENAMES].size() || cli_args[DIRECTORY].size()))) {
		show_help();
		write(STDERR, ARGS_ERR_TEXT, strlen(ARGS_ERR_TEXT));
		exit(EXIT_FAILURE);
	}

	return cli_args;
}

}; // !ns tracker
