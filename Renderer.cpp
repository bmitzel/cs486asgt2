/* 
 * Programmer: Brian Mitzel
 * Email: bmitzel@csu.fullerton.edu
 * Course: CPSC 486
 * 
 * Filename: Renderer.cpp
 *
 * This is a C++ implementation of a basic OpenGL renderer.
 * It will create a window and draw 3 PLY models, a ground
 * plane, and a sky box. It supports toggling between
 * a GLSL shader program and the OpenGL fixed function
 * pipeline. It can also toggle the drawing of the models'
 * bounding volumes. Finally, it is intended to support
 * clicking on each model with the mouse to toggle the
 * drawing of that model's bounding volume on/off.
 */

#include "Renderer.h"

Renderer::Renderer( int argc, char* argv[] )
: drawBoundingSpheres( false )
, useGLSLProgram( true )
{
	Renderer::thisInstance = this;
	
	// Initialize GLUT
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
	glutInitWindowSize( 800, 600 );
	glutCreateWindow( "Picking" );
	
	// Initialize GLEW
	glewExperimental = true;
	if( glewInit( ) != GLEW_OK )
	{
		fprintf( stderr, "GLEW init failed.\n" );
		exit( 1 );
	}
	
	// Load the PLY models
	scene.Insert( "data/bunny.ply", Point3( -2.0f, 1.0f, 0.0f ) );
	scene.Insert( "data/dragon.ply", Point3( 0.0f, 1.0f, 0.0f ) );
	scene.Insert( "data/happy_buddha.ply", Point3( 2.0f, 1.0f, 0.0f ) );
	
	// Set OpenGL state
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LESS );
 	glFrontFace( GL_CCW );
 	glEnable( GL_NORMALIZE );
	
	// Load the shader program
	const char* vertexShaderSource = "blinn_phong.vert.glsl";
	const char* fragmentShaderSource = "blinn_phong.frag.glsl";
	FragmentShader fragmentShader( fragmentShaderSource );
	VertexShader vertexShader( vertexShaderSource );
	shaderProgram = new GLSLProgram( );
	shaderProgram->attach( vertexShader );
	shaderProgram->attach( fragmentShader );
	shaderProgram->link( );
	shaderProgram->activate( );
	printf( "Shader program built from %s and %s.\n", vertexShaderSource, fragmentShaderSource );
	if( shaderProgram->isActive( ) )
	{
		printf( "Shader program is loaded and active with id %d.\n", shaderProgram->id( ) );
	}
	else
	{
		printf( "Shader program did not load and activate correctly. Exiting." );
		exit( 1 );
	}

	// Set up shader program uniform variables
	uIsLightOn = glGetUniformLocation( shaderProgram->id( ), "isLightOn" );
	uLight0_position = glGetUniformLocation( shaderProgram->id( ), "light0_position" );
	uLight0_color = glGetUniformLocation( shaderProgram->id( ), "light0_color" );
	uAmbient = glGetUniformLocation( shaderProgram->id( ), "ambient" );
	uDiffuse = glGetUniformLocation( shaderProgram->id( ), "diffuse" );
	uSpecular = glGetUniformLocation( shaderProgram->id( ), "specular" );
	uShininess = glGetUniformLocation( shaderProgram->id( ), "shininess" );
  
	// Set up the light for the fixed function pipeline
	glShadeModel( GL_SMOOTH );
	GLfloat l_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat l_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat l_position[] = { 0.0, 8.0, 0.0, 1.0 };

	glLightfv( GL_LIGHT0, GL_AMBIENT, l_ambient );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, l_diffuse );
	glLightfv( GL_LIGHT0, GL_POSITION, l_position );

	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
  
	// Register callbacks with GLUT
	glutKeyboardFunc( KeyboardCallback );
	glutMouseFunc( MouseCallback );
	glutDisplayFunc( DisplayCallback );
	glutReshapeFunc( ReshapeCallback );
	glutTimerFunc( 16, UpdateCallback, 0 );
	
	// Print version info
	MsglVersion( );
	
	puts("Press 'h' to see a help message at any time.");

	glutMainLoop( );
}

