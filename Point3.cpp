/* 
 * Programmer: Brian Mitzel
 * Email: bmitzel@csu.fullerton.edu
 * Course: CPSC 486
 * 
 * Filename: Point3.cpp
 *
 * A C++ model for a 3D point object.
 */

#include "Point3.h"

Vec3 Point3::operator-( const Point3& p ) const
{
	return Vec3( ( x - p.x ), ( y - p.y ), ( z - p.z ) );
}
