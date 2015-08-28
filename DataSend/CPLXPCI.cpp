#include "stdafx.h"
#include "CPLXPCI.h"

//#include "EX_SDMDlg.h"
#include "mmsystem.h" 
#pragma comment(lib, "winmm.lib")
//���캯��
CPciProcess::CPciProcess()
{
	m_uiVendorId = VENDOR_ID;
	m_uiDeviceId = DEVICE_ID;
	memset(&pKey, PCI_FIELD_IGNORE, sizeof(PLX_DEVICE_KEY));
	memset(&pPlxIntr,0,sizeof(PLX_INTERRUPT));
	memset(&pDevice,0,sizeof(PLX_DEVICE_OBJECT));
	memset(&pEvent,0,sizeof(PLX_NOTIFY_OBJECT));
}

//��������
CPciProcess::~CPciProcess()
{

}
//��ʼ������
//����豸���������ö�д����
bool CPciProcess::fnPciInit()
{
	PLX_STATUS RET;
	pKey.VendorId = m_uiVendorId;
	pKey.DeviceId = m_uiDeviceId;
	do 
	{
		m_bIsBusy = false;
	} while (m_bIsBusy);
	PCI_SET_BUSY;
	RET = PlxPci_DeviceFind(&pKey,SELECT_1ST_DEVICE);
	if (RET != ApiSuccess)
	{
		PCI_SET_IDLE;
		return false;
	}
	RET = PlxPci_DeviceOpen(&pKey,&pDevice); 
	if (RET != ApiSuccess)
	{
		PCI_SET_IDLE;
		return false;
	}	
	PLX_STATUS pStatusa;
	PLX_STATUS pStatusb;
	ULONG data;
	data = PlxPci_PlxRegisterRead(&pDevice,REGISTER_SPACE1_OFFSET, &pStatusa);
	pStatusb = PlxPci_PlxRegisterWrite(&pDevice,REGISTER_SPACE1_OFFSET, data | REGISTER_SPACE_ENABLE_MASK);
	PCI_SET_IDLE;
	return true;
}
//���ڴ�
bool CPciProcess::fnPciReadMem(ULONG offset,unsigned int len,unsigned char* data)
{
	PLX_STATUS RET;
	PCI_SET_BUSY;
	RET = PlxPci_PciBarSpaceRead(
		&pDevice,
		BAR_3_SPACE_OFFSET,
		offset,
		data,
		len,
		BitSize16,
		TRUE
		);

	if (RET != ApiSuccess)
	{
		PCI_SET_IDLE;
		return false;
	}
	PCI_SET_IDLE;
	return true;
}
bool CPciProcess::fnPciReadMem(ULONG offset,ULONG& data)
{
	volatile PLX_STATUS RET;
	PCI_SET_BUSY;
	RET = PlxPci_PciBarSpaceRead(
		&pDevice,
		BAR_3_SPACE_OFFSET,
		offset,
		&data,
		sizeof(data),
		BitSize16,
		TRUE
		);

	if (RET != ApiSuccess)
	{
		PCI_SET_IDLE;
		return false;
	}
	PCI_SET_IDLE;
return true;
}
bool CPciProcess::fnPciReadMem(ULONG offset, USHORT& data)
{
	volatile PLX_STATUS RET;
	PCI_SET_BUSY;
	RET = PlxPci_PciBarSpaceRead(
		&pDevice,
		BAR_3_SPACE_OFFSET,
		offset,
		&data,
		sizeof(data),
		BitSize16,
		TRUE
		);

	if (RET != ApiSuccess)
	{
		PCI_SET_IDLE;
		return false;
	}
	PCI_SET_IDLE;
	return true;
}
//д�ڴ�
bool CPciProcess::fnPciWriteMem(ULONG offset, unsigned char* data,unsigned int len)
{
	PLX_STATUS RET;
	PCI_SET_BUSY;
	RET = PlxPci_PciBarSpaceWrite(
		&pDevice,
		BAR_3_SPACE_OFFSET,
		offset,
		data,
		len,
		BitSize16,
		TRUE
		);
	if (RET!=ApiSuccess)
	{
		PCI_SET_IDLE;
		return false;
	}
	PCI_SET_IDLE;
	return true;
}
bool CPciProcess::fnPciWriteMem(ULONG offset, ULONG data)
{
	PLX_STATUS RET;
	PCI_SET_BUSY;
	RET = PlxPci_PciBarSpaceWrite(
		&pDevice,
		BAR_3_SPACE_OFFSET,
		offset,
		&data,
		sizeof(data),
		BitSize16,
		TRUE
		);
	if (RET!=ApiSuccess)
	{
		PCI_SET_IDLE;
		return false;
	}
	PCI_SET_IDLE;
	return true;
}

/*
bool CPciProcess::fnPciWriteMemInt(ULONG offset, ULONG data)    //д�ж�ר��
{
	PLX_STATUS RET;
	PCI_SET_BUSY;
	RET = PlxPci_PciBarSpaceWrite(
		&pDevice,
		BAR_3_SPACE_OFFSET,
		offset,
		&data,
		sizeof(data),
		BitSize32,
		TRUE
		);
	if (RET!=ApiSuccess)
	{
		PCI_SET_IDLE;
		return false;
	}
	PCI_SET_IDLE;
	return true;
}
*/

