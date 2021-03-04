//p141 윈도우 메뉴 붙이기, 커맨드 메시지 처리하기, p150텍스트 파일 잃어오기
//p153 다름 이름으로 저장 대화상자 이용하기, p159 글꼴 대화상자 이용하기, p164 색 대화상자 이용하기
//p168 복사하기, 붙여넣기 메뉴 항복 비활성화하기
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include "resource.h"


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
void OutFromFile(TCHAR filename[], HWND hwnd);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int nCmdShow) {
	HWND hwnd;
	MSG msg;
	WNDCLASSEX wndclass;
	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
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

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	
	int answer;

	OPENFILENAME OFN;
	TCHAR str[100], lpstrFile[100] = _T("");
	TCHAR filter[] = _T("Every File(*.*)\0*.*\0Text File\0*.txt;*.doc\0");

	HDC hdc;
	PAINTSTRUCT ps;

	CHOOSEFONT FONT;
	static COLORREF fColor;
	HFONT hFont, oldFont;
	static LOGFONT LogFont;

	CHOOSECOLOR COLOR;
	static COLORREF tmp[16], color;
	HBRUSH hBrush, oldBrush;
	int i;

	static HMENU hMenu, hSubMenu;

	switch (iMsg)
	{
	case WM_CREATE:
		hMenu = GetMenu(hwnd);
		hSubMenu = GetSubMenu(hMenu, 1);
		EnableMenuItem(hSubMenu, ID_EDITCOPY, MF_GRAYED);
		EnableMenuItem(hSubMenu, ID_EDITPASTE, MF_GRAYED);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_FILENEW:
			MessageBox(hwnd, _T("새 파일을 열겠습니까?"), _T("새 파일 선택"), MB_OKCANCEL);
			break;
		case ID_EXIT:
			answer = MessageBox(hwnd, _T("파일을 저장하고 끝내겠습니까?"), _T("끝내기 선택"), MB_YESNOCANCEL);
			if (answer == IDYES || answer == IDNO)
				PostQuitMessage(0);
			break;
		case ID_FILEOPEN:
			memset(&OFN, 0, sizeof(OPENFILENAME));
			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = hwnd;
			OFN.lpstrFilter = filter;
			OFN.lpstrFile = lpstrFile;
			OFN.nMaxFile = 100;
			OFN.lpstrInitialDir = _T(".");	//현 프로그램이 실행되는 현재 폴더(.)
			if (GetOpenFileName(&OFN) != 0) {
				OutFromFile(OFN.lpstrFile, hwnd);
			}
			break;
		case ID_FILESAVE:
			memset(&OFN, 0, sizeof(OPENFILENAME));
			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = hwnd;
			OFN.lpstrFilter = filter;
			OFN.lpstrFile = lpstrFile;
			OFN.nMaxFile = 256;
			OFN.lpstrInitialDir = _T(".");
			if (GetSaveFileName(&OFN) != 0) {
				_stprintf_s(str, _T("%s 파일로 저장하겠습니까?"), OFN.lpstrFile);
				MessageBox(hwnd, str, _T("저장하기 선택"), MB_OK);
			}
		case ID_FONTDLG:
			memset(&FONT, 0, sizeof(CHOOSEFONT));
			FONT.lStructSize = sizeof(CHOOSEFONT);
			FONT.hwndOwner = hwnd;
			FONT.lpLogFont = &LogFont;
			FONT.Flags = CF_EFFECTS | CF_SCREENFONTS;
			if (ChooseFont(&FONT) != 0) {
				fColor = FONT.rgbColors;
				InvalidateRgn(hwnd, NULL, TRUE);
			}
		case ID_COLORDLG:
			for (i = 0; i < 16; i++)
				tmp[i] = RGB(rand() % 256, rand() % 256, rand() % 256);
			memset(&COLOR, 0, sizeof(CHOOSECOLOR));
			COLOR.lStructSize = sizeof(CHOOSECOLOR);
			COLOR.hwndOwner = hwnd;
			COLOR.lpCustColors = tmp;
			COLOR.Flags = CC_FULLOPEN;
			if (ChooseColor(&COLOR) != 0) {
				color = COLOR.rgbResult;
				InvalidateRgn(hwnd, NULL, TRUE);
			}
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		hFont = CreateFontIndirect(&LogFont);
		oldFont = (HFONT)SelectObject(hdc, hFont);
		SetTextColor(hdc, fColor);
		TextOut(hdc, 10, 10, _T("HelloWorld"), 10);
		SelectObject(hdc, oldFont);
		DeleteObject(hFont);

		hBrush = CreateSolidBrush(color);
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Ellipse(hdc, 200, 200, 400, 400);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);

		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

void OutFromFile(TCHAR filename[], HWND hwnd) {
	FILE *fPtr;
	HDC hdc;
	int line;
	TCHAR buffer[500];
	line = 0;
	hdc = GetDC(hwnd);
#ifdef _UNICODE
	_tfopen_s(&fPtr, filename, _T("r"));
#else
	_tfopen_s(&fPtr, filename, _T("r"));
#endif
	while (_fgetts(buffer, 100, fPtr) != NULL) {
		if (buffer[_tcslen(buffer) - 1] == _T('\n'))
			buffer[_tcslen(buffer) - 1] = NULL;
		TextOut(hdc, 0, line * 20, buffer, _tcslen(buffer));
		line++;
	}
	fclose(fPtr);
	ReleaseDC(hwnd, hdc);
}