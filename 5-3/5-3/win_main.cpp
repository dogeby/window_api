//p214 마스크를 이용해 애니메이션 만들기

#include <windows.h>
#include <TCHAR.H>
#include "resource.h"
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam);
HINSTANCE hInst;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdLine, int nCmdShow)
{
	HWND 	 hwnd;
	MSG 	 msg;
	WNDCLASS WndClass;
	hInst = hInstance;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = _T("Window Class Name");
	RegisterClass(&WndClass);
	hwnd = CreateWindow(_T("Window Class Name"),
		_T("Window Title Name"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}
void Animation(int xPos, int yPos, HDC hdc)
{
	HDC memdc;
	HBITMAP RunBit[10], hBit, oldBit, Mask[10];
	static int count;
	int i;
	count++;
	count = count % 10;
	RunBit[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP11)); //	for (i = 0; i < 10; i++)
	RunBit[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP12)); //		RunBit[i] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_R1+i));
	RunBit[2] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP13)); //
	RunBit[3] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP14)); //
	RunBit[4] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP15)); //
	RunBit[5] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP16)); //
	RunBit[6] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP17)); //
	RunBit[7] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP18)); //
	RunBit[8] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP19)); //
	RunBit[9] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP20)); //
	Mask[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1)); //  for (i = 0; i < 10; i++)
	Mask[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2)); //		Mask[i] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_M1+i));
	Mask[2] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP3));
	Mask[3] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP4));
	Mask[4] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP5));
	Mask[5] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP6));
	Mask[6] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP7));
	Mask[7] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP8));
	Mask[8] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP9));
	Mask[9] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP10));
	memdc = CreateCompatibleDC(hdc);
	hBit = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP21));
	oldBit = (HBITMAP)SelectObject(memdc, hBit);
	BitBlt(hdc, 0, 0, 819, 614, memdc, 0, 0, SRCCOPY);
	SelectObject(memdc, Mask[count]);
	BitBlt(hdc, xPos, yPos, 180, 240, memdc, 0, 0, SRCAND);
	SelectObject(memdc, RunBit[count]);
	BitBlt(hdc, xPos, yPos, 180, 240, memdc, 0, 0, SRCPAINT);
	SelectObject(memdc, oldBit);
	for (i = 0; i < 10; i++)
	{
		DeleteObject(RunBit[i]);
		DeleteObject(Mask[i]);
	}
	DeleteDC(memdc);
	DeleteObject(hBit);
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static int xPos;

	switch (iMsg)
	{
	case WM_CREATE:
		xPos = -100;
		SetTimer(hwnd, 1, 100, NULL);
		break;
	case WM_TIMER:
		xPos += 10;
		if (xPos > 819) xPos = -100;
		InvalidateRgn(hwnd, NULL, true);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		Animation(xPos, 300, hdc);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		KillTimer(hwnd, 1);
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}