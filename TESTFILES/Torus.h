// torus.h
// -- triangular mesh for a torus
// cs541 8/17

#ifndef CS541_TORUS_H
#define CS541_TORUS_H

#include "Mesh3D.h"

class Torus : public Mesh3D {
  public:
    Torus(float thickness, int mesh_size);
    ~Torus(void);
    int vertexCount(void);
	Vector3D* vertexArray(void);
	Vector3D* normalArray(void);
    int faceCount(void);
    Face* faceArray(void);
  private:
    int vertex_count,
        face_count;
	Vector3D *vertices,
           *normals;
    Face *faces;
};


#endif

