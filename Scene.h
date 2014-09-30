/* 
 * Programmer: Brian Mitzel
 * Email: bmitzel@csu.fullerton.edu
 * Course: CPSC 486
 * 
 * Filename: Scene.h
 *
 * This is a C++ definition of a Scene object which
 * contains a list of 3D Models and a Camera object.
 */

#include <list>

#include "Camera.h"
#include "Model.h"

#ifndef SCENE_H
#define SCENE_H

class Scene
{
public:
	Scene( );
	~Scene( );
	void Insert( char* filename, const Point3& loc );
	const std::list< Model* > GetModels( ) const;
	const Camera& GetCamera( ) const;
private:
	std::list< Model* > models;
	Camera camera;
};

#endif
