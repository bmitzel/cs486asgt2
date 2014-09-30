/* 
 * Programmer: Brian Mitzel
 * Email: bmitzel@csu.fullerton.edu
 * Course: CPSC 486
 * 
 * Filename: Ray.h
 *
 * A C++ module for a 3D Ray object.
 */

#include "Point3.h"
#include "Vec3.h"

#ifndef RAY_H
#define RAY_H

class Ray
{
public:
	Ray( float near[ 3 ], float far[ 3 ] );
	
	Point3 origin;
	Vec3 direction;
};

#endif
