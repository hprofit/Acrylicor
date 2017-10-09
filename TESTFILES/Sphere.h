// Sphere.h
// -- triangular mesh for sphere
// cs541 8/17

#ifndef CS541_SPHERE_H
#define CS541_SPHERE_H

#include <vector>
#include "Mesh3D.h"


class Sphere : public Mesh3D {
  public:
    Sphere(int mesh_size);
    int vertexCount(void);
	Vector3D* vertexArray(void);
	Vector3D* normalArray(void);
    int faceCount(void);
    Face* faceArray(void);
  private:
    std::vector<Vector3D> vertices,
                        normals;
    std::vector<Face> faces;
};


#endif

