/* 
 * Programmer: Brian Mitzel
 * Email: bmitzel@csu.fullerton.edu
 * Course: CPSC 486
 * 
 * Filename: Model.cpp
 *
 * A C++ module implementing a 3D Model class to represent
 * objects drawn on a display.
 */

#include "Model.h"

Model::Model( char* filename, const Point3& loc )
: location( loc )
, drawBoundingSphere( false )
{
	faceList = readPlyModel( filename );
}

bool Model::DrawBoundingSphere( ) const
{
	return drawBoundingSphere;
}

void Model::SetDrawBoundingSphere( bool flag )
{
	drawBoundingSphere = flag;
}

void Model::ToggleDrawBoundingSphere( )
{
	drawBoundingSphere = !drawBoundingSphere;
}

bool Model::Intersects( Ray& ray )
{
	printf( "faceList->center = ( %f, %f, %f )\n", faceList->center[ 0 ], faceList->center[ 1 ], faceList->center[ 2 ] );
	Vec3 l = Point3( faceList->center[ 0 ], faceList->center[ 1 ], faceList->center[ 2 ] )
		- ray.origin;
	float s = dot( l, ray.direction );
	
	// Ray points away from sphere, or squared length of l < r^2
	if ( s < 0 || l.Length2( ) < ( faceList->radius * faceList->radius ) )
	{
		return false;
	}
	
	// ?
	float msqr = l.Length2( ) - ( s * s );
	if ( msqr > ( faceList->radius * faceList->radius ) )
	{
		return false;
	}
	
	return true;
}

FaceList* Model::GetFaceList( ) const
{
	return faceList;
}
