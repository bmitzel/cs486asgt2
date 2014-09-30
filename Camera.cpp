/* 
 * Programmer: Brian Mitzel
 * Email: bmitzel@csu.fullerton.edu
 * Course: CPSC 486
 * 
 * Filename: Camera.cpp
 *
 * A C++ module implementing a Camera class for use in 3D
 * rendering
 */

#include "Camera.h"

Camera::Camera( float eyeX, float eyeY, float eyeZ, float refX, float refY, float refZ,
	float upX, float upY, float upZ )
: eyePosition( eyeX, eyeY, eyeZ )
, refPoint( refX, refY, refZ )
, upVector( upX, upY, upZ )
{
}
