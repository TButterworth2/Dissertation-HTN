
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch( uMsg )
	{
	case WM_PAINT:
		break;

	default:
		return DefWindowProc( hWnd, uMsg, wParam, lParam );
	}

	return 0;

}

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{

	return 0;

}
