#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  int /*<<< orphan*/  snapname ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  errbuf ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
#define  EEXIST 132 
#define  EINVAL 131 
#define  ENOSPC 130 
#define  ENOTSUP 129 
#define  EXDEV 128 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  ZFS_TYPE_SNAPSHOT ; 
 char* dgettext (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  fnvlist_add_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  g_zfs ; 
 int getopt (int,char**,char*) ; 
 char* gettext (char*) ; 
 int lzc_bookmark (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ optind ; 
 int optopt ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_do_bookmark(int argc, char **argv)
{
	char snapname[ZFS_MAX_DATASET_NAME_LEN];
	zfs_handle_t *zhp;
	nvlist_t *nvl;
	int ret = 0;
	int c;

	/* check options */
	while ((c = getopt(argc, argv, "")) != -1) {
		switch (c) {
		case '?':
			(void) fprintf(stderr,
			    gettext("invalid option '%c'\n"), optopt);
			goto usage;
		}
	}

	argc -= optind;
	argv += optind;

	/* check number of arguments */
	if (argc < 1) {
		(void) fprintf(stderr, gettext("missing snapshot argument\n"));
		goto usage;
	}
	if (argc < 2) {
		(void) fprintf(stderr, gettext("missing bookmark argument\n"));
		goto usage;
	}

	if (strchr(argv[1], '#') == NULL) {
		(void) fprintf(stderr,
		    gettext("invalid bookmark name '%s' -- "
		    "must contain a '#'\n"), argv[1]);
		goto usage;
	}

	if (argv[0][0] == '@') {
		/*
		 * Snapshot name begins with @.
		 * Default to same fs as bookmark.
		 */
		(void) strncpy(snapname, argv[1], sizeof (snapname));
		*strchr(snapname, '#') = '\0';
		(void) strlcat(snapname, argv[0], sizeof (snapname));
	} else {
		(void) strncpy(snapname, argv[0], sizeof (snapname));
	}
	zhp = zfs_open(g_zfs, snapname, ZFS_TYPE_SNAPSHOT);
	if (zhp == NULL)
		goto usage;
	zfs_close(zhp);


	nvl = fnvlist_alloc();
	fnvlist_add_string(nvl, argv[1], snapname);
	ret = lzc_bookmark(nvl, NULL);
	fnvlist_free(nvl);

	if (ret != 0) {
		const char *err_msg;
		char errbuf[1024];

		(void) snprintf(errbuf, sizeof (errbuf),
		    dgettext(TEXT_DOMAIN,
		    "cannot create bookmark '%s'"), argv[1]);

		switch (ret) {
		case EXDEV:
			err_msg = "bookmark is in a different pool";
			break;
		case EEXIST:
			err_msg = "bookmark exists";
			break;
		case EINVAL:
			err_msg = "invalid argument";
			break;
		case ENOTSUP:
			err_msg = "bookmark feature not enabled";
			break;
		case ENOSPC:
			err_msg = "out of space";
			break;
		default:
			err_msg = "unknown error";
			break;
		}
		(void) fprintf(stderr, "%s: %s\n", errbuf,
		    dgettext(TEXT_DOMAIN, err_msg));
	}

	return (ret != 0);

usage:
	usage(B_FALSE);
	return (-1);
}