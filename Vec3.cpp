/* 
 * Programmer: Brian Mitzel
 * Email: bmitzel@csu.fullerton.edu
 * Course: CPSC 486
 * 
 * Filename: Vec3.cpp
 *
 * Procedural module that implements a 3D Vector class
 */

#include "Vec3.h"

// Copy constructor with Vec4
Vec3::Vec3( const Vec4& v )
	: x( v.x )
	, y( v.y )
	, z( v.z )
{
}

// Returns the length of the vector
float Vec3::Length() const
{
	return sqrt( ( x * x ) + ( y * y ) + ( z * z ) );
}

// Returns the squared length of the vector
float Vec3::Length2() const
{
	return ( x * x ) + ( y * y ) + ( z * z );
}

// Returns the negative vector
Vec3 Vec3::Negative() const
{
	return Vec3( -x, -y, -z );
}

// Returns the normalized vector
Vec3 Vec3::Normal() const
{
	return Vec3( ( x / Length() ), ( y / Length() ), ( z / Length() ) );
}

// Returns the sum of this plus another Vec3
Vec3 Vec3::operator+( const Vec3& v ) const
{
	return Vec3( ( x + v.x ), ( y + v.y ), ( z + v.z ) );
}

// Returns the difference of this minus another Vec3
Vec3 Vec3::operator-( const Vec3& v ) const
{
	return Vec3( ( x - v.x ), ( y - v.y ), ( z - v.z ) );
}

// Returns the product of this times a scalar
Vec3 Vec3::operator*( float c ) const
{
	return Vec3( ( c * x ), ( c * y ), ( c * z ) );
}

// Returns the quotient of this divided by a scalar
Vec3 Vec3::operator/( float c ) const
{
	return Vec3( ( x / c ), ( y / c ), ( z / c ) );
}

// Assigns a Vec3's values to this vector and returns this vector
const Vec3& Vec3::operator=( const Vec3& v )
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this; // enables cascading assignments
}

// Prints this vector's values to a file
void Vec3::Print( FILE*& f ) const
{
	fprintf( f,
		"Vec3:\n"
		" x = %f\n"
		" y = %f\n"
		" z = %f\n"
		, x, y, z
	);
}
