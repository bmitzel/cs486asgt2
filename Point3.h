/* 
 * Programmer: Brian Mitzel
 * Email: bmitzel@csu.fullerton.edu
 * Course: CPSC 486
 * 
 * Filename: Point3.h
 *
 * A C++ model for a 3D point object.
 */

#include "Vec3.h"

#ifndef POINT3_H
#define POINT3_H

class Vec3;

class Point3
{
public:
	Point3( float a = 0.0f, float b = 0.0f, float c = 0.0f )
	: x( a )
	, y( b )
	, z( c )
	{
		// empty function body
	}
	
	Vec3 operator-( const Point3& p ) const;
	
	float x;
	float y;
	float z;
};

#endif
