// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CPicture1;
class CF1RangeRef;
class CF1ObjPos;
class CF1Rect;
class CF1ReplaceResults;
class CF1ODBCQuery;
class CF1ODBCConnect;
class CF1BookView;
class CF1FileSpec;
class CF1NumberFormat;
class CF1CellFormat;

/////////////////////////////////////////////////////////////////////////////
// CF1Book wrapper class

class CF1Book : public CWnd
{
protected:
	DECLARE_DYNCREATE(CF1Book)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x13e51003, 0xa52b, 0x11d0, { 0x86, 0xda, 0x0, 0x60, 0x8c, 0xb9, 0xfb, 0xfb } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd, UINT nID,
		CCreateContext* pContext = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); }

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID,
		CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); }

// Attributes
public:
	unsigned long GetBackColor();
	void SetBackColor(unsigned long);
	long GetCol();
	void SetCol(long);
	long GetRow();
	void SetRow(long);
	long GetShowHScrollBar();
	void SetShowHScrollBar(long);
	CString GetText();
	void SetText(LPCTSTR);
	double GetNumber();
	void SetNumber(double);
	CString GetFormula();
	void SetFormula(LPCTSTR);
	long GetFixedCol();
	void SetFixedCol(long);
	long GetFixedCols();
	void SetFixedCols(long);
	long GetFixedRow();
	void SetFixedRow(long);
	long GetFixedRows();
	void SetFixedRows(long);
	BOOL GetShowGridLines();
	void SetShowGridLines(BOOL);
	BOOL GetShowRowHeading();
	void SetShowRowHeading(BOOL);
	long GetShowSelections();
	void SetShowSelections(long);
	long GetLeftCol();
	void SetLeftCol(long);
	long GetMaxCol();
	void SetMaxCol(long);
	long GetMaxRow();
	void SetMaxRow(long);
	long GetTopRow();
	void SetTopRow(long);
	BOOL GetAllowResize();
	void SetAllowResize(BOOL);
	BOOL GetAllowSelections();
	void SetAllowSelections(BOOL);
	BOOL GetAllowFormulas();
	void SetAllowFormulas(BOOL);
	BOOL GetAllowInCellEditing();
	void SetAllowInCellEditing(BOOL);
	long GetShowVScrollBar();
	void SetShowVScrollBar(long);
	BOOL GetAllowFillRange();
	void SetAllowFillRange(BOOL);
	BOOL GetAllowMoveRange();
	void SetAllowMoveRange(BOOL);
	long GetSelStartCol();
	void SetSelStartCol(long);
	long GetSelStartRow();
	void SetSelStartRow(long);
	long GetSelEndCol();
	void SetSelEndCol(long);
	long GetSelEndRow();
	void SetSelEndRow(long);
	unsigned long GetExtraColor();
	void SetExtraColor(unsigned long);
	CString GetFileName();
	void SetFileName(LPCTSTR);
	BOOL GetAutoRecalc();
	void SetAutoRecalc(BOOL);
	BOOL GetPrintGridLines();
	void SetPrintGridLines(BOOL);
	BOOL GetPrintRowHeading();
	void SetPrintRowHeading(BOOL);
	BOOL GetPrintHCenter();
	void SetPrintHCenter(BOOL);
	BOOL GetPrintVCenter();
	void SetPrintVCenter(BOOL);
	BOOL GetPrintLeftToRight();
	void SetPrintLeftToRight(BOOL);
	CString GetPrintHeader();
	void SetPrintHeader(LPCTSTR);
	CString GetPrintFooter();
	void SetPrintFooter(LPCTSTR);
	double GetPrintLeftMargin();
	void SetPrintLeftMargin(double);
	double GetPrintTopMargin();
	void SetPrintTopMargin(double);
	double GetPrintRightMargin();
	void SetPrintRightMargin(double);
	double GetPrintBottomMargin();
	void SetPrintBottomMargin(double);
	CString GetPrintArea();
	void SetPrintArea(LPCTSTR);
	CString GetPrintTitles();
	void SetPrintTitles(LPCTSTR);
	BOOL GetPrintNoColor();
	void SetPrintNoColor(BOOL);
	CString GetSelection();
	void SetSelection(LPCTSTR);
	CString GetTableName();
	void SetTableName(LPCTSTR);
	BOOL GetDoCancelEdit();
	void SetDoCancelEdit(BOOL);
	BOOL GetDoSelChange();
	void SetDoSelChange(BOOL);
	BOOL GetDoStartEdit();
	void SetDoStartEdit(BOOL);
	BOOL GetDoEndEdit();
	void SetDoEndEdit(BOOL);
	BOOL GetDoStartRecalc();
	void SetDoStartRecalc(BOOL);
	BOOL GetDoEndRecalc();
	void SetDoEndRecalc(BOOL);
	BOOL GetDoClick();
	void SetDoClick(BOOL);
	BOOL GetDoDblClick();
	void SetDoDblClick(BOOL);
	BOOL GetShowColHeading();
	void SetShowColHeading(BOOL);
	BOOL GetPrintColHeading();
	void SetPrintColHeading(BOOL);
	CString GetEntry();
	void SetEntry(LPCTSTR);
	BOOL GetRepaint();
	void SetRepaint(BOOL);
	BOOL GetAllowArrows();
	void SetAllowArrows(BOOL);
	BOOL GetAllowTabs();
	void SetAllowTabs(BOOL);
	CString GetFormattedText();
	void SetFormattedText(LPCTSTR);
	BOOL GetRowMode();
	void SetRowMode(BOOL);
	BOOL GetAllowDelete();
	void SetAllowDelete(BOOL);
	BOOL GetEnableProtection();
	void SetEnableProtection(BOOL);
	long GetMinCol();
	void SetMinCol(long);
	long GetMinRow();
	void SetMinRow(long);
	BOOL GetDoTopLeftChanged();
	void SetDoTopLeftChanged(BOOL);
	BOOL GetAllowEditHeaders();
	void SetAllowEditHeaders(BOOL);
	BOOL GetDoObjClick();
	void SetDoObjClick(BOOL);
	BOOL GetDoObjDblClick();
	void SetDoObjDblClick(BOOL);
	BOOL GetAllowObjSelections();
	void SetAllowObjSelections(BOOL);
	BOOL GetDoRClick();
	void SetDoRClick(BOOL);
	BOOL GetDoRDblClick();
	void SetDoRDblClick(BOOL);
	CString GetClip();
	void SetClip(LPCTSTR);
	CString GetClipValues();
	void SetClipValues(LPCTSTR);
	BOOL GetPrintLandscape();
	void SetPrintLandscape(BOOL);
	BOOL GetEnabled();
	void SetEnabled(BOOL);
	short GetBorderStyle();
	void SetBorderStyle(short);
	CString GetAppName();
	void SetAppName(LPCTSTR);
	short GetHdrHeight();
	void SetHdrHeight(short);
	short GetHdrWidth();
	void SetHdrWidth(short);
	CString GetNumberFormat();
	void SetNumberFormat(LPCTSTR);
	CString GetTopLeftText();
	void SetTopLeftText(LPCTSTR);
	BOOL GetEnterMovesDown();
	void SetEnterMovesDown(BOOL);
	long GetLastCol();
	void SetLastCol(long);
	long GetLastRow();
	void SetLastRow(long);
	BOOL GetLogical();
	void SetLogical(BOOL);
	long GetMode();
	void SetMode(long);
	long GetPolyEditMode();
	void SetPolyEditMode(long);
	short GetViewScale();
	void SetViewScale(short);
	short GetSelectionCount();
	void SetSelectionCount(short);
	CString GetTitle();
	void SetTitle(LPCTSTR);
	short GetType();
	void SetType(short);
	BOOL GetShowFormulas();
	void SetShowFormulas(BOOL);
	BOOL GetShowZeroValues();
	void SetShowZeroValues(BOOL);
	BOOL GetDoObjValueChanged();
	void SetDoObjValueChanged(BOOL);
	BOOL GetScrollToLastRC();
	void SetScrollToLastRC(BOOL);
	BOOL GetModified();
	void SetModified(BOOL);
	BOOL GetDoObjGotFocus();
	void SetDoObjGotFocus(BOOL);
	BOOL GetDoObjLostFocus();
	void SetDoObjLostFocus(BOOL);
	long GetPrintDevMode();
	void SetPrintDevMode(long);
	long GetNumSheets();
	void SetNumSheets(long);
	long GetSheet();
	void SetSheet(long);
	long GetColWidthUnits();
	void SetColWidthUnits(long);
	BOOL GetShowTypeMarkers();
	void SetShowTypeMarkers(BOOL);
	long GetShowTabs();
	void SetShowTabs(long);
	BOOL GetShowEditBar();
	void SetShowEditBar(BOOL);
	BOOL GetShowEditBarCellRef();
	void SetShowEditBarCellRef(BOOL);
	BOOL GetAllowDesigner();
	void SetAllowDesigner(BOOL);
	OLE_HANDLE GetHWnd();
	void SetHWnd(OLE_HANDLE);
	BOOL GetAllowAutoFill();
	void SetAllowAutoFill(BOOL);
	BOOL GetCompressed();
	void SetCompressed(BOOL);
	CString GetFontName();
	void SetFontName(LPCTSTR);
	short GetFontSize();
	void SetFontSize(short);
	BOOL GetFontBold();
	void SetFontBold(BOOL);
	BOOL GetFontItalic();
	void SetFontItalic(BOOL);
	BOOL GetFontUnderline();
	void SetFontUnderline(BOOL);
	BOOL GetFontStrikeout();
	void SetFontStrikeout(BOOL);
	unsigned long GetFontColor();
	void SetFontColor(unsigned long);
	long GetFontCharSet();
	void SetFontCharSet(long);
	long GetHAlign();
	void SetHAlign(long);
	BOOL GetWordWrap();
	void SetWordWrap(BOOL);
	long GetVAlign();
	void SetVAlign(long);
	BOOL GetLaunchWorkbookDesigner();
	void SetLaunchWorkbookDesigner(BOOL);
	double GetPrintHeaderMargin();
	void SetPrintHeaderMargin(double);
	double GetPrintFooterMargin();
	void SetPrintFooterMargin(double);
	CString GetFormulaLocal();
	void SetFormulaLocal(LPCTSTR);
	CString GetNumberFormatLocal();
	void SetNumberFormatLocal(LPCTSTR);
	CString GetSelectionLocal();
	void SetSelectionLocal(LPCTSTR);
	CString GetDataTransferRange();
	void SetDataTransferRange(LPCTSTR);
	BOOL GetCanEditPaste();
	void SetCanEditPaste(BOOL);
	short GetObjPatternStyle();
	void SetObjPatternStyle(short);
	unsigned long GetObjPatternFG();
	void SetObjPatternFG(unsigned long);
	unsigned long GetObjPatternBG();
	void SetObjPatternBG(unsigned long);
	CString GetDefaultFontName();
	void SetDefaultFontName(LPCTSTR);
	short GetDefaultFontSize();
	void SetDefaultFontSize(short);
	BOOL GetSelHdrRow();
	void SetSelHdrRow(BOOL);
	BOOL GetSelHdrCol();
	void SetSelHdrCol(BOOL);
	BOOL GetSelHdrTopLeft();
	void SetSelHdrTopLeft(BOOL);
	BOOL GetIterationEnabled();
	void SetIterationEnabled(BOOL);
	short GetIterationMax();
	void SetIterationMax(short);
	double GetIterationMaxChange();
	void SetIterationMaxChange(double);
	short GetPrintScale();
	void SetPrintScale(short);
	BOOL GetPrintScaleFitToPage();
	void SetPrintScaleFitToPage(BOOL);
	long GetPrintScaleFitVPages();
	void SetPrintScaleFitVPages(long);
	long GetPrintScaleFitHPages();
	void SetPrintScaleFitHPages(long);
	short GetLineStyle();
	void SetLineStyle(short);
	unsigned long GetLineColor();
	void SetLineColor(unsigned long);
	short GetLineWeight();
	void SetLineWeight(short);
	CString GetODBCSQLState();
	void SetODBCSQLState(LPCTSTR);
	long GetODBCNativeError();
	void SetODBCNativeError(long);
	CString GetODBCErrorMsg();
	void SetODBCErrorMsg(LPCTSTR);
	BOOL GetDataTransferHeadings();
	void SetDataTransferHeadings(BOOL);
	BOOL GetFormatPaintMode();
	void SetFormatPaintMode(BOOL);
	BOOL GetCanEditPasteSpecial();
	void SetCanEditPasteSpecial(BOOL);
	BOOL GetPrecisionAsDisplayed();
	void SetPrecisionAsDisplayed(BOOL);
	BOOL GetDoSafeEvents();
	void SetDoSafeEvents(BOOL);
	long GetDefaultFontCharSet();
	void SetDefaultFontCharSet(long);
	BOOL GetWantAllWindowInfoChanges();
	void SetWantAllWindowInfoChanges(BOOL);
	CString GetUrl();
	void SetUrl(LPCTSTR);
	long GetMousePointer();
	void SetMousePointer(long);
	CPicture1 GetMouseIcon();
	void SetMouseIcon(LPDISPATCH);