Renderer::~Renderer( )
{
	delete shaderProgram;
}

bool Renderer::_MsglError( FILE* out, const char* filename, int line ) const
{
	bool ret = false;
	GLenum err = glGetError( );
	while( err != GL_NO_ERROR )
	{
		ret = true;
		fprintf( out, "GL ERROR:%s:%d: %s\n", filename, line, gluErrorString( err ) );
		err = glGetError( );
	}
	return ret;
}

void Renderer::MsglVersion( ) const
{  
	fprintf( stderr, "Vendor: %s\n", glGetString( GL_VENDOR ) );
	fprintf( stderr, "Renderer: %s\n", glGetString( GL_RENDERER ) );
	fprintf( stderr, "OpenGL Version: %s\n", glGetString( GL_VERSION ) );
	fprintf( stderr, "GLSL Version: %s\n", glGetString( GL_SHADING_LANGUAGE_VERSION ) );
}

void Renderer::PrintHelpMessage( ) const
{
	puts( "Press 'h' to print this message again." );
	puts( "Press 'b' to toggle rendering the bounding volumes." );
	puts( "Press 'g' to toggle between the GLSL program and the fixed function pipeline." );
	puts( "Press ESC or 'q' to quit." );
}

void Renderer::VecCopy4f( float *dest, const float *src ) const
{
	for( int i = 0; i < 4; i++ )
	{
		dest[ i ] = src[ i ];
	}
}

void Renderer::MatMultVec4f( float vout[ 4 ], const float v[ 4 ], float m[ 16 ] ) const
{
	float c[ 4 ];
	VecCopy4f( c, v );
	vout[ 0 ] = m[ 0 ] * c[ 0 ] + m[ 4 ] * c[ 1 ] + m[ 8 ]  * c[ 2 ] + m[ 12 ] * c[ 3 ];
	vout[ 1 ] = m[ 1 ] * c[ 0 ] + m[ 5 ] * c[ 1 ] + m[ 9 ]  * c[ 2 ] + m[ 13 ] * c[ 3 ];
	vout[ 2 ] = m[ 2 ] * c[ 0 ] + m[ 6 ] * c[ 1 ] + m[ 10 ] * c[ 2 ] + m[ 14 ] * c[ 3 ];
	vout[ 3 ] = m[ 3 ] * c[ 0 ] + m[ 7 ] * c[ 1 ] + m[ 11 ] * c[ 2 ] + m[ 15 ] * c[ 3 ];
}

void Renderer::TransformVecByModelView( float outVec[ 4 ], const float inVec[ 4 ] ) const
{
	float modelview[ 16 ];
	glGetFloatv( GL_MODELVIEW_MATRIX, modelview );
	MatMultVec4f( outVec, inVec, modelview );
}

void Renderer::DrawGroundPlane( )
{
	glBegin( GL_QUADS );
	glVertex3f( -10.0f, 0.0f, -10.0f );
	glVertex3f( -10.0f, 0.0f, 10.0f );
	glVertex3f( 10.0f, 0.0f, 10.0f );
	glVertex3f( 10.0f, 0.0f, -10.0f );
	glEnd();
}

void Renderer::DrawSkyBox( )
{
	glBegin( GL_QUADS );
	glVertex3f( -10.0f, 0.0f, -10.0f );
	glVertex3f( -10.0f, 20.0f, -10.0f );
	glVertex3f( 10.0f, 20.0f, -10.0f );
	glVertex3f( 10.0f, 0.0f, -10.0f );
	glVertex3f( -10.0f, 0.0f, 10.0f );
	glVertex3f( -10.0f, 20.0f, 10.0f );
	glVertex3f( 10.0f, 20.0f, 10.0f );
	glVertex3f( 10.0f, 0.0f, 10.0f );
	glVertex3f( -10.0f, 0.0f, -10.0f );
	glVertex3f( -10.0f, 20.0f, -10.0f );
	glVertex3f( -10.0f, 20.0f, 10.0f );
	glVertex3f( -10.0f, 0.0f, 10.0f );
	glVertex3f( 10.0f, 0.0f, -10.0f );
	glVertex3f( 10.0f, 20.0f, -10.0f );
	glVertex3f( 10.0f, 20.0f, 10.0f );
	glVertex3f( 10.0f, 0.0f, 10.0f );
	glVertex3f( -10.0f, 20.0f, -10.0f );
	glVertex3f( -10.0f, 20.0f, 10.0f );
	glVertex3f( 10.0f, 20.0f, 10.0f );
	glVertex3f( 10.0f, 20.0f, -10.0f );
	glEnd();
}

