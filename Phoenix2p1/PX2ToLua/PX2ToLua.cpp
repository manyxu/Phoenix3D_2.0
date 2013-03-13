/*
** Lua binding: PX2
** Generated automatically by tolua++-1.0.92 on 02/23/13 14:26:46.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_PX2_open (lua_State* tolua_S);

#include "PX2ToLua.hpp"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_Transform (lua_State* tolua_S)
{
 Transform* self = (Transform*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_UIView (lua_State* tolua_S)
{
 UIView* self = (UIView*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_Movable (lua_State* tolua_S)
{
 Movable* self = (Movable*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_UIFrame (lua_State* tolua_S)
{
 UIFrame* self = (UIFrame*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_APoint (lua_State* tolua_S)
{
 APoint* self = (APoint*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_AVector (lua_State* tolua_S)
{
 AVector* self = (AVector*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_Triangles (lua_State* tolua_S)
{
 Triangles* self = (Triangles*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_TriMesh (lua_State* tolua_S)
{
 TriMesh* self = (TriMesh*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_Float4 (lua_State* tolua_S)
{
 Float4* self = (Float4*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_MovablePtr (lua_State* tolua_S)
{
 MovablePtr* self = (MovablePtr*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_UIPicBox (lua_State* tolua_S)
{
 UIPicBox* self = (UIPicBox*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_UIStaticText (lua_State* tolua_S)
{
 UIStaticText* self = (UIStaticText*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_HPoint (lua_State* tolua_S)
{
 HPoint* self = (HPoint*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_Float3 (lua_State* tolua_S)
{
 Float3* self = (Float3*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_UIAnimPicBox (lua_State* tolua_S)
{
 UIAnimPicBox* self = (UIAnimPicBox*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_Renderable (lua_State* tolua_S)
{
 Renderable* self = (Renderable*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_UIButtonBase (lua_State* tolua_S)
{
 UIButtonBase* self = (UIButtonBase*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_UIButton (lua_State* tolua_S)
{
 UIButton* self = (UIButton*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_Node (lua_State* tolua_S)
{
 Node* self = (Node*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_SwitchNode (lua_State* tolua_S)
{
 SwitchNode* self = (SwitchNode*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_InputEventData (lua_State* tolua_S)
{
 InputEventData* self = (InputEventData*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"Sizef");
 tolua_usertype(tolua_S,"UIView");
 tolua_usertype(tolua_S,"std::vector<MultiTouchState>");
 tolua_usertype(tolua_S,"UIAnimPicBoxControl");
 tolua_usertype(tolua_S,"Controlledable");
 tolua_usertype(tolua_S,"UIFrame");
 tolua_usertype(tolua_S,"APoint");
 tolua_usertype(tolua_S,"Node");
 tolua_usertype(tolua_S,"Triangles");
 tolua_usertype(tolua_S,"TriMesh");
 tolua_usertype(tolua_S,"Float4");
 tolua_usertype(tolua_S,"MovablePtr");
 tolua_usertype(tolua_S,"UIPicBox");
 tolua_usertype(tolua_S,"HPoint");
 tolua_usertype(tolua_S,"HMatrix");
 tolua_usertype(tolua_S,"Texture2D");
 tolua_usertype(tolua_S,"UIButtonBase");
 tolua_usertype(tolua_S,"Transform");
 tolua_usertype(tolua_S,"Scene");
 tolua_usertype(tolua_S,"Vector3f");
 tolua_usertype(tolua_S,"Singleton<Project>");
 tolua_usertype(tolua_S,"Project");
 tolua_usertype(tolua_S,"std::vector<Pointer0<UIPicBox> >");
 tolua_usertype(tolua_S,"Culler");
 tolua_usertype(tolua_S,"Camera");
 tolua_usertype(tolua_S,"Renderer");
 tolua_usertype(tolua_S,"Movable");
 tolua_usertype(tolua_S,"VertexFormat");
 tolua_usertype(tolua_S,"UIManager");
 tolua_usertype(tolua_S,"IndexBuffer");
 tolua_usertype(tolua_S,"std::map<std::string,UIViewPtr>");
 tolua_usertype(tolua_S,"SwitchNode");
 tolua_usertype(tolua_S,"MouseState");
 tolua_usertype(tolua_S,"EventHandler");
 tolua_usertype(tolua_S,"Singleton<UIManager>");
 tolua_usertype(tolua_S,"MaterialInstance");
 tolua_usertype(tolua_S,"UIStaticText");
 tolua_usertype(tolua_S,"VertexBuffer");
 tolua_usertype(tolua_S,"MultiTouchState");
 tolua_usertype(tolua_S,"InputEventData");
 tolua_usertype(tolua_S,"Float3");
 tolua_usertype(tolua_S,"Font");
 tolua_usertype(tolua_S,"Renderable");
 tolua_usertype(tolua_S,"UIButton");
 tolua_usertype(tolua_S,"UIAnimPicBox");
 tolua_usertype(tolua_S,"Bound");
 tolua_usertype(tolua_S,"AVector");
 tolua_usertype(tolua_S,"Light");
}

/* method: new of class  APoint */
#ifndef TOLUA_DISABLE_tolua_PX2_APoint_new00
static int tolua_PX2_APoint_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"APoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   APoint* tolua_ret = (APoint*)  Mtolua_new((APoint)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"APoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  APoint */
#ifndef TOLUA_DISABLE_tolua_PX2_APoint_new00_local
static int tolua_PX2_APoint_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"APoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   APoint* tolua_ret = (APoint*)  Mtolua_new((APoint)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"APoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  APoint */
#ifndef TOLUA_DISABLE_tolua_PX2_APoint_new01
static int tolua_PX2_APoint_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"APoint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const APoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const APoint* pnt = ((const APoint*)  tolua_tousertype(tolua_S,2,0));
  {
   APoint* tolua_ret = (APoint*)  Mtolua_new((APoint)(*pnt));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"APoint");
  }
 }
 return 1;
tolua_lerror:
 return tolua_PX2_APoint_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  APoint */
#ifndef TOLUA_DISABLE_tolua_PX2_APoint_new01_local
static int tolua_PX2_APoint_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"APoint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const APoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const APoint* pnt = ((const APoint*)  tolua_tousertype(tolua_S,2,0));
  {
   APoint* tolua_ret = (APoint*)  Mtolua_new((APoint)(*pnt));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"APoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_PX2_APoint_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  APoint */
#ifndef TOLUA_DISABLE_tolua_PX2_APoint_new02
static int tolua_PX2_APoint_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"APoint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  float z = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   APoint* tolua_ret = (APoint*)  Mtolua_new((APoint)(x,y,z));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"APoint");
  }
 }
 return 1;
tolua_lerror:
 return tolua_PX2_APoint_new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  APoint */
