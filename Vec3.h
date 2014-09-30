/* 
 * Programmer: Brian Mitzel
 * Email: bmitzel@csu.fullerton.edu
 * Course: CPSC 486
 * 
 * Filename: Vec3.h
 *
 * Procedural module that implements a 3D Vector class
 */

#pragma once

#include <cmath>
#include <cstdio>

#include "Point3.h"
#include "Vec4.h"

class Vec4;

class Vec3
{
public:
	float x;
	float y;
	float z;

	// Default constructor
	Vec3( float a = 0.0f, float b = 0.0f, float c = 0.0f )
		: x( a )
		, y( b )
		, z( c )
	{
	}
	
	// Copy constructor with Point3
	Vec3( const Point3& p )
		: x( p.x )
		, y( p.y )
		, z( p.z )
	{
	}
	
	// Copy constructor with Vec3
	Vec3( const Vec3& v )
		: x( v.x )
		, y( v.y )
		, z( v.z )
	{
	}

 	// Copy constructor with Vec4
 	Vec3( const Vec4& v );

	// Destructor
	~Vec3()
	{
	}

	float Length() const;
	float Length2() const;
	Vec3 Negative() const;
	Vec3 Normal() const;
	Vec3 operator+( const Vec3& v ) const;
	Vec3 operator-( const Vec3& v ) const;
	Vec3 operator*( float c ) const;
	Vec3 operator/( float c ) const;
	const Vec3& operator=( const Vec3& v );
	void Print( FILE*& f ) const;
};
