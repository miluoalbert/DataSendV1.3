#ifndef __CPLXPCI_H__
#define __CPLXPCI_H__
#include "PlxApi.h"
#include <vector>
#include <iostream>
#pragma comment(lib, "PlxApi.lib")


#define VENDOR_ID 0x10B5
#define DEVICE_ID 0x9054
#define REGISTER_SPACE0_OFFSET 0x04
#define REGISTER_SPACE1_OFFSET 0xF4
#define REGISTER_SPACE_ENABLE_MASK 0x00000001
#define REGISTER_SPACE_DISABLE_MASK 0x00000000
#define BAR_2_SPACE_OFFSET 2
#define BAR_3_SPACE_OFFSET 3
#define SELECT_1ST_DEVICE 0

#define PCI_SET_BUSY while(m_bIsBusy) ;m_bIsBusy = true
#define PCI_SET_IDLE fnDelay();m_bIsBusy = false
using namespace std;


class CPciProcess
{
private:
	PLX_DEVICE_KEY pKey;
	PLX_DEVICE_OBJECT pDevice;
	PLX_INTERRUPT pPlxIntr;
	PLX_NOTIFY_OBJECT pEvent;
	unsigned int m_uiVendorId;
	unsigned int m_uiDeviceId;
	
public:
	CPciProcess();//���캯�����ڹ��������Ӧ��ʵ��Ӳ������ֵ���趨
	~CPciProcess();
	bool m_bIsBusy;
	bool fnPciInit();//PCI��ʼ������
	bool fnPciReadMem(ULONG offset,unsigned int len,unsigned char* data );//���ڴ�
	bool fnPciReadMem(ULONG offset,ULONG& data);
	bool fnPciReadMem(ULONG offset, USHORT& data);			//��һ�ζ��ڴ�  -----���by Albert
	bool fnPciWriteMem(ULONG offset, unsigned char* data,unsigned int len);//д�ڴ�
	bool fnPciWriteMem(ULONG offset, ULONG data);
	bool fnPciWriteMem(ULONG offset, USHORT data); //bool fnPciWriteMem(ULONG offset, short data);    ------����by Albert
	//bool fnPciWriteMemInt(ULONG offset, ULONG data);
	ULONG fnPciReadReg(ULONG offset);//���Ĵ���
	void fnPciWriteReg(ULONG offset, unsigned char* data);//д�ڴ�
	bool fnPciClose();//�ر�PCI�豸
	bool fnPciStartThread();//�����ж��߳�
	static void fnDelay();
	static UINT fnPciIntThread(LPVOID pParam);//��ʼ���߳�
	//UINT fnPciIntThread(LPVOID pParam);//��ʼ���߳�
	CWinThread* CWTThread;	

	static UINT fnExeThread(LPVOID pPV);	//ִ��������߳�

	CWinThread* ExecuteThread;

	bool m_bExeThreadIsAlive;

	// �¼�����
	HANDLE m_hShutdownEvent;
	HANDLE m_hExeEvent;
	HANDLE m_hEventArray[2];
};
#endif