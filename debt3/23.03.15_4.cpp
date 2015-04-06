/*3.	4.	Перемещение мыши в верхней половине окна приводит к появлению периодического мерцания заголовка окна.
Нажатие любой буквы из линейки «QWER..» перемещает окно в правый верхний угол экрана.*/

#include<Windows.h>
#include<stdlib.h>
#include<string>
#include<tchar.h>

static TCHAR WindowsClass[] = _T("win32app");
static TCHAR Title[] = _T("Мерцающий заголовок");
HINSTANCE hinst;

RECT desktop;
int _X, _Y, _W, _H; // координаты окна

enum VKey {
	Q = 81, W = 87, E = 69, R = 82, T = 84, Y = 89, U = 85, I = 73, O = 79, P = 80,
	q = 113, w = 119, e = 101, r = 114, t = 116, y = 121, u = 117, i = 105, o = 111, p = 112
};


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)

{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hinstance;
	wcex.hIcon = LoadIcon(hinstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	/*wcex.hbrBackground = CreateSolidBrush(RGB(100, 70, 150));*/
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = WindowsClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, _T("Call faild!"), _T("MyApp"), NULL);
		return 1;
	}

	hinst = hinstance;

	//Получить координаты рабочего стола
	GetWindowRect(GetDesktopWindow(), &desktop);

	_X = desktop.right / 4;
	_Y = desktop.bottom / 4;
	_W = _X * 2;
	_H = _Y * 2;



	HWND hWnd = CreateWindow(
		WindowsClass,
		Title,
		WS_OVERLAPPEDWINDOW,
		_X,
		_Y,
		_W,
		_H,
		NULL,
		NULL,
		hinst,
		NULL);

	if (!hWnd)
	{
		MessageBox(NULL, _T("Create window faild!"), _T("MyApp"), NULL);
		return 1;
	}

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return(int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rect;
	RECT desktop;

	switch (message)
	{

	case WM_KEYDOWN:
	{
					   switch (LOWORD(wParam))
					   {

					   case (VKey::Q) : case (VKey::q) :
					   case (VKey::W) : case (VKey::w) :
					   case (VKey::E) : case (VKey::e) :
					   case (VKey::R) : case (VKey::r) :
					   case (VKey::T) : case (VKey::t) :
					   case (VKey::Y) : case (VKey::y) :
					   case (VKey::U) : case (VKey::u) :
					   case (VKey::I) : case (VKey::i) :
					   case (VKey::O) : case (VKey::o) :
					   case (VKey::P) : case (VKey::p) :

										SetWindowPos(hWnd, HWND_TOP, 0, 0, _W, _H, SWP_SHOWWINDOW);
						   break;
					   }
					   break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}