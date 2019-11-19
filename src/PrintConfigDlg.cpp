//
//////////////////////////////////////////////////////////////////
//
//  Windows Mbox Viewer is a free tool to view, search and print mbox mail archives..
//
// Source code and executable can be downloaded from
//  https://sourceforge.net/projects/mbox-viewer/  and
//  https://github.com/eneam/mboxviewer
//
//  Copyright(C) 2019  Enea Mansutti, Zbigniew Minciel
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the version 3 of GNU Affero General Public License
//  as published by the Free Software Foundation; 
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the GNU
//  Library General Public License for more details.
//
//  You should have received a copy of the GNU Library General Public
//  License along with this program; if not, write to the
//  Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
//  Boston, MA  02110 - 1301, USA.
//
//////////////////////////////////////////////////////////////////
//

// PrintConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mboxview.h"
#include "PrintConfigDlg.h"
#include "afxdialogex.h"
#include "MboxMail.h"


// PrintConfigDlg dialog

IMPLEMENT_DYNAMIC(PrintConfigDlg, CDialogEx)

PrintConfigDlg::PrintConfigDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PRINT_DLG, pParent)
{
	m_NamePatternParams.SetDflts();
}

PrintConfigDlg::~PrintConfigDlg()
{
}

void PrintConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_FILE_DATE, m_NamePatternParams.m_bDate);
	DDX_Check(pDX, IDC_FILE_TIME, m_NamePatternParams.m_bTime);
	DDX_Check(pDX, IDC_FILE_FROM, m_NamePatternParams.m_bFrom);
	DDX_Check(pDX, IDC_FILE_TO, m_NamePatternParams.m_bTo);
	DDX_Check(pDX, IDC_FILE_SUBJECT, m_NamePatternParams.m_bSubject);
	DDX_Check(pDX, IDC_FILE_UNIQUE_ID, m_NamePatternParams.m_bUniqueId);
	DDX_Text(pDX, IDC_FILE_NAME_ADJUSTED_MAX_SIZE, m_NamePatternParams.m_nFileNameFormatSizeLimit);
	DDX_Text(pDX, IDC_FILE_NAME_MAX_SIZE, m_NamePatternParams.m_nWantedFileNameFormatSizeLimit);
	DDX_Radio(pDX, IDC_PRT_DO_NOT_PROMPT, m_NamePatternParams.m_bPrintDialog);
	DDX_Radio(pDX, IDC_HTML2PDF_SCRIPT_TYPE, m_NamePatternParams.m_bScriptType);
	DDX_Text(pDX, IDC_CHROME_EXE_PATH, m_NamePatternParams.m_ChromeBrowserPath);
	DDX_Text(pDX, IDC_HTML2PDF_SCRIPT_PATH, m_NamePatternParams.m_UserDefinedScriptPath);
	DDX_Check(pDX, IDC_SEPARATE_PDF, m_NamePatternParams.m_bPrintToSeparatePDFFiles);
	DDX_Check(pDX, IDC_SEPARATE_HTML, m_NamePatternParams.m_bPrintToSeparateHTMLFiles);
	DDX_Check(pDX, IDC_ADD_HDR_COLOR, m_NamePatternParams.m_bAddBackgroundColorToMailHeader);
	DDX_Check(pDX, IDC_PAGE_BREAK, m_NamePatternParams.m_bAddBreakPageAfterEachMailInPDF);
	DDX_Check(pDX, IDC_KEEP_BODY_BKGRND_COLOR, m_NamePatternParams.m_bKeepMailBodyBackgroundColor);

	int deb = 1;
}


BEGIN_MESSAGE_MAP(PrintConfigDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &PrintConfigDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_FILE_NAME_MAX_SIZE, &PrintConfigDlg::OnEnChangeFileNameMaxSize)
	ON_BN_CLICKED(IDC_PRT_PAGE_SETP, &PrintConfigDlg::OnBnClickedPrtPageSetp)
	ON_BN_CLICKED(IDC_HTML2PDF_SCRIPT_TYPE, &PrintConfigDlg::OnBnClickedHtml2pdfScriptType)
	ON_BN_CLICKED(IDC_RADIO3, &PrintConfigDlg::OnBnClickedRadio3)
