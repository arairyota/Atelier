#ifndef POLYGON_H
#define POLYGON_H

#include "Object2d.h"
#include "texture.h"

class CPolygon : public Object2D {
private:
	bool _isDraw = false;

public:
	CPolygon() { _isDraw = false; }
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	virtual void Set(XMFLOAT2 position, XMFLOAT2 rotation, XMFLOAT2 scale, XMMATRIX mtx, CTexture* texture);
	virtual void SetLeftToRight(XMFLOAT2 position, XMFLOAT2 rotation, XMFLOAT2 scale, XMMATRIX mtx, CTexture* texture);
	virtual XMFLOAT2 GetPos() { return _position; };
	void SetDrawFlag(bool flag) { _isDraw = flag; };
	void SetPositon(XMFLOAT2 position) { _position = position; };
	void SetScaleX(float scale) { _scale.x = scale; }
};

#endif // 0