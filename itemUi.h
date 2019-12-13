#ifndef ItemUI_H
#define	ItemUI_H



#include "actionUi.h"

class CPolygon;

class itemUi :
	public actionUi
{
public:
	itemUi();
	~itemUi();

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void Set(XMFLOAT2 position, XMFLOAT2 rotation, XMFLOAT2 scale, XMMATRIX mtx, CTexture* texture) override;

private:
	
};

#endif