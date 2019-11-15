#ifndef MESHCYLINDER_H
#define MESHCYLINDER_H

#include "Mesh.h"

#define PI	(3.14)

class MeshCylinder : public Mesh {
public:
	void Init(float SizeX, float SizeZ, int GridNumX, int GridNumZ);
	void Uninit();
	void Update() {};
	void Draw();
};

#endif // !MESH_CYLINDER_H
