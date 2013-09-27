#ifndef _DEMO__DX_CRENDER_H_
#define _DEMO__DX_CRENDER_H_

#include <d3dx10.h>

#include "../Common/Import/Math/CMatrix4x4.h"
using gen::CMatrix4x4;

namespace DX {

	// This class is used to seperate the rendering code from the main DX class.
	// The Ambient colour, specular colour and specular power are already known. The only info
	// required are the texture to be used and the WorldMatrix of the model to be rendered. The
	// ambient colour, specular colour and specular power can be changed.
	//
	// Default Values:
	// Ambient Colour	RGB( 0.3f, 0.3f, 0.3f )
	// Specular Colour	RGB( 0.6f, 0.6f, 0.6f )
	// Specular Power	1
	class CRender
	{

	public:

		// The basic contructor of the CRender class.
		// The render setup will be performed here.
		CRender();

		// Basic destructor. Checks to see if the render variables have been released.
		// If not then they will be released and cleaned up here.
		~CRender();


	public:

		// This is the main render function. Only one model can be rendered at a time. The world matrix of the model to be
		// rendered is required as a parameter. Also the texture ID needs to be passed in for the model.
		void Render(const CMatrix4x4* worldMatrix, ID3D10ShaderResourceView* texture);

		// Returns the effect technique. Used for the loading of the mesh template.
		ID3D10EffectTechnique* GetTechnique() { return m_pEffectTechnique; }



		// Sets the colour of the ambient light. The old colour will be overwritten.
		void SetAmbientLight(float fR, float fG, float fB);

		// Sets the colour of the specular light. The old colour will be overwritten.
		void SetSpecularColour(float fR, float fG, float fB);

		// Sets the specular power. The old value will be overwritten.
		void SetSpecularPower(float fPower);

		// Returns the current specular power that is to be used.
		float GetSpecularPower();

		// Return the colour of the ambient light in the three variables pR, pG and pB.
		void GetAmbientLight(float* pR, float* pG, float* pB);

		// Return the colour of the specular light in the three variables pR, pG and pB.
		void GetSpecularLight(float* pR, float* pG, float* pB);

	private:

		// Storage variables. These are used to store the colours of the ambient and specular light as well as the specular
		// power ready to be passed on to the renderer. This avoids having to pass them every time the render function is called.

		D3DXCOLOR* m_pAmbientColour;// Ambient Light
		D3DXCOLOR* m_pSpecularColour;// Specular Light
		float m_SpecularPower;// Specular Power

	private:

		// These are the variables used to pass the variables to the GPU.
		ID3D10Effect* m_pEffect;
		ID3D10EffectTechnique* m_pEffectTechnique;

	};


}// namespace DX

#endif// _DEMO__DX_CRENDER_H_
