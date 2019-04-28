#if !defined(_OPEN_CONTAINING_FOLDER_DLG_)
#define _OPEN_CONTAINING_FOLDER_DLG_

#pragma once


// OpenContainingFolderDlg dialog

class OpenContainingFolderDlg : public CDialogEx
{
	DECLARE_DYNAMIC(OpenContainingFolderDlg)

public:
	OpenContainingFolderDlg(CString &text, bool blockOpenFileOption=FALSE, CWnd* pParent=0);
	virtual ~OpenContainingFolderDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPEN_FOLDER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	CString m_text;
	BOOL m_blockOpenFileOption;
	afx_msg void OnBnClickedYes();
};

#endif // _OPEN_CONTAINING_FOLDER_DLG_
