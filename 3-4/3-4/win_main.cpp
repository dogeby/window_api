//래스터 연산 사용해서 p115 고무줄 효과가 있는 직선 그리기, p117 고무줄 효과가 있는 원 그리기
#include <windows.h>
#include <tchar.h>


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);


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

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	static int startX, startY, oldX, oldY;
	static BOOL Drag;
	int endX, endY;

	switch (iMsg)
	{
	case WM_CREATE:
		startX = startY = oldX = oldY = 50;
		Drag = FALSE;
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		
		//MoveToEx(hdc, startX, startY, NULL);
		//LineTo(hdc, oldX, oldY);

		Ellipse(hdc, startX, startY, oldX, oldY);

		EndPaint(hwnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		Drag = TRUE;
		break;
	case WM_LBUTTONUP:
		Drag = FALSE;
		break;
	case WM_MOUSEMOVE:
		hdc = GetDC(hwnd);
		if (Drag) {
			SetROP2(hdc, R2_XORPEN);	//래스터 xor연산 흰색(255,255,255) xor 흰색 = 검은색(0,0,0), 검은색 xor 흰색 = 흰색.
			SelectObject(hdc, (HPEN)GetStockObject(WHITE_PEN));
			endX = LOWORD(lParam);
			endY = HIWORD(lParam);

			//MoveToEx(hdc, startX, startY, NULL);
			//LineTo(hdc, oldX, oldY);
			//MoveToEx(hdc, startX, startY, NULL);
			//LineTo(hdc, endX, endY);

			SelectObject(hdc, (HBRUSH)GetStockObject(BLACK_BRUSH));
			Ellipse(hdc, startX, startY, oldX, oldY);
			Ellipse(hdc, startX, startY, endX, endY);

			oldX = endX;
			oldY = endY;
		}
		ReleaseDC(hwnd, hdc);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
