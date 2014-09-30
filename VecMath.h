/* 
 * Programmer: Brian Mitzel
 * Email: bmitzel@csu.fullerton.edu
 * Course: CPSC 486
 *
 * Filename: VecMath.h
 *
 * This header includes the declarations of some helper
 * functions for vector math.
 */

#pragma once

#include "Vec3.h"

float dot( const Vec3& a, const Vec3& b );
Vec3 cross( const Vec3& a, const Vec3& b );
