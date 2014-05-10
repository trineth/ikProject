// CS184 Simple OpenGL Example
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include "point.h"
#include "link.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#ifdef OSX
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif

#include <time.h>
#include <math.h>

#ifdef _WIN32
static DWORD lastTime;
#else
static struct timeval lastTime;
#endif

#define PI 3.14159265
float posX = 0.0f;
float posY = 0.0f;
float posZ = 0.0f;
float tX = 80.0f;
float tY = -384.0f;
float tZ = -2.0f;
float fov = -23.5f;
float angle = 90;
float rotx = 239;
float roty = -153.00f;
float width = 2;

using namespace std;

//****************************************************
// Some Classes
//****************************************************
class Viewport {
  public:
    int w, h; // width and height
};


//****************************************************
// Global Variables
//****************************************************
Link[4] links;

//****************************************************
// reshape viewport if the window is resized
//****************************************************
void myReshape(int w, int h) {
  viewport.w = w;
  viewport.h = h;

  glViewport(0,0,viewport.w,viewport.h);// sets the rectangle that will be the window
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();                // loading the identity matrix for the screen

  //----------- setting the projection -------------------------
  // glOrtho sets left, right, bottom, top, zNear, zFar of the chord system


  // glOrtho(-1, 1 + (w-400)/200.0 , -1 -(h-400)/200.0, 1, 1, -1); // resize type = add
  // glOrtho(-w/400.0, w/400.0, -h/400.0, h/400.0, 1, -1); // resize type = center

  glOrtho(-1, 1, -1, 1, 1, -1);    // resize type = stretch

  //------------------------------------------------------------
}

//****************************************************
// helper methods
//****************************************************
void generateLinks() {
  link[0] = Point(0, 0, 10);
  link[1] = Point(0, 10, 10);
  link[2] = Point(5, 10, 10);
  link[3] = Point(5, 6, 10);
}

void renderVertex(Point points[], int i) {
    float* values = points[i].getValues();
    // float* normal = points[i].getNormal(posX,posY,posZ);
    // glNormal3f(normal[0], normal[1], normal[2]);
    glVertex3f(values[0], values[1], values[2]);
}

// points must have at least 4 elements
void drawRectangle(Point points[]) {
  glBegin(GL_TRIANGLES);
  renderVertex(points, 0);
  renderVertex(points, 2);
  renderVertex(points, 1);
  glEnd();

  glBegin(GL_TRIANGLES);
  renderVertex(points, 0);
  renderVertex(points, 3);
  renderVertex(points, 2);
  glEnd();
}

// Draws an arbitrary rectangle using the two link endpoints
// code adapted from stack overflow:
// http://stackoverflow.com/questions/7854043/drawing-rectangle-between-two-points-with-arbitrary-width
void drawLink(Link link) {
  Point point1 = link.getTail();
  Point point2 = link.getHead();

  //Calculate a vector between start and end points
  Point vector(point2 - point1);

  //Then calculate a perpendicular to it (just swap X and Y coordinates)
  //P.X = V.Y; //Use separate variable otherwise you overwrite X coordinate here
  //P.Y = -V.X; //Flip the sign of either the X or Y (edit by adam.wulf)
  Point perp(vector.getY(), -vector.getX(), vector.getZ());

  //Normalize that perpendicular
  float length = sqrt(perp.getX() * perp.getX() + perp.getY() * perp.getY()); //Thats length of perpendicular
  // N.X = P.X / Length;
  // N.Y = P.Y / Length; //Now N is normalized perpendicular
  Point n(perp.getX()/length, perp.getY()/length, perp.getZ());

  //Calculate 4 points that form a rectangle by adding normalized perpendicular and multiplying it by half of the desired width
  // R1.X = Point1.X + N.X * Width / 2;
  // R1.Y = Point1.Y + N.Y * Width / 2;
  // R2.X = Point1.X - N.X * Width / 2;
  // R2.Y = Point1.Y - N.Y * Width / 2;
  // R3.X = Point2.X + N.X * Width / 2;
  // R3.Y = Point2.Y + N.Y * Width / 2;
  // R4.X = Point2.X - N.X * Width / 2;
  // R4.Y = Point2.Y - N.Y * Width / 2;
  Point r1(point1 + n*width/2);
  Point r2(point1 - n*width/2);
  Point r3(point2 + n*width/2);
  Point r4(point2 - n*width/2);
  Points[4] points = {r1, r2, r3, r4};
  drawRectangle(points);
}

