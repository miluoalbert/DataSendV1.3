
// DataSendDlg.h : 头文件
//

#pragma once


// CDataSendDlg 对话框
class CDataSendDlg : public CDialogEx
{
// 构造
public:
	CDataSendDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DATASEND_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg CString DectHex(USHORT);
	DECLARE_MESSAGE_MAP()
public:
	CString m_address;
	CString m_intup;
	CString m_data;
	CString m_intdown;
	afx_msg void OnBnClickedPciSend();
	
	afx_msg void OnBnClickedPciRead();
	afx_msg void OnBnClickedIntOn();
	afx_msg void OnBnClickedIntOff();
	afx_msg void OnBnClickedIntread();
	afx_msg void OnClose();
	int m_delayn;
	afx_msg void OnBnClickedButton1();
};
