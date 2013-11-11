#ifndef _DEMO__DX_CRENDERDEVICE_H_
#define _DEMO__DX_CRENDERDEVICE_H_

#include <d3d10.h>
#include <D3DX10.h>

#include "CVector4.h"
using gen::CVector4;

namespace DX {

	// This class acts as a wrapper for the ID3D10Device variable, making the
	// creation and use of the device easier and more convenient.
	class CRenderDevice
	{

	public:

		// Basic Constructor. All pointers will be initialized to NULL.
		CRenderDevice();

		// Destructor. Will check if all pointers have been released. If not
		// then they will be released in here. Recomend that you still call
		// DeleteDevice() instead.
		~CRenderDevice();

		// Creates the DirectX device. This must be called before the device is used.
		bool SetupDevice(HWND hWnd);

		// Deletes the device and releases all of the variables.
		void DeleteDevice();

		// Clears the screen ready for the scene to be drawn.
		void ClearScreen(const CVector4& clearColour);

		void DrawIndexed(unsigned int numIndices);

		// Presents the back buffer to the screen.
		void Present();

		// Returns a pointer to the d3d device.
		ID3D10Device* GetDevice();

	private:

		// These functions are used to split up the creation of the device.
		// This is used to make debugging the code easier.
		
		bool DeviceAndSwapChain(HRESULT& hr, HWND hWnd);
		bool RenderTargetView(HRESULT& hr);
		bool DepthStencilView(HRESULT& hr);

		// Main variables used for the device.

		// The width and height of the window.
		int	m_ViewWidth, m_ViewHeight;

		// Pointer to the main render device.
		ID3D10Device*	m_pd3dDevice;


		IDXGISwapChain*	m_pSwapChain;
		
		ID3D10RenderTargetView*	m_pRenderTargetView;
		ID3D10DepthStencilView*	m_pDepthStencilView;

		ID3D10Texture2D*		m_pDepthStencil;

	};

}// namespace DX

#endif// _DEMO__DX_CRENDERDEVICE_H_
