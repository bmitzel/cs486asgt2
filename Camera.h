/* 
 * Programmer: Brian Mitzel
 * Email: bmitzel@csu.fullerton.edu
 * Course: CPSC 486
 * 
 * Filename: Camera.h
 *
 * A C++ module defining a Camera class for use in 3D
 * rendering
 */

#include "Point3.h"
#include "Vec3.h"

#ifndef CAMERA_H
#define CAMERA_H

class Camera
{
public:
	Camera( float eyeX, float eyeY, float eyeZ, float refX, float refY, float refZ,
		float upX, float upY, float upZ );

	Point3 eyePosition;
	Point3 refPoint;
	Vec3 upVector;
};

#endif
