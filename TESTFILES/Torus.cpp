// torus.cpp
// -- generate a torus mesh
// jsh 8/17

#include <fstream>
#include <cmath>
#include "Torus.h"
using namespace std;


Torus::Torus(float thickness, int size)
    : vertex_count(size*size),
      face_count(2*vertex_count) {
  const float PI = 4.0f*atan(1.0f);
  float major_radius = 1.0f/(1.0f+thickness),
        minor_radius = thickness*major_radius;

  vertices = new Vector3D[vertex_count];
  for (int j=0; j < size; ++j) {
    float phi = 2*PI*j/size;
    for (int i=0; i < size; ++i) {
      int index = size*j + i;
      float theta = 2*PI*i/size,
            rho = major_radius + minor_radius*cos(theta);
	  vertices[index].Set(rho*cos(phi), rho*sin(phi), minor_radius*sin(theta), 1.0f);
    }
  }

  normals = new Vector3D[vertex_count];
  for (int j=0; j < size; ++j) {
    float phi = 2*PI*j/size;
    for (int i=0; i < size; ++i) {
      int index = size*j + i;
      float theta = 2*PI*i/size;
	  vertices[index].Set(cos(theta)*cos(phi), cos(theta)*sin(phi), sin(theta), 0.0f);
    }
  }

  faces = new Face[face_count];
  for (int j=0; j < size; ++j) {
    int jp1 = (j+1)%size;
    for (int i=0; i < size; ++i) {
      int index = 2*(size*j+i),
          ip1 = (i+1)%size;
      faces[index][0] = size*j+i;
      faces[index][1] = size*jp1+i;
      faces[index][2] = size*jp1+ip1;
      faces[index][3] = faces[index][0];
      faces[index][4] = faces[index][2];
      faces[index][5] = size*j+ip1;
    }
  }

}


Torus::~Torus(void) {
  delete[] faces;
  delete[] normals;
  delete[] vertices;
}


int Torus::vertexCount(void) {
  return vertex_count;
}


Vector3D* Torus::vertexArray(void) {
  return vertices;
}


Vector3D* Torus::normalArray(void) {
  return normals;
}


int Torus::faceCount(void) {
  return face_count;
}


Mesh3D::Face* Torus::faceArray(void) {
  return faces;
}

