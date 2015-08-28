
// DataSendDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DataSend.h"
#include "DataSendDlg.h"
#include "afxdialogex.h"
#include "CPLXPCI.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CPciProcess MyPCI;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDataSendDlg 对话框




CDataSendDlg::CDataSendDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDataSendDlg::IDD, pParent)
	, m_address(_T(""))
	, m_intup(_T(""))
	, m_data(_T(""))
	, m_intdown(_T(""))
	, m_delayn(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDataSendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ADD, m_address);
	DDX_Text(pDX, IDC_INT_UP, m_intup);
	DDX_Text(pDX, IDC_DATA, m_data);
	DDX_Text(pDX, IDC_INT_DOWN, m_intdown);
}

BEGIN_MESSAGE_MAP(CDataSendDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PCI_SEND, &CDataSendDlg::OnBnClickedPciSend)
	ON_BN_CLICKED(IDC_PCI_READ, &CDataSendDlg::OnBnClickedPciRead)
	ON_BN_CLICKED(IDC_INT_ON, &CDataSendDlg::OnBnClickedIntOn)
	ON_BN_CLICKED(IDC_INT_OFF, &CDataSendDlg::OnBnClickedIntOff)
	ON_BN_CLICKED(IDC_INTREAD, &CDataSendDlg::OnBnClickedIntread)
	ON_BN_CLICKED(IDC_BUTTON1, &CDataSendDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDataSendDlg 消息处理程序

BOOL CDataSendDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
		if(MyPCI.fnPciInit()!= TRUE )
	{
		//PCI初始化失败，关闭窗口
		MessageBox(_T("PCI初始化失败！"));
		//exit(NULL);
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDataSendDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDataSendDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDataSendDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDataSendDlg::OnBnClickedPciSend()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	USHORT data =static_cast<USHORT> (_tcstoul(m_data,0,16));
	ULONG address = _tcstoul(m_address,0,16);
	MyPCI.fnPciWriteMem(address,data);
	UpdateData(FALSE);
}


void CDataSendDlg::OnBnClickedPciRead()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	ULONG address = _tcstoul(m_address,0,16);
	USHORT data;
	MyPCI.fnPciReadMem(address,data);
	m_data = DectHex(data);
	UpdateData(FALSE);
}


void CDataSendDlg::OnBnClickedIntOn()
{
	// TODO: 在此添加控件通知处理程序代码
	
	m_intdown="0x5555";
	USHORT intdown = 0x5555;
	MyPCI.fnPciWriteMem(0x2004,intdown);		//全局传输地址映射中为0x2004 – 0x2007
	UpdateData(FALSE);
}


void CDataSendDlg::OnBnClickedIntOff()
{
	// TODO: 在此添加控件通知处理程序代码
	m_intdown="0xffff";
	USHORT intdown = 0xffff;
	MyPCI.fnPciWriteMem(0x2004,intdown);		//全局传输地址映射中为0x2004 – 0x2007
	UpdateData(FALSE);
}


void CDataSendDlg::OnBnClickedIntread()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	USHORT intup;
	MyPCI.fnPciReadMem(0x2000,intup);		//全局传输地址映射中为0x2000 – 0x2003
	m_intup = DectHex(intup);
	UpdateData(FALSE);
}
void CDataSendDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(MyPCI.fnPciClose())
	{
		MessageBox(_T("PCI关闭遇到问题"));
	}else ;
}

CString CDataSendDlg::DectHex(USHORT conv)
{
	CString Result = _T("");
	TCHAR res[sizeof(USHORT)+5] = _T("");//此处数组的长度至少为9，否则会出现数组越界的错误
	UINT count = 0;
	UINT divi = 16;
	UINT tem = 0;

	if (conv>65535)
	{
		MessageBox(_T("Error!Out of bound!"));
	} 
	else
	{
		while(conv>=divi)
		{
			tem=conv % divi;
			if (tem>9)
			{
				res[count] = char(tem+55);
			} 
			else
			{
				res[count] = char(tem+48);
			}
			
			conv -= tem;
			conv /= divi;
			count ++;
		}
		
		if (conv>9)
		{
			res[count] = char(conv+55);
		} 
		else
		{
			res[count] = char(conv+48);
		}
		
		count ++;
		res[count]='\0';
		Result = res;
	}
	Result.MakeReverse();
	return Result;
}






void CDataSendDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	USHORT intdown = 0x5555;
	MyPCI.fnPciWriteMem(0x2004,intdown);		//全局传输地址映射中为0x2004 – 0x2007

	//delay();	//延时

	intdown = 0xffff;
	MyPCI.fnPciWriteMem(0x2004,intdown);		//全局传输地址映射中为0x2004 – 0x2007
	MessageBox(_T("开关完毕"));
}