void Renderer::Pick( int mx, int my )
{
	GLint viewPort[ 4 ];
	double modelView[ 16 ];
	double projection[ 16 ];
	int wx = mx;
	int wy;
	
	// Initialize matrices and window coordinates
	glGetDoublev( GL_PROJECTION_MATRIX, projection ); // deprecated
	glGetDoublev( GL_MODELVIEW_MATRIX, modelView );   // deprecated
	glGetIntegerv( GL_VIEWPORT, viewPort );
	wy = viewPort[ 3 ] - my - 1;
	printf( "mx = %d\n", mx );
	printf( "my = %d\n", my );
	printf( "wx = %d\n", wx );
	printf( "wy = %d\n", wy );

	// Find points on front and back of view frustum
	double xx;
	double yy;
	double zz;
	gluUnProject( wx, wy, 0.0, modelView, projection, viewPort, &xx, &yy, &zz );
	float near[ 3 ] = { xx, yy, zz }; // point on front of view frustum
	printf( "near = ( %f, %f, %f )\n", near[ 0 ], near[ 1 ], near[ 2 ] );
	gluUnProject( wx, wy, 1.0, modelView, projection, viewPort, &xx, &yy, &zz );
	float far[ 3 ] = { xx, yy, zz };  // point on back of view frustum
	printf( "far = ( %f, %f, %f )\n", far[ 0 ], far[ 1 ], far[ 2 ] );

	// Cast a ray and check for intersection with scene objects
	Ray r( near, far );
	for ( std::list< Model* >::const_iterator itr = scene.GetModels( ).begin( );
		 itr != scene.GetModels( ).end( ); itr++ )
	{
		printf( "r.origin = ( %f, %f, %f )\n", r.origin.x, r.origin.y, r.origin.z );
		printf( "faceList->center = ( %f, %f, %f )\n",
				( *itr )->GetFaceList( )->center[ 0 ],
				( *itr )->GetFaceList( )->center[ 1 ],
				( *itr )->GetFaceList( )->center[ 2 ] );
		if ( ( *itr )->Intersects( r ) )
		{
			( *itr )->ToggleDrawBoundingSphere( );
		}
	}
}

