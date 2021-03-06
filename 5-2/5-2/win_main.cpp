//p197 비트맵 출력하기, p202 움직이는 텍스트 표현하기, p205 더블 버퍼링 이용 움직이는 텍스트 표현하기
//오류시 '링커-시스템-하위시스템-창'으로 변경
#include <windows.h>
#include <tchar.h>
#include "resource.h"

HINSTANCE hInst;
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
void TextPrint(HDC hdc, int x, int y, TCHAR text[]);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int nCmdShow) {
	HWND hwnd;
	MSG msg;
	WNDCLASSEX wndclass;
	hInst = hInstance;
	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = _T("ClassNameEx");
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(
		_T("ClassNameEx"), _T("Window Title Name"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL
	);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

void TextPrint(HDC hdc, int x, int y, TCHAR text[]) {
	int i, j;
	SetTextColor(hdc, RGB(255, 255, 255));
	for (i = -1; i <= 1; i++) {
		for (j = -1; j <= 1; j++)
			TextOut(hdc, x + i, y + j, text, _tcslen(text));
		SetTextColor(hdc, RGB(0, 0, 0));
		TextOut(hdc, x, y, text, _tcslen(text));
	}
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	static HDC hdc, mem1dc, mem2dc;
	PAINTSTRUCT ps;
	static HBITMAP hBit1, hBit2, oldBit1, oldBit2;

	static RECT rectView;
	static int yPos;
	TCHAR word[] = _T("대한민국 화이팅");

	switch (iMsg)
	{
	case WM_CREATE:
		yPos = -30;
		GetClientRect(hwnd, &rectView);
		SetTimer(hwnd, 1, 70, NULL);
		hBit2 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP5_2));
		break;
	case WM_TIMER:
		yPos += 5;
		if (yPos > rectView.bottom) yPos = -30;
		InvalidateRgn(hwnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		GetClientRect(hwnd, &rectView);
		hdc = BeginPaint(hwnd, &ps);
		mem1dc = CreateCompatibleDC(hdc);
		mem2dc = CreateCompatibleDC(mem1dc);
		if (hBit1 == NULL)
			hBit1 = CreateCompatibleBitmap(hdc, 530, 530);
		oldBit1= (HBITMAP)SelectObject(mem1dc, hBit1);
		oldBit2 = (HBITMAP)SelectObject(mem2dc, hBit2);
		BitBlt(mem1dc, 0, 0, 530, 530, mem2dc, 0, 0, SRCCOPY);
		//StretchBlt(hdc, 0, 0, 1060, 530, memdc, 0, 0, 530, 530, SRCCOPY);
		SetBkMode(mem1dc, TRANSPARENT);
		TextPrint(mem1dc, 200, yPos, word);
		BitBlt(hdc, 0, 0, 530, 530, mem1dc, 0, 0, SRCCOPY);
		SelectObject(mem1dc, oldBit1);
		SelectObject(mem2dc, oldBit2);
		DeleteDC(mem2dc);
		DeleteDC(mem1dc);
		//TextOut(hdc, 200, yPos, word, _tcslen(word));
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		if (hBit1) DeleteObject(hBit1);
		DeleteObject(hBit2);
		KillTimer(hwnd, 1);
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}