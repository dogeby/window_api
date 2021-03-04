//p89 도형 그리기
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
	HPEN hpen, hpen2, oldpen;
	HBRUSH hbrush, oldbrush;
	POINT point[10] = { {600, 600}, {700, 30}, {800, 150}, {250, 250}, {900, 300} };
	POINT point2[10] = { {900, 500}, {400, 30}, {200, 150}, {350, 250}, {500, 300} };


	switch (iMsg)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		hpen = CreatePen(PS_DOT, 1, RGB(255, 0, 0));
		oldpen = (HPEN)SelectObject(hdc, hpen);
		hbrush = CreateSolidBrush(RGB(0, 255, 0));
		oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
		Ellipse(hdc, 20, 20, 150, 150);	//원그리기

		hpen2 = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		hpen = (HPEN)SelectObject(hdc, hpen2);
		DeleteObject(hpen);

		MoveToEx(hdc, 0, 0, NULL);
		LineTo(hdc, 15, 15);	//선그리기
		Rectangle(hdc, 200, 200, 300, 300);	//사각형그리기
		Polyline(hdc, point, 5);
		Polygon(hdc, point2, 5);	//다각형그리기

		hpen2 = (HPEN) SelectObject(hdc, oldpen);
		hbrush = (HBRUSH) SelectObject(hdc, oldbrush);
		DeleteObject(hpen2);
		DeleteObject(hbrush);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}