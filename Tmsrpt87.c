//
//  This program code is a part of The Master Scheduler (TMS)
//  and is Copyright (C) 1991-2004 Schedule Masters, Inc.
//  All rights reserved.
//
//  TMSRpt87 - Load Data from the Connexionz RTI System into TMS
//
//  Two load points:
//
//     Stops.txt - A modified excel worksheet saved as tab-separated text
//                 containing platform tag (stop number), address/intersection,
//                 platform number, latitude, longitude
//
//    
//  Patterns.txt - A modified excel worksheet saved as tab-separated text
//                 containing route number, pattern name, direction, 
//                 platform tag (stop number), platform number, address/intersection,
//                 and a "schedule adherence timpoint" flag.
//
#include "TMSHeader.h"

#include <math.h>
#include <ctype.h>

#define kmToMiles( k )  ((double)(k) * 0.6213712)
#define FAbs( x )		((x) > 0.0 ? (x) : -(x))
#define Square( x )		((x) * (x))

/* Radius of Earth in km */
#define RadiusOfEarth	6367.5

/* Trig constants */
#define PI				3.14159265358979323846
#define	degToRad		(PI/180.0)


int GetCircularZone(	double coordLong,  double coordLat,	// Coordinate of interest.
						double centerLong, double centerLat,// Center of zones.
						double zoneMeters[],				// Array of distances from center - increasing distance sequence.
						int numZones )						// Number of zone distances.
{
	// If the given coordinate is in a zone, return the index of the zone in the range [0..numZones - 1].
	// If the given coordinate is outside the furthest zone, return numZones.
	register double dlong, dlat, sin_dlatDiv2, sin_dlongDiv2, sqrtA, d;
	register int i;

	/* Convert to radians */
	register double lat1	= centerLat  * degToRad;
	register double	long1	= centerLong * degToRad;
	register double lat2	= coordLat   * degToRad;
	register double long2	= coordLong  * degToRad;

	/* Do the calculation.  Only compute intermediate results once. */
	dlong = long2 - long1;
	dlat = lat2 - lat1;
	sin_dlatDiv2 = sin(dlat/2.0);
	sin_dlongDiv2 = sin(dlong/2.0);
	sqrtA = sqrt(sin_dlatDiv2 * sin_dlatDiv2 + cos(lat1) * cos(lat2) * sin_dlongDiv2 * sin_dlongDiv2);
	d = RadiusOfEarth * 2.0 * asin(sqrtA < 1.0 ? sqrtA : 1.0) * 1000.0;	// Convert to meters.

	// Find the smallest zone greater than the computed distance..
	for( i = 0; i < numZones; ++i )
		if( d < zoneMeters[i] )
			break;
	return i;
}

int GetZone(NODESDef *pNODES)
{
	// Center of the Christchurch Bus Exchange.
	double latCenter = -43.53379800, longCenter = 172.63757300;
	double zoneMeters[4] = { 15000, 20000, 30000, 40000};
	double latCoord, longCoord;

  int    iZone;

  latCoord = pNODES->latitude;
  longCoord = pNODES->longitude;

	iZone = GetCircularZone( latCoord, longCoord,latCenter, longCenter, zoneMeters, sizeof(zoneMeters) / sizeof(zoneMeters[0]) );

  pNODES->JURISDICTIONSrecordID = (iZone < 4 ? iZone + 1 : NO_RECORD);
	
  return 0;
}
#define PATMAXRTEDIRS  85
#define PATMAXNODES   100
#define PATMAXPATS     10

typedef struct PatternNodesStruct
{
  long platformTag;
  long platformNumber;
  long NODESrecordID;
  long nodeSequence;
  BOOL bTimepoint;
} PatternNodesDef;

typedef struct PatternDataStruct
{
  long PATTERNNAMESrecordID;
  int  numNodes;
  PatternNodesDef Nodes[PATMAXNODES];
} PatternDataDef;

typedef struct PatternStruct
{
  long ROUTESrecordID;
  long directionIndex;
  int  numPatterns;
  PatternDataDef Data[PATMAXPATS];
} PatternDef;

typedef struct BASEPatternDataStruct
{
  long NODESrecordID;
  long nodeSequence;
  BOOL bTimepoint;
  int  next;
} BASEPatternDataDef;

