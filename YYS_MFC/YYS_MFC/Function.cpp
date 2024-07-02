#include "stdafx.h"
#include "Function.h"
#include "YYS_MFCDlg.h"
//用一个数组保存鼠标点击位置，间隔时间

static HWND clickwindow[2] = { 0 };
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lparam)
{
	TCHAR classname[MAX_PATH] = { 0 };
	GetClassName(hwnd, classname, MAX_PATH);
	if (strstr(classname, (char*)lparam) != NULL)
	{
		for (int i = 0; i < 2; i++)
		{
			if (!IsWindow(clickwindow[i]))
			{
				clickwindow[i] = 0;
			}
			if (clickwindow[i] == hwnd)
			{
				return true;
			}
			if (clickwindow[i] == 0)
			{
				clickwindow[i] = hwnd;
				return true;
			}
		}
	}
	return true;
}

void GetYYSWindow(CString classname , HWND* window)
{
	EnumWindows(EnumWindowsProc, (LPARAM)classname.GetString());
	for (int i = 0; i < 2; i++)
	{
		window[i] = clickwindow[i];
	}
}

//获取运行程序同级目录
CString getpath()
{
	TCHAR szTemp[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, szTemp, MAX_PATH);
	_tcsrchr(szTemp, _T('\\'))[1] = 0;
	return szTemp;
}

void GetMousePointFromFile(CString type, std::vector<MouseClick> &click_list)
{
	CString filename = "C:\\YYS\\" + type + ".txt";
	FILE *file = fopen(filename, "r");
	char buf[MAX_PATH] = { 0 };
	char temp[MAX_PATH] = { 0 };
	int x, y, time;
	POINT point;
	MouseClick click = { 0 };
	if (file)
	{
		while (fscanf(file, "%[^\n]", buf) != EOF)
		{
			strcpy(temp, buf);
			fgetc(file);
			{
				for (int i = 0; i < MAX_PATH; i++)
				{
					if (buf[i] == ',')
					{
						memset(&temp[i], 0, strlen(&temp[i]));
						x = atoi(temp);
						strcpy(temp, &buf[i + 1]);
					}
					if (buf[i] == ':')
					{
						memset(&temp[i], 0, strlen(&temp[i]));
						y = atoi(temp);
						strcpy(temp, &buf[i + 1]);
					}
					time = atoi(temp);
				}
			}
			point.x = x;
			point.y = y;
			click.point = point;
			click.sleep_time = time;
			click_list.push_back(click);
		}
		fclose(file);
	}
}

//插入鼠标点击位置  间隔时间
void GetMousePoint(CString type,std::vector<MouseClick> &click_list, bool ifReadFile = true)
{
	CString filename = "C:\\YYS\\" + type + ".txt";
	FILE *file = fopen(filename, "a+");
	char buf[MAX_PATH] = { 0 };
	char result;
	POINT point;
	int sleeptime;
	MouseClick click = {0};
	if (file)
	{
	lable:
		printf("请按下F10确定点击位置：\n");
		while (1)
		{
			if ((GetAsyncKeyState(VK_F10) & 0x8000))
			{
				GetCursorPos(&point);
				break;
			}
			Sleep(20);
		}
		printf("x = %d y = %d\n",point.x,point.y);//

		printf("请输入间隔时间(ms)：\n");

		scanf("%d", &sleeptime);

		//写入
		sprintf(buf, "%d,%d:%d\n", point.x, point.y, sleeptime);
		fwrite(buf, 1, strlen(buf), file);

		char a = getchar();//按回车默认/r/n
		if (a == '/r')
		{
			printf("是 r\n");
		}
		else if (a == '/n')
		{
			printf("是 n\n");
		}
		else
		{
			printf("啥也不是\n");
		}
		printf("time = %d\n", sleeptime);
		click.point = point;
		click.sleep_time = sleeptime;
		click_list.push_back(click);
	           
		printf("是否继续插入鼠标点击位置（y/n）:\n");
		scanf("%c", &result);
		if (result == 'y')
		{
			goto lable;
		}
		else
		{
			return;
		}
	}
	fclose(file);
	//mouse_event()
}

int getRand_(int min, int max) {
	return (rand() % (max - min + 1)) + min;
}
void SendMousePressed(std::vector<MouseClick> &click_list)
{
	int randNum_x = 0,randNum_y = 0;
	for (int i = 0; i < click_list.size(); i++)
	{
		randNum_x = getRand_(0, 10);
		randNum_y = getRand_(0, 10);
		//单次点击
		SetCursorPos(click_list.at(i).point.x+ randNum_x, click_list.at(i).point.y + randNum_y);
		mouse_event(MOUSEEVENTF_LEFTDOWN,0 , 0, 0, 0);
		Sleep(10);
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		Sleep(click_list.at(i).sleep_time);
	}
}

void widechar2char(wchar_t * widechar_str, char *char_str)
{
	int length = WideCharToMultiByte(CP_ACP, 0, widechar_str, -1, NULL, 0, NULL, NULL);
	char *temp = new char[length];
	if (temp)
	{
		WideCharToMultiByte(CP_ACP, 0, widechar_str, -1, temp, length, NULL, NULL);
		strcpy(char_str, temp);
		delete temp;
	}
}

void char2widechar(char *char_str, wchar_t * widechar_str)
{
	int length = MultiByteToWideChar(CP_ACP, 0, char_str, -1, NULL, 0);
	wchar_t *temp = new wchar_t[length];
	if (temp)
	{
		MultiByteToWideChar(CP_ACP, 0, char_str, -1, temp, length);
		wcscpy(widechar_str, temp);
		delete temp;
	}
}

void Debug(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	char buf[1024] = { 0 };
	vsprintf(buf, format, args);
	strcat(buf, "\n");
	printf(buf);
	va_end(args);
}
int getRand(int min, int max) {
	return (rand() % (max - min + 1)) + min;
}