END_MESSAGE_MAP()


// PrintConfigDlg message handlers


void PrintConfigDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData();
#if 0
	// Introduced UniqueId so no need for thos ??
	if ((m_NamePatternParams.m_bDate == 0) &&
		(m_NamePatternParams.m_bTime == 0) &&
		(m_NamePatternParams.m_bFrom == 0) &&
		(m_NamePatternParams.m_bTo == 0) &&
		(m_NamePatternParams.m_bSubject == 0)
		)
	{
		CString txt;
		txt.Format("No fields are checked!");
		AfxMessageBox(txt, MB_OK | MB_ICONHAND);
		return;
	}
#endif

	NamePatternParams::UpdateFilePrintconfig(m_NamePatternParams);

	CDialogEx::OnOK();
}

BOOL PrintConfigDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	UpdateData(TRUE);

	if (GetSafeHwnd()) {
		CWnd *p = GetDlgItem(IDC_FILE_UNIQUE_ID);
		if (p) {
			((CButton*)p)->SetCheck(1);
			p->EnableWindow(FALSE);
		}
		p = GetDlgItem(IDC_FILE_NAME_ADJUSTED_MAX_SIZE);
		if (p) {
			NamePatternParams::UpdateFilePrintconfig(m_NamePatternParams);
			CString adjustedMaxSize;
			adjustedMaxSize.Format("%d", m_NamePatternParams.m_nFileNameFormatSizeLimit);
			((CButton*)p)->SetWindowText(adjustedMaxSize);
			p->EnableWindow(FALSE);
		}

		p = GetDlgItem(IDC_KEEP_BODY_BKGRND_COLOR);
		if (p) {
			if (m_NamePatternParams.m_bScriptType == 0)
			{
				((CButton*)p)->SetCheck(1);
				p->EnableWindow(FALSE);
			}
			else
				p->EnableWindow(TRUE);
		}
	}

	//UpdateData(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void PrintConfigDlg::OnEnChangeFileNameMaxSize()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	NamePatternParams::UpdateFilePrintconfig(m_NamePatternParams);
	if (GetSafeHwnd())
	{
		CString wantedMaxSize;
		CWnd *p = GetDlgItem(IDC_FILE_NAME_MAX_SIZE);
		if (p) {
			((CButton*)p)->GetWindowText(wantedMaxSize);
			int nWantedMaxSize = atoi((LPCSTR)wantedMaxSize);
			if (nWantedMaxSize > 260)
			{
				wantedMaxSize = "260";
				((CButton*)p)->SetWindowText(wantedMaxSize);
			}
		}
		else
			return;

		m_NamePatternParams.m_nWantedFileNameFormatSizeLimit = atoi((LPCSTR)wantedMaxSize);
		NamePatternParams::UpdateFilePrintconfig(m_NamePatternParams);
		p = GetDlgItem(IDC_FILE_NAME_ADJUSTED_MAX_SIZE);
		if (p) {
			CString adjustedMaxSize;
			adjustedMaxSize.Format("%d", m_NamePatternParams.m_nFileNameFormatSizeLimit);
			((CButton*)p)->SetWindowText(adjustedMaxSize);
			p->EnableWindow(FALSE);
		}
	}
	int deb = 1;
}