// Operations
public:
	double GetNumberRC(long nRow, long nCol);
	void SetNumberRC(long nRow, long nCol, double newValue);
	void FormatCellsDlg(long Pages);
	CString GetColText(long nCol);
	void SetColText(long nCol, LPCTSTR lpszNewValue);
	CString GetDefinedName(LPCTSTR Name);
	void SetDefinedName(LPCTSTR Name, LPCTSTR lpszNewValue);
	CString GetEntryRC(long nRow, long nCol);
	void SetEntryRC(long nRow, long nCol, LPCTSTR lpszNewValue);
	CString GetFormattedTextRC(long nRow, long nCol);
	CString GetFormulaRC(long nRow, long nCol);
	void SetFormulaRC(long nRow, long nCol, LPCTSTR lpszNewValue);
	long GetLastColForRow(long nRow);
	BOOL GetLogicalRC(long nRow, long nCol);
	void SetLogicalRC(long nRow, long nCol, BOOL bNewValue);
	CString GetRowText(long nRow);
	void SetRowText(long nRow, LPCTSTR lpszNewValue);
	CString GetTextRC(long nRow, long nCol);
	void SetTextRC(long nRow, long nCol, LPCTSTR lpszNewValue);
	short GetTypeRC(long nRow, long nCol);
	long GetObjCellType(long ObjID);
	void SetObjCellType(long ObjID, long nNewValue);
	long GetObjCellRow(long ObjID);
	void SetObjCellRow(long ObjID, long nNewValue);
	long GetObjCellCol(long ObjID);
	void SetObjCellCol(long ObjID, long nNewValue);
	long GetObjSelection(short nSelection);
	void EditPasteValues();
	void GetAlignment(short* pHorizontal, BOOL* pWordWrap, short* pVertical, short* pOrientation);
	void GetBorder(short* pLeft, short* pRight, short* pTop, short* pBottom, short* pShade, long* pcrLeft, long* pcrRight, long* pcrTop, long* pcrBottom);
	void GetFont(BSTR* pName, short* pSize, BOOL* pBold, BOOL* pItalic, BOOL* pUnderline, BOOL* pStrikeout, long* pcrColor, BOOL* pOutline, BOOL* pShadow);
	void GetLineStyle(short* pStyle, long* pcrColor, short* pWeight);
	void GetPattern(short* pPattern, long* pcrFG, long* pcrBG);
	void GetProtection(BOOL* pLocked, BOOL* pHidden);
	void GetTabbedText(long nR1, long nC1, long nR2, long nC2, BOOL bValuesOnly, long* phText);
	void SetTabbedText(long nStartRow, long nStartCol, long* pRows, long* pCols, BOOL bValuesOnly, LPCTSTR pText);
	void AddColPageBreak(long nCol);
	void AddPageBreak();
	void AddRowPageBreak(long nRow);
	void AddSelection(long nRow1, long nCol1, long nRow2, long nCol2);
	void Attach(LPCTSTR Title);
	void AttachToSS(long hSrcSS);
	void CalculationDlg();
	void CancelEdit();
	void CheckRecalc();
	void ClearClipboard();
	void ClearRange(long nRow1, long nCol1, long nRow2, long nCol2, long ClearType);
	void ColorPaletteDlg();
	void ColWidthDlg();
	void CopyAll(long hSrcSS);
	void CopyRange(long nDstR1, long nDstC1, long nDstR2, long nDstC2, long hSrcSS, long nSrcR1, long nSrcC1, long nSrcR2, long nSrcC2);
	void DefinedNameDlg();
	void DeleteDefinedName(LPCTSTR pName);
	void DeleteRange(long nRow1, long nCol1, long nRow2, long nCol2, long ShiftType);
	void Draw(long hDC, long x, long y, long cx, long cy, long nRow, long nCol, long* pRows, long* pCols, long nFixedRow, long nFixedCol, long nFixedRows, long nFixedCols);
	void EditClear(long ClearType);
	void EditCopy();
	void EditCopyDown();
	void EditCopyRight();
	void EditCut();
	void EditDelete(long ShiftType);
	void EditInsert(long InsertType);
	void EditPaste();
	void EndEdit();
	void FilePageSetupDlg();
	void FilePrint(BOOL bShowPrintDlg);
	void FilePrintSetupDlg();
	void FormatAlignmentDlg();
	void FormatBorderDlg();
	void FormatCurrency0();
	void FormatCurrency2();
	void FormatDefaultFontDlg();
	void FormatFixed();
	void FormatFixed2();
	void FormatFontDlg();
	void FormatFraction();
	void FormatGeneral();
	void FormatHmmampm();
	void FormatMdyy();
	void FormatNumberDlg();
	void FormatPatternDlg();
	void FormatPercent();
	void FormatScientific();
	void GetActiveCell(long* pRow, long* pCol);
	short GetColWidth(long nCol);
	void SetColWidth(long nCol, short nNewValue);
	short GetRowHeight(long nRow);
	void SetRowHeight(long nRow, short nNewValue);
	void GetDefaultFont(BSTR* pBuf, short* pSize);
	void GetHdrSelection(BOOL* pTopLeftHdr, BOOL* pRowHdr, BOOL* pColHdr);
	void GetIteration(BOOL* pIteration, short* pMaxIterations, double* pMaxChange);
	void GetPrintScale(short* pScale, BOOL* pFitToPage, long* pVPages, long* pHPages);
	void GetSelection(short nSelection, long* pR1, long* pC1, long* pR2, long* pC2);
	void GotoDlg();
	void HeapMin();
	void InitTable();
	void InsertRange(long nRow1, long nCol1, long nRow2, long nCol2, long InsertType);
	void LineStyleDlg();
	void MoveRange(long nRow1, long nCol1, long nRow2, long nCol2, long nRowOffset, long nColOffset);
	void ObjAddItem(long ObjID, LPCTSTR ItemText);
	void ObjAddSelection(long ObjID);
	void ObjBringToFront();
	void ObjDeleteItem(long ObjID, short nItem);
	void ObjGetCell(long ObjID, short* pControlCellType, long* pRow, long* pCol);
	void ObjGetPos(long ObjID, float* pX1, float* pY1, float* pX2, float* pY2);
	void ObjGetSelection(short nSelection, long* pID);
	void ObjInsertItem(long ObjID, short nItem, LPCTSTR ItemText);
	void ObjNameDlg();
	void ObjNew(short ObjType, float nX1, float nY1, float nX2, float nY2, long* pID);
	void ObjNewPicture(float nX1, float nY1, float nX2, float nY2, long* pID, long hMF, long nMapMode, long nWndExtentX, long nWndExtentY);
	void ObjOptionsDlg();
	void ObjPosToTwips(float nX1, float nY1, float nX2, float nY2, long* pX, long* pY, long* pCX, long* pCY, short* pShown);
	void ObjSendToBack();
	void ObjSetCell(long ObjID, short CellType, long nRow, long nCol);
	void ObjSetPicture(long ObjID, long hMF, short nMapMode, long nWndExtentX, long nWndExtentY);
	void ObjSetPos(long ObjID, float nX1, float nY1, float nX2, float nY2);
	void ObjSetSelection(long ObjID);
	void OpenFileDlg(LPCTSTR pTitle, long hWndParent, BSTR* pBuf);
	void ProtectionDlg();
	void RangeToTwips(long nRow1, long nCol1, long nRow2, long nCol2, long* pX, long* pY, long* pCX, long* pCY, short* pShown);
	void Read(LPCTSTR pPathName, short* pFileType);
	void ReadFromBlob(long hBlob, short nReservedBytes);
	void Recalc();
	void RemoveColPageBreak(long nCol);
	void RemovePageBreak();
	void RemoveRowPageBreak(long nRow);
	void RowHeightDlg();
	void SaveFileDlg(LPCTSTR pTitle, BSTR* pBuf, short* pFileType);
	void SaveWindowInfo();
	void SetActiveCell(long nRow, long nCol);
	void SetAlignment(short HAlign, BOOL bWordWrap, short VAlign, short nOrientation);
	void SetBorder(short nOutline, short nLeft, short nRight, short nTop, short nBottom, short nShade, unsigned long crOutline, unsigned long crLeft, unsigned long crRight, unsigned long crTop, unsigned long crBottom);
	void SetColWidth(long nCol1, long nCol2, short nWidth, BOOL bDefColWidth);
	void SetColWidthAuto(long nRow1, long nCol1, long nRow2, long nCol2, BOOL bSetDefaults);
	void SetDefaultFont(LPCTSTR Name, short nSize);
	void SetFont(LPCTSTR pName, short nSize, BOOL bBold, BOOL bItalic, BOOL bUnderline, BOOL bStrikeout, unsigned long crColor, BOOL bOutline, BOOL bShadow);
	void SetHdrSelection(BOOL bTopLeftHdr, BOOL bRowHdr, BOOL bColHdr);
	void SetIteration(BOOL bIteration, short nMaxIterations, double nMaxChange);
	void SetLineStyle(short nStyle, unsigned long crColor, short nWeight);
	void SetPattern(short nPattern, unsigned long crFG, unsigned long crBG);
	void SetPrintAreaFromSelection();
	void SetPrintScale(short nScale, BOOL bFitToPage, short nVPages, short nHPages);
	void SetPrintTitlesFromSelection();
	void SetProtection(BOOL bLocked, BOOL bHidden);
	void SetRowHeight(long nRow1, long nRow2, short nHeight, BOOL bDefRowHeight);
	void SetRowHeightAuto(long nRow1, long nCol1, long nRow2, long nCol2, BOOL bSetDefaults);
	void SetSelection(long nRow1, long nCol1, long nRow2, long nCol2);
	void ShowActiveCell();
	void Sort3(long nRow1, long nCol1, long nRow2, long nCol2, BOOL bSortByRows, long nKey1, long nKey2, long nKey3);
	void SortDlg();
	void StartEdit(BOOL bClear, BOOL bInCellEditFocus, BOOL bArrowsExitEditMode);
	void SwapTables(long hSS2);
	void TransactCommit();
	void TransactRollback();
	void TransactStart();
	void TwipsToRC(long x, long y, long* pRow, long* pCol);
	void SSUpdate();
	short SSVersion();
	void Write(LPCTSTR PathName, short FileType);
	void WriteToBlob(long* phBlob, short nReservedBytes);
	void SetRowHidden(long nRow1, long nRow2, BOOL bHidden);
	void SetColHidden(long nCol1, long nCol2, BOOL bHidden);
	void SetColWidthTwips(long nCol1, long nCol2, short nWidth, BOOL bDefColWidth);
	CString GetDefinedNameByIndex(short nName);
	CString GetSheetName(short nSheet);
	void SetSheetName(short nSheet, LPCTSTR lpszNewValue);
	unsigned long GetPaletteEntry(long nEntry);
	void SetPaletteEntry(long nEntry, unsigned long newValue);
	void EditInsertSheets();
	void EditDeleteSheets();
	void InsertSheets(long nSheet, long nSheets);
	void DeleteSheets(long nSheet, long nSheets);
	void Refresh();
	short GetColWidthTwips(long nCol);
	void SetColWidthTwips(long nCol, short nNewValue);
	long NextColPageBreak(long Col);
	long NextRowPageBreak(long Row);
	long ObjFirstID();
	long ObjNextID(long ObjID);
	short ObjGetItemCount(long ObjID);
	long ObjGetType(long ObjID);
	short ObjGetSelectionCount();
	CString FormatRCNr(long Row, long Col, BOOL DoAbsolute);
	long SS();
	CString GetObjItem(long ObjID, short nItem);
	void SetObjItem(long ObjID, short nItem, LPCTSTR lpszNewValue);
	CString GetObjItems(long ObjID);
	void SetObjItems(long ObjID, LPCTSTR lpszNewValue);
	CString GetObjName(long ObjID);
	void SetObjName(long ObjID, LPCTSTR lpszNewValue);
	CString GetObjText(long ObjID);
	void SetObjText(long ObjID, LPCTSTR lpszNewValue);
	short GetObjValue(long ObjID);
	void SetObjValue(long ObjID, short nNewValue);
	BOOL GetObjVisible(long ObjID);
	void SetObjVisible(long ObjID, BOOL bNewValue);
	long ObjNameToID(LPCTSTR Name);
	long DefinedNameCount();
	CString GetAutoFillItems(short nIndex);
	void SetAutoFillItems(short nIndex, LPCTSTR lpszNewValue);
	void ValidationRuleDlg();
	void SetValidationRule(LPCTSTR Rule, LPCTSTR Text);
	void GetValidationRule(BSTR* Rule, BSTR* Text);
	short AutoFillItemsCount();
	void CopyRangeEx(long nDstSheet, long nDstR1, long nDstC1, long nDstR2, long nDstC2, long hSrcSS, long nSrcSheet, long nSrcR1, long nSrcC1, long nSrcR2, long nSrcC2);
	void Sort(long nR1, long nC1, long nR2, long nC2, BOOL bSortByRows, const VARIANT& Keys);
	BOOL GetColHidden(long nCol);
	void SetColHidden(long nCol, BOOL bNewValue);
	BOOL GetRowHidden(long nRow);
	void SetRowHidden(long nRow, BOOL bNewValue);
	void DeleteAutoFillItems(short nIndex);
	void ODBCConnect(BSTR* pConnect, BOOL bShowErrors, short* pRetCode);
	void ODBCDisconnect();
	void ODBCQuery(BSTR* pQuery, long nRow, long nCol, BOOL bForceShowDlg, BOOL* pSetColNames, BOOL* pSetColFormats, BOOL* pSetColWidths, BOOL* pSetMaxRC, short* pRetCode);
	BOOL GetSheetSelected(long nSheet);
	void SetSheetSelected(long nSheet, BOOL bNewValue);
	void LaunchDesigner();
	void AboutBox();
	void PrintPreviewDC(long hDC, short nPage, short* pPages);
	void PrintPreview(long hWnd, long x, long y, long cx, long cy, short nPage, short* pPages);
	CString GetEntrySRC(long nSheet, long nRow, long nCol);
	void SetEntrySRC(long nSheet, long nRow, long nCol, LPCTSTR lpszNewValue);
	CString GetFormattedTextSRC(long nSheet, long nRow, long nCol);
	CString GetFormulaSRC(long nSheet, long nRow, long nCol);
	void SetFormulaSRC(long nSheet, long nRow, long nCol, LPCTSTR lpszNewValue);
	BOOL GetLogicalSRC(long nSheet, long nRow, long nCol);
	void SetLogicalSRC(long nSheet, long nRow, long nCol, BOOL bNewValue);
	double GetNumberSRC(long nSheet, long nRow, long nCol);
	void SetNumberSRC(long nSheet, long nRow, long nCol, double newValue);
	CString GetTextSRC(long nSheet, long nRow, long nCol);
	void SetTextSRC(long nSheet, long nRow, long nCol, LPCTSTR lpszNewValue);
	short GetTypeSRC(long nSheet, long nRow, long nCol);
	void WriteRange(long nSheet, long nRow1, long nCol1, long nRow2, long nCol2, LPCTSTR pPathName, short FileType);
	void InsertHTML(long nSheet, long nRow1, long nCol1, long nRow2, long nCol2, LPCTSTR pPathName, BOOL bDataOnly, LPCTSTR pAnchorName);
	void FilePrintEx(BOOL bShowPrintDlg, BOOL bPrintWorkbook);
	void FilePrintPreview();
	CString GetFormulaLocalRC(long nRow, long nCol);
	void SetFormulaLocalRC(long nRow, long nCol, LPCTSTR lpszNewValue);
	CString GetFormulaLocalSRC(long nSheet, long nRow, long nCol);
	void SetFormulaLocalSRC(long nSheet, long nRow, long nCol, LPCTSTR lpszNewValue);
	CString GetDefinedNameLocal(LPCTSTR Name);
	void SetDefinedNameLocal(LPCTSTR Name, LPCTSTR lpszNewValue);
	void CopyDataFromArray(long nSheet, long nRow1, long nCol1, long nRow2, long nCol2, BOOL bValuesOnly, const VARIANT& Array);
	void CopyDataToArray(long nSheet, long nRow1, long nCol1, long nRow2, long nCol2, BOOL bValuesOnly, const VARIANT& Array);
	void FindDlg();
	void ReplaceDlg();
	void Find(LPCTSTR FindWhat, long nSheet, long nRow1, long nCol1, long nRow2, long nCol2, short Flags, long* pFound);
	void Replace(LPCTSTR FindWhat, LPCTSTR ReplaceWith, long nSheet, long nRow1, long nCol1, long nRow2, long nCol2, short Flags, long* pFound, long* pReplaced);
	void ODBCError(BSTR* pSQLState, long* pNativeError, BSTR* pErrorMsg);
	void ODBCPrepare(LPCTSTR SQLStr, short* pRetCode);
	void ODBCBindParameter(long nParam, long nCol, short CDataType, short* pRetCode);
	void ODBCExecute(long nRow1, long nRow2, short* pRetCode);
	void InsertDlg();
	void ObjNewPolygon(float X1, float Y1, float X2, float Y2, long* pID, const VARIANT& ArrayX, const VARIANT& ArrayY, BOOL bClosed);
	void ObjSetPolygonPoints(long nID, const VARIANT& ArrayX, const VARIANT& ArrayY, BOOL bClosed);
	void DefRowHeightDlg();
	void DefColWidthDlg();
	void DeleteDlg();
	void FormatObjectDlg(long Pages);
	void OptionsDlg(long Pages);
	void FormatSheetDlg(long Pages, BOOL bDesignerMode);
	CString GetTabbedTextEx(long nR1, long nC1, long nR2, long nC2, BOOL bValuesOnly);
	CF1RangeRef SetTabbedTextEx(long nStartRow, long nStartCol, BOOL bValuesOnly, LPCTSTR pText);
	long ObjCreate(long ObjType, float nX1, float nY1, float nX2, float nY2);
	long ObjCreatePicture(float nX1, float nY1, float nX2, float nY2, long hMF, long nMapMode, long nWndExtentX, long nWndExtentY);
	long ReadEx(LPCTSTR pPathName);
	long WriteToBlobEx(short nReservedBytes);
	long ObjCreatePolygon(float X1, float Y1, float X2, float Y2, const VARIANT& ArrayX, const VARIANT& ArrayY, BOOL bClosed);
	CF1ObjPos ObjGetPosEx(long ObjID);
	short ObjPosShown(float X1, float Y1, float X2, float Y2);
	CF1RangeRef GetSelectionEx(short nSelection);
	CF1Rect ObjPosToTwipsEx(float X1, float Y1, float X2, float Y2);
	CF1Rect RangeToTwipsEx(long nRow1, long nCol1, long nRow2, long nCol2);
	short RangeShown(long nR1, long nC1, long nR2, long nC2);
	long TwipsToRow(long nTwips);
	long TwipsToCol(long nTwips);
	short PrintPreviewDCEx(long hDC, short nPage);
	short PrintPreviewEx(long hWnd, long x, long y, long cx, long cy, short nPage);
	void SaveFileDlgEx(LPCTSTR Title, LPDISPATCH pFileSpec);
	void ODBCConnectEx(LPDISPATCH pConnectObj, BOOL bShowErrors);
	void ODBCQueryEx(LPDISPATCH pQueryObj, long nRow, long nCol, BOOL bForceShowDlg);
	short ODBCPrepareEx(LPCTSTR SQLStr);
	short ODBCBindParameterEx(long nParam, long nCol, long CDataType);
	short ODBCExecuteEx(long nRow1, long nRow2);
	long FindEx(LPCTSTR FindWhat, long nSheet, long nRow1, long nCol1, long nRow2, long nCol2, short Flags);
	CF1ReplaceResults ReplaceEx(LPCTSTR FindWhat, LPCTSTR ReplaceWith, long nSheet, long nRow1, long nCol1, long nRow2, long nCol2, short Flags);
	CString OpenFileDlgEx(LPCTSTR pTitle, long hWndParent);
	CF1BookView CreateBookView();
	void EditPasteSpecial(long PasteWhat, long PasteOp);
	void PasteSpecialDlg();
	CF1NumberFormat GetFirstNumberFormat();
	void GetNextNumberFormat(LPDISPATCH pNumberFormat);
	CF1Rect RangeToPixelsEx(long nRow1, long nCol1, long nRow2, long nCol2);
	void WriteEx(LPCTSTR PathName, long FileType);
	void WriteRangeEx(long nSheet, long nRow1, long nCol1, long nRow2, long nCol2, LPCTSTR pPathName, long FileType);
	void GetFontEx(BSTR* pName, long* pCharSet, short* pSize, BOOL* pBold, BOOL* pItalic, BOOL* pUnderline, BOOL* pStrikeout, long* pcrColor, BOOL* pOutline, BOOL* pShadow);
	void SetFontEx(LPCTSTR pName, long CharSet, short nSize, BOOL bBold, BOOL bItalic, BOOL bUnderline, BOOL bStrikeout, unsigned long crColor, BOOL bOutline, BOOL bShadow);
	void GetDefaultFontEx(BSTR* pBuf, long* pCharSet, short* pSize);
	void SetDefaultFontEx(LPCTSTR Name, long CharSet, short nSize);
	CF1CellFormat CreateNewCellFormat();
	CF1CellFormat GetCellFormat();
	void SetCellFormat(LPDISPATCH CellFormat);
	CString ErrorNumberToText(long SSError);

protected:
	void OnClickVcf1ctrl1(long nRow, long nCol);
	void OnDblClickVcf1ctrl1(long nRow, long nCol);
  void OnMouseUpVcf1ctrl1(short Button, short Shift, long x, long y); 
  void OnRClickVcf1ctrl1(long nRow, long nCol);
	DECLARE_EVENTSINK_MAP()

};