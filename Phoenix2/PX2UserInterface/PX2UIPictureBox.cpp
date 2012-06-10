/*
*
* 文件名称	：	PX2UIPictureBox.cpp
*
*/

#include "PX2UIPictureBox.hpp"
#include "PX2UIManager.hpp"
#include "PX2ResourceManager.hpp"
using namespace PX2;

PX2_IMPLEMENT_RTTI(PX2, UIElement, UIPictureBox);
PX2_IMPLEMENT_DEFAULT_NAMES(UIElement, UIPictureBox);

//----------------------------------------------------------------------------
UIPictureBox::UIPictureBox (UIElement *parent, int ID, const std::string &name,
							const std::string &textureName,
							Float4 color,
							float deltaX, float deltaY, float width, float height, bool visible)
							:
mColor(color),
UIElement(parent, ID, name, deltaX, deltaY, width, height, false, visible)
{
	mUIType = UIElement::UT_PICTUREBOX;

	VertexFormat *vformat = UIManager::GetSingleton().GetUIVertexFromat();
	float wndWidth = UIManager::GetSingleton().GetWndWidth();
	float wndHeight = UIManager::GetSingleton().GetWndHeight();

	float xmin = mPosition[0]/wndWidth;
	float xmax = (mPosition[0]+mSize[0])/wndWidth;
	float ymin = mPosition[1]/wndHeight;
	float ymax = (mPosition[1]+mSize[0])/wndHeight;

	mCamera = UIManager::GetSingleton().GetUICamera();
	mMesh = ScreenTarget::CreateRectangle(vformat, (int)wndWidth, (int)wndHeight,
		xmin, xmax, ymin, ymax, 0.0f);

	mVertexBuffer = mMesh->GetVertexBuffer();
	mIndexBuffer = mMesh->GetIndexBuffer();
	mVBA.ApplyTo(vformat, mVertexBuffer);

	SetTexture(textureName);
}
//----------------------------------------------------------------------------
UIPictureBox::~UIPictureBox ()
{
	mTexture = 0;
	mMesh = 0;
	mCamera = 0;
	mMaterialInstance = 0;
}
//----------------------------------------------------------------------------
void UIPictureBox::SetTexture (std::string textureName)
{
	if (textureName != "")
	{
		//mTexture = Texture::LoadTdtf(textureName);
		mTexture = DynamicCast<Texture2D>(ResourceManager
			::GetSingleton().GetSingleton().BlockLoad(textureName));

		assertion (mTexture!=0, "load %s faild!", textureName.c_str());

		if (mTexture)
		{
			mMaterialInstance = UIManager::GetSingleton().GetUIMaterial()->
				CreateInstance(DynamicCast<Texture2D>(mTexture));

			mMesh->SetMaterialInstance(mMaterialInstance);
		}
	}
	else
	{
		mTexture = 0;
		mMaterialInstance = 0;
		mMesh->SetMaterialInstance(0);
	}
}
//----------------------------------------------------------------------------
void UIPictureBox::SetTexture (Texture *texture)
{
	mTexture = texture;

	mMaterialInstance = UIManager::GetSingleton().GetUIMaterial()->
		CreateInstance(DynamicCast<Texture2D>(mTexture));

	mMesh->SetMaterialInstance(mMaterialInstance);
}
//----------------------------------------------------------------------------
void UIPictureBox::CalculatePostionSize ()
{
	float wndWidth = UIManager::GetSingleton().GetWndWidth();
	float wndHeight = UIManager::GetSingleton().GetWndHeight();

	float xmin = mPosition[0]/wndWidth;
	float xmax = (mPosition[0]+mSize[0])/wndWidth;
	float ymin = mPosition[1]/wndHeight;
	float ymax = (mPosition[1]+mSize[1])/wndHeight;

	mVBA.Position<Float3>(0) = Float3(xmin, ymin, 0.0f);
	mVBA.Position<Float3>(1) = Float3(xmax, ymin, 0.0f);
	mVBA.Position<Float3>(2) = Float3(xmax, ymax, 0.0f);
	mVBA.Position<Float3>(3) = Float3(xmin, ymax, 0.0f);
}
//----------------------------------------------------------------------------
void UIPictureBox::SetPosition (float offsetParentX, float offsetParentY)
{
	UIElement::SetPosition(offsetParentX, offsetParentY);

	CalculatePostionSize();

	Renderer::UpdateAll(mVertexBuffer);
}
//----------------------------------------------------------------------------
void UIPictureBox::SetSize (float width, float height)
{
	UIElement::SetSize(width, height);

	CalculatePostionSize();

	Renderer::UpdateAll(mVertexBuffer);
}
//----------------------------------------------------------------------------
void UIPictureBox::Move (float deltaX, float deltaY)
{
	UIElement::Move(deltaX, deltaY);

	CalculatePostionSize();

	Renderer::UpdateAll(mVertexBuffer);
}
//----------------------------------------------------------------------------
void UIPictureBox::SetUV (float uLeftBotton,	float vLeftBotton,
						  float uRightUp,		float vRightUp)
{
	mVBA.TCoord<Float2>(0, 0) = Float2(uLeftBotton, vLeftBotton);
	mVBA.TCoord<Float2>(0, 1) = Float2(uRightUp, vLeftBotton);
	mVBA.TCoord<Float2>(0, 3) = Float2(uRightUp, vRightUp);
	mVBA.TCoord<Float2>(0, 4) = Float2(uLeftBotton, vRightUp);

	Renderer::UpdateAll(mVertexBuffer);
}
//----------------------------------------------------------------------------
void UIPictureBox::SetUV (float uLeftBotton,	float vLeftBotton,
						  float uRightBotton,	float vRightBotton,
						  float uRightUp,		float vRightUp,
						  float uLeftUp,		float vLeftUp)
{
	mVBA.TCoord<Float2>(0, 0) = Float2(uLeftBotton, vLeftBotton);
	mVBA.TCoord<Float2>(0, 1) = Float2(uRightBotton, vRightBotton);
	mVBA.TCoord<Float2>(0, 3) = Float2(uRightUp, vRightUp);
	mVBA.TCoord<Float2>(0, 4) = Float2(uLeftUp, vLeftUp);

	Renderer::UpdateAll(mVertexBuffer);
}
//----------------------------------------------------------------------------
void UIPictureBox::GetVisibleSet (VisibleSet &set)
{
	set.Insert(mMesh);
}
//----------------------------------------------------------------------------
void UIPictureBox::Draw (Renderer *renderer)
{
	Camera *pCamera = renderer->GetCamera();

	renderer->SetCamera(mCamera);
	renderer->Draw(mMesh);

	// 置回
	renderer->SetCamera(pCamera);
}
//----------------------------------------------------------------------------