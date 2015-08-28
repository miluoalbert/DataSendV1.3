
// DataSendDlg.cpp : ʵ���ļ�
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
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CDataSendDlg �Ի���




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


// CDataSendDlg ��Ϣ�������

BOOL CDataSendDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
		if(MyPCI.fnPciInit()!= TRUE )
	{
		//PCI��ʼ��ʧ�ܣ��رմ���
		MessageBox(_T("PCI��ʼ��ʧ�ܣ�"));
		//exit(NULL);
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDataSendDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDataSendDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDataSendDlg::OnBnClickedPciSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	USHORT data =static_cast<USHORT> (_tcstoul(m_data,0,16));
	ULONG address = _tcstoul(m_address,0,16);
	MyPCI.fnPciWriteMem(address,data);
	UpdateData(FALSE);
}


void CDataSendDlg::OnBnClickedPciRead()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	ULONG address = _tcstoul(m_address,0,16);
	USHORT data;
	MyPCI.fnPciReadMem(address,data);
	m_data = DectHex(data);
	UpdateData(FALSE);
}


void CDataSendDlg::OnBnClickedIntOn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	m_intdown="0x5555";
	USHORT intdown = 0x5555;
	MyPCI.fnPciWriteMem(0x2004,intdown);		//ȫ�ִ����ַӳ����Ϊ0x2004 �C 0x2007
	UpdateData(FALSE);
}


void CDataSendDlg::OnBnClickedIntOff()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_intdown="0xffff";
	USHORT intdown = 0xffff;
	MyPCI.fnPciWriteMem(0x2004,intdown);		//ȫ�ִ����ַӳ����Ϊ0x2004 �C 0x2007
	UpdateData(FALSE);
}


void CDataSendDlg::OnBnClickedIntread()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	USHORT intup;
	MyPCI.fnPciReadMem(0x2000,intup);		//ȫ�ִ����ַӳ����Ϊ0x2000 �C 0x2003
	m_intup = DectHex(intup);
	UpdateData(FALSE);
}
void CDataSendDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(MyPCI.fnPciClose())
	{
		MessageBox(_T("PCI�ر���������"));
	}else ;
}

CString CDataSendDlg::DectHex(USHORT conv)
{
	CString Result = _T("");
	TCHAR res[sizeof(USHORT)+5] = _T("");//�˴�����ĳ�������Ϊ9��������������Խ��Ĵ���
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	USHORT intdown = 0x5555;
	MyPCI.fnPciWriteMem(0x2004,intdown);		//ȫ�ִ����ַӳ����Ϊ0x2004 �C 0x2007

	//delay();	//��ʱ

	intdown = 0xffff;
	MyPCI.fnPciWriteMem(0x2004,intdown);		//ȫ�ִ����ַӳ����Ϊ0x2004 �C 0x2007
	MessageBox(_T("�������"));
}
