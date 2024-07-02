/*!
@file
In dit bestand staat de implementatie van de configuratie van een standaard grafiek venster
 op het STM32F412 Discovery board die in RGT/DSB practica  kan worden gebruikt.

@version $Rev: 3649 $
@author $Author: ewout $

@copyright Copyright 2017-2018 Hogeschool van Arnhem en Nijmegen, ir drs E.J Boks

$URL: http://svn.hanese.nl/docenten/svn/ewout/vakken/algemeen/software/STM32/STM32Basis/HAL/gemeenschappelijk/Libraries/Middlewares/ST/STemWin/BSP/STM32F412G-Discovery/standaardGrafiekVenster.cpp $
$Id: standaardGrafiekVenster.cpp 3649 2019-10-03 16:34:04Z ewout $ */

/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.32                          *
*        Compiled Oct  8 2015, 11:59:02                              *
*        (c) 2015 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
#include "standaardGrafiekVenster.h"
//#include <signaalDemo.h>

/* voor het doorgeven van envents aan de GUI taak */
// USER END

#include "DIALOG.h"

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] =
		{
				{ WINDOW_CreateIndirect, "Window", ID_WINDOW_0,
						0, 0, 240, 320, 0, 0x0, 0 },
				{ GRAPH_CreateIndirect, "Graph", ID_GRAPH_0,
						2, 60, 240, 320, 0, 0x0, 0 }
		};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg)
{
	switch (pMsg->MsgId)
	{
		case WM_INIT_DIALOG:
			/* niets */
			break;
		case WM_NOTIFY_PARENT:

		default:
			WM_DefaultProc(pMsg);
			break;
	}
}

WM_HWIN StandaardGrafiekVenster::maakVenster()
{
	WM_HWIN hWin;

	hWin = GUI_CreateDialogBox(_aDialogCreate,
	                           GUI_COUNTOF(_aDialogCreate),
	                           _cbDialog, WM_HBKWIN, 0, 0);
	return hWin;
}

void StandaardGrafiekVenster::sluitVenster(const WM_HWIN hWin)
{
	GUI_EndDialog(hWin,0);
}

