/* $Id$ */

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>

#define DEF_INTV	5
#define DEF_CNT		5

#define ACT_LIST	1
#define ACT_ABS		2
#define ACT_DELTA	3

static int intv	= DEF_INTV;
static int cnt	= DEF_CNT;
static int showtitle = 1;

int
main(int argc, char *argv[])
{
	int act	= ACT_DELTA;
	long l;
	int c;

	while ((c = getopt(argc, argv, "ae:hlnr:w:")) != -1) {
		switch (c) {
		case 'a':
			act = ACT_ABS;
			break;
		case 'e':
			break;
		case 'h':
			usage(EXIT_SUCCESS);
			/* NOTREACHED */
		case 'l':
			act = ACT_LIST;
			break;
		case 'n':
			showtitle = 0;
			break;
		case 'r':
			break;
		case 'w':
			err(EX_UNAVAILABLE, "-w not supported");
			/* NOTREACHED */
		default:
			usage(EX_USAGE);
			/* NOTREACHED */
		}
	}
	argv += optind;
	argc -= optind;

	switch (argc) {
	case 2:
		if ((l = strtoul(argv[1], NULL, 10)) < 0 ||
		    l > INT_MAX) {
			warnx("count too long");
			usage(EX_USAGE);
		}
		cnt = (int)l;
		/* FALLTHROUGH */
	case 1:
		if ((l = strtoul(argv[0], NULL, 10)) < 0 ||
		    l > INT_MAX) {
			warnx("interval too long");
			usage(EX_USAGE);
		}
		intv = (int)l;
		break;
	case 0:
		break;
	default:
		usage(EX_USAGE);
		/* NOTREACHED */
	}

	switch (act) {
	case ACT_LIST:
		list();
		break;
	case ACT_ABS:
	case ACT_DELTA:
		show(act);
		break;
	}
	exit(EXIT_SUCCESS);
}

static __dead void
usage(int status)
{
	(void)fprintf(stderr, "usage: %s\n", __progname);
	exit(status);
}