void Renderer::Display( )
{
	Camera cam = scene.GetCamera( );
	
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );
	gluLookAt( cam.eyePosition.x, cam.eyePosition.y, cam.eyePosition.z,
		cam.refPoint.x, cam.refPoint.y, cam.refPoint.z,
		cam.upVector.x, cam.upVector.y, cam.upVector.z
	);

	// Set light and material properties for the models
	if ( useGLSLProgram )
	{
		TransformVecByModelView( light0, light0_position );

		glUniform4fv( uLight0_position, 1, light0 );
		glUniform4fv( uLight0_color, 1, light0_specular );

		glUniform4fv( uAmbient, 1, littleBit );
		glUniform4fv( uDiffuse, 1, medium );
		glUniform4fv( uSpecular, 1, one );
		glUniform1fv( uShininess, 1, high );
		glUniform1i( uIsLightOn, true );
	}
	else
	{
		GLfloat ambient[] = { 0.5, 0.5, 0.5 };
		GLfloat diffuse[] = { 0.07568, 0.61424, 0.07568 };
		GLfloat specular[] = { 0.633, 0.727811, 0.633 };
		GLfloat shine = 0.6;
      
		glMaterialfv( GL_FRONT, GL_AMBIENT, ambient );
		glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse );
		glMaterialfv( GL_FRONT, GL_SPECULAR, specular );
		glMaterialf( GL_FRONT, GL_SHININESS, shine * 128.0 );
	}

	// Draw the ground plane and sky box
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );
	gluLookAt( cam.eyePosition.x, cam.eyePosition.y, cam.eyePosition.z,
		cam.refPoint.x, cam.refPoint.y, cam.refPoint.z,
		cam.upVector.x, cam.upVector.y, cam.upVector.z
	);
	DrawGroundPlane( );
	DrawSkyBox( );

	// Scale and draw the models
	for ( std::list< Model* >::const_iterator itr = scene.GetModels( ).begin( );
		 itr != scene.GetModels( ).end( ); itr++ )
	{
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity( );
		gluLookAt( cam.eyePosition.x, cam.eyePosition.y, cam.eyePosition.z,
			cam.refPoint.x, cam.refPoint.y, cam.refPoint.z,
			cam.upVector.x, cam.upVector.y, cam.upVector.z
		);
		FaceList* fl = ( *itr )->GetFaceList( );
		glTranslatef( ( *itr )->location.x, ( *itr )->location.y, ( *itr )->location.z );
		double scaleFactor = 1.0 / fl->radius;
		glScalef( scaleFactor, scaleFactor, scaleFactor );

		// Draw the model
		glBegin( GL_TRIANGLES );
		for ( int i = 0; i < fl->fc; i++ )
		{
			for ( int j = 0; j < 3; j++ )
			{
				glColor3dv( fl->colors[ fl->faces[ i ][ j ] ] );
				glNormal3dv( fl->v_normals[ fl->faces[ i ][ j ] ] );
				glVertex3dv( fl->vertices[ fl->faces[ i ][ j ] ] );
			}
		}
		glEnd( );
		
		// Draw the bounding sphere
		if ( ( *itr )->DrawBoundingSphere( ) )
		{
			glutSolidSphere( fl->radius, 20, 20 );
		}
	}

	glutSwapBuffers( );
}

void Renderer::Keyboard( unsigned char key, int x, int y )
{
	switch( key )
	{
	case 'b':
		drawBoundingSpheres = !drawBoundingSpheres;
		for ( std::list< Model* >::const_iterator itr = scene.GetModels( ).begin( );
			 itr != scene.GetModels( ).end( ); itr++ )
		{
			( *itr )->SetDrawBoundingSphere( drawBoundingSpheres );
		}
		break;
	case 'g':
		if ( useGLSLProgram )
		{
			shaderProgram->deactivate( );
		}
		else
		{
			shaderProgram->activate( );
		}
		useGLSLProgram = !useGLSLProgram;
		break;
	case 'h':
		PrintHelpMessage( );
		break;
	case 27: // The 'esc' key
	case 'q':
		glutLeaveMainLoop( );
		break;
	default:
		fprintf( stderr, "You pushed '%c' (%d).\n", key, key );
		break;
	}
}

void Renderer::Mouse( int button, int state, int x, int y )
{
	if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
	{
		printf( "Mouse click at ( %d, %d )\n", x, y );
		Pick( x, y );
	}
}

void Renderer::UpdateCallback( int x )
{
	glutPostRedisplay( );
	glutTimerFunc( 16, UpdateCallback, 0 );
}

// Call Keyboard( ) on thisInstance to access class members
void Renderer::KeyboardCallback( unsigned char key, int x, int y )
{
	thisInstance->Keyboard( key, x, y );
}

// Call Mouse( ) on thisInstance to access class members
void Renderer::MouseCallback( int button, int state, int x, int y )
{
	thisInstance->Mouse( button, state, x, y );
}

void Renderer::ReshapeCallback( int width, int height )
{
	if ( height == 0 )
	{
		height = 1;
	}
	glViewport( 0, 0, static_cast< GLsizei >( width ), static_cast< GLsizei >( height ) );
	double ratio = static_cast< double >( width ) / static_cast< double >( height );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	glFrustum( -ratio, ratio, -ratio, ratio, 1.0f, 40.0f );
}

// Call Display( ) on thisInstance to access class members
void Renderer::DisplayCallback( )
{
	thisInstance->Display( );
}

Renderer* Renderer::thisInstance;