void NamePatternParams::SetDflts()
{
	m_bDate = TRUE;
	m_bTime = TRUE;
	m_bFrom = TRUE;
	m_bTo = TRUE;
	m_bSubject = TRUE;
	m_bUniqueId = TRUE;
	m_nFileNameFormatSizeLimit = 260;
	m_nWantedFileNameFormatSizeLimit = m_nFileNameFormatSizeLimit;
	m_bPrintDialog = 1;
	m_bScriptType = 0;
	m_ChromeBrowserPath = "C:\\Program Files (x86)\\Google\\Chrome\\Application\\chrome.exe";
	m_bPrintToSeparatePDFFiles = FALSE;
	m_bPrintToSeparateHTMLFiles = FALSE;
	m_bPrintToSeparateTEXTFiles = FALSE;

	m_bAddBackgroundColorToMailHeader = TRUE;
	m_bAddBreakPageAfterEachMailInPDF = FALSE;
	m_bKeepMailBodyBackgroundColor = TRUE;
	
	char *pValue;
	errno_t  er = _get_pgmptr(&pValue);
	CString procFullPath;
	if ((er == 0) && pValue)
		procFullPath.Append(pValue);

	CString driveName;
	CString directory;
	CString fileNameBase;
	CString fileNameExtention;

	MboxMail::SplitFilePath(procFullPath, driveName, directory, fileNameBase, fileNameExtention);

	CString procPath;
	BOOL ret = CPathGetPath(procFullPath, procPath);

	m_UserDefinedScriptPath = procPath + "\\scripts\\HTML2PDF-single-wkhtmltopdf.cmd";

	int deb = 1;
}

void NamePatternParams::Copy(NamePatternParams &src)
{
	if (this == &src)
		return;

	m_bDate = src.m_bDate;
	m_bTime = src.m_bTime;
	m_bFrom = src.m_bFrom;
	m_bTo = src.m_bTo;
	m_bSubject = src.m_bSubject;
	m_bUniqueId = src.m_bUniqueId;
	m_nFileNameFormatSizeLimit = src.m_nFileNameFormatSizeLimit;
	m_nWantedFileNameFormatSizeLimit = src.m_nWantedFileNameFormatSizeLimit;
	m_bPrintDialog = src.m_bPrintDialog;
	m_bScriptType = src.m_bScriptType;
	m_ChromeBrowserPath = src.m_ChromeBrowserPath;
	m_UserDefinedScriptPath = src.m_UserDefinedScriptPath;
	m_bPrintToSeparatePDFFiles = src.m_bPrintToSeparatePDFFiles;
	m_bPrintToSeparateHTMLFiles = src.m_bPrintToSeparateHTMLFiles;
	m_bPrintToSeparateTEXTFiles = src.m_bPrintToSeparateTEXTFiles;
	m_bAddBackgroundColorToMailHeader = src.m_bAddBackgroundColorToMailHeader;
	m_bAddBreakPageAfterEachMailInPDF = src.m_bAddBreakPageAfterEachMailInPDF;
	m_bKeepMailBodyBackgroundColor = src.m_bKeepMailBodyBackgroundColor;
}

