/* 
 * Programmer: Brian Mitzel
 * Email: bmitzel@csu.fullerton.edu
 * Course: CPSC 486
 * 
 * Filename: Model.h
 *
 * A C++ module defining a 3D Model class to represent
 * objects drawn on a display.
 */

#include <string>

#include "PlyModel.h"
#include "Ray.h"
#include "Vec3.h"
#include "VecMath.h"

#ifndef MODEL_H
#define MODEL_H

class Model
{
public:
	Model( char* filename, const Point3& loc );
	bool DrawBoundingSphere( ) const;
	void SetDrawBoundingSphere( bool flag );
	void ToggleDrawBoundingSphere( );
	bool Intersects( Ray& ray );
	FaceList* GetFaceList( ) const;

	Point3 location;
private:
	bool drawBoundingSphere;
	FaceList* faceList; // contains center and radius of bounding sphere
};

#endif
