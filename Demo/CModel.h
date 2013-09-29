#ifndef _DEMO__DX_CMODEL_H_
#define _DEMO__DX_CMODEL_H_

#include "CMatrix4x4.h"
#include "CVector3.h"
using gen::CMatrix4x4;
using gen::CVector3;
using gen::TUInt32;

namespace DX {

	class CModel
	{

	public:

		// Basic Constructor
		CModel(TUInt32 modelID, TUInt32 templateID);

		// Basic Constructor. Set the start position of the model in ( fX, fY, fZ ).
		explicit CModel(TUInt32 modelID, TUInt32 templateID, float fX, float fY, float fZ);

		// Basic Constructor. Set the start position of the model.
		explicit CModel(TUInt32 modelID, TUInt32 templateID, const CVector3& position);

		// Basic Destructor.
		// This will delete the WorldMatrix
		~CModel();

		// Returns a pointer to the WorldMatrix.
		// This will be used for the rendering.
		CMatrix4x4* GetWorldMatrix();


		//============================================================
		// Misc
		//============================================================

		// Sets the UID of the texture to be used for rendering.
		void SetTextureID(TUInt32 texID);

		// Gets the UID of the texture to be used for rendering.
		TUInt32 GetTextureID();

		// Gets the UID of the current model.
		TUInt32 GetUID();

		// Returns the UID of the models template.
		TUInt32 GetTemplateID();

		//============================================================
		// Translation
		//============================================================

		// Move the model in the world X direction.
		void MoveX(float distance);

		// Move the model in the world Y direction.
		void MoveY(float distance);

		// Move the model in the world Z direction.
		void MoveZ(float distance);


		// Move the model in the local X direction.
		void MoveLocalX(float distance);

		// Move the model in the local Y direction.
		void MoveLocalY(float distance);

		// Move the model in the local Z direction.
		void MoveLocalZ(float distance);



		
		// Set the X position of the model.
		void SetX(float position);

		// Set the Y position of the model.
		void SetY(float position);

		// Set the Z position of the model.
		void SetZ(float position);




		// Rotate the model around the local X axis.
		void RotateX(float angle);

		// Rotate the model around the local Y axis.
		void RotateY(float angle);

		// Rotate the model around the local Z axis.
		void RotateZ(float angle);




		// Get the current X position of the model in world space.
		float GetX();

		// Get the current Y position of the model in world space.
		float GetY();

		// Get the current Z position of the model in world space.
		float GetZ();


		// Get the current position of the model in world space.
		CVector3 GetPosition();

	private:

		// The world matrix of the model.
		CMatrix4x4* m_pWorldMatrix;

		// The UID of the texture to be used when rendering.
		TUInt32 m_TextureID;

		// The UID of the model. Set in the constructor.
		TUInt32 m_ModelID;

		// The UID of the models template. This is used in rendering.
		TUInt32 m_TemplateID;

	};

}// namespace DX

#endif// _DEMO__DX_CMODEL_H_
