#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  privstrlen; int /*<<< orphan*/  privstr; int /*<<< orphan*/  privtstrlen; int /*<<< orphan*/  privtstr; } ;
struct TYPE_6__ {TYPE_1__ privset; } ;
struct TYPE_7__ {TYPE_2__ tt; int /*<<< orphan*/  id; } ;
typedef  TYPE_3__ tokenstr_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int AU_OFLAG_XML ; 
 int /*<<< orphan*/  close_attr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_attr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  print_delim (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  print_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_tok_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
print_privset_tok(FILE *fp, tokenstr_t *tok, char *del, int oflags)
{

	print_tok_type(fp, tok->id, "privilege", oflags);
	if (oflags & AU_OFLAG_XML) {
		open_attr(fp, "type");
		print_string(fp, tok->tt.privset.privtstr,
		    tok->tt.privset.privtstrlen);
		close_attr(fp);
		open_attr(fp, "priv");
		print_string(fp, tok->tt.privset.privstr,
		    tok->tt.privset.privstrlen);
		close_attr(fp);
	} else {
		print_delim(fp, del);
		print_string(fp, tok->tt.privset.privtstr,
		    tok->tt.privset.privtstrlen);
		print_delim(fp, del);
		print_string(fp, tok->tt.privset.privstr,
			tok->tt.privset.privstrlen);
	}
}