#pragma once


// DialogBK �Ի���

class DialogBK : public CDialogEx
{
	DECLARE_DYNAMIC(DialogBK)

public:
	DialogBK(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DialogBK();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
