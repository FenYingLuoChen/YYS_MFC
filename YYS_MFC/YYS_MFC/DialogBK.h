#pragma once


// DialogBK 对话框

class DialogBK : public CDialogEx
{
	DECLARE_DYNAMIC(DialogBK)

public:
	DialogBK(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DialogBK();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