void printCamera() {
  std::cout << "Pos X, Y, Z:" << posX << " " << posY << " " << posZ << "\n";
  std::cout << "tX, tY, tZ:" << tX << " " << tY << " " << tZ << "\n";
  std::cout << "fov, angle:" << fov << " " << angle << " " << "\n";
  std::cout << "rotx, roty:" << rotx << " " << roty << "\n\n";
}

//****************************************************
// sets the window up
//****************************************************
void initScene(int argc, char *argv[]) {
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Clear to black, fully transparent

  myReshape(viewport.w,viewport.h);
  //parser.parse(argc, argv);

  generateLinks();
}


//***************************************************
// function that does the actual drawing
//***************************************************
void myDisplay() {

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );


  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(fov, 1.0, 0.1, 800.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  //gluLookAt(tX, tY, tZ, 0, 0, 0, 0, 1, 0);
  // glRotatef(angle, 0, 1, 0);
  glTranslatef(0,0,fov);
  glTranslatef(posX,posY,1);
  glRotatef(rotx,1,0,0);
  glRotatef(roty,0,1,0);  
  glColor3f(0.2f, 0.9f, 0.7f);

  // Enable lighting
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  GLfloat lightpos[] = {10, 10, 10, 0.};
  glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

  glPointSize(3.0f);

  // //Rendering just the points
  // glPointSize(6.0f);
  // glBegin(GL_LINES);
  // Point* points;
  // float* values;
  // for (int i = 0; i < patchNum; i++) {
  //   Patch patch = patches[i];
  //   points = patch.getPoints();
  //   for (int j = 0; j < 16; j++) {
  //     values = points[j].getValues();
  //     glVertex3f(values[0], values[1], values[2]);
  //   }

  // }
  // glEnd();

  for (int i = 0; i < 4; i++) {
    drawLink(links[i]);
  }

  glFlush();
  glutSwapBuffers();
  printCamera();
}
//****************************************************
// called by glut when there are no messages to handle
//****************************************************
void myFrameMove() {
  //nothing here for now
#ifdef _WIN32
  Sleep(10);                                   //give ~10ms back to OS (so as not to waste the CPU)
#endif
  glutPostRedisplay(); // forces glut to call the display function (myDisplay())
}

void processKeys(unsigned char key, int x, int y) {
  switch(key) {
    case 43: // +
      fov += 0.5f; break;
    case 45: // -
      fov -= 0.5f; break;
    case 61: // =
      fov += 0.5f; break;
  }
}

void processSpecialKeys(int key, int x, int y) {
  int mod = glutGetModifiers();
  switch(key) {
    case GLUT_KEY_UP :
      if (mod == GLUT_ACTIVE_SHIFT) {
        posY -= 0.5f;
      } else {
        rotx += 1.0f;
      }
      break;
    case GLUT_KEY_DOWN :
      if (mod == GLUT_ACTIVE_SHIFT) {
        posY += 0.5f;
      } else {
        rotx -= 1.0f;
      }
      break;
    case GLUT_KEY_LEFT :
      if (mod == GLUT_ACTIVE_SHIFT) {
        posX += 0.5f;
      } else {
        roty -= 1.0f;
      }
      break;
    case GLUT_KEY_RIGHT :
      if (mod == GLUT_ACTIVE_SHIFT) {
        posX -= 0.5f;
      } else {
        roty += 1.0f;
      }
      break;

    case GLUT_KEY_PAGE_UP :
      tZ += 1.0f; break;
    case GLUT_KEY_PAGE_DOWN :
      tZ -= 1.0f; break;
    case GLUT_KEY_F11 :
      fov += 1.0f; break;
    case GLUT_KEY_F12 :
      fov -= 1.0f; break;
    case GLUT_KEY_F1 :
      angle += 1.0f; break;
    case GLUT_KEY_F2 :
      angle -= 1.0f; break;
  }
}

//****************************************************
// the usual stuff, nothing exciting here
//****************************************************
int main(int argc, char *argv[]) {
  //This initializes glut
  glutInit(&argc, argv);

  //This tells glut to use a double-buffered window with red, green, and blue channels 
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  // Initalize theviewport size
  viewport.w = 800;
  viewport.h = 800;

  //The size and position of the window
  glutInitWindowSize(viewport.w, viewport.h);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Inverse Kinematics");

  initScene(argc, argv);                                 // quick function to set up scene


  glutDisplayFunc(myDisplay);                  // function to run when its time to draw something
  glutReshapeFunc(myReshape);                  // function to run when the window gets resized
  glutIdleFunc(myFrameMove);                   // function to run when not handling any other task
  glutKeyboardFunc(processKeys);
  glutSpecialFunc(processSpecialKeys);         
  glutMainLoop();                              // infinite loop that will keep drawing and resizing and whatever else

  return 0;
}








