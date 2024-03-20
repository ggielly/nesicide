#include <stdio.h>
#include <string.h>
#include "GUI.hpp"
#include "famitracker-core/App.hpp"
#include "../parse_arguments.hpp"
#include "../defaults.hpp"
#ifdef WINDOWS
#	include <Windows.h>
#endif

const char *default_sound=DEFAULT_SOUND;

struct arguments_t
{
	bool help;
	std::string sound;
};

static void parse_arguments(int argc, char *argv[], arguments_t &a)
{
	ParseArguments pa;
	const char *flagfields[] = {"-help"};
	pa.setFlagFields(flagfields, 1);
	pa.parse(argv, argc);

	a.help = pa.flag("-help");
	if (a.help)
		return;

	a.sound = pa.string("sound", default_sound);
}

static void print_help()
{
	printf(
"Usage: app [-sound ENGINE] [--help]\n\n"
"    -sound ENGINE\n"
"        Specify which sound engine to use. This will load a module\n"
"        in your PATH named " SOUNDSINKLIB_FORMAT ". Default is " DEFAULT_SOUND ".\n"
"        (eg. -sound jack)\n"
"    --help\n"
"        Print this message\n",

				"ENGINE"
	);
}

int main(int argc, char *argv[])
{
	gui::init(argc, argv);

	arguments_t args;

	parse_arguments(argc-1, argv+1, args);

	if (args.help)
	{
		print_help();
		return 0;
	}

	printf("Welcome to FamiTracker!\n");
	fflush(stdout);

	gui::init_2(args.sound.c_str());

	gui::spin();

	gui::destroy();

	return 0;
}