bool CPciProcess::fnPciWriteMem(ULONG offset, USHORT data)
{
	PLX_STATUS RET;
	PCI_SET_BUSY;
	RET = PlxPci_PciBarSpaceWrite(
		&pDevice,
		BAR_3_SPACE_OFFSET,
		offset,
		&data,
		sizeof(data),
		BitSize16,
		TRUE
		);
	if (RET!=ApiSuccess)
	{
		PCI_SET_IDLE;
		return false;
	}
	PCI_SET_IDLE;
	return true;
}
//���Ĵ���
ULONG CPciProcess::fnPciReadReg(ULONG offset)
{
	ULONG data = 0;
	PLX_STATUS pStatus;
	PCI_SET_BUSY;
	data = PlxPci_PlxRegisterRead(&pDevice,offset, &pStatus);
	PCI_SET_IDLE;
	return data;
}
//д�Ĵ���
void CPciProcess::fnPciWriteReg(ULONG offset, unsigned char* data)
{
	
}
//�ر�PCI�豸
bool CPciProcess::fnPciClose()
{
	PLX_STATUS RET;

	PLX_STATUS pStatus;
	PCI_SET_BUSY;
	pStatus = PlxPci_InterruptDisable(&pDevice,&pPlxIntr);

	RET = PlxPci_DeviceClose(&pDevice);
	PCI_SET_IDLE;	
	if (RET != ApiSuccess)
	{
		PCI_SET_IDLE;
		return false;
	}
	PCI_SET_IDLE;
	return true;
}

/*
//�����ж��߳�
bool CPciProcess::fnPciStartThread()
{
	PCI_SET_BUSY;
	CWTThread = AfxBeginThread(fnPciIntThread, this);
	if (m_bExeThreadIsAlive)
	{
		do
		{
			SetEvent(m_hShutdownEvent);
		} while (m_bExeThreadIsAlive);
	}
	if (m_hShutdownEvent != NULL)
		ResetEvent(m_hShutdownEvent);
	m_hShutdownEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (m_hExeEvent != NULL)
		ResetEvent(m_hExeEvent);
	m_hExeEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	m_hEventArray[0] = m_hShutdownEvent;	// highest priority
	m_hEventArray[1] = m_hExeEvent;

	ExecuteThread = AfxBeginThread(fnExeThread,this);
	PCI_SET_IDLE;
	return true;
}

//�����߳�
UINT CPciProcess::fnExeThread(LPVOID ppv)
{
	DWORD Event = 0;
	int icount = 0;
	CPciProcess *cpp = (CPciProcess*)ppv;
	do{
		Event = WaitForMultipleObjects(2, cpp->m_hEventArray, FALSE, INFINITE);
		switch(Event)
		{
		case 0:
			cpp->m_bExeThreadIsAlive = FALSE;
			// Kill this thread.  
			// Return 100
			AfxEndThread(100);
			break;
		case 1:
			icount++;
			LINK.fnSendMessageToWinform();
			ResetEvent(cpp->m_hExeEvent);
			break;
		}
	}while(1) ;
}
//��ʼ���߳�
UINT CPciProcess::fnPciIntThread(LPVOID pParam)
{
	PLX_STATUS pStatus;
	ULONG data;

//	CCommUtl *port = (CCommUtl*)pParam;
	do 
	{
		CPciProcess *port = (CPciProcess*)pParam;
		while(port->m_bIsBusy) ;
		port->m_bIsBusy = true;
		//PCI_SET_BUSY;
		
		pStatus = PlxPci_InterruptEnable(&(port->pDevice),&(port->pPlxIntr));

		data = PlxPci_PlxRegisterRead(&(port->pDevice),0x68,&pStatus);
		pStatus = PlxPci_PlxRegisterWrite(&(port->pDevice),0x68,data | 0x8800);
		port->pPlxIntr.LocalToPci = 0x00000001;
		pStatus = PlxPci_NotificationRegisterFor(&(port->pDevice),&(port->pPlxIntr),&(port->pEvent));
		port->m_bIsBusy = false;

		pStatus = PlxPci_NotificationWait(&(port->pDevice),&(port->pEvent),PLX_TIMEOUT_INFINITE);

		switch(pStatus)
		{
		case ApiSuccess: 
			{
				//LINK.m_bAsyLock = true;
				//MessageBox(LINK.m_pCWnd->m_hWnd,0,0,0);
				//Get Button Value 
				SetEvent(port->m_hExeEvent);			
			}		
			break;
		case ApiInvalidAddress:
			//Send Fatal Error to Windows
		case ApiInvalidDeviceInfo:
			//Send Fatal Error to Windows
		default:
			//Send Fatal Error to Windows
			break;
		}
		fnDelay();
		pStatus = PlxPci_NotificationCancel(&(port->pDevice),&(port->pEvent));
		//PCI_SET_IDLE;
		
	} while (1);
	return 0;
}
*/
void CPciProcess::fnDelay()
{
	int ipi,ipj,ipk;
	for (ipi = 0;ipi<300;ipi++)
	{
		for (ipj = 0;ipj<100;ipj++)
		{
			for (ipk = 0;ipk<100;ipk++)
			{
			}
		}
	}
}
