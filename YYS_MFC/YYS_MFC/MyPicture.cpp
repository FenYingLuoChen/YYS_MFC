#include "stdafx.h"
#include "MyPicture.h"

HWND MyPicture::HwndMain = NULL;
HWND MyPicture::HwndSub = NULL;
char* MyPicture::BackGround;
HWND * MyPicture::window = NULL;
int MyPicture::type = 0;


MyPicture::MyPicture(char * filename)
{
	if (window == NULL)
	{
		window = new HWND[2];
		GetYYSWindow(CYYS_MFCDlg::classname, window);
	}
	IfInit = false;
	BackGround = "C://YYS//Bitmap//BackGround.bmp";
	MainSubWnd();
	Bitmap = filename;
	Init();
	IfInit = true;
	
}

MyPicture::~MyPicture()
{
	
}

void MyPicture::Init()
{
	//初始化图片
	FILE * file = fopen(Bitmap,"r");
	if (file == NULL)
	{
		CYYS_MFCDlg::Get()->OpenConSole(Bitmap);
		Debug("%s init 鼠标移动到要截取的图片并且按下F10 HwndMain = %X HwndSub = %X",Bitmap,HwndMain,HwndSub);
		POINT point;
		while (1)
		{
			if ((GetAsyncKeyState(VK_F10) & 0x8000))
			{
				GetCursorPos(&point);
				break;
			}
		}
		if (point.x != 0 && point.y != 0)
		{
			Debug("截取完成");
			HWND hwnd = WindowFromPoint(point);
			ScreenToClient(hwnd, &point);
			SetCursorPos(0, 0);
			Sleep(50);
			SaveBmpFromPointToFile(Bitmap,point,hwnd);
		}
		CYYS_MFCDlg::Get()->CloseConSole();
	}
	else
	{
		fclose(file);
	}
}

void MyPicture::SaveBmpFromPointToFile(char * filename, POINT point, HWND hwnd, int width, int height)
{
	if (filename == NULL || hwnd == NULL)
	{
		return;
	}
	HDC hdc = GetDC(hwnd);
	HDC hdc_temp = CreateCompatibleDC(hdc);
	HBITMAP hbitmap = CreateCompatibleBitmap(hdc, width, height);//创建内存位图画板
	SelectObject(hdc_temp, hbitmap);
	BitBlt(hdc_temp, 0, 0, width, height, hdc, point.x, point.y, SRCCOPY);
	if (point.x != 0)
	{
		point.x -= 5;
		point.y -= 5;
	}
	BITMAPINFO bitmapinfo = { 0 };
	bitmapinfo.bmiHeader.biSize = sizeof(bitmapinfo.bmiHeader);
	GetDIBits(hdc, hbitmap, 0, height, NULL, &bitmapinfo, DIB_RGB_COLORS);

	int size = bitmapinfo.bmiHeader.biSizeImage;//颜色数据大小

	BYTE *data = new BYTE[size];
	GetDIBits(hdc, hbitmap, 0, height, data, &bitmapinfo, DIB_RGB_COLORS);
	bitmapinfo.bmiHeader.biCompression = BI_RGB;

	BITMAPFILEHEADER bf;
	bf.bfType = 0x4d42;
	bf.bfSize = size + sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER);
	bf.bfOffBits = sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER);

	FILE *file = fopen(filename, "wb+");
	if (file)
	{
		fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, file);
		fwrite(&bitmapinfo.bmiHeader, sizeof(BITMAPINFOHEADER), 1, file);
		fwrite(data, 1, size, file);
		fclose(file);
	}
	if (data)
	{
		delete data;
		data = NULL;
	}
	ReleaseDC(hwnd, hdc);
	DeleteDC(hdc_temp);
	DeleteObject(hbitmap);
}

