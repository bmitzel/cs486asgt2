/* 
 * Programmer: Brian Mitzel
 * Email: bmitzel@csu.fullerton.edu
 * Course: CPSC 486
 * 
 * Filename: Vec4.cpp
 *
 * Procedural module that implements a 4D Vector class
 */

#include "Vec4.h"

// Copy constructor with Vec3
// When converting a Vec3 to a Vec4, w should default to 1.0 to represent a position
inline Vec4::Vec4( const Vec3& v )
	: x( v.x )
	, y( v.y )
	, z( v.z )
	, w( 1.0f )
{
}

// Returns the length of the vector
inline float Vec4::Length() const
{
	return sqrt( ( x * x ) + ( y * y ) + ( z * z ) + ( w * w ) );
}

// Returns the squared length of the vector
inline float Vec4::Length2() const
{
	return ( x * x ) + ( y * y ) + ( z * z ) + ( w * w );
}

// Returns the negative vector
inline Vec4 Vec4::Negative() const
{
	return Vec4( -x, -y, -z, -w );
}

// Returns the normalized vector
inline Vec4 Vec4::Normal() const
{
	return Vec4( ( x / Length() ), ( y / Length() ), ( z / Length() ), ( w / Length() ) );
}

// Returns the sum of this plus another Vec4
inline Vec4 Vec4::operator+( const Vec4& v ) const
{
	return Vec4( ( x + v.x ), ( y + v.y ), ( z + v.z ), ( w + v.w ) );
}

// Returns the difference of this minus another Vec4
inline Vec4 Vec4::operator-( const Vec4& v ) const
{
	return Vec4( ( x - v.x ), ( y - v.y ), ( z - v.z ), ( w - v.w ) );
}

// Returns the product of this times a scalar
inline Vec4 Vec4::operator*( float c ) const
{
	return Vec4( ( c * x ), ( c * y ), ( c * z ), ( c * w ) );
}

// Returns the quotient of this divided by a scalar
inline Vec4 Vec4::operator/( float c ) const
{
	return Vec4( ( x / c ), ( y / c ), ( z / c ), ( w / c ) );
}

// Assigns a Vec4's values to this vector and returns this vector
inline const Vec4& Vec4::operator=( const Vec4& v )
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
	return *this; // enables cascading assignments
}

// Prints this vector's values to a file
void Vec4::Print( FILE*& f ) const
{
	fprintf( f,
		"Vec4:\n"
		" x = %f\n"
		" y = %f\n"
		" z = %f\n"
		" w = %f\n"
		, x, y, z, w
	);
}
