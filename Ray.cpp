/* 
 * Programmer: Brian Mitzel
 * Email: bmitzel@csu.fullerton.edu
 * Course: CPSC 486
 * 
 * Filename: Ray.cpp
 *
 * A C++ module for a 3D Ray object.
 */

#include "Ray.h"

Ray::Ray( float near[ 3 ], float far[ 3 ] )
: origin( near[ 0 ], near[ 1 ], near[ 2 ] )
, direction( far[ 0 ] - near[ 0 ], far[ 1 ] - near[ 1 ], far[ 2 ] - near[ 2 ] )
{
}