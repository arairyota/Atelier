#ifndef MESHWALL_H
#define MESHWALL_H


#define PI	(3.14)

class MeshWall : public Mesh {
public:
	void Init();
	void Uninit();
	void Update() {};
	void Draw();
	void Set(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scale, float SizeX, float SizeZ, float GridNumX, float GridNumZ, float uvX, float uvY);
};

#endif // !MESHWALL_H