#ifndef TOLUA_DISABLE_tolua_PX2_APoint_new02_local
static int tolua_PX2_APoint_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"APoint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  float z = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   APoint* tolua_ret = (APoint*)  Mtolua_new((APoint)(x,y,z));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"APoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_PX2_APoint_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  APoint */
#ifndef TOLUA_DISABLE_tolua_PX2_APoint_delete00
static int tolua_PX2_APoint_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"APoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  APoint* self = (APoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  APoint */
#ifndef TOLUA_DISABLE_tolua_PX2_APoint__sub00
static int tolua_PX2_APoint__sub00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const APoint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const APoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const APoint* self = (const APoint*)  tolua_tousertype(tolua_S,1,0);
  const APoint* pnt = ((const APoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
  {
   AVector tolua_ret = (AVector)  self->operator-(*pnt);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((AVector)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"AVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(AVector));
     tolua_pushusertype(tolua_S,tolua_obj,"AVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.sub'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  APoint */
#ifndef TOLUA_DISABLE_tolua_PX2_APoint__add00
static int tolua_PX2_APoint__add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const APoint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const AVector",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const APoint* self = (const APoint*)  tolua_tousertype(tolua_S,1,0);
  const AVector* vec = ((const AVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'", NULL);
#endif
  {
   APoint tolua_ret = (APoint)  self->operator+(*vec);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((APoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"APoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(APoint));
     tolua_pushusertype(tolua_S,tolua_obj,"APoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  APoint */
#ifndef TOLUA_DISABLE_tolua_PX2_APoint__sub01
static int tolua_PX2_APoint__sub01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const APoint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const AVector",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const APoint* self = (const APoint*)  tolua_tousertype(tolua_S,1,0);
  const AVector* vec = ((const AVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
  {
   APoint tolua_ret = (APoint)  self->operator-(*vec);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((APoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"APoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(APoint));
     tolua_pushusertype(tolua_S,tolua_obj,"APoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_PX2_APoint__sub00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  APoint */
#ifndef TOLUA_DISABLE_tolua_PX2_APoint__add01
static int tolua_PX2_APoint__add01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const APoint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const APoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const APoint* self = (const APoint*)  tolua_tousertype(tolua_S,1,0);
  const APoint* pnt = ((const APoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'", NULL);
#endif
  {
   APoint tolua_ret = (APoint)  self->operator+(*pnt);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((APoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"APoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(APoint));
     tolua_pushusertype(tolua_S,tolua_obj,"APoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_PX2_APoint__add00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator* of class  APoint */
#ifndef TOLUA_DISABLE_tolua_PX2_APoint__mul00
static int tolua_PX2_APoint__mul00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const APoint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const APoint* self = (const APoint*)  tolua_tousertype(tolua_S,1,0);
  float scalar = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator*'", NULL);
#endif
  {
   APoint tolua_ret = (APoint)  self->operator*(scalar);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((APoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"APoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(APoint));
     tolua_pushusertype(tolua_S,tolua_obj,"APoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.mul'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator/ of class  APoint */
#ifndef TOLUA_DISABLE_tolua_PX2_APoint__div00
static int tolua_PX2_APoint__div00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const APoint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const APoint* self = (const APoint*)  tolua_tousertype(tolua_S,1,0);
  float scalar = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator/'", NULL);
#endif
  {
   APoint tolua_ret = (APoint)  self->operator/(scalar);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((APoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"APoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(APoint));
     tolua_pushusertype(tolua_S,tolua_obj,"APoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.div'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  APoint */
#ifndef TOLUA_DISABLE_tolua_PX2_APoint__sub02
static int tolua_PX2_APoint__sub02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const APoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const APoint* self = (const APoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
  {
   APoint tolua_ret = (APoint)  self->operator-();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((APoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"APoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(APoint));
     tolua_pushusertype(tolua_S,tolua_obj,"APoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_PX2_APoint__sub01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Dot of class  APoint */
#ifndef TOLUA_DISABLE_tolua_PX2_APoint_Dot00
static int tolua_PX2_APoint_Dot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const APoint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const AVector",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const APoint* self = (const APoint*)  tolua_tousertype(tolua_S,1,0);
  const AVector* vec = ((const AVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Dot'", NULL);
#endif
  {
   float tolua_ret = (float)  self->Dot(*vec);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Dot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: ORIGIN of class  APoint */
#ifndef TOLUA_DISABLE_tolua_get_APoint_ORIGIN
static int tolua_get_APoint_ORIGIN(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)&APoint::ORIGIN,"const APoint");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  AVector */
#ifndef TOLUA_DISABLE_tolua_PX2_AVector_new00
static int tolua_PX2_AVector_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   AVector* tolua_ret = (AVector*)  Mtolua_new((AVector)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AVector");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  AVector */
#ifndef TOLUA_DISABLE_tolua_PX2_AVector_new00_local
static int tolua_PX2_AVector_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   AVector* tolua_ret = (AVector*)  Mtolua_new((AVector)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  AVector */
#ifndef TOLUA_DISABLE_tolua_PX2_AVector_new01
static int tolua_PX2_AVector_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AVector",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const AVector",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const AVector* vec = ((const AVector*)  tolua_tousertype(tolua_S,2,0));
  {
   AVector* tolua_ret = (AVector*)  Mtolua_new((AVector)(*vec));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AVector");
  }
 }
 return 1;
tolua_lerror:
 return tolua_PX2_AVector_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  AVector */
#ifndef TOLUA_DISABLE_tolua_PX2_AVector_new01_local
static int tolua_PX2_AVector_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AVector",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const AVector",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const AVector* vec = ((const AVector*)  tolua_tousertype(tolua_S,2,0));
  {
   AVector* tolua_ret = (AVector*)  Mtolua_new((AVector)(*vec));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_PX2_AVector_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  AVector */
#ifndef TOLUA_DISABLE_tolua_PX2_AVector_new02
static int tolua_PX2_AVector_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AVector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  float z = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   AVector* tolua_ret = (AVector*)  Mtolua_new((AVector)(x,y,z));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AVector");
  }
 }
 return 1;
tolua_lerror:
 return tolua_PX2_AVector_new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  AVector */
#ifndef TOLUA_DISABLE_tolua_PX2_AVector_new02_local
static int tolua_PX2_AVector_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AVector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  float z = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   AVector* tolua_ret = (AVector*)  Mtolua_new((AVector)(x,y,z));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_PX2_AVector_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  AVector */
#ifndef TOLUA_DISABLE_tolua_PX2_AVector_new03
static int tolua_PX2_AVector_new03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AVector",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Float3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Float3* tuple = ((const Float3*)  tolua_tousertype(tolua_S,2,0));
  {
   AVector* tolua_ret = (AVector*)  Mtolua_new((AVector)(*tuple));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AVector");
  }
 }
 return 1;
tolua_lerror:
 return tolua_PX2_AVector_new02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  AVector */
#ifndef TOLUA_DISABLE_tolua_PX2_AVector_new03_local
static int tolua_PX2_AVector_new03_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AVector",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Float3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Float3* tuple = ((const Float3*)  tolua_tousertype(tolua_S,2,0));
  {
   AVector* tolua_ret = (AVector*)  Mtolua_new((AVector)(*tuple));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_PX2_AVector_new02_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  AVector */
#ifndef TOLUA_DISABLE_tolua_PX2_AVector_new04
static int tolua_PX2_AVector_new04(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AVector",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3f",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Vector3f* vec = ((const Vector3f*)  tolua_tousertype(tolua_S,2,0));
  {
   AVector* tolua_ret = (AVector*)  Mtolua_new((AVector)(*vec));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AVector");
  }
 }
 return 1;
tolua_lerror:
 return tolua_PX2_AVector_new03(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  AVector */
#ifndef TOLUA_DISABLE_tolua_PX2_AVector_new04_local
static int tolua_PX2_AVector_new04_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AVector",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3f",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Vector3f* vec = ((const Vector3f*)  tolua_tousertype(tolua_S,2,0));
  {
   AVector* tolua_ret = (AVector*)  Mtolua_new((AVector)(*vec));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_PX2_AVector_new03_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  AVector */
#ifndef TOLUA_DISABLE_tolua_PX2_AVector_delete00
static int tolua_PX2_AVector_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AVector* self = (AVector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  AVector */
#ifndef TOLUA_DISABLE_tolua_PX2_AVector__add00
static int tolua_PX2_AVector__add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AVector",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const AVector",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const AVector* self = (const AVector*)  tolua_tousertype(tolua_S,1,0);
  const AVector* vec = ((const AVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'", NULL);
#endif
  {
   AVector tolua_ret = (AVector)  self->operator+(*vec);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((AVector)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"AVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(AVector));
     tolua_pushusertype(tolua_S,tolua_obj,"AVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  AVector */
#ifndef TOLUA_DISABLE_tolua_PX2_AVector__sub00
static int tolua_PX2_AVector__sub00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AVector",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const AVector",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const AVector* self = (const AVector*)  tolua_tousertype(tolua_S,1,0);
  const AVector* vec = ((const AVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
  {
   AVector tolua_ret = (AVector)  self->operator-(*vec);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((AVector)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"AVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(AVector));
     tolua_pushusertype(tolua_S,tolua_obj,"AVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.sub'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator* of class  AVector */
#ifndef TOLUA_DISABLE_tolua_PX2_AVector__mul00
static int tolua_PX2_AVector__mul00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AVector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const AVector* self = (const AVector*)  tolua_tousertype(tolua_S,1,0);
  float scalar = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator*'", NULL);
#endif
  {
   AVector tolua_ret = (AVector)  self->operator*(scalar);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((AVector)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"AVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(AVector));
     tolua_pushusertype(tolua_S,tolua_obj,"AVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.mul'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator/ of class  AVector */
#ifndef TOLUA_DISABLE_tolua_PX2_AVector__div00
static int tolua_PX2_AVector__div00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AVector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const AVector* self = (const AVector*)  tolua_tousertype(tolua_S,1,0);
  float scalar = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator/'", NULL);
#endif
  {
   AVector tolua_ret = (AVector)  self->operator/(scalar);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((AVector)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"AVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(AVector));
     tolua_pushusertype(tolua_S,tolua_obj,"AVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.div'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  AVector */
#ifndef TOLUA_DISABLE_tolua_PX2_AVector__sub01
static int tolua_PX2_AVector__sub01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const AVector* self = (const AVector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
  {
   AVector tolua_ret = (AVector)  self->operator-();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((AVector)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"AVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(AVector));
     tolua_pushusertype(tolua_S,tolua_obj,"AVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_PX2_AVector__sub00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Length of class  AVector */
#ifndef TOLUA_DISABLE_tolua_PX2_AVector_Length00
static int tolua_PX2_AVector_Length00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const AVector* self = (const AVector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Length'", NULL);
#endif
  {
   float tolua_ret = (float)  self->Length();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Length'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SquaredLength of class  AVector */
#ifndef TOLUA_DISABLE_tolua_PX2_AVector_SquaredLength00
static int tolua_PX2_AVector_SquaredLength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const AVector* self = (const AVector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SquaredLength'", NULL);
#endif
  {
   float tolua_ret = (float)  self->SquaredLength();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SquaredLength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Dot of class  AVector */
#ifndef TOLUA_DISABLE_tolua_PX2_AVector_Dot00
static int tolua_PX2_AVector_Dot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AVector",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const AVector",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const AVector* self = (const AVector*)  tolua_tousertype(tolua_S,1,0);
  const AVector* vec = ((const AVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Dot'", NULL);
#endif
  {
   float tolua_ret = (float)  self->Dot(*vec);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Dot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Normalize of class  AVector */
#ifndef TOLUA_DISABLE_tolua_PX2_AVector_Normalize00
static int tolua_PX2_AVector_Normalize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AVector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AVector* self = (AVector*)  tolua_tousertype(tolua_S,1,0);
  const float epsilon = ((const float)  tolua_tonumber(tolua_S,2,Mathf::ZERO_TOLERANCE));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Normalize'", NULL);
#endif
  {
   float tolua_ret = (float)  self->Normalize(epsilon);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Normalize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Cross of class  AVector */
#ifndef TOLUA_DISABLE_tolua_PX2_AVector_Cross00
static int tolua_PX2_AVector_Cross00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AVector",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const AVector",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const AVector* self = (const AVector*)  tolua_tousertype(tolua_S,1,0);
  const AVector* vec = ((const AVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Cross'", NULL);
#endif
  {
   AVector tolua_ret = (AVector)  self->Cross(*vec);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((AVector)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"AVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(AVector));
     tolua_pushusertype(tolua_S,tolua_obj,"AVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Cross'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UnitCross of class  AVector */
#ifndef TOLUA_DISABLE_tolua_PX2_AVector_UnitCross00
static int tolua_PX2_AVector_UnitCross00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AVector",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const AVector",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const AVector* self = (const AVector*)  tolua_tousertype(tolua_S,1,0);
  const AVector* vec = ((const AVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'UnitCross'", NULL);
#endif
  {
   AVector tolua_ret = (AVector)  self->UnitCross(*vec);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((AVector)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"AVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(AVector));
     tolua_pushusertype(tolua_S,tolua_obj,"AVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UnitCross'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Orthonormalize of class  AVector */
#ifndef TOLUA_DISABLE_tolua_PX2_AVector_Orthonormalize00
static int tolua_PX2_AVector_Orthonormalize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AVector",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"AVector",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"AVector",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"AVector",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AVector* vec0 = ((AVector*)  tolua_tousertype(tolua_S,2,0));
  AVector* vec1 = ((AVector*)  tolua_tousertype(tolua_S,3,0));
  AVector* vec2 = ((AVector*)  tolua_tousertype(tolua_S,4,0));
  {
   AVector::Orthonormalize(*vec0,*vec1,*vec2);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Orthonormalize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Orthonormalize of class  AVector */
#ifndef TOLUA_DISABLE_tolua_PX2_AVector_Orthonormalize01
static int tolua_PX2_AVector_Orthonormalize01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AVector",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"AVector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  AVector* vec = ((AVector*)  tolua_tousertype(tolua_S,2,0));
  {
   AVector::Orthonormalize(vec);
  }
 }
 return 0;
tolua_lerror:
 return tolua_PX2_AVector_Orthonormalize00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GenerateOrthonormalBasis of class  AVector */
#ifndef TOLUA_DISABLE_tolua_PX2_AVector_GenerateOrthonormalBasis00
static int tolua_PX2_AVector_GenerateOrthonormalBasis00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AVector",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"AVector",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"AVector",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"AVector",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AVector* vec0 = ((AVector*)  tolua_tousertype(tolua_S,2,0));
  AVector* vec1 = ((AVector*)  tolua_tousertype(tolua_S,3,0));
  AVector* vec2 = ((AVector*)  tolua_tousertype(tolua_S,4,0));
  {
   AVector::GenerateOrthonormalBasis(*vec0,*vec1,*vec2);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GenerateOrthonormalBasis'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GenerateComplementBasis of class  AVector */
#ifndef TOLUA_DISABLE_tolua_PX2_AVector_GenerateComplementBasis00
static int tolua_PX2_AVector_GenerateComplementBasis00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AVector",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"AVector",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"AVector",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const AVector",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AVector* vec0 = ((AVector*)  tolua_tousertype(tolua_S,2,0));
  AVector* vec1 = ((AVector*)  tolua_tousertype(tolua_S,3,0));
  const AVector* vec2 = ((const AVector*)  tolua_tousertype(tolua_S,4,0));
  {
   AVector::GenerateComplementBasis(*vec0,*vec1,*vec2);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GenerateComplementBasis'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: ZERO of class  AVector */
#ifndef TOLUA_DISABLE_tolua_get_AVector_ZERO
static int tolua_get_AVector_ZERO(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)&AVector::ZERO,"const AVector");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: UNIT_X of class  AVector */
#ifndef TOLUA_DISABLE_tolua_get_AVector_UNIT_X
static int tolua_get_AVector_UNIT_X(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)&AVector::UNIT_X,"const AVector");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: UNIT_Y of class  AVector */
#ifndef TOLUA_DISABLE_tolua_get_AVector_UNIT_Y
static int tolua_get_AVector_UNIT_Y(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)&AVector::UNIT_Y,"const AVector");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: UNIT_Z of class  AVector */
#ifndef TOLUA_DISABLE_tolua_get_AVector_UNIT_Z
static int tolua_get_AVector_UNIT_Z(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)&AVector::UNIT_Z,"const AVector");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  HPoint */
#ifndef TOLUA_DISABLE_tolua_PX2_HPoint_new00
static int tolua_PX2_HPoint_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"HPoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   HPoint* tolua_ret = (HPoint*)  Mtolua_new((HPoint)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"HPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  HPoint */
#ifndef TOLUA_DISABLE_tolua_PX2_HPoint_new00_local
static int tolua_PX2_HPoint_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"HPoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   HPoint* tolua_ret = (HPoint*)  Mtolua_new((HPoint)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"HPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  HPoint */
#ifndef TOLUA_DISABLE_tolua_PX2_HPoint_new01
static int tolua_PX2_HPoint_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"HPoint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const HPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const HPoint* pnt = ((const HPoint*)  tolua_tousertype(tolua_S,2,0));
  {
   HPoint* tolua_ret = (HPoint*)  Mtolua_new((HPoint)(*pnt));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"HPoint");
  }
 }
 return 1;
tolua_lerror:
 return tolua_PX2_HPoint_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  HPoint */
#ifndef TOLUA_DISABLE_tolua_PX2_HPoint_new01_local
static int tolua_PX2_HPoint_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"HPoint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const HPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const HPoint* pnt = ((const HPoint*)  tolua_tousertype(tolua_S,2,0));
  {
   HPoint* tolua_ret = (HPoint*)  Mtolua_new((HPoint)(*pnt));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"HPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_PX2_HPoint_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  HPoint */
#ifndef TOLUA_DISABLE_tolua_PX2_HPoint_new02
static int tolua_PX2_HPoint_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"HPoint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  float z = ((float)  tolua_tonumber(tolua_S,4,0));
  float w = ((float)  tolua_tonumber(tolua_S,5,0));
  {
   HPoint* tolua_ret = (HPoint*)  Mtolua_new((HPoint)(x,y,z,w));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"HPoint");
  }
 }
 return 1;
tolua_lerror:
 return tolua_PX2_HPoint_new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  HPoint */
#ifndef TOLUA_DISABLE_tolua_PX2_HPoint_new02_local
static int tolua_PX2_HPoint_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"HPoint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  float z = ((float)  tolua_tonumber(tolua_S,4,0));
  float w = ((float)  tolua_tonumber(tolua_S,5,0));
  {
   HPoint* tolua_ret = (HPoint*)  Mtolua_new((HPoint)(x,y,z,w));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"HPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_PX2_HPoint_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  HPoint */
#ifndef TOLUA_DISABLE_tolua_PX2_HPoint_delete00
static int tolua_PX2_HPoint_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"HPoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  HPoint* self = (HPoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator[] of class  HPoint */
#ifndef TOLUA_DISABLE_tolua_PX2_HPoint__geti00
static int tolua_PX2_HPoint__geti00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const HPoint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const HPoint* self = (const HPoint*)  tolua_tousertype(tolua_S,1,0);
  int i = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator[]'", NULL);
#endif
  {
   float tolua_ret = (float)  self->operator[](i);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.geti'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator&[] of class  HPoint */
#ifndef TOLUA_DISABLE_tolua_PX2_HPoint__seti00
static int tolua_PX2_HPoint__seti00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"HPoint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  HPoint* self = (HPoint*)  tolua_tousertype(tolua_S,1,0);
  int i = ((int)  tolua_tonumber(tolua_S,2,0));
  float tolua_value = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator&[]'", NULL);
#endif
  self->operator[](i) =  tolua_value;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.seti'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator[] of class  HPoint */
#ifndef TOLUA_DISABLE_tolua_PX2_HPoint__geti01
static int tolua_PX2_HPoint__geti01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"HPoint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  HPoint* self = (HPoint*)  tolua_tousertype(tolua_S,1,0);
  int i = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator[]'", NULL);
#endif
  {
   float tolua_ret = (float)  self->operator[](i);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_PX2_HPoint__geti00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: X of class  HPoint */
#ifndef TOLUA_DISABLE_tolua_PX2_HPoint_X00
static int tolua_PX2_HPoint_X00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const HPoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const HPoint* self = (const HPoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'X'", NULL);
#endif
  {
   float tolua_ret = (float)  self->X();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'X'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: X of class  HPoint */
#ifndef TOLUA_DISABLE_tolua_PX2_HPoint_X01
static int tolua_PX2_HPoint_X01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"HPoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  HPoint* self = (HPoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'X'", NULL);
#endif
  {
   float tolua_ret = (float)  self->X();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_PX2_HPoint_X00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Y of class  HPoint */
#ifndef TOLUA_DISABLE_tolua_PX2_HPoint_Y00
static int tolua_PX2_HPoint_Y00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const HPoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const HPoint* self = (const HPoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Y'", NULL);
#endif
  {
   float tolua_ret = (float)  self->Y();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Y'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Y of class  HPoint */
#ifndef TOLUA_DISABLE_tolua_PX2_HPoint_Y01
static int tolua_PX2_HPoint_Y01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"HPoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  HPoint* self = (HPoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Y'", NULL);
#endif
  {
   float tolua_ret = (float)  self->Y();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_PX2_HPoint_Y00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Z of class  HPoint */
#ifndef TOLUA_DISABLE_tolua_PX2_HPoint_Z00
static int tolua_PX2_HPoint_Z00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const HPoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const HPoint* self = (const HPoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Z'", NULL);
#endif
  {
   float tolua_ret = (float)  self->Z();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Z'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Z of class  HPoint */
#ifndef TOLUA_DISABLE_tolua_PX2_HPoint_Z01
static int tolua_PX2_HPoint_Z01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"HPoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  HPoint* self = (HPoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Z'", NULL);
#endif
  {
   float tolua_ret = (float)  self->Z();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_PX2_HPoint_Z00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: W of class  HPoint */
#ifndef TOLUA_DISABLE_tolua_PX2_HPoint_W00
static int tolua_PX2_HPoint_W00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const HPoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const HPoint* self = (const HPoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'W'", NULL);
#endif
  {
   float tolua_ret = (float)  self->W();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'W'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: W of class  HPoint */
#ifndef TOLUA_DISABLE_tolua_PX2_HPoint_W01
static int tolua_PX2_HPoint_W01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"HPoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  HPoint* self = (HPoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'W'", NULL);
#endif
  {
   float tolua_ret = (float)  self->W();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_PX2_HPoint_W00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  HPoint */
#ifndef TOLUA_DISABLE_tolua_PX2_HPoint__eq00
static int tolua_PX2_HPoint__eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const HPoint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const HPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const HPoint* self = (const HPoint*)  tolua_tousertype(tolua_S,1,0);
  const HPoint* pnt = ((const HPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*pnt);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator< of class  HPoint */
#ifndef TOLUA_DISABLE_tolua_PX2_HPoint__lt00
static int tolua_PX2_HPoint__lt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const HPoint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const HPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const HPoint* self = (const HPoint*)  tolua_tousertype(tolua_S,1,0);
  const HPoint* pnt = ((const HPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator<'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator<(*pnt);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.lt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator<= of class  HPoint */
#ifndef TOLUA_DISABLE_tolua_PX2_HPoint__le00
static int tolua_PX2_HPoint__le00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const HPoint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const HPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const HPoint* self = (const HPoint*)  tolua_tousertype(tolua_S,1,0);
  const HPoint* pnt = ((const HPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator<='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator<=(*pnt);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.le'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Transform */
#ifndef TOLUA_DISABLE_tolua_PX2_Transform_new00
static int tolua_PX2_Transform_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Transform",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Transform* tolua_ret = (Transform*)  Mtolua_new((Transform)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Transform");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Transform */
#ifndef TOLUA_DISABLE_tolua_PX2_Transform_new00_local
static int tolua_PX2_Transform_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Transform",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Transform* tolua_ret = (Transform*)  Mtolua_new((Transform)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Transform");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  Transform */
#ifndef TOLUA_DISABLE_tolua_PX2_Transform_delete00
static int tolua_PX2_Transform_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Transform",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Transform* self = (Transform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MakeIdentity of class  Transform */
#ifndef TOLUA_DISABLE_tolua_PX2_Transform_MakeIdentity00
static int tolua_PX2_Transform_MakeIdentity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Transform",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Transform* self = (Transform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MakeIdentity'", NULL);
#endif
  {
   self->MakeIdentity();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MakeIdentity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MakeUnitScale of class  Transform */
#ifndef TOLUA_DISABLE_tolua_PX2_Transform_MakeUnitScale00
static int tolua_PX2_Transform_MakeUnitScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Transform",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Transform* self = (Transform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MakeUnitScale'", NULL);
#endif
  {
   self->MakeUnitScale();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MakeUnitScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsIdentity of class  Transform */
#ifndef TOLUA_DISABLE_tolua_PX2_Transform_IsIdentity00
static int tolua_PX2_Transform_IsIdentity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Transform",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Transform* self = (const Transform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsIdentity'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsIdentity();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsIdentity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsRSMatrix of class  Transform */
#ifndef TOLUA_DISABLE_tolua_PX2_Transform_IsRSMatrix00
static int tolua_PX2_Transform_IsRSMatrix00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Transform",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Transform* self = (const Transform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsRSMatrix'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsRSMatrix();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsRSMatrix'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsUniformScale of class  Transform */
#ifndef TOLUA_DISABLE_tolua_PX2_Transform_IsUniformScale00
static int tolua_PX2_Transform_IsUniformScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Transform",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Transform* self = (const Transform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsUniformScale'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsUniformScale();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsUniformScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRotate of class  Transform */
#ifndef TOLUA_DISABLE_tolua_PX2_Transform_SetRotate00
static int tolua_PX2_Transform_SetRotate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Transform",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const HMatrix",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Transform* self = (Transform*)  tolua_tousertype(tolua_S,1,0);
  const HMatrix* rotate = ((const HMatrix*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRotate'", NULL);
#endif
  {
   self->SetRotate(*rotate);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRotate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMatrix of class  Transform */
#ifndef TOLUA_DISABLE_tolua_PX2_Transform_SetMatrix00
static int tolua_PX2_Transform_SetMatrix00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Transform",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const HMatrix",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Transform* self = (Transform*)  tolua_tousertype(tolua_S,1,0);
  const HMatrix* matrix = ((const HMatrix*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMatrix'", NULL);
#endif
  {
   self->SetMatrix(*matrix);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMatrix'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTranslate of class  Transform */
#ifndef TOLUA_DISABLE_tolua_PX2_Transform_SetTranslate00
static int tolua_PX2_Transform_SetTranslate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Transform",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const APoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Transform* self = (Transform*)  tolua_tousertype(tolua_S,1,0);
  const APoint* translate = ((const APoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTranslate'", NULL);
#endif
  {
   self->SetTranslate(*translate);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTranslate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetScale of class  Transform */
#ifndef TOLUA_DISABLE_tolua_PX2_Transform_SetScale00
static int tolua_PX2_Transform_SetScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Transform",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const APoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Transform* self = (Transform*)  tolua_tousertype(tolua_S,1,0);
  const APoint* scale = ((const APoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetScale'", NULL);
#endif
  {
   self->SetScale(*scale);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetUniformScale of class  Transform */
#ifndef TOLUA_DISABLE_tolua_PX2_Transform_SetUniformScale00
static int tolua_PX2_Transform_SetUniformScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Transform",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Transform* self = (Transform*)  tolua_tousertype(tolua_S,1,0);
  float scale = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetUniformScale'", NULL);
#endif
  {
   self->SetUniformScale(scale);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetUniformScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRotate of class  Transform */
#ifndef TOLUA_DISABLE_tolua_PX2_Transform_GetRotate00
static int tolua_PX2_Transform_GetRotate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Transform",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Transform* self = (const Transform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRotate'", NULL);
#endif
  {
   const HMatrix& tolua_ret = (const HMatrix&)  self->GetRotate();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const HMatrix");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRotate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMatrix of class  Transform */
#ifndef TOLUA_DISABLE_tolua_PX2_Transform_GetMatrix00
static int tolua_PX2_Transform_GetMatrix00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Transform",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Transform* self = (const Transform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMatrix'", NULL);
#endif
  {
   const HMatrix& tolua_ret = (const HMatrix&)  self->GetMatrix();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const HMatrix");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMatrix'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTranslate of class  Transform */
#ifndef TOLUA_DISABLE_tolua_PX2_Transform_GetTranslate00
static int tolua_PX2_Transform_GetTranslate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Transform",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Transform* self = (const Transform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTranslate'", NULL);
#endif
  {
   const APoint& tolua_ret = (const APoint&)  self->GetTranslate();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const APoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTranslate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetScale of class  Transform */
#ifndef TOLUA_DISABLE_tolua_PX2_Transform_GetScale00
static int tolua_PX2_Transform_GetScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Transform",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Transform* self = (const Transform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetScale'", NULL);
#endif
  {
   const APoint& tolua_ret = (const APoint&)  self->GetScale();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const APoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetUniformScale of class  Transform */
#ifndef TOLUA_DISABLE_tolua_PX2_Transform_GetUniformScale00
static int tolua_PX2_Transform_GetUniformScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Transform",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Transform* self = (const Transform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetUniformScale'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetUniformScale();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetUniformScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNorm of class  Transform */
#ifndef TOLUA_DISABLE_tolua_PX2_Transform_GetNorm00
static int tolua_PX2_Transform_GetNorm00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Transform",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Transform* self = (const Transform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNorm'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetNorm();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNorm'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator* of class  Transform */
#ifndef TOLUA_DISABLE_tolua_PX2_Transform__mul00
static int tolua_PX2_Transform__mul00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Transform",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const APoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Transform* self = (const Transform*)  tolua_tousertype(tolua_S,1,0);
  const APoint* pnt = ((const APoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator*'", NULL);
#endif
  {
   APoint tolua_ret = (APoint)  self->operator*(*pnt);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((APoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"APoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(APoint));
     tolua_pushusertype(tolua_S,tolua_obj,"APoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.mul'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator* of class  Transform */
#ifndef TOLUA_DISABLE_tolua_PX2_Transform__mul01
static int tolua_PX2_Transform__mul01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Transform",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const AVector",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Transform* self = (const Transform*)  tolua_tousertype(tolua_S,1,0);
  const AVector* vec = ((const AVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator*'", NULL);
#endif
  {
   AVector tolua_ret = (AVector)  self->operator*(*vec);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((AVector)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"AVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(AVector));
     tolua_pushusertype(tolua_S,tolua_obj,"AVector");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_PX2_Transform__mul00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator* of class  Transform */
#ifndef TOLUA_DISABLE_tolua_PX2_Transform__mul02
static int tolua_PX2_Transform__mul02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Transform",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Transform",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Transform* self = (const Transform*)  tolua_tousertype(tolua_S,1,0);
  const Transform* transform = ((const Transform*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator*'", NULL);
#endif
  {
   Transform tolua_ret = (Transform)  self->operator*(*transform);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((Transform)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"Transform");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Transform));
     tolua_pushusertype(tolua_S,tolua_obj,"Transform");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_PX2_Transform__mul01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Matrix of class  Transform */
#ifndef TOLUA_DISABLE_tolua_PX2_Transform_Matrix00
static int tolua_PX2_Transform_Matrix00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Transform",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Transform* self = (const Transform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Matrix'", NULL);
#endif
  {
   const HMatrix& tolua_ret = (const HMatrix&)  self->Matrix();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const HMatrix");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Matrix'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Inverse of class  Transform */
#ifndef TOLUA_DISABLE_tolua_PX2_Transform_Inverse00
static int tolua_PX2_Transform_Inverse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Transform",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Transform* self = (const Transform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Inverse'", NULL);
#endif
  {
   const HMatrix& tolua_ret = (const HMatrix&)  self->Inverse();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const HMatrix");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Inverse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: InverseTransform of class  Transform */
#ifndef TOLUA_DISABLE_tolua_PX2_Transform_InverseTransform00
static int tolua_PX2_Transform_InverseTransform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Transform",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Transform* self = (const Transform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'InverseTransform'", NULL);
#endif
  {
   Transform tolua_ret = (Transform)  self->InverseTransform();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((Transform)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"Transform");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Transform));
     tolua_pushusertype(tolua_S,tolua_obj,"Transform");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InverseTransform'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: IDENTITY of class  Transform */
#ifndef TOLUA_DISABLE_tolua_get_Transform_IDENTITY
static int tolua_get_Transform_IDENTITY(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)&Transform::IDENTITY,"const Transform");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetStreamingSize of class  Transform */
#ifndef TOLUA_DISABLE_tolua_PX2_Transform_GetStreamingSize00
static int tolua_PX2_Transform_GetStreamingSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Transform",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   int tolua_ret = (int)  Transform::GetStreamingSize();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetStreamingSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  Movable */
#ifndef TOLUA_DISABLE_tolua_PX2_Movable_delete00
static int tolua_PX2_Movable_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Movable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Movable* self = (Movable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: LocalTransform of class  Movable */
#ifndef TOLUA_DISABLE_tolua_get_Movable_LocalTransform
static int tolua_get_Movable_LocalTransform(lua_State* tolua_S)
{
  Movable* self = (Movable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'LocalTransform'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->LocalTransform,"Transform");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: LocalTransform of class  Movable */
#ifndef TOLUA_DISABLE_tolua_set_Movable_LocalTransform
static int tolua_set_Movable_LocalTransform(lua_State* tolua_S)
{
  Movable* self = (Movable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'LocalTransform'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Transform",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->LocalTransform = *((Transform*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: WorldTransform of class  Movable */
#ifndef TOLUA_DISABLE_tolua_get_Movable_WorldTransform
static int tolua_get_Movable_WorldTransform(lua_State* tolua_S)
{
  Movable* self = (Movable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'WorldTransform'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->WorldTransform,"Transform");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: WorldTransform of class  Movable */
#ifndef TOLUA_DISABLE_tolua_set_Movable_WorldTransform
static int tolua_set_Movable_WorldTransform(lua_State* tolua_S)
{
  Movable* self = (Movable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'WorldTransform'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Transform",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->WorldTransform = *((Transform*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: WorldTransformIsCurrent of class  Movable */
#ifndef TOLUA_DISABLE_tolua_get_Movable_WorldTransformIsCurrent
static int tolua_get_Movable_WorldTransformIsCurrent(lua_State* tolua_S)
{
  Movable* self = (Movable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'WorldTransformIsCurrent'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->WorldTransformIsCurrent);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: WorldTransformIsCurrent of class  Movable */
#ifndef TOLUA_DISABLE_tolua_set_Movable_WorldTransformIsCurrent
static int tolua_set_Movable_WorldTransformIsCurrent(lua_State* tolua_S)
{
  Movable* self = (Movable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'WorldTransformIsCurrent'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->WorldTransformIsCurrent = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: WorldBound of class  Movable */
#ifndef TOLUA_DISABLE_tolua_get_Movable_WorldBound
static int tolua_get_Movable_WorldBound(lua_State* tolua_S)
{
  Movable* self = (Movable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'WorldBound'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->WorldBound,"Bound");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: WorldBound of class  Movable */
#ifndef TOLUA_DISABLE_tolua_set_Movable_WorldBound
static int tolua_set_Movable_WorldBound(lua_State* tolua_S)
{
  Movable* self = (Movable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'WorldBound'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Bound",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->WorldBound = *((Bound*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: WorldBoundIsCurrent of class  Movable */
#ifndef TOLUA_DISABLE_tolua_get_Movable_WorldBoundIsCurrent
static int tolua_get_Movable_WorldBoundIsCurrent(lua_State* tolua_S)
{
  Movable* self = (Movable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'WorldBoundIsCurrent'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->WorldBoundIsCurrent);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: WorldBoundIsCurrent of class  Movable */
#ifndef TOLUA_DISABLE_tolua_set_Movable_WorldBoundIsCurrent
static int tolua_set_Movable_WorldBoundIsCurrent(lua_State* tolua_S)
{
  Movable* self = (Movable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'WorldBoundIsCurrent'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->WorldBoundIsCurrent = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Culling of class  Movable */
#ifndef TOLUA_DISABLE_tolua_get_Movable_Culling
static int tolua_get_Movable_Culling(lua_State* tolua_S)
{
  Movable* self = (Movable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Culling'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Culling);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Culling of class  Movable */
#ifndef TOLUA_DISABLE_tolua_set_Movable_Culling
static int tolua_set_Movable_Culling(lua_State* tolua_S)
{
  Movable* self = (Movable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Culling'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Culling = ((Movable::CullingMode) (int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: Update of class  Movable */
#ifndef TOLUA_DISABLE_tolua_PX2_Movable_Update00
static int tolua_PX2_Movable_Update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Movable",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Movable* self = (Movable*)  tolua_tousertype(tolua_S,1,0);
  double applicationTime = ((double)  tolua_tonumber(tolua_S,2,-Mathd::MAX_REAL));
  bool initiator = ((bool)  tolua_toboolean(tolua_S,3,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Update'", NULL);
#endif
  {
   self->Update(applicationTime,initiator);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetParent of class  Movable */
#ifndef TOLUA_DISABLE_tolua_PX2_Movable_GetParent00
static int tolua_PX2_Movable_GetParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Movable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Movable* self = (Movable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetParent'", NULL);
#endif
  {
   Movable* tolua_ret = (Movable*)  self->GetParent();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Movable");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetParent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  Renderable */
#ifndef TOLUA_DISABLE_tolua_PX2_Renderable_delete00
static int tolua_PX2_Renderable_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Renderable* self = (Renderable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPrimitiveType of class  Renderable */
#ifndef TOLUA_DISABLE_tolua_PX2_Renderable_GetPrimitiveType00
static int tolua_PX2_Renderable_GetPrimitiveType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderable* self = (const Renderable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPrimitiveType'", NULL);
#endif
  {
   Renderable::PrimitiveType tolua_ret = (Renderable::PrimitiveType)  self->GetPrimitiveType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPrimitiveType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetVertexFormat of class  Renderable */
#ifndef TOLUA_DISABLE_tolua_PX2_Renderable_SetVertexFormat00
static int tolua_PX2_Renderable_SetVertexFormat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderable",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"VertexFormat",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Renderable* self = (Renderable*)  tolua_tousertype(tolua_S,1,0);
  VertexFormat* vformat = ((VertexFormat*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetVertexFormat'", NULL);
#endif
  {
   self->SetVertexFormat(vformat);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetVertexFormat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetVertexFormat of class  Renderable */
#ifndef TOLUA_DISABLE_tolua_PX2_Renderable_GetVertexFormat00
static int tolua_PX2_Renderable_GetVertexFormat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderable* self = (const Renderable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetVertexFormat'", NULL);
#endif
  {
   const VertexFormat* tolua_ret = (const VertexFormat*)  self->GetVertexFormat();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"const VertexFormat");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetVertexFormat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetVertexFormat of class  Renderable */
#ifndef TOLUA_DISABLE_tolua_PX2_Renderable_GetVertexFormat01
static int tolua_PX2_Renderable_GetVertexFormat01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Renderable* self = (Renderable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetVertexFormat'", NULL);
#endif
  {
   VertexFormat* tolua_ret = (VertexFormat*)  self->GetVertexFormat();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"VertexFormat");
  }
 }
 return 1;
tolua_lerror:
 return tolua_PX2_Renderable_GetVertexFormat00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetVertexBuffer of class  Renderable */
#ifndef TOLUA_DISABLE_tolua_PX2_Renderable_SetVertexBuffer00
static int tolua_PX2_Renderable_SetVertexBuffer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderable",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"VertexBuffer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Renderable* self = (Renderable*)  tolua_tousertype(tolua_S,1,0);
  VertexBuffer* vbuffer = ((VertexBuffer*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetVertexBuffer'", NULL);
#endif
  {
   self->SetVertexBuffer(vbuffer);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetVertexBuffer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetVertexBuffer of class  Renderable */
#ifndef TOLUA_DISABLE_tolua_PX2_Renderable_GetVertexBuffer00
static int tolua_PX2_Renderable_GetVertexBuffer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderable* self = (const Renderable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetVertexBuffer'", NULL);
#endif
  {
   const VertexBuffer* tolua_ret = (const VertexBuffer*)  self->GetVertexBuffer();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"const VertexBuffer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetVertexBuffer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetVertexBuffer of class  Renderable */
#ifndef TOLUA_DISABLE_tolua_PX2_Renderable_GetVertexBuffer01
static int tolua_PX2_Renderable_GetVertexBuffer01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Renderable* self = (Renderable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetVertexBuffer'", NULL);
#endif
  {
   VertexBuffer* tolua_ret = (VertexBuffer*)  self->GetVertexBuffer();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"VertexBuffer");
  }
 }
 return 1;
tolua_lerror:
 return tolua_PX2_Renderable_GetVertexBuffer00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetIndexBuffer of class  Renderable */
#ifndef TOLUA_DISABLE_tolua_PX2_Renderable_SetIndexBuffer00
static int tolua_PX2_Renderable_SetIndexBuffer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderable",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"IndexBuffer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Renderable* self = (Renderable*)  tolua_tousertype(tolua_S,1,0);
  IndexBuffer* ibuffer = ((IndexBuffer*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetIndexBuffer'", NULL);
#endif
  {
   self->SetIndexBuffer(ibuffer);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetIndexBuffer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetIndexBuffer of class  Renderable */
#ifndef TOLUA_DISABLE_tolua_PX2_Renderable_GetIndexBuffer00
static int tolua_PX2_Renderable_GetIndexBuffer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderable* self = (const Renderable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetIndexBuffer'", NULL);
#endif
  {
   const IndexBuffer* tolua_ret = (const IndexBuffer*)  self->GetIndexBuffer();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"const IndexBuffer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetIndexBuffer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetIndexBuffer of class  Renderable */
#ifndef TOLUA_DISABLE_tolua_PX2_Renderable_GetIndexBuffer01
static int tolua_PX2_Renderable_GetIndexBuffer01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Renderable* self = (Renderable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetIndexBuffer'", NULL);
#endif
  {
   IndexBuffer* tolua_ret = (IndexBuffer*)  self->GetIndexBuffer();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"IndexBuffer");
  }
 }
 return 1;
tolua_lerror:
 return tolua_PX2_Renderable_GetIndexBuffer00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetModelBound of class  Renderable */
#ifndef TOLUA_DISABLE_tolua_PX2_Renderable_GetModelBound00
static int tolua_PX2_Renderable_GetModelBound00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderable* self = (const Renderable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetModelBound'", NULL);
#endif
  {
   const Bound& tolua_ret = (const Bound&)  self->GetModelBound();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Bound");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetModelBound'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetModelBound of class  Renderable */
#ifndef TOLUA_DISABLE_tolua_PX2_Renderable_GetModelBound01
static int tolua_PX2_Renderable_GetModelBound01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Renderable* self = (Renderable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetModelBound'", NULL);
#endif
  {
   Bound& tolua_ret = (Bound&)  self->GetModelBound();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"Bound");
  }
 }
 return 1;
tolua_lerror:
 return tolua_PX2_Renderable_GetModelBound00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddRenderUsage of class  Renderable */
#ifndef TOLUA_DISABLE_tolua_PX2_Renderable_AddRenderUsage00
static int tolua_PX2_Renderable_AddRenderUsage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderable",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Renderable* self = (Renderable*)  tolua_tousertype(tolua_S,1,0);
  Renderable::RenderUsage usage = ((Renderable::RenderUsage) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddRenderUsage'", NULL);
#endif
  {
   self->AddRenderUsage(usage);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddRenderUsage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveRenderUsage of class  Renderable */
#ifndef TOLUA_DISABLE_tolua_PX2_Renderable_RemoveRenderUsage00
static int tolua_PX2_Renderable_RemoveRenderUsage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderable",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Renderable* self = (Renderable*)  tolua_tousertype(tolua_S,1,0);
  Renderable::RenderUsage usage = ((Renderable::RenderUsage) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveRenderUsage'", NULL);
#endif
  {
   self->RemoveRenderUsage(usage);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveRenderUsage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRenderUsage of class  Renderable */
#ifndef TOLUA_DISABLE_tolua_PX2_Renderable_GetRenderUsage00
static int tolua_PX2_Renderable_GetRenderUsage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Renderable* self = (Renderable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRenderUsage'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->GetRenderUsage();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRenderUsage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRenderLayer of class  Renderable */
#ifndef TOLUA_DISABLE_tolua_PX2_Renderable_SetRenderLayer00
static int tolua_PX2_Renderable_SetRenderLayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderable",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Renderable* self = (Renderable*)  tolua_tousertype(tolua_S,1,0);
  Renderable::RenderLayer layer = ((Renderable::RenderLayer) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRenderLayer'", NULL);
#endif
  {
   self->SetRenderLayer(layer);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRenderLayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSortIndex of class  Renderable */
#ifndef TOLUA_DISABLE_tolua_PX2_Renderable_GetSortIndex00
static int tolua_PX2_Renderable_GetSortIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Renderable* self = (Renderable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSortIndex'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->GetSortIndex();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSortIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaterialInstance of class  Renderable */
#ifndef TOLUA_DISABLE_tolua_PX2_Renderable_SetMaterialInstance00
static int tolua_PX2_Renderable_SetMaterialInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderable",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"MaterialInstance",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Renderable* self = (Renderable*)  tolua_tousertype(tolua_S,1,0);
  MaterialInstance* material = ((MaterialInstance*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMaterialInstance'", NULL);
#endif
  {
   self->SetMaterialInstance(material);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMaterialInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaterialInstance of class  Renderable */
#ifndef TOLUA_DISABLE_tolua_PX2_Renderable_GetMaterialInstance00
static int tolua_PX2_Renderable_GetMaterialInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderable* self = (const Renderable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaterialInstance'", NULL);
#endif
  {
   MaterialInstance* tolua_ret = (MaterialInstance*)  self->GetMaterialInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"MaterialInstance");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaterialInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddLight of class  Renderable */
#ifndef TOLUA_DISABLE_tolua_PX2_Renderable_AddLight00
static int tolua_PX2_Renderable_AddLight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderable",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Light",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Renderable* self = (Renderable*)  tolua_tousertype(tolua_S,1,0);
  Light* light = ((Light*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddLight'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->AddLight(light);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddLight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveLight of class  Renderable */
#ifndef TOLUA_DISABLE_tolua_PX2_Renderable_RemoveLight00
static int tolua_PX2_Renderable_RemoveLight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderable",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Light",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Renderable* self = (Renderable*)  tolua_tousertype(tolua_S,1,0);
  Light* light = ((Light*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveLight'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->RemoveLight(light);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveLight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ClearLights of class  Renderable */
#ifndef TOLUA_DISABLE_tolua_PX2_Renderable_ClearLights00
static int tolua_PX2_Renderable_ClearLights00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Renderable* self = (Renderable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ClearLights'", NULL);
#endif
  {
   self->ClearLights();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ClearLights'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumLights of class  Renderable */
#ifndef TOLUA_DISABLE_tolua_PX2_Renderable_GetNumLights00
static int tolua_PX2_Renderable_GetNumLights00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Renderable* self = (Renderable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumLights'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetNumLights();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumLights'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLight of class  Renderable */
#ifndef TOLUA_DISABLE_tolua_PX2_Renderable_GetLight00
static int tolua_PX2_Renderable_GetLight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderable",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Renderable* self = (Renderable*)  tolua_tousertype(tolua_S,1,0);
  int i = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLight'", NULL);
#endif
  {
   Light* tolua_ret = (Light*)  self->GetLight(i);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Light");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UpdateModelSpace of class  Renderable */
#ifndef TOLUA_DISABLE_tolua_PX2_Renderable_UpdateModelSpace00
static int tolua_PX2_Renderable_UpdateModelSpace00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderable",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Renderable* self = (Renderable*)  tolua_tousertype(tolua_S,1,0);
  Renderable::UpdateType type = ((Renderable::UpdateType) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'UpdateModelSpace'", NULL);
#endif
  {
   self->UpdateModelSpace(type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UpdateModelSpace'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  Triangles */
#ifndef TOLUA_DISABLE_tolua_PX2_Triangles_delete00
static int tolua_PX2_Triangles_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Triangles",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Triangles* self = (Triangles*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumTriangles of class  Triangles */
#ifndef TOLUA_DISABLE_tolua_PX2_Triangles_GetNumTriangles00
static int tolua_PX2_Triangles_GetNumTriangles00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Triangles",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Triangles* self = (const Triangles*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumTriangles'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetNumTriangles();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumTriangles'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTriangle of class  Triangles */
#ifndef TOLUA_DISABLE_tolua_PX2_Triangles_GetTriangle00
static int tolua_PX2_Triangles_GetTriangle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Triangles",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Triangles* self = (const Triangles*)  tolua_tousertype(tolua_S,1,0);
  int i = ((int)  tolua_tonumber(tolua_S,2,0));
  int v0 = ((int)  tolua_tonumber(tolua_S,3,0));
  int v1 = ((int)  tolua_tonumber(tolua_S,4,0));
  int v2 = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTriangle'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetTriangle(i,v0,v1,v2);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushnumber(tolua_S,(lua_Number)v0);
   tolua_pushnumber(tolua_S,(lua_Number)v1);
   tolua_pushnumber(tolua_S,(lua_Number)v2);
  }
 }
 return 4;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTriangle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetModelTriangle of class  Triangles */
#ifndef TOLUA_DISABLE_tolua_PX2_Triangles_GetModelTriangle00
static int tolua_PX2_Triangles_GetModelTriangle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Triangles",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"APoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Triangles* self = (const Triangles*)  tolua_tousertype(tolua_S,1,0);
  int i = ((int)  tolua_tonumber(tolua_S,2,0));
  APoint* modelTriangle = ((APoint*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetModelTriangle'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetModelTriangle(i,modelTriangle);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetModelTriangle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetWorldTriangle of class  Triangles */
#ifndef TOLUA_DISABLE_tolua_PX2_Triangles_GetWorldTriangle00
static int tolua_PX2_Triangles_GetWorldTriangle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Triangles",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"APoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Triangles* self = (const Triangles*)  tolua_tousertype(tolua_S,1,0);
  int i = ((int)  tolua_tonumber(tolua_S,2,0));
  APoint* worldTriangle = ((APoint*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetWorldTriangle'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetWorldTriangle(i,worldTriangle);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetWorldTriangle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumVertices of class  Triangles */
#ifndef TOLUA_DISABLE_tolua_PX2_Triangles_GetNumVertices00
static int tolua_PX2_Triangles_GetNumVertices00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Triangles",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Triangles* self = (const Triangles*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumVertices'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetNumVertices();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumVertices'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetWorldTransform of class  Triangles */
#ifndef TOLUA_DISABLE_tolua_PX2_Triangles_GetWorldTransform00
static int tolua_PX2_Triangles_GetWorldTransform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Triangles",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Triangles* self = (const Triangles*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetWorldTransform'", NULL);
#endif
  {
   const Transform& tolua_ret = (const Transform&)  self->GetWorldTransform();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Transform");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetWorldTransform'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPosition of class  Triangles */
#ifndef TOLUA_DISABLE_tolua_PX2_Triangles_GetPosition00
static int tolua_PX2_Triangles_GetPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Triangles",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Triangles* self = (const Triangles*)  tolua_tousertype(tolua_S,1,0);
  int v = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPosition'", NULL);
#endif
  {
   Float3 tolua_ret = (Float3)  self->GetPosition(v);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((Float3)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"Float3");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Float3));
     tolua_pushusertype(tolua_S,tolua_obj,"Float3");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UpdateModelSpace of class  Triangles */
#ifndef TOLUA_DISABLE_tolua_PX2_Triangles_UpdateModelSpace00
static int tolua_PX2_Triangles_UpdateModelSpace00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Triangles",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Triangles* self = (Triangles*)  tolua_tousertype(tolua_S,1,0);
  Renderable::UpdateType type = ((Renderable::UpdateType) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'UpdateModelSpace'", NULL);
#endif
  {
   self->UpdateModelSpace(type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UpdateModelSpace'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  TriMesh */
#ifndef TOLUA_DISABLE_tolua_PX2_TriMesh_new00
static int tolua_PX2_TriMesh_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TriMesh",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"VertexFormat",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"VertexBuffer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"IndexBuffer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VertexFormat* vformat = ((VertexFormat*)  tolua_tousertype(tolua_S,2,0));
  VertexBuffer* vbuffer = ((VertexBuffer*)  tolua_tousertype(tolua_S,3,0));
  IndexBuffer* ibuffer = ((IndexBuffer*)  tolua_tousertype(tolua_S,4,0));
  {
   TriMesh* tolua_ret = (TriMesh*)  Mtolua_new((TriMesh)(vformat,vbuffer,ibuffer));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TriMesh");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  TriMesh */
#ifndef TOLUA_DISABLE_tolua_PX2_TriMesh_new00_local
static int tolua_PX2_TriMesh_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TriMesh",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"VertexFormat",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"VertexBuffer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"IndexBuffer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VertexFormat* vformat = ((VertexFormat*)  tolua_tousertype(tolua_S,2,0));
  VertexBuffer* vbuffer = ((VertexBuffer*)  tolua_tousertype(tolua_S,3,0));
  IndexBuffer* ibuffer = ((IndexBuffer*)  tolua_tousertype(tolua_S,4,0));
  {
   TriMesh* tolua_ret = (TriMesh*)  Mtolua_new((TriMesh)(vformat,vbuffer,ibuffer));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TriMesh");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  TriMesh */
#ifndef TOLUA_DISABLE_tolua_PX2_TriMesh_delete00
static int tolua_PX2_TriMesh_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TriMesh",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TriMesh* self = (TriMesh*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumTriangles of class  TriMesh */
#ifndef TOLUA_DISABLE_tolua_PX2_TriMesh_GetNumTriangles00
static int tolua_PX2_TriMesh_GetNumTriangles00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const TriMesh",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const TriMesh* self = (const TriMesh*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumTriangles'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetNumTriangles();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumTriangles'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTriangle of class  TriMesh */
#ifndef TOLUA_DISABLE_tolua_PX2_TriMesh_GetTriangle00
static int tolua_PX2_TriMesh_GetTriangle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const TriMesh",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const TriMesh* self = (const TriMesh*)  tolua_tousertype(tolua_S,1,0);
  int i = ((int)  tolua_tonumber(tolua_S,2,0));
  int v0 = ((int)  tolua_tonumber(tolua_S,3,0));
  int v1 = ((int)  tolua_tonumber(tolua_S,4,0));
  int v2 = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTriangle'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetTriangle(i,v0,v1,v2);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushnumber(tolua_S,(lua_Number)v0);
   tolua_pushnumber(tolua_S,(lua_Number)v1);
   tolua_pushnumber(tolua_S,(lua_Number)v2);
  }
 }
 return 4;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTriangle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Node */
#ifndef TOLUA_DISABLE_tolua_PX2_Node_new00
static int tolua_PX2_Node_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Node* tolua_ret = (Node*)  Mtolua_new((Node)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Node");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Node */
#ifndef TOLUA_DISABLE_tolua_PX2_Node_new00_local
static int tolua_PX2_Node_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Node* tolua_ret = (Node*)  Mtolua_new((Node)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Node");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  Node */
#ifndef TOLUA_DISABLE_tolua_PX2_Node_delete00
static int tolua_PX2_Node_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumChildren of class  Node */
#ifndef TOLUA_DISABLE_tolua_PX2_Node_GetNumChildren00
static int tolua_PX2_Node_GetNumChildren00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Node* self = (const Node*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumChildren'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetNumChildren();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumChildren'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AttachChild of class  Node */
#ifndef TOLUA_DISABLE_tolua_PX2_Node_AttachChild00
static int tolua_PX2_Node_AttachChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Movable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  Movable* child = ((Movable*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AttachChild'", NULL);
#endif
  {
   int tolua_ret = (int)  self->AttachChild(child);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AttachChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DetachChild of class  Node */
#ifndef TOLUA_DISABLE_tolua_PX2_Node_DetachChild00
static int tolua_PX2_Node_DetachChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Movable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  Movable* child = ((Movable*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DetachChild'", NULL);
#endif
  {
   int tolua_ret = (int)  self->DetachChild(child);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DetachChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DetachChildAt of class  Node */
#ifndef TOLUA_DISABLE_tolua_PX2_Node_DetachChildAt00
static int tolua_PX2_Node_DetachChildAt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  int i = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DetachChildAt'", NULL);
#endif
  {
   MovablePtr tolua_ret = (MovablePtr)  self->DetachChildAt(i);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((MovablePtr)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"MovablePtr");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(MovablePtr));
     tolua_pushusertype(tolua_S,tolua_obj,"MovablePtr");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DetachChildAt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DetachAllChildren of class  Node */
#ifndef TOLUA_DISABLE_tolua_PX2_Node_DetachAllChildren00
static int tolua_PX2_Node_DetachAllChildren00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DetachAllChildren'", NULL);
#endif
  {
   self->DetachAllChildren();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DetachAllChildren'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetChild of class  Node */
#ifndef TOLUA_DISABLE_tolua_PX2_Node_SetChild00
static int tolua_PX2_Node_SetChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"Movable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  int i = ((int)  tolua_tonumber(tolua_S,2,0));
  Movable* child = ((Movable*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetChild'", NULL);
#endif
  {
   MovablePtr tolua_ret = (MovablePtr)  self->SetChild(i,child);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((MovablePtr)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"MovablePtr");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(MovablePtr));
     tolua_pushusertype(tolua_S,tolua_obj,"MovablePtr");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetChild of class  Node */
#ifndef TOLUA_DISABLE_tolua_PX2_Node_GetChild00
static int tolua_PX2_Node_GetChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  int i = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetChild'", NULL);
#endif
  {
   MovablePtr tolua_ret = (MovablePtr)  self->GetChild(i);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((MovablePtr)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"MovablePtr");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(MovablePtr));
     tolua_pushusertype(tolua_S,tolua_obj,"MovablePtr");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnNotPicked of class  Node */
#ifndef TOLUA_DISABLE_tolua_PX2_Node_OnNotPicked00
static int tolua_PX2_Node_OnNotPicked00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  int pickInfo = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnNotPicked'", NULL);
#endif
  {
   self->OnNotPicked(pickInfo);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnNotPicked'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  SwitchNode */
#ifndef TOLUA_DISABLE_tolua_PX2_SwitchNode_new00
static int tolua_PX2_SwitchNode_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SwitchNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SwitchNode* tolua_ret = (SwitchNode*)  Mtolua_new((SwitchNode)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SwitchNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  SwitchNode */
#ifndef TOLUA_DISABLE_tolua_PX2_SwitchNode_new00_local
static int tolua_PX2_SwitchNode_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SwitchNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SwitchNode* tolua_ret = (SwitchNode*)  Mtolua_new((SwitchNode)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SwitchNode");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  SwitchNode */
#ifndef TOLUA_DISABLE_tolua_PX2_SwitchNode_delete00
static int tolua_PX2_SwitchNode_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SwitchNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SwitchNode* self = (SwitchNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Create of class  SwitchNode */
#ifndef TOLUA_DISABLE_tolua_PX2_SwitchNode_Create00
static int tolua_PX2_SwitchNode_Create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SwitchNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SwitchNode* tolua_ret = (SwitchNode*)  SwitchNode::Create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SwitchNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetActiveChild of class  SwitchNode */
#ifndef TOLUA_DISABLE_tolua_PX2_SwitchNode_SetActiveChild00
static int tolua_PX2_SwitchNode_SetActiveChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SwitchNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SwitchNode* self = (SwitchNode*)  tolua_tousertype(tolua_S,1,0);
  int activeChild = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetActiveChild'", NULL);
#endif
  {
   self->SetActiveChild(activeChild);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetActiveChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetActiveChild of class  SwitchNode */
#ifndef TOLUA_DISABLE_tolua_PX2_SwitchNode_GetActiveChild00
static int tolua_PX2_SwitchNode_GetActiveChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SwitchNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SwitchNode* self = (const SwitchNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetActiveChild'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetActiveChild();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetActiveChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DisableAllChildren of class  SwitchNode */
#ifndef TOLUA_DISABLE_tolua_PX2_SwitchNode_DisableAllChildren00
static int tolua_PX2_SwitchNode_DisableAllChildren00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SwitchNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SwitchNode* self = (SwitchNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DisableAllChildren'", NULL);
#endif
  {
   self->DisableAllChildren();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DisableAllChildren'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  InputEventData */
#ifndef TOLUA_DISABLE_tolua_PX2_InputEventData_new00
static int tolua_PX2_InputEventData_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"InputEventData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   InputEventData* tolua_ret = (InputEventData*)  Mtolua_new((InputEventData)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"InputEventData");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  InputEventData */
#ifndef TOLUA_DISABLE_tolua_PX2_InputEventData_new00_local
static int tolua_PX2_InputEventData_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"InputEventData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   InputEventData* tolua_ret = (InputEventData*)  Mtolua_new((InputEventData)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"InputEventData");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  InputEventData */
#ifndef TOLUA_DISABLE_tolua_PX2_InputEventData_delete00
static int tolua_PX2_InputEventData_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"InputEventData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  InputEventData* self = (InputEventData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KCode of class  InputEventData */
#ifndef TOLUA_DISABLE_tolua_get_InputEventData_KCode
static int tolua_get_InputEventData_KCode(lua_State* tolua_S)
{
  InputEventData* self = (InputEventData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'KCode'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->KCode);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: KCode of class  InputEventData */
#ifndef TOLUA_DISABLE_tolua_set_InputEventData_KCode
static int tolua_set_InputEventData_KCode(lua_State* tolua_S)
{
  InputEventData* self = (InputEventData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'KCode'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->KCode = ((KeyCode) (int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: MButtonID of class  InputEventData */
#ifndef TOLUA_DISABLE_tolua_get_InputEventData_MButtonID
static int tolua_get_InputEventData_MButtonID(lua_State* tolua_S)
{
  InputEventData* self = (InputEventData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'MButtonID'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->MButtonID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: MButtonID of class  InputEventData */
#ifndef TOLUA_DISABLE_tolua_set_InputEventData_MButtonID
static int tolua_set_InputEventData_MButtonID(lua_State* tolua_S)
{
  InputEventData* self = (InputEventData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'MButtonID'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->MButtonID = ((MouseButtonID) (int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: MState of class  InputEventData */
#ifndef TOLUA_DISABLE_tolua_get_InputEventData_MState
static int tolua_get_InputEventData_MState(lua_State* tolua_S)
{
  InputEventData* self = (InputEventData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'MState'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->MState,"MouseState");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: MState of class  InputEventData */
#ifndef TOLUA_DISABLE_tolua_set_InputEventData_MState
static int tolua_set_InputEventData_MState(lua_State* tolua_S)
{
  InputEventData* self = (InputEventData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'MState'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"MouseState",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->MState = *((MouseState*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: TState of class  InputEventData */
#ifndef TOLUA_DISABLE_tolua_get_InputEventData_TState
static int tolua_get_InputEventData_TState(lua_State* tolua_S)
{
  InputEventData* self = (InputEventData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'TState'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->TState,"MultiTouchState");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: TState of class  InputEventData */
#ifndef TOLUA_DISABLE_tolua_set_InputEventData_TState
static int tolua_set_InputEventData_TState(lua_State* tolua_S)
{
  InputEventData* self = (InputEventData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'TState'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"MultiTouchState",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->TState = *((MultiTouchState*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: TStates of class  InputEventData */
#ifndef TOLUA_DISABLE_tolua_get_InputEventData_TStates
static int tolua_get_InputEventData_TStates(lua_State* tolua_S)
{
  InputEventData* self = (InputEventData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'TStates'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->TStates,"std::vector<MultiTouchState>");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: TStates of class  InputEventData */
#ifndef TOLUA_DISABLE_tolua_set_InputEventData_TStates
static int tolua_set_InputEventData_TStates(lua_State* tolua_S)
{
  InputEventData* self = (InputEventData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'TStates'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"std::vector<MultiTouchState>",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->TStates = *((std::vector<MultiTouchState>*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: ViewID of class  InputEventData */
#ifndef TOLUA_DISABLE_tolua_get_InputEventData_ViewID
static int tolua_get_InputEventData_ViewID(lua_State* tolua_S)
{
  InputEventData* self = (InputEventData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ViewID'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->ViewID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: ViewID of class  InputEventData */
#ifndef TOLUA_DISABLE_tolua_set_InputEventData_ViewID
static int tolua_set_InputEventData_ViewID(lua_State* tolua_S)
{
  InputEventData* self = (InputEventData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ViewID'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->ViewID = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UIPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIPicBox_new00
static int tolua_PX2_UIPicBox_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIPicBox",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::string filename = ((std::string)  tolua_tocppstring(tolua_S,2,"Data/images/default.png"));
  {
   UIPicBox* tolua_ret = (UIPicBox*)  Mtolua_new((UIPicBox)(filename));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIPicBox");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  UIPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIPicBox_new00_local
static int tolua_PX2_UIPicBox_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIPicBox",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::string filename = ((std::string)  tolua_tocppstring(tolua_S,2,"Data/images/default.png"));
  {
   UIPicBox* tolua_ret = (UIPicBox*)  Mtolua_new((UIPicBox)(filename));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIPicBox");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  UIPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIPicBox_delete00
static int tolua_PX2_UIPicBox_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPicBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPicBox* self = (UIPicBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPicBoxType of class  UIPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIPicBox_SetPicBoxType00
static int tolua_PX2_UIPicBox_SetPicBoxType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPicBox",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPicBox* self = (UIPicBox*)  tolua_tousertype(tolua_S,1,0);
  UIPicBox::PicBoxType type = ((UIPicBox::PicBoxType) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPicBoxType'", NULL);
#endif
  {
   self->SetPicBoxType(type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPicBoxType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPicBoxType of class  UIPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIPicBox_GetPicBoxType00
static int tolua_PX2_UIPicBox_GetPicBoxType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPicBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPicBox* self = (UIPicBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPicBoxType'", NULL);
#endif
  {
   UIPicBox::PicBoxType tolua_ret = (UIPicBox::PicBoxType)  self->GetPicBoxType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPicBoxType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDynamic of class  UIPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIPicBox_SetDynamic00
static int tolua_PX2_UIPicBox_SetDynamic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPicBox",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPicBox* self = (UIPicBox*)  tolua_tousertype(tolua_S,1,0);
  bool dyn = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDynamic'", NULL);
#endif
  {
   self->SetDynamic(dyn);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDynamic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsDynamic of class  UIPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIPicBox_IsDynamic00
static int tolua_PX2_UIPicBox_IsDynamic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPicBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPicBox* self = (UIPicBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsDynamic'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsDynamic();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsDynamic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSize of class  UIPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIPicBox_SetSize00
static int tolua_PX2_UIPicBox_SetSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPicBox",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPicBox* self = (UIPicBox*)  tolua_tousertype(tolua_S,1,0);
  float width = ((float)  tolua_tonumber(tolua_S,2,0));
  float height = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSize'", NULL);
#endif
  {
   self->SetSize(width,height);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSize of class  UIPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIPicBox_SetSize01
static int tolua_PX2_UIPicBox_SetSize01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPicBox",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Sizef",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  UIPicBox* self = (UIPicBox*)  tolua_tousertype(tolua_S,1,0);
  const Sizef* size = ((const Sizef*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSize'", NULL);
#endif
  {
   self->SetSize(*size);
  }
 }
 return 0;
tolua_lerror:
 return tolua_PX2_UIPicBox_SetSize00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSize of class  UIPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIPicBox_GetSize00
static int tolua_PX2_UIPicBox_GetSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIPicBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIPicBox* self = (const UIPicBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSize'", NULL);
#endif
  {
   const Sizef& tolua_ret = (const Sizef&)  self->GetSize();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Sizef");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetWidth of class  UIPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIPicBox_SetWidth00
static int tolua_PX2_UIPicBox_SetWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPicBox",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPicBox* self = (UIPicBox*)  tolua_tousertype(tolua_S,1,0);
  float width = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetWidth'", NULL);
#endif
  {
   self->SetWidth(width);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetWidth of class  UIPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIPicBox_GetWidth00
static int tolua_PX2_UIPicBox_GetWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPicBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPicBox* self = (UIPicBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetWidth'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetWidth();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetHeight of class  UIPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIPicBox_SetHeight00
static int tolua_PX2_UIPicBox_SetHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPicBox",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPicBox* self = (UIPicBox*)  tolua_tousertype(tolua_S,1,0);
  float height = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetHeight'", NULL);
#endif
  {
   self->SetHeight(height);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHeight of class  UIPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIPicBox_GetHeight00
static int tolua_PX2_UIPicBox_GetHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPicBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPicBox* self = (UIPicBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHeight'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetHeight();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetColor of class  UIPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIPicBox_SetColor00
static int tolua_PX2_UIPicBox_SetColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPicBox",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Float3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPicBox* self = (UIPicBox*)  tolua_tousertype(tolua_S,1,0);
  Float3 color = *((Float3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetColor'", NULL);
#endif
  {
   self->SetColor(color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetColor of class  UIPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIPicBox_GetColor00
static int tolua_PX2_UIPicBox_GetColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIPicBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIPicBox* self = (const UIPicBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetColor'", NULL);
#endif
  {
   Float3 tolua_ret = (Float3)  self->GetColor();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((Float3)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"Float3");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Float3));
     tolua_pushusertype(tolua_S,tolua_obj,"Float3");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAlpha of class  UIPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIPicBox_SetAlpha00
static int tolua_PX2_UIPicBox_SetAlpha00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPicBox",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPicBox* self = (UIPicBox*)  tolua_tousertype(tolua_S,1,0);
  float alpha = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAlpha'", NULL);
#endif
  {
   self->SetAlpha(alpha);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAlpha'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAlpha of class  UIPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIPicBox_GetAlpha00
static int tolua_PX2_UIPicBox_GetAlpha00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIPicBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIPicBox* self = (const UIPicBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAlpha'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetAlpha();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAlpha'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTexture of class  UIPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIPicBox_SetTexture00
static int tolua_PX2_UIPicBox_SetTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPicBox",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Texture2D",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPicBox* self = (UIPicBox*)  tolua_tousertype(tolua_S,1,0);
  Texture2D* tex = ((Texture2D*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTexture'", NULL);
#endif
  {
   self->SetTexture(tex);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTexture of class  UIPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIPicBox_SetTexture01
static int tolua_PX2_UIPicBox_SetTexture01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPicBox",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  UIPicBox* self = (UIPicBox*)  tolua_tousertype(tolua_S,1,0);
  const std::string filename = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTexture'", NULL);
#endif
  {
   self->SetTexture(filename);
   tolua_pushcppstring(tolua_S,(const char*)filename);
  }
 }
 return 1;
tolua_lerror:
 return tolua_PX2_UIPicBox_SetTexture00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTexture of class  UIPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIPicBox_SetTexture02
static int tolua_PX2_UIPicBox_SetTexture02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPicBox",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  UIPicBox* self = (UIPicBox*)  tolua_tousertype(tolua_S,1,0);
  const std::string texPackName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  std::string eleName = ((std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTexture'", NULL);
#endif
  {
   self->SetTexture(texPackName,eleName);
   tolua_pushcppstring(tolua_S,(const char*)texPackName);
  }
 }
 return 1;
tolua_lerror:
 return tolua_PX2_UIPicBox_SetTexture01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTexture of class  UIPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIPicBox_GetTexture00
static int tolua_PX2_UIPicBox_GetTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPicBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPicBox* self = (UIPicBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTexture'", NULL);
#endif
  {
   Texture2D* tolua_ret = (Texture2D*)  self->GetTexture();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Texture2D");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDoubleSide of class  UIPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIPicBox_SetDoubleSide00
static int tolua_PX2_UIPicBox_SetDoubleSide00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPicBox",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPicBox* self = (UIPicBox*)  tolua_tousertype(tolua_S,1,0);
  bool d = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDoubleSide'", NULL);
#endif
  {
   self->SetDoubleSide(d);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDoubleSide'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsDoubleSide of class  UIPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIPicBox_IsDoubleSide00
static int tolua_PX2_UIPicBox_IsDoubleSide00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPicBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPicBox* self = (UIPicBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsDoubleSide'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsDoubleSide();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsDoubleSide'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTexCornorSize of class  UIPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIPicBox_SetTexCornorSize00
static int tolua_PX2_UIPicBox_SetTexCornorSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPicBox",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPicBox* self = (UIPicBox*)  tolua_tousertype(tolua_S,1,0);
  float width = ((float)  tolua_tonumber(tolua_S,2,0));
  float height = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTexCornorSize'", NULL);
#endif
  {
   self->SetTexCornorSize(width,height);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTexCornorSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTexCornorSize of class  UIPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIPicBox_SetTexCornorSize01
static int tolua_PX2_UIPicBox_SetTexCornorSize01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPicBox",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Sizef",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  UIPicBox* self = (UIPicBox*)  tolua_tousertype(tolua_S,1,0);
  const Sizef* size = ((const Sizef*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTexCornorSize'", NULL);
#endif
  {
   self->SetTexCornorSize(*size);
  }
 }
 return 0;
tolua_lerror:
 return tolua_PX2_UIPicBox_SetTexCornorSize00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTexCornorSize of class  UIPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIPicBox_GetTexCornorSize00
static int tolua_PX2_UIPicBox_GetTexCornorSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPicBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPicBox* self = (UIPicBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTexCornorSize'", NULL);
#endif
  {
   const Sizef& tolua_ret = (const Sizef&)  self->GetTexCornorSize();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Sizef");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTexCornorSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTexCornerWidth of class  UIPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIPicBox_SetTexCornerWidth00
static int tolua_PX2_UIPicBox_SetTexCornerWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPicBox",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPicBox* self = (UIPicBox*)  tolua_tousertype(tolua_S,1,0);
  float width = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTexCornerWidth'", NULL);
#endif
  {
   self->SetTexCornerWidth(width);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTexCornerWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTexCornerWidth of class  UIPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIPicBox_GetTexCornerWidth00
static int tolua_PX2_UIPicBox_GetTexCornerWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPicBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPicBox* self = (UIPicBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTexCornerWidth'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetTexCornerWidth();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTexCornerWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTexCornerHeight of class  UIPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIPicBox_SetTexCornerHeight00
static int tolua_PX2_UIPicBox_SetTexCornerHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPicBox",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPicBox* self = (UIPicBox*)  tolua_tousertype(tolua_S,1,0);
  float height = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTexCornerHeight'", NULL);
#endif
  {
   self->SetTexCornerHeight(height);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTexCornerHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTexCornerHeight of class  UIPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIPicBox_GetTexCornerHeight00
static int tolua_PX2_UIPicBox_GetTexCornerHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIPicBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIPicBox* self = (UIPicBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTexCornerHeight'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetTexCornerHeight();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTexCornerHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UIAnimPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIAnimPicBox_new00
static int tolua_PX2_UIAnimPicBox_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIAnimPicBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIAnimPicBox* tolua_ret = (UIAnimPicBox*)  Mtolua_new((UIAnimPicBox)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIAnimPicBox");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  UIAnimPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIAnimPicBox_new00_local
static int tolua_PX2_UIAnimPicBox_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIAnimPicBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIAnimPicBox* tolua_ret = (UIAnimPicBox*)  Mtolua_new((UIAnimPicBox)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIAnimPicBox");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  UIAnimPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIAnimPicBox_delete00
static int tolua_PX2_UIAnimPicBox_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIAnimPicBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIAnimPicBox* self = (UIAnimPicBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAPBCtrl of class  UIAnimPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIAnimPicBox_GetAPBCtrl00
static int tolua_PX2_UIAnimPicBox_GetAPBCtrl00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIAnimPicBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIAnimPicBox* self = (UIAnimPicBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAPBCtrl'", NULL);
#endif
  {
   UIAnimPicBoxControl* tolua_ret = (UIAnimPicBoxControl*)  self->GetAPBCtrl();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIAnimPicBoxControl");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAPBCtrl'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Play of class  UIAnimPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIAnimPicBox_Play00
static int tolua_PX2_UIAnimPicBox_Play00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIAnimPicBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIAnimPicBox* self = (UIAnimPicBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Play'", NULL);
#endif
  {
   self->Play();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Play'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFrameTexPack of class  UIAnimPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIAnimPicBox_SetFrameTexPack00
static int tolua_PX2_UIAnimPicBox_SetFrameTexPack00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIAnimPicBox",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIAnimPicBox* self = (UIAnimPicBox*)  tolua_tousertype(tolua_S,1,0);
  const std::string filename = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFrameTexPack'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetFrameTexPack(filename);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)filename);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFrameTexPack'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFrameTexPack of class  UIAnimPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIAnimPicBox_GetFrameTexPack00
static int tolua_PX2_UIAnimPicBox_GetFrameTexPack00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIAnimPicBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIAnimPicBox* self = (const UIAnimPicBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFrameTexPack'", NULL);
#endif
  {
   const std::string tolua_ret = (const std::string)  self->GetFrameTexPack();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFrameTexPack'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddFrameTex of class  UIAnimPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIAnimPicBox_AddFrameTex00
static int tolua_PX2_UIAnimPicBox_AddFrameTex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIAnimPicBox",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIAnimPicBox* self = (UIAnimPicBox*)  tolua_tousertype(tolua_S,1,0);
  const std::string filename = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddFrameTex'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->AddFrameTex(filename);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)filename);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddFrameTex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ClearFrames of class  UIAnimPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIAnimPicBox_ClearFrames00
static int tolua_PX2_UIAnimPicBox_ClearFrames00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIAnimPicBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIAnimPicBox* self = (UIAnimPicBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ClearFrames'", NULL);
#endif
  {
   self->ClearFrames();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ClearFrames'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumFrames of class  UIAnimPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIAnimPicBox_GetNumFrames00
static int tolua_PX2_UIAnimPicBox_GetNumFrames00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIAnimPicBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIAnimPicBox* self = (UIAnimPicBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumFrames'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetNumFrames();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumFrames'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetIntervalTime of class  UIAnimPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIAnimPicBox_SetIntervalTime00
static int tolua_PX2_UIAnimPicBox_SetIntervalTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIAnimPicBox",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIAnimPicBox* self = (UIAnimPicBox*)  tolua_tousertype(tolua_S,1,0);
  float seconds = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetIntervalTime'", NULL);
#endif
  {
   self->SetIntervalTime(seconds);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetIntervalTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetIntervalTime of class  UIAnimPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIAnimPicBox_GetIntervalTime00
static int tolua_PX2_UIAnimPicBox_GetIntervalTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIAnimPicBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIAnimPicBox* self = (UIAnimPicBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetIntervalTime'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetIntervalTime();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetIntervalTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetActiveIndex of class  UIAnimPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIAnimPicBox_SetActiveIndex00
static int tolua_PX2_UIAnimPicBox_SetActiveIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIAnimPicBox",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIAnimPicBox* self = (UIAnimPicBox*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetActiveIndex'", NULL);
#endif
  {
   self->SetActiveIndex(index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetActiveIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetActiveIndex of class  UIAnimPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIAnimPicBox_GetActiveIndex00
static int tolua_PX2_UIAnimPicBox_GetActiveIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIAnimPicBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIAnimPicBox* self = (UIAnimPicBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetActiveIndex'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetActiveIndex();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetActiveIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAsMovable of class  UIAnimPicBox */
#ifndef TOLUA_DISABLE_tolua_PX2_UIAnimPicBox_GetAsMovable00
static int tolua_PX2_UIAnimPicBox_GetAsMovable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIAnimPicBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIAnimPicBox* self = (UIAnimPicBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAsMovable'", NULL);
#endif
  {
   Movable* tolua_ret = (Movable*)  self->GetAsMovable();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Movable");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAsMovable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UIFrame */
#ifndef TOLUA_DISABLE_tolua_PX2_UIFrame_new00
static int tolua_PX2_UIFrame_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIFrame* tolua_ret = (UIFrame*)  Mtolua_new((UIFrame)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIFrame");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  UIFrame */
#ifndef TOLUA_DISABLE_tolua_PX2_UIFrame_new00_local
static int tolua_PX2_UIFrame_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIFrame* tolua_ret = (UIFrame*)  Mtolua_new((UIFrame)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIFrame");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  UIFrame */
#ifndef TOLUA_DISABLE_tolua_PX2_UIFrame_delete00
static int tolua_PX2_UIFrame_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIFrame* self = (UIFrame*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RegistScriptHandler of class  UIFrame */
#ifndef TOLUA_DISABLE_tolua_PX2_UIFrame_RegistScriptHandler00
static int tolua_PX2_UIFrame_RegistScriptHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIFrame",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIFrame* self = (UIFrame*)  tolua_tousertype(tolua_S,1,0);
  std::string handler = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RegistScriptHandler'", NULL);
#endif
  {
   self->RegistScriptHandler(handler);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RegistScriptHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UnRegistScriptHandler of class  UIFrame */
#ifndef TOLUA_DISABLE_tolua_PX2_UIFrame_UnRegistScriptHandler00
static int tolua_PX2_UIFrame_UnRegistScriptHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIFrame* self = (UIFrame*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'UnRegistScriptHandler'", NULL);
#endif
  {
   self->UnRegistScriptHandler();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UnRegistScriptHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  UIButtonBase */
#ifndef TOLUA_DISABLE_tolua_PX2_UIButtonBase_delete00
static int tolua_PX2_UIButtonBase_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButtonBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButtonBase* self = (UIButtonBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetButtonState of class  UIButtonBase */
#ifndef TOLUA_DISABLE_tolua_PX2_UIButtonBase_SetButtonState00
static int tolua_PX2_UIButtonBase_SetButtonState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButtonBase",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButtonBase* self = (UIButtonBase*)  tolua_tousertype(tolua_S,1,0);
  UIButtonBase::ButtonState state = ((UIButtonBase::ButtonState) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetButtonState'", NULL);
#endif
  {
   self->SetButtonState(state);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetButtonState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetButtonState of class  UIButtonBase */
#ifndef TOLUA_DISABLE_tolua_PX2_UIButtonBase_GetButtonState00
static int tolua_PX2_UIButtonBase_GetButtonState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIButtonBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIButtonBase* self = (const UIButtonBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetButtonState'", NULL);
#endif
  {
   UIButtonBase::ButtonState tolua_ret = (UIButtonBase::ButtonState)  self->GetButtonState();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetButtonState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPicBox of class  UIButtonBase */
#ifndef TOLUA_DISABLE_tolua_PX2_UIButtonBase_SetPicBox00
static int tolua_PX2_UIButtonBase_SetPicBox00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButtonBase",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"UIPicBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButtonBase* self = (UIButtonBase*)  tolua_tousertype(tolua_S,1,0);
  UIButtonBase::ButtonState state = ((UIButtonBase::ButtonState) (int)  tolua_tonumber(tolua_S,2,0));
  UIPicBox* pic = ((UIPicBox*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPicBox'", NULL);
#endif
  {
   self->SetPicBox(state,pic);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPicBox'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPicBoxAtState of class  UIButtonBase */
#ifndef TOLUA_DISABLE_tolua_PX2_UIButtonBase_GetPicBoxAtState00
static int tolua_PX2_UIButtonBase_GetPicBoxAtState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButtonBase",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButtonBase* self = (UIButtonBase*)  tolua_tousertype(tolua_S,1,0);
  UIButtonBase::ButtonState state = ((UIButtonBase::ButtonState) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPicBoxAtState'", NULL);
#endif
  {
   UIPicBox* tolua_ret = (UIPicBox*)  self->GetPicBoxAtState(state);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIPicBox");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPicBoxAtState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSize of class  UIButtonBase */
#ifndef TOLUA_DISABLE_tolua_PX2_UIButtonBase_SetSize00
static int tolua_PX2_UIButtonBase_SetSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButtonBase",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButtonBase* self = (UIButtonBase*)  tolua_tousertype(tolua_S,1,0);
  float width = ((float)  tolua_tonumber(tolua_S,2,0));
  float height = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSize'", NULL);
#endif
  {
   self->SetSize(width,height);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSize of class  UIButtonBase */
#ifndef TOLUA_DISABLE_tolua_PX2_UIButtonBase_SetSize01
static int tolua_PX2_UIButtonBase_SetSize01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButtonBase",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Sizef",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  UIButtonBase* self = (UIButtonBase*)  tolua_tousertype(tolua_S,1,0);
  const Sizef* size = ((const Sizef*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSize'", NULL);
#endif
  {
   self->SetSize(*size);
  }
 }
 return 0;
tolua_lerror:
 return tolua_PX2_UIButtonBase_SetSize00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSize of class  UIButtonBase */
#ifndef TOLUA_DISABLE_tolua_PX2_UIButtonBase_GetSize00
static int tolua_PX2_UIButtonBase_GetSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIButtonBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIButtonBase* self = (const UIButtonBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSize'", NULL);
#endif
  {
   const Sizef& tolua_ret = (const Sizef&)  self->GetSize();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Sizef");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetWidth of class  UIButtonBase */
#ifndef TOLUA_DISABLE_tolua_PX2_UIButtonBase_SetWidth00
static int tolua_PX2_UIButtonBase_SetWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButtonBase",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButtonBase* self = (UIButtonBase*)  tolua_tousertype(tolua_S,1,0);
  float width = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetWidth'", NULL);
#endif
  {
   self->SetWidth(width);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetWidth of class  UIButtonBase */
#ifndef TOLUA_DISABLE_tolua_PX2_UIButtonBase_GetWidth00
static int tolua_PX2_UIButtonBase_GetWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButtonBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButtonBase* self = (UIButtonBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetWidth'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetWidth();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetHeight of class  UIButtonBase */
#ifndef TOLUA_DISABLE_tolua_PX2_UIButtonBase_SetHeight00
static int tolua_PX2_UIButtonBase_SetHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButtonBase",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButtonBase* self = (UIButtonBase*)  tolua_tousertype(tolua_S,1,0);
  float height = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetHeight'", NULL);
#endif
  {
   self->SetHeight(height);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHeight of class  UIButtonBase */
#ifndef TOLUA_DISABLE_tolua_PX2_UIButtonBase_GetHeight00
static int tolua_PX2_UIButtonBase_GetHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButtonBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButtonBase* self = (UIButtonBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHeight'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetHeight();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_PX2_UIButton_new00
static int tolua_PX2_UIButton_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIButton* tolua_ret = (UIButton*)  Mtolua_new((UIButton)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIButton");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_PX2_UIButton_new00_local
static int tolua_PX2_UIButton_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIButton* tolua_ret = (UIButton*)  Mtolua_new((UIButton)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIButton");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  UIButton */
#ifndef TOLUA_DISABLE_tolua_PX2_UIButton_delete00
static int tolua_PX2_UIButton_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIButton* self = (UIButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UIStaticText */
#ifndef TOLUA_DISABLE_tolua_PX2_UIStaticText_new00
static int tolua_PX2_UIStaticText_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIStaticText",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIStaticText* tolua_ret = (UIStaticText*)  Mtolua_new((UIStaticText)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIStaticText");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  UIStaticText */
#ifndef TOLUA_DISABLE_tolua_PX2_UIStaticText_new00_local
static int tolua_PX2_UIStaticText_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIStaticText",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIStaticText* tolua_ret = (UIStaticText*)  Mtolua_new((UIStaticText)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIStaticText");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  UIStaticText */
#ifndef TOLUA_DISABLE_tolua_PX2_UIStaticText_delete00
static int tolua_PX2_UIStaticText_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIStaticText",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIStaticText* self = (UIStaticText*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFont of class  UIStaticText */
#ifndef TOLUA_DISABLE_tolua_PX2_UIStaticText_SetFont00
static int tolua_PX2_UIStaticText_SetFont00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIStaticText",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIStaticText* self = (UIStaticText*)  tolua_tousertype(tolua_S,1,0);
  const std::string fontFilename = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  int fontWidth = ((int)  tolua_tonumber(tolua_S,3,0));
  int fontHeight = ((int)  tolua_tonumber(tolua_S,4,0));
  unsigned int fontStyle = ((unsigned int)  tolua_tonumber(tolua_S,5,FES_NORMAL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFont'", NULL);
#endif
  {
   self->SetFont(fontFilename,fontWidth,fontHeight,fontStyle);
   tolua_pushcppstring(tolua_S,(const char*)fontFilename);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFont'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFont of class  UIStaticText */
#ifndef TOLUA_DISABLE_tolua_PX2_UIStaticText_GetFont00
static int tolua_PX2_UIStaticText_GetFont00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIStaticText",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIStaticText* self = (UIStaticText*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFont'", NULL);
#endif
  {
   Font* tolua_ret = (Font*)  self->GetFont();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Font");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFont'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetText of class  UIStaticText */
#ifndef TOLUA_DISABLE_tolua_PX2_UIStaticText_SetText00
static int tolua_PX2_UIStaticText_SetText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIStaticText",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIStaticText* self = (UIStaticText*)  tolua_tousertype(tolua_S,1,0);
  std::string text = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetText'", NULL);
#endif
  {
   self->SetText(text);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetText of class  UIStaticText */
#ifndef TOLUA_DISABLE_tolua_PX2_UIStaticText_GetText00
static int tolua_PX2_UIStaticText_GetText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIStaticText",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIStaticText* self = (const UIStaticText*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetText'", NULL);
#endif
  {
   const std::string tolua_ret = (const std::string)  self->GetText();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFontStyle of class  UIStaticText */
#ifndef TOLUA_DISABLE_tolua_PX2_UIStaticText_SetFontStyle00
static int tolua_PX2_UIStaticText_SetFontStyle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIStaticText",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIStaticText* self = (UIStaticText*)  tolua_tousertype(tolua_S,1,0);
  int style = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFontStyle'", NULL);
#endif
  {
   self->SetFontStyle(style);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFontStyle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFontStyle of class  UIStaticText */
#ifndef TOLUA_DISABLE_tolua_PX2_UIStaticText_GetFontStyle00
static int tolua_PX2_UIStaticText_GetFontStyle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIStaticText",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIStaticText* self = (UIStaticText*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFontStyle'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetFontStyle();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFontStyle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDrawStyle of class  UIStaticText */
#ifndef TOLUA_DISABLE_tolua_PX2_UIStaticText_SetDrawStyle00
static int tolua_PX2_UIStaticText_SetDrawStyle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIStaticText",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIStaticText* self = (UIStaticText*)  tolua_tousertype(tolua_S,1,0);
  int style = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDrawStyle'", NULL);
#endif
  {
   self->SetDrawStyle(style);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDrawStyle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDrawStyle of class  UIStaticText */
#ifndef TOLUA_DISABLE_tolua_PX2_UIStaticText_GetDrawStyle00
static int tolua_PX2_UIStaticText_GetDrawStyle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIStaticText",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIStaticText* self = (UIStaticText*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDrawStyle'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetDrawStyle();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDrawStyle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetColor of class  UIStaticText */
#ifndef TOLUA_DISABLE_tolua_PX2_UIStaticText_SetColor00
static int tolua_PX2_UIStaticText_SetColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIStaticText",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Float3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIStaticText* self = (UIStaticText*)  tolua_tousertype(tolua_S,1,0);
  Float3 color = *((Float3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetColor'", NULL);
#endif
  {
   self->SetColor(color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetColor of class  UIStaticText */
#ifndef TOLUA_DISABLE_tolua_PX2_UIStaticText_GetColor00
static int tolua_PX2_UIStaticText_GetColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIStaticText",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIStaticText* self = (const UIStaticText*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetColor'", NULL);
#endif
  {
   const Float3& tolua_ret = (const Float3&)  self->GetColor();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Float3");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAlpha of class  UIStaticText */
#ifndef TOLUA_DISABLE_tolua_PX2_UIStaticText_SetAlpha00
static int tolua_PX2_UIStaticText_SetAlpha00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIStaticText",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIStaticText* self = (UIStaticText*)  tolua_tousertype(tolua_S,1,0);
  float alpha = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAlpha'", NULL);
#endif
  {
   self->SetAlpha(alpha);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAlpha'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAlpha of class  UIStaticText */
#ifndef TOLUA_DISABLE_tolua_PX2_UIStaticText_GetAlpha00
static int tolua_PX2_UIStaticText_GetAlpha00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIStaticText",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIStaticText* self = (UIStaticText*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAlpha'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetAlpha();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAlpha'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFontWidth of class  UIStaticText */
#ifndef TOLUA_DISABLE_tolua_PX2_UIStaticText_SetFontWidth00
static int tolua_PX2_UIStaticText_SetFontWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIStaticText",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIStaticText* self = (UIStaticText*)  tolua_tousertype(tolua_S,1,0);
  int width = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFontWidth'", NULL);
#endif
  {
   self->SetFontWidth(width);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFontWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFontWidth of class  UIStaticText */
#ifndef TOLUA_DISABLE_tolua_PX2_UIStaticText_GetFontWidth00
static int tolua_PX2_UIStaticText_GetFontWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIStaticText",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIStaticText* self = (UIStaticText*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFontWidth'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetFontWidth();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFontWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFontHeight of class  UIStaticText */
#ifndef TOLUA_DISABLE_tolua_PX2_UIStaticText_SetFontHeight00
static int tolua_PX2_UIStaticText_SetFontHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIStaticText",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIStaticText* self = (UIStaticText*)  tolua_tousertype(tolua_S,1,0);
  int height = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFontHeight'", NULL);
#endif
  {
   self->SetFontHeight(height);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFontHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFontHeight of class  UIStaticText */
#ifndef TOLUA_DISABLE_tolua_PX2_UIStaticText_GetFontHeight00
static int tolua_PX2_UIStaticText_GetFontHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIStaticText",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIStaticText* self = (UIStaticText*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFontHeight'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetFontHeight();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFontHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDoubleSide of class  UIStaticText */
#ifndef TOLUA_DISABLE_tolua_PX2_UIStaticText_SetDoubleSide00
static int tolua_PX2_UIStaticText_SetDoubleSide00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIStaticText",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIStaticText* self = (UIStaticText*)  tolua_tousertype(tolua_S,1,0);
  bool d = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDoubleSide'", NULL);
#endif
  {
   self->SetDoubleSide(d);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDoubleSide'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsDoubleSide of class  UIStaticText */
#ifndef TOLUA_DISABLE_tolua_PX2_UIStaticText_IsDoubleSide00
static int tolua_PX2_UIStaticText_IsDoubleSide00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIStaticText",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIStaticText* self = (UIStaticText*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsDoubleSide'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsDoubleSide();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsDoubleSide'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDefaultView of class  UIManager */
#ifndef TOLUA_DISABLE_tolua_PX2_UIManager_GetDefaultView00
static int tolua_PX2_UIManager_GetDefaultView00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIManager* self = (UIManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDefaultView'", NULL);
#endif
  {
   UIView* tolua_ret = (UIView*)  self->GetDefaultView();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIView");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDefaultView'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddUIView of class  UIManager */
#ifndef TOLUA_DISABLE_tolua_PX2_UIManager_AddUIView00
static int tolua_PX2_UIManager_AddUIView00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"UIView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIManager* self = (UIManager*)  tolua_tousertype(tolua_S,1,0);
  std::string name = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  UIView* view = ((UIView*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddUIView'", NULL);
#endif
  {
   self->AddUIView(name,view);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddUIView'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetUIViews of class  UIManager */
#ifndef TOLUA_DISABLE_tolua_PX2_UIManager_GetUIViews00
static int tolua_PX2_UIManager_GetUIViews00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIManager* self = (UIManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetUIViews'", NULL);
#endif
  {
   std::map<std::string,UIViewPtr>& tolua_ret = (std::map<std::string,UIViewPtr>&)  self->GetUIViews();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"std::map<std::string,UIViewPtr>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetUIViews'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetUIView of class  UIManager */
#ifndef TOLUA_DISABLE_tolua_PX2_UIManager_GetUIView00
static int tolua_PX2_UIManager_GetUIView00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIManager* self = (UIManager*)  tolua_tousertype(tolua_S,1,0);
  std::string name = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetUIView'", NULL);
#endif
  {
   UIView* tolua_ret = (UIView*)  self->GetUIView(name);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIView");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetUIView'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateUIPicBox of class  UIManager */
#ifndef TOLUA_DISABLE_tolua_PX2_UIManager_CreateUIPicBox00
static int tolua_PX2_UIManager_CreateUIPicBox00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIManager",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const APoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIManager* self = (UIManager*)  tolua_tousertype(tolua_S,1,0);
  const APoint* localPos = ((const APoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateUIPicBox'", NULL);
#endif
  {
   UIPicBox* tolua_ret = (UIPicBox*)  self->CreateUIPicBox(*localPos);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIPicBox");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateUIPicBox'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateUIPicBox of class  UIManager */
#ifndef TOLUA_DISABLE_tolua_PX2_UIManager_CreateUIPicBox01
static int tolua_PX2_UIManager_CreateUIPicBox01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIManager",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const APoint",0,&tolua_err)) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  UIManager* self = (UIManager*)  tolua_tousertype(tolua_S,1,0);
  const APoint* localPos = ((const APoint*)  tolua_tousertype(tolua_S,2,0));
  const std::string texPack = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateUIPicBox'", NULL);
#endif
  {
   UIPicBox* tolua_ret = (UIPicBox*)  self->CreateUIPicBox(*localPos,texPack);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIPicBox");
   tolua_pushcppstring(tolua_S,(const char*)texPack);
  }
 }
 return 2;
tolua_lerror:
 return tolua_PX2_UIManager_CreateUIPicBox00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateUIAnimPicBox of class  UIManager */
#ifndef TOLUA_DISABLE_tolua_PX2_UIManager_CreateUIAnimPicBox00
static int tolua_PX2_UIManager_CreateUIAnimPicBox00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIManager",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const APoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIManager* self = (UIManager*)  tolua_tousertype(tolua_S,1,0);
  const APoint* localPos = ((const APoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateUIAnimPicBox'", NULL);
#endif
  {
   UIAnimPicBox* tolua_ret = (UIAnimPicBox*)  self->CreateUIAnimPicBox(*localPos);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIAnimPicBox");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateUIAnimPicBox'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateUIAnimPicBox of class  UIManager */
#ifndef TOLUA_DISABLE_tolua_PX2_UIManager_CreateUIAnimPicBox01
static int tolua_PX2_UIManager_CreateUIAnimPicBox01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIManager",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const APoint",0,&tolua_err)) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  UIManager* self = (UIManager*)  tolua_tousertype(tolua_S,1,0);
  const APoint* localPos = ((const APoint*)  tolua_tousertype(tolua_S,2,0));
  const std::string filename = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateUIAnimPicBox'", NULL);
#endif
  {
   UIAnimPicBox* tolua_ret = (UIAnimPicBox*)  self->CreateUIAnimPicBox(*localPos,filename);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIAnimPicBox");
   tolua_pushcppstring(tolua_S,(const char*)filename);
  }
 }
 return 2;
tolua_lerror:
 return tolua_PX2_UIManager_CreateUIAnimPicBox00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateUIStaticText of class  UIManager */
#ifndef TOLUA_DISABLE_tolua_PX2_UIManager_CreateUIStaticText00
static int tolua_PX2_UIManager_CreateUIStaticText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIManager",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const APoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIManager* self = (UIManager*)  tolua_tousertype(tolua_S,1,0);
  const APoint* localPos = ((const APoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateUIStaticText'", NULL);
#endif
  {
   UIStaticText* tolua_ret = (UIStaticText*)  self->CreateUIStaticText(*localPos);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIStaticText");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateUIStaticText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateUIFrame of class  UIManager */
#ifndef TOLUA_DISABLE_tolua_PX2_UIManager_CreateUIFrame00
static int tolua_PX2_UIManager_CreateUIFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIManager",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const APoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIManager* self = (UIManager*)  tolua_tousertype(tolua_S,1,0);
  const APoint* localPos = ((const APoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateUIFrame'", NULL);
#endif
  {
   UIFrame* tolua_ret = (UIFrame*)  self->CreateUIFrame(*localPos);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIFrame");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateUIFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateUIButton of class  UIManager */
#ifndef TOLUA_DISABLE_tolua_PX2_UIManager_CreateUIButton00
static int tolua_PX2_UIManager_CreateUIButton00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIManager",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const APoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIManager* self = (UIManager*)  tolua_tousertype(tolua_S,1,0);
  const APoint* localPos = ((const APoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateUIButton'", NULL);
#endif
  {
   UIButton* tolua_ret = (UIButton*)  self->CreateUIButton(*localPos);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIButton");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateUIButton'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __EventHandler__ of class  UIManager */
#ifndef TOLUA_DISABLE_tolua_get_UIManager___EventHandler__
static int tolua_get_UIManager___EventHandler__(lua_State* tolua_S)
{
  UIManager* self = (UIManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__EventHandler__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<EventHandler*>(self), "EventHandler");
#else
   tolua_pushusertype(tolua_S,(void*)((EventHandler*)self), "EventHandler");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UIView */
#ifndef TOLUA_DISABLE_tolua_PX2_UIView_new00
static int tolua_PX2_UIView_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   UIView* tolua_ret = (UIView*)  Mtolua_new((UIView)(id));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIView");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  UIView */
#ifndef TOLUA_DISABLE_tolua_PX2_UIView_new00_local
static int tolua_PX2_UIView_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   UIView* tolua_ret = (UIView*)  Mtolua_new((UIView)(id));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIView");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  UIView */
#ifndef TOLUA_DISABLE_tolua_PX2_UIView_delete00
static int tolua_PX2_UIView_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIView* self = (UIView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetID of class  UIView */
#ifndef TOLUA_DISABLE_tolua_PX2_UIView_GetID00
static int tolua_PX2_UIView_GetID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIView* self = (UIView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetID'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetID();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSize of class  UIView */
#ifndef TOLUA_DISABLE_tolua_PX2_UIView_SetSize00
static int tolua_PX2_UIView_SetSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIView* self = (UIView*)  tolua_tousertype(tolua_S,1,0);
  float width = ((float)  tolua_tonumber(tolua_S,2,0));
  float height = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSize'", NULL);
#endif
  {
   self->SetSize(width,height);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSize of class  UIView */
#ifndef TOLUA_DISABLE_tolua_PX2_UIView_SetSize01
static int tolua_PX2_UIView_SetSize01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIView",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Sizef",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  UIView* self = (UIView*)  tolua_tousertype(tolua_S,1,0);
  const Sizef* size = ((const Sizef*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSize'", NULL);
#endif
  {
   self->SetSize(*size);
  }
 }
 return 0;
tolua_lerror:
 return tolua_PX2_UIView_SetSize00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSize of class  UIView */
#ifndef TOLUA_DISABLE_tolua_PX2_UIView_GetSize00
static int tolua_PX2_UIView_GetSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIView* self = (const UIView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSize'", NULL);
#endif
  {
   const Sizef& tolua_ret = (const Sizef&)  self->GetSize();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Sizef");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetWidth of class  UIView */
#ifndef TOLUA_DISABLE_tolua_PX2_UIView_SetWidth00
static int tolua_PX2_UIView_SetWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIView* self = (UIView*)  tolua_tousertype(tolua_S,1,0);
  float width = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetWidth'", NULL);
#endif
  {
   self->SetWidth(width);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetWidth of class  UIView */
#ifndef TOLUA_DISABLE_tolua_PX2_UIView_GetWidth00
static int tolua_PX2_UIView_GetWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIView* self = (UIView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetWidth'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetWidth();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetHeight of class  UIView */
#ifndef TOLUA_DISABLE_tolua_PX2_UIView_SetHeight00
static int tolua_PX2_UIView_SetHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIView* self = (UIView*)  tolua_tousertype(tolua_S,1,0);
  float height = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetHeight'", NULL);
#endif
  {
   self->SetHeight(height);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHeight of class  UIView */
#ifndef TOLUA_DISABLE_tolua_PX2_UIView_GetHeight00
static int tolua_PX2_UIView_GetHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIView* self = (UIView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHeight'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetHeight();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRenderer of class  UIView */
#ifndef TOLUA_DISABLE_tolua_PX2_UIView_SetRenderer00
static int tolua_PX2_UIView_SetRenderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIView* self = (UIView*)  tolua_tousertype(tolua_S,1,0);
  Renderer* renderer = ((Renderer*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRenderer'", NULL);
#endif
  {
   self->SetRenderer(renderer);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRenderer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRenderer of class  UIView */
#ifndef TOLUA_DISABLE_tolua_PX2_UIView_GetRenderer00
static int tolua_PX2_UIView_GetRenderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIView* self = (UIView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRenderer'", NULL);
#endif
  {
   Renderer* tolua_ret = (Renderer*)  self->GetRenderer();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Renderer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRenderer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMainFrame of class  UIView */
#ifndef TOLUA_DISABLE_tolua_PX2_UIView_SetMainFrame00
static int tolua_PX2_UIView_SetMainFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIView* self = (UIView*)  tolua_tousertype(tolua_S,1,0);
  UIFrame* frame = ((UIFrame*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMainFrame'", NULL);
#endif
  {
   self->SetMainFrame(frame);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMainFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMainFrame of class  UIView */
#ifndef TOLUA_DISABLE_tolua_PX2_UIView_GetMainFrame00
static int tolua_PX2_UIView_GetMainFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIView* self = (UIView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMainFrame'", NULL);
#endif
  {
   UIFrame* tolua_ret = (UIFrame*)  self->GetMainFrame();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIFrame");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMainFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCamera of class  UIView */
#ifndef TOLUA_DISABLE_tolua_PX2_UIView_GetCamera00
static int tolua_PX2_UIView_GetCamera00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIView* self = (UIView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCamera'", NULL);
#endif
  {
   Camera* tolua_ret = (Camera*)  self->GetCamera();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Camera");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCamera'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCuller of class  UIView */
#ifndef TOLUA_DISABLE_tolua_PX2_UIView_GetCuller00
static int tolua_PX2_UIView_GetCuller00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIView* self = (UIView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCuller'", NULL);
#endif
  {
   Culler& tolua_ret = (Culler&)  self->GetCuller();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"Culler");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCuller'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPickedPicBoxs of class  UIView */
#ifndef TOLUA_DISABLE_tolua_PX2_UIView_GetPickedPicBoxs00
static int tolua_PX2_UIView_GetPickedPicBoxs00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIView* self = (UIView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPickedPicBoxs'", NULL);
#endif
  {
   std::vector<Pointer0<UIPicBox> >& tolua_ret = (std::vector<Pointer0<UIPicBox> >&)  self->GetPickedPicBoxs();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"std::vector<Pointer0<UIPicBox> >");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPickedPicBoxs'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetName of class  Project */
#ifndef TOLUA_DISABLE_tolua_PX2_Project_GetName00
static int tolua_PX2_Project_GetName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Project",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Project* self = (const Project*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetName'", NULL);
#endif
  {
   const std::string tolua_ret = (const std::string)  self->GetName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetWidth of class  Project */
#ifndef TOLUA_DISABLE_tolua_PX2_Project_GetWidth00
static int tolua_PX2_Project_GetWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Project",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Project* self = (const Project*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetWidth'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetWidth();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHeight of class  Project */
#ifndef TOLUA_DISABLE_tolua_PX2_Project_GetHeight00
static int tolua_PX2_Project_GetHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Project",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Project* self = (const Project*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHeight'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetHeight();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetColor of class  Project */
#ifndef TOLUA_DISABLE_tolua_PX2_Project_SetColor00
static int tolua_PX2_Project_SetColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Project",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Float4",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Project* self = (Project*)  tolua_tousertype(tolua_S,1,0);
  Float4 color = *((Float4*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetColor'", NULL);
#endif
  {
   self->SetColor(color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetColor of class  Project */
#ifndef TOLUA_DISABLE_tolua_PX2_Project_GetColor00
static int tolua_PX2_Project_GetColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Project",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Project* self = (Project*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetColor'", NULL);
#endif
  {
   Float4 tolua_ret = (Float4)  self->GetColor();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((Float4)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"Float4");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Float4));
     tolua_pushusertype(tolua_S,tolua_obj,"Float4");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetScene of class  Project */
#ifndef TOLUA_DISABLE_tolua_PX2_Project_SetScene00
static int tolua_PX2_Project_SetScene00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Project",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Scene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Project* self = (Project*)  tolua_tousertype(tolua_S,1,0);
  Scene* scene = ((Scene*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetScene'", NULL);
#endif
  {
   self->SetScene(scene);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetScene'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetScene of class  Project */
#ifndef TOLUA_DISABLE_tolua_PX2_Project_GetScene00
static int tolua_PX2_Project_GetScene00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Project",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Project* self = (const Project*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetScene'", NULL);
#endif
  {
   Scene* tolua_ret = (Scene*)  self->GetScene();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Scene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetScene'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetUI of class  Project */
#ifndef TOLUA_DISABLE_tolua_PX2_Project_GetUI00
static int tolua_PX2_Project_GetUI00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Project",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Project* self = (const Project*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetUI'", NULL);
#endif
  {
   UIFrame* tolua_ret = (UIFrame*)  self->GetUI();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIFrame");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetUI'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetShowProjectInfo of class  Project */
#ifndef TOLUA_DISABLE_tolua_PX2_Project_SetShowProjectInfo00
static int tolua_PX2_Project_SetShowProjectInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Project",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Project* self = (Project*)  tolua_tousertype(tolua_S,1,0);
  bool show = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetShowProjectInfo'", NULL);
#endif
  {
   self->SetShowProjectInfo(show);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetShowProjectInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsShowProjectInfo of class  Project */
#ifndef TOLUA_DISABLE_tolua_PX2_Project_IsShowProjectInfo00
static int tolua_PX2_Project_IsShowProjectInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Project",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Project* self = (Project*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsShowProjectInfo'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsShowProjectInfo();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsShowProjectInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_PX2_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"APoint","APoint","HPoint",tolua_collect_APoint);
  #else
  tolua_cclass(tolua_S,"APoint","APoint","HPoint",NULL);
  #endif
  tolua_beginmodule(tolua_S,"APoint");
   tolua_function(tolua_S,"new",tolua_PX2_APoint_new00);
   tolua_function(tolua_S,"new_local",tolua_PX2_APoint_new00_local);
   tolua_function(tolua_S,".call",tolua_PX2_APoint_new00_local);
   tolua_function(tolua_S,"new",tolua_PX2_APoint_new01);
   tolua_function(tolua_S,"new_local",tolua_PX2_APoint_new01_local);
   tolua_function(tolua_S,".call",tolua_PX2_APoint_new01_local);
   tolua_function(tolua_S,"new",tolua_PX2_APoint_new02);
   tolua_function(tolua_S,"new_local",tolua_PX2_APoint_new02_local);
   tolua_function(tolua_S,".call",tolua_PX2_APoint_new02_local);
   tolua_function(tolua_S,"delete",tolua_PX2_APoint_delete00);
   tolua_function(tolua_S,".sub",tolua_PX2_APoint__sub00);
   tolua_function(tolua_S,".add",tolua_PX2_APoint__add00);
   tolua_function(tolua_S,".sub",tolua_PX2_APoint__sub01);
   tolua_function(tolua_S,".add",tolua_PX2_APoint__add01);
   tolua_function(tolua_S,".mul",tolua_PX2_APoint__mul00);
   tolua_function(tolua_S,".div",tolua_PX2_APoint__div00);
   tolua_function(tolua_S,".sub",tolua_PX2_APoint__sub02);
   tolua_function(tolua_S,"Dot",tolua_PX2_APoint_Dot00);
   tolua_variable(tolua_S,"ORIGIN",tolua_get_APoint_ORIGIN,NULL);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"AVector","AVector","HPoint",tolua_collect_AVector);
  #else
  tolua_cclass(tolua_S,"AVector","AVector","HPoint",NULL);
  #endif
  tolua_beginmodule(tolua_S,"AVector");
   tolua_function(tolua_S,"new",tolua_PX2_AVector_new00);
   tolua_function(tolua_S,"new_local",tolua_PX2_AVector_new00_local);
   tolua_function(tolua_S,".call",tolua_PX2_AVector_new00_local);
   tolua_function(tolua_S,"new",tolua_PX2_AVector_new01);
   tolua_function(tolua_S,"new_local",tolua_PX2_AVector_new01_local);
   tolua_function(tolua_S,".call",tolua_PX2_AVector_new01_local);
   tolua_function(tolua_S,"new",tolua_PX2_AVector_new02);
   tolua_function(tolua_S,"new_local",tolua_PX2_AVector_new02_local);
   tolua_function(tolua_S,".call",tolua_PX2_AVector_new02_local);
   tolua_function(tolua_S,"new",tolua_PX2_AVector_new03);
   tolua_function(tolua_S,"new_local",tolua_PX2_AVector_new03_local);
   tolua_function(tolua_S,".call",tolua_PX2_AVector_new03_local);
   tolua_function(tolua_S,"new",tolua_PX2_AVector_new04);
   tolua_function(tolua_S,"new_local",tolua_PX2_AVector_new04_local);
   tolua_function(tolua_S,".call",tolua_PX2_AVector_new04_local);
   tolua_function(tolua_S,"delete",tolua_PX2_AVector_delete00);
   tolua_function(tolua_S,".add",tolua_PX2_AVector__add00);
   tolua_function(tolua_S,".sub",tolua_PX2_AVector__sub00);
   tolua_function(tolua_S,".mul",tolua_PX2_AVector__mul00);
   tolua_function(tolua_S,".div",tolua_PX2_AVector__div00);
   tolua_function(tolua_S,".sub",tolua_PX2_AVector__sub01);
   tolua_function(tolua_S,"Length",tolua_PX2_AVector_Length00);
   tolua_function(tolua_S,"SquaredLength",tolua_PX2_AVector_SquaredLength00);
   tolua_function(tolua_S,"Dot",tolua_PX2_AVector_Dot00);
   tolua_function(tolua_S,"Normalize",tolua_PX2_AVector_Normalize00);
   tolua_function(tolua_S,"Cross",tolua_PX2_AVector_Cross00);
   tolua_function(tolua_S,"UnitCross",tolua_PX2_AVector_UnitCross00);
   tolua_function(tolua_S,"Orthonormalize",tolua_PX2_AVector_Orthonormalize00);
   tolua_function(tolua_S,"Orthonormalize",tolua_PX2_AVector_Orthonormalize01);
   tolua_function(tolua_S,"GenerateOrthonormalBasis",tolua_PX2_AVector_GenerateOrthonormalBasis00);
   tolua_function(tolua_S,"GenerateComplementBasis",tolua_PX2_AVector_GenerateComplementBasis00);
   tolua_variable(tolua_S,"ZERO",tolua_get_AVector_ZERO,NULL);
   tolua_variable(tolua_S,"UNIT_X",tolua_get_AVector_UNIT_X,NULL);
   tolua_variable(tolua_S,"UNIT_Y",tolua_get_AVector_UNIT_Y,NULL);
   tolua_variable(tolua_S,"UNIT_Z",tolua_get_AVector_UNIT_Z,NULL);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"HPoint","HPoint","",tolua_collect_HPoint);
  #else
  tolua_cclass(tolua_S,"HPoint","HPoint","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"HPoint");
   tolua_function(tolua_S,"new",tolua_PX2_HPoint_new00);
   tolua_function(tolua_S,"new_local",tolua_PX2_HPoint_new00_local);
   tolua_function(tolua_S,".call",tolua_PX2_HPoint_new00_local);
   tolua_function(tolua_S,"new",tolua_PX2_HPoint_new01);
   tolua_function(tolua_S,"new_local",tolua_PX2_HPoint_new01_local);
   tolua_function(tolua_S,".call",tolua_PX2_HPoint_new01_local);
   tolua_function(tolua_S,"new",tolua_PX2_HPoint_new02);
   tolua_function(tolua_S,"new_local",tolua_PX2_HPoint_new02_local);
   tolua_function(tolua_S,".call",tolua_PX2_HPoint_new02_local);
   tolua_function(tolua_S,"delete",tolua_PX2_HPoint_delete00);
   tolua_function(tolua_S,".geti",tolua_PX2_HPoint__geti00);
   tolua_function(tolua_S,".seti",tolua_PX2_HPoint__seti00);
   tolua_function(tolua_S,".geti",tolua_PX2_HPoint__geti01);
   tolua_function(tolua_S,"X",tolua_PX2_HPoint_X00);
   tolua_function(tolua_S,"X",tolua_PX2_HPoint_X01);
   tolua_function(tolua_S,"Y",tolua_PX2_HPoint_Y00);
   tolua_function(tolua_S,"Y",tolua_PX2_HPoint_Y01);
   tolua_function(tolua_S,"Z",tolua_PX2_HPoint_Z00);
   tolua_function(tolua_S,"Z",tolua_PX2_HPoint_Z01);
   tolua_function(tolua_S,"W",tolua_PX2_HPoint_W00);
   tolua_function(tolua_S,"W",tolua_PX2_HPoint_W01);
   tolua_function(tolua_S,".eq",tolua_PX2_HPoint__eq00);
   tolua_function(tolua_S,".lt",tolua_PX2_HPoint__lt00);
   tolua_function(tolua_S,".le",tolua_PX2_HPoint__le00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Transform","Transform","",tolua_collect_Transform);
  #else
  tolua_cclass(tolua_S,"Transform","Transform","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Transform");
   tolua_function(tolua_S,"new",tolua_PX2_Transform_new00);
   tolua_function(tolua_S,"new_local",tolua_PX2_Transform_new00_local);
   tolua_function(tolua_S,".call",tolua_PX2_Transform_new00_local);
   tolua_function(tolua_S,"delete",tolua_PX2_Transform_delete00);
   tolua_function(tolua_S,"MakeIdentity",tolua_PX2_Transform_MakeIdentity00);
   tolua_function(tolua_S,"MakeUnitScale",tolua_PX2_Transform_MakeUnitScale00);
   tolua_function(tolua_S,"IsIdentity",tolua_PX2_Transform_IsIdentity00);
   tolua_function(tolua_S,"IsRSMatrix",tolua_PX2_Transform_IsRSMatrix00);
   tolua_function(tolua_S,"IsUniformScale",tolua_PX2_Transform_IsUniformScale00);
   tolua_function(tolua_S,"SetRotate",tolua_PX2_Transform_SetRotate00);
   tolua_function(tolua_S,"SetMatrix",tolua_PX2_Transform_SetMatrix00);
   tolua_function(tolua_S,"SetTranslate",tolua_PX2_Transform_SetTranslate00);
   tolua_function(tolua_S,"SetScale",tolua_PX2_Transform_SetScale00);
   tolua_function(tolua_S,"SetUniformScale",tolua_PX2_Transform_SetUniformScale00);
   tolua_function(tolua_S,"GetRotate",tolua_PX2_Transform_GetRotate00);
   tolua_function(tolua_S,"GetMatrix",tolua_PX2_Transform_GetMatrix00);
   tolua_function(tolua_S,"GetTranslate",tolua_PX2_Transform_GetTranslate00);
   tolua_function(tolua_S,"GetScale",tolua_PX2_Transform_GetScale00);
   tolua_function(tolua_S,"GetUniformScale",tolua_PX2_Transform_GetUniformScale00);
   tolua_function(tolua_S,"GetNorm",tolua_PX2_Transform_GetNorm00);
   tolua_function(tolua_S,".mul",tolua_PX2_Transform__mul00);
   tolua_function(tolua_S,".mul",tolua_PX2_Transform__mul01);
   tolua_function(tolua_S,".mul",tolua_PX2_Transform__mul02);
   tolua_function(tolua_S,"Matrix",tolua_PX2_Transform_Matrix00);
   tolua_function(tolua_S,"Inverse",tolua_PX2_Transform_Inverse00);
   tolua_function(tolua_S,"InverseTransform",tolua_PX2_Transform_InverseTransform00);
   tolua_variable(tolua_S,"IDENTITY",tolua_get_Transform_IDENTITY,NULL);
   tolua_function(tolua_S,"GetStreamingSize",tolua_PX2_Transform_GetStreamingSize00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Movable","Movable","Controlledable",tolua_collect_Movable);
  #else
  tolua_cclass(tolua_S,"Movable","Movable","Controlledable",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Movable");
   tolua_function(tolua_S,"delete",tolua_PX2_Movable_delete00);
   tolua_variable(tolua_S,"LocalTransform",tolua_get_Movable_LocalTransform,tolua_set_Movable_LocalTransform);
   tolua_variable(tolua_S,"WorldTransform",tolua_get_Movable_WorldTransform,tolua_set_Movable_WorldTransform);
   tolua_variable(tolua_S,"WorldTransformIsCurrent",tolua_get_Movable_WorldTransformIsCurrent,tolua_set_Movable_WorldTransformIsCurrent);
   tolua_variable(tolua_S,"WorldBound",tolua_get_Movable_WorldBound,tolua_set_Movable_WorldBound);
   tolua_variable(tolua_S,"WorldBoundIsCurrent",tolua_get_Movable_WorldBoundIsCurrent,tolua_set_Movable_WorldBoundIsCurrent);
   tolua_constant(tolua_S,"CULL_DYNAMIC",Movable::CULL_DYNAMIC);
   tolua_constant(tolua_S,"CULL_ALWAYS",Movable::CULL_ALWAYS);
   tolua_constant(tolua_S,"CULL_NEVER",Movable::CULL_NEVER);
   tolua_variable(tolua_S,"Culling",tolua_get_Movable_Culling,tolua_set_Movable_Culling);
   tolua_function(tolua_S,"Update",tolua_PX2_Movable_Update00);
   tolua_function(tolua_S,"GetParent",tolua_PX2_Movable_GetParent00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Renderable","Renderable","Movable",tolua_collect_Renderable);
  #else
  tolua_cclass(tolua_S,"Renderable","Renderable","Movable",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Renderable");
   tolua_constant(tolua_S,"PT_NONE",Renderable::PT_NONE);
   tolua_constant(tolua_S,"PT_POLYPOINT",Renderable::PT_POLYPOINT);
   tolua_constant(tolua_S,"PT_POLYSEGMENTS_DISJOINT",Renderable::PT_POLYSEGMENTS_DISJOINT);
   tolua_constant(tolua_S,"PT_POLYSEGMENTS_CONTIGUOUS",Renderable::PT_POLYSEGMENTS_CONTIGUOUS);
   tolua_constant(tolua_S,"PT_TRIANGLES",Renderable::PT_TRIANGLES);
   tolua_constant(tolua_S,"PT_TRIMESH",Renderable::PT_TRIMESH);
   tolua_constant(tolua_S,"PT_TRISTRIP",Renderable::PT_TRISTRIP);
   tolua_constant(tolua_S,"PT_TRIFAN",Renderable::PT_TRIFAN);
   tolua_constant(tolua_S,"PT_MAX_QUANTITY",Renderable::PT_MAX_QUANTITY);
   tolua_function(tolua_S,"delete",tolua_PX2_Renderable_delete00);
   tolua_function(tolua_S,"GetPrimitiveType",tolua_PX2_Renderable_GetPrimitiveType00);
   tolua_function(tolua_S,"SetVertexFormat",tolua_PX2_Renderable_SetVertexFormat00);
   tolua_function(tolua_S,"GetVertexFormat",tolua_PX2_Renderable_GetVertexFormat00);
   tolua_function(tolua_S,"GetVertexFormat",tolua_PX2_Renderable_GetVertexFormat01);
   tolua_function(tolua_S,"SetVertexBuffer",tolua_PX2_Renderable_SetVertexBuffer00);
   tolua_function(tolua_S,"GetVertexBuffer",tolua_PX2_Renderable_GetVertexBuffer00);
   tolua_function(tolua_S,"GetVertexBuffer",tolua_PX2_Renderable_GetVertexBuffer01);
   tolua_function(tolua_S,"SetIndexBuffer",tolua_PX2_Renderable_SetIndexBuffer00);
   tolua_function(tolua_S,"GetIndexBuffer",tolua_PX2_Renderable_GetIndexBuffer00);
   tolua_function(tolua_S,"GetIndexBuffer",tolua_PX2_Renderable_GetIndexBuffer01);
   tolua_function(tolua_S,"GetModelBound",tolua_PX2_Renderable_GetModelBound00);
   tolua_function(tolua_S,"GetModelBound",tolua_PX2_Renderable_GetModelBound01);
   tolua_constant(tolua_S,"RU_UI",Renderable::RU_UI);
   tolua_constant(tolua_S,"RU_GENERAL",Renderable::RU_GENERAL);
   tolua_constant(tolua_S,"RU_REFLECT",Renderable::RU_REFLECT);
   tolua_constant(tolua_S,"RU_SHADOWMAP",Renderable::RU_SHADOWMAP);
   tolua_constant(tolua_S,"RU_QUANTITY",Renderable::RU_QUANTITY);
   tolua_function(tolua_S,"AddRenderUsage",tolua_PX2_Renderable_AddRenderUsage00);
   tolua_function(tolua_S,"RemoveRenderUsage",tolua_PX2_Renderable_RemoveRenderUsage00);
   tolua_function(tolua_S,"GetRenderUsage",tolua_PX2_Renderable_GetRenderUsage00);
   tolua_constant(tolua_S,"RL_BACKGROUND",Renderable::RL_BACKGROUND);
   tolua_constant(tolua_S,"RL_SKY",Renderable::RL_SKY);
   tolua_constant(tolua_S,"RL_TERRAIN",Renderable::RL_TERRAIN);
   tolua_constant(tolua_S,"RL_SCENE",Renderable::RL_SCENE);
   tolua_constant(tolua_S,"RL_FRONT",Renderable::RL_FRONT);
   tolua_function(tolua_S,"SetRenderLayer",tolua_PX2_Renderable_SetRenderLayer00);
   tolua_function(tolua_S,"GetSortIndex",tolua_PX2_Renderable_GetSortIndex00);
   tolua_function(tolua_S,"SetMaterialInstance",tolua_PX2_Renderable_SetMaterialInstance00);
   tolua_function(tolua_S,"GetMaterialInstance",tolua_PX2_Renderable_GetMaterialInstance00);
   tolua_function(tolua_S,"AddLight",tolua_PX2_Renderable_AddLight00);
   tolua_function(tolua_S,"RemoveLight",tolua_PX2_Renderable_RemoveLight00);
   tolua_function(tolua_S,"ClearLights",tolua_PX2_Renderable_ClearLights00);
   tolua_function(tolua_S,"GetNumLights",tolua_PX2_Renderable_GetNumLights00);
   tolua_function(tolua_S,"GetLight",tolua_PX2_Renderable_GetLight00);
   tolua_constant(tolua_S,"GU_MODEL_BOUND_ONLY",Renderable::GU_MODEL_BOUND_ONLY);
   tolua_constant(tolua_S,"GU_NORMALS",Renderable::GU_NORMALS);
   tolua_constant(tolua_S,"GU_USE_GEOMETRY",Renderable::GU_USE_GEOMETRY);
   tolua_constant(tolua_S,"GU_USE_TCOORD_CHANNEL",Renderable::GU_USE_TCOORD_CHANNEL);
   tolua_function(tolua_S,"UpdateModelSpace",tolua_PX2_Renderable_UpdateModelSpace00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Triangles","Triangles","Renderable",tolua_collect_Triangles);
  #else
  tolua_cclass(tolua_S,"Triangles","Triangles","Renderable",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Triangles");
   tolua_function(tolua_S,"delete",tolua_PX2_Triangles_delete00);
   tolua_function(tolua_S,"GetNumTriangles",tolua_PX2_Triangles_GetNumTriangles00);
   tolua_function(tolua_S,"GetTriangle",tolua_PX2_Triangles_GetTriangle00);
   tolua_function(tolua_S,"GetModelTriangle",tolua_PX2_Triangles_GetModelTriangle00);
   tolua_function(tolua_S,"GetWorldTriangle",tolua_PX2_Triangles_GetWorldTriangle00);
   tolua_function(tolua_S,"GetNumVertices",tolua_PX2_Triangles_GetNumVertices00);
   tolua_function(tolua_S,"GetWorldTransform",tolua_PX2_Triangles_GetWorldTransform00);
   tolua_function(tolua_S,"GetPosition",tolua_PX2_Triangles_GetPosition00);
   tolua_function(tolua_S,"UpdateModelSpace",tolua_PX2_Triangles_UpdateModelSpace00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"TriMesh","TriMesh","Triangles",tolua_collect_TriMesh);
  #else
  tolua_cclass(tolua_S,"TriMesh","TriMesh","Triangles",NULL);
  #endif
  tolua_beginmodule(tolua_S,"TriMesh");
   tolua_function(tolua_S,"new",tolua_PX2_TriMesh_new00);
   tolua_function(tolua_S,"new_local",tolua_PX2_TriMesh_new00_local);
   tolua_function(tolua_S,".call",tolua_PX2_TriMesh_new00_local);
   tolua_function(tolua_S,"delete",tolua_PX2_TriMesh_delete00);
   tolua_function(tolua_S,"GetNumTriangles",tolua_PX2_TriMesh_GetNumTriangles00);
   tolua_function(tolua_S,"GetTriangle",tolua_PX2_TriMesh_GetTriangle00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Node","Node","Movable",tolua_collect_Node);
  #else
  tolua_cclass(tolua_S,"Node","Node","Movable",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Node");
   tolua_function(tolua_S,"new",tolua_PX2_Node_new00);
   tolua_function(tolua_S,"new_local",tolua_PX2_Node_new00_local);
   tolua_function(tolua_S,".call",tolua_PX2_Node_new00_local);
   tolua_function(tolua_S,"delete",tolua_PX2_Node_delete00);
   tolua_function(tolua_S,"GetNumChildren",tolua_PX2_Node_GetNumChildren00);
   tolua_function(tolua_S,"AttachChild",tolua_PX2_Node_AttachChild00);
   tolua_function(tolua_S,"DetachChild",tolua_PX2_Node_DetachChild00);
   tolua_function(tolua_S,"DetachChildAt",tolua_PX2_Node_DetachChildAt00);
   tolua_function(tolua_S,"DetachAllChildren",tolua_PX2_Node_DetachAllChildren00);
   tolua_function(tolua_S,"SetChild",tolua_PX2_Node_SetChild00);
   tolua_function(tolua_S,"GetChild",tolua_PX2_Node_GetChild00);
   tolua_function(tolua_S,"OnNotPicked",tolua_PX2_Node_OnNotPicked00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"SwitchNode","SwitchNode","Node",tolua_collect_SwitchNode);
  #else
  tolua_cclass(tolua_S,"SwitchNode","SwitchNode","Node",NULL);
  #endif
  tolua_beginmodule(tolua_S,"SwitchNode");
   tolua_function(tolua_S,"new",tolua_PX2_SwitchNode_new00);
   tolua_function(tolua_S,"new_local",tolua_PX2_SwitchNode_new00_local);
   tolua_function(tolua_S,".call",tolua_PX2_SwitchNode_new00_local);
   tolua_function(tolua_S,"delete",tolua_PX2_SwitchNode_delete00);
   tolua_function(tolua_S,"Create",tolua_PX2_SwitchNode_Create00);
   tolua_constant(tolua_S,"SN_INVALID_CHILD",SwitchNode::SN_INVALID_CHILD);
   tolua_function(tolua_S,"SetActiveChild",tolua_PX2_SwitchNode_SetActiveChild00);
   tolua_function(tolua_S,"GetActiveChild",tolua_PX2_SwitchNode_GetActiveChild00);
   tolua_function(tolua_S,"DisableAllChildren",tolua_PX2_SwitchNode_DisableAllChildren00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"KC_UNASSIGNED",KC_UNASSIGNED);
  tolua_constant(tolua_S,"KC_ESCAPE",KC_ESCAPE);
  tolua_constant(tolua_S,"KC_1",KC_1);
  tolua_constant(tolua_S,"KC_2",KC_2);
  tolua_constant(tolua_S,"KC_3",KC_3);
  tolua_constant(tolua_S,"KC_4",KC_4);
  tolua_constant(tolua_S,"KC_5",KC_5);
  tolua_constant(tolua_S,"KC_6",KC_6);
  tolua_constant(tolua_S,"KC_7",KC_7);
  tolua_constant(tolua_S,"KC_8",KC_8);
  tolua_constant(tolua_S,"KC_9",KC_9);
  tolua_constant(tolua_S,"KC_0",KC_0);
  tolua_constant(tolua_S,"KC_MINUS",KC_MINUS);
  tolua_constant(tolua_S,"KC_EQUALS",KC_EQUALS);
  tolua_constant(tolua_S,"KC_BACK",KC_BACK);
  tolua_constant(tolua_S,"KC_TAB",KC_TAB);
  tolua_constant(tolua_S,"KC_Q",KC_Q);
  tolua_constant(tolua_S,"KC_W",KC_W);
  tolua_constant(tolua_S,"KC_E",KC_E);
  tolua_constant(tolua_S,"KC_R",KC_R);
  tolua_constant(tolua_S,"KC_T",KC_T);
  tolua_constant(tolua_S,"KC_Y",KC_Y);
  tolua_constant(tolua_S,"KC_U",KC_U);
  tolua_constant(tolua_S,"KC_I",KC_I);
  tolua_constant(tolua_S,"KC_O",KC_O);
  tolua_constant(tolua_S,"KC_P",KC_P);
  tolua_constant(tolua_S,"KC_LBRACKET",KC_LBRACKET);
  tolua_constant(tolua_S,"KC_RBRACKET",KC_RBRACKET);
  tolua_constant(tolua_S,"KC_RETURN",KC_RETURN);
  tolua_constant(tolua_S,"KC_LCONTROL",KC_LCONTROL);
  tolua_constant(tolua_S,"KC_A",KC_A);
  tolua_constant(tolua_S,"KC_S",KC_S);
  tolua_constant(tolua_S,"KC_D",KC_D);
  tolua_constant(tolua_S,"KC_F",KC_F);
  tolua_constant(tolua_S,"KC_G",KC_G);
  tolua_constant(tolua_S,"KC_H",KC_H);
  tolua_constant(tolua_S,"KC_J",KC_J);
  tolua_constant(tolua_S,"KC_K",KC_K);
  tolua_constant(tolua_S,"KC_L",KC_L);
  tolua_constant(tolua_S,"KC_SEMICOLON",KC_SEMICOLON);
  tolua_constant(tolua_S,"KC_APOSTROPHE",KC_APOSTROPHE);
  tolua_constant(tolua_S,"KC_GRAVE",KC_GRAVE);
  tolua_constant(tolua_S,"KC_LSHIFT",KC_LSHIFT);
  tolua_constant(tolua_S,"KC_BACKSLASH",KC_BACKSLASH);
  tolua_constant(tolua_S,"KC_Z",KC_Z);
  tolua_constant(tolua_S,"KC_X",KC_X);
  tolua_constant(tolua_S,"KC_C",KC_C);
  tolua_constant(tolua_S,"KC_V",KC_V);
  tolua_constant(tolua_S,"KC_B",KC_B);
  tolua_constant(tolua_S,"KC_N",KC_N);
  tolua_constant(tolua_S,"KC_M",KC_M);
  tolua_constant(tolua_S,"KC_COMMA",KC_COMMA);
  tolua_constant(tolua_S,"KC_PERIOD",KC_PERIOD);
  tolua_constant(tolua_S,"KC_SLASH",KC_SLASH);
  tolua_constant(tolua_S,"KC_RSHIFT",KC_RSHIFT);
  tolua_constant(tolua_S,"KC_MULTIPLY",KC_MULTIPLY);
  tolua_constant(tolua_S,"KC_LMENU",KC_LMENU);
  tolua_constant(tolua_S,"KC_SPACE",KC_SPACE);
  tolua_constant(tolua_S,"KC_CAPITAL",KC_CAPITAL);
  tolua_constant(tolua_S,"KC_F1",KC_F1);
  tolua_constant(tolua_S,"KC_F2",KC_F2);
  tolua_constant(tolua_S,"KC_F3",KC_F3);
  tolua_constant(tolua_S,"KC_F4",KC_F4);
  tolua_constant(tolua_S,"KC_F5",KC_F5);
  tolua_constant(tolua_S,"KC_F6",KC_F6);
  tolua_constant(tolua_S,"KC_F7",KC_F7);
  tolua_constant(tolua_S,"KC_F8",KC_F8);
  tolua_constant(tolua_S,"KC_F9",KC_F9);
  tolua_constant(tolua_S,"KC_F10",KC_F10);
  tolua_constant(tolua_S,"KC_NUMLOCK",KC_NUMLOCK);
  tolua_constant(tolua_S,"KC_SCROLL",KC_SCROLL);
  tolua_constant(tolua_S,"KC_NUMPAD7",KC_NUMPAD7);
  tolua_constant(tolua_S,"KC_NUMPAD8",KC_NUMPAD8);
  tolua_constant(tolua_S,"KC_NUMPAD9",KC_NUMPAD9);
  tolua_constant(tolua_S,"KC_SUBTRACT",KC_SUBTRACT);
  tolua_constant(tolua_S,"KC_NUMPAD4",KC_NUMPAD4);
  tolua_constant(tolua_S,"KC_NUMPAD5",KC_NUMPAD5);
  tolua_constant(tolua_S,"KC_NUMPAD6",KC_NUMPAD6);
  tolua_constant(tolua_S,"KC_ADD",KC_ADD);
  tolua_constant(tolua_S,"KC_NUMPAD1",KC_NUMPAD1);
  tolua_constant(tolua_S,"KC_NUMPAD2",KC_NUMPAD2);
  tolua_constant(tolua_S,"KC_NUMPAD3",KC_NUMPAD3);
  tolua_constant(tolua_S,"KC_NUMPAD0",KC_NUMPAD0);
  tolua_constant(tolua_S,"KC_DECIMAL",KC_DECIMAL);
  tolua_constant(tolua_S,"KC_OEM_102",KC_OEM_102);
  tolua_constant(tolua_S,"KC_F11",KC_F11);
  tolua_constant(tolua_S,"KC_F12",KC_F12);
  tolua_constant(tolua_S,"KC_F13",KC_F13);
  tolua_constant(tolua_S,"KC_F14",KC_F14);
  tolua_constant(tolua_S,"KC_F15",KC_F15);
  tolua_constant(tolua_S,"KC_KANA",KC_KANA);
  tolua_constant(tolua_S,"KC_ABNT_C1",KC_ABNT_C1);
  tolua_constant(tolua_S,"KC_CONVERT",KC_CONVERT);
  tolua_constant(tolua_S,"KC_NOCONVERT",KC_NOCONVERT);
  tolua_constant(tolua_S,"KC_YEN",KC_YEN);
  tolua_constant(tolua_S,"KC_ABNT_C2",KC_ABNT_C2);
  tolua_constant(tolua_S,"KC_NUMPADEQUALS",KC_NUMPADEQUALS);
  tolua_constant(tolua_S,"KC_PREVTRACK",KC_PREVTRACK);
  tolua_constant(tolua_S,"KC_AT",KC_AT);
  tolua_constant(tolua_S,"KC_COLON",KC_COLON);
  tolua_constant(tolua_S,"KC_UNDERLINE",KC_UNDERLINE);
  tolua_constant(tolua_S,"KC_KANJI",KC_KANJI);
  tolua_constant(tolua_S,"KC_STOP",KC_STOP);
  tolua_constant(tolua_S,"KC_AX",KC_AX);
  tolua_constant(tolua_S,"KC_UNLABELED",KC_UNLABELED);
  tolua_constant(tolua_S,"KC_NEXTTRACK",KC_NEXTTRACK);
  tolua_constant(tolua_S,"KC_NUMPADENTER",KC_NUMPADENTER);
  tolua_constant(tolua_S,"KC_RCONTROL",KC_RCONTROL);
  tolua_constant(tolua_S,"KC_MUTE",KC_MUTE);
  tolua_constant(tolua_S,"KC_CALCULATOR",KC_CALCULATOR);
  tolua_constant(tolua_S,"KC_PLAYPAUSE",KC_PLAYPAUSE);
  tolua_constant(tolua_S,"KC_MEDIASTOP",KC_MEDIASTOP);
  tolua_constant(tolua_S,"KC_VOLUMEDOWN",KC_VOLUMEDOWN);
  tolua_constant(tolua_S,"KC_VOLUMEUP",KC_VOLUMEUP);
  tolua_constant(tolua_S,"KC_WEBHOME",KC_WEBHOME);
  tolua_constant(tolua_S,"KC_NUMPADCOMMA",KC_NUMPADCOMMA);
  tolua_constant(tolua_S,"KC_DIVIDE",KC_DIVIDE);
  tolua_constant(tolua_S,"KC_SYSRQ",KC_SYSRQ);
  tolua_constant(tolua_S,"KC_RMENU",KC_RMENU);
  tolua_constant(tolua_S,"KC_PAUSE",KC_PAUSE);
  tolua_constant(tolua_S,"KC_HOME",KC_HOME);
  tolua_constant(tolua_S,"KC_UP",KC_UP);
  tolua_constant(tolua_S,"KC_PGUP",KC_PGUP);
  tolua_constant(tolua_S,"KC_LEFT",KC_LEFT);
  tolua_constant(tolua_S,"KC_RIGHT",KC_RIGHT);
  tolua_constant(tolua_S,"KC_END",KC_END);
  tolua_constant(tolua_S,"KC_DOWN",KC_DOWN);
  tolua_constant(tolua_S,"KC_PGDOWN",KC_PGDOWN);
  tolua_constant(tolua_S,"KC_INSERT",KC_INSERT);
  tolua_constant(tolua_S,"KC_DELETE",KC_DELETE);
  tolua_constant(tolua_S,"KC_LWIN",KC_LWIN);
  tolua_constant(tolua_S,"KC_RWIN",KC_RWIN);
  tolua_constant(tolua_S,"KC_APPS",KC_APPS);
  tolua_constant(tolua_S,"KC_POWER",KC_POWER);
  tolua_constant(tolua_S,"KC_SLEEP",KC_SLEEP);
  tolua_constant(tolua_S,"KC_WAKE",KC_WAKE);
  tolua_constant(tolua_S,"KC_WEBSEARCH",KC_WEBSEARCH);
  tolua_constant(tolua_S,"KC_WEBFAVORITES",KC_WEBFAVORITES);
  tolua_constant(tolua_S,"KC_WEBREFRESH",KC_WEBREFRESH);
  tolua_constant(tolua_S,"KC_WEBSTOP",KC_WEBSTOP);
  tolua_constant(tolua_S,"KC_WEBFORWARD",KC_WEBFORWARD);
  tolua_constant(tolua_S,"KC_WEBBACK",KC_WEBBACK);
  tolua_constant(tolua_S,"KC_MYCOMPUTER",KC_MYCOMPUTER);
  tolua_constant(tolua_S,"KC_MAIL",KC_MAIL);
  tolua_constant(tolua_S,"KC_MEDIASELECT",KC_MEDIASELECT);
  tolua_constant(tolua_S,"MBID_LEFT",MBID_LEFT);
  tolua_constant(tolua_S,"MBID_RIGHT",MBID_RIGHT);
  tolua_constant(tolua_S,"MBID_MIDDLE",MBID_MIDDLE);
  tolua_constant(tolua_S,"MBID_Button3",MBID_Button3);
  tolua_constant(tolua_S,"MBID_Button4",MBID_Button4);
  tolua_constant(tolua_S,"MBID_Button5",MBID_Button5);
  tolua_constant(tolua_S,"MBID_Button6",MBID_Button6);
  tolua_constant(tolua_S,"MBID_Button7",MBID_Button7);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"InputEventData","InputEventData","",tolua_collect_InputEventData);
  #else
  tolua_cclass(tolua_S,"InputEventData","InputEventData","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"InputEventData");
   tolua_function(tolua_S,"new",tolua_PX2_InputEventData_new00);
   tolua_function(tolua_S,"new_local",tolua_PX2_InputEventData_new00_local);
   tolua_function(tolua_S,".call",tolua_PX2_InputEventData_new00_local);
   tolua_function(tolua_S,"delete",tolua_PX2_InputEventData_delete00);
   tolua_variable(tolua_S,"KCode",tolua_get_InputEventData_KCode,tolua_set_InputEventData_KCode);
   tolua_variable(tolua_S,"MButtonID",tolua_get_InputEventData_MButtonID,tolua_set_InputEventData_MButtonID);
   tolua_variable(tolua_S,"MState",tolua_get_InputEventData_MState,tolua_set_InputEventData_MState);
   tolua_variable(tolua_S,"TState",tolua_get_InputEventData_TState,tolua_set_InputEventData_TState);
   tolua_variable(tolua_S,"TStates",tolua_get_InputEventData_TStates,tolua_set_InputEventData_TStates);
   tolua_variable(tolua_S,"ViewID",tolua_get_InputEventData_ViewID,tolua_set_InputEventData_ViewID);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UIPicBox","UIPicBox","TriMesh",tolua_collect_UIPicBox);
  #else
  tolua_cclass(tolua_S,"UIPicBox","UIPicBox","TriMesh",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UIPicBox");
   tolua_function(tolua_S,"new",tolua_PX2_UIPicBox_new00);
   tolua_function(tolua_S,"new_local",tolua_PX2_UIPicBox_new00_local);
   tolua_function(tolua_S,".call",tolua_PX2_UIPicBox_new00_local);
   tolua_function(tolua_S,"delete",tolua_PX2_UIPicBox_delete00);
   tolua_constant(tolua_S,"PBT_NORMAL",UIPicBox::PBT_NORMAL);
   tolua_constant(tolua_S,"PBT_NINE",UIPicBox::PBT_NINE);
   tolua_constant(tolua_S,"PBT_MAX_TYPE",UIPicBox::PBT_MAX_TYPE);
   tolua_function(tolua_S,"SetPicBoxType",tolua_PX2_UIPicBox_SetPicBoxType00);
   tolua_function(tolua_S,"GetPicBoxType",tolua_PX2_UIPicBox_GetPicBoxType00);
   tolua_function(tolua_S,"SetDynamic",tolua_PX2_UIPicBox_SetDynamic00);
   tolua_function(tolua_S,"IsDynamic",tolua_PX2_UIPicBox_IsDynamic00);
   tolua_function(tolua_S,"SetSize",tolua_PX2_UIPicBox_SetSize00);
   tolua_function(tolua_S,"SetSize",tolua_PX2_UIPicBox_SetSize01);
   tolua_function(tolua_S,"GetSize",tolua_PX2_UIPicBox_GetSize00);
   tolua_function(tolua_S,"SetWidth",tolua_PX2_UIPicBox_SetWidth00);
   tolua_function(tolua_S,"GetWidth",tolua_PX2_UIPicBox_GetWidth00);
   tolua_function(tolua_S,"SetHeight",tolua_PX2_UIPicBox_SetHeight00);
   tolua_function(tolua_S,"GetHeight",tolua_PX2_UIPicBox_GetHeight00);
   tolua_function(tolua_S,"SetColor",tolua_PX2_UIPicBox_SetColor00);
   tolua_function(tolua_S,"GetColor",tolua_PX2_UIPicBox_GetColor00);
   tolua_function(tolua_S,"SetAlpha",tolua_PX2_UIPicBox_SetAlpha00);
   tolua_function(tolua_S,"GetAlpha",tolua_PX2_UIPicBox_GetAlpha00);
   tolua_function(tolua_S,"SetTexture",tolua_PX2_UIPicBox_SetTexture00);
   tolua_function(tolua_S,"SetTexture",tolua_PX2_UIPicBox_SetTexture01);
   tolua_function(tolua_S,"SetTexture",tolua_PX2_UIPicBox_SetTexture02);
   tolua_function(tolua_S,"GetTexture",tolua_PX2_UIPicBox_GetTexture00);
   tolua_function(tolua_S,"SetDoubleSide",tolua_PX2_UIPicBox_SetDoubleSide00);
   tolua_function(tolua_S,"IsDoubleSide",tolua_PX2_UIPicBox_IsDoubleSide00);
   tolua_function(tolua_S,"SetTexCornorSize",tolua_PX2_UIPicBox_SetTexCornorSize00);
   tolua_function(tolua_S,"SetTexCornorSize",tolua_PX2_UIPicBox_SetTexCornorSize01);
   tolua_function(tolua_S,"GetTexCornorSize",tolua_PX2_UIPicBox_GetTexCornorSize00);
   tolua_function(tolua_S,"SetTexCornerWidth",tolua_PX2_UIPicBox_SetTexCornerWidth00);
   tolua_function(tolua_S,"GetTexCornerWidth",tolua_PX2_UIPicBox_GetTexCornerWidth00);
   tolua_function(tolua_S,"SetTexCornerHeight",tolua_PX2_UIPicBox_SetTexCornerHeight00);
   tolua_function(tolua_S,"GetTexCornerHeight",tolua_PX2_UIPicBox_GetTexCornerHeight00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UIAnimPicBox","UIAnimPicBox","UIPicBox",tolua_collect_UIAnimPicBox);
  #else
  tolua_cclass(tolua_S,"UIAnimPicBox","UIAnimPicBox","UIPicBox",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UIAnimPicBox");
   tolua_function(tolua_S,"new",tolua_PX2_UIAnimPicBox_new00);
   tolua_function(tolua_S,"new_local",tolua_PX2_UIAnimPicBox_new00_local);
   tolua_function(tolua_S,".call",tolua_PX2_UIAnimPicBox_new00_local);
   tolua_function(tolua_S,"delete",tolua_PX2_UIAnimPicBox_delete00);
   tolua_function(tolua_S,"GetAPBCtrl",tolua_PX2_UIAnimPicBox_GetAPBCtrl00);
   tolua_function(tolua_S,"Play",tolua_PX2_UIAnimPicBox_Play00);
   tolua_function(tolua_S,"SetFrameTexPack",tolua_PX2_UIAnimPicBox_SetFrameTexPack00);
   tolua_function(tolua_S,"GetFrameTexPack",tolua_PX2_UIAnimPicBox_GetFrameTexPack00);
   tolua_function(tolua_S,"AddFrameTex",tolua_PX2_UIAnimPicBox_AddFrameTex00);
   tolua_function(tolua_S,"ClearFrames",tolua_PX2_UIAnimPicBox_ClearFrames00);
   tolua_function(tolua_S,"GetNumFrames",tolua_PX2_UIAnimPicBox_GetNumFrames00);
   tolua_function(tolua_S,"SetIntervalTime",tolua_PX2_UIAnimPicBox_SetIntervalTime00);
   tolua_function(tolua_S,"GetIntervalTime",tolua_PX2_UIAnimPicBox_GetIntervalTime00);
   tolua_function(tolua_S,"SetActiveIndex",tolua_PX2_UIAnimPicBox_SetActiveIndex00);
   tolua_function(tolua_S,"GetActiveIndex",tolua_PX2_UIAnimPicBox_GetActiveIndex00);
   tolua_function(tolua_S,"GetAsMovable",tolua_PX2_UIAnimPicBox_GetAsMovable00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UIFrame","UIFrame","Node",tolua_collect_UIFrame);
  #else
  tolua_cclass(tolua_S,"UIFrame","UIFrame","Node",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UIFrame");
   tolua_function(tolua_S,"new",tolua_PX2_UIFrame_new00);
   tolua_function(tolua_S,"new_local",tolua_PX2_UIFrame_new00_local);
   tolua_function(tolua_S,".call",tolua_PX2_UIFrame_new00_local);
   tolua_function(tolua_S,"delete",tolua_PX2_UIFrame_delete00);
   tolua_function(tolua_S,"RegistScriptHandler",tolua_PX2_UIFrame_RegistScriptHandler00);
   tolua_function(tolua_S,"UnRegistScriptHandler",tolua_PX2_UIFrame_UnRegistScriptHandler00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UIButtonBase","UIButtonBase","UIFrame",tolua_collect_UIButtonBase);
  #else
  tolua_cclass(tolua_S,"UIButtonBase","UIButtonBase","UIFrame",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UIButtonBase");
   tolua_function(tolua_S,"delete",tolua_PX2_UIButtonBase_delete00);
   tolua_constant(tolua_S,"BS_NORMAL",UIButtonBase::BS_NORMAL);
   tolua_constant(tolua_S,"BS_OVER",UIButtonBase::BS_OVER);
   tolua_constant(tolua_S,"BS_DOWN",UIButtonBase::BS_DOWN);
   tolua_constant(tolua_S,"BS_DISABLED",UIButtonBase::BS_DISABLED);
   tolua_constant(tolua_S,"BS_MAX_STATE",UIButtonBase::BS_MAX_STATE);
   tolua_function(tolua_S,"SetButtonState",tolua_PX2_UIButtonBase_SetButtonState00);
   tolua_function(tolua_S,"GetButtonState",tolua_PX2_UIButtonBase_GetButtonState00);
   tolua_function(tolua_S,"SetPicBox",tolua_PX2_UIButtonBase_SetPicBox00);
   tolua_function(tolua_S,"GetPicBoxAtState",tolua_PX2_UIButtonBase_GetPicBoxAtState00);
   tolua_function(tolua_S,"SetSize",tolua_PX2_UIButtonBase_SetSize00);
   tolua_function(tolua_S,"SetSize",tolua_PX2_UIButtonBase_SetSize01);
   tolua_function(tolua_S,"GetSize",tolua_PX2_UIButtonBase_GetSize00);
   tolua_function(tolua_S,"SetWidth",tolua_PX2_UIButtonBase_SetWidth00);
   tolua_function(tolua_S,"GetWidth",tolua_PX2_UIButtonBase_GetWidth00);
   tolua_function(tolua_S,"SetHeight",tolua_PX2_UIButtonBase_SetHeight00);
   tolua_function(tolua_S,"GetHeight",tolua_PX2_UIButtonBase_GetHeight00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UIButton","UIButton","UIButtonBase",tolua_collect_UIButton);
  #else
  tolua_cclass(tolua_S,"UIButton","UIButton","UIButtonBase",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UIButton");
   tolua_function(tolua_S,"new",tolua_PX2_UIButton_new00);
   tolua_function(tolua_S,"new_local",tolua_PX2_UIButton_new00_local);
   tolua_function(tolua_S,".call",tolua_PX2_UIButton_new00_local);
   tolua_function(tolua_S,"delete",tolua_PX2_UIButton_delete00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UIStaticText","UIStaticText","TriMesh",tolua_collect_UIStaticText);
  #else
  tolua_cclass(tolua_S,"UIStaticText","UIStaticText","TriMesh",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UIStaticText");
   tolua_function(tolua_S,"new",tolua_PX2_UIStaticText_new00);
   tolua_function(tolua_S,"new_local",tolua_PX2_UIStaticText_new00_local);
   tolua_function(tolua_S,".call",tolua_PX2_UIStaticText_new00_local);
   tolua_function(tolua_S,"delete",tolua_PX2_UIStaticText_delete00);
   tolua_function(tolua_S,"SetFont",tolua_PX2_UIStaticText_SetFont00);
   tolua_function(tolua_S,"GetFont",tolua_PX2_UIStaticText_GetFont00);
   tolua_function(tolua_S,"SetText",tolua_PX2_UIStaticText_SetText00);
   tolua_function(tolua_S,"GetText",tolua_PX2_UIStaticText_GetText00);
   tolua_function(tolua_S,"SetFontStyle",tolua_PX2_UIStaticText_SetFontStyle00);
   tolua_function(tolua_S,"GetFontStyle",tolua_PX2_UIStaticText_GetFontStyle00);
   tolua_function(tolua_S,"SetDrawStyle",tolua_PX2_UIStaticText_SetDrawStyle00);
   tolua_function(tolua_S,"GetDrawStyle",tolua_PX2_UIStaticText_GetDrawStyle00);
   tolua_function(tolua_S,"SetColor",tolua_PX2_UIStaticText_SetColor00);
   tolua_function(tolua_S,"GetColor",tolua_PX2_UIStaticText_GetColor00);
   tolua_function(tolua_S,"SetAlpha",tolua_PX2_UIStaticText_SetAlpha00);
   tolua_function(tolua_S,"GetAlpha",tolua_PX2_UIStaticText_GetAlpha00);
   tolua_function(tolua_S,"SetFontWidth",tolua_PX2_UIStaticText_SetFontWidth00);
   tolua_function(tolua_S,"GetFontWidth",tolua_PX2_UIStaticText_GetFontWidth00);
   tolua_function(tolua_S,"SetFontHeight",tolua_PX2_UIStaticText_SetFontHeight00);
   tolua_function(tolua_S,"GetFontHeight",tolua_PX2_UIStaticText_GetFontHeight00);
   tolua_function(tolua_S,"SetDoubleSide",tolua_PX2_UIStaticText_SetDoubleSide00);
   tolua_function(tolua_S,"IsDoubleSide",tolua_PX2_UIStaticText_IsDoubleSide00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"UIManager","UIManager","Singleton<UIManager>",NULL);
  tolua_beginmodule(tolua_S,"UIManager");
   tolua_function(tolua_S,"GetDefaultView",tolua_PX2_UIManager_GetDefaultView00);
   tolua_function(tolua_S,"AddUIView",tolua_PX2_UIManager_AddUIView00);
   tolua_function(tolua_S,"GetUIViews",tolua_PX2_UIManager_GetUIViews00);
   tolua_function(tolua_S,"GetUIView",tolua_PX2_UIManager_GetUIView00);
   tolua_function(tolua_S,"CreateUIPicBox",tolua_PX2_UIManager_CreateUIPicBox00);
   tolua_function(tolua_S,"CreateUIPicBox",tolua_PX2_UIManager_CreateUIPicBox01);
   tolua_function(tolua_S,"CreateUIAnimPicBox",tolua_PX2_UIManager_CreateUIAnimPicBox00);
   tolua_function(tolua_S,"CreateUIAnimPicBox",tolua_PX2_UIManager_CreateUIAnimPicBox01);
   tolua_function(tolua_S,"CreateUIStaticText",tolua_PX2_UIManager_CreateUIStaticText00);
   tolua_function(tolua_S,"CreateUIFrame",tolua_PX2_UIManager_CreateUIFrame00);
   tolua_function(tolua_S,"CreateUIButton",tolua_PX2_UIManager_CreateUIButton00);
   tolua_variable(tolua_S,"__EventHandler__",tolua_get_UIManager___EventHandler__,NULL);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UIView","UIView","",tolua_collect_UIView);
  #else
  tolua_cclass(tolua_S,"UIView","UIView","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UIView");
   tolua_function(tolua_S,"new",tolua_PX2_UIView_new00);
   tolua_function(tolua_S,"new_local",tolua_PX2_UIView_new00_local);
   tolua_function(tolua_S,".call",tolua_PX2_UIView_new00_local);
   tolua_function(tolua_S,"delete",tolua_PX2_UIView_delete00);
   tolua_function(tolua_S,"GetID",tolua_PX2_UIView_GetID00);
   tolua_function(tolua_S,"SetSize",tolua_PX2_UIView_SetSize00);
   tolua_function(tolua_S,"SetSize",tolua_PX2_UIView_SetSize01);
   tolua_function(tolua_S,"GetSize",tolua_PX2_UIView_GetSize00);
   tolua_function(tolua_S,"SetWidth",tolua_PX2_UIView_SetWidth00);
   tolua_function(tolua_S,"GetWidth",tolua_PX2_UIView_GetWidth00);
   tolua_function(tolua_S,"SetHeight",tolua_PX2_UIView_SetHeight00);
   tolua_function(tolua_S,"GetHeight",tolua_PX2_UIView_GetHeight00);
   tolua_function(tolua_S,"SetRenderer",tolua_PX2_UIView_SetRenderer00);
   tolua_function(tolua_S,"GetRenderer",tolua_PX2_UIView_GetRenderer00);
   tolua_function(tolua_S,"SetMainFrame",tolua_PX2_UIView_SetMainFrame00);
   tolua_function(tolua_S,"GetMainFrame",tolua_PX2_UIView_GetMainFrame00);
   tolua_function(tolua_S,"GetCamera",tolua_PX2_UIView_GetCamera00);
   tolua_function(tolua_S,"GetCuller",tolua_PX2_UIView_GetCuller00);
   tolua_function(tolua_S,"GetPickedPicBoxs",tolua_PX2_UIView_GetPickedPicBoxs00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Project","Project","Singleton<Project>",NULL);
  tolua_beginmodule(tolua_S,"Project");
   tolua_function(tolua_S,"GetName",tolua_PX2_Project_GetName00);
   tolua_function(tolua_S,"GetWidth",tolua_PX2_Project_GetWidth00);
   tolua_function(tolua_S,"GetHeight",tolua_PX2_Project_GetHeight00);
   tolua_function(tolua_S,"SetColor",tolua_PX2_Project_SetColor00);
   tolua_function(tolua_S,"GetColor",tolua_PX2_Project_GetColor00);
   tolua_function(tolua_S,"SetScene",tolua_PX2_Project_SetScene00);
   tolua_function(tolua_S,"GetScene",tolua_PX2_Project_GetScene00);
   tolua_function(tolua_S,"GetUI",tolua_PX2_Project_GetUI00);
   tolua_function(tolua_S,"SetShowProjectInfo",tolua_PX2_Project_SetShowProjectInfo00);
   tolua_function(tolua_S,"IsShowProjectInfo",tolua_PX2_Project_IsShowProjectInfo00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_PX2 (lua_State* tolua_S) {
 return tolua_PX2_open(tolua_S);
};
#endif

