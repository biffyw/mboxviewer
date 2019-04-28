// OpenContainingFolderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mboxview.h"
#include "OpenContainingFolderDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#undef THIS_FILE
#define THIS_FILE __FILE__
#define new DEBUG_NEW
#endif

// OpenContainingFolderDlg dialog

IMPLEMENT_DYNAMIC(OpenContainingFolderDlg, CDialogEx)

OpenContainingFolderDlg::OpenContainingFolderDlg(CString &text, bool blockOpenFileOption, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OPEN_FOLDER, pParent)
{
	m_text = text;
	m_blockOpenFileOption = blockOpenFileOption;
}

OpenContainingFolderDlg::~OpenContainingFolderDlg()
{
}

void OpenContainingFolderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(OpenContainingFolderDlg, CDialogEx)
ON_BN_CLICKED(IDYES, &OpenContainingFolderDlg::OnBnClickedYes)
END_MESSAGE_MAP()


// OpenContainingFolderDlg message handlers

BOOL OpenContainingFolderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	if ((m_blockOpenFileOption == TRUE) && GetSafeHwnd()) {
		CWnd *p = GetDlgItem(IDYES);
		if (p) {
			p->EnableWindow(FALSE);
		}
	}
	UpdateData(TRUE);

	//SetDlgItemText(IDC_STATIC, "Desired Text String")

	GetDlgItem(IDC_STATIC)->SetWindowText(m_text);

	;// SetWindowText(caption);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void OpenContainingFolderDlg::OnBnClickedYes()
{
	// TODO: Add your control notification handler code here
	EndDialog(IDYES);
}
