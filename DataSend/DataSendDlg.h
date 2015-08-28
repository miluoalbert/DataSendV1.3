
// DataSendDlg.h : ͷ�ļ�
//

#pragma once


// CDataSendDlg �Ի���
class CDataSendDlg : public CDialogEx
{
// ����
public:
	CDataSendDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DATASEND_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
