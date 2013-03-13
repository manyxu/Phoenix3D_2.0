/*
*
* 文件名称	：	PX2Font.cpp
*
*/

#include "PX2Font.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
#define BLINK_CIRCLE		1200
#define BLINK_HALFCIRCLE	600
#define BLINKMODEL_SMOOTH	1
#define BLINKMODEL_SUDDEN	2
//----------------------------------------------------------------------------
unsigned int Font::msCounts = 0;
//----------------------------------------------------------------------------
Font::Font (FontType type)
	:
mFontType(type)
{
	msCounts++;

	mCodingType = CCT_GBK;
	mFontExtStyle = FES_NORMAL;
	mFontWidth = 0;
	mFontHeight = 0;
	mCharWidth = 0.0f;
	mCharHeight = 0.0f;
	mLineInterval = 0.0f;
	mCharNumMaxCache = 0;
	mTexWidth = 0;
	mTexHeight = 0;
	mCharCodingObj = 0;
	mGlyphMap = 0;
	mShowNum = 0;

	mDrawRects.resize(FONT_MAXRECTNUM);
}
//----------------------------------------------------------------------------
Font::Font ()
{
}
//----------------------------------------------------------------------------
Font::~Font ()
{
}
//----------------------------------------------------------------------------
bool Font::Initlize (int fontWidth, int fontHeight, 
	const char *fontFilename, CharCodingType codingType,
	unsigned int fontExtStyle)
{
	mFontFilename = fontFilename;
	mCodingType = codingType;
	mFontExtStyle = fontExtStyle;

	mCharWidth = (float)fontWidth;
	mCharHeight = (float)fontHeight;
	mFontWidth = fontWidth;
	mFontHeight = fontHeight;

	return true;
}
//----------------------------------------------------------------------------
void Font::GetFontSize (int &width, int &height)
{
	width = mFontWidth;
	height = mFontHeight;
}
//----------------------------------------------------------------------------
void Font::SetCharSize (int width, int height)
{
	mCharWidth = (float)width;
	mCharHeight = (float)height;
}
//----------------------------------------------------------------------------
void Font::GetCharSize (float &width, float &height)
{
	width = (float)mCharWidth;
	height = (float)mCharHeight;
}
//----------------------------------------------------------------------------
void Font::SetLineInterval (float interval)
{
	mLineInterval = interval;
}
//----------------------------------------------------------------------------
void Font::GetLineInterval (float &interval)
{
	interval = mLineInterval;
}
//----------------------------------------------------------------------------
void Font::GetCharSize (const unsigned char *character, float &width,
	float &height)
{
	wchar_t wChar = mCharCodingObj->ToUnicode(character);
	mGlyphMap->GetUnicodeCharSize(wChar, width, height);
	height = (float)mFontHeight;
}
//----------------------------------------------------------------------------
void Font::GetCharExtent (const unsigned char *character, float &width,
	float &height)
{
	GetCharSize(character, width, height);
	width = (width/mFontWidth) * mCharWidth;
	height = (height/mFontHeight) * mCharHeight;
}
//----------------------------------------------------------------------------
void Font::GetTextExtent (const char *text, float &width, float &height,
	bool doTransfer)
{
	if (!text)
		return;

	width = 0.0f;
	height = 0.0f;

	const char *p = text;
	float allWidth = 0.0f;
	int ctrlCodeSize = 0;
	bool isFirstCharFind = false;
	CharCtrlCode ctrlCode;

	while (true)
	{
		ctrlCodeSize = mCharCodingObj->GetControlCode(p, ctrlCode, doTransfer);
		p += ctrlCodeSize;

		if (CCC_ENDOFSTRING == ctrlCode)
		{
			if (allWidth > width)
			{
				width = allWidth;
			}
			break;
		}

		if (CCC_NEWLINE == ctrlCode)
		{
			// 遇到换行，看是否更新最大行宽
			if (allWidth > width)
				width = allWidth;

			// 从新累计行宽
			allWidth = 0;

			// 清除标志，再遇到字符时累计高度
			isFirstCharFind = false;
		}
		else if (CCC_CHARACTER == ctrlCode)
		{
			float charWidth;
			float charHeight;
			unsigned char cc[4];
			int charSize = mCharCodingObj->GetAChar(p, cc);

			GetCharExtent(cc, charWidth, charHeight);
			p += charSize;
			allWidth += charWidth;

			// 如果是本行的第一个字符，累计高度
			if (!isFirstCharFind)
			{
				height += mCharHeight + mLineInterval;
				isFirstCharFind = true;
			}
		}
	}
}
//----------------------------------------------------------------------------
void Font::GetTextExtentFitInWidth (const char *text, float fixedWidth, 
	float &width, int &numBytes, bool doTransfer)
{
	if (!text)
		return;

	width = 0.0f;
	numBytes = 0;

	const char *p = text;
	int ctrlCodeSize = 0;
	CharCtrlCode ctrlCode;

	while (true)
	{
		ctrlCodeSize = mCharCodingObj->GetControlCode(p, ctrlCode, doTransfer);
		p += ctrlCodeSize;

		if (CCC_ENDOFSTRING == ctrlCode)
			break;

		if (CCC_CHARACTER == ctrlCode)
		{
			float charWidth = 0.0f;
			float charHeight = 0.0f;
			unsigned char cc[4];
			int charSize = mCharCodingObj->GetAChar(p, cc);

			GetCharExtent(cc, charWidth, charHeight);
			p += charSize;

			if (width + charWidth > fixedWidth)
				break;

			width += charWidth;
			numBytes += charSize;
		}
	}
}
//----------------------------------------------------------------------------
inline void SetupCharPoly (FontDrawRect *poly, float x, float y, float w,
	float h, const Rectf &rectUV, const Float4 &color)
{
	poly->Rect.Set(x, y, x+w, y+h);
	poly->RectUV = rectUV;
	poly->Color = color;
}
//----------------------------------------------------------------------------
void Font::TextOutM (TriMesh *mesh, const char *text, float xPos, float yPos,
	const Float4 &color, unsigned int drawStyle, bool doTransfer, float scale, 
	float depth)
{
	if (!text)
		return;

	const char *p = text;
	CharCtrlCode ctrlCode;
	int ctrlCodeSize = 0;
	float curX = xPos;
	float curY = yPos;
	Float4 curColor = color;
	Float4 shadowColor = Float4(0.0f, 0.0f, 0.0f, color[3]);
	int showCharNum = 0;
	bool blink = false;
	int blinkModel = BLINKMODEL_SMOOTH;

	while (true)
	{
		ctrlCodeSize = mCharCodingObj->GetControlCode(p, ctrlCode, doTransfer);
		p += ctrlCodeSize;

		if (CCC_ENDOFSTRING == ctrlCode)
			break;

		switch (ctrlCode)
		{
		case CCC_NEWLINE:
			{
				// 重新计算坐标
				curX = xPos;
				curY -= (mCharHeight + mLineInterval);
			}
			break;
		case CCC_CHARACTER:
			{
				// 取一个字符
				unsigned char cc[4];
				int charSize = mCharCodingObj->GetAChar(p, cc);

				// 获得字符的宽，高
				float charWidth = 0.0f;
				float charHeight = 0.0f;
				GetCharExtent(cc, charWidth, charHeight);

				Rectf rectUV;
				Texture2D *tex = TexUVMaping(cc, rectUV);

				if (0 == mTexture)
					mTexture = tex;

				charWidth *= scale;
				charHeight *= scale;

				if (mTexture == tex)
				{
					shadowColor[3] = curColor[3];

					if (drawStyle == FD_SHADOW)
					{
						SetupCharPoly(&mDrawRects[0]+mShowNum,
							curX+1.0f, curY-1.0f, charWidth, charHeight,
							rectUV, shadowColor);
						mShowNum++;
					}
					else if (drawStyle == FD_BORDER)
					{
						SetupCharPoly(&mDrawRects[0]+mShowNum, 
							curX-1.0f, curY, charWidth, charHeight, 
							rectUV, shadowColor);
						mShowNum++;
						SetupCharPoly(&mDrawRects[0]+mShowNum, 
							curX+1.0f, curY, charWidth, charHeight, 
							rectUV, shadowColor);
						mShowNum++;
						SetupCharPoly(&mDrawRects[0]+mShowNum, 
							curX, curY-1.0f, charWidth, charHeight, 
							rectUV, shadowColor);
						mShowNum++;
						SetupCharPoly(&mDrawRects[0]+mShowNum, 
							curX, curY+1.0f, charWidth, charHeight,
							rectUV, shadowColor);
						mShowNum++;
					}

					SetupCharPoly(&mDrawRects[0]+mShowNum,
						curX, curY, charWidth, charHeight, rectUV, curColor);
					mShowNum++;
					showCharNum++;
					p += charSize;
					curX += charWidth;
				}

				// 如果贴图缓存满或者多边形缓冲区满或者切换了贴图，则把当前的多边形缓冲区输出
				if (showCharNum>=mCharNumMaxCache || (mShowNum+8)>=FONT_MAXRECTNUM
					|| mTexture!=tex)
				{
					RenderText(mesh, depth);
					showCharNum = 0;
				}
			}
			break;
		case CCC_TRANSFER:
			{
				switch(*p)
				{
				case 'R':
					curColor = Float4::RED;
					p += 1;
					break;
				case 'G':
					curColor = Float4::GREEN;
					p += 1;
					break;
				case 'B':
					curColor = Float4::BLUE;
					p += 1;
					break;
				case 'K':
					curColor = Float4::BLACK;
					p += 1;
					break;
				case 'Y':
					curColor = Float4::YELLOW;
					p += 1;
					break;
				case 'W':
					curColor = Float4::WHITE;
					p += 1;
					break;
				case 'n':
					curColor = color;
					p += 1;
					blink = false;
					break;
				case 'b':
					blink = true;
					if (*(p+1) == '1')
					{
						blinkModel = BLINKMODEL_SMOOTH;
						p += 2;
					}
					else if (*(p+1) == '2')
					{
						blinkModel = BLINKMODEL_SUDDEN;
						p += 2;
					}
					else
					{
						blinkModel = BLINKMODEL_SMOOTH;
						p += 1;
					}
					break;
				}

				if (blink)
				{
					if (BLINKMODEL_SMOOTH == blinkModel)
					{
						int microSec = (int)GetTimeInMicroseconds();
						int msNum = microSec % BLINK_CIRCLE;
						if (msNum >= BLINK_HALFCIRCLE)
							msNum = BLINK_CIRCLE - msNum - 1;
						msNum = msNum*320/BLINK_HALFCIRCLE;
						if (msNum > 255)
							msNum = 255;
					}
					else
					{
						int microSec = (int)GetTimeInMicroseconds();
						if ((microSec/BLINK_HALFCIRCLE) % 2)
							curColor = Float4::ZERO;
					}
				}
			}
			break;
		default:
			break;
		} // switch (ctrlCode)
	} // while (true)

	RenderText(mesh, depth);
}
//----------------------------------------------------------------------------
void Font::TextOutRect(TriMesh *mesh, const char *text, Rectf &rect,
	float offsetX, float offsetY, bool autoWrap, const Float4 &color,
	unsigned int fontStyle, bool doTransfer, float scale)
{
	if (!text)
		return;

	const char *p = text;
	CharCtrlCode ctrlCode;
	int ctrlCodeSize = 0;
	Rectf rec = rect;
	rec.Left = (float)((int)rec.Left);
	rec.Top = (float)((int)rec.Top);
	float curX = rec.Left;
	float curY = rec.Top;
	Float4 curColor = color;
	Float4 shadowColor = Float4(0.0f, 0.0f, 0.0f, color[3]);
	int showCharNum = 0;
	bool blink = false;
	int blinkModel = BLINKMODEL_SMOOTH;

	while (true)
	{
		ctrlCodeSize = mCharCodingObj->GetControlCode(p, ctrlCode, doTransfer);
		p += ctrlCodeSize;

		if (CCC_ENDOFSTRING == ctrlCode)
			break;

		switch (ctrlCodeSize)
		{
		case CCC_NEWLINE:
			{
				curX = rec.Left;
				curY -= (mCharHeight + mLineInterval) * scale;
			}
			break;
		case CCC_CHARACTER:
			{
				float charWidth = 0.0f;
				float charHeight = 0.0f;
				Rectf rectUV;
				float xx1 = 0.0f;
				float xx2 = 0.0f;
				float yy1 = 0.0f;
				float yy2 = 0.0f;
				float uOffset1 = 0.0f;
				float uOffset2 = 0.0f;
				float vOffset1 = 0.0f;
				float vOffset2 = 0.0f;

				if (autoWrap)
				{
					float dis = GetMinDisToNewLine(p, doTransfer);
					if (dis > rec.Width())
						rec.Right = rec.Left + dis;
					if (curX+dis > rec.Right)
					{
						// 自动换行， 重新计算X坐标
						curX = rec.Left;
						curY -= (mCharHeight + mLineInterval)*scale;
						int numSpace = mCharCodingObj->JumpOverSpaces(p);
						if (numSpace > 0)
						{
							p += numSpace;
							continue;
						}
					}
				}

				// 取一个字符
				unsigned char cc[8];
				int charSize = mCharCodingObj->GetAChar(p, cc);

				// 取字符的宽，高
				GetCharExtent(cc, charWidth, charHeight);

				charWidth *= scale;
				charHeight *= scale;

				if (autoWrap)
				{
					xx1 = curX;
					xx2 = curY + charWidth;
				}
				else
				{
					xx1 = curX + offsetX;
					xx2 = curX + charWidth + offsetX;
				}
				yy1 = curY + offsetY;
				yy2 = curY + charHeight + offsetY;

				// 超出矩形区域则不显示，进行下一循环
				if (yy2<=rec.Bottom || yy1>=rec.Top ||
					(!autoWrap && (xx1>=rec.Right || xx2<=rec.Left)))
				{
					p += charSize;
					curX += charWidth;
					continue;;
				}

				// 按矩形区域裁剪字符多边形，同时计算纹理坐标偏移值
				float height = yy2 - yy1;
				if (yy1 < rec.Bottom)
				{
					vOffset1 = (rect.Bottom - yy1)/height;
					yy1 = rec.Bottom;
				}

				if (yy2 > rec.Top)
				{
					vOffset2 = (yy2 - rec.Top)/height;
					yy2 = rec.Top;
				}

				if (!autoWrap)
				{
					float width = xx2 - xx1;

					if (xx1 < rec.Left)
					{
						uOffset1 = (rec.Left - xx1)/width;
						xx1 = rec.Left;
					}
					if (xx2 > rec.Right)
					{
						uOffset2 = (xx2 - rec.Right)/width;
						xx2 = rec.Right;
					}
				}

				// 取字符的贴图数据
				Texture2D *tex = TexUVMaping(cc, rectUV);
				
				if (0 == mTexture)
				{
					mTexture = tex;
				}

				if (mTexture == tex)
				{
					// 对纹理坐标进行调整
					float uWidth = rectUV.Width();
					float vHeight = rectUV.Height();
					rectUV.Left += uOffset1 * uWidth;
					rectUV.Right -= uOffset2 * uWidth;
					rectUV.Top -= vOffset1 * vHeight;
					rectUV.Bottom += vOffset2 * vHeight;

					shadowColor[3] = curColor[3];

					if (fontStyle == FD_SHADOW)
					{
						SetupCharPoly(&mDrawRects[0]+mShowNum, 
							xx1+1.0f, yy1-1.0f, xx2-xx1, yy2-yy1, rectUV, shadowColor);
						mShowNum++;
					}
					if (fontStyle == FD_BORDER)
					{
						SetupCharPoly(&mDrawRects[0]+mShowNum, 
							xx1-1.0f, yy1, xx2-xx1, yy2-yy1, rectUV, shadowColor);
						mShowNum++;
						SetupCharPoly(&mDrawRects[0]+mShowNum, 
							xx1+1.0f, yy1, xx2-xx1, yy2-yy1, rectUV, shadowColor);
						mShowNum++;
						SetupCharPoly(&mDrawRects[0]+mShowNum, 
							xx1, yy1-1.0f, xx2-xx1, yy2-yy1, rectUV, shadowColor);
						mShowNum++;
						SetupCharPoly(&mDrawRects[0]+mShowNum, 
							xx1, yy1+1.0f, xx2-xx1, yy2-yy1, rectUV, shadowColor);
						mShowNum++;
					}
					SetupCharPoly(&mDrawRects[0]+mShowNum, 
						xx1, yy1, xx2-xx1, yy2-yy1,rectUV, curColor);
					mShowNum++;
					showCharNum++;
					p += charSize;
					curX += charWidth;
				}

				if (showCharNum>=mCharNumMaxCache || mShowNum>=FONT_MAXRECTNUM 
					|| mTexture!=tex)
				{
					RenderText(mesh);
				}
			}
			break;
		case CCC_TRANSFER:
			{
				switch (*p)
				{
				case 'R':
					curColor = Float4::RED;
					p += 1;
					break;
				case 'G':
					curColor = Float4::BLUE;
					p += 1;
					break;
				case 'B':
					curColor = Float4::BLUE;
					p += 1;
					break;
				case 'K':
					curColor = Float4::BLACK;
					p += 1;
					break;
				case 'Y':
					curColor = Float4::YELLOW;
					p += 1;
					break;
				case 'W':
					curColor = Float4::WHITE;
					p += 1;
					break;
				case 'n':
					curColor = color;
					p += 1;
					blink = false;
					break;
				case 'b':
					blink = true;
					if (*(p+1) == '1')
					{
						blinkModel = BLINKMODEL_SMOOTH;
						p += 2;
					}
					else if (*(p+1) == '2')
					{
						blinkModel = BLINKMODEL_SUDDEN;
						p += 2;
					}
					else
					{
						blinkModel = BLINKMODEL_SMOOTH;
						p += 1;
					}
					break;
				default:
					break;
				}

				if (blink)
				{
					if (BLINKMODEL_SMOOTH == blinkModel)
					{
						int microSec = (int)GetTimeInMicroseconds();
						int msNum = microSec % BLINK_CIRCLE;
						if (msNum >= BLINK_HALFCIRCLE)
							msNum = BLINK_CIRCLE - msNum - 1;
						msNum = msNum*320/BLINK_HALFCIRCLE;
						if (msNum > 255)
							msNum = 255;
					}
					else
					{
						int microSec = (int)GetTimeInMicroseconds();
						if ((microSec/BLINK_HALFCIRCLE) % 2)
							curColor = Float4::ZERO;
					}
				}
			}
			break;
		default:
			break;
		} // switch (ctrlCodeSize)
	} // whild (true)

	RenderText(mesh);
}
//----------------------------------------------------------------------------
void Font::RenderText (TriMesh *mesh, float depth)
{
	VertexFormat *vFormat = mesh->GetVertexFormat();
	VertexBuffer *vBuffer = mesh->GetVertexBuffer();
	IndexBuffer *iBuffer = mesh->GetIndexBuffer();
	if (!vBuffer)
	{
		vBuffer = new0 VertexBuffer(4*mShowNum, vFormat->GetStride(), 
			Buffer::BU_DYNAMIC);
		iBuffer = new0 IndexBuffer(6*mShowNum, 2);
		unsigned short *indices = (unsigned short*)iBuffer->GetData();
		for (int i=0; i<mShowNum; i++)
		{
			unsigned short v0 = i*4 + 0;
			unsigned short v1 = i*4 + 1;
			unsigned short v2 = i*4 + 2;
			unsigned short v3 = i*4 + 3;
			*indices++ = v0;
			*indices++ = v1;
			*indices++ = v2;
			*indices++ = v0;
			*indices++ = v2;
			*indices++ = v3;
		}

		mesh->SetVertexBuffer(vBuffer);
		mesh->SetIndexBuffer(iBuffer);
	}
	else
	{
		int vertexNum = vBuffer->GetNumElements();
		if (vertexNum < 4*mShowNum)
		{
			vBuffer = new0 VertexBuffer(4*mShowNum, vFormat->GetStride(), 
				Buffer::BU_DYNAMIC);
			iBuffer = new0 IndexBuffer(6*mShowNum, 2);
			unsigned short *indices = (unsigned short*)iBuffer->GetData();
			for (int i=0; i<mShowNum; i++)
			{
				unsigned short v0 = i*4 + 0;
				unsigned short v1 = i*4 + 1;
				unsigned short v2 = i*4 + 2;
				unsigned short v3 = i*4 + 3;
				*indices++ = v0;
				*indices++ = v1;
				*indices++ = v2;
				*indices++ = v0;
				*indices++ = v2;
				*indices++ = v3;
			}

			mesh->SetVertexBuffer(vBuffer);
			mesh->SetIndexBuffer(iBuffer);
		}
	}

	VertexBufferAccessor vba(vFormat, vBuffer);

	for (int i=0; i<mShowNum; i++)
	{
		FontDrawRect &rect = mDrawRects[i];

		vba.Position<Float3>(4*i)	= Float3(rect.Rect.Left, depth, rect.Rect.Bottom);
		vba.Color<Float4>(0, 4*i)	= rect.Color;
		vba.TCoord<Float2>(0, 4*i)	= Float2(rect.RectUV.Left, rect.RectUV.Bottom);

		vba.Position<Float3>(4*i+1) = Float3(rect.Rect.Right, depth, rect.Rect.Bottom);
		vba.Color<Float4>(0, 4*i+1) = rect.Color;
		vba.TCoord<Float2>(0, 4*i+1)= Float2(rect.RectUV.Right, rect.RectUV.Bottom);

		vba.Position<Float3>(4*i+2) = Float3(rect.Rect.Right, depth, rect.Rect.Top);
		vba.Color<Float4>(0, 4*i+2) = rect.Color;
		vba.TCoord<Float2>(0, 4*i+2)= Float2(rect.RectUV.Right, rect.RectUV.Top);

		vba.Position<Float3>(4*i+3) = Float3(rect.Rect.Left, depth, rect.Rect.Top);
		vba.Color<Float4>(0, 4*i+3) = rect.Color;
		vba.TCoord<Float2>(0, 4*i+3)= Float2(rect.RectUV.Left, rect.RectUV.Top);
	}
	vBuffer->SetNumElements(4*mShowNum);
	iBuffer->SetNumElements(6*mShowNum);
	mesh->UpdateModelSpace(Renderable::GU_MODEL_BOUND_ONLY);
	Renderer::UpdateAll(vBuffer);
	Renderer::UpdateAll(iBuffer);

	mShowNum = 0;
}
//----------------------------------------------------------------------------
float Font::GetMinDisToNewLine (const char *text, bool doTransfer)
{
	if (!text)
		return 0.0f;

	CharCtrlCode ctrlCode;
	mCharCodingObj->GetControlCode(text, ctrlCode, doTransfer);
	if (CCC_CHARACTER != ctrlCode)
		return 0.0f;	

	const unsigned char *p = (unsigned char *)text;
	float fRet = 0.0f;
	float charWidth = 0.0f;
	float charHeight = 0.0f;

	unsigned char cc[4];
	int charSize = 0;
	charSize = mCharCodingObj->GetAChar((const char*)p, cc);

	if (mCharCodingObj->IsEnglish(cc)) // 英文，不包括空格
	{
		while (true)
		{
			charSize = mCharCodingObj->GetAChar((const char*)p, cc);
			if (mCharCodingObj->IsEnglish(cc))
			{
				GetCharExtent(cc, charWidth, charHeight);
				fRet += charWidth;
				p += charSize;

				if( mCharCodingObj->IsPunctuation(cc) )
					return fRet;
			}
			else
			{
				return fRet;
			}
		}
	}
	else // 中文
	{
		GetCharExtent(cc, charWidth, charHeight);
		return charWidth;
	}

	return 0;
}
//----------------------------------------------------------------------------