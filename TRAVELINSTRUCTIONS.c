//
//  This program code is a part of The Master Scheduler (TMS)
//  and is Copyright (C) 1991-2004 Schedule Masters, Inc.
//  All rights reserved.
//
#include "TMSHeader.h"
#include "cistms.h"

#define TABSET 5

int sort_instructions(const void *a, const void *b)
{
  TIDataDef *pa, *pb;

  pa = (TIDataDef *)a;
  pb = (TIDataDef *)b;
  
  return(pa->fromTime < pb->fromTime ? -1 : pa->fromTime > pb->fromTime ? 1 : 0);
}

BOOL CALLBACK TRAVELINSTRUCTIONSMsgProc(HWND hWndDlg, UINT Message, WPARAM wParam, LPARAM lParam)
{
  static HANDLE hCtlLIST;
  static HANDLE hCtlTITLE;
  static int    tabPos[TABSET] = { 3, 17, 30, 35, 39};
  COSTDef *pCOST;
  long    *pParam;
  WORD DlgWidthUnits;
  char routeNumber[ROUTES_NUMBER_LENGTH + 1];
  char routeName[ROUTES_NAME_LENGTH + 1];
  char directionAbbr[DIRECTIONS_ABBRNAME_LENGTH + 1];
  char fromNode[NODES_ABBRNAME_LENGTH + 1];
  char toNode[NODES_ABBRNAME_LENGTH + 1];
  char travelDirections[1024];
  char *ptr;
  char lineSep[3] = {13, 10, 0};
  long fNode;
  long tNode;
  long travelTime;
  long dwellTime;
  long startTime;
  long endTime;
  long equivalentTravelTime;
  BOOL bDidOne;
  int  adjustedTabPos[TABSET];
  int  nI;
  int  nJ;

  switch(Message)
  {
//
//  WM_INITDIALOG - Initialize the dialog
//
    case WM_INITDIALOG:
//
//  Set up the handles to the the controls
//
      hCtlTITLE = GetDlgItem(hWndDlg, TRAVELINSTRUCTIONS_TITLE);
      hCtlLIST = GetDlgItem(hWndDlg, TRAVELINSTRUCTIONS_LIST);
//
//  Dissect the parameter
//
      if(bUseCISPlan)
      {
        pCOST = (COSTDef *)lParam;
        if(pCOST == NULL)
        {
          SendMessage(hWndDlg, WM_COMMAND, MAKEWPARAM(IDCANCEL, 0), (LPARAM)0);
          break;
        }
      }
      else
      {
        pParam = (long *)lParam;
        if(pParam == NULL)
        {
          SendMessage(hWndDlg, WM_COMMAND, MAKEWPARAM(IDCANCEL, 0), (LPARAM)0);
          break;
        }
        if(pParam == 0)
          SendMessage(hWndDlg, WM_SETTEXT, (WPARAM)0, (LONG)(LPSTR)"Travel Instructions");
        else
        {
          SendMessage(hWndDlg, WM_GETTEXT, (WPARAM)sizeof(szFormatString),
                (LONG)(LPSTR)szFormatString);
          sprintf(tempString, szFormatString, *pParam);
          SendMessage(hWndDlg, WM_SETTEXT, (WPARAM)0, (LONG)(LPSTR)tempString);
        }
      }
//
//  Set up the tab stops
//
      DlgWidthUnits = LOWORD(GetDialogBaseUnits()) / 4;
      for(nI = 0; nI < TABSET; nI++)
      {
        adjustedTabPos[nI] = (DlgWidthUnits * tabPos[nI] * 2);
      }
      SendMessage(hCtlTITLE, LB_SETTABSTOPS, (WPARAM)TABSET, (LPARAM)adjustedTabPos);
      SendMessage(hCtlLIST, LB_SETTABSTOPS, (WPARAM)TABSET, (LPARAM)adjustedTabPos);
//
//  Directions for CISplan
//
      if(bUseCISPlan)
      {
        SendMessage(hWndDlg, WM_SETTEXT, (WPARAM)0, (LONG)(LPSTR)"Travel Instructions");
        SendMessage(hCtlTITLE, WM_SETTEXT, (WPARAM)0,
              (LONG)(LPSTR)"...as generated by the TMS Trip Planner");
        bDidOne = FALSE;
        for(nI = 0; nI < MAXPIECES; nI++)
        {
          fNode = pCOST->TRAVEL[nI].startNODESrecordID;
          tNode = pCOST->TRAVEL[nI].startAPointNODESrecordID;
//          if(fNode != NO_RECORD && tNode != NO_RECORD && fNode != tNode)
          if(fNode != NO_RECORD && tNode != NO_RECORD && 
                !NodesEquivalent(fNode, tNode, &equivalentTravelTime))
          {
            strcpy(travelDirections, CISplanReliefConnect(&startTime, &endTime, &dwellTime,
                  TRUE, fNode, tNode, pCOST->TRAVEL[nI].startAPointTime, FALSE, m_ServiceRecordID));
            if(startTime == -25 * 60 * 60)
              travelTime = NO_TIME;
            else
              travelTime = (endTime - startTime) + dwellTime;
            sprintf(tempString, "Piece %d: Start", nI + 1);
            SendMessage(hCtlLIST, LB_ADDSTRING, (WPARAM)0, (LONG)(LPSTR)tempString);
            ptr = strtok(travelDirections, lineSep);
            while(ptr != 0)
            {
              sprintf(tempString, "\t%s", ptr);
              SendMessage(hCtlLIST, LB_ADDSTRING, (WPARAM)0, (LONG)(LPSTR)tempString);
              ptr = strtok(NULL, lineSep);
            }
            bDidOne = TRUE;  
          }
          fNode = pCOST->TRAVEL[nI].endBPointNODESrecordID;
          tNode = pCOST->TRAVEL[nI].endNODESrecordID;
//          if(fNode != NO_RECORD && tNode != NO_RECORD)
          if(fNode != NO_RECORD && tNode != NO_RECORD &&
                !NodesEquivalent(fNode, tNode, &equivalentTravelTime))
          {
            strcpy(travelDirections, CISplanReliefConnect(&startTime, &endTime, &dwellTime,
                  TRUE, fNode, tNode, pCOST->TRAVEL[nI].endBPointTime, TRUE, m_ServiceRecordID));
            if(startTime == -25 * 60 * 60)
              travelTime = NO_TIME;
            else
              travelTime = (endTime - startTime) + dwellTime;
            sprintf(tempString, "Piece %d: End", nI + 1);
            SendMessage(hCtlLIST, LB_ADDSTRING, (WPARAM)0, (LONG)(LPSTR)tempString);
            ptr = strtok(travelDirections, lineSep);
            while(ptr != 0)
            {
              sprintf(tempString, "\t%s", ptr);
              SendMessage(hCtlLIST, LB_ADDSTRING, (WPARAM)0, (LONG)(LPSTR)tempString);
              ptr = strtok(NULL, lineSep);
            }
            bDidOne = TRUE;  
          }
        }
        if(!bDidOne)
          SendMessage(hCtlLIST, LB_ADDSTRING, (WPARAM)0, (LONG)(LPSTR)"No travel required");
      }
//
//  Directions for Dynamic Travels
//
      else
      {
        SendMessage(hCtlTITLE, WM_SETTEXT, (WPARAM)0,
              (LONG)(LPSTR)"...as generated by the TMS Dynamic Travels Matrix");
//
//  Display the travel instructions in fromTime order
//
        qsort((void *)TIData, numTravelInstructions, sizeof(TIDataDef), sort_instructions);
        for(nI = 0; nI < numTravelInstructions; nI++)
        {
//
//  Get the route number and name of the trip
//
          ROUTESKey0.recordID = TIData[nI].ROUTESrecordID;
          btrieve(B_GETEQUAL, TMS_ROUTES, &ROUTES, &ROUTESKey0, 0);
          strcpy(routeNumber, "");
          for(nJ = 0; nJ < ROUTES_NUMBER_LENGTH; nJ++)
          { 
            if(ROUTES.number[nJ] != ' ')
            {
              strncpy(routeNumber, &ROUTES.number[nJ], ROUTES_NUMBER_LENGTH - nJ);
              trim(routeNumber, ROUTES_NUMBER_LENGTH - nJ);
              break;
            }
          }
          strncpy(routeName, ROUTES.name, ROUTES_NAME_LENGTH);
          trim(routeName, ROUTES_NAME_LENGTH);
//
//  Get the trip direction
//
          DIRECTIONSKey0.recordID = TIData[nI].DIRECTIONSrecordID;
          btrieve(B_GETEQUAL, TMS_DIRECTIONS, &DIRECTIONS, &DIRECTIONSKey0, 0);
          strncpy(directionAbbr, DIRECTIONS.abbrName, DIRECTIONS_ABBRNAME_LENGTH);
          trim(directionAbbr, DIRECTIONS_ABBRNAME_LENGTH);
//
//  Get the from node name
//
          NODESKey0.recordID = TIData[nI].fromNODESrecordID;
          btrieve(B_GETEQUAL, TMS_NODES, &NODES, &NODESKey0, 0);
          strncpy(fromNode, NODES.abbrName, NODES_ABBRNAME_LENGTH);
          trim(fromNode, NODES_ABBRNAME_LENGTH);
//
//  Get the to node name
//
          NODESKey0.recordID = TIData[nI].toNODESrecordID;
          btrieve(B_GETEQUAL, TMS_NODES, &NODES, &NODESKey0, 0);
          strncpy(toNode, NODES.abbrName, NODES_ABBRNAME_LENGTH);
          trim(toNode, NODES_ABBRNAME_LENGTH);
//
//  Travel number
//
          sprintf(tempString, "%d\t", nI + 1);
//
//  On location and time
//
          sprintf(szarString, "%s at %s\t", fromNode, Tchar(TIData[nI].fromTime));
          strcat(tempString, szarString);
//
//  To location and time
//
          sprintf(szarString, "%s at %s\t", toNode, Tchar(TIData[nI].toTime));
          strcat(tempString, szarString);
//
//  Travel + Dwell total
//
          strcat(tempString,
                chhmm(TIData[nI].toTime - TIData[nI].fromTime + TIData[nI].dwellTime));
          strcat(tempString, "\t");
//
//  Direction
//
          strcat(tempString, directionAbbr);
          strcat(tempString, "\t");
//
//  Route number and names
//
          strcat(tempString, routeNumber);
          strcat(tempString, " - ");
          strcat(tempString, routeName);
//
//  Display it
//
          SendMessage(hCtlLIST, LB_ADDSTRING, (WPARAM)0, (LONG)(LPSTR)tempString);
        }
      }
      break;

    case WM_CLOSE:
      SendMessage(hWndDlg, WM_COMMAND, MAKEWPARAM(IDCANCEL, 0), (LPARAM)0);
      break;

    case WM_COMMAND:
      switch(wParam)
      {
        case IDCANCEL:  // Labelled "Close"
          EndDialog(hWndDlg, FALSE);
          break;

        case IDHELP:
          WinHelp(hWndDlg, szarHelpFile, HELP_CONTEXT, Technical_Support);
          break;
      }
      break;

    default:
      return FALSE;
  }
  return TRUE;
}
