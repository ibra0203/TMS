// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "f1replaceresults.h"


/////////////////////////////////////////////////////////////////////////////
// CF1ReplaceResults properties

/////////////////////////////////////////////////////////////////////////////
// CF1ReplaceResults operations

long CF1ReplaceResults::GetFound()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CF1ReplaceResults::GetReplaced()
{
	long result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}
