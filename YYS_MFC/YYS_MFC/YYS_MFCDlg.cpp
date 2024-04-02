
// YYS_MFCDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "YYS_MFC.h"
#include "YYS_MFCDlg.h"
#include "afxdialogex.h"
#include "log.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CYYS_MFCDlg �Ի���



CYYS_MFCDlg::CYYS_MFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_YYS_MFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_ICON);
	window = new HWND[2];
}

void CYYS_MFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combox);
}

BEGIN_MESSAGE_MAP(CYYS_MFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CYYS_MFCDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CYYS_MFCDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CYYS_MFCDlg::OnBnClickedButton2)
	ON_WM_LBUTTONDOWN()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CYYS_MFCDlg ��Ϣ�������

BOOL CYYS_MFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�
	//LONG style = ::GetWindowLong(this->m_hWnd, GWL_STYLE);
	////ȥ�߿�
	//::SetWindowLong(m_hWnd, GWL_STYLE, style&~WS_CAPTION);
	LOG("init_combox hwnd = %X  str = %s",m_hWnd,"TestLog");
	init_combox();
	
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CYYS_MFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CYYS_MFCDlg::OnPaint()
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
HCURSOR CYYS_MFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CYYS_MFCDlg::init_combox()
{
	CString init_fileName = "C:\\YYS\\init.txt";
	FILE * file = fopen(init_fileName,"r");
	char buf[128] = {0};
	char temp[128] = { 0 };
	if (file)
	{
		while (fscanf(file, "%[^\n]", buf) != EOF)
		{
			fgetc(file);//�������з�
			if (buf[0] == 'x')
			{
				x = atoi(&buf[2]);
			}
			else if (buf[0] == 'y')
			{
				y = atoi(&buf[2]);
			}
			else if (buf[0] == 'w')
			{
				width = atoi(&buf[6]);
			}
			else if (buf[0] == 'h')
			{
				height = atoi(&buf[7]);
			}
			else if (buf[0] == 'c')
			{
				classname = &buf[6];
			}
			else
			{
				m_combox.AddString(buf);
			}
		}
		fclose(file);
	}
}


void CYYS_MFCDlg::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nSel;
	nSel = m_combox.GetCurSel();
	m_combox.GetLBText(nSel, m_str_combox);
}

//¼��
void CYYS_MFCDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if_read = false;
	if_reset = true;
	GetMousePoint(m_str_combox, click_list);
}

//��ȡ
void CYYS_MFCDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if_reset = false;
	if_read = true;
	GetMousePoint(m_str_combox, click_list);
}

HWND hwnd_input;
struct ThreadParam
{
	std::vector<MouseClick> &click_list;
	int num;
};
DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	ThreadParam *param = (ThreadParam *)lpParam;
	// TODO: Add your thread code here
	int num = param->num;
	std::vector<MouseClick> click_list = param->click_list;
	while (num != 0)
	{
		SendMousePressed(click_list);
		if ((GetAsyncKeyState(VK_F11) & 0x8000))
		{
			break;
		}
		num--;
	}
	return 0;
}
void CYYS_MFCDlg::rememberOption(FILE*file)
{
	time_t current = 0, last = 0;
	MouseClick click = { 0 };
	BOOL ifPushback = FALSE;
	char buf[MAX_PATH] = { 0 };
	POINT last_point = {0,0};
	printf("��ʼ��¼��갴��λ�ü����ʱ��(�ఴһ�ο�ʼλ��) ��esc�˳���¼\n");
	int i = 0;
	while (true)
	{
		if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000))//��갴�� ��¼
		{
			GetCursorPos(&point);
			//��ͬ�����޳�
			if ((point.x != last_point.x && point.y != last_point.y))
			{
				current = clock();
				if (ifPushback)
				{
					click.sleep_time = current - last;
					click_list.push_back(click);
					sprintf(buf, "%d,%d:%d\n", click.point.x, click.point.y, click.sleep_time);
					fwrite(buf, 1, strlen(buf), file);
				}
				click.point = point;
				ifPushback = TRUE;
				last_point = point;
				last = current;
			}
			
			
		}
		if ((GetAsyncKeyState(VK_ESCAPE) & 0x8000))//�˳���¼
		{
			printf("����%d����갴��\n",i);
			printf("���˳���¼\n");
			break;
		}
		Sleep(20);

	}
}
//���������λ��  ���ʱ��
void CYYS_MFCDlg :: GetMousePoint(CString type, std::vector<MouseClick> &click_list)
{
	
	char buf[MAX_PATH] = { 0 };
	char temp[MAX_PATH] = {0};
	char result;
	CString filename = "C:\\YYS\\" + type + ".txt";
	MouseClick click = { 0 };
	initwindowpos();
	click_list.clear();
	if (if_reset)
	{
		DeleteFile(filename);
		FILE *file = fopen(filename, "a+");	
		if (file)
		{

			OpenConSole(type);
	
			rememberOption(file);
			
			printf("���� %s ���д���:\n", type);
			int num = 0;
			scanf("%d", &num);
			fclose(file);
			CloseConSole();
				
			ThreadParam param{ click_list ,num};
			DWORD ThreadId;
			HANDLE hThread = ::CreateThread(NULL, 0, ThreadProc, &param, 0, &ThreadId);	
			CloseHandle(hThread);
				
		}
	}
	else
	{
		FILE *file = fopen(filename, "r");
		int x_num,y_num;
		if (file)
		{
			OpenConSole(type);
			while (fscanf(file, "%[^\n]", buf) != EOF)
			{
				fgetc(file);//�������з�
				strcpy(temp, buf);
				for (int i = 0; i < strlen(buf); i++)
				{
					if (buf[i] == ',')
					{
						memset(&temp[i], 0, strlen(&buf[i]));
						point.x = atoi(temp);
						strcpy(temp, &buf[i + 1]);
					}
					if (buf[i] == ':')
					{
						memset(&temp[i], 0, strlen(&buf[i]));
						point.y = atoi(temp);
						sleeptime = atoi(&buf[i+1]);
						click.point = point;
						click.sleep_time = sleeptime;
						click_list.push_back(click);
						break;
					}
				}
			}
			printf("���� %s ���д���:\n", type);
			int num = 0;
			scanf("%d", &num);
			CloseConSole();
			fclose(file);
			ThreadParam param{ click_list ,num };
			CreateThread(NULL, 0, ThreadProc, &param, 0, 0);
		}
	}
	//mouse_event()
}