void NamePatternParams::UpdateRegistry(NamePatternParams &current, NamePatternParams &updated)
{
	if (&current == &updated)
		return;

	if (updated.m_bDate != current.m_bDate) {
		CProfile::_WriteProfileInt(HKEY_CURRENT_USER, sz_Software_mboxview, "printFileNameDate", updated.m_bDate);
	}
	if (updated.m_bTime != current.m_bTime) {
		CProfile::_WriteProfileInt(HKEY_CURRENT_USER, sz_Software_mboxview, "printFileNameTime", updated.m_bTime);
	}
	if (updated.m_bFrom != current.m_bFrom) {
		CProfile::_WriteProfileInt(HKEY_CURRENT_USER, sz_Software_mboxview, "printFileNameFrom", updated.m_bFrom);
	}
	if (updated.m_bTo != current.m_bTo) {
		CProfile::_WriteProfileInt(HKEY_CURRENT_USER, sz_Software_mboxview, "printFileNameTo", updated.m_bTo);
	}
	if (updated.m_bSubject != current.m_bSubject) {
		CProfile::_WriteProfileInt(HKEY_CURRENT_USER, sz_Software_mboxview, "printFileNameSubject", updated.m_bSubject);
	}
	if (updated.m_nFileNameFormatSizeLimit != current.m_nFileNameFormatSizeLimit) {
		CProfile::_WriteProfileInt(HKEY_CURRENT_USER, sz_Software_mboxview, "printFileNameMaxLength", updated.m_nWantedFileNameFormatSizeLimit);
	}
	if (updated.m_bPrintDialog != current.m_bPrintDialog) {
		CProfile::_WriteProfileInt(HKEY_CURRENT_USER, sz_Software_mboxview, "printDialogType", updated.m_bPrintDialog);
	}
	if (updated.m_bScriptType != current.m_bScriptType) {
		CProfile::_WriteProfileInt(HKEY_CURRENT_USER, sz_Software_mboxview, "printHTML2PDFScriptType", updated.m_bScriptType);
	}
	if (updated.m_ChromeBrowserPath != current.m_ChromeBrowserPath) {
		CProfile::_WriteProfileString(HKEY_CURRENT_USER, sz_Software_mboxview, "printChromeBrowserPath", updated.m_ChromeBrowserPath);
	}
	if (updated.m_UserDefinedScriptPath != current.m_UserDefinedScriptPath) {
		CProfile::_WriteProfileString(HKEY_CURRENT_USER, sz_Software_mboxview, "printUserDefinedScriptPath", updated.m_UserDefinedScriptPath);
	}
	if (updated.m_bAddBackgroundColorToMailHeader != current.m_bAddBackgroundColorToMailHeader) {
		CProfile::_WriteProfileInt(HKEY_CURRENT_USER, sz_Software_mboxview, "printMailHdrBackgroundColor", updated.m_bAddBackgroundColorToMailHeader);
	}
	if (updated.m_bAddBreakPageAfterEachMailInPDF != current.m_bAddBreakPageAfterEachMailInPDF) {
		CProfile::_WriteProfileInt(HKEY_CURRENT_USER, sz_Software_mboxview, "printPDFPageBreakAfterEachMail", updated.m_bAddBreakPageAfterEachMailInPDF);
	}
	if (updated.m_bKeepMailBodyBackgroundColor != current.m_bKeepMailBodyBackgroundColor) {
		CProfile::_WriteProfileInt(HKEY_CURRENT_USER, sz_Software_mboxview, "printMailBodyBackgroundColor", updated.m_bKeepMailBodyBackgroundColor);
	}
}


