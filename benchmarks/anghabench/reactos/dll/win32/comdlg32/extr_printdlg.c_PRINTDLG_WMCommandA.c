#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
typedef  void* WORD ;
typedef  int UINT ;
struct TYPE_11__ {void* dmOrientation; void* dmDefaultSource; void* dmPaperSize; } ;
struct TYPE_12__ {TYPE_1__ s1; } ;
struct TYPE_15__ {TYPE_2__ u1; scalar_t__ dmFormName; } ;
struct TYPE_14__ {int Flags; void* nToPage; void* nFromPage; int /*<<< orphan*/  hwndOwner; } ;
struct TYPE_13__ {int /*<<< orphan*/  hLandscapeIcon; int /*<<< orphan*/  hPortraitIcon; TYPE_5__* lpDevMode; int /*<<< orphan*/  hNoCollateIcon; int /*<<< orphan*/  hCollateIcon; int /*<<< orphan*/  HelpMessageID; TYPE_4__* lpPrintDlg; } ;
typedef  TYPE_3__ PRINT_PTRA ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_4__* LPPRINTDLGA ;
typedef  TYPE_5__* LPDEVMODEA ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  BST_CHECKED ; 
 int /*<<< orphan*/  CBN_SELCHANGE ; 
 int CB_ERR ; 
 int /*<<< orphan*/  CB_GETCURSEL ; 
 int /*<<< orphan*/  CB_GETITEMDATA ; 
 int /*<<< orphan*/  CB_GETLBTEXT ; 
 int /*<<< orphan*/  CB_GETLBTEXTLEN ; 
 int CCHFORMNAME ; 
 int /*<<< orphan*/  CheckRadioButton (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClosePrinter (int /*<<< orphan*/ ) ; 
 void* DMORIENT_LANDSCAPE ; 
 void* DMORIENT_PORTRAIT ; 
 int DM_IN_BUFFER ; 
 int DM_IN_PROMPT ; 
 int DM_OUT_BUFFER ; 
 int /*<<< orphan*/  DocumentPropertiesA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_5__*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  EN_CHANGE ; 
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EndDialog (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int const) ; 
 void* GetDlgItemInt (int /*<<< orphan*/ ,int const,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItemTextA (int /*<<< orphan*/ ,int const,char*,int) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HIWORD (int /*<<< orphan*/ ) ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
#define  IDCANCEL 141 
#define  IDOK 140 
 int IMAGE_ICON ; 
 int /*<<< orphan*/  IsDlgButtonChecked (int /*<<< orphan*/ ,int const) ; 
 int LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OpenPrinterA (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int PD_PRINTSETUP ; 
 int /*<<< orphan*/  PRINTDLG_ChangePrinterA (int /*<<< orphan*/ ,char*,TYPE_3__*) ; 
 int /*<<< orphan*/  PRINTDLG_UpdatePrintDlgA (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  STM_SETIMAGE ; 
 void* SendDlgItemMessageA (int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int SendDlgItemMessageW (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRUE ; 
#define  chx2 139 
#define  cmb1 138 
#define  cmb2 137 
#define  cmb3 136 
#define  cmb4 135 
#define  edt1 134 
#define  edt2 133 
#define  edt3 132 
 int const ico1 ; 
 int const ico3 ; 
#define  psh2 131 
#define  pshHelp 130 
#define  rad1 129 
#define  rad2 128 
 int /*<<< orphan*/  rad3 ; 
 int const stc10 ; 

__attribute__((used)) static LRESULT PRINTDLG_WMCommandA(HWND hDlg, WPARAM wParam,
                                   PRINT_PTRA* PrintStructures)
{
    LPPRINTDLGA lppd = PrintStructures->lpPrintDlg;
    UINT PrinterComboID = (lppd->Flags & PD_PRINTSETUP) ? cmb1 : cmb4;
    LPDEVMODEA lpdm = PrintStructures->lpDevMode;

    switch (LOWORD(wParam))  {
    case IDOK:
        TRACE(" OK button was hit\n");
        if (!PRINTDLG_UpdatePrintDlgA(hDlg, PrintStructures)) {
	    FIXME("Update printdlg was not successful!\n");
	    return(FALSE);
	}
	EndDialog(hDlg, TRUE);
	return(TRUE);

    case IDCANCEL:
        TRACE(" CANCEL button was hit\n");
        EndDialog(hDlg, FALSE);
	return(FALSE);

     case pshHelp:
        TRACE(" HELP button was hit\n");
        SendMessageA(lppd->hwndOwner, PrintStructures->HelpMessageID,
        			(WPARAM) hDlg, (LPARAM) lppd);
        break;

     case chx2:                         /* collate pages checkbox */
        if (IsDlgButtonChecked(hDlg, chx2) == BST_CHECKED)
            SendDlgItemMessageA(hDlg, ico3, STM_SETIMAGE, IMAGE_ICON,
                                    (LPARAM)PrintStructures->hCollateIcon);
        else
            SendDlgItemMessageA(hDlg, ico3, STM_SETIMAGE, IMAGE_ICON,
                                    (LPARAM)PrintStructures->hNoCollateIcon);
        break;
     case edt1:                         /* from page nr editbox */
     case edt2:                         /* to page nr editbox */
        if (HIWORD(wParam)==EN_CHANGE) {
	    WORD nToPage;
	    WORD nFromPage;
	    nFromPage = GetDlgItemInt(hDlg, edt1, NULL, FALSE);
	    nToPage   = GetDlgItemInt(hDlg, edt2, NULL, FALSE);
            if (nFromPage != lppd->nFromPage || nToPage != lppd->nToPage)
	        CheckRadioButton(hDlg, rad1, rad3, rad3);
	}
        break;

    case edt3:
        if(HIWORD(wParam) == EN_CHANGE) {
	    INT copies = GetDlgItemInt(hDlg, edt3, NULL, FALSE);
	    if(copies <= 1)
	        EnableWindow(GetDlgItem(hDlg, chx2), FALSE);
	    else
	        EnableWindow(GetDlgItem(hDlg, chx2), TRUE);
	}
	break;

     case psh2:                       /* Properties button */
       {
         HANDLE hPrinter;
         char   PrinterName[256];

         GetDlgItemTextA(hDlg, PrinterComboID, PrinterName, 255);
         if (!OpenPrinterA(PrinterName, &hPrinter, NULL)) {
	     FIXME(" Call to OpenPrinter did not succeed!\n");
	     break;
	 }
	 DocumentPropertiesA(hDlg, hPrinter, PrinterName,
			     PrintStructures->lpDevMode,
			     PrintStructures->lpDevMode,
			     DM_IN_BUFFER | DM_OUT_BUFFER | DM_IN_PROMPT);
	 ClosePrinter(hPrinter);
         break;
       }

    case rad1: /* Paperorientation */
        if (lppd->Flags & PD_PRINTSETUP)
        {
              lpdm->u1.s1.dmOrientation = DMORIENT_PORTRAIT;
              SendDlgItemMessageA(hDlg, ico1, STM_SETIMAGE, IMAGE_ICON,
                          (LPARAM)(PrintStructures->hPortraitIcon));
        }
        break;

    case rad2: /* Paperorientation */
        if (lppd->Flags & PD_PRINTSETUP)
        {
              lpdm->u1.s1.dmOrientation = DMORIENT_LANDSCAPE;
              SendDlgItemMessageA(hDlg, ico1, STM_SETIMAGE, IMAGE_ICON,
                          (LPARAM)(PrintStructures->hLandscapeIcon));
        }
        break;

    case cmb1: /* Printer Combobox in PRINT SETUP, quality combobox in PRINT16 */
	 if (PrinterComboID != LOWORD(wParam)) {
	     break;
	 }
	 /* FALLTHROUGH */
    case cmb4:                         /* Printer combobox */
         if (HIWORD(wParam)==CBN_SELCHANGE) {
	     char   *PrinterName;
	     INT index = SendDlgItemMessageW(hDlg, LOWORD(wParam), CB_GETCURSEL, 0, 0);
	     INT length = SendDlgItemMessageW(hDlg, LOWORD(wParam), CB_GETLBTEXTLEN, index, 0);
	     PrinterName = HeapAlloc(GetProcessHeap(),0,length+1);
	     SendDlgItemMessageA(hDlg, LOWORD(wParam), CB_GETLBTEXT, index, (LPARAM)PrinterName);
	     PRINTDLG_ChangePrinterA(hDlg, PrinterName, PrintStructures);
	     HeapFree(GetProcessHeap(),0,PrinterName);
	 }
	 break;

    case cmb2: /* Papersize */
      {
	  DWORD Sel = SendDlgItemMessageA(hDlg, cmb2, CB_GETCURSEL, 0, 0);
	  if(Sel != CB_ERR) {
	      lpdm->u1.s1.dmPaperSize = SendDlgItemMessageA(hDlg, cmb2,
							    CB_GETITEMDATA,
							    Sel, 0);
	      GetDlgItemTextA(hDlg, cmb2, (char *)lpdm->dmFormName, CCHFORMNAME);
	  }
      }
      break;

    case cmb3: /* Bin */
      {
	  DWORD Sel = SendDlgItemMessageA(hDlg, cmb3, CB_GETCURSEL, 0, 0);
	  if(Sel != CB_ERR)
	      lpdm->u1.s1.dmDefaultSource = SendDlgItemMessageA(hDlg, cmb3,
							  CB_GETITEMDATA, Sel,
							  0);
      }
      break;
    }
    if(lppd->Flags & PD_PRINTSETUP) {
        switch (LOWORD(wParam)) {
	case rad1:                         /* orientation */
	case rad2:
	    if (IsDlgButtonChecked(hDlg, rad1) == BST_CHECKED) {
	        if(lpdm->u1.s1.dmOrientation != DMORIENT_PORTRAIT) {
		    lpdm->u1.s1.dmOrientation = DMORIENT_PORTRAIT;
                    SendDlgItemMessageA(hDlg, stc10, STM_SETIMAGE, IMAGE_ICON,
					(LPARAM)PrintStructures->hPortraitIcon);
                    SendDlgItemMessageA(hDlg, ico1, STM_SETIMAGE, IMAGE_ICON,
					(LPARAM)PrintStructures->hPortraitIcon);
		}
	    } else {
	        if(lpdm->u1.s1.dmOrientation != DMORIENT_LANDSCAPE) {
	            lpdm->u1.s1.dmOrientation = DMORIENT_LANDSCAPE;
                    SendDlgItemMessageA(hDlg, stc10, STM_SETIMAGE, IMAGE_ICON,
					(LPARAM)PrintStructures->hLandscapeIcon);
                    SendDlgItemMessageA(hDlg, ico1, STM_SETIMAGE, IMAGE_ICON,
					(LPARAM)PrintStructures->hLandscapeIcon);
		}
	    }
	    break;
	}
    }
    return FALSE;
}