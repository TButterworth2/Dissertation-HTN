
#include <Windows.h>

#include <sstream>
using std::stringstream;

#include "Common\Input.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch( uMsg )
	{
	case WM_CREATE:
		InitInput();
		break;

	case WM_DESTROY:
		DestroyWindow( hWnd );
		PostQuitMessage( 0 );
		break;

	case WM_KEYDOWN:
		KeyDownEvent( static_cast<EKeyState>( wParam ) );
		break;

	case WM_KEYUP:
		KeyUpEvent( static_cast<EKeyState>( wParam ) );
		break;

	default:
		return DefWindowProc( hWnd, uMsg, wParam, lParam );
	}

	return 0;

}

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	//================================================================
	// Setup
	//================================================================

	HWND hWnd;
	WNDCLASSEX wndEx;

	wndEx.cbSize        = sizeof(WNDCLASSEX);
	wndEx.style         = CS_HREDRAW | CS_VREDRAW;
	wndEx.lpfnWndProc   = WndProc;
	wndEx.cbClsExtra    = 0;
	wndEx.cbWndExtra    = 0;
	wndEx.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	wndEx.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wndEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndEx.lpszMenuName  = NULL;
	wndEx.lpszClassName = "Hierarchical Task Network";
	wndEx.hInstance     = hInst;
	wndEx.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx( &wndEx );

	
	hWnd = CreateWindowEx( WS_EX_OVERLAPPEDWINDOW, "Hierarchical Task Network", "Hierarchical Task Network", WS_OVERLAPPEDWINDOW, 20, 10, 640, 480,
						NULL, NULL, hInst, NULL );
	if( hWnd == 0 )
	{
		std::stringstream ss;
		ss << GetLastError();
		MessageBox( NULL, ss.str().c_str(), "ERROR", NULL );
		return 1;
	}

	
	BOOL bl;
	
	bl = ShowWindow( hWnd, nCmdShow );
	if( bl != 0 )
		return 2;

	bl = UpdateWindow( hWnd );
	if( bl == 0 )
		return 3;

	//================================================================
	// End Setup
	//================================================================

	//================================================================
	// Main Loop
	//================================================================
	
	MSG msg;
	ZeroMemory( &msg, sizeof(msg) );

	bool running = true;

	while( running )
	{
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			if( KeyHit( Key_Escape ) )
			{
				running = false;
			}
		}
	}

	return 0;
}
