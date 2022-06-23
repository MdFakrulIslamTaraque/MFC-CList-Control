
// MFCListControlDlg.h : header file
//

#pragma once


// CMFCListControlDlg dialog
class CMFCListControlDlg : public CDialogEx
{
// Construction
public:
	CMFCListControlDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCLISTCONTROL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list_control_up;
	afx_msg void OnLvnEndlabeleditListUp(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonDelete();
};
