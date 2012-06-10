/*
* Phoenix2 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2Property.hpp
*
* 版本		:	1.0 (2011/03/29)
*
* 作者		：	more
*
*/

#ifndef PX2PROPERTY_HPP
#define PX2PROPERTY_HPP

#include "PX2EditorPrerequisites.hpp"

namespace PX2Editor
{

	class Property;

	typedef void (*ButtonDownCallback)(Property *prop);

	class wxStringButtonEditor : public wxPGTextCtrlEditor
	{
		WX_PG_DECLARE_EDITOR_CLASS(wxStringButtonEditor)
	public:
		wxStringButtonEditor();
		wxStringButtonEditor (Property *prop);
		virtual ~wxStringButtonEditor();

		wxPG_DECLARE_CREATECONTROLS
			virtual bool OnEvent( wxPropertyGrid* propGrid,
			wxPGProperty* property,
			wxWindow* ctrl,
			wxEvent& event ) const;

		void SetButtonDownCallback (ButtonDownCallback fun);

	protected:

		ButtonDownCallback mButtonDownCallback;
		Property *mProperty;
	};

	class PropertyPage;

	/**
	* 从此派生的属性不需要手动调用PropertyPage::AddProperty,构造函数直接将其加
	* 入属性列表，并进行内存管理。
	*/
	class Property : public PX2::EventHandler
	{
	public:

		enum PropertyType
		{
			PT_CATEGORY,
			PT_INT,
			PT_FLOAT,
			PT_BOOL,
			PT_BOOLCHECK,
			PT_COLOR3FLOAT3,
			PT_FLOAT2,
			PT_FLOAT3,
			PT_FLOAT4,
			PT_STRING,
			PT_STRINGBUTTON,
			PT_TRANSFORMATION,
			//
			PT_ACTORTRANSFORMATION,
			//
			PT_QUANTITY
		};

		Property (PropertyPage *parent, std::string name, PropertyType type, void *data);
		virtual ~Property ();

		PropertyType GetType () { return mType; }
		std::string GetName () { return mName; }

		// PT_STRINGBUTTON，按钮被按下，触发回调函数
		void SetButtonDownCallback (ButtonDownCallback fun);

		virtual void OnChange (wxPropertyGridEvent &event);

		// PX2 Event
		virtual void DoEnter ();
		virtual void DoUpdate ();
		virtual void DoExecute (PX2::Event *event);
		virtual void DoLeave ();

		// wx
		wxPGProperty *GetWxProperty ();

	protected:
		Property ();
		wxColor StringToColor (wxString strColor);

		std::string mName;
		PropertyType mType;
		void *mData;

public_internal:
		PropertyPage *mParent;
		wxPGProperty *mProperty;
		wxStringButtonEditor *mStringButtonEditor;
		ButtonDownCallback mButtonDownCallback;
	};

	typedef PX2::Pointer0<Property> PropertyPtr;

}

#endif