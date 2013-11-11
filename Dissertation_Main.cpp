
#include <Windows.h>

#include <sstream>
using std::stringstream;

#include "Common\Input.h"

#include "Demo\CSceneManager.h"
using namespace Scene;
using gen::CVector3;	using gen::CVector4;

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
	const char* BASIC = "BasicRender";
	const char* PIXEL = "PixelLighting";

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


	ISceneManager* sceneManager = CreateSceneManager();

	sceneManager->CreateRenderDevice( hWnd, "..\\..\\Dissertation-HTN\\Demo\\effects.fx", PIXEL );

	CVector3 ambientColour = CVector3( 0.4f, 0.4f, 0.4f );
	CVector3 specularColour = CVector3( 0.8f, 0.8f, 0.8f );
	CVector4 clearColour = CVector4( 0.0f, 0.0f, 0.0f, 1.0f );

	sceneManager->SetClearColour( clearColour.x, clearColour.y, clearColour.z, clearColour.w );
	sceneManager->SetAmbientColour( ambientColour.x, ambientColour.y, ambientColour.z );

	unsigned int cubeTemplate=0, cube=0;
	cubeTemplate = sceneManager->CreateTemplate( "..\\..\\Dissertation-HTN\\Demo\\Media\\cube.x" );
	cube = sceneManager->CreateModel( cubeTemplate );

	unsigned int planetTemp, planet;

	planetTemp = sceneManager->CreateTemplate( "..\\..\\Dissertation-HTN\\Demo\\Media\\planet.x" );
	planet = sceneManager->CreateModel( planetTemp );
	sceneManager->MoveWorldZ( 1000.0f, planet );

	IRTSCamera* camera = sceneManager->CreateCamera( 0.0f, 10.0f, -20.0f );

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

			sceneManager->Render();

			if( KeyHit( Key_Escape ) )
			{
				running = false;
			}

			if( KeyHeld( Key_W ) )
			{
				camera->MoveLocalZ( 0.001f );
			}
			else if( KeyHeld( Key_S ) )
			{
				camera->MoveLocalZ( -0.001f );
			}
		}
	}

	sceneManager->DeleteCamera();

	delete sceneManager;

	return 0;
}
