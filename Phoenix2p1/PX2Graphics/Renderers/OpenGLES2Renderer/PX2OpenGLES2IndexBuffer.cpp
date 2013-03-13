/*
*
* ÎÄ¼þÃû³Æ	£º	TdOpenGLES2IndexBuffer.cpp
*
*/

#include "PX2OpenGLES2IndexBuffer.hpp"
#include "PX2OpenGLES2Mapping.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
PdrIndexBuffer::PdrIndexBuffer (Renderer*, const IndexBuffer* ibuffer)
	:
mBuffer(0),
mIBuffer(ibuffer)
{
	PX2_GL_CHECK(glGenBuffers(1, &mBuffer));

	PX2_GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffer);)

	PX2_GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, ibuffer->GetNumBytes(),
		ibuffer->GetData(), gOGLBufferUsage[ibuffer->GetUsage()]));

	PX2_GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
//----------------------------------------------------------------------------
PdrIndexBuffer::~PdrIndexBuffer ()
{
	PX2_GL_CHECK(glDeleteBuffers(1, &mBuffer));
}
//----------------------------------------------------------------------------
void PdrIndexBuffer::Enable (Renderer*)
{
	PX2_GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffer));
}
//----------------------------------------------------------------------------
void PdrIndexBuffer::Disable (Renderer*)
{
	PX2_GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
//----------------------------------------------------------------------------
void* PdrIndexBuffer::Lock (Buffer::Locking mode)
{
	PX2_GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, mBuffer));

	int eleSize = mIBuffer->GetElementSize();
	int eleNum = mIBuffer->GetNumElements();
	int totalSize = eleSize * eleNum;
	int numBytes = mIBuffer->GetNumBytes();

	PX2_GL_CHECK(glBufferData(GL_ARRAY_BUFFER, mIBuffer->GetNumBytes(), 
		mIBuffer->GetData(), gOGLBufferUsage[mIBuffer->GetUsage()]));

	PX2_GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));

	return 0;
}
//----------------------------------------------------------------------------
void PdrIndexBuffer::Unlock ()
{
}
//----------------------------------------------------------------------------
