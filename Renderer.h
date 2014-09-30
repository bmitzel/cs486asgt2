/* 
 * Programmer: Brian Mitzel
 * Email: bmitzel@csu.fullerton.edu
 * Course: CPSC 486
 * 
 * Filename: Renderer.h
 *
 * This C++ header file contains the definition of a basic
 * OpenGL Renderer object. This renderer supports drawing
 * PLY models, drawing a ground plane, and drawing a sky
 * box. It also supports mouse and keyboard input. The
 * included GLSL shader program can be toggled on or off.
 * The drawing of bounding volumes can also be toggled on
 * or off. Clicking on a model with the mouse is also
 * intended to toggle the drawing of that model's bounding
 * volume on or off.
 */

#include <cmath>
#include <list>
#include <string>

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>

#include "GLSLShader.h"
#include "PlyModel.h"
#include "Point3.h"
#include "Ray.h"
#include "Scene.h"
#include "Vec3.h"
#include "Vec4.h"

#ifndef RENDERER_H
#define RENDERER_H

#pragma GCC diagnostic ignored "-Wwrite-strings"

#define MsglError( ) _MsglError( stderr, __FILE__, __LINE__ )

const float light0_position[] = { 0.0f, 8.0f, 0.0f, 1.0f };
const float light0_specular[] = { 0.6f, 0.3f, 0.0f, 1.0f };
// specular
const float one[] = { 1.0f, 1.0f, 1.0f, 1.0f };
// diffuse
const float medium[] = { 0.5f, 0.5f, 0.5f, 1.0f };
// ambient
const float littleBit[] = { 0.2f, 0.2f, 0.2f, 1.0f };
// shininess
const float high[] = { 100.0f };

class Renderer
{
public:
	Renderer( int argc, char* argv[] );
	~Renderer( );
private:
	bool _MsglError( FILE* out, const char* filename, int line ) const;
	void MsglVersion( ) const;
	void PrintHelpMessage( ) const;
	void InitEyePosition( );
	void InitUpVector( );
	void VecCopy4f( float *dest, const float *src ) const;
	void MatMultVec4f( float vout[ 4 ], const float v[ 4 ], float m[ 16 ] ) const;
	void TransformVecByModelView( float outVec[ 4 ], const float inVec[ 4 ] ) const;
	void DrawGroundPlane( );
	void DrawSkyBox( );
	void Pick( int mx, int my );
	void Display( );
	void Keyboard( unsigned char key, int x, int y );
	void Mouse( int button, int state, int x, int y );
	static void UpdateCallback( int x );
	static void KeyboardCallback( unsigned char key, int x, int y );
	static void MouseCallback( int button, int state, int x, int y );
	static void ReshapeCallback( int width, int height );
	static void DisplayCallback( );
	
	// Reference for GLUT callback functions
	static Renderer* thisInstance;
	
	// Member variables
	Scene scene;
	GLSLProgram* shaderProgram;
	float light0[ 4 ];
	bool drawBoundingSpheres;
	bool useGLSLProgram;
	
	// Uniform params for lighting fragment shader 
	unsigned int uIsLightOn; 
	unsigned int uLight0_position;
	unsigned int uLight0_color;
	unsigned int uAmbient;
	unsigned int uDiffuse;
	unsigned int uSpecular;
	unsigned int uShininess;
};

#endif
