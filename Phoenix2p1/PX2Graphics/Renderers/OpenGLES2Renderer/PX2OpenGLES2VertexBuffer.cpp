/*
*
* ÎÄ¼þÃû³Æ	£º	TdOpenGLES2VertexBuffer.cpp
*
*/

#include "PX2OpenGLES2VertexBuffer.hpp"
#include "PX2OpenGLES2Mapping.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
PdrVertexBuffer::PdrVertexBuffer (Renderer*, const VertexBuffer* vbuffer)
	:
mBuffer(0)
{
	PX2_GL_CHECK(glGenBuffers(1, &mBuffer));

	PX2_GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, mBuffer));

	int eleSize = vbuffer->GetElementSize();
	int eleNum = vbuffer->GetNumElements();
	int totalSize = eleSize * eleNum;
	int numBytes = vbuffer->GetNumBytes();

	glBufferData(GL_ARRAY_BUFFER, vbuffer->GetNumBytes(), vbuffer->GetData(),
		gOGLBufferUsage[vbuffer->GetUsage()]);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
//----------------------------------------------------------------------------
PdrVertexBuffer::~PdrVertexBuffer ()
{
	glDeleteBuffers(1, &mBuffer);
}
//----------------------------------------------------------------------------
void PdrVertexBuffer::Enable (Renderer*, unsigned int, unsigned int,
							  unsigned int)
{
	glBindBuffer(GL_ARRAY_BUFFER, mBuffer);
}
//----------------------------------------------------------------------------
void PdrVertexBuffer::Disable (Renderer*, unsigned int)
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
//----------------------------------------------------------------------------
void* PdrVertexBuffer::Lock (Buffer::Locking mode)
{
	PX2_UNUSED(mode);
	assertion (false, "OpenglES2 does't support.");
	return 0;
}
//----------------------------------------------------------------------------
void PdrVertexBuffer::Unlock ()
{
	assertion (false, "OpenglES does't support.");
}
//----------------------------------------------------------------------------
