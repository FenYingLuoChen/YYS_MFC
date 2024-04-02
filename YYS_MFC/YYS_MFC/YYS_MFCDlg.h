
// YYS_MFCDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "Function.h"

// CYYS_MFCDlg �Ի���
class CYYS_MFCDlg : public CDialogEx
{
// ����
public:
	CYYS_MFCDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_YYS_MFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	void init_combox();

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	void GetMousePoint(CString type, std::vector<MouseClick> &click_list);
	void SendMousePressed();
	void OpenConSole(CString type);
	void CloseConSole();
	void rememberOption(FILE*file);
	//DWORD WINAPI ThreadProc(LPVOID lpParam);
	//void initwindowpos();
	//BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lparam);
	std::vector<MouseClick> click_list;
	CString m_str_combox;
	BOOL if_read = true;
	BOOL if_reset = false;
	CComboBox m_combox;
	POINT point = { 0 };
	int sleeptime;
	int x, y, width, height;
	CString classname;
	HWND *window = NULL;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	void initwindowpos();
	void rePosWindowpos();
	DWORD WindowFormat[2] = { 0 };
};