void NamePatternParams::LoadFromRegistry()
{
	BOOL retval;
	DWORD bDate, bTime, bFrom, bTo, bSubject, bPrintDialog, bScriptType, nWantedFileNameFormatSizeLimit;
	DWORD bAddBackgroundColorToMailHeader, bAddBreakPageAfterEachMailInPDF, bKeepMailBodyBackgroundColor;
	CString chromeBrowserPath;
	CString userDefinedScriptPath;

	if (retval = CProfile::_GetProfileInt(HKEY_CURRENT_USER, sz_Software_mboxview, _T("printFileNameDate"), bDate))
		m_bDate = bDate;
	if (retval = CProfile::_GetProfileInt(HKEY_CURRENT_USER, sz_Software_mboxview, _T("printFileNameTime"), bTime))
		m_bTime = bTime;
	if (retval = CProfile::_GetProfileInt(HKEY_CURRENT_USER, sz_Software_mboxview, _T("printFileNameFrom"), bFrom))
		m_bFrom = bFrom;
	if (retval = CProfile::_GetProfileInt(HKEY_CURRENT_USER, sz_Software_mboxview, _T("printFileNameTo"), bTo))
		m_bTo = bTo;
	if (retval = CProfile::_GetProfileInt(HKEY_CURRENT_USER, sz_Software_mboxview, _T("printFileNameSubject"), bSubject))
		m_bSubject = bSubject;
	if (retval = CProfile::_GetProfileInt(HKEY_CURRENT_USER, sz_Software_mboxview, _T("printFileNameMaxLength"), nWantedFileNameFormatSizeLimit))
		m_nWantedFileNameFormatSizeLimit = nWantedFileNameFormatSizeLimit;
	if (retval = CProfile::_GetProfileInt(HKEY_CURRENT_USER, sz_Software_mboxview, _T("printDialogType"), bPrintDialog))
		m_bPrintDialog = bPrintDialog;
	if (retval = CProfile::_GetProfileInt(HKEY_CURRENT_USER, sz_Software_mboxview, _T("printHTML2PDFScriptType"), bScriptType))
		m_bScriptType = bScriptType;
	if (retval = CProfile::_GetProfileString(HKEY_CURRENT_USER, sz_Software_mboxview, _T("printChromeBrowserPath"), chromeBrowserPath))
		m_ChromeBrowserPath = chromeBrowserPath;
	if (retval = CProfile::_GetProfileString(HKEY_CURRENT_USER, sz_Software_mboxview, _T("printUserDefinedScriptPath"), userDefinedScriptPath))
		m_UserDefinedScriptPath = userDefinedScriptPath;
	if (retval = CProfile::_GetProfileInt(HKEY_CURRENT_USER, sz_Software_mboxview, _T("printMailHdrBackgroundColor"), bAddBackgroundColorToMailHeader))
		m_bAddBackgroundColorToMailHeader = bAddBackgroundColorToMailHeader;
	if (retval = CProfile::_GetProfileInt(HKEY_CURRENT_USER, sz_Software_mboxview, _T("printPDFPageBreakAfterEachMail"), bAddBreakPageAfterEachMailInPDF))
		m_bAddBreakPageAfterEachMailInPDF = bAddBreakPageAfterEachMailInPDF;
	if (retval = CProfile::_GetProfileInt(HKEY_CURRENT_USER, sz_Software_mboxview, _T("printMailBodyBackgroundColor"), bKeepMailBodyBackgroundColor))
		m_bKeepMailBodyBackgroundColor = bKeepMailBodyBackgroundColor;
}

void NamePatternParams::UpdateFilePrintconfig(struct NamePatternParams &namePatternParams)
{
	CString printCacheName;
	MboxMail::GetPrintCachePath(printCacheName);
	int maxFileSize = _MAX_PATH - printCacheName.GetLength() - 1 - 4 - 14; // -1 for flder separatorr, -4 for suffix, -14 for fudge factor (HHML_GROUP and PDF_GROUP)
	if (maxFileSize < 0)
		maxFileSize = 0;

	if (namePatternParams.m_nWantedFileNameFormatSizeLimit > maxFileSize)
	{
		namePatternParams.m_nFileNameFormatSizeLimit = maxFileSize;
	}
	else
		namePatternParams.m_nFileNameFormatSizeLimit = namePatternParams.m_nWantedFileNameFormatSizeLimit;

}


void PrintConfigDlg::OnBnClickedPrtPageSetp()
{
	// TODO: Add your control notification handler code here
	NMsgView::PrintToPrinterPageSetup(this);
}


void PrintConfigDlg::OnBnClickedHtml2pdfScriptType()
{
	// TODO: Add your control notification handler code here
	if (GetSafeHwnd())
	{
		CWnd *p = GetDlgItem(IDC_KEEP_BODY_BKGRND_COLOR);
		if (p) {
			((CButton*)p)->SetCheck(1);
			p->EnableWindow(FALSE);
		}
	}
	int deb = 1;
}


void PrintConfigDlg::OnBnClickedRadio3()
{
	// TODO: Add your control notification handler code here
	if (GetSafeHwnd())
	{
		CWnd *p = GetDlgItem(IDC_KEEP_BODY_BKGRND_COLOR);
		if (p) {
			p->EnableWindow(TRUE);
		}
	}
	int deb = 1;
}
