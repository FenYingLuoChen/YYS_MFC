#pragma once
#include "Function.h"
#include "YYS_MFCDlg.h"
class MyPicture
{
public:
	MyPicture(char* filename);
	~MyPicture();

	//��ʼ��
	void Init();
	//��������ָ��λ�û�ȡͼƬ����
	void SaveBmpFromPointToFile(char * filename, POINT point, HWND hwnd, int width = 10, int height = 10);
	//���±���ͼƬ
	void UpdateBackGround();
	//��ȡͼƬλ��
	BOOL GetBmpPos();
	//���
	BOOL Click();
	//����
	void EndClick();
	//�������δ���
	void MainSubWnd();
	//�ƶ���ͼ
	static void MouseDrag();

	//������
	static HWND HwndMain;
	//�δ���
	static HWND HwndSub;
	//����ͼƬ
	static char* BackGround;
	//���δ������ֱ�ʶ 0 ������ 1 �δ���
	static int type;
	//������
	static HWND * window;

	//��ǰͼƬ
	char * Bitmap;
	//��ǰͼƬλ��
	POINT BmpPos;
	//�Ƿ��ʼ��ͼƬ
	BOOL IfInit;

};