//
//  TMSRpt87() - Mainline
//
BOOL FAR TMSRPT87(TMSRPTPassedDataDef *pPassedData)
{
  BASEPatternDataDef BASEPatternData[500];
  BASEPatternDataDef thisPatternData[500];
  PatternDef *pPatterns;
  NODESDef tempNODES;
  FILE *fp, *fpe;
  BOOL bLoadStops;
  BOOL bLoadPatterns;
  BOOL bSameRouteNumber;
  BOOL bSamePatternName;
  BOOL bSameDirection;
  BOOL bReindexRoute;
  BOOL bReindexPattern;
  BOOL bReindexDirection;
  BOOL bFlushRoute;
  BOOL bFlushPattern;
  BOOL bFlushDirection;
  BOOL bFound;
  char inputLine[1024];
  char *ptr;
  char szInputRouteNumber[ROUTES_NUMBER_LENGTH + 1];
  char szInputPatternName[PATTERNNAMES_NAME_LENGTH + 1];
  char szInputDirection[DIRECTIONS_LONGNAME_LENGTH + 1];
  char szPrevInputRouteNumber[ROUTES_NUMBER_LENGTH + 1];
  char szPrevInputPatternName[PATTERNNAMES_NAME_LENGTH + 1];
  char szPrevInputDirection[DIRECTIONS_LONGNAME_LENGTH + 1];
  long stopNum;
  long recID;
  long ROUTESrecordID;
  long SERVICESrecordID;
  long DIRECTIONSrecordID;
  long PATTERNNAMESrecordID;
  long directionIndex;
  long TMSPatternNodes[50];
  long SERVICESrecordIDs[25];
  long firstSeq;

  int  previousPatternIndex;
  int  rcode2;
  int  nI, nJ, nK, nL, nM;
  int  numRteDirs;
  int  rteDirIndex;
  int  patIndex;
  int  numTMSPatternNodes;
  int  TMSPatternIndex;
  int  numServices;
  int  increment;
  int  numBASEPatternDataItems;
  int  numThisPatternDataItems;
  int  nMStart;
  int  next;
  int  prev;

  fp = NULL;
  fpe = NULL;
  pPatterns = NULL;
//
//  Find out what he wants to do
//
//  Stops?
//
  MessageBeep(MB_ICONQUESTION);
  nI = MessageBox(hWndMain, "Do you wish to load stop data?", TMS, MB_ICONQUESTION | MB_YESNOCANCEL);
  if(nI == IDCANCEL)
  {
    goto cleanup;
  }
  bLoadStops = (nI == IDYES);
//
//  Patterns?
//
  MessageBeep(MB_ICONQUESTION);
  nI = MessageBox(hWndMain, "Do you wish to load pattern data?", TMS, MB_ICONQUESTION | MB_YESNOCANCEL);
  if(nI == IDCANCEL)
  {
    goto cleanup;
  }
  bLoadPatterns = (nI == IDYES);
//
//  Status bar
//
  for(nI = 0; nI < m_LastReport; nI++)
  {
    if(TMSRPT[nI].originalReportNumber == pPassedData->nReportNumber)
    {
      StatusBarStart(hWndMain, TMSRPT[nI].szReportName);
      break;
    }
  }
//
//  Load stops
//
  if(bLoadStops)
  {
//
//  Open the text file
//
    fp = fopen("stops.txt", "r");
    if(fp == NULL)
    {
      MessageBox(hWndMain, "Failed to open stops.txt", TMS, MB_OK);
      goto cleanup;
    }
//
//  Read from the input file and write to the TMS database
//
    rcode2 = btrieve(B_GETLAST, TMS_NODES, &NODES, &NODESKey0, 0);
    recID = AssignRecID(rcode2, NODES.recordID);
    StatusBarText("Loading nodes/stops...");
    while(fgets(inputLine, sizeof(inputLine), fp))
    {
      if(StatusBarAbort())
      {
        goto cleanup;
      }
      memset(&NODES, 0x00, sizeof(NODESDef));
      NODES.recordID = recID++;
//
//  Number
//
      strcpy(tempString, strtok(inputLine, "\t"));
      stopNum = atol(tempString);
//
//  Abbr
//
      sprintf(tempString, "%04ld", stopNum);
      strncpy(NODES.abbrName, tempString, NODES_ABBRNAME_LENGTH);
//
//  Long name
//
      sprintf(tempString, "Stop%04ld", stopNum);
      strncpy(NODES.longName, tempString, NODES_LONGNAME_LENGTH);
//
//  Address
//
      strcpy(tempString, strtok(NULL, "\t"));
      pad(tempString, NODES_INTERSECTION_LENGTH);
      strncpy(NODES.intersection, tempString, NODES_INTERSECTION_LENGTH);
//
//  Description
//
      strncpy(NODES.description, tempString, NODES_DESCRIPTION_LENGTH);
//
//  Platform number
//
      strcpy(tempString, strtok(NULL, "\t"));
      NODES.number = atol(tempString);
//
//  Lat
//
      strcpy(tempString, strtok(NULL, "\t"));
      NODES.latitude = (float)atof(tempString);
//
//  Lon
//
      strcpy(tempString, strtok(NULL, "\t\n"));
      NODES.longitude = (float)atof(tempString);
//
//  Comments RecordID
//
      NODES.COMMENTSrecordID = atol(tempString);
//
//  Jurisdiction
//
      GetZone(&NODES);
//
//  Flags
//
      NODES.flags = NODES_FLAG_STOP;
//
//  Insert
// 
      rcode2 = btrieve(B_INSERT, TMS_NODES, &NODES, &NODESKey0, 0);
    }
//
//  Close the file
//
    fclose(fp);
  }
//
//  Load patterns
//
  if(bLoadPatterns)
  {
//
//  Open the text file
//
    fp = fopen("patterns.txt", "r");
    if(fp == NULL)
    {
      MessageBox(hWndMain, "Failed to open patterns.txt", TMS, MB_OK);
      goto cleanup;
    }
//
//  Open the error log
//
    fpe = fopen("error.log", "w");
    if(fpe == NULL)
    {
      MessageBox(hWndMain, "Failed to open error.log", TMS, MB_OK);
      goto cleanup;
    }
//
//  Get all the services
//
    rcode2 = btrieve(B_GETFIRST, TMS_SERVICES, &SERVICES, &SERVICESKey1, 1);
    if(rcode2 != 0)
    {
      MessageBox(hWndMain, "There were no services in the Services Table", TMS, MB_OK);
      goto cleanup;
    }
    numServices = 0;
    while(rcode2 == 0)
    {
      SERVICESrecordIDs[numServices] = SERVICES.recordID;
      numServices++;
      rcode2 = btrieve(B_GETNEXT, TMS_SERVICES, &SERVICES, &SERVICESKey1, 1);
    }
//
//  Allocate space for the structure
//
    pPatterns = (PatternDef *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(PatternDef) * PATMAXRTEDIRS); 
    if(pPatterns == NULL)
    {
      AllocationError(__FILE__, __LINE__, FALSE);
      goto cleanup;
    }
//
//  Use the first service in the system as the default.
//
    SERVICESrecordID = SERVICESrecordIDs[0];
//
//  Establish counters
//
    numRteDirs = 0;
    for(nI = 0; nI < PATMAXRTEDIRS; nI++)
    {
      pPatterns[nI].numPatterns = 0;
      for(nJ = 0; nJ < PATMAXPATS; nJ++)
      {
        pPatterns[nI].Data[nJ].numNodes = 0;
      }
    }
//
//  Cycle through the data
//
    bFlushRoute = FALSE;
    bFlushPattern = FALSE;
    bFlushDirection = FALSE;
    previousPatternIndex = NO_RECORD;
    strcpy(szPrevInputRouteNumber, "");
    strcpy(szPrevInputPatternName, "");
    strcpy(szPrevInputDirection, "");
    StatusBarText("Loading patterns...");
    while(fgets(inputLine, sizeof(inputLine), fp))
    {
      if(StatusBarAbort())
      {
        goto cleanup;
      }
//
//  Parse out the route number, pattern name, and direction
//
//  Route number
//
      strcpy(szInputRouteNumber, strtok(inputLine, "\t"));
      for(nI = 0; nI < (int)strlen(szInputRouteNumber); nI++)
      {
        szInputRouteNumber[nI] = toupper(szInputRouteNumber[nI]);
      }
//
//  Pattern name
//
      strcpy(szInputPatternName, strtok(NULL, "\t"));
      for(nI = 0; nI < (int)strlen(szInputPatternName); nI++)
      {
        szInputPatternName[nI] = toupper(szInputPatternName[nI]);
      }
//
//  Direction
//
      strcpy(szInputDirection, strtok(NULL, "\t"));
      for(nI = 0; nI < (int)strlen(szInputDirection); nI++)
      {
        szInputDirection[nI] = toupper(szInputDirection[nI]);
      }
//
//  Show the status
//
      sprintf(tempString, "Route: %s\nPattern: %s\nDirection: %s", 
            szInputRouteNumber, szInputPatternName, szInputDirection);
      StatusBarText(tempString);
//
//  See what's changed
//
      bSameRouteNumber = (strcmp(szInputRouteNumber, szPrevInputRouteNumber) == 0);
      bSamePatternName = (strcmp(szInputPatternName, szPrevInputPatternName) == 0);
      bSameDirection = (strcmp(szInputDirection, szPrevInputDirection) == 0);
//
//  Are we flushing?
//
//  Route
//
      if(bFlushRoute && bSameRouteNumber)
      {
        continue;
      }
//
//  Pattern name
//
      if(bFlushPattern && bSamePatternName)
      {
        continue;
      }
//
//  Direction
//
      if(bFlushDirection && bSameDirection)
      {
        continue;
      }
//
//  Set the reindexing flags
//
      bReindexRoute = FALSE;
      bReindexPattern = FALSE;
      bReindexDirection = FALSE;
//
//  Is there a change in route, pattern, or direction
//
      if(!bSameRouteNumber || !bSamePatternName || !bSameDirection)
      {
//
//  Is the route the same?
//
        if(bSameRouteNumber)
        {
//
//  Is the pattern name the same?
//
          if(bSamePatternName)
          {
//
//  We can't get here unless the direction changed
//
            fprintf(fpe, "    Loading direction %s\r\n", szInputDirection);
            bReindexDirection = TRUE;
          }
//
//  No - the pattern's changed.  Assume the need to recalculate
//  the direction recordIDs/date from TMS
//
          else
          {
            fprintf(fpe, "  Loading Pattern %s\r\n", szInputPatternName);
            fprintf(fpe, "    Loading direction %s\r\n", szInputDirection);
            bReindexPattern = TRUE;
            bReindexDirection = TRUE;
          }
        }
//
//  No - the route's changed.  Assume the need to recalculate
//  the pattern and direction recordIDs/data from TMS
//
        else
        {
          fprintf(fpe, "\r\nLoading Route %s\r\n", szInputRouteNumber);
          fprintf(fpe, "  Loading Pattern %s\r\n", szInputPatternName);
          fprintf(fpe, "    Loading direction %s\r\n", szInputDirection);
          bReindexRoute = TRUE;
          bReindexPattern = TRUE;
          bReindexDirection = TRUE;
        }
      }
//
//  Reindex as per the above
//
//  Route - Locate the route record in TMS.  There's no clean way
//  to do this because the route number in TMS could be padded with
//  blanks on the front or back.  Just cycle through.
//
      if(bReindexRoute)
      {
        bFlushRoute = TRUE;
        ROUTESrecordID = NO_RECORD;
        rcode2 = btrieve(B_GETFIRST, TMS_ROUTES, &ROUTES, &ROUTESKey1, 1);
        while(rcode2 == 0)
        {
          strncpy(szarString, ROUTES.number, ROUTES_NUMBER_LENGTH);
          trim(szarString, ROUTES_NUMBER_LENGTH);
          ptr = szarString;
          while(*ptr)
          {
            if(*ptr == ' ')
            {
              ptr++;
            }
            else
            {
              break;
            }
          }
          strcpy(tempString, ptr);
          for(nI = 0; nI < (int)strlen(tempString); nI++)
          {
            tempString[nI] = toupper(tempString[nI]);
          }
          if(strcmp(tempString, szInputRouteNumber) == 0)
          {
            ROUTESrecordID = ROUTES.recordID;
            bFlushRoute = FALSE;
            break;
          }
          rcode2 = btrieve(B_GETNEXT, TMS_ROUTES, &ROUTES, &ROUTESKey1, 1);
        }
        if(!bFlushRoute)
        {
          strcpy(szPrevInputRouteNumber, szInputRouteNumber);
        }
        else
        {
          fprintf(fpe, "      Route %s not found in Routes Table - flushing input stream\r\n", szInputRouteNumber);
        }
      }
//
//  Direction - Find the direction record in TMS.  The name must
//  match exactly in the directions table or the records with
//  direction name on the input file get flushed.
//
      if(bReindexDirection)
      {
        bFlushDirection = TRUE;
        for(nI = 0; nI < 2; nI++)
        {
          if(ROUTES.DIRECTIONSrecordID[nI] == NO_RECORD)
          {
            continue;
          }
          DIRECTIONSKey0.recordID = ROUTES.DIRECTIONSrecordID[nI];
          rcode2 = btrieve(B_GETEQUAL, TMS_DIRECTIONS, &DIRECTIONS, &DIRECTIONSKey0, 0);
          if(rcode2 == 0)
          {
            strncpy(tempString, DIRECTIONS.longName, DIRECTIONS_LONGNAME_LENGTH);
            trim(tempString, DIRECTIONS_LONGNAME_LENGTH);
            for(nJ = 0; nJ < (int)strlen(tempString); nJ++)
            {
              tempString[nJ] = toupper(tempString[nJ]);
            }
            if(strcmp(tempString, szInputDirection) == 0)
            {
              DIRECTIONSrecordID = DIRECTIONS.recordID;
              directionIndex = nI;
              bFlushDirection = FALSE;
              break;
            }
          }
        }
        if(bFlushDirection)
        {
          fprintf(fpe, "      Direction %s not found for this route - flushing input stream\r\n", szInputDirection);
        }
        else
        {
          for(bFound = FALSE, nI = 0; nI < numRteDirs; nI++)
          {
            if(pPatterns[nI].ROUTESrecordID == ROUTESrecordID &&
                  pPatterns[nI].directionIndex == directionIndex)
            {
              rteDirIndex = nI;
              bFound = TRUE;
              break;
            }
          }
          if(!bFound)
          {
            pPatterns[numRteDirs].ROUTESrecordID = ROUTESrecordID;
            pPatterns[numRteDirs].directionIndex = directionIndex;
            rteDirIndex = numRteDirs;
            numRteDirs++;
          }
          strcpy(szPrevInputDirection, szInputDirection);
        }
      }
//
//  Pattern name - Find the pattern name in TMS.  Not only does the
//  name have to exist, but is has to occur on the route and direction
//  already figured out.  There's no service reference in the
//  Connexionz input file, so we'll assume the first service in the
//  Services Table, as established earlier.
//
      if(bReindexPattern)
      {
        bFlushPattern = TRUE;
        strncpy(PATTERNNAMESKey1.name, szInputPatternName, PATTERNNAMES_NAME_LENGTH);
        pad(PATTERNNAMESKey1.name, PATTERNNAMES_NAME_LENGTH);
        rcode2 = btrieve(B_GETEQUAL, TMS_PATTERNNAMES, &PATTERNNAMES, &PATTERNNAMESKey1, 1);
        if(rcode2 == 0)
        {
          PATTERNNAMESrecordID = PATTERNNAMES.recordID;
          PATTERNSKey2.ROUTESrecordID = ROUTESrecordID;
          PATTERNSKey2.SERVICESrecordID = SERVICESrecordID;
          PATTERNSKey2.PATTERNNAMESrecordID = PATTERNNAMESrecordID;
          PATTERNSKey2.directionIndex = directionIndex;
          PATTERNSKey2.nodeSequence = NO_RECORD;
          rcode2 = btrieve(B_GETGREATER, TMS_PATTERNS, &PATTERNS, &PATTERNSKey2, 2);
          if(rcode2 == 0 &&
                PATTERNS.ROUTESrecordID == ROUTESrecordID &&
                PATTERNS.SERVICESrecordID == SERVICESrecordID &&
                PATTERNS.PATTERNNAMESrecordID == PATTERNNAMESrecordID &&
                PATTERNS.directionIndex == directionIndex)
          {
            bFlushPattern = FALSE;
            numTMSPatternNodes = 0;
            TMSPatternIndex = 0;
            while(rcode2 == 0 &&
                  PATTERNS.ROUTESrecordID == ROUTESrecordID &&
                  PATTERNS.SERVICESrecordID == SERVICESrecordID &&
                  PATTERNS.PATTERNNAMESrecordID == PATTERNNAMESrecordID &&
                  PATTERNS.directionIndex == directionIndex)
            {
              if(!(PATTERNS.flags & PATTERNS_FLAG_BUSSTOP))
              {
                TMSPatternNodes[numTMSPatternNodes] = PATTERNS.NODESrecordID;
                numTMSPatternNodes++;
              }
              rcode2 = btrieve(B_GETNEXT, TMS_PATTERNS, &PATTERNS, &PATTERNSKey2, 2);
            }
          }
        }
        if(bFlushPattern)
        {
          fprintf(fpe, "      Pattern %s not found for this route/dir - flushing input stream\r\n", szInputPatternName);
        }
        else
        {
          for(bFound = FALSE, nI = 0; nI < pPatterns[rteDirIndex].numPatterns; nI++)
          {
            if(pPatterns[rteDirIndex].Data[nI].PATTERNNAMESrecordID == PATTERNNAMESrecordID)
            {
              patIndex = nI;
              bFound = TRUE;
              break;
            }
          }
          if(!bFound)
          {
            pPatterns[rteDirIndex].Data[pPatterns[rteDirIndex].numPatterns].PATTERNNAMESrecordID = PATTERNNAMESrecordID;
            patIndex = pPatterns[rteDirIndex].numPatterns;
            pPatterns[rteDirIndex].numPatterns++;
          }
        }
        strcpy(szPrevInputPatternName, szInputPatternName);
      }
//
//  Parse the rest of the input string
//
      nI = pPatterns[rteDirIndex].Data[patIndex].numNodes;
//
//  Platform Tag
//
      strcpy(tempString, strtok(NULL, "\t"));
      pPatterns[rteDirIndex].Data[patIndex].Nodes[nI].platformTag = atol(tempString);
//
//  Platform number
//
      strcpy(tempString, strtok(NULL, "\t"));
      pPatterns[rteDirIndex].Data[patIndex].Nodes[nI].platformNumber = atol(tempString);
//
//  Name (not kept)
//
      strcpy(tempString, strtok(NULL, "\t"));
//
//  Sequence number (used later)
//
      pPatterns[rteDirIndex].Data[patIndex].Nodes[nI].nodeSequence = NO_RECORD;
//
//  Timepoint flag
//
      strcpy(tempString, strtok(NULL, "\t\n"));
      pPatterns[rteDirIndex].Data[patIndex].Nodes[nI].bTimepoint = (strcmp(tempString, "Stop") != 0);
//
//  Done parsing - locate the node/stop in the Nodes Table.
//  If it's flagged as a timepoint, find it via the pattern and update the OB or IB Node number fields.
//  While we're here, we might as well update the lat/long in case there are bogus values in the Nodes Table
//
      if(pPatterns[rteDirIndex].Data[patIndex].Nodes[nI].bTimepoint)
      {
        NODESKey0.recordID = TMSPatternNodes[TMSPatternIndex];
        rcode2 = btrieve(B_GETEQUAL, TMS_NODES, &NODES, &NODESKey0, 0);
        if(rcode2 == 0)
        {
          memcpy(&tempNODES, &NODES, sizeof(NODESDef));
          if(directionIndex == 0)
          {
            tempNODES.OBStopNumber = pPatterns[rteDirIndex].Data[patIndex].Nodes[nI].platformTag;
          }
          else
          {
            tempNODES.IBStopNumber = pPatterns[rteDirIndex].Data[patIndex].Nodes[nI].platformTag;
          }
          sprintf(NODESKey2.abbrName, "%04ld", pPatterns[rteDirIndex].Data[patIndex].Nodes[nI].platformTag);
          rcode2 = btrieve(B_GETEQUAL, TMS_NODES, &NODES, &NODESKey2, 2);
          if(rcode2 == 0)
          {
            tempNODES.latitude = NODES.latitude;
            tempNODES.longitude = NODES.longitude;
            NODESKey0.recordID = TMSPatternNodes[TMSPatternIndex];
            rcode2 = btrieve(B_GETEQUAL, TMS_NODES, &NODES, &NODESKey0, 0);
          }
          memcpy(&NODES, &tempNODES, sizeof(NODESDef));
          rcode2 = btrieve(B_UPDATE, TMS_NODES, &NODES, &NODESKey0, 0);
          pPatterns[rteDirIndex].Data[patIndex].Nodes[nI].NODESrecordID = (rcode2 == 0 ? NODES.recordID : NO_RECORD);
        }
        TMSPatternIndex++;
      }
//
//  Not a timepoint.  Find it by name (Stopnnnn)
//
      else
      {
        sprintf(NODESKey2.abbrName, "%04ld", pPatterns[rteDirIndex].Data[patIndex].Nodes[nI].platformTag);
        rcode2 = btrieve(B_GETEQUAL, TMS_NODES, &NODES, &NODESKey2, 2);
        pPatterns[rteDirIndex].Data[patIndex].Nodes[nI].NODESrecordID = (rcode2 == 0 ? NODES.recordID : NO_RECORD);
      }
//
//  Add 1 to the number of nodes and cycle back to read another record
//
      pPatterns[rteDirIndex].Data[patIndex].numNodes++;
    }  // while fgets
//
//  Data structure loaded
//
//  Cycle through the unique routes and directions
//
    StatusBarText("Adjusting patterns...");
    for(nI = 0; nI < numRteDirs; nI++)
    {
      if(StatusBarAbort())
      {
        goto cleanup;
      }
      ROUTESrecordID = pPatterns[nI].ROUTESrecordID;
      directionIndex = pPatterns[nI].directionIndex;
//
//  Now through all the services in the service list
//
      for(nJ = 0; nJ < numServices; nJ++)
      {
        if(StatusBarAbort())
        {
          goto cleanup;
        }
        SERVICESrecordID = SERVICESrecordIDs[nJ];
//
//  Get the BASE pattern for this rte/ser/dir
//
//  There should be no intervening stops
//
        numBASEPatternDataItems = 0;
        PATTERNSKey2.ROUTESrecordID = ROUTESrecordID;
        PATTERNSKey2.SERVICESrecordID = SERVICESrecordID;
        PATTERNSKey2.directionIndex = directionIndex;
        PATTERNSKey2.PATTERNNAMESrecordID = basePatternRecordID;
        PATTERNSKey2.nodeSequence = NO_RECORD;
        rcode2 = btrieve(B_GETGREATER, TMS_PATTERNS, &PATTERNS, &PATTERNSKey2, 2);
        while(rcode2 == 0 &&
              PATTERNS.ROUTESrecordID == ROUTESrecordID &&
              PATTERNS.SERVICESrecordID == SERVICESrecordID &&
              PATTERNS.directionIndex == directionIndex && 
              PATTERNS.PATTERNNAMESrecordID == basePatternRecordID)
        {
          BASEPatternData[numBASEPatternDataItems].NODESrecordID = PATTERNS.NODESrecordID;
          BASEPatternData[numBASEPatternDataItems].nodeSequence = PATTERNS.nodeSequence;
          BASEPatternData[numBASEPatternDataItems].bTimepoint = TRUE;
          BASEPatternData[numBASEPatternDataItems].next = numBASEPatternDataItems + 1;
          numBASEPatternDataItems++;
          rcode2 = btrieve(B_GETNEXT, TMS_PATTERNS, &PATTERNS, &PATTERNSKey2, 2);
        }
//
//  No BASE pattern?  No service.  Cycle through.
//
        if(numBASEPatternDataItems == 0)
        {
          continue;
        }
//
//  Terminate the linked list
//
        if(numBASEPatternDataItems != 0)
        {
          BASEPatternData[numBASEPatternDataItems - 1].next = NO_RECORD;
        }
//
//  Cycle through the input pattern names
//

        for(nK = 0; nK < pPatterns[nI].numPatterns; nK++)
        {
          if(StatusBarAbort())
          {
            goto cleanup;
          }
          PATTERNNAMESrecordID = pPatterns[nI].Data[nK].PATTERNNAMESrecordID;
//
//  Locate and save this pattern from TMS
//
//  There should be no intervening stops
//
          numThisPatternDataItems = 0;
          PATTERNSKey2.ROUTESrecordID = ROUTESrecordID;
          PATTERNSKey2.SERVICESrecordID = SERVICESrecordID;
          PATTERNSKey2.directionIndex = directionIndex;
          PATTERNSKey2.PATTERNNAMESrecordID = PATTERNNAMESrecordID;
          PATTERNSKey2.nodeSequence = NO_RECORD;
          rcode2 = btrieve(B_GETGREATER, TMS_PATTERNS, &PATTERNS, &PATTERNSKey2, 2);
          while(rcode2 == 0 &&
                PATTERNS.ROUTESrecordID == ROUTESrecordID &&
                PATTERNS.SERVICESrecordID == SERVICESrecordID &&
                PATTERNS.directionIndex == directionIndex && 
                PATTERNS.PATTERNNAMESrecordID == PATTERNNAMESrecordID)
          {
            thisPatternData[numThisPatternDataItems].NODESrecordID = PATTERNS.NODESrecordID;
            thisPatternData[numThisPatternDataItems].nodeSequence = PATTERNS.nodeSequence;
            thisPatternData[numThisPatternDataItems].bTimepoint = TRUE;
            thisPatternData[numThisPatternDataItems].next = numThisPatternDataItems + 1;
            numThisPatternDataItems++;
            rcode2 = btrieve(B_GETNEXT, TMS_PATTERNS, &PATTERNS, &PATTERNSKey2, 2);
          }
//
//  Terminate the linked list
//
          if(numThisPatternDataItems != 0)
          {
            thisPatternData[numThisPatternDataItems - 1].next = NO_RECORD;
          }
//
//  Cycle through the timepoints in thisPatternData to
//  stamp the sequence number on the input pattern data
//
          nMStart = 0;
          for(nL = 0; nL < numThisPatternDataItems; nL++)
          {
            for(nM = nMStart; nM < pPatterns[nI].Data[nK].numNodes; nM++)
            {
              if(thisPatternData[nL].NODESrecordID == pPatterns[nI].Data[nK].Nodes[nM].NODESrecordID)
              {
                pPatterns[nI].Data[nK].Nodes[nM].nodeSequence = thisPatternData[nL].nodeSequence;
                nMStart = nM + 1;
                break;
              }
            }
          }
//
//  Cycle through the now timepoint-sequenced input pattern
//  to locate the points within the BASE pattern structure.
//
//  This will overwrite the sequence numbers of the timepoints
//. but since they're supposedly identical, who cares.  What it
//  will get, though, is any stops that have been added to
//  the structure to this point.
//
          nMStart = 0;
          prev = 0;
          for(nL = 0; nL < pPatterns[nI].Data[nK].numNodes; nL++)
          {
            nM = nMStart;
            bFound = FALSE;
            while(nM != NO_RECORD)
            {
              if(BASEPatternData[nM].nodeSequence != NO_RECORD)
              {
                if(pPatterns[nI].Data[nK].Nodes[nL].nodeSequence == BASEPatternData[nM].nodeSequence)
                {
                  bFound = TRUE;
                  prev = nM;
                  nMStart = BASEPatternData[nM].next;
                  break;
                }
              }
              nM = BASEPatternData[nM].next;
            }
            if(!bFound)
            {
              BASEPatternData[numBASEPatternDataItems].NODESrecordID = pPatterns[nI].Data[nK].Nodes[nL].NODESrecordID;
              BASEPatternData[numBASEPatternDataItems].nodeSequence = pPatterns[nI].Data[nK].Nodes[nL].nodeSequence;
              BASEPatternData[numBASEPatternDataItems].bTimepoint = pPatterns[nI].Data[nK].Nodes[nL].bTimepoint;
              next = BASEPatternData[prev].next;
              BASEPatternData[numBASEPatternDataItems].next = next;
              BASEPatternData[prev].next = numBASEPatternDataItems;
              nMStart = numBASEPatternDataItems;
              prev = numBASEPatternDataItems;
              numBASEPatternDataItems++;
            }
          }
        }  //nK
//
//  Sort out the BASE structure so it's sequential
//
//  Re-use "thisPatternData" to do so.
//
        next = 0;
        for(nK = 0; nK < numBASEPatternDataItems; nK++)
        {
          thisPatternData[nK].NODESrecordID = BASEPatternData[next].NODESrecordID;
          thisPatternData[nK].nodeSequence = BASEPatternData[next].nodeSequence;
          thisPatternData[nK].bTimepoint = BASEPatternData[next].bTimepoint;
          next = BASEPatternData[next].next;
        }
//
//  Go through the now-sorted and complete BASE structure and
//  assign sequence numbers where none (NO_RECORD) exist.  The
//  first and last records have to have sequence numbers, as
//  they were from the original BASE pattern in TMS.
//
        firstSeq = 0;
        for(nK = 1; nK < numBASEPatternDataItems; nK++)
        {
          if(thisPatternData[nK].nodeSequence != NO_RECORD)
          {
            if(nK != firstSeq + 1)
            {
              increment = thisPatternData[nK].nodeSequence - thisPatternData[firstSeq].nodeSequence;
              increment /= (nK - firstSeq);
              for(nL = firstSeq + 1; nL < nK; nL++)
              {
                thisPatternData[nL].nodeSequence = thisPatternData[nL - 1].nodeSequence + increment;
              }
            }
            firstSeq = nK;
          }
        }
//
//  Update the BASE pattern in TMS
//
        rcode2 = btrieve(B_GETLAST, TMS_PATTERNS, &PATTERNS, &PATTERNSKey0, 0);
        recID = AssignRecID(rcode2, PATTERNS.recordID);
        for(nK = 1; nK < numBASEPatternDataItems - 1; nK++)
        {
          if(thisPatternData[nK].bTimepoint)
          {
            continue;
          }
          memset(&PATTERNS, 0x00, sizeof(PATTERNSDef));
          PATTERNS.recordID = recID++;
          PATTERNS.COMMENTSrecordID = NO_RECORD;
          PATTERNS.ROUTESrecordID = ROUTESrecordID;
          PATTERNS.SERVICESrecordID = SERVICESrecordID;
          PATTERNS.directionIndex = directionIndex;
          PATTERNS.PATTERNNAMESrecordID = basePatternRecordID;
          PATTERNS.NODESrecordID = thisPatternData[nK].NODESrecordID;
          PATTERNS.nodeSequence = thisPatternData[nK].nodeSequence;
          PATTERNS.flags = PATTERNS_FLAG_BUSSTOP;
          rcode2 = btrieve(B_INSERT, TMS_PATTERNS, &PATTERNS, &PATTERNSKey0, 0);
        }
//
//  Cycle through the input pattern names
//

        for(nK = 0; nK < pPatterns[nI].numPatterns; nK++)
        {
          if(StatusBarAbort())
          {
            goto cleanup;
          }
          PATTERNNAMESrecordID = pPatterns[nI].Data[nK].PATTERNNAMESrecordID;
//
//  Cycle through the incoming pattern and locate the corresponding stop in
//  the BASE pattern (which happens to be sitting in thisPatternData), get
//  the sequence number, and add it to the TMS sub-pattern.
//
          rcode2 = btrieve(B_GETLAST, TMS_PATTERNS, &PATTERNS, &PATTERNSKey0, 0);
          recID = AssignRecID(rcode2, PATTERNS.recordID);
          nMStart = 0;
          for(nL = 0; nL < pPatterns[nI].Data[nK].numNodes; nL++)
          {
            if(pPatterns[nI].Data[nK].Nodes[nL].bTimepoint)
            {
              continue;
            }
            for(nM = nMStart; nM < numBASEPatternDataItems; nM++)
            {
              if(pPatterns[nI].Data[nK].Nodes[nL].NODESrecordID == thisPatternData[nM].NODESrecordID)
              {
                memset(&PATTERNS, 0x00, sizeof(PATTERNSDef));
                PATTERNS.recordID = recID++;
                PATTERNS.COMMENTSrecordID = NO_RECORD;
                PATTERNS.ROUTESrecordID = ROUTESrecordID;
                PATTERNS.SERVICESrecordID = SERVICESrecordID;
                PATTERNS.directionIndex = directionIndex;
                PATTERNS.PATTERNNAMESrecordID = PATTERNNAMESrecordID;
                PATTERNS.NODESrecordID = thisPatternData[nM].NODESrecordID;
                PATTERNS.nodeSequence = thisPatternData[nM].nodeSequence;
                PATTERNS.flags = PATTERNS_FLAG_BUSSTOP;
                rcode2 = btrieve(B_INSERT, TMS_PATTERNS, &PATTERNS, &PATTERNSKey0, 0);
                nMStart = nM + 1;
                break;
              }
            }  // nM
          }  // nL
        }  // nK
      }  // nJ
    }  // nI
//
//  Close the file
//
    fclose(fp);
  }
//
//  Cleanup
//
  cleanup:
    if(fp != NULL)
    {
      fclose(fp);
    }
    if(fpe != NULL)
    {
      fclose(fpe);
    }
    TMSHeapFree(pPatterns);
    StatusBarEnd();
//
//  All done
//
  MessageBox(NULL, "Done!", TMS, MB_OK);

  return(TRUE);
}
