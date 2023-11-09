#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_7__ {int /*<<< orphan*/  atr; } ;
struct TYPE_6__ {int /*<<< orphan*/  atr; } ;
struct TYPE_5__ {int /*<<< orphan*/  atr; } ;
struct TYPE_8__ {TYPE_3__ inputbox; TYPE_2__ border; TYPE_1__ dialog; } ;

/* Variables and functions */
 char ACS_HLINE ; 
 int /*<<< orphan*/  ACS_LTEE ; 
 char ACS_RTEE ; 
 int ERRDISPLAYTOOSMALL ; 
 int INPUTBOX_HEIGTH_MIN ; 
 int INPUTBOX_WIDTH_MIN ; 
#define  KEY_BACKSPACE 135 
#define  KEY_DOWN 134 
#define  KEY_ESC 133 
#define  KEY_LEFT 132 
#define  KEY_RESIZE 131 
#define  KEY_RIGHT 130 
#define  KEY_UP 129 
 int MAX_LEN ; 
#define  TAB 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  delwin (int /*<<< orphan*/ *) ; 
 char* dialog_input_result ; 
 TYPE_4__ dlg ; 
 int /*<<< orphan*/  draw_box (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  draw_shadow (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  flash () ; 
 int getmaxx (int /*<<< orphan*/ ) ; 
 int getmaxy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getyx (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  isprint (int) ; 
 int /*<<< orphan*/  keypad (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvwaddch (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * newwin (int,int,int,int) ; 
 int on_key_esc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_key_resize () ; 
 int /*<<< orphan*/  print_autowrap (int /*<<< orphan*/ *,char const*,int,int,int) ; 
 int /*<<< orphan*/  print_buttons (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  print_title (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  stdscr ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  waddch (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  waddstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  wattrset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int wgetch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ *) ; 

int dialog_inputbox(const char *title, const char *prompt, int height, int width,
		    const char *init)
{
	int i, x, y, box_y, box_x, box_width;
	int input_x = 0, key = 0, button = -1;
	int show_x, len, pos;
	char *instr = dialog_input_result;
	WINDOW *dialog;

	if (!init)
		instr[0] = '\0';
	else
		strcpy(instr, init);

do_resize:
	if (getmaxy(stdscr) <= (height - INPUTBOX_HEIGTH_MIN))
		return -ERRDISPLAYTOOSMALL;
	if (getmaxx(stdscr) <= (width - INPUTBOX_WIDTH_MIN))
		return -ERRDISPLAYTOOSMALL;

	/* center dialog box on screen */
	x = (getmaxx(stdscr) - width) / 2;
	y = (getmaxy(stdscr) - height) / 2;

	draw_shadow(stdscr, y, x, height, width);

	dialog = newwin(height, width, y, x);
	keypad(dialog, TRUE);

	draw_box(dialog, 0, 0, height, width,
		 dlg.dialog.atr, dlg.border.atr);
	wattrset(dialog, dlg.border.atr);
	mvwaddch(dialog, height - 3, 0, ACS_LTEE);
	for (i = 0; i < width - 2; i++)
		waddch(dialog, ACS_HLINE);
	wattrset(dialog, dlg.dialog.atr);
	waddch(dialog, ACS_RTEE);

	print_title(dialog, title, width);

	wattrset(dialog, dlg.dialog.atr);
	print_autowrap(dialog, prompt, width - 2, 1, 3);

	/* Draw the input field box */
	box_width = width - 6;
	getyx(dialog, y, x);
	box_y = y + 2;
	box_x = (width - box_width) / 2;
	draw_box(dialog, y + 1, box_x - 1, 3, box_width + 2,
		 dlg.dialog.atr, dlg.border.atr);

	print_buttons(dialog, height, width, 0);

	/* Set up the initial value */
	wmove(dialog, box_y, box_x);
	wattrset(dialog, dlg.inputbox.atr);

	len = strlen(instr);
	pos = len;

	if (len >= box_width) {
		show_x = len - box_width + 1;
		input_x = box_width - 1;
		for (i = 0; i < box_width - 1; i++)
			waddch(dialog, instr[show_x + i]);
	} else {
		show_x = 0;
		input_x = len;
		waddstr(dialog, instr);
	}

	wmove(dialog, box_y, box_x + input_x);

	wrefresh(dialog);

	while (key != KEY_ESC) {
		key = wgetch(dialog);

		if (button == -1) {	/* Input box selected */
			switch (key) {
			case TAB:
			case KEY_UP:
			case KEY_DOWN:
				break;
			case KEY_BACKSPACE:
			case 127:
				if (pos) {
					wattrset(dialog, dlg.inputbox.atr);
					if (input_x == 0) {
						show_x--;
					} else
						input_x--;

					if (pos < len) {
						for (i = pos - 1; i < len; i++) {
							instr[i] = instr[i+1];
						}
					}

					pos--;
					len--;
					instr[len] = '\0';
					wmove(dialog, box_y, box_x);
					for (i = 0; i < box_width; i++) {
						if (!instr[show_x + i]) {
							waddch(dialog, ' ');
							break;
						}
						waddch(dialog, instr[show_x + i]);
					}
					wmove(dialog, box_y, input_x + box_x);
					wrefresh(dialog);
				}
				continue;
			case KEY_LEFT:
				if (pos > 0) {
					if (input_x > 0) {
						wmove(dialog, box_y, --input_x + box_x);
					} else if (input_x == 0) {
						show_x--;
						wmove(dialog, box_y, box_x);
						for (i = 0; i < box_width; i++) {
							if (!instr[show_x + i]) {
								waddch(dialog, ' ');
								break;
							}
							waddch(dialog, instr[show_x + i]);
						}
						wmove(dialog, box_y, box_x);
					}
					pos--;
				}
				continue;
			case KEY_RIGHT:
				if (pos < len) {
					if (input_x < box_width - 1) {
						wmove(dialog, box_y, ++input_x + box_x);
					} else if (input_x == box_width - 1) {
						show_x++;
						wmove(dialog, box_y, box_x);
						for (i = 0; i < box_width; i++) {
							if (!instr[show_x + i]) {
								waddch(dialog, ' ');
								break;
							}
							waddch(dialog, instr[show_x + i]);
						}
						wmove(dialog, box_y, input_x + box_x);
					}
					pos++;
				}
				continue;
			default:
				if (key < 0x100 && isprint(key)) {
					if (len < MAX_LEN) {
						wattrset(dialog, dlg.inputbox.atr);
						if (pos < len) {
							for (i = len; i > pos; i--)
								instr[i] = instr[i-1];
							instr[pos] = key;
						} else {
							instr[len] = key;
						}
						pos++;
						len++;
						instr[len] = '\0';

						if (input_x == box_width - 1) {
							show_x++;
						} else {
							input_x++;
						}

						wmove(dialog, box_y, box_x);
						for (i = 0; i < box_width; i++) {
							if (!instr[show_x + i]) {
								waddch(dialog, ' ');
								break;
							}
							waddch(dialog, instr[show_x + i]);
						}
						wmove(dialog, box_y, input_x + box_x);
						wrefresh(dialog);
					} else
						flash();	/* Alarm user about overflow */
					continue;
				}
			}
		}
		switch (key) {
		case 'O':
		case 'o':
			delwin(dialog);
			return 0;
		case 'H':
		case 'h':
			delwin(dialog);
			return 1;
		case KEY_UP:
		case KEY_LEFT:
			switch (button) {
			case -1:
				button = 1;	/* Indicates "Help" button is selected */
				print_buttons(dialog, height, width, 1);
				break;
			case 0:
				button = -1;	/* Indicates input box is selected */
				print_buttons(dialog, height, width, 0);
				wmove(dialog, box_y, box_x + input_x);
				wrefresh(dialog);
				break;
			case 1:
				button = 0;	/* Indicates "OK" button is selected */
				print_buttons(dialog, height, width, 0);
				break;
			}
			break;
		case TAB:
		case KEY_DOWN:
		case KEY_RIGHT:
			switch (button) {
			case -1:
				button = 0;	/* Indicates "OK" button is selected */
				print_buttons(dialog, height, width, 0);
				break;
			case 0:
				button = 1;	/* Indicates "Help" button is selected */
				print_buttons(dialog, height, width, 1);
				break;
			case 1:
				button = -1;	/* Indicates input box is selected */
				print_buttons(dialog, height, width, 0);
				wmove(dialog, box_y, box_x + input_x);
				wrefresh(dialog);
				break;
			}
			break;
		case ' ':
		case '\n':
			delwin(dialog);
			return (button == -1 ? 0 : button);
		case 'X':
		case 'x':
			key = KEY_ESC;
			break;
		case KEY_ESC:
			key = on_key_esc(dialog);
			break;
		case KEY_RESIZE:
			delwin(dialog);
			on_key_resize();
			goto do_resize;
		}
	}

	delwin(dialog);
	return KEY_ESC;		/* ESC pressed */
}