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
mBuffer(0)
{
	PX2_GL_CHECK(glGenBuffers(1, &mBuffer));

	PX2_GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffer);)

	PX2_GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, ibuffer->GetNumBytes(),
		ibuffer->GetData(), gOGLBufferUsage[ibuffer->GetUsage()]));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
//----------------------------------------------------------------------------
PdrIndexBuffer::~PdrIndexBuffer ()
{
	glDeleteBuffers(1, &mBuffer);
}
//----------------------------------------------------------------------------
void PdrIndexBuffer::Enable (Renderer*)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffer);
}
//----------------------------------------------------------------------------
void PdrIndexBuffer::Disable (Renderer*)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
//----------------------------------------------------------------------------
void* PdrIndexBuffer::Lock (Buffer::Locking mode)
{
	PX2_UNUSED(mode);
	assertion (false, "OpenglES does't support Lock.");
	return 0;
}
//----------------------------------------------------------------------------
void PdrIndexBuffer::Unlock ()
{
	assertion (false, "OpenglES does't support Unlock.");
}
//----------------------------------------------------------------------------