void MyPicture::UpdateBackGround()
{
	HWND hwnd = NULL;
	if (type == 0)
	{
		hwnd = HwndMain;
	}
	else
	{
		hwnd = HwndSub;
	}
	POINT point;
	point.x = 0;
	point.y = 0;
	RECT rect;
	GetWindowRect(hwnd, &rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;
	SaveBmpFromPointToFile(BackGround, point, hwnd, width, height);
}

BOOL MyPicture::GetBmpPos()
{
	UpdateBackGround();

	GdiplusStartupInput m_gdiplusStartupInput;
	ULONG_PTR m_gdiplusToken;
	GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, NULL);
	if (IfInit && (Bitmap == NULL || BackGround == NULL))
	{
		return FALSE;
	}

	HWND hwnd = NULL;
	if (type == 0)
	{
		hwnd = HwndMain;
	}
	else
	{
		hwnd = HwndSub;
	}

	RECT rect;
	GetWindowRect(hwnd, &rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	char temp[MAX_PATH] = { 0 };
	WCHAR Temp[MAX_PATH] = { 0 };
	strcpy(temp, BackGround);
	char2widechar(temp, Temp);
	::Bitmap * Big_bitmap = new ::Bitmap(Temp);//Bitmap 内存需要释放，最好用new形式构建
	
	if (!IfInit)
	{
		FILE * file = fopen("C://YYS//Bitmap//Explore//OK.bmp", "r");
		if (file == NULL)
		{
			CYYS_MFCDlg::Get()->OpenConSole(Bitmap);
			Debug("鼠标移动到截取OK.bmp的位置并且按下F10");
			POINT point;
			while (1)
			{
				if ((GetAsyncKeyState(VK_F10) & 0x8000))
				{
					GetCursorPos(&point);
					break;
				}
			}
			if (point.x != 0 && point.y != 0)
			{
				Debug("截取完成");
				HWND hwnd = WindowFromPoint(point);
				ScreenToClient(hwnd, &point);
				SetCursorPos(0, 0);
				HwndMain = hwnd;
				Sleep(50);
				SaveBmpFromPointToFile("C://YYS//Bitmap//Explore//OK.bmp", point, hwnd);
			}
			CYYS_MFCDlg::Get()->CloseConSole();
			return TRUE;
		}
		else
		{
			fclose(file);
			strcpy(temp, "C://YYS//Bitmap//Explore//OK.bmp");
		}
	}
	else
	{
		strcpy(temp, Bitmap);
		
	}
	char2widechar(temp, Temp);
	::Bitmap * Small_bitmap = new ::Bitmap(Temp);
	int i, j, m, n;
	BmpPos.x = 0;
	BmpPos.y = 0;
	Color color_big, color_small;

	Big_bitmap->GetPixel(0, 0, &color_big);
	Small_bitmap->GetPixel(5, 5, &color_small);

	for (i = 5; i < height - 5; i++)
	{
		for (j = 5; j < width - 5; j++)
		{
			Big_bitmap->GetPixel(j, i, &color_big);
			Small_bitmap->GetPixel(5, 5, &color_small);
			if (abs((int)color_big.GetRed() - (int)color_small.GetRed()) == 0 && abs((int)color_big.GetBlue() - (int)color_small.GetBlue()) == 0 && abs((int)color_big.GetGreen() - (int)color_small.GetGreen()) == 0)
			{
				BOOL break_ = FALSE;
				for (m = 0; m < 10 && !break_; m++)
				{
					for (n = 0; n < 10 && !break_; n++)
					{
						Big_bitmap->GetPixel(j - 5 + n, i - 5 + m, &color_big);
						Small_bitmap->GetPixel(n, m, &color_small);
						if (abs((int)color_big.GetRed() - (int)color_small.GetRed()) != 0 ||
							abs((int)color_big.GetBlue() - (int)color_small.GetBlue()) != 0 ||
							abs((int)color_big.GetGreen() - (int)color_small.GetGreen()) != 0)
						{
							break_ = TRUE;
						}

					}
				}
				if (!break_)
				{
					BmpPos.x = j;
					BmpPos.y = i;
					goto lable;
				}
			}
		}
	}
	lable:
	delete Big_bitmap;
	delete Small_bitmap;

	GdiplusShutdown(m_gdiplusToken);
	if (BmpPos.x != 0)
	{
		ClientToScreen(hwnd, &BmpPos);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL MyPicture::Click()
{
	if (GetBmpPos())
	{
		SetCursorPos(BmpPos.x, BmpPos.y);
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		Sleep(10);
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		return TRUE;
	}
	return FALSE;
}

void MyPicture::EndClick()
{
	HWND hwnd = NULL;
	if (type == 0)
	{
		hwnd = HwndMain;
	}
	else
	{
		hwnd = HwndSub;
	}
	RECT rect;
	POINT point;
	GetWindowRect(hwnd, &rect);
	point.x = rect.top - 60 + getRand(0, 10);
	point.y = rect.bottom - 40 + getRand(0, 10);

	SetCursorPos(point.x, point.y);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	Sleep(10);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

void MyPicture::MainSubWnd()
{
	if (HwndMain == NULL)
	{
		HwndMain = window[0];
		if (GetBmpPos())
		{
			if (HwndMain == window[0])
			{
				HwndSub = window[1];
			}
			else
			{
				HwndSub = window[0];
			}
		}
		else
		{
			HwndMain = window[1];
			HwndSub = window[0];
		}
	}
}

void MyPicture::MouseDrag()
{
	RECT rect;
	GetWindowRect(HwndMain, &rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	POINT point;
	point.x = rect.left + width/2 + getRand(0, 10);
	point.y = rect.bottom - height/5 - getRand(0, 10);
	SetCursorPos(point.x, point.y);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	Sleep(10);
	mouse_event(MOUSEEVENTF_MOVE, -(width/4), 0, 0, 0);
	Sleep(10);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}
