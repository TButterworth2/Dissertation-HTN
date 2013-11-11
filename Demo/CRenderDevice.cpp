
#include "CRenderDevice.h"

namespace DX {

	// Basic Constructor. All pointers will be initialized to NULL.
	CRenderDevice::CRenderDevice()
	{
		m_ViewWidth = m_ViewHeight = 0;

		m_pd3dDevice		= NULL;
		m_pSwapChain		= NULL;

		m_pDepthStencil		= NULL;

		m_pRenderTargetView	= NULL;
		m_pDepthStencilView	= NULL;
	}

	// Destructor. Will check if all pointers have been released. If not
	// then they will be released in here. Recomend that you still call
	// DeleteDevice() instead.
	CRenderDevice::~CRenderDevice()
	{
		if( m_pd3dDevice )
		{
			DeleteDevice();
		}
	}

	// Creates the DirectX device. This must be called before the device is used.
	bool CRenderDevice::SetupDevice(HWND hWnd)
	{
		HRESULT hr = S_OK;

		if( DeviceAndSwapChain( hr, hWnd ) == false )
		{
			return false;
		}

		if( RenderTargetView( hr ) == false )
		{
			return false;
		}

		if( DepthStencilView( hr ) == false )
		{
			return false;
		}

		// Select the back buffer and depth buffer to use for rendering now
		m_pd3dDevice->OMSetRenderTargets( 1, &m_pRenderTargetView, m_pDepthStencilView );


		// Setup the viewport - defines which part of the window we will render to, almost always the whole window
		D3D10_VIEWPORT vp;
		vp.Width  = m_ViewWidth;
		vp.Height = m_ViewHeight;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		m_pd3dDevice->RSSetViewports( 1, &vp );

		
		return true;
	}

	// Deletes the device and releases all of the variables.
	void CRenderDevice::DeleteDevice()
	{
		if( m_pSwapChain )
		{
			m_pSwapChain->Release();
			m_pSwapChain = NULL;
		}

		if( m_pRenderTargetView )
		{
			m_pRenderTargetView->Release();
			m_pRenderTargetView = NULL;
		}

		if( m_pDepthStencilView )
		{
			m_pDepthStencilView->Release();
			m_pDepthStencilView = NULL;
		}

		if( m_pDepthStencil )
		{
			m_pDepthStencil->Release();
			m_pDepthStencil = NULL;
		}

		if( m_pd3dDevice )
		{
			m_pd3dDevice->ClearState();
			m_pd3dDevice->Release();

			m_pd3dDevice = NULL;
		}
	}

	// Clears the screen ready for the scene to be drawn.
	void CRenderDevice::ClearScreen(const CVector4& clearColour)
	{
		m_pd3dDevice->ClearRenderTargetView( m_pRenderTargetView, &clearColour[0] );
		m_pd3dDevice->ClearDepthStencilView( m_pDepthStencilView, D3D10_CLEAR_DEPTH | D3D10_CLEAR_STENCIL, 1.0f, 0 );
	}

	void CRenderDevice::DrawIndexed(unsigned int numIndices)
	{
		m_pd3dDevice->DrawIndexed( numIndices, 0, 0 );
	}

	// Presents the back buffer to the screen.
	void CRenderDevice::Present()
	{
		m_pSwapChain->Present( 0, NULL );
	}

	// Returns a pointer to the d3d device.
	ID3D10Device* CRenderDevice::GetDevice()
	{
		return m_pd3dDevice;
	}

	//============================================================================================================
	//============================================================================================================

	// These functions are used to split up the creation of the device.
	// This is used to make debugging the code easier.
	
	bool CRenderDevice::DeviceAndSwapChain(HRESULT& hr, HWND hWnd)
	{
		RECT rc;
		ZeroMemory( &rc, sizeof(rc) );
		GetClientRect( hWnd, &rc );

		m_ViewWidth = rc.right - rc.left;
		m_ViewHeight = rc.bottom - rc.top;


		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory( &sd, sizeof( sd ) );
		sd.BufferCount = 1;
		sd.BufferDesc.Width = m_ViewWidth;             // Target window size
		sd.BufferDesc.Height = m_ViewHeight;           // --"--
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // Pixel format of target window
		sd.BufferDesc.RefreshRate.Numerator = 60;          // Refresh rate of monitor
		sd.BufferDesc.RefreshRate.Denominator = 1;         // --"--

		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.OutputWindow = hWnd;                          // Target window
		sd.Windowed = TRUE;                                // Whether to render in a window (TRUE) or go fullscreen (FALSE)
		hr = D3D10CreateDeviceAndSwapChain( NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, 0,
											D3D10_SDK_VERSION, &sd, &m_pSwapChain, &m_pd3dDevice );
		if( FAILED( hr ) )
		{
			MessageBox( NULL, "NO DEVICE OR SWAP CHAIN", "", NULL );
			return false;
		}

		return true;
	}

	bool CRenderDevice::RenderTargetView(HRESULT& hr)
	{
		ID3D10Texture2D* pBackBuffer;
		hr = m_pSwapChain->GetBuffer( 0, __uuidof( ID3D10Texture2D ), ( LPVOID* )&pBackBuffer );
		if( FAILED( hr ) )
		{
			MessageBox( NULL, "NO back bufer", "", NULL );
			return false;
		}

		hr = m_pd3dDevice->CreateRenderTargetView( pBackBuffer, NULL, &m_pRenderTargetView );
		pBackBuffer->Release();
		if( FAILED( hr ) )
		{
			MessageBox( NULL, "NO m_pRenderTargetView", "", NULL );
			return false;
		}

		return true;
	}

	bool CRenderDevice::DepthStencilView(HRESULT& hr)
	{
		// Create a texture (bitmap) to use for a depth buffer
		D3D10_TEXTURE2D_DESC descDepth;
		descDepth.Width = m_ViewWidth;
		descDepth.Height = m_ViewHeight;
		descDepth.MipLevels = 1;
		descDepth.ArraySize = 1;
		descDepth.Format = DXGI_FORMAT_D32_FLOAT;
		descDepth.SampleDesc.Count = 1;
		descDepth.SampleDesc.Quality = 0;
		descDepth.Usage = D3D10_USAGE_DEFAULT;
		descDepth.BindFlags = D3D10_BIND_DEPTH_STENCIL;
		descDepth.CPUAccessFlags = 0;
		descDepth.MiscFlags = 0;
		hr = m_pd3dDevice->CreateTexture2D( &descDepth, NULL, &m_pDepthStencil );
		if( FAILED( hr ) )
		{
			MessageBox( NULL, "NO m_pDepthStencil", "", NULL );
			return false;
		}

		// Create the depth stencil view, i.e. indicate that the texture just created is to be used as a depth buffer
		D3D10_DEPTH_STENCIL_VIEW_DESC descDSV;
		descDSV.Format = descDepth.Format;
		descDSV.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;
		hr = m_pd3dDevice->CreateDepthStencilView( m_pDepthStencil, &descDSV, &m_pDepthStencilView );
		if( FAILED( hr ) )
		{
			MessageBox( NULL, "NO m_pDepthStencilView", "", NULL );
			return false;
		}

		return true;
	}

}// namespace DX