void CYYS_MFCDlg::OpenConSole(CString type)
{
	if (AllocConsole())
	{
		//�ض����׼���������Ϊ�½�����̨Ӧ�ô���
		freopen("CONOUT$", "w", stdout);
		freopen("CONIN$","r",stdin);
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTitle(type);
		HWND hwnd = ::FindWindow("ConsoleWindowClass",NULL);
		//�򵥴��� Ĭ��ֻ��һ�������д���
		if (hwnd != NULL)
		{
			::SetWindowPos(hwnd, 0,760, 390, 400,300, SWP_SHOWWINDOW);
		}
	}
}

void CYYS_MFCDlg::CloseConSole()
{
	//�ر��ض����׼���������
	fclose(stdin);
	fclose(stdout);
	FreeConsole();
}



int getRand(int min, int max) {
	return (rand() % (max - min + 1)) + min;
}
void CYYS_MFCDlg::SendMousePressed()
{
	int randNum_x = 0, randNum_y = 0;
	for (int i = 0; i < click_list.size(); i++)
	{
		randNum_x = getRand(0, 5);
		randNum_y = getRand(0, 5);
		//���ε��
		SetCursorPos(click_list.at(i).point.x + randNum_x, click_list.at(i).point.y + randNum_y);
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		Sleep(10);
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		Sleep(click_list.at(i).sleep_time);
	}
}



void CYYS_MFCDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//ʵ�ֶԻ�����ק
	::SendMessage(this->m_hWnd,WM_SYSCOMMAND,SC_MOVE + HTCAPTION,0);
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CYYS_MFCDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (window != NULL)
	{
		delete[] window;
		window = NULL;
	}
	//rePosWindowpos();
	CDialogEx::OnClose();
}

void CYYS_MFCDlg::initwindowpos()
{
	GetYYSWindow(classname, window);
	if (IsWindow(window[0]))
	{
		::MoveWindow(window[0], x, y, width, height, true);
		::SetWindowPos(window[0], HWND_TOPMOST, x, y, width, height, SWP_NOMOVE | SWP_NOSIZE);
	}
	if (IsWindow(window[1]))
	{
		::MoveWindow(window[1], x, y + height + 20, width, height, true);
		::SetWindowPos(window[1], HWND_TOPMOST, x, y + height + 20, width, height, SWP_NOMOVE | SWP_NOSIZE);
	}
}

void CYYS_MFCDlg::rePosWindowpos()
{
	GetYYSWindow(classname, window);
	if (IsWindow(window[0]))
	{
		::MoveWindow(window[0], x, y, width, height, true);
		::SetWindowPos(window[0], HWND_NOTOPMOST, x, y, width, height, SWP_NOMOVE | SWP_NOSIZE);
	}
	if (IsWindow(window[1]))
	{
		::MoveWindow(window[1], x, y + height + 20, width, height, true);
		::SetWindowPos(window[1], HWND_NOTOPMOST, x, y + height + 20, width, height, SWP_NOMOVE | SWP_NOSIZE);
	}
}