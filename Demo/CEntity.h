#ifndef _DEMO__DX_CENTITY_H_
#define _DEMO__DX_CENTITY_H_

#include "CMatrix4x4.h"
#include "CVector3.h"
using gen::CMatrix4x4;
using gen::CVector3;

namespace Scene {

	class IEntity
	{

	public:

		IEntity() {}

		explicit IEntity(float fX, float fY, float fZ) {}

		explicit IEntity(CVector3 position) {}

		virtual ~IEntity() {};

		// Move the model in the world X direction.
		virtual void MoveX(float distance) = 0;

		// Move the model in the world Y direction.
		virtual void MoveY(float distance) = 0;

		// Move the model in the world Z direction.
		virtual void MoveZ(float distance) = 0;


		// Move the model in the local X direction.
		virtual void MoveLocalX(float distance) = 0;

		// Move the model in the local Y direction.
		virtual void MoveLocalY(float distance) = 0;

		// Move the model in the local Z direction.
		virtual void MoveLocalZ(float distance) = 0;



		
		// Set the X position of the model.
		virtual void SetX(float position) = 0;

		// Set the Y position of the model.
		virtual void SetY(float position) = 0;

		// Set the Z position of the model.
		virtual void SetZ(float position) = 0;




		// Rotate the model around the local X axis.
		virtual void RotateX(float angle) = 0;

		// Rotate the model around the local Y axis.
		virtual void RotateY(float angle) = 0;

		// Rotate the model around the local Z axis.
		virtual void RotateZ(float angle) = 0;




		// Get the current X position of the model in world space.
		virtual float GetX() = 0;

		// Get the current Y position of the model in world space.
		virtual float GetY() = 0;

		// Get the current Z position of the model in world space.
		virtual float GetZ() = 0;


		// Get the current position of the model in world space.
		virtual CVector3& GetPosition() = 0;

		// Returns the entities world matrix for use in other classes.
		virtual CMatrix4x4* GetWorldMatrix() = 0;

	};

}// namespace Scene

namespace DX {

	class CEntity : public Scene::IEntity
	{

	public:

		CEntity() : IEntity() { m_pWorldMatrix = new CMatrix4x4(CMatrix4x4::kIdentity); }

		explicit CEntity(float fX, float fY, float fZ) : IEntity( fX, fY, fZ ) { m_pWorldMatrix = new CMatrix4x4( CVector3( fX, fY, fZ ) ); }

		explicit CEntity(CVector3 position) : IEntity( position ) { m_pWorldMatrix = new CMatrix4x4( position ); }


		virtual ~CEntity() { delete m_pWorldMatrix; }



		// Move the model in the world X direction.
		virtual void MoveX(float distance);

		// Move the model in the world Y direction.
		virtual void MoveY(float distance);

		// Move the model in the world Z direction.
		virtual void MoveZ(float distance);


		// Move the model in the local X direction.
		virtual void MoveLocalX(float distance);

		// Move the model in the local Y direction.
		virtual void MoveLocalY(float distance);

		// Move the model in the local Z direction.
		virtual void MoveLocalZ(float distance);



		
		// Set the X position of the model.
		virtual void SetX(float position);

		// Set the Y position of the model.
		virtual void SetY(float position);

		// Set the Z position of the model.
		virtual void SetZ(float position);




		// Rotate the model around the local X axis.
		virtual void RotateX(float angle);

		// Rotate the model around the local Y axis.
		virtual void RotateY(float angle);

		// Rotate the model around the local Z axis.
		virtual void RotateZ(float angle);




		// Get the current X position of the model in world space.
		virtual float GetX();

		// Get the current Y position of the model in world space.
		virtual float GetY();

		// Get the current Z position of the model in world space.
		virtual float GetZ();


		// Get the current position of the model in world space.
		virtual CVector3& GetPosition();

		// Returns the entities world matrix for use in other classes.
		virtual CMatrix4x4* GetWorldMatrix() { return m_pWorldMatrix; }

	private:

		// The world matrix of the model.
		CMatrix4x4* m_pWorldMatrix;

	};

}// namespace DX

#endif// _DEMO__DX_CENTITY_H_
