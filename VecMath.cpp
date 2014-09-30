/* 
 * Programmer: Brian Mitzel
 * Email: bmitzel@csu.fullerton.edu
 * Course: CPSC 486
 *
 * Filename: VecMath.cpp
 *
 * This C++ source file contains the implementations of some
 * vector math helper functions.
 */

#include "VecMath.h"

// Returns the dot product of two 3D vectors
float dot( const Vec3& a, const Vec3& b )
{
	return ( a.x * b.x ) + ( a.y * b.y ) + ( a.z * b.z );
}

// Returns the cross product of two 3D vectors
Vec3 cross( const Vec3& a, const Vec3& b )
{
	return Vec3( ( ( a.y * b.z ) - ( a.z * b.y ) )
			   , ( ( a.z * b.x ) - ( a.x * b.z ) )
			   , ( ( a.x * b.y ) - ( a.y * b.x ) )
			   );
}
