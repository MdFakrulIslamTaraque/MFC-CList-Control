
// MFCListControlDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCListControl.h"
#include "MFCListControlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCListControlDlg dialog



CMFCListControlDlg::CMFCListControlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCLISTCONTROL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCListControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_Up, m_list_control_up);
}

BEGIN_MESSAGE_MAP(CMFCListControlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST_Up, &CMFCListControlDlg::OnLvnEndlabeleditListUp)
	ON_BN_CLICKED(IDC_BUTTON_Delete, &CMFCListControlDlg::OnBnClickedButtonDelete)
END_MESSAGE_MAP()


// CMFCListControlDlg message handlers

BOOL CMFCListControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog 
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	 
	// TODO: Add extra initialization here


	//adding chec Box
	DWORD dwCheckBox = m_list_control_up.GetExtendedStyle();
	m_list_control_up.SetExtendedStyle(dwCheckBox | LVS_EX_CHECKBOXES | LVS_EX_BORDERSELECT);


	static CImageList imageList;
	imageList.Create(16, 16, ILC_COLOR32,5,0);
	
	CString strItem = _T("");
	for (int i = 0; i < 5; ++i)
	{
		imageList.Add(AfxGetApp()->LoadIcon(IDI_ICON1 + i));
		strItem.Format(_T("%d th Item"), i);
		m_list_control_up.InsertItem(i,strItem,i);
	}

	m_list_control_up.SetImageList(&imageList, LVSIL_SMALL);

	//another way of adding single element 
	LVITEM item;
	::ZeroMemory(&item, sizeof(item));
	item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	item.pszText = _T("extra added");
	item.iImage = 4;
	item.state = LVIS_SELECTED | LVIS_FOCUSED;
	m_list_control_up.InsertItem(&item);

	//adding column
	m_list_control_up.InsertColumn(0, _T("Name"), LVCFMT_LEFT, 200);
	m_list_control_up.InsertColumn(1, _T("Description"), LVCFMT_LEFT, 300);
	m_list_control_up.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);


	m_list_control_up.SetItemText(5, 0, _T("Replaced Name1"));
	m_list_control_up.SetItemText(5, 1, _T("Test String!"));


	return TRUE;  // return TRUE  unless you set the focus to a control
} 

void CMFCListControlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCListControlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCListControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCListControlDlg::OnLvnEndlabeleditListUp(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLVDISPINFO* pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	
	//to get edit control, first select the item,pause, then click once (don't just double click)
	CString strText = _T("");
	CEdit* pEdit = m_list_control_up.GetEditControl();
	pEdit->GetWindowTextW(strText);
	m_list_control_up.SetItemText(pDispInfo->item.iItem, 0, strText);
	*pResult = 0;
}


void CMFCListControlDlg::OnBnClickedButtonDelete()
{
	int nSelectedItem = m_list_control_up.GetItemCount();
	for (int i = nSelectedItem; i >= 0; i--)
	{
		if (m_list_control_up.GetCheck(i))
			m_list_control_up.DeleteItem(i);
	}
}
