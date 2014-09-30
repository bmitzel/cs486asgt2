/* 
 * Programmer: Brian Mitzel
 * Email: bmitzel@csu.fullerton.edu
 * Course: CPSC 486
 * 
 * Filename: Scene.cpp
 *
 * This is a C++ implementation of a Scene object which
 * contains a list of 3D Models and a Camera object.
 */

#include "Scene.h"

Scene::Scene( )
: camera( 0.0f, 1.5f, 4.0f, 0.0f, 1.5f, 0.0f, 0.0f, 1.0f, 0.0f )
{
}

Scene::~Scene( )
{
	while ( !models.empty( ) )
	{
		delete models.back( );
		models.pop_back( );
	}
}

void Scene::Insert( char* filename, const Point3& loc )
{
	Model* newModel = new Model( filename, loc );
	models.push_back( newModel );
}

const std::list< Model* > Scene::GetModels( ) const
{
	return models;
}

const Camera& Scene::GetCamera( ) const
{
	return camera;
}
