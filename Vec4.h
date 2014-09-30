/* 
 * Programmer: Brian Mitzel
 * Email: bmitzel@csu.fullerton.edu
 * Course: CPSC 486
 * 
 * Filename: Vec4.h
 *
 * Procedural module that implements a 4D Vector Class
 */

#pragma once

#include <cmath>
#include <cstdio>

#include "Vec3.h"

class Vec3;

class Vec4
{
public:
	float x;
	float y;
	float z;
	float w;

	// Default constructor
	// When instantiating a new Vec4, w should default to 0.0 to represent a directional vector
	Vec4( float a = 0.0f, float b = 0.0f, float c = 0.0f, float d = 0.0f )
		: x( a )
		, y( b )
		, z( c )
		, w( d )
	{
	}
	
	// Copy constructor with Vec3
	Vec4( const Vec3& v );

	// Copy constructor with Vec4
	Vec4( const Vec4& v )
		: x( v.x )
		, y( v.y )
		, z( v.z )
		, w( v.w )
	{
	}

	// Destructor
	~Vec4()
	{
	}

	float Length() const;
	float Length2() const;
	Vec4 Negative() const;
	Vec4 Normal() const;
	Vec4 operator+( const Vec4& v ) const;
	Vec4 operator-( const Vec4& v ) const;
	Vec4 operator*( float c ) const;
	Vec4 operator/( float c ) const;
	const Vec4& operator=( const Vec4& v );
	void Print( FILE*& f ) const;
};
