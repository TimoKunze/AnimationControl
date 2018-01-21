//////////////////////////////////////////////////////////////////////
/// \class Animation
/// \author Timo "TimoSoft" Kunze
/// \brief <em>Superclasses \c SysAnimate32</em>
///
/// This class superclasses \c SysAnimate32 and makes it accessible by COM.
///
/// \todo Support 24bpp GIFs.
/// \todo Move the OLE drag'n'drop flags into their own struct?
///
/// \if UNICODE
///   \sa AnimLibU::IAnimation
/// \else
///   \sa AnimLibA::IAnimation
/// \endif
//////////////////////////////////////////////////////////////////////


#pragma once

#include "res/resource.h"
#ifdef UNICODE
	#include "AnimU.h"
#else
	#include "AnimA.h"
#endif
#include "_IAnimationEvents_CP.h"
#include "ICategorizeProperties.h"
#include "ICreditsProvider.h"
#include "helpers.h"
#include "EnumOLEVERB.h"
#include "PropertyNotifySinkImpl.h"
#include "AboutDlg.h"
#include "CommonProperties.h"
#include "TargetOLEDataObject.h"


class ATL_NO_VTABLE Animation : 
    public CComObjectRootEx<CComSingleThreadModel>,
    #ifdef _UNICODE
    	public IDispatchImpl<IAnimation, &IID_IAnimation, &LIBID_AnimLibU, /*wMajor =*/ VERSION_MAJOR, /*wMinor =*/ VERSION_MINOR>,
    #else
    	public IDispatchImpl<IAnimation, &IID_IAnimation, &LIBID_AnimLibA, /*wMajor =*/ VERSION_MAJOR, /*wMinor =*/ VERSION_MINOR>,
    #endif
    public IPersistStreamInitImpl<Animation>,
    public IOleControlImpl<Animation>,
    public IOleObjectImpl<Animation>,
    public IOleInPlaceActiveObjectImpl<Animation>,
    public IViewObjectExImpl<Animation>,
    public IOleInPlaceObjectWindowlessImpl<Animation>,
    public ISupportErrorInfo,
    public IConnectionPointContainerImpl<Animation>,
    public Proxy_IAnimationEvents<Animation>,
    public IPersistStorageImpl<Animation>,
    public IPersistPropertyBagImpl<Animation>,
    public ISpecifyPropertyPages,
    public IQuickActivateImpl<Animation>,
    #ifdef _UNICODE
    	public IProvideClassInfo2Impl<&CLSID_Animation, &__uuidof(_IAnimationEvents), &LIBID_AnimLibU, /*wMajor =*/ VERSION_MAJOR, /*wMinor =*/ VERSION_MINOR>,
    #else
    	public IProvideClassInfo2Impl<&CLSID_Animation, &__uuidof(_IAnimationEvents), &LIBID_AnimLibA, /*wMajor =*/ VERSION_MAJOR, /*wMinor =*/ VERSION_MINOR>,
    #endif
    public IPropertyNotifySinkCP<Animation>,
    public CComCoClass<Animation, &CLSID_Animation>,
    public CComControl<Animation>,
    public IPerPropertyBrowsingImpl<Animation>,
    public IDropTarget,
    public ICategorizeProperties,
    public ICreditsProvider
{
public:
	/// \brief <em>The constructor of this class</em>
	///
	/// Used for initialization.
	Animation();

	#ifndef DOXYGEN_SHOULD_SKIP_THIS
		DECLARE_OLEMISC_STATUS(OLEMISC_ACTIVATEWHENVISIBLE | OLEMISC_ALIGNABLE | OLEMISC_INSIDEOUT | OLEMISC_NOUIACTIVATE | OLEMISC_RECOMPOSEONRESIZE | OLEMISC_SETCLIENTSITEFIRST)
		DECLARE_REGISTRY_RESOURCEID(IDR_ANIMATION)

		#ifdef UNICODE
			DECLARE_WND_SUPERCLASS(TEXT("AnimationU"), ANIMATE_CLASSW)
		#else
			DECLARE_WND_SUPERCLASS(TEXT("AnimationA"), ANIMATE_CLASSA)
		#endif

		DECLARE_PROTECT_FINAL_CONSTRUCT()

		// we have a solid background and draw the entire rectangle
		DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

		BEGIN_COM_MAP(Animation)
			COM_INTERFACE_ENTRY(IAnimation)
			COM_INTERFACE_ENTRY(IDispatch)
			COM_INTERFACE_ENTRY(IViewObjectEx)
			COM_INTERFACE_ENTRY(IViewObject2)
			COM_INTERFACE_ENTRY(IViewObject)
			COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
			COM_INTERFACE_ENTRY(IOleInPlaceObject)
			COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
			COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
			COM_INTERFACE_ENTRY(IOleControl)
			COM_INTERFACE_ENTRY(IOleObject)
			COM_INTERFACE_ENTRY(IPersistStreamInit)
			COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
			COM_INTERFACE_ENTRY(ISupportErrorInfo)
			COM_INTERFACE_ENTRY(IConnectionPointContainer)
			COM_INTERFACE_ENTRY(IPersistPropertyBag)
			COM_INTERFACE_ENTRY(IQuickActivate)
			COM_INTERFACE_ENTRY(IPersistStorage)
			COM_INTERFACE_ENTRY(IProvideClassInfo)
			COM_INTERFACE_ENTRY(IProvideClassInfo2)
			COM_INTERFACE_ENTRY_IID(IID_ICategorizeProperties, ICategorizeProperties)
			COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
			COM_INTERFACE_ENTRY(IPerPropertyBrowsing)
			COM_INTERFACE_ENTRY(IDropTarget)
		END_COM_MAP()

		BEGIN_PROP_MAP(Animation)
			// NOTE: Don't forget to update Load and Save! This is for property bags only, not for streams!
			PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
			PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
			PROP_ENTRY_TYPE("AnimationBackStyle", DISPID_ANIM_ANIMATIONBACKSTYLE, CLSID_NULL, VT_I4)
			PROP_ENTRY_TYPE("Appearance", DISPID_ANIM_APPEARANCE, CLSID_NULL, VT_I4)
			PROP_ENTRY_TYPE("AutoStartReplay", DISPID_ANIM_AUTOSTARTREPLAY, CLSID_NULL, VT_BOOL)
			PROP_ENTRY_TYPE("BackColor", DISPID_ANIM_BACKCOLOR, CLSID_StockColorPage, VT_I4)
			PROP_ENTRY_TYPE("BorderStyle", DISPID_ANIM_BORDERSTYLE, CLSID_NULL, VT_I4)
			PROP_ENTRY_TYPE("CenterAnimation", DISPID_ANIM_CENTERANIMATION, CLSID_NULL, VT_BOOL)
			PROP_ENTRY_TYPE("DisabledEvents", DISPID_ANIM_DISABLEDEVENTS, CLSID_NULL, VT_I4)
			PROP_ENTRY_TYPE("DontRedraw", DISPID_ANIM_DONTREDRAW, CLSID_NULL, VT_BOOL)
			PROP_ENTRY_TYPE("Enabled", DISPID_ANIM_ENABLED, CLSID_NULL, VT_BOOL)
			PROP_ENTRY_TYPE("HoverTime", DISPID_ANIM_HOVERTIME, CLSID_NULL, VT_I4)
			PROP_ENTRY_TYPE("MouseIcon", DISPID_ANIM_MOUSEICON, CLSID_StockPicturePage, VT_DISPATCH)
			PROP_ENTRY_TYPE("MousePointer", DISPID_ANIM_MOUSEPOINTER, CLSID_NULL, VT_I4)
			PROP_ENTRY_TYPE("RegisterForOLEDragDrop", DISPID_ANIM_REGISTERFOROLEDRAGDROP, CLSID_NULL, VT_BOOL)
			PROP_ENTRY_TYPE("SupportOLEDragImages", DISPID_ANIM_SUPPORTOLEDRAGIMAGES, CLSID_NULL, VT_BOOL)
		END_PROP_MAP()

		BEGIN_CONNECTION_POINT_MAP(Animation)
			CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
			CONNECTION_POINT_ENTRY(__uuidof(_IAnimationEvents))
		END_CONNECTION_POINT_MAP()

		BEGIN_MSG_MAP(Animation)
			MESSAGE_HANDLER(WM_CONTEXTMENU, OnContextMenu)
			MESSAGE_HANDLER(WM_CREATE, OnCreate)
			MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
			MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
			MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
			MESSAGE_HANDLER(WM_MBUTTONDOWN, OnMButtonDown)
			MESSAGE_HANDLER(WM_MBUTTONUP, OnMButtonUp)
			MESSAGE_HANDLER(WM_MOUSEACTIVATE, OnMouseActivate)
			MESSAGE_HANDLER(WM_MOUSEHOVER, OnMouseHover)
			MESSAGE_HANDLER(WM_MOUSEHWHEEL, OnMouseWheel)
			MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)
			MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
			MESSAGE_HANDLER(WM_MOUSEWHEEL, OnMouseWheel)
			MESSAGE_HANDLER(WM_NCHITTEST, OnNCHitTest)
			MESSAGE_HANDLER(WM_RBUTTONDOWN, OnRButtonDown)
			MESSAGE_HANDLER(WM_RBUTTONUP, OnRButtonUp)
			MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
			MESSAGE_HANDLER(WM_SETREDRAW, OnSetRedraw)
			MESSAGE_HANDLER(WM_THEMECHANGED, OnThemeChanged)
			MESSAGE_HANDLER(WM_TIMER, OnTimer)
			MESSAGE_HANDLER(WM_WINDOWPOSCHANGED, OnWindowPosChanged)
			MESSAGE_HANDLER(WM_XBUTTONDOWN, OnXButtonDown)
			MESSAGE_HANDLER(WM_XBUTTONUP, OnXButtonUp)

			MESSAGE_HANDLER(OCM_CTLCOLORSTATIC, OnReflectedCtlColorStatic)

			MESSAGE_HANDLER(ACM_OPEN, OnOpen)

			REFLECTED_COMMAND_CODE_HANDLER(ACN_START, OnReflectedStart)
			REFLECTED_COMMAND_CODE_HANDLER(ACN_STOP, OnReflectedStop)

			CHAIN_MSG_MAP(CComControl<Animation>)
		END_MSG_MAP()
	#endif

	//////////////////////////////////////////////////////////////////////
	/// \name Implementation of ISupportsErrorInfo
	///
	//@{
	/// \brief <em>Retrieves whether an interface supports the \c IErrorInfo interface</em>
	///
	/// \param[in] interfaceToCheck The IID of the interface to check.
	///
	/// \return \c S_OK if the interface identified by \c interfaceToCheck supports \c IErrorInfo;
	///         otherwise \c S_FALSE.
	///
	/// \sa <a href="https://msdn.microsoft.com/en-us/library/ms221233.aspx">IErrorInfo</a>
	virtual HRESULT STDMETHODCALLTYPE InterfaceSupportsErrorInfo(REFIID interfaceToCheck);
	//@}
	//////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////
	/// \name Implementation of persistance
	///
	//@{
	/// \brief <em>Overrides \c IPersistStreamInitImpl::GetSizeMax to make object properties persistent</em>
	///
	/// Object properties can't be persisted through \c IPersistStreamInitImpl by just using ATL's
	/// persistence macros. So we communicate directly with the stream. This requires we override
	/// \c IPersistStreamInitImpl::GetSizeMax.
	///
	/// \param[in] pSize The maximum number of bytes that persistence of the control's properties will
	///            consume.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa Load, Save,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms687287.aspx">IPersistStreamInit::GetSizeMax</a>,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms682273.aspx">IPersistStreamInit</a>
	virtual HRESULT STDMETHODCALLTYPE GetSizeMax(ULARGE_INTEGER* pSize);
	/// \brief <em>Overrides \c IPersistStreamInitImpl::Load to make object properties persistent</em>
	///
	/// Object properties can't be persisted through \c IPersistStreamInitImpl by just using ATL's
	/// persistence macros. So we override \c IPersistStreamInitImpl::Load and read directly from
	/// the stream.
	///
	/// \param[in] pStream The \c IStream implementation which stores the control's properties.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa Save, GetSizeMax,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms680730.aspx">IPersistStreamInit::Load</a>,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms682273.aspx">IPersistStreamInit</a>
	///     <a href="https://msdn.microsoft.com/en-us/library/aa380034.aspx">IStream</a>
	virtual HRESULT STDMETHODCALLTYPE Load(LPSTREAM pStream);
	/// \brief <em>Overrides \c IPersistStreamInitImpl::Save to make object properties persistent</em>
	///
	/// Object properties can't be persisted through \c IPersistStreamInitImpl by just using ATL's
	/// persistence macros. So we override \c IPersistStreamInitImpl::Save and write directly into
	/// the stream.
	///
	/// \param[in] pStream The \c IStream implementation which stores the control's properties.
	/// \param[in] clearDirtyFlag Flag indicating whether the control should clear its dirty flag after
	///            saving. If \c TRUE, the flag is cleared, otherwise not. A value of \c FALSE allows
	///            the caller to do a "Save Copy As" operation.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa Load, GetSizeMax,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms694439.aspx">IPersistStreamInit::Save</a>,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms682273.aspx">IPersistStreamInit</a>
	///     <a href="https://msdn.microsoft.com/en-us/library/aa380034.aspx">IStream</a>
	virtual HRESULT STDMETHODCALLTYPE Save(LPSTREAM pStream, BOOL clearDirtyFlag);
	//@}
	//////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////
	/// \name Implementation of IAnimation
	///
	//@{
	/// \brief <em>Retrieves the current setting of the \c AnimationBackStyle property</em>
	///
	/// Retrieves how the animation's background is drawn. Any of the values defined by the
	/// \c AnimationBackStyleConstants enumeration is valid.
	///
	/// \param[out] pValue The property's current setting.
	///
	/// \return An \c HRESULT error code.
	///
	/// \attention Changing this property destroys and recreates the control window.
	///
	/// \if UNICODE
	///   \sa put_AnimationBackStyle, get_BackColor, AnimLibU::AnimationBackStyleConstants
	/// \else
	///   \sa put_AnimationBackStyle, get_BackColor, AnimLibA::AnimationBackStyleConstants
	/// \endif
	virtual HRESULT STDMETHODCALLTYPE get_AnimationBackStyle(AnimationBackStyleConstants* pValue);
	/// \brief <em>Sets the \c AnimationBackStyle property</em>
	///
	/// Sets how the animation's background is drawn. Any of the values defined by the
	/// \c AnimationBackStyleConstants enumeration is valid.
	///
	/// \param[in] newValue The setting to apply.
	///
	/// \return An \c HRESULT error code.
	///
	/// \attention Changing this property destroys and recreates the control window.
	///
	/// \if UNICODE
	///   \sa get_AnimationBackStyle, put_BackColor, AnimLibU::AnimationBackStyleConstants
	/// \else
	///   \sa get_AnimationBackStyle, put_BackColor, AnimLibA::AnimationBackStyleConstants
	/// \endif
	virtual HRESULT STDMETHODCALLTYPE put_AnimationBackStyle(AnimationBackStyleConstants newValue);
	/// \brief <em>Retrieves the current setting of the \c Appearance property</em>
	///
	/// Retrieves the kind of border that is drawn around the control. Any of the values defined by
	/// the \c AppearanceConstants enumeration is valid.
	///
	/// \param[out] pValue The property's current setting.
	///
	/// \return An \c HRESULT error code.
	///
	/// \if UNICODE
	///   \sa put_Appearance, get_BorderStyle, AnimLibU::AppearanceConstants
	/// \else
	///   \sa put_Appearance, get_BorderStyle, AnimLibA::AppearanceConstants
	/// \endif
	virtual HRESULT STDMETHODCALLTYPE get_Appearance(AppearanceConstants* pValue);
	/// \brief <em>Sets the \c Appearance property</em>
	///
	/// Sets the kind of border that is drawn around the control. Any of the values defined by the
	/// \c AppearanceConstants enumeration is valid.
	///
	/// \param[in] newValue The setting to apply.
	///
	/// \return An \c HRESULT error code.
	///
	/// \if UNICODE
	///   \sa get_Appearance, put_BorderStyle, AnimLibU::AppearanceConstants
	/// \else
	///   \sa get_Appearance, put_BorderStyle, AnimLibA::AppearanceConstants
	/// \endif
	virtual HRESULT STDMETHODCALLTYPE put_Appearance(AppearanceConstants newValue);
	/// \brief <em>Retrieves the control's application ID</em>
	///
	/// Retrieves the control's application ID. This property is part of the fingerprint that
	/// uniquely identifies each software written by Timo "TimoSoft" Kunze.
	///
	/// \param[out] pValue The application ID.
	///
	/// \return An \c HRESULT error code.
	///
	/// \remarks This property is hidden and read-only.
	///
	/// \sa get_AppName, get_AppShortName, get_Build, get_CharSet, get_IsRelease, get_Programmer,
	///     get_Tester
	virtual HRESULT STDMETHODCALLTYPE get_AppID(SHORT* pValue);
	/// \brief <em>Retrieves the control's application name</em>
	///
	/// Retrieves the control's application name. This property is part of the fingerprint that
	/// uniquely identifies each software written by Timo "TimoSoft" Kunze.
	///
	/// \param[out] pValue The application name.
	///
	/// \return An \c HRESULT error code.
	///
	/// \remarks This property is hidden and read-only.
	///
	/// \sa get_AppID, get_AppShortName, get_Build, get_CharSet, get_IsRelease, get_Programmer,
	///     get_Tester
	virtual HRESULT STDMETHODCALLTYPE get_AppName(BSTR* pValue);
	/// \brief <em>Retrieves the control's short application name</em>
	///
	/// Retrieves the control's short application name. This property is part of the fingerprint that
	/// uniquely identifies each software written by Timo "TimoSoft" Kunze.
	///
	/// \param[out] pValue The short application name.
	///
	/// \return An \c HRESULT error code.
	///
	/// \remarks This property is hidden and read-only.
	///
	/// \sa get_AppID, get_AppName, get_Build, get_CharSet, get_IsRelease, get_Programmer, get_Tester
	virtual HRESULT STDMETHODCALLTYPE get_AppShortName(BSTR* pValue);
	/// \brief <em>Retrieves the current setting of the \c AutoStartReplay property</em>
	///
	/// Retrieves whether replay of the animation is started automatically after the animation was loaded.
	/// If set to \c VARIANT_TRUE, the animation starts automatically (playing all frames in an endless
	/// loop), otherwise not.
	///
	/// \param[out] pValue The property's current setting.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa put_AutoStartReplay, OpenAnimationFromFile, OpenAnimationFromResource, StartReplay,
	///     Raise_StartedReplay
	virtual HRESULT STDMETHODCALLTYPE get_AutoStartReplay(VARIANT_BOOL* pValue);
	/// \brief <em>Sets the \c AutoStartReplay property</em>
	///
	/// Sets whether replay of the animation is started automatically after the animation was loaded.
	/// If set to \c VARIANT_TRUE, the animation starts automatically (playing all frames in an endless
	/// loop), otherwise not.
	///
	/// \param[in] newValue The setting to apply.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa get_AutoStartReplay, OpenAnimationFromFile, OpenAnimationFromResource, StartReplay,
	///     Raise_StartedReplay
	virtual HRESULT STDMETHODCALLTYPE put_AutoStartReplay(VARIANT_BOOL newValue);
	/// \brief <em>Retrieves the current setting of the \c BackColor property</em>
	///
	/// Retrieves the control's background color.
	///
	/// \param[out] pValue The property's current setting.
	///
	/// \return An \c HRESULT error code.
	///
	/// \remarks This property isn't supported for comctl32.dll version 6.0 or newer.
	///
	/// \sa put_BackColor, get_AnimationBackStyle
	virtual HRESULT STDMETHODCALLTYPE get_BackColor(OLE_COLOR* pValue);
	/// \brief <em>Sets the \c BackColor property</em>
	///
	/// Sets the control's background color.
	///
	/// \param[in] newValue The setting to apply.
	///
	/// \return An \c HRESULT error code.
	///
	/// \remarks This property isn't supported for comctl32.dll version 6.0 or newer.
	///
	/// \sa get_BackColor, put_AnimationBackStyle
	virtual HRESULT STDMETHODCALLTYPE put_BackColor(OLE_COLOR newValue);
	/// \brief <em>Retrieves the current setting of the \c BorderStyle property</em>
	///
	/// Retrieves the kind of inner border that is drawn around the control. Any of the values defined
	/// by the \c BorderStyleConstants enumeration is valid.
	///
	/// \param[out] pValue The property's current setting.
	///
	/// \return An \c HRESULT error code.
	///
	/// \if UNICODE
	///   \sa put_BorderStyle, get_Appearance, AnimLibU::BorderStyleConstants
	/// \else
	///   \sa put_BorderStyle, get_Appearance, AnimLibA::BorderStyleConstants
	/// \endif
	virtual HRESULT STDMETHODCALLTYPE get_BorderStyle(BorderStyleConstants* pValue);
	/// \brief <em>Sets the \c BorderStyle property</em>
	///
	/// Sets the kind of inner border that is drawn around the control. Any of the values defined by
	/// the \c BorderStyleConstants enumeration is valid.
	///
	/// \param[in] newValue The setting to apply.
	///
	/// \return An \c HRESULT error code.
	///
	/// \if UNICODE
	///   \sa get_BorderStyle, put_Appearance, AnimLibU::BorderStyleConstants
	/// \else
	///   \sa get_BorderStyle, put_Appearance, AnimLibA::BorderStyleConstants
	/// \endif
	virtual HRESULT STDMETHODCALLTYPE put_BorderStyle(BorderStyleConstants newValue);
	/// \brief <em>Retrieves the control's build number</em>
	///
	/// Retrieves the control's build number. This property is part of the fingerprint that
	/// uniquely identifies each software written by Timo "TimoSoft" Kunze.
	///
	/// \param[out] pValue The build number.
	///
	/// \return An \c HRESULT error code.
	///
	/// \remarks This property is hidden and read-only.
	///
	/// \sa get_AppID, get_AppName, get_AppShortName, get_CharSet, get_IsRelease, get_Programmer,
	///     get_Tester
	virtual HRESULT STDMETHODCALLTYPE get_Build(LONG* pValue);
	/// \brief <em>Retrieves the current setting of the \c CenterAnimation property</em>
	///
	/// Retrieves whether the animation is centered within the control. If set to \c VARIANT_TRUE, the
	/// animation is centered, otherwise not.
	///
	/// \param[out] pValue The property's current setting.
	///
	/// \return An \c HRESULT error code.
	///
	/// \attention Changing this property destroys and recreates the control window.
	///
	/// \sa put_CenterAnimation
	virtual HRESULT STDMETHODCALLTYPE get_CenterAnimation(VARIANT_BOOL* pValue);
	/// \brief <em>Sets the \c CenterAnimation property</em>
	///
	/// Sets whether the animation is centered within the control. If set to \c VARIANT_TRUE, the
	/// animation is centered, otherwise not.
	///
	/// \param[in] newValue The setting to apply.
	///
	/// \return An \c HRESULT error code.
	///
	/// \attention Changing this property destroys and recreates the control window.
	///
	/// \sa get_CenterAnimation
	virtual HRESULT STDMETHODCALLTYPE put_CenterAnimation(VARIANT_BOOL newValue);
	/// \brief <em>Retrieves the control's character set</em>
	///
	/// Retrieves the control's character set (Unicode/ANSI). This property is part of the fingerprint
	/// that uniquely identifies each software written by Timo "TimoSoft" Kunze.
	///
	/// \param[out] pValue The character set.
	///
	/// \return An \c HRESULT error code.
	///
	/// \remarks This property is hidden and read-only.
	///
	/// \sa get_AppID, get_AppName, get_AppShortName, get_Build, get_IsRelease, get_Programmer,
	///     get_Tester
	virtual HRESULT STDMETHODCALLTYPE get_CharSet(BSTR* pValue);
	/// \brief <em>Retrieves the current setting of the \c DisabledEvents property</em>
	///
	/// Retrieves the events that won't be fired. Disabling events increases performance. Any
	/// combination of the values defined by the \c DisabledEventsConstants enumeration is valid.
	///
	/// \param[out] pValue The property's current setting.
	///
	/// \return An \c HRESULT error code.
	///
	/// \if UNICODE
	///   \sa put_DisabledEvents, AnimLibU::DisabledEventsConstants
	/// \else
	///   \sa put_DisabledEvents, AnimLibA::DisabledEventsConstants
	/// \endif
	virtual HRESULT STDMETHODCALLTYPE get_DisabledEvents(DisabledEventsConstants* pValue);
	/// \brief <em>Sets the \c DisabledEvents property</em>
	///
	/// Sets the events that won't be fired. Disabling events increases performance. Any
	/// combination of the values defined by the \c DisabledEventsConstants enumeration is valid.
	///
	/// \param[in] newValue The setting to apply.
	///
	/// \return An \c HRESULT error code.
	///
	/// \if UNICODE
	///   \sa get_DisabledEvents, AnimLibU::DisabledEventsConstants
	/// \else
	///   \sa get_DisabledEvents, AnimLibA::DisabledEventsConstants
	/// \endif
	virtual HRESULT STDMETHODCALLTYPE put_DisabledEvents(DisabledEventsConstants newValue);
	/// \brief <em>Retrieves the current setting of the \c DontRedraw property</em>
	///
	/// Retrieves whether automatic redrawing of the control is enabled or disabled. If set to
	/// \c VARIANT_FALSE, the control will redraw itself automatically; otherwise not.
	///
	/// \param[out] pValue The property's current setting.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa put_DontRedraw
	virtual HRESULT STDMETHODCALLTYPE get_DontRedraw(VARIANT_BOOL* pValue);
	/// \brief <em>Sets the \c DontRedraw property</em>
	///
	/// Enables or disables automatic redrawing of the control. Disabling redraw while doing large changes
	/// on the control may increase performance. If set to \c VARIANT_FALSE, the control will redraw itself
	/// automatically; otherwise not.
	///
	/// \param[in] newValue The setting to apply.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa get_DontRedraw
	virtual HRESULT STDMETHODCALLTYPE put_DontRedraw(VARIANT_BOOL newValue);
	/// \brief <em>Retrieves the current setting of the \c Enabled property</em>
	///
	/// Retrieves whether the control is enabled or disabled for user input. If set to \c VARIANT_TRUE,
	/// it reacts to user input; otherwise not.
	///
	/// \param[out] pValue The property's current setting.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa put_Enabled
	virtual HRESULT STDMETHODCALLTYPE get_Enabled(VARIANT_BOOL* pValue);
	/// \brief <em>Sets the \c Enabled property</em>
	///
	/// Enables or disables the control for user input. If set to \c VARIANT_TRUE, the control reacts
	/// to user input; otherwise not.
	///
	/// \param[in] newValue The setting to apply.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa get_Enabled
	virtual HRESULT STDMETHODCALLTYPE put_Enabled(VARIANT_BOOL newValue);
	/// \brief <em>Retrieves the current setting of the \c HoverTime property</em>
	///
	/// Retrieves the number of milliseconds the mouse cursor must be located over the control's client
	/// area before the \c MouseHover event is fired. If set to -1, the system hover time is used.
	///
	/// \param[out] pValue The property's current setting.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa put_HoverTime, Raise_MouseHover
	virtual HRESULT STDMETHODCALLTYPE get_HoverTime(LONG* pValue);
	/// \brief <em>Sets the \c HoverTime property</em>
	///
	/// Sets the number of milliseconds the mouse cursor must be located over the control's client
	/// area before the \c MouseHover event is fired. If set to -1, the system hover time is used.
	///
	/// \param[in] newValue The setting to apply.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa get_HoverTime, Raise_MouseHover
	virtual HRESULT STDMETHODCALLTYPE put_HoverTime(LONG newValue);
	/// \brief <em>Retrieves the current setting of the \c hWnd property</em>
	///
	/// Retrieves the control's window handle.
	///
	/// \param[out] pValue The property's current setting.
	///
	/// \return An \c HRESULT error code.
	///
	/// \remarks This property is read-only.
	///
	/// \sa Raise_RecreatedControlWindow, Raise_DestroyedControlWindow
	virtual HRESULT STDMETHODCALLTYPE get_hWnd(OLE_HANDLE* pValue);
	/// \brief <em>Retrieves the current setting of the \c IsPlaying property</em>
	///
	/// Retrieves whether the control is currently playing an animation. If \c VARIANT_TRUE, it is playing an
	/// animation; otherwise not.
	///
	/// \param[out] pValue The property's current setting.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa StartReplay, StopReplay, Raise_StartedReplay, Raise_StoppedReplay
	virtual HRESULT STDMETHODCALLTYPE get_IsPlaying(VARIANT_BOOL* pValue);
	/// \brief <em>Retrieves the control's release type</em>
	///
	/// Retrieves the control's release type. This property is part of the fingerprint that uniquely
	/// identifies each software written by Timo "TimoSoft" Kunze. If set to \c VARIANT_TRUE, the
	/// control was compiled for release; otherwise it was compiled for debugging.
	///
	/// \param[out] pValue The release type.
	///
	/// \return An \c HRESULT error code.
	///
	/// \remarks This property is hidden and read-only.
	///
	/// \sa get_AppID, get_AppName, get_AppShortName, get_Build, get_CharSet, get_Programmer, get_Tester
	virtual HRESULT STDMETHODCALLTYPE get_IsRelease(VARIANT_BOOL* pValue);
	/// \brief <em>Retrieves the current setting of the \c MouseIcon property</em>
	///
	/// Retrieves a user-defined mouse cursor. It's used if \c MousePointer is set to \c mpCustom.
	///
	/// \param[out] ppMouseIcon Receives the picture object's \c IPictureDisp implementation.
	///
	/// \return An \c HRESULT error code.
	///
	/// \if UNICODE
	///   \sa put_MouseIcon, putref_MouseIcon, get_MousePointer, AnimLibU::MousePointerConstants,
	///       <a href="https://msdn.microsoft.com/en-us/library/ms680762.aspx">IPictureDisp</a>
	/// \else
	///   \sa put_MouseIcon, putref_MouseIcon, get_MousePointer, AnimLibA::MousePointerConstants,
	///       <a href="https://msdn.microsoft.com/en-us/library/ms680762.aspx">IPictureDisp</a>
	/// \endif
	virtual HRESULT STDMETHODCALLTYPE get_MouseIcon(IPictureDisp** ppMouseIcon);
	/// \brief <em>Sets the \c MouseIcon property</em>
	///
	/// Sets a user-defined mouse cursor. It's used if \c MousePointer is set to \c mpCustom.
	///
	/// \param[in] pNewMouseIcon The new picture object's \c IPictureDisp implementation.
	///
	/// \return An \c HRESULT error code.
	///
	/// \remarks The object identified by \c pNewMouseIcon is cloned.
	///
	/// \if UNICODE
	///   \sa get_MouseIcon, putref_MouseIcon, put_MousePointer, AnimLibU::MousePointerConstants,
	///       <a href="https://msdn.microsoft.com/en-us/library/ms680762.aspx">IPictureDisp</a>
	/// \else
	///   \sa get_MouseIcon, putref_MouseIcon, put_MousePointer, AnimLibA::MousePointerConstants,
	///       <a href="https://msdn.microsoft.com/en-us/library/ms680762.aspx">IPictureDisp</a>
	/// \endif
	virtual HRESULT STDMETHODCALLTYPE put_MouseIcon(IPictureDisp* pNewMouseIcon);
	/// \brief <em>Sets the \c MouseIcon property</em>
	///
	/// Sets a user-defined mouse cursor. It's used if \c MousePointer is set to \c mpCustom.
	///
	/// \param[in] pNewMouseIcon The new picture object's \c IPictureDisp implementation.
	///
	/// \return An \c HRESULT error code.
	///
	/// \if UNICODE
	///   \sa get_MouseIcon, put_MouseIcon, put_MousePointer, AnimLibU::MousePointerConstants,
	///       <a href="https://msdn.microsoft.com/en-us/library/ms680762.aspx">IPictureDisp</a>
	/// \else
	///   \sa get_MouseIcon, put_MouseIcon, put_MousePointer, AnimLibA::MousePointerConstants,
	///       <a href="https://msdn.microsoft.com/en-us/library/ms680762.aspx">IPictureDisp</a>
	/// \endif
	virtual HRESULT STDMETHODCALLTYPE putref_MouseIcon(IPictureDisp* pNewMouseIcon);
	/// \brief <em>Retrieves the current setting of the \c MousePointer property</em>
	///
	/// Retrieves the cursor's type that's used if the mouse cursor is placed within the control's
	/// client area. Any of the values defined by the \c MousePointerConstants enumeration is valid.
	///
	/// \param[out] pValue The property's current setting.
	///
	/// \return An \c HRESULT error code.
	///
	/// \if UNICODE
	///   \sa put_MousePointer, get_MouseIcon, AnimLibU::MousePointerConstants
	/// \else
	///   \sa put_MousePointer, get_MouseIcon, AnimLibA::MousePointerConstants
	/// \endif
	virtual HRESULT STDMETHODCALLTYPE get_MousePointer(MousePointerConstants* pValue);
	/// \brief <em>Sets the \c MousePointer property</em>
	///
	/// Sets the cursor's type that's used if the mouse cursor is placed within the control's
	/// client area. Any of the values defined by the \c MousePointerConstants enumeration is valid.
	///
	/// \param[in] newValue The setting to apply.
	///
	/// \return An \c HRESULT error code.
	///
	/// \if UNICODE
	///   \sa get_MousePointer, put_MouseIcon, AnimLibU::MousePointerConstants
	/// \else
	///   \sa get_MousePointer, put_MouseIcon, AnimLibA::MousePointerConstants
	/// \endif
	virtual HRESULT STDMETHODCALLTYPE put_MousePointer(MousePointerConstants newValue);
	/// \brief <em>Retrieves the name(s) of the control's programmer(s)</em>
	///
	/// Retrieves the name(s) of the control's programmer(s). This property is part of the fingerprint
	/// that uniquely identifies each software written by Timo "TimoSoft" Kunze.
	///
	/// \param[out] pValue The programmer.
	///
	/// \return An \c HRESULT error code.
	///
	/// \remarks This property is hidden and read-only.
	///
	/// \sa get_AppID, get_AppName, get_AppShortName, get_Build, get_CharSet, get_IsRelease, get_Tester
	virtual HRESULT STDMETHODCALLTYPE get_Programmer(BSTR* pValue);
	/// \brief <em>Retrieves the current setting of the \c RegisterForOLEDragDrop property</em>
	///
	/// Retrieves whether the control is registered as a target for OLE drag'n'drop. If set to
	/// \c VARIANT_TRUE, the control accepts OLE drag'n'drop actions; otherwise not.
	///
	/// \param[out] pValue The property's current setting.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa put_RegisterForOLEDragDrop, get_SupportOLEDragImages, Raise_OLEDragEnter
	virtual HRESULT STDMETHODCALLTYPE get_RegisterForOLEDragDrop(VARIANT_BOOL* pValue);
	/// \brief <em>Sets the \c RegisterForOLEDragDrop property</em>
	///
	/// Sets whether the control is registered as a target for OLE drag'n'drop. If set to
	/// \c VARIANT_TRUE, the control accepts OLE drag'n'drop actions; otherwise not.
	///
	/// \param[in] newValue The setting to apply.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa get_RegisterForOLEDragDrop, put_SupportOLEDragImages, Raise_OLEDragEnter
	virtual HRESULT STDMETHODCALLTYPE put_RegisterForOLEDragDrop(VARIANT_BOOL newValue);
	/// \brief <em>Retrieves the current setting of the \c SupportOLEDragImages property</em>
	///
	/// Retrieves whether the control creates an \c IDropTargetHelper object, so that a drag image can be
	/// shown during OLE drag'n'drop. If set to \c VARIANT_TRUE, the control creates the object; otherwise
	/// not.
	///
	/// \param[out] pValue The property's current setting.
	///
	/// \return An \c HRESULT error code.
	///
	/// \remarks Requires shell32.dll version 5.0 or higher.
	///
	/// \sa put_SupportOLEDragImages, get_RegisterForOLEDragDrop, FinishOLEDragDrop,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms646238.aspx">IDropTargetHelper</a>
	virtual HRESULT STDMETHODCALLTYPE get_SupportOLEDragImages(VARIANT_BOOL* pValue);
	/// \brief <em>Sets the \c SupportOLEDragImages property</em>
	///
	/// Sets whether the control creates an \c IDropTargetHelper object, so that a drag image can be
	/// shown during OLE drag'n'drop. If set to \c VARIANT_TRUE, the control creates the object; otherwise
	/// not.
	///
	/// \param[in] newValue The setting to apply.
	///
	/// \return An \c HRESULT error code.
	///
	/// \remarks Requires shell32.dll version 5.0 or higher.
	///
	/// \sa get_SupportOLEDragImages, put_RegisterForOLEDragDrop, FinishOLEDragDrop,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms646238.aspx">IDropTargetHelper</a>
	virtual HRESULT STDMETHODCALLTYPE put_SupportOLEDragImages(VARIANT_BOOL newValue);
	/// \brief <em>Retrieves the name(s) of the control's tester(s)</em>
	///
	/// Retrieves the name(s) of the control's tester(s). This property is part of the fingerprint
	/// that uniquely identifies each software written by Timo "TimoSoft" Kunze.
	///
	/// \param[out] pValue The name(s) of the tester(s).
	///
	/// \return An \c HRESULT error code.
	///
	/// \remarks This property is hidden and read-only.
	///
	/// \sa get_AppID, get_AppName, get_AppShortName, get_Build, get_CharSet, get_IsRelease,
	///     get_Programmer
	virtual HRESULT STDMETHODCALLTYPE get_Tester(BSTR* pValue);
	/// \brief <em>Retrieves the control's version</em>
	///
	/// \param[out] pValue The control's version.
	///
	/// \return An \c HRESULT error code.
	///
	/// \remarks This property is read-only.
	virtual HRESULT STDMETHODCALLTYPE get_Version(BSTR* pValue);

	/// \brief <em>Displays the control's credits</em>
	///
	/// Displays some information about this control and its author.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa AboutDlg
	virtual HRESULT STDMETHODCALLTYPE About(void);
	/// \brief <em>Closes the currently opened animation</em>
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa OpenAnimationFromFile, OpenAnimationFromResource, StopReplay
	virtual HRESULT STDMETHODCALLTYPE CloseAnimation(void);
	/// \brief <em>Displays a single frame of the animation</em>
	///
	/// \param[in] frameNumber The zero-based index of the frame to display.
	/// \param[out] pSuccess If \c VARIANT_TRUE, the frame was displayed successfully; otherwise not.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa StartReplay, StopReplay, OpenAnimationFromFile, OpenAnimationFromResource
	virtual HRESULT STDMETHODCALLTYPE DisplayFrame(LONG frameNumber, VARIANT_BOOL* pSuccess);
	/// \brief <em>Finishes a pending drop operation</em>
	///
	/// During a drag'n'drop operation the drag image is displayed until the \c OLEDragDrop event has been
	/// handled. This order is intended by Microsoft Windows. However, if a message box is displayed from
	/// within the \c OLEDragDrop event, or the drop operation cannot be performed asynchronously and takes
	/// a long time, it may be desirable to remove the drag image earlier.\n
	/// This method will break the intended order and finish the drag'n'drop operation (including removal
	/// of the drag image) immediately.
	///
	/// \remarks This method will fail if not called from the \c OLEDragDrop event handler or if no drag
	///          images are used.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa Raise_OLEDragDrop, get_SupportOLEDragImages
	virtual HRESULT STDMETHODCALLTYPE FinishOLEDragDrop(void);
	/// \brief <em>Loads the control's settings from the specified file</em>
	///
	/// \param[in] file The file to read from.
	/// \param[out] pSucceeded Will be set to \c VARIANT_TRUE on success and to \c VARIANT_FALSE otherwise.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa SaveSettingsToFile
	virtual HRESULT STDMETHODCALLTYPE LoadSettingsFromFile(BSTR file, VARIANT_BOOL* pSucceeded);
	/// \brief <em>Opens the specified animation file and displays the first frame</em>
	///
	/// \param[in] filePath The path of the animation file to open.
	/// \param[out] pSuccess If \c VARIANT_TRUE, the specified file was opened successfully; otherwise not.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa OpenAnimationFromResource, CloseAnimation, get_AutoStartReplay, StartReplay, DisplayFrame
	virtual HRESULT STDMETHODCALLTYPE OpenAnimationFromFile(BSTR filePath, VARIANT_BOOL* pSuccess);
	/// \brief <em>Opens the specified animation resource and displays the first frame</em>
	///
	/// \param[in] hModule The handle of the module from which to load the animation resource.
	/// \param[in] resourceID The ID of the resource to load.
	/// \param[in] resourceTypeName The type name of the resource to load. Set it to an empty string if you
	///            want to load an AVI animation. Otherwise set it to the name of the type under which the
	///            animation is stored in the resource file.
	/// \param[out] pSuccess If \c VARIANT_TRUE, the specified resource was opened successfully; otherwise
	///             not.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa OpenAnimationFromResource, CloseAnimation, get_AutoStartReplay, StartReplay, DisplayFrame
	virtual HRESULT STDMETHODCALLTYPE OpenAnimationFromResource(LONG hModule, LONG resourceID, BSTR resourceTypeName, VARIANT_BOOL* pSuccess);
	/// \brief <em>Advises the control to redraw itself</em>
	///
	/// \return An \c HRESULT error code.
	virtual HRESULT STDMETHODCALLTYPE Refresh(void);
	/// \brief <em>Saves the control's settings to the specified file</em>
	///
	/// \param[in] file The file to write to.
	/// \param[out] pSucceeded Will be set to \c VARIANT_TRUE on success and to \c VARIANT_FALSE otherwise.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa LoadSettingsFromFile
	virtual HRESULT STDMETHODCALLTYPE SaveSettingsToFile(BSTR file, VARIANT_BOOL* pSucceeded);
	/// \brief <em>Starts playing the animation</em>
	///
	/// \param[in] startFrame The zero-based index of the frame at which the animation shoult start.
	/// \param[in] endFrame The zero-based index of the frame at which the animation shoult end. If set to
	///            \c -1, the animation will be played up to the last frame.
	/// \param[in] repeats The number of repeats of the animation. If set to \c -1, the animation will
	///            repeat until it is stopped using the \c StopReplay method. If set to \c -2, the animation
	///            will repeat as often as recommended by the animation itself. If the animation does not
	///            specify a number of repeats, it will repeat until it is stopped using the \c StopReplay
	///            method.
	/// \param[out] pSuccess If \c VARIANT_TRUE, the animation was started successfully; otherwise not.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa StopReplay, get_IsPlaying, get_AutoStartReplay, OpenAnimationFromFile, OpenAnimationFromResource,
	///     DisplayFrame, Raise_StartedReplay
	virtual HRESULT STDMETHODCALLTYPE StartReplay(LONG startFrame = 0, LONG endFrame = -1, LONG repeats = -2, VARIANT_BOOL* pSuccess = NULL);
	/// \brief <em>Stops playing the animation</em>
	///
	/// \param[out] pSuccess If \c VARIANT_TRUE, the animation was stopped successfully; otherwise not.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa StartReplay, get_IsPlaying, CloseAnimation, DisplayFrame, Raise_StoppedReplay
	virtual HRESULT STDMETHODCALLTYPE StopReplay(VARIANT_BOOL* pSuccess);
	//@}
	//////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////
	/// \name Property object changes
	///
	//@{
	/// \brief <em>Will be called after a property object was changed</em>
	///
	/// \param[in] propertyObject The \c DISPID of the property object.
	/// \param[in] objectProperty The \c DISPID of the property that was changed.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa PropertyNotifySinkImpl::OnChanged
	HRESULT OnPropertyObjectChanged(DISPID /*propertyObject*/, DISPID /*objectProperty*/);
	/// \brief <em>Will be called before a property object is changed</em>
	///
	/// \param[in] propertyObject The \c DISPID of the property object.
	/// \param[in] objectProperty The \c DISPID of the property that is about to be changed.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa PropertyNotifySinkImpl::OnRequestEdit
	HRESULT OnPropertyObjectRequestEdit(DISPID /*propertyObject*/, DISPID /*objectProperty*/);
	//@}
	//////////////////////////////////////////////////////////////////////

	/// \brief <em>Called to create the control window</em>
	///
	/// Called to create the control window. This method overrides \c CWindowImpl::Create() and is
	/// used to customize the window styles.
	///
	/// \param[in] hWndParent The control's parent window.
	/// \param[in] rect The control's bounding rectangle.
	/// \param[in] szWindowName The control's window name.
	/// \param[in] dwStyle The control's window style. Will be ignored.
	/// \param[in] dwExStyle The control's extended window style. Will be ignored.
	/// \param[in] MenuOrID The control's ID.
	/// \param[in] lpCreateParam The window creation data. Will be passed to the created window.
	///
	/// \return The created window's handle.
	///
	/// \sa OnCreate, GetStyleBits, GetExStyleBits
	HWND Create(HWND hWndParent, ATL::_U_RECT rect = NULL, LPCTSTR szWindowName = NULL, DWORD dwStyle = 0, DWORD dwExStyle = 0, ATL::_U_MENUorID MenuOrID = 0U, LPVOID lpCreateParam = NULL);
	/// \brief <em>Overrides ATL's \c CComControlBase::OnDraw method</em>
	///
	/// This method is called if the control needs to be drawn.
	///
	/// \param[in] drawInfo Contains any details like the device context required for drawing.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa <a href="https://msdn.microsoft.com/en-us/library/056hw3hs.aspx">CComControlBase::OnDraw</a>
	virtual HRESULT OnDraw(ATL_DRAWINFO& drawInfo);
	/// \brief <em>Called after receiving the last message (typically \c WM_NCDESTROY)</em>
	///
	/// \param[in] hWnd The window being destroyed.
	///
	/// \sa OnCreate, OnDestroy
	void OnFinalMessage(HWND /*hWnd*/);
	/// \brief <em>Informs an embedded object of its display location within its container</em>
	///
	/// \param[in] pClientSite The \c IOleClientSite implementation of the container application's
	///            client side.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa <a href="https://msdn.microsoft.com/en-us/library/ms684013.aspx">IOleObject::SetClientSite</a>
	virtual HRESULT STDMETHODCALLTYPE IOleObject_SetClientSite(LPOLECLIENTSITE pClientSite);

protected:
	//////////////////////////////////////////////////////////////////////
	/// \name Implementation of IDropTarget
	///
	//@{
	/// \brief <em>Indicates whether a drop can be accepted, and, if so, the effect of the drop</em>
	///
	/// This method is called by the \c DoDragDrop function to determine the target's preferred drop
	/// effect the first time the user moves the mouse into the control during OLE drag'n'Drop. The
	/// target communicates the \c DoDragDrop function the drop effect it wants to be used on drop.
	///
	/// \param[in] pDataObject The \c IDataObject implementation of the object containing the dragged
	///            data.
	/// \param[in] keyState The pressed modifier keys (Shift, Ctrl, Alt) and mouse buttons. Any
	///            combination of the pressed button's and key's \c MK_* flags is valid.
	/// \param[in] mousePosition The mouse cursor's position (in pixels) relative to the screen's
	///            upper-left corner.
	/// \param[in,out] pEffect On entry, a bit field of the drop effects (defined by the \c DROPEFFECT
	///                enumeration) supported by the drag source. On return, this paramter must be set
	///                to the drop effect that the target wants to be used on drop.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa DragOver, DragLeave, Drop, Raise_OLEDragEnter,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms680106.aspx">IDropTarget::DragEnter</a>
	virtual HRESULT STDMETHODCALLTYPE DragEnter(IDataObject* pDataObject, DWORD keyState, POINTL mousePosition, DWORD* pEffect);
	/// \brief <em>Notifies the target that it no longer is the target of the current OLE drag'n'drop operation</em>
	///
	/// This method is called by the \c DoDragDrop function if the user moves the mouse out of the
	/// control during OLE drag'n'Drop or if the user canceled the operation. The target must release
	/// any references it holds to the data object.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa DragEnter, DragOver, Drop, Raise_OLEDragLeave,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms680110.aspx">IDropTarget::DragLeave</a>
	virtual HRESULT STDMETHODCALLTYPE DragLeave(void);
	/// \brief <em>Communicates the current drop effect to the \c DoDragDrop function</em>
	///
	/// This method is called by the \c DoDragDrop function if the user moves the mouse over the
	/// control during OLE drag'n'Drop. The target communicates the \c DoDragDrop function the drop
	/// effect it wants to be used on drop.
	///
	/// \param[in] keyState The pressed modifier keys (Shift, Ctrl, Alt) and mouse buttons. Any
	///            combination of the pressed button's and key's \c MK_* flags is valid.
	/// \param[in] mousePosition The mouse cursor's position (in pixels) relative to the screen's
	///            upper-left corner.
	/// \param[in,out] pEffect On entry, the current drop effect (defined by the \c DROPEFFECT
	///                enumeration). On return, this paramter must be set to the drop effect that the
	///                target wants to be used on drop.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa DragEnter, DragLeave, Drop, Raise_OLEDragMouseMove,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms680129.aspx">IDropTarget::DragOver</a>
	virtual HRESULT STDMETHODCALLTYPE DragOver(DWORD keyState, POINTL mousePosition, DWORD* pEffect);
	/// \brief <em>Incorporates the source data into the target and completes the drag'n'drop operation</em>
	///
	/// This method is called by the \c DoDragDrop function if the user completes the drag'n'drop
	/// operation. The target must incorporate the dragged data into itself and pass the used drop
	/// effect back to the \c DoDragDrop function. The target must release any references it holds to
	/// the data object.
	///
	/// \param[in] pDataObject The \c IDataObject implementation of the object containing the data
	///            to transfer.
	/// \param[in] keyState The pressed modifier keys (Shift, Ctrl, Alt) and mouse buttons. Any
	///            combination of the pressed button's and key's \c MK_* flags is valid.
	/// \param[in] mousePosition The mouse cursor's position (in pixels) relative to the screen's
	///            upper-left corner.
	/// \param[in,out] pEffect On entry, a bit field of the drop effects (defined by the \c DROPEFFECT
	///                enumeration) supported by the drag source. On return, this paramter must be set
	///                to the drop effect that the target finally executed.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa DragEnter, DragOver, DragLeave, Raise_OLEDragDrop,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms687242.aspx">IDropTarget::Drop</a>
	virtual HRESULT STDMETHODCALLTYPE Drop(IDataObject* pDataObject, DWORD keyState, POINTL mousePosition, DWORD* pEffect);
	//@}
	//////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////
	/// \name Implementation of ICategorizeProperties
	///
	//@{
	/// \brief <em>Retrieves a category's name</em>
	///
	/// \param[in] category The ID of the category whose name is requested.
	// \param[in] languageID The locale identifier identifying the language in which name should be
	//            provided.
	/// \param[out] pName The category's name.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa ICategorizeProperties::GetCategoryName
	virtual HRESULT STDMETHODCALLTYPE GetCategoryName(PROPCAT category, LCID /*languageID*/, BSTR* pName);
	/// \brief <em>Maps a property to a category</em>
	///
	/// \param[in] property The ID of the property whose category is requested.
	/// \param[out] pCategory The category's ID.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa ICategorizeProperties::MapPropertyToCategory
	virtual HRESULT STDMETHODCALLTYPE MapPropertyToCategory(DISPID property, PROPCAT* pCategory);
	//@}
	//////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////
	/// \name Implementation of ICreditsProvider
	///
	//@{
	/// \brief <em>Retrieves the name of the control's authors</em>
	///
	/// \return A string containing the names of all authors.
	CAtlString GetAuthors(void);
	/// \brief <em>Retrieves the URL of the website that has information about the control</em>
	///
	/// \return A string containing the URL.
	CAtlString GetHomepage(void);
	/// \brief <em>Retrieves the URL of the website where users can donate via Paypal</em>
	///
	/// \return A string containing the URL.
	CAtlString GetPaypalLink(void);
	/// \brief <em>Retrieves persons, websites, organizations we want to thank especially</em>
	///
	/// \return A string containing the special thanks.
	CAtlString GetSpecialThanks(void);
	/// \brief <em>Retrieves persons, websites, organizations we want to thank</em>
	///
	/// \return A string containing the thanks.
	CAtlString GetThanks(void);
	/// \brief <em>Retrieves the control's version</em>
	///
	/// \return A string containing the version.
	CAtlString GetVersion(void);
	//@}
	//////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////
	/// \name Implementation of IPerPropertyBrowsing
	///
	//@{
	/// \brief <em>A displayable string for a property's current value is required</em>
	///
	/// This method is called if the caller's user interface requests a user-friendly description of the
	/// specified property's current value that may be displayed instead of the value itself.
	/// We use this method for enumeration-type properties to display strings like "1 - At Root" instead
	/// of "1 - lsLinesAtRoot".
	///
	/// \param[in] property The ID of the property whose display name is requested.
	/// \param[out] pDescription The setting's display name.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa GetPredefinedStrings, GetDisplayStringForSetting,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms688734.aspx">IPerPropertyBrowsing::GetDisplayString</a>
	virtual HRESULT STDMETHODCALLTYPE GetDisplayString(DISPID property, BSTR* pDescription);
	/// \brief <em>Displayable strings for a property's predefined values are required</em>
	///
	/// This method is called if the caller's user interface requests user-friendly descriptions of the
	/// specified property's predefined values that may be displayed instead of the values itself.
	/// We use this method for enumeration-type properties to display strings like "1 - At Root" instead
	/// of "1 - lsLinesAtRoot".
	///
	/// \param[in] property The ID of the property whose display names are requested.
	/// \param[in,out] pDescriptions A caller-allocated, counted array structure containing the element
	///                count and address of a callee-allocated array of strings. This array will be
	///                filled with the display name strings.
	/// \param[in,out] pCookies A caller-allocated, counted array structure containing the element
	///                count and address of a callee-allocated array of \c DWORD values. Each \c DWORD
	///                value identifies a predefined value of the property.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa GetDisplayString, GetPredefinedValue, GetDisplayStringForSetting,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms679724.aspx">IPerPropertyBrowsing::GetPredefinedStrings</a>
	virtual HRESULT STDMETHODCALLTYPE GetPredefinedStrings(DISPID property, CALPOLESTR* pDescriptions, CADWORD* pCookies);
	/// \brief <em>A property's predefined value identified by a token is required</em>
	///
	/// This method is called if the caller's user interface requires a property's predefined value that
	/// it has the token of. The token was returned by the \c GetPredefinedStrings method.
	/// We use this method for enumeration-type properties to transform strings like "1 - At Root"
	/// back to the underlying enumeration value (here: \c lsLinesAtRoot).
	///
	/// \param[in] property The ID of the property for which a predefined value is requested.
	/// \param[in] cookie Token identifying which value to return. The token was previously returned
	///            in the \c pCookies array filled by \c IPerPropertyBrowsing::GetPredefinedStrings.
	/// \param[out] pPropertyValue A \c VARIANT that will receive the predefined value.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa GetPredefinedStrings,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms690401.aspx">IPerPropertyBrowsing::GetPredefinedValue</a>
	virtual HRESULT STDMETHODCALLTYPE GetPredefinedValue(DISPID property, DWORD cookie, VARIANT* pPropertyValue);
	/// \brief <em>A property's property page is required</em>
	///
	/// This method is called to request the \c CLSID of the property page used to edit the specified
	/// property.
	///
	/// \param[in] property The ID of the property whose property page is requested.
	/// \param[out] pPropertyPage The property page's \c CLSID.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa <a href="https://msdn.microsoft.com/en-us/library/ms694476.aspx">IPerPropertyBrowsing::MapPropertyToPage</a>
	virtual HRESULT STDMETHODCALLTYPE MapPropertyToPage(DISPID property, CLSID* pPropertyPage);
	//@}
	//////////////////////////////////////////////////////////////////////

	/// \brief <em>Retrieves a displayable string for a specified setting of a specified property</em>
	///
	/// Retrieves a user-friendly description of the specified property's specified setting. This
	/// description may be displayed by the caller's user interface instead of the setting itself.
	/// We use this method for enumeration-type properties to display strings like "1 - At Root" instead
	/// of "1 - lsLinesAtRoot".
	///
	/// \param[in] property The ID of the property for which to retrieve the display name.
	/// \param[in] cookie Token identifying the setting for which to retrieve a description.
	/// \param[out] description The setting's display name.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa GetDisplayString, GetPredefinedStrings, GetResStringWithNumber
	HRESULT GetDisplayStringForSetting(DISPID property, DWORD cookie, CComBSTR& description);

	//////////////////////////////////////////////////////////////////////
	/// \name Implementation of ISpecifyPropertyPages
	///
	//@{
	/// \brief <em>The property pages to show are required</em>
	///
	/// This method is called if the property pages, that may be displayed for this object, are required.
	///
	/// \param[out] pPropertyPages A caller-allocated, counted array structure containing the element
	///             count and address of a callee-allocated array of \c GUID structures. Each \c GUID
	///             structure identifies a property page to display.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa CommonProperties,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms687276.aspx">ISpecifyPropertyPages::GetPages</a>
	virtual HRESULT STDMETHODCALLTYPE GetPages(CAUUID* pPropertyPages);
	//@}
	//////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////
	/// \name Message handlers
	///
	//@{
	/// \brief <em>\c WM_CONTEXTMENU handler</em>
	///
	/// Will be called if the control's context menu should be displayed.
	/// We use this handler to raise the \c ContextMenu event.
	///
	/// \sa OnRButtonDown, Raise_ContextMenu,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms647592.aspx">WM_CONTEXTMENU</a>
	LRESULT OnContextMenu(UINT /*message*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*wasHandled*/);
	/// \brief <em>\c WM_CREATE handler</em>
	///
	/// Will be called right after the control was created.
	/// We use this handler to configure the control window and to raise the \c RecreatedControlWindow event.
	///
	/// \sa OnDestroy, OnFinalMessage, Raise_RecreatedControlWindow,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms632619.aspx">WM_CREATE</a>
	LRESULT OnCreate(UINT message, WPARAM wParam, LPARAM lParam, BOOL& /*wasHandled*/);
	/// \brief <em>\c WM_DESTROY handler</em>
	///
	/// Will be called while the control is being destroyed.
	/// We use this handler to tidy up and to raise the \c DestroyedControlWindow event.
	///
	/// \sa OnCreate, OnFinalMessage, Raise_DestroyedControlWindow,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms632620.aspx">WM_DESTROY</a>
	LRESULT OnDestroy(UINT /*message*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& wasHandled);
	/// \brief <em>\c WM_LBUTTONDOWN handler</em>
	///
	/// Will be called if the user presses the left mouse button while the mouse cursor is located over
	/// the control's client area.
	/// We use this handler to raise the \c MouseDown event.
	///
	/// \sa OnMButtonDown, OnRButtonDown, OnXButtonDown, Raise_MouseDown,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms645607.aspx">WM_LBUTTONDOWN</a>
	LRESULT OnLButtonDown(UINT /*message*/, WPARAM wParam, LPARAM lParam, BOOL& wasHandled);
	/// \brief <em>\c WM_LBUTTONUP handler</em>
	///
	/// Will be called if the user releases the left mouse button while the mouse cursor is located over
	/// the control's client area.
	/// We use this handler to raise the \c MouseUp event.
	///
	/// \sa OnMButtonUp, OnRButtonUp, OnXButtonUp, Raise_MouseUp,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms645608.aspx">WM_LBUTTONUP</a>
	LRESULT OnLButtonUp(UINT /*message*/, WPARAM wParam, LPARAM lParam, BOOL& wasHandled);
	/// \brief <em>\c WM_MBUTTONDOWN handler</em>
	///
	/// Will be called if the user presses the middle mouse button while the mouse cursor is located over
	/// the control's client area.
	/// We use this handler to raise the \c MouseDown event.
	///
	/// \sa OnLButtonDown, OnRButtonDown, OnXButtonDown, Raise_MouseDown,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms645610.aspx">WM_MBUTTONDOWN</a>
	LRESULT OnMButtonDown(UINT /*message*/, WPARAM wParam, LPARAM lParam, BOOL& wasHandled);
	/// \brief <em>\c WM_MBUTTONUP handler</em>
	///
	/// Will be called if the user releases the middle mouse button while the mouse cursor is located over
	/// the control's client area.
	/// We use this handler to raise the \c MouseUp event.
	///
	/// \sa OnLButtonUp, OnRButtonUp, OnXButtonUp, Raise_MouseUp,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms645611.aspx">WM_MBUTTONUP</a>
	LRESULT OnMButtonUp(UINT /*message*/, WPARAM wParam, LPARAM lParam, BOOL& wasHandled);
	/// \brief <em>\c WM_MOUSEACTIVATE handler</em>
	///
	/// Will be called if the control is inactive and the user clicked in its client area.
	/// We use this handler to exclude the control from receiving focus.
	///
	/// \sa <a href="https://msdn.microsoft.com/en-us/library/ms645612.aspx">WM_MOUSEACTIVATE</a>
	LRESULT OnMouseActivate(UINT /*message*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& wasHandled);
	/// \brief <em>\c WM_MOUSEHOVER handler</em>
	///
	/// Will be called if the mouse cursor has been located over the control's client area for a previously
	/// specified number of milliseconds.
	/// We use this handler to raise the \c MouseHover event.
	///
	/// \sa Raise_MouseHover,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms645613.aspx">WM_MOUSEHOVER</a>
	LRESULT OnMouseHover(UINT /*message*/, WPARAM wParam, LPARAM lParam, BOOL& wasHandled);
	/// \brief <em>\c WM_MOUSELEAVE handler</em>
	///
	/// Will be called if the user moves the mouse cursor out of the control's client area.
	/// We use this handler to raise the \c MouseLeave event.
	///
	/// \sa Raise_MouseLeave,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms645615.aspx">WM_MOUSELEAVE</a>
	LRESULT OnMouseLeave(UINT /*message*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& wasHandled);
	/// \brief <em>\c WM_MOUSEMOVE handler</em>
	///
	/// Will be called if the user moves the mouse while the mouse cursor is located over the control's
	/// client area.
	/// We use this handler to raise the \c MouseMove event.
	///
	/// \sa OnLButtonDown, OnLButtonUp, OnMouseWheel, Raise_MouseMove,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms645616.aspx">WM_MOUSEMOVE</a>
	LRESULT OnMouseMove(UINT /*message*/, WPARAM wParam, LPARAM lParam, BOOL& wasHandled);
	/// \brief <em>\c WM_MOUSEWHEEL and \c WM_MOUSEHWHEEL handler</em>
	///
	/// Will be called if the user rotates the mouse wheel while the mouse cursor is located over the
	/// control's client area.
	/// We use this handler to raise the \c MouseWheel event.
	///
	/// \sa OnMouseMove,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms645617.aspx">WM_MOUSEWHEEL</a>,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms645614.aspx">WM_MOUSEHWHEEL</a>
	// \sa OnMouseMove, Raise_MouseWheel,
	//     <a href="https://msdn.microsoft.com/en-us/library/ms645617.aspx">WM_MOUSEWHEEL</a>,
	//     <a href="https://msdn.microsoft.com/en-us/library/ms645614.aspx">WM_MOUSEHWHEEL</a>
	LRESULT OnMouseWheel(UINT message, WPARAM wParam, LPARAM lParam, BOOL& wasHandled);
	/// \brief <em>\c WM_NCHITTEST handler</em>
	///
	/// Will be called if the Windows window engine needs to know what the specified point belongs to.
	/// We use this handler to support mouse events.
	///
	/// \sa <a href="https://msdn.microsoft.com/en-us/library/ms645618.aspx">WM_NCHITTEST</a>
	LRESULT OnNCHitTest(UINT /*message*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*wasHandled*/);
	/// \brief <em>\c WM_RBUTTONDOWN handler</em>
	///
	/// Will be called if the user presses the right mouse button while the mouse cursor is located over
	/// the control's client area.
	/// We use this handler to raise the \c MouseDown event.
	///
	/// \sa OnLButtonDown, OnMButtonDown, OnXButtonDown, Raise_MouseDown,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms646242.aspx">WM_RBUTTONDOWN</a>
	LRESULT OnRButtonDown(UINT /*message*/, WPARAM wParam, LPARAM lParam, BOOL& wasHandled);
	/// \brief <em>\c WM_RBUTTONUP handler</em>
	///
	/// Will be called if the user releases the right mouse button while the mouse cursor is located over
	/// the control's client area.
	/// We use this handler to raise the \c MouseUp event.
	///
	/// \sa OnLButtonUp, OnMButtonUp, OnXButtonUp, Raise_MouseUp,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms646243.aspx">WM_RBUTTONUP</a>
	LRESULT OnRButtonUp(UINT /*message*/, WPARAM wParam, LPARAM lParam, BOOL& wasHandled);
	/// \brief <em>\c WM_SETCURSOR handler</em>
	///
	/// Will be called if the mouse cursor type is required that shall be used while the mouse cursor is
	/// located over the control's client area.
	/// We use this handler to set the mouse cursor type.
	///
	/// \sa get_MouseIcon, get_MousePointer,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms648382.aspx">WM_SETCURSOR</a>
	LRESULT OnSetCursor(UINT /*message*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& wasHandled);
	/// \brief <em>\c WM_SETREDRAW handler</em>
	///
	/// Will be called if the control's redraw state shall be changed.
	/// We use this handler for proper handling of the \c DontRedraw property.
	///
	/// \sa get_DontRedraw,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms534853.aspx">WM_SETREDRAW</a>
	LRESULT OnSetRedraw(UINT message, WPARAM wParam, LPARAM lParam, BOOL& /*wasHandled*/);
	/// \brief <em>\c WM_THEMECHANGED handler</em>
	///
	/// Will be called on themable systems if the theme was changed.
	/// We use this handler to update our appearance.
	///
	/// \sa Flags::usingThemes,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms632650.aspx">WM_THEMECHANGED</a>
	LRESULT OnThemeChanged(UINT /*message*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& wasHandled);
	/// \brief <em>\c WM_TIMER handler</em>
	///
	/// Will be called when a timer expires that's associated with the control.
	/// We use this handler for the \c DontRedraw property.
	///
	/// \sa get_DontRedraw,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms644902.aspx">WM_TIMER</a>
	LRESULT OnTimer(UINT /*message*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& wasHandled);
	/// \brief <em>\c WM_WINDOWPOSCHANGED handler</em>
	///
	/// Will be called if the control was moved.
	/// We use this handler to resize the control on COM level and to raise the \c ResizedControlWindow
	/// event.
	///
	/// \sa Raise_ResizedControlWindow,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms632652.aspx">WM_WINDOWPOSCHANGED</a>
	LRESULT OnWindowPosChanged(UINT /*message*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& wasHandled);
	/// \brief <em>\c WM_XBUTTONDOWN handler</em>
	///
	/// Will be called if the user presses one of the extended mouse buttons while the mouse cursor is
	/// located over the control's client area.
	/// We use this handler to raise the \c MouseDown event.
	///
	/// \sa OnLButtonDown, OnMButtonDown, OnRButtonDown, Raise_MouseDown,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms646245.aspx">WM_XBUTTONDOWN</a>
	LRESULT OnXButtonDown(UINT /*message*/, WPARAM wParam, LPARAM lParam, BOOL& wasHandled);
	/// \brief <em>\c WM_XBUTTONUP handler</em>
	///
	/// Will be called if the user releases one of the extended mouse buttons while the mouse cursor is
	/// located over the control's client area.
	/// We use this handler to raise the \c MouseUp event.
	///
	/// \sa OnLButtonUp, OnMButtonUp, OnRButtonUp, Raise_MouseUp,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms646246.aspx">WM_XBUTTONUP</a>
	LRESULT OnXButtonUp(UINT /*message*/, WPARAM wParam, LPARAM lParam, BOOL& wasHandled);
	/// \brief <em>\c WM_CTLCOLORSTATIC handler</em>
	///
	/// Will be called if the control asks its parent window to configure the specified device context for
	/// drawing the control, i. e. to setup the colors and brushes.
	/// We use this handler for the \c BackColor property and for proper theming support.
	///
	/// \sa get_BackColor,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms651165.aspx">WM_CTLCOLORSTATIC</a>
	LRESULT OnReflectedCtlColorStatic(UINT /*message*/, WPARAM wParam, LPARAM lParam, BOOL& /*wasHandled*/);
	/// \brief <em>\c ACM_OPEN handler</em>
	///
	/// Will be called if the control shall open a new animation.
	/// We use this handler to synchronize the \c Flags::animationType flag.
	///
	/// \sa OpenAnimationFromFile, OpenAnimationFromResource, CloseAnimation, Flags::animationType,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms673605.aspx">ACM_OPEN</a>
	LRESULT OnOpen(UINT message, WPARAM wParam, LPARAM lParam, BOOL& /*wasHandled*/);
	//@}
	//////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////
	/// \name Notification handlers
	///
	//@{
	//@}
	//////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////
	/// \name Command handlers
	///
	//@{
	/// \brief <em>\c ACN_START handler</em>
	///
	/// Will be called if the control's parent window is notified, that the control has started to play the
	/// animation.
	/// We use this handler to raise the \c StartedReplay event.
	///
	/// \sa OnReflectedStop, Raise_StartedReplay,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms673603.aspx">ACN_START</a>
	LRESULT OnReflectedStart(WORD /*notifyCode*/, WORD /*controlID*/, HWND /*hWnd*/, BOOL& /*wasHandled*/);
	/// \brief <em>\c ACN_STOP handler</em>
	///
	/// Will be called if the control's parent window is notified, that the control has stopped to play the
	/// animation.
	/// We use this handler to raise the \c StoppedReplay event.
	///
	/// \sa OnReflectedStart, Raise_StoppedReplay,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms673604.aspx">ACN_STOP</a>
	LRESULT OnReflectedStop(WORD /*notifyCode*/, WORD /*controlID*/, HWND /*hWnd*/, BOOL& /*wasHandled*/);
	//@}
	//////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////
	/// \name Event raisers
	///
	//@{
	/// \brief <em>Raises the \c Click event</em>
	///
	/// \param[in] button The mouse buttons that were pressed during the click. This should always be
	///            \c vbLeftButton (defined by VB's \c MouseButtonConstants enumeration).
	/// \param[in] shift The modifier keys (Shift, Ctrl, Alt) that were pressed during the click. Any
	///            combination of the values defined by VB's \c ShiftConstants enumeration is valid.
	/// \param[in] x The x-coordinate (in pixels) of the click's position relative to the control's
	///            upper-left corner.
	/// \param[in] y The y-coordinate (in pixels) of the click's position relative to the control's
	///            upper-left corner.
	///
	/// \return An \c HRESULT error code.
	///
	/// \remarks This event may be disabled.
	///
	/// \if UNICODE
	///   \sa Proxy_IAnimationEvents::Fire_Click, AnimLibU::_IAnimationEvents::Click,
	///       Raise_DblClick, Raise_MClick, Raise_RClick, Raise_XClick
	/// \else
	///   \sa Proxy_IAnimationEvents::Fire_Click, AnimLibA::_IAnimationEvents::Click,
	///       Raise_DblClick, Raise_MClick, Raise_RClick, Raise_XClick
	/// \endif
	inline HRESULT Raise_Click(SHORT button, SHORT shift, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y);
	/// \brief <em>Raises the \c ContextMenu event</em>
	///
	/// \param[in] button The pressed mouse buttons. Any combination of the values defined by VB's
	///            \c MouseButtonConstants enumeration is valid.
	/// \param[in] shift The pressed modifier keys (Shift, Ctrl, Alt). Any combination of the values
	///            defined by VB's \c ShiftConstants enumeration is valid.
	/// \param[in] x The x-coordinate (in pixels) of the menu's proposed position relative to the control's
	///            upper-left corner.
	/// \param[in] y The y-coordinate (in pixels) of the menu's proposed position relative to the control's
	///            upper-left corner.
	///
	/// \return An \c HRESULT error code.
	///
	/// \if UNICODE
	///   \sa Proxy_IAnimationEvents::Fire_ContextMenu, AnimLibU::_IAnimationEvents::ContextMenu,
	///       Raise_RClick
	/// \else
	///   \sa Proxy_IAnimationEvents::Fire_ContextMenu, AnimLibA::_IAnimationEvents::ContextMenu,
	///       Raise_RClick
	/// \endif
	inline HRESULT Raise_ContextMenu(SHORT button, SHORT shift, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y);
	/// \brief <em>Raises the \c DblClick event</em>
	///
	/// \param[in] button The mouse buttons that were pressed during the double-click. This should
	///            always be \c vbLeftButton (defined by VB's \c MouseButtonConstants enumeration).
	/// \param[in] shift The modifier keys (Shift, Ctrl, Alt) that were pressed during the double-click.
	///            Any combination of the values defined by VB's \c ShiftConstants enumeration is valid.
	/// \param[in] x The x-coordinate (in pixels) of the double-click's position relative to the control's
	///            upper-left corner.
	/// \param[in] y The y-coordinate (in pixels) of the double-click's position relative to the control's
	///            upper-left corner.
	///
	/// \return An \c HRESULT error code.
	///
	/// \remarks This event may be disabled.
	///
	/// \if UNICODE
	///   \sa Proxy_IAnimationEvents::Fire_DblClick, AnimLibU::_IAnimationEvents::DblClick,
	///       Raise_Click, Raise_MDblClick, Raise_RDblClick, Raise_XDblClick
	/// \else
	///   \sa Proxy_IAnimationEvents::Fire_DblClick, AnimLibA::_IAnimationEvents::DblClick,
	///       Raise_Click, Raise_MDblClick, Raise_RDblClick, Raise_XDblClick
	/// \endif
	inline HRESULT Raise_DblClick(SHORT button, SHORT shift, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y);
	/// \brief <em>Raises the \c DestroyedControlWindow event</em>
	///
	/// \param[in] hWnd The control's window handle.
	///
	/// \return An \c HRESULT error code.
	///
	/// \if UNICODE
	///   \sa Proxy_IAnimationEvents::Fire_DestroyedControlWindow,
	///       AnimLibU::_IAnimationEvents::DestroyedControlWindow, Raise_RecreatedControlWindow,
	///       get_hWnd
	/// \else
	///   \sa Proxy_IAnimationEvents::Fire_DestroyedControlWindow,
	///       AnimLibA::_IAnimationEvents::DestroyedControlWindow, Raise_RecreatedControlWindow,
	///       get_hWnd
	/// \endif
	inline HRESULT Raise_DestroyedControlWindow(LONG hWnd);
	/// \brief <em>Raises the \c MClick event</em>
	///
	/// \param[in] button The mouse buttons that were pressed during the click. This should always be
	///            \c vbMiddleButton (defined by VB's \c MouseButtonConstants enumeration).
	/// \param[in] shift The modifier keys (Shift, Ctrl, Alt) that were pressed during the click. Any
	///            combination of the values defined by VB's \c ShiftConstants enumeration is valid.
	/// \param[in] x The x-coordinate (in pixels) of the click's position relative to the control's
	///            upper-left corner.
	/// \param[in] y The y-coordinate (in pixels) of the click's position relative to the control's
	///            upper-left corner.
	///
	/// \return An \c HRESULT error code.
	///
	/// \remarks This event may be disabled.
	///
	/// \if UNICODE
	///   \sa Proxy_IAnimationEvents::Fire_MClick, AnimLibU::_IAnimationEvents::MClick, Raise_MDblClick,
	///       Raise_Click, Raise_RClick, Raise_XClick
	/// \else
	///   \sa Proxy_IAnimationEvents::Fire_MClick, AnimLibA::_IAnimationEvents::MClick, Raise_MDblClick,
	///       Raise_Click, Raise_RClick, Raise_XClick
	/// \endif
	inline HRESULT Raise_MClick(SHORT button, SHORT shift, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y);
	/// \brief <em>Raises the \c MDblClick event</em>
	///
	/// \param[in] button The mouse buttons that were pressed during the double-click. This should
	///            always be \c vbMiddleButton (defined by VB's \c MouseButtonConstants enumeration).
	/// \param[in] shift The modifier keys (Shift, Ctrl, Alt) that were pressed during the double-click.
	///            Any combination of the values defined by VB's \c ShiftConstants enumeration is valid.
	/// \param[in] x The x-coordinate (in pixels) of the double-click's position relative to the control's
	///            upper-left corner.
	/// \param[in] y The y-coordinate (in pixels) of the double-click's position relative to the control's
	///            upper-left corner.
	///
	/// \return An \c HRESULT error code.
	///
	/// \remarks This event may be disabled.
	///
	/// \if UNICODE
	///   \sa Proxy_IAnimationEvents::Fire_MDblClick, AnimLibU::_IAnimationEvents::MDblClick, Raise_MClick,
	///       Raise_DblClick, Raise_RDblClick, Raise_XDblClick
	/// \else
	///   \sa Proxy_IAnimationEvents::Fire_MDblClick, AnimLibA::_IAnimationEvents::MDblClick, Raise_MClick,
	///       Raise_DblClick, Raise_RDblClick, Raise_XDblClick
	/// \endif
	inline HRESULT Raise_MDblClick(SHORT button, SHORT shift, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y);
	/// \brief <em>Raises the \c MouseDown event</em>
	///
	/// \param[in] button The pressed mouse button. Any of the values defined by VB's
	///            \c MouseButtonConstants enumeration or the \c ExtendedMouseButtonConstants enumeration
	///            is valid.
	/// \param[in] shift The pressed modifier keys (Shift, Ctrl, Alt). Any combination of the values
	///            defined by VB's \c ShiftConstants enumeration is valid.
	/// \param[in] x The x-coordinate (in pixels) of the mouse cursor's position relative to the control's
	///            upper-left corner.
	/// \param[in] y The y-coordinate (in pixels) of the mouse cursor's position relative to the control's
	///            upper-left corner.
	///
	/// \return An \c HRESULT error code.
	///
	/// \remarks This event may be disabled.
	///
	/// \if UNICODE
	///   \sa Proxy_IAnimationEvents::Fire_MouseDown, AnimLibU::_IAnimationEvents::MouseDown, Raise_MouseUp,
	///       Raise_Click, Raise_MClick, Raise_RClick, Raise_XClick, AnimLibU::ExtendedMouseButtonConstants
	/// \else
	///   \sa Proxy_IAnimationEvents::Fire_MouseDown, AnimLibA::_IAnimationEvents::MouseDown, Raise_MouseUp,
	///       Raise_Click, Raise_MClick, Raise_RClick, Raise_XClick, AnimLibA::ExtendedMouseButtonConstants
	/// \endif
	inline HRESULT Raise_MouseDown(SHORT button, SHORT shift, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y);
	/// \brief <em>Raises the \c MouseEnter event</em>
	///
	/// \param[in] button The pressed mouse buttons. Any combination of the values defined by VB's
	///            \c MouseButtonConstants enumeration or the \c ExtendedMouseButtonConstants enumeration
	///            is valid.
	/// \param[in] shift The pressed modifier keys (Shift, Ctrl, Alt). Any combination of the values
	///            defined by VB's \c ShiftConstants enumeration is valid.
	/// \param[in] x The x-coordinate (in pixels) of the mouse cursor's position relative to the control's
	///            upper-left corner.
	/// \param[in] y The y-coordinate (in pixels) of the mouse cursor's position relative to the control's
	///            upper-left corner.
	///
	/// \return An \c HRESULT error code.
	///
	/// \remarks This event may be disabled.
	///
	/// \if UNICODE
	///   \sa Proxy_IAnimationEvents::Fire_MouseEnter, AnimLibU::_IAnimationEvents::MouseEnter,
	///       Raise_MouseLeave, Raise_MouseHover, Raise_MouseMove, AnimLibU::ExtendedMouseButtonConstants
	/// \else
	///   \sa Proxy_IAnimationEvents::Fire_MouseEnter, AnimLibA::_IAnimationEvents::MouseEnter,
	///       Raise_MouseLeave, Raise_MouseHover, Raise_MouseMove, AnimLibA::ExtendedMouseButtonConstants
	/// \endif
	inline HRESULT Raise_MouseEnter(SHORT button, SHORT shift, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y);
	/// \brief <em>Raises the \c MouseHover event</em>
	///
	/// \param[in] button The pressed mouse buttons. Any combination of the values defined by VB's
	///            \c MouseButtonConstants enumeration or the \c ExtendedMouseButtonConstants enumeration
	///            is valid.
	/// \param[in] shift The pressed modifier keys (Shift, Ctrl, Alt). Any combination of the values
	///            defined by VB's \c ShiftConstants enumeration is valid.
	/// \param[in] x The x-coordinate (in pixels) of the mouse cursor's position relative to the control's
	///            upper-left corner.
	/// \param[in] y The y-coordinate (in pixels) of the mouse cursor's position relative to the control's
	///            upper-left corner.
	///
	/// \return An \c HRESULT error code.
	///
	/// \remarks This event may be disabled.
	///
	/// \if UNICODE
	///   \sa Proxy_IAnimationEvents::Fire_MouseHover, AnimLibU::_IAnimationEvents::MouseHover,
	///       Raise_MouseEnter, Raise_MouseLeave, Raise_MouseMove, put_HoverTime,
	///       AnimLibU::ExtendedMouseButtonConstants
	/// \else
	///   \sa Proxy_IAnimationEvents::Fire_MouseHover, AnimLibA::_IAnimationEvents::MouseHover,
	///       Raise_MouseEnter, Raise_MouseLeave, Raise_MouseMove, put_HoverTime,
	///       AnimLibA::ExtendedMouseButtonConstants
	/// \endif
	inline HRESULT Raise_MouseHover(SHORT button, SHORT shift, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y);
	/// \brief <em>Raises the \c MouseLeave event</em>
	///
	/// \param[in] button The pressed mouse buttons. Any combination of the values defined by VB's
	///            \c MouseButtonConstants enumeration or the \c ExtendedMouseButtonConstants enumeration
	///            is valid.
	/// \param[in] shift The pressed modifier keys (Shift, Ctrl, Alt). Any combination of the values
	///            defined by VB's \c ShiftConstants enumeration is valid.
	/// \param[in] x The x-coordinate (in pixels) of the mouse cursor's position relative to the control's
	///            upper-left corner.
	/// \param[in] y The y-coordinate (in pixels) of the mouse cursor's position relative to the control's
	///            upper-left corner.
	///
	/// \return An \c HRESULT error code.
	///
	/// \remarks This event may be disabled.
	///
	/// \if UNICODE
	///   \sa Proxy_IAnimationEvents::Fire_MouseLeave, AnimLibU::_IAnimationEvents::MouseLeave,
	///       Raise_MouseEnter, Raise_MouseHover, Raise_MouseMove, AnimLibU::ExtendedMouseButtonConstants
	/// \else
	///   \sa Proxy_IAnimationEvents::Fire_MouseLeave, AnimLibA::_IAnimationEvents::MouseLeave,
	///       Raise_MouseEnter, Raise_MouseHover, Raise_MouseMove, AnimLibA::ExtendedMouseButtonConstants
	/// \endif
	inline HRESULT Raise_MouseLeave(SHORT button, SHORT shift, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y);
	/// \brief <em>Raises the \c MouseMove event</em>
	///
	/// \param[in] button The pressed mouse buttons. Any combination of the values defined by VB's
	///            \c MouseButtonConstants enumeration or the \c ExtendedMouseButtonConstants enumeration
	///            is valid.
	/// \param[in] shift The pressed modifier keys (Shift, Ctrl, Alt). Any combination of the values
	///            defined by VB's \c ShiftConstants enumeration is valid.
	/// \param[in] x The x-coordinate (in pixels) of the mouse cursor's position relative to the control's
	///            upper-left corner.
	/// \param[in] y The y-coordinate (in pixels) of the mouse cursor's position relative to the control's
	///            upper-left corner.
	///
	/// \return An \c HRESULT error code.
	///
	/// \remarks This event may be disabled.
	///
	/// \if UNICODE
	///   \sa Proxy_IAnimationEvents::Fire_MouseMove, AnimLibU::_IAnimationEvents::MouseMove,
	///       Raise_MouseEnter, Raise_MouseLeave, Raise_MouseDown, Raise_MouseUp,
	///       AnimLibU::ExtendedMouseButtonConstants
	/// \else
	///   \sa Proxy_IAnimationEvents::Fire_MouseMove, AnimLibA::_IAnimationEvents::MouseMove,
	///       Raise_MouseEnter, Raise_MouseLeave, Raise_MouseDown, Raise_MouseUp,
	///       AnimLibA::ExtendedMouseButtonConstants
	/// \endif
	// \if UNICODE
	//   \sa Proxy_IAnimationEvents::Fire_MouseMove, AnimLibU::_IAnimationEvents::MouseMove,
	//       Raise_MouseEnter, Raise_MouseLeave, Raise_MouseDown, Raise_MouseUp, Raise_MouseWheel,
	//       AnimLibU::ExtendedMouseButtonConstants
	// \else
	//   \sa Proxy_IAnimationEvents::Fire_MouseMove, AnimLibA::_IAnimationEvents::MouseMove,
	//       Raise_MouseEnter, Raise_MouseLeave, Raise_MouseDown, Raise_MouseUp, Raise_MouseWheel,
	//       AnimLibA::ExtendedMouseButtonConstants
	// \endif
	inline HRESULT Raise_MouseMove(SHORT button, SHORT shift, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y);
	/// \brief <em>Raises the \c MouseUp event</em>
	///
	/// \param[in] button The released mouse buttons. Any of the values defined by VB's
	///            \c MouseButtonConstants enumeration or the \c ExtendedMouseButtonConstants enumeration
	///            is valid.
	/// \param[in] shift The pressed modifier keys (Shift, Ctrl, Alt). Any combination of the values
	///            defined by VB's \c ShiftConstants enumeration is valid.
	/// \param[in] x The x-coordinate (in pixels) of the mouse cursor's position relative to the control's
	///            upper-left corner.
	/// \param[in] y The y-coordinate (in pixels) of the mouse cursor's position relative to the control's
	///            upper-left corner.
	///
	/// \return An \c HRESULT error code.
	///
	/// \remarks This event may be disabled.
	///
	/// \if UNICODE
	///   \sa Proxy_IAnimationEvents::Fire_MouseUp, AnimLibU::_IAnimationEvents::MouseUp, Raise_MouseDown,
	///       Raise_Click, Raise_MClick, Raise_RClick, Raise_XClick, AnimLibU::ExtendedMouseButtonConstants
	/// \else
	///   \sa Proxy_IAnimationEvents::Fire_MouseUp, AnimLibA::_IAnimationEvents::MouseUp, Raise_MouseDown,
	///       Raise_Click, Raise_MClick, Raise_RClick, Raise_XClick, AnimLibA::ExtendedMouseButtonConstants
	/// \endif
	inline HRESULT Raise_MouseUp(SHORT button, SHORT shift, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y);
	// \brief <em>Raises the \c MouseWheel event</em>
	//
	// \param[in] button The pressed mouse buttons. Any combination of the values defined by VB's
	//            \c MouseButtonConstants enumeration or the \c ExtendedMouseButtonConstants enumeration
	//            is valid.
	// \param[in] shift The pressed modifier keys (Shift, Ctrl, Alt). Any combination of the values
	//            defined by VB's \c ShiftConstants enumeration is valid.
	// \param[in] x The x-coordinate (in pixels) of the mouse cursor's position relative to the control's
	//            upper-left corner.
	// \param[in] y The y-coordinate (in pixels) of the mouse cursor's position relative to the control's
	//            upper-left corner.
	// \param[in] scrollAxis Specifies whether the user intents to scroll vertically or horizontally.
	//            Any of the values defined by the \c ScrollAxisConstants enumeration is valid.
	// \param[in] wheelDelta The distance the wheel has been rotated.
	//
	// \return An \c HRESULT error code.
	//
	// \remarks This event may be disabled.
	//
	// \if UNICODE
	//   \sa Proxy_IAnimationEvents::Fire_MouseWheel, AnimLibU::_IAnimationEvents::MouseWheel,
	//       Raise_MouseMove, AnimLibU::ExtendedMouseButtonConstants, AnimLibU::ScrollAxisConstants
	// \else
	//   \sa Proxy_IAnimationEvents::Fire_MouseWheel, AnimLibA::_IAnimationEvents::MouseWheel,
	//       Raise_MouseMove, AnimLibA::ExtendedMouseButtonConstants, AnimLibA::ScrollAxisConstants
	// \endif
	//inline HRESULT Raise_MouseWheel(SHORT button, SHORT shift, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y, ScrollAxisConstants scrollAxis, SHORT wheelDelta);
	/// \brief <em>Raises the \c OLEDragDrop event</em>
	///
	/// \param[in] pData The dropped data.
	/// \param[in,out] pEffect On entry, a bit field of the drop effects (defined by the \c DROPEFFECT
	///                enumeration) supported by the drag source. On return, the drop effect that the
	///                client finally executed.
	/// \param[in] keyState The pressed modifier keys (Shift, Ctrl, Alt) and mouse buttons. Any
	///            combination of the pressed button's and key's \c MK_* flags is valid.
	/// \param[in] mousePosition The mouse cursor's position (in pixels) relative to the screen's
	///            upper-left corner.
	///
	/// \return An \c HRESULT error code.
	///
	/// \if UNICODE
	///   \sa Proxy_IAnimationEvents::Fire_OLEDragDrop, AnimLibU::_IAnimationEvents::OLEDragDrop,
	///       Raise_OLEDragEnter, Raise_OLEDragMouseMove, Raise_OLEDragLeave, Raise_MouseUp,
	///       get_RegisterForOLEDragDrop, FinishOLEDragDrop,
	///       <a href="https://msdn.microsoft.com/en-us/library/ms693457.aspx">DROPEFFECT</a>
	/// \else
	///   \sa Proxy_IAnimationEvents::Fire_OLEDragDrop, AnimLibA::_IAnimationEvents::OLEDragDrop,
	///       Raise_OLEDragEnter, Raise_OLEDragMouseMove, Raise_OLEDragLeave, Raise_MouseUp,
	///       get_RegisterForOLEDragDrop, FinishOLEDragDrop,
	///       <a href="https://msdn.microsoft.com/en-us/library/ms693457.aspx">DROPEFFECT</a>
	/// \endif
	inline HRESULT Raise_OLEDragDrop(IDataObject* pData, DWORD* pEffect, DWORD keyState, POINTL mousePosition);
	/// \brief <em>Raises the \c OLEDragEnter event</em>
	///
	/// \param[in] pData The dragged data. If \c NULL, the cached data object is used. We use this when
	///            we call this method from other places than \c DragEnter.
	/// \param[in,out] pEffect On entry, a bit field of the drop effects (defined by the \c DROPEFFECT
	///                enumeration) supported by the drag source. On return, the drop effect that the
	///                client wants to be used on drop.
	/// \param[in] keyState The pressed modifier keys (Shift, Ctrl, Alt) and mouse buttons. Any
	///            combination of the pressed button's and key's \c MK_* flags is valid.
	/// \param[in] mousePosition The mouse cursor's position (in pixels) relative to the screen's
	///            upper-left corner.
	///
	/// \return An \c HRESULT error code.
	///
	/// \if UNICODE
	///   \sa Proxy_IAnimationEvents::Fire_OLEDragEnter, AnimLibU::_IAnimationEvents::OLEDragEnter,
	///       Raise_OLEDragMouseMove, Raise_OLEDragLeave, Raise_OLEDragDrop, Raise_MouseEnter,
	///       <a href="https://msdn.microsoft.com/en-us/library/ms693457.aspx">DROPEFFECT</a>
	/// \else
	///   \sa Proxy_IAnimationEvents::Fire_OLEDragEnter, AnimLibA::_IAnimationEvents::OLEDragEnter,
	///       Raise_OLEDragMouseMove, Raise_OLEDragLeave, Raise_OLEDragDrop, Raise_MouseEnter,
	///       <a href="https://msdn.microsoft.com/en-us/library/ms693457.aspx">DROPEFFECT</a>
	/// \endif
	inline HRESULT Raise_OLEDragEnter(IDataObject* pData, DWORD* pEffect, DWORD keyState, POINTL mousePosition);
	/// \brief <em>Raises the \c OLEDragLeave event</em>
	///
	/// \return An \c HRESULT error code.
	///
	/// \if UNICODE
	///   \sa Proxy_IAnimationEvents::Fire_OLEDragLeave, AnimLibU::_IAnimationEvents::OLEDragLeave,
	///       Raise_OLEDragEnter, Raise_OLEDragMouseMove, Raise_OLEDragDrop, Raise_MouseLeave
	/// \else
	///   \sa Proxy_IAnimationEvents::Fire_OLEDragLeave, AnimLibA::_IAnimationEvents::OLEDragLeave,
	///       Raise_OLEDragEnter, Raise_OLEDragMouseMove, Raise_OLEDragDrop, Raise_MouseLeave
	/// \endif
	inline HRESULT Raise_OLEDragLeave(void);
	/// \brief <em>Raises the \c OLEDragMouseMove event</em>
	///
	/// \param[in,out] pEffect On entry, a bit field of the drop effects (defined by the \c DROPEFFECT
	///                enumeration) supported by the drag source. On return, the drop effect that the
	///                client wants to be used on drop.
	/// \param[in] keyState The pressed modifier keys (Shift, Ctrl, Alt) and mouse buttons. Any
	///            combination of the pressed button's and key's \c MK_* flags is valid.
	/// \param[in] mousePosition The mouse cursor's position (in pixels) relative to the screen's
	///            upper-left corner.
	///
	/// \return An \c HRESULT error code.
	///
	/// \if UNICODE
	///   \sa Proxy_IAnimationEvents::Fire_OLEDragMouseMove, AnimLibU::_IAnimationEvents::OLEDragMouseMove,
	///       Raise_OLEDragEnter, Raise_OLEDragLeave, Raise_OLEDragDrop, Raise_MouseMove,
	///       <a href="https://msdn.microsoft.com/en-us/library/ms693457.aspx">DROPEFFECT</a>
	/// \else
	///   \sa Proxy_IAnimationEvents::Fire_OLEDragMouseMove, AnimLibA::_IAnimationEvents::OLEDragMouseMove,
	///       Raise_OLEDragEnter, Raise_OLEDragLeave, Raise_OLEDragDrop, Raise_MouseMove,
	///       <a href="https://msdn.microsoft.com/en-us/library/ms693457.aspx">DROPEFFECT</a>
	/// \endif
	inline HRESULT Raise_OLEDragMouseMove(DWORD* pEffect, DWORD keyState, POINTL mousePosition);
	/// \brief <em>Raises the \c RClick event</em>
	///
	/// \param[in] button The mouse buttons that were pressed during the click. This should always be
	///            \c vbRightButton (defined by VB's \c MouseButtonConstants enumeration).
	/// \param[in] shift The modifier keys (Shift, Ctrl, Alt) that were pressed during the click. Any
	///            combination of the values defined by VB's \c ShiftConstants enumeration is valid.
	/// \param[in] x The x-coordinate (in pixels) of the click's position relative to the control's
	///            upper-left corner.
	/// \param[in] y The y-coordinate (in pixels) of the click's position relative to the control's
	///            upper-left corner.
	///
	/// \return An \c HRESULT error code.
	///
	/// \remarks This event may be disabled.
	///
	/// \if UNICODE
	///   \sa Proxy_IAnimationEvents::Fire_RClick, AnimLibU::_IAnimationEvents::RClick, Raise_ContextMenu,
	///       Raise_RDblClick, Raise_Click, Raise_MClick, Raise_XClick
	/// \else
	///   \sa Proxy_IAnimationEvents::Fire_RClick, AnimLibA::_IAnimationEvents::RClick, Raise_ContextMenu,
	///       Raise_RDblClick, Raise_Click, Raise_MClick, Raise_XClick
	/// \endif
	inline HRESULT Raise_RClick(SHORT button, SHORT shift, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y);
	/// \brief <em>Raises the \c RDblClick event</em>
	///
	/// \param[in] button The mouse buttons that were pressed during the double-click. This should
	///            always be \c vbRightButton (defined by VB's \c MouseButtonConstants enumeration).
	/// \param[in] shift The modifier keys (Shift, Ctrl, Alt) that were pressed during the double-click.
	///            Any combination of the values defined by VB's \c ShiftConstants enumeration is valid.
	/// \param[in] x The x-coordinate (in pixels) of the double-click's position relative to the control's
	///            upper-left corner.
	/// \param[in] y The y-coordinate (in pixels) of the double-click's position relative to the control's
	///            upper-left corner.
	///
	/// \return An \c HRESULT error code.
	///
	/// \remarks This event may be disabled.
	///
	/// \if UNICODE
	///   \sa Proxy_IAnimationEvents::Fire_RDblClick, AnimLibU::_IAnimationEvents::RDblClick, Raise_RClick,
	///       Raise_DblClick, Raise_MDblClick, Raise_XDblClick
	/// \else
	///   \sa Proxy_IAnimationEvents::Fire_RDblClick, AnimLibA::_IAnimationEvents::RDblClick, Raise_RClick,
	///       Raise_DblClick, Raise_MDblClick, Raise_XDblClick
	/// \endif
	inline HRESULT Raise_RDblClick(SHORT button, SHORT shift, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y);
	/// \brief <em>Raises the \c RecreatedControlWindow event</em>
	///
	/// \param[in] hWnd The control's window handle.
	///
	/// \return An \c HRESULT error code.
	///
	/// \if UNICODE
	///   \sa Proxy_IAnimationEvents::Fire_RecreatedControlWindow,
	///       AnimLibU::_IAnimationEvents::RecreatedControlWindow, Raise_DestroyedControlWindow,
	///       get_hWnd
	/// \else
	///   \sa Proxy_IAnimationEvents::Fire_RecreatedControlWindow,
	///       AnimLibA::_IAnimationEvents::RecreatedControlWindow, Raise_DestroyedControlWindow,
	///       get_hWnd
	/// \endif
	inline HRESULT Raise_RecreatedControlWindow(LONG hWnd);
	/// \brief <em>Raises the \c ResizedControlWindow event</em>
	///
	/// \return An \c HRESULT error code.
	///
	/// \if UNICODE
	///   \sa Proxy_IAnimationEvents::Fire_ResizedControlWindow,
	///       AnimLibU::_IAnimationEvents::ResizedControlWindow
	/// \else
	///   \sa Proxy_IAnimationEvents::Fire_ResizedControlWindow,
	///       AnimLibA::_IAnimationEvents::ResizedControlWindow
	/// \endif
	inline HRESULT Raise_ResizedControlWindow(void);
	/// \brief <em>Raises the \c StartedReplay event</em>
	///
	/// \return An \c HRESULT error code.
	///
	/// \if UNICODE
	///   \sa Proxy_IAnimationEvents::Fire_StartedReplay, AnimLibU::_IAnimationEvents::StartedReplay,
	///       Raise_StoppedReplay, StartReplay, get_AutoStartReplay, get_IsPlaying
	/// \else
	///   \sa Proxy_IAnimationEvents::Fire_StartedReplay, AnimLibA::_IAnimationEvents::StartedReplay,
	///       Raise_StoppedReplay, StartReplay, get_AutoStartReplay, get_IsPlaying
	/// \endif
	inline HRESULT Raise_StartedReplay(void);
	/// \brief <em>Raises the \c StoppedReplay event</em>
	///
	/// \return An \c HRESULT error code.
	///
	/// \if UNICODE
	///   \sa Proxy_IAnimationEvents::Fire_StoppedReplay, AnimLibU::_IAnimationEvents::StoppedReplay,
	///       Raise_StartedReplay, StopReplay, get_IsPlaying
	/// \else
	///   \sa Proxy_IAnimationEvents::Fire_StoppedReplay, AnimLibA::_IAnimationEvents::StoppedReplay,
	///       Raise_StartedReplay, StopReplay, get_IsPlaying
	/// \endif
	inline HRESULT Raise_StoppedReplay(void);
	/// \brief <em>Raises the \c XClick event</em>
	///
	/// \param[in] button The mouse buttons that were pressed during the click. This should always be
	///            a constant defined by the \c ExtendedMouseButtonConstants enumeration.
	/// \param[in] shift The modifier keys (Shift, Ctrl, Alt) that were pressed during the click. Any
	///            combination of the values defined by VB's \c ShiftConstants enumeration is valid.
	/// \param[in] x The x-coordinate (in pixels) of the click's position relative to the control's
	///            upper-left corner.
	/// \param[in] y The y-coordinate (in pixels) of the click's position relative to the control's
	///            upper-left corner.
	///
	/// \return An \c HRESULT error code.
	///
	/// \remarks This event may be disabled.
	///
	/// \if UNICODE
	///   \sa Proxy_IAnimationEvents::Fire_XClick, AnimLibU::_IAnimationEvents::XClick,
	///       Raise_XDblClick, Raise_Click, Raise_MClick, Raise_RClick,
	///       AnimLibU::ExtendedMouseButtonConstants
	/// \else
	///   \sa Proxy_IAnimationEvents::Fire_XClick, AnimLibA::_IAnimationEvents::XClick,
	///       Raise_XDblClick, Raise_Click, Raise_MClick, Raise_RClick,
	///       AnimLibA::ExtendedMouseButtonConstants
	/// \endif
	inline HRESULT Raise_XClick(SHORT button, SHORT shift, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y);
	/// \brief <em>Raises the \c XDblClick event</em>
	///
	/// \param[in] button The mouse buttons that were pressed during the double-click. This should
	///            always be a constant defined by the \c ExtendedMouseButtonConstants enumeration.
	/// \param[in] shift The modifier keys (Shift, Ctrl, Alt) that were pressed during the double-click.
	///            Any combination of the values defined by VB's \c ShiftConstants enumeration is valid.
	/// \param[in] x The x-coordinate (in pixels) of the double-click's position relative to the control's
	///            upper-left corner.
	/// \param[in] y The y-coordinate (in pixels) of the double-click's position relative to the control's
	///            upper-left corner.
	///
	/// \return An \c HRESULT error code.
	///
	/// \remarks This event may be disabled.
	///
	/// \if UNICODE
	///   \sa Proxy_IAnimationEvents::Fire_XDblClick, AnimLibU::_IAnimationEvents::XDblClick,
	///       Raise_XClick, Raise_DblClick, Raise_MDblClick, Raise_RDblClick,
	///       AnimLibU::ExtendedMouseButtonConstants
	/// \else
	///   \sa Proxy_IAnimationEvents::Fire_XDblClick, AnimLibA::_IAnimationEvents::XDblClick,
	///       Raise_XClick, Raise_DblClick, Raise_MDblClick, Raise_RDblClick,
	///       AnimLibA::ExtendedMouseButtonConstants
	/// \endif
	inline HRESULT Raise_XDblClick(SHORT button, SHORT shift, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y);
	//@}
	//////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////
	/// \name Implementation of IOleObject
	///
	//@{
	/// \brief <em>Implementation of \c IOleObject::DoVerb</em>
	///
	/// Will be called if one of the control's registered actions (verbs) shall be executed; e. g.
	/// executing the "About" verb will display the About dialog.
	///
	/// \param[in] verbID The requested verb's ID.
	/// \param[in] pMessage A \c MSG structure describing the event (such as a double-click) that
	///            invoked the verb.
	/// \param[in] pActiveSite The \c IOleClientSite implementation of the control's active client site
	///            where the event occurred that invoked the verb.
	/// \param[in] reserved Reserved; must be zero.
	/// \param[in] hWndParent The handle of the document window containing the control.
	/// \param[in] pBoundingRectangle A \c RECT structure containing the coordinates and size in pixels
	///            of the control within the window specified by \c hWndParent.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa EnumVerbs,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms694508.aspx">IOleObject::DoVerb</a>
	virtual HRESULT STDMETHODCALLTYPE DoVerb(LONG verbID, LPMSG pMessage, IOleClientSite* pActiveSite, LONG reserved, HWND hWndParent, LPCRECT pBoundingRectangle);
	/// \brief <em>Implementation of \c IOleObject::EnumVerbs</em>
	///
	/// Will be called if the control's container requests the control's registered actions (verbs); e. g.
	/// we provide a verb "About" that will display the About dialog on execution.
	///
	/// \param[out] ppEnumerator Receives the \c IEnumOLEVERB implementation of the verbs' enumerator.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa DoVerb,
	///     <a href="https://msdn.microsoft.com/en-us/library/ms692781.aspx">IOleObject::EnumVerbs</a>
	virtual HRESULT STDMETHODCALLTYPE EnumVerbs(IEnumOLEVERB** ppEnumerator);
	//@}
	//////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////
	/// \name Implementation of IOleControl
	///
	//@{
	/// \brief <em>Implementation of \c IOleControl::GetControlInfo</em>
	///
	/// Will be called if the container requests details about the control's keyboard mnemonics and keyboard
	/// behavior.
	///
	/// \param[in, out] pControlInfo The requested details.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa <a href="https://msdn.microsoft.com/en-us/library/ms693730.aspx">IOleControl::GetControlInfo</a>
	virtual HRESULT STDMETHODCALLTYPE GetControlInfo(LPCONTROLINFO pControlInfo);
	//@}
	//////////////////////////////////////////////////////////////////////

	/// \brief <em>Executes the About verb</em>
	///
	/// Will be called if the control's registered actions (verbs) "About" shall be executed. We'll
	/// display the About dialog.
	///
	/// \param[in] hWndParent The window to use as parent for any user interface.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa DoVerb, About
	HRESULT DoVerbAbout(HWND hWndParent);

	//////////////////////////////////////////////////////////////////////
	/// \name MFC clones
	///
	//@{
	/// \brief <em>A rewrite of MFC's \c COleControl::RecreateControlWindow</em>
	///
	/// Destroys and re-creates the control window.
	///
	/// \remarks This rewrite probably isn't complete.
	///
	/// \sa <a href="https://msdn.microsoft.com/en-us/library/5tx8h2fd.aspx">COleControl::RecreateControlWindow</a>
	void RecreateControlWindow(void);
	//@}
	//////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////
	/// \name Control window configuration
	///
	//@{
	/// \brief <em>Calculates the extended window style bits</em>
	///
	/// Calculates the extended window style bits that the control must have set to match the current
	/// property settings.
	///
	/// \return A bit field of \c WS_EX_* constants specifying the required extended window styles.
	///
	/// \sa GetStyleBits, SendConfigurationMessages, Create
	DWORD GetExStyleBits(void);
	/// \brief <em>Calculates the window style bits</em>
	///
	/// Calculates the window style bits that the control must have set to match the current property
	/// settings.
	///
	/// \return A bit field of \c WS_* and \c ACS_* constants specifying the required window styles.
	///
	/// \sa GetExStyleBits, SendConfigurationMessages, Create
	DWORD GetStyleBits(void);
	/// \brief <em>Configures the control by sending messages</em>
	///
	/// Sends \c WM_* and \c ACM_* messages to the control window to make it match the current property
	/// settings. Will be called out of \c Raise_RecreatedControlWindow.
	///
	/// \sa GetExStyleBits, GetStyleBits, Raise_RecreatedControlWindow
	void SendConfigurationMessages(void);
	//@}
	//////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////
	/// \name Value translation
	///
	//@{
	/// \brief <em>Translates a \c MousePointerConstants type mouse cursor into a \c HCURSOR type mouse cursor</em>
	///
	/// \param[in] mousePointer The \c MousePointerConstants type mouse cursor to translate.
	///
	/// \return The translated \c HCURSOR type mouse cursor.
	///
	/// \if UNICODE
	///   \sa AnimLibU::MousePointerConstants, OnSetCursor, put_MousePointer
	/// \else
	///   \sa AnimLibA::MousePointerConstants, OnSetCursor, put_MousePointer
	/// \endif
	HCURSOR MousePointerConst2hCursor(MousePointerConstants mousePointer);
	//@}
	//////////////////////////////////////////////////////////////////////

	/// \brief <em>Retrieves whether we're in design mode or in user mode</em>
	///
	/// \return \c TRUE if the control is in design mode (i. e. is placed on a window which is edited
	///         by a form editor); \c FALSE if the control is in user mode (i. e. is placed on a window
	///         getting used by an end-user).
	BOOL IsInDesignMode(void);


	/// \brief <em>Holds a control instance's properties' settings</em>
	typedef struct Properties
	{
		/// \brief <em>Holds a picture property's settings</em>
		typedef struct PictureProperty
		{
			/// \brief <em>Holds whether we're listening for events fired by the picture object</em>
			///
			/// If greater than 0, we're advised to the \c IPictureDisp object identified by \c pPictureDisp.
			/// I. e. we will be notified if a property of the picture object changes. If 0, we won't receive any
			/// events fired by the \c IPictureDisp object.
			///
			/// \sa pPictureDisp, pPropertyNotifySink
			int watching;
			/// \brief <em>A pointer to the picture object's implementation of \c IPictureDisp</em>
			IPictureDisp* pPictureDisp;
			/// \brief <em>Receives notifications on changes to this property object's settings</em>
			///
			/// \sa InitializePropertyWatcher, PropertyNotifySinkImpl
			CComObject< PropertyNotifySinkImpl<Animation> >* pPropertyNotifySink;

			PictureProperty()
			{
				watching = 0;
				pPictureDisp = NULL;
				pPropertyNotifySink = NULL;
			}

			~PictureProperty()
			{
				Release();
			}

			PictureProperty& operator =(const PictureProperty& source)
			{
				Release();

				pPictureDisp = source.pPictureDisp;
				if(pPictureDisp) {
					pPictureDisp->AddRef();
				}
				InitializePropertyWatcher(source.pPropertyNotifySink->properties.pObjectToNotify, source.pPropertyNotifySink->properties.propertyToWatch);
				if(source.watching > 0) {
					StartWatching();
				}
				return *this;
			}

			/// \brief <em>Initializes an object that will watch this property for changes</em>
			///
			/// \param[in] pObjectToNotify The object to notify on changes.
			/// \param[in] propertyToWatch The property to watch for changes.
			///
			/// \return An \c HRESULT error code.
			///
			/// \sa StartWatching, StopWatching
			HRESULT InitializePropertyWatcher(Animation* pObjectToNotify, DISPID propertyToWatch)
			{
				CComObject< PropertyNotifySinkImpl<Animation> >::CreateInstance(&pPropertyNotifySink);
				ATLASSUME(pPropertyNotifySink);
				pPropertyNotifySink->AddRef();
				return pPropertyNotifySink->Initialize(pObjectToNotify, propertyToWatch);
			}

			/// \brief <em>Prepares the object for destruction</em>
			void Release(void)
			{
				if(pPropertyNotifySink) {
					StopWatching();
					pPropertyNotifySink->Release();
					pPropertyNotifySink = NULL;
				}
				if(pPictureDisp) {
					pPictureDisp->Release();
					pPictureDisp = NULL;
				}
				ATLASSERT(watching == 0);
			}

			/// \brief <em>Starts watching the property object for changes</em>
			///
			/// \return An \c HRESULT error code.
			///
			/// \sa StopWatching, InitializePropertyWatcher
			HRESULT StartWatching(void)
			{
				if(pPictureDisp) {
					ATLASSUME(pPropertyNotifySink);
					HRESULT hr = pPropertyNotifySink->StartWatching(pPictureDisp);
					ATLASSERT(SUCCEEDED(hr));
					if(SUCCEEDED(hr)) {
						++watching;
					}
					return hr;
				}
				return E_FAIL;
			}

			/// \brief <em>Stops watching the property object for changes</em>
			///
			/// \return An \c HRESULT error code.
			///
			/// \sa StartWatching, InitializePropertyWatcher
			HRESULT StopWatching(void)
			{
				if(watching > 0) {
					ATLASSUME(pPropertyNotifySink);
					HRESULT hr = pPropertyNotifySink->StopWatching(pPictureDisp);
					ATLASSERT(SUCCEEDED(hr));
					if(SUCCEEDED(hr)) {
						--watching;
					}
					return hr;
				}
				return E_FAIL;
			}
		} PictureProperty;

		/// \brief <em>Holds the \c AnimationBackStyle property's setting</em>
		///
		/// \sa get_AnimationBackStyle, put_AnimationBackStyle
		AnimationBackStyleConstants animationBackStyle;
		/// \brief <em>Holds the \c Appearance property's setting</em>
		///
		/// \sa get_Appearance, put_Appearance
		AppearanceConstants appearance;
		/// \brief <em>Holds the \c AutoStartReplay property's setting</em>
		///
		/// \sa get_AutoStartReplay, put_AutoStartReplay
		UINT autoStartReplay : 1;
		/// \brief <em>Holds the \c BackColor property's setting</em>
		///
		/// \sa get_BackColor, put_BackColor
		OLE_COLOR backColor;
		/// \brief <em>Holds the \c BorderStyle property's setting</em>
		///
		/// \sa get_BorderStyle, put_BorderStyle
		BorderStyleConstants borderStyle;
		/// \brief <em>Holds the \c CenterAnimation property's setting</em>
		///
		/// \sa get_CenterAnimation, put_CenterAnimation
		UINT centerAnimation : 1;
		/// \brief <em>Holds the \c DisabledEvents property's setting</em>
		///
		/// \sa get_DisabledEvents, put_DisabledEvents
		DisabledEventsConstants disabledEvents;
		/// \brief <em>Holds the \c DontRedraw property's setting</em>
		///
		/// \sa get_DontRedraw, put_DontRedraw
		UINT dontRedraw : 1;
		/// \brief <em>Holds the \c Enabled property's setting</em>
		///
		/// \sa get_Enabled, put_Enabled
		UINT enabled : 1;
		/// \brief <em>Holds the \c HoverTime property's setting</em>
		///
		/// \sa get_HoverTime, put_HoverTime
		long hoverTime;
		/// \brief <em>Holds the \c MouseIcon property's settings</em>
		///
		/// \sa get_MouseIcon, put_MouseIcon, putref_MouseIcon
		PictureProperty mouseIcon;
		/// \brief <em>Holds the \c MousePointer property's setting</em>
		///
		/// \sa get_MousePointer, put_MousePointer
		MousePointerConstants mousePointer;
		/// \brief <em>Holds the \c RegisterForOLEDragDrop property's setting</em>
		///
		/// \sa get_RegisterForOLEDragDrop, put_RegisterForOLEDragDrop
		UINT registerForOLEDragDrop : 1;
		/// \brief <em>Holds the \c SupportOLEDragImages property's setting</em>
		///
		/// \sa get_SupportOLEDragImages, put_SupportOLEDragImages
		UINT supportOLEDragImages : 1;

		Properties()
		{
			ResetToDefaults();
		}

		~Properties()
		{
			Release();
		}

		/// \brief <em>Prepares the object for destruction</em>
		void Release(void)
		{
			mouseIcon.Release();
		}

		/// \brief <em>Resets all properties to their defaults</em>
		void ResetToDefaults(void)
		{
			animationBackStyle = absUseBackColor;
			appearance = a2D;
			autoStartReplay = TRUE;
			backColor = 0x80000000 | COLOR_BTNFACE;
			borderStyle = bsNone;
			centerAnimation = TRUE;
			disabledEvents = static_cast<DisabledEventsConstants>(deMouseEvents | deClickEvents);
			dontRedraw = FALSE;
			enabled = TRUE;
			hoverTime = -1;
			mousePointer = mpDefault;
			registerForOLEDragDrop = FALSE;
			supportOLEDragImages = TRUE;
		}
	} Properties;
	/// \brief <em>Holds the control's properties' settings</em>
	Properties properties;

	/// \brief <em>Holds the control's flags</em>
	struct Flags
	{
		/// \brief <em>Specifies the kind of animation we're displaying</em>
		///
		/// \sa StartReplay
		enum AnimationType
		{
			/// \brief We're not displaying any animation
			///
			/// \sa OnOpen
			atNone,
			/// \brief We're displaying an AVI animation
			atAVI,
			/// \brief We're displaying a GIF animation
			atGIF
		} animationType;
		/// \brief <em>If \c TRUE, we're currently playing an AVI animation</em>
		///
		/// \sa OnReflectedStart, OnReflectedStop, get_IsPlaying
		UINT isPlayingAVI : 1;
		/// \brief <em>If \c TRUE, we're using themes</em>
		///
		/// \sa OnThemeChanged
		UINT usingThemes : 1;

		Flags()
		{
			animationType = atNone;
			usingThemes = FALSE;
		}
	} flags;


	/// \brief <em>Holds mouse status variables</em>
	typedef struct MouseStatus
	{
	protected:
		/// \brief <em>Holds all mouse buttons that may cause a click event in the immediate future</em>
		///
		/// A bit field of \c SHORT values representing those mouse buttons that are currently pressed and
		/// may cause a click event in the immediate future.
		///
		/// \sa StoreClickCandidate, IsClickCandidate, RemoveClickCandidate, Raise_Click, Raise_MClick,
		///     Raise_RClick, Raise_XClick
		SHORT clickCandidates;
		/// \brief <em>Holds the mouse button that may cause a double-click on the next \c WM_*BUTTONDOWN message</em>
		///
		/// \sa StoreDoubleClickCandidate, IsDoubleClickCandidate, RemoveAllDoubleClickCandidates,
		///     Raise_MouseDown, Raise_MouseUp
		SHORT doubleClickCandidate;
		/// \brief <em>Holds the timestamp until which the next \c WM_*BUTTONDOWN message has to be received in order to trigger a double-click</em>
		///
		/// \sa StoreDoubleClickCandidate, IsDoubleClickCandidate, RemoveAllDoubleClickCandidates,
		///     Raise_MouseDown, Raise_MouseUp
		LONG doubleClickTimeOut;
		/// \brief <em>Holds the position of the click message that has been stored as a candidate for a double-click</em>
		///
		/// \sa StoreDoubleClickCandidate, IsDoubleClickCandidate, RemoveAllDoubleClickCandidates,
		///     Raise_MouseDown, Raise_MouseUp
		POINT clickPosition;

	public:
		/// \brief <em>If \c TRUE, the \c MouseEnter event already was raised</em>
		///
		/// \sa Raise_MouseEnter
		UINT enteredControl : 1;
		/// \brief <em>If \c TRUE, the \c MouseHover event already was raised</em>
		///
		/// \attention This member is not reliable with \c deMouseEvents being set.
		///
		/// \sa Raise_MouseHover
		UINT hoveredControl : 1;
		/// \brief <em>Holds the mouse cursor's last position</em>
		///
		/// \attention This member is not reliable with \c deMouseEvents being set.
		POINT lastPosition;

		MouseStatus()
		{
			clickCandidates = 0;
			enteredControl = FALSE;
			hoveredControl = FALSE;
			doubleClickCandidate = 0;
			doubleClickTimeOut = 0;
		}

		/// \brief <em>Changes flags to indicate the \c MouseEnter event was just raised</em>
		///
		/// \sa enteredControl, HoverControl, LeaveControl
		void EnterControl(void)
		{
			RemoveAllClickCandidates();
			enteredControl = TRUE;
		}

		/// \brief <em>Changes flags to indicate the \c MouseHover event was just raised</em>
		///
		/// \sa enteredControl, hoveredControl, EnterControl, LeaveControl
		void HoverControl(void)
		{
			enteredControl = TRUE;
			hoveredControl = TRUE;
		}

		/// \brief <em>Changes flags to indicate the \c MouseLeave event was just raised</em>
		///
		/// \sa enteredControl, hoveredControl, EnterControl
		void LeaveControl(void)
		{
			enteredControl = FALSE;
			hoveredControl = FALSE;
		}

		/// \brief <em>Stores a mouse button as click candidate</em>
		///
		/// param[in] button The mouse button to store.
		///
		/// \sa clickCandidates, IsClickCandidate, RemoveClickCandidate
		void StoreClickCandidate(SHORT button)
		{
			// avoid combined click events
			if(clickCandidates == 0) {
				clickCandidates |= button;
			}
		}

		/// \brief <em>Stores a mouse button as double-click candidate</em>
		///
		/// param[in] button The mouse button to store.
		///
		/// \sa doubleClickCandidate, IsDoubleClickCandidate, RemoveAllDoubleClickCandidates
		void StoreDoubleClickCandidate(SHORT button)
		{
			doubleClickCandidate = button;
			doubleClickTimeOut = GetMessageTime() + GetDoubleClickTime();
			DWORD position = GetMessagePos();
			clickPosition.x = GET_X_LPARAM(position);
			clickPosition.y = GET_Y_LPARAM(position);
		}

		/// \brief <em>Retrieves whether a mouse button is a click candidate</em>
		///
		/// \param[in] button The mouse button to check.
		///
		/// \return \c TRUE if the button is stored as a click candidate; otherwise \c FALSE.
		///
		/// \attention This member is not reliable with \c deMouseEvents being set.
		///
		/// \sa clickCandidates, StoreClickCandidate, RemoveClickCandidate
		BOOL IsClickCandidate(SHORT button)
		{
			return (clickCandidates & button);
		}

		/// \brief <em>Retrieves whether a mouse button is a double-click candidate</em>
		///
		/// \param[in] button The mouse button to check.
		///
		/// \return \c TRUE if the button is stored as a double-click candidate and the current message also
		///         matches the other double-click conditions; otherwise \c FALSE.
		///
		/// \sa doubleClickCandidate, StoreDoubleClickCandidate, RemoveAllDoubleClickCandidates
		BOOL IsDoubleClickCandidate(SHORT button)
		{
			if(IsClickCandidate(button) && doubleClickCandidate == button && GetMessageTime() <= doubleClickTimeOut) {
				DWORD position = GetMessagePos();
				if(abs(GET_X_LPARAM(position) - clickPosition.x) < (GetSystemMetrics(SM_CXDOUBLECLK) >> 1) && abs(GET_Y_LPARAM(position) - clickPosition.y) < (GetSystemMetrics(SM_CYDOUBLECLK) >> 1)) {
					return TRUE;
				}
			}
			return FALSE;
		}

		/// \brief <em>Removes a mouse button from the list of click candidates</em>
		///
		/// \param[in] button The mouse button to remove.
		///
		/// \sa clickCandidates, RemoveAllClickCandidates, StoreClickCandidate, IsClickCandidate
		void RemoveClickCandidate(SHORT button)
		{
			clickCandidates &= ~button;
		}

		/// \brief <em>Clears the list of click candidates</em>
		///
		/// \sa clickCandidates, RemoveClickCandidate, StoreClickCandidate, IsClickCandidate
		void RemoveAllClickCandidates(void)
		{
			clickCandidates = 0;
		}

		/// \brief <em>Clears the list of click candidates</em>
		///
		/// \sa doubleClickCandidate, StoreDoubleClickCandidate, IsDoubleClickCandidate
		void RemoveAllDoubleClickCandidates(void)
		{
			doubleClickCandidate = 0;
			doubleClickTimeOut = 0;
		}
	} MouseStatus;

	/// \brief <em>Holds the control's mouse status</em>
	MouseStatus mouseStatus;

	/// \brief <em>Holds data and flags related to drag'n'drop</em>
	struct DragDropStatus
	{
		//////////////////////////////////////////////////////////////////////
		/// \name OLE Drag'n'Drop
		///
		//@{
		/// \brief <em>The currently dragged data</em>
		CComPtr<IOLEDataObject> pActiveDataObject;
		/// \brief <em>Holds the mouse cursors last position (in screen coordinates)</em>
		POINTL lastMousePosition;
		/// \brief <em>The \c IDropTargetHelper object used for drag image support</em>
		///
		/// \sa put_SupportOLEDragImages,
		///     <a href="https://msdn.microsoft.com/en-us/library/ms646238.aspx">IDropTargetHelper</a>
		IDropTargetHelper* pDropTargetHelper;
		/// \brief <em>Holds the \c IDataObject to pass to \c IDropTargetHelper::Drop in \c FinishOLEDragDrop</em>
		///
		/// \sa FinishOLEDragDrop, Drop,
		///     <a href="https://msdn.microsoft.com/en-us/library/ms688421.aspx">IDataObject</a>,
		///     <a href="https://msdn.microsoft.com/en-us/library/bb762027.aspx">IDropTargetHelper::Drop</a>
		IDataObject* drop_pDataObject;
		/// \brief <em>Holds the mouse position to pass to \c IDropTargetHelper::Drop in \c FinishOLEDragDrop</em>
		///
		/// \sa FinishOLEDragDrop, Drop,
		///     <a href="https://msdn.microsoft.com/en-us/library/bb762027.aspx">IDropTargetHelper::Drop</a>
		POINT drop_mousePosition;
		/// \brief <em>Holds the drop effect to pass to \c IDropTargetHelper::Drop in \c FinishOLEDragDrop</em>
		///
		/// \sa FinishOLEDragDrop, Drop,
		///     <a href="https://msdn.microsoft.com/en-us/library/bb762027.aspx">IDropTargetHelper::Drop</a>
		DWORD drop_effect;
		//@}
		//////////////////////////////////////////////////////////////////////

		DragDropStatus()
		{
			pActiveDataObject = NULL;
			pDropTargetHelper = NULL;
			drop_pDataObject = NULL;
		}

		~DragDropStatus()
		{
			if(pDropTargetHelper) {
				pDropTargetHelper->Release();
			}
		}

		/// \brief <em>Resets all member variables to their defaults</em>
		void Reset(void)
		{
			if(this->pActiveDataObject) {
				this->pActiveDataObject = NULL;
			}
			drop_pDataObject = NULL;
		}

		/// \brief <em>Performs any tasks that must be done if \c IDropTarget::DragEnter is called</em>
		///
		/// \return An \c HRESULT error code.
		///
		/// \sa OLEDragLeaveOrDrop
		HRESULT OLEDragEnter(void)
		{
			return S_OK;
		}

		/// \brief <em>Performs any tasks that must be done if \c IDropTarget::DragLeave or \c IDropTarget::Drop is called</em>
		///
		/// \sa OLEDragEnter
		void OLEDragLeaveOrDrop(void)
		{
			//
		}
	} dragDropStatus;

	/// \brief <em>Holds IDs and intervals of timers that we use</em>
	///
	/// \sa OnTimer
	static struct Timers
	{
		/// \brief <em>The ID of the timer that is used to redraw the control window after recreation</em>
		static const UINT_PTR ID_REDRAW = 12;
		/// \brief <em>The ID of the timer that is used to draw the next frame of the GIF</em>
		static const UINT_PTR ID_DRAWGIFFRAME = 17;

		/// \brief <em>The interval of the timer that is used to redraw the control window after recreation</em>
		static const UINT INT_REDRAW = 10;
	} timers;

	/// \brief <em>The brush that the control's background is drawn with, if the control is themed and disabled</em>
	CBrush themedBackBrush;

	//////////////////////////////////////////////////////////////////////
	/// \name GIF support
	///
	//@{
	/// \brief <em>Loads a GIF image from a stream</em>
	///
	/// \param[in] pInputStream The input stream to load the GIF image from.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa GIFData, RenderGIFFrame,
	///     <a href="https://msdn.microsoft.com/en-us/library/aa380034.aspx">IStream</a>
	HRESULT LoadGIF(LPSTREAM pInputStream);
	/// \brief <em>Loads a GIF image from a file</em>
	///
	/// \overload
	///
	/// \param[in] pFile The GIF file to load.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa GIFData, RenderGIFFrame
	HRESULT LoadGIF(LPTSTR pFile);
	/// \brief <em>Loads a GIF image from a resource</em>
	///
	/// \overload
	///
	/// \param[in] hModule The handle of the module from which to load the GIF resource.
	/// \param[in] resourceID The ID of the resource to load.
	/// \param[in] pResourceTypeName The type name of the resource to load. Set it to an empty string if you
	///            want to load an AVI animation. Otherwise set it to the name of the type under which the
	///            animation is stored in the resource file.
	///
	/// \return An \c HRESULT error code.
	///
	/// \sa GIFData, RenderGIFFrame
	HRESULT LoadGIF(HMODULE hModule, int resourceID, LPTSTR pResourceTypeName);
	/// \brief <em>Removes or sets the GIFData::isPlaying flag</em>
	///
	/// Removes or sets the GIFData::isPlaying flag and raises the \c StartedReplay and \c StoppedReplay
	/// events accordingly.
	///
	/// \param[in] newState The flag's new state.
	///
	/// \return The flag's previous state.
	///
	/// \sa GIFData::isPlaying, LoadGIF, StartReplay, StopReplay, Raise_StartedReplay, Raise_StoppedReplay
	UINT SetIsPlayingGIFFlag(UINT newState);
	/// \brief <em>Updates the off-screen buffers, so that the specified frame is buffered</em>
	///
	/// Updates the off-screen buffers, so that the specified frame is buffered. If the specified frame is
	/// not the GIF animation's first frame, the preceding frames are rendered to the buffers before the
	/// specified frame is rendered.
	///
	/// \param[in] frameToInitializeWith The frame to buffer.
	///
	/// \sa RenderGIFFrame, GIFData::screenWithCurrentFrame, GIFData::screenWithoutCurrentFrame
	void InitializeScreenBuffersWithSpecifiedGIFFrame(int frameToInitializeWith);
	/// \brief <em>Renders the specified frame to the specified device context at the specified position</em>
	///
	/// \param[in] frameToRender The frame to render.
	/// \param[in] targetDC The device context into which to render the frame.
	/// \param[in] position The position (in pixels) at which to render the frame.
	///
	/// \sa RenderGIFFrameBackground, InitializeScreenBuffersWithSpecifiedGIFFrame
	void RenderGIFFrame(int frameToRender, CDC& targetDC, CPoint& position);
	/// \brief <em>Renders the background of the specified frame to the specified device context at the specified position</em>
	///
	/// \param[in] frameToRenderBackgroundFor The frame for which to render the background.
	/// \param[in] targetDC The device context into which to render the frame background.
	/// \param[in] position The position (in pixels) at which to render the frame background.
	/// \param[in] drawTransparent If \c TRUE, the control's background is used as the frame's background;
	///            otherwise the animation's background is used.
	///
	/// \sa RenderGIFFrame, InitializeScreenBuffersWithSpecifiedGIFFrame
	void RenderGIFFrameBackground(int frameToRenderBackgroundFor, CDC& targetDC, CPoint& position, BOOL drawTransparent);

	/// \brief <em>Holds a 32 bit color value</em>
	///
	/// Holds a color value. Its size is 4 bytes instead of 3, because GDI works with aligned color tables.
	///
	/// \sa Frame::pLocalColorTable, GIFData::pGlobalColorTable
	typedef struct Color
	{
		// \brief <em>The color's blue fraction</em>
		BYTE b;
		// \brief <em>The color's green fraction</em>
		BYTE g;
		// \brief <em>The color's red fraction</em>
		BYTE r;
		// \brief <em>A filling byte used for alignment</em>
		BYTE x;
	} Color;

	/// \brief <em>Holds information about a GIF frame</em>
	///
	/// \sa GIFData, LoadGIF, RenderGIFFrame
	typedef struct Frame
	{
		/// \brief <em>The frame's bounding rectangle relative to the upper-left corner of the GIF's logical screen</em>
		///
		/// \sa GIFData::logicalScreenRectangle
		CRect boundingRectangle;
		/// \brief <em>If \c TRUE, the frame has a real private color table</em>
		///
		/// \sa localColorTableSize, pLocalColorTable, GIFData::hasGlobalColorTable
		UINT hasLocalColorTable : 1;
		/// \brief <em>The number of elements in the frame's private color table</em>
		///
		/// \remarks If the frame does not have a private color table, the GIF's global color table is used.
		///          To make implementation easier, the global color table will be copied to the private
		///          color table.
		///
		/// \sa pLocalColorTable, hasLocalColorTable, GIFData::globalColorTableSize
		int localColorTableSize;
		/// \brief <em>The frame's private color table</em>
		///
		/// \remarks If the frame does not have a private color table, the GIF's global color table is used.
		///          To make implementation easier, the global color table will be copied to the private
		///          color table.
		///
		/// \sa localColorTableSize, hasLocalColorTable, GIFData::pGlobalColorTable
		Color* pLocalColorTable;

		/// \brief <em>The width of a row of the frame in bytes</em>
		int bytesPerRow;
		/// \brief <em>The color codes of the frame's pixels</em>
		///
		/// The color codes of the frame's pixels. These codes are indices into the color table, which contains
		/// the decoded RGB colors.
		///
		/// \sa Color
		LPBYTE pPixels;

		/// \brief <em>If \c TRUE, one entry in the frame's private color table is used to mark transparent pixels</em>
		///
		/// \sa transparentColorIndex, pLocalColorTable
		UINT hasTransparentColor : 1;
		/// \brief <em>The entry in the frame's private color table, that is used to mark transparent pixels</em>
		///
		/// \sa hasTransparentColor, pLocalColorTable
		int transparentColorIndex;
		/// \brief <em>The number of milliseconds that the frame should be displayed</em>
		///
		/// If the GIF contains multiple frames, this member holds the number of milliseconds, that the frame
		/// shall be displayed before displaying the next one.
		///
		/// \remarks If \c waitForUserInput is set to \c TRUE, the control waits for some user interaction
		///          before it displays the next frame. In this case, the time specified by the \c delayTime
		///          member works as a timeout, i. e. after the specifed period of time has passed, the next
		///          frame is displayed even if no user interaction occured.
		///
		/// \sa waitForUserInput
		int delayTime;
		/// \brief <em>If \c TRUE, the control waits for user interaction before displaying the next frame</em>
		///
		/// If the GIF contains multiple frames, this member specifies whether the control waits for user
		/// interaction before it displays the next frame.
		///
		/// \remarks If \c waitForUserInput is set to \c TRUE, the control waits for some user interaction
		///          before it displays the next frame. In this case, the time specified by the \c delayTime
		///          member works as a timeout, i. e. after the specifed period of time has passed, the next
		///          frame is displayed even if no user interaction occured.
		///
		/// \sa delayTime
		UINT waitForUserInput : 1;
		/// \brief <em>Specifies whether and how the frame shall be erased before displaying the next frame</em>
		///
		/// \sa RenderGIFFrameBackground
		enum DisposalMethod
		{
			/// \brief No disposal method was specified for this frame
			dmNotSpecified = 0,
			/// \brief Simply leave the frame in place and don't remove
			dmLeaveInPlace = 1,
			/// \brief Fill the frame's bounding rectangle with the GIF's background color
			///
			/// \sa boundingRectangle, GIFData::backColorIndex
			dmRestoreToBackground = 2,
			/// \brief Fill the frame's bounding rectangle with what was there before the frame was drawn
			///
			/// \sa boundingRectangle
			dmRestoreToWhatWasThereBefore = 3
		} disposalMethod;

		Frame()
		{
			localColorTableSize = 0;
			pLocalColorTable = NULL;
			hasLocalColorTable = FALSE;

			pPixels = NULL;

			disposalMethod = dmNotSpecified;
			hasTransparentColor = FALSE;
			delayTime = 100;
			waitForUserInput = FALSE;
		}

		~Frame()
		{
			if(pPixels) {
				HeapFree(GetProcessHeap(), 0, pPixels);
			}
			if(pLocalColorTable) {
				HeapFree(GetProcessHeap(), 0, pLocalColorTable);
			}
		}

		/// \brief <em>Initializes the members and creates buffers for the color table and the pixel map</em>
		///
		/// \sa pLocalColorTable, pPixels
		void Initialize(void)
		{
			if(pPixels) {
				HeapFree(GetProcessHeap(), 0, pPixels);
				pPixels = NULL;
			}

			bytesPerRow = boundingRectangle.Width();
			// TODO: Try to avoid the memory allocation for each single frame.
			pLocalColorTable = static_cast<Color*>(HeapAlloc(GetProcessHeap(), 0, localColorTableSize * sizeof(Color)));

			// align bytesPerRow
			bytesPerRow += (sizeof(int) - boundingRectangle.Width() % sizeof(int)) % sizeof(int);

			// TODO: Try to avoid the memory allocation for each single frame.
			pPixels = static_cast<LPBYTE>(HeapAlloc(GetProcessHeap(), 0, bytesPerRow * boundingRectangle.Height() * sizeof(BYTE)));
		}
	} Frame;

	/// \brief <em>Holds information about a GIF image</em>
	///
	/// \sa LoadGIF, Frame
	struct GIFData
	{
		/// \brief <em>Contains a LZW decoder used to decode the GIF frames</em>
		///
		/// \sa Frame
		struct LZWDecoder
		{
			/// \brief <em>The maximum number of codes in the code table</em>
			#define MAX_CODES 4096

			/// \brief <em>The input stream to decode</em>
			///
			/// \sa pOutput, <a href="https://msdn.microsoft.com/en-us/library/aa380034.aspx">IStream</a>
			LPSTREAM pInputStream;
			/// \brief <em>The output buffer to write the decoded frame to</em>
			///
			/// \sa outputSize, pInputStream, OutputLine
			LPBYTE pOutput;
			/// \brief <em>The size of the output buffer defined by \c pOutput</em>
			///
			/// \sa pOutput
			LONGLONG outputSize;
			/// \brief <em>The zero-based index of the pixel row to output next</em>
			///
			/// \sa interlaced, numberOfRows, OutputLine
			LONGLONG rowToOutputNext;
			/// \brief <em>The frame's width in pixels</em>
			///
			/// \sa numberOfRows
			SHORT lineWidth;
			/// \brief <em>The frame's height in pixels</em>
			///
			/// \sa lineWidth, rowToOutputNext
			SHORT numberOfRows;
			/// \brief <em>If \c TRUE, the frame is interlaced, i. e. its pixel rows are not stored continuous</em>
			///
			/// \sa rowToOutputNext, OutputLine
			BOOL interlaced;

			/// \brief <em>The current width of the codes in bits</em>
			SHORT currentCodeSize;
			/// \brief <em>The number of bytes in the current data block, that have not yet been decoded</em>
			///
			/// \sa bitsLeftInCurrentByte, currentBlock, currentByte, pNextByteInBlock, GetNextCode
			SHORT bytesLeftInBlock;
			/// \brief <em>The number of bits in the current byte, that belong to the next code</em>
			///
			/// \sa bytesLeftInBlock, currentByte, GetNextCode
			SHORT bitsLeftInCurrentByte;
			/// \brief <em>The data block that is currently being decoded</em>
			///
			/// \sa bytesLeftInBlock, pNextByteInBlock, currentByte, GetNextCode
			BYTE currentBlock[257];
			/// \brief <em>The data block's next byte to decode</em>
			///
			/// \sa currentBlock, currentByte, GetNextCode
			LPBYTE pNextByteInBlock;
			/// \brief <em>The byte of the data block that is currently decoded</em>
			///
			/// \sa currentBlock, pNextByteInBlock, bitsLeftInCurrentByte, GetNextCode
			BYTE currentByte;

			/// \brief <em>Decodes a LZW compressed input stream</em>
			///
			/// \param[in] pInputStream The LZW compressed input stream to decode.
			/// \param[in,out] pOutput The output buffer for the decoded pixels.
			/// \param[in] outputSize The size (in bytes) of the output buffer specified by \c pOutput.
			/// \param[in] lineWidth The width (in pixels) of the image to decode.
			/// \param[in] numberOfRows The height (in pixels) of the image to decode.
			/// \param[in] interlaced If \c TRUE, the image to decode is stored in interlaced format, i. e.
			///            its pixel rows are not stored continuously.
			///
			/// \return \c TRUE, if the stream was decoded successfully; otherwise \c FALSE.
			///
			/// \sa OutputLine
			BOOL Decode(LPSTREAM pInputStream, LPBYTE pOutput, LONGLONG outputSize, SHORT lineWidth, SHORT numberOfRows, BOOL interlaced)
			{
				this->pInputStream = pInputStream;
				this->pOutput = pOutput;
				this->outputSize = outputSize;
				this->rowToOutputNext = 0;
				this->lineWidth = lineWidth;
				this->numberOfRows = numberOfRows;
				this->interlaced = interlaced;

				register SHORT code;
				register SHORT fc = 0;
				register SHORT oc = 0;

				SHORT initialCodeSize = GetByte();
				if(initialCodeSize < 0) {
					return FALSE;
				}
				if((initialCodeSize < 2) || (initialCodeSize > 9)) {
					return FALSE;
				}

				// initialize
				currentCodeSize = initialCodeSize + 1;
				SHORT highestCodeForCurrentCodeSize = 1 << currentCodeSize;
				SHORT clearCode = 1 << initialCodeSize;
				SHORT endCode = clearCode + 1;
				SHORT firstAvailableCode = endCode + 1;
				SHORT lastReadCode = firstAvailableCode;
				bitsLeftInCurrentByte = 0;
				bytesLeftInBlock = 0;

				LPBYTE pDecodedLine = static_cast<LPBYTE>(HeapAlloc(GetProcessHeap(), 0, lineWidth * sizeof(BYTE)));
				if(!pDecodedLine) {
					return FALSE;
				}
				LPBYTE pOutputBuffer = pDecodedLine;

				LPBYTE pOutputStack = static_cast<LPBYTE>(HeapAlloc(GetProcessHeap(), 0, MAX_CODES * sizeof(BYTE)));
				if(!pOutputStack) {
					HeapFree(GetProcessHeap(), 0, pDecodedLine);
					return FALSE;
				}
				LPBYTE pSuffixes = static_cast<LPBYTE>(HeapAlloc(GetProcessHeap(), 0, MAX_CODES * sizeof(BYTE)));
				if(!pSuffixes) {
					HeapFree(GetProcessHeap(), 0, pDecodedLine);
					HeapFree(GetProcessHeap(), 0, pOutputStack);
					return FALSE;
				}
				PUSHORT pPrefixes = static_cast<PUSHORT>(HeapAlloc(GetProcessHeap(), 0, MAX_CODES * sizeof(USHORT)));
				if(!pPrefixes) {
					HeapFree(GetProcessHeap(), 0, pDecodedLine);
					HeapFree(GetProcessHeap(), 0, pSuffixes);
					HeapFree(GetProcessHeap(), 0, pOutputStack);
					return FALSE;
				}

				register LPBYTE stackPointer = pOutputStack;
				register LPBYTE outputBufferPointer = pOutputBuffer;
				register SHORT remainingOutputBufferSize = lineWidth;

				/* This is the main loop. For each code we get we pass through the linked list of prefix codes,
				   pushing the corresponding "character" for each code onto the stack. When the list reaches a
				   single "character" we push that on the stack too, and then start unstacking each character for
				   output in the correct order. Special handling is included for the clear code, and the whole
				   thing ends when we get an ending code. */
				SHORT foundCode;
				SHORT doneRows = 0;
				while((doneRows < numberOfRows) && ((foundCode = GetNextCode()) != endCode)) {
					// if we had an error, return without completing the decode
					if(foundCode < 0) {
						HeapFree(GetProcessHeap(), 0, pDecodedLine);
						HeapFree(GetProcessHeap(), 0, pPrefixes);
						HeapFree(GetProcessHeap(), 0, pSuffixes);
						HeapFree(GetProcessHeap(), 0, pOutputStack);
						return FALSE;
					}

					// if the code is a clear code, reinitialize all necessary items
					if(foundCode == clearCode) {
						currentCodeSize = initialCodeSize + 1;
						lastReadCode = firstAvailableCode;
						highestCodeForCurrentCodeSize = 1 << currentCodeSize;

						// continue reading codes until we get a non-clear code
						while((foundCode = GetNextCode()) == clearCode);

						// if we get an ending code immediately after a clear code, then break out of the loop
						if(foundCode == endCode) {
							break;
						}

						// finally, if the code is beyond the range of already set codes, then set it to color zero
						if(foundCode >= lastReadCode) {
							foundCode = 0;
						}

						oc = fc = foundCode;

						/* And let us not forget to put the char into the buffer... And if, on the off chance, we were
						   exactly one pixel from the end of the line, we have to output the buffer. */
						*outputBufferPointer++ = static_cast<BYTE>(foundCode & 0xFF);
						if(--remainingOutputBufferSize == 0) {
							if(OutputLine(pOutputBuffer, lineWidth)) {
								++doneRows;
							} else {
								HeapFree(GetProcessHeap(), 0, pDecodedLine);
								HeapFree(GetProcessHeap(), 0, pPrefixes);
								HeapFree(GetProcessHeap(), 0, pSuffixes);
								HeapFree(GetProcessHeap(), 0, pOutputStack);
								return FALSE;
							}

							outputBufferPointer = pOutputBuffer;
							remainingOutputBufferSize = lineWidth;
						}
					} else {
						/* In this case, it's not a clear code or an ending code, so it must be a code code. So we can
						   now decode the code into a stack of character codes. */
						code = foundCode;

						/* If, on the off chance, the code we got is beyond the range of those already set up, we trick
						   the decoder into thinking it actually got the last code read. */
						if(code >= lastReadCode) {
							code = oc;
							*stackPointer++ = static_cast<BYTE>(fc & 0xFF);
						}

						/* Here we scan back along the linked list of prefixes, pushing characters (i. e. suffixes)
						   onto the stack as we do so. */
						while(code >= firstAvailableCode) {
							*stackPointer++ = pSuffixes[code];
							code = pPrefixes[code];
						}

						/* Push the last character on the stack, and set up the new prefix and suffix, and if the
						   required slot number is greater than that allowed by the current bit size, increase the bit
						   size. (NOTE - If we are all full, we *don't* save the new suffix and prefix. */
						*stackPointer++ = static_cast<BYTE>(code & 0xFF);
						if(lastReadCode < highestCodeForCurrentCodeSize) {
							fc = code;
							pSuffixes[lastReadCode] = static_cast<BYTE>(fc & 0xFF);
							pPrefixes[lastReadCode++] = oc;
							oc = foundCode;
						}
						if(lastReadCode >= highestCodeForCurrentCodeSize) {
							if(currentCodeSize < 12) {
								highestCodeForCurrentCodeSize <<= 1;
								++currentCodeSize;
							}
						}

						/* Now that we've pushed the decoded string (in reverse order) onto the stack, lets pop it off
						   and put it into our decode buffer. When the decode buffer is full, write another line. */
						while(stackPointer > pOutputStack) {
							*outputBufferPointer++ = *(--stackPointer);
							if(--remainingOutputBufferSize == 0) {
								if(OutputLine(pOutputBuffer, lineWidth)) {
									++doneRows;
								} else {
									HeapFree(GetProcessHeap(), 0, pDecodedLine);
									HeapFree(GetProcessHeap(), 0, pPrefixes);
									HeapFree(GetProcessHeap(), 0, pSuffixes);
									HeapFree(GetProcessHeap(), 0, pOutputStack);
									return FALSE;
								}

								outputBufferPointer = pOutputBuffer;
								remainingOutputBufferSize = lineWidth;
							}
						}
					}
				}

				BOOL success = TRUE;
				if(remainingOutputBufferSize != lineWidth) {
					success = OutputLine(pOutputBuffer, lineWidth - remainingOutputBufferSize);
				}

				HeapFree(GetProcessHeap(), 0, pDecodedLine);
				HeapFree(GetProcessHeap(), 0, pPrefixes);
				HeapFree(GetProcessHeap(), 0, pSuffixes);
				HeapFree(GetProcessHeap(), 0, pOutputStack);
				return success;
			}

			/// \brief <em>Retrieves the next byte from the input stream</em>
			///
			/// \return The next byte from the input stream, if successful; otherwise -1.
			///
			/// \sa GetNextCode, Decode
			SHORT GetByte(void)
			{
				BYTE ret;
				if(SUCCEEDED(pInputStream->Read(&ret, 1, NULL))) {
					return ret;
				}
				return -1;
			}

			/// \brief <em>Retrieves the next code from the input stream</em>
			///
			/// \return The next code from the input stream, if successful; otherwise -1.
			///
			/// \sa GetByte, Decode
			SHORT GetNextCode(void)
			{
				if(bitsLeftInCurrentByte == 0) {
					if(bytesLeftInBlock <= 0) {
						// out of bytes in current block, so read next block
						pNextByteInBlock = currentBlock;
						bytesLeftInBlock = GetByte();
						if(bytesLeftInBlock < 0) {
							return bytesLeftInBlock;
						} else if(bytesLeftInBlock) {
							for(SHORT i = 0; i < bytesLeftInBlock; ++i) {
								SHORT x = GetByte();
								if(x < 0) {
									return -1;
								}
								currentBlock[i] = static_cast<BYTE>(x & 0xFF);
							}
						}
					}
					currentByte = *pNextByteInBlock++;
					bitsLeftInCurrentByte = 8;
					--bytesLeftInBlock;
				}

				ULONG ret = currentByte >> (8 - bitsLeftInCurrentByte);
				while(currentCodeSize > bitsLeftInCurrentByte) {
					if(bytesLeftInBlock <= 0) {
						// out of bytes in current block, so read next block
						pNextByteInBlock = currentBlock;
						bytesLeftInBlock = GetByte();
						if(bytesLeftInBlock < 0) {
							return bytesLeftInBlock;
						} else if(bytesLeftInBlock) {
							for(SHORT i = 0; i < bytesLeftInBlock; ++i) {
								SHORT x = GetByte();
								if(x < 0) {
									return -1;
								}
								currentBlock[i] = static_cast<BYTE>(x & 0xFF);
							}
						}
					}
					currentByte = *pNextByteInBlock++;
					ret |= currentByte << bitsLeftInCurrentByte;
					bitsLeftInCurrentByte += 8;
					--bytesLeftInBlock;
				}
				//bitsLeftInCurrentByte -= currentCodeSize;
				bitsLeftInCurrentByte = bitsLeftInCurrentByte - currentCodeSize;

				LONG codeMask[13] = { 0, 0x0001, 0x0003, 0x0007, 0x000F, 0x001F, 0x003F, 0x007F, 0x00FF, 0x01FF, 0x03FF, 0x07FF, 0x0FFF };
				ret &= codeMask[currentCodeSize];
				return static_cast<SHORT>(ret);
			}

			/// \brief <em>Writes a decoded line of the input image to the output buffer</em>
			///
			/// \param[in] pBuffer A buffer storing the data to write to the output buffer.
			/// \param[in] bufferSize The size (in bytes) of the buffer specified by \c pBuffer.
			///
			/// \return \c TRUE, if the line was written successfully; otherwise \c FALSE.
			///
			/// \sa Decode, lineWidth
			BOOL OutputLine(LPBYTE pBuffer, SHORT bufferSize)
			{
				BOOL success = TRUE;
				SHORT outputOffset = static_cast<SHORT>(static_cast<LONGLONG>(rowToOutputNext * lineWidth));
				if(outputOffset + bufferSize > outputSize) {
					bufferSize = static_cast<SHORT>(static_cast<LONGLONG>(outputSize - outputOffset));
					success = FALSE;
				}
				for(SHORT i = 0; i < bufferSize; ++i) {
					pOutput[outputOffset + i] = pBuffer[i];
				}

				if(interlaced) {
					if((rowToOutputNext & 7) == 0) {
						rowToOutputNext += 8;
						if(rowToOutputNext >= numberOfRows) {
							rowToOutputNext = 4;
						}
					} else if((rowToOutputNext & 3) == 0) {
						rowToOutputNext += 8;
						if(rowToOutputNext >= numberOfRows) {
							rowToOutputNext = 2;
						}
					} else if((rowToOutputNext & 1) == 0) {
						rowToOutputNext += 4;
						if(rowToOutputNext >= numberOfRows) {
							rowToOutputNext = 1;
						}
					} else {
						rowToOutputNext += 2;
					}
				} else {
					++rowToOutputNext;
				}

				return success;
			}
		} lzwDecoder;

		/// \brief <em>The bounding rectangle of the GIF's logical screen</em>
		///
		/// \sa Frame::boundingRectangle
		CRect logicalScreenRectangle;
		/// \brief <em>If \c TRUE, the GIF has a global color table for all its frames</em>
		///
		/// \sa globalColorTableSize, pGlobalColorTable, Frame::hasLocalColorTable
		UINT hasGlobalColorTable : 1;
		/// \brief <em>The number of elements in the GIF's global color table</em>
		///
		/// \sa pGlobalColorTable, hasGlobalColorTable, Frame::localColorTableSize
		int globalColorTableSize;
		/// \brief <em>The GIF's global color table</em>
		///
		/// \sa globalColorTableSize, hasGlobalColorTable, Frame::pLocalColorTable
		Color* pGlobalColorTable;
		/// \brief <em>The entry in the GIF's global color table, that is used to mark background pixels</em>
		///
		/// \sa Frame::transparentColorIndex
		int backColorIndex;
		/// \brief <em>The GIF's color depth in bits per pixel</em>
		///
		/// \sa pGlobalColorTable
		int colorDepth;
		#ifdef USE_STL
			/// \brief <em>A list of the GIF's frames</em>
			///
			/// \sa Frame
			std::vector<Frame*> frames;
		#else
			/// \brief <em>A list of the GIF's frames</em>
			///
			/// \sa Frame
			CAtlArray<Frame*> frames;
		#endif

		/// \brief <em>The zero-based index of the frame at which to start the animation</em>
		///
		/// \sa endFrame, currentFrame, numberOfLoops, StartReplay
		int startFrame;
		/// \brief <em>The zero-based index of the frame at which to stop the animation</em>
		///
		/// \sa startFrame, currentFrame, numberOfLoops, StartReplay
		int endFrame;
		/// \brief <em>The number of repeats of the animation</em>
		///
		/// Specifies how often the animation shall be repeated. Only the frames from \c startFrame to
		/// \c endFrame are repeated. If set to -1, the animation is repeated until it is stopped using the
		/// \c StopReplay method.
		///
		/// \sa recommendedNumberOfLoops, currentLoop, startFrame, endFrame, StartReplay, StopReplay
		int numberOfLoops;
		/// \brief <em>The number of repeats of the animation as recommended by the animation itself</em>
		///
		/// Specifies how often the animation wants itself to be repeated. Only the frames from \c startFrame
		/// to \c endFrame are repeated. If set to -1, the animation doesn't specify how often it shall be
		/// repeated.
		///
		/// \sa numberOfLoops, currentLoop, startFrame, endFrame, StartReplay, StopReplay
		int recommendedNumberOfLoops;
		/// \brief <em>The zero-based index of the frame, that is currently displayed</em>
		///
		/// \sa startFrame, endFrame
		int currentFrame;
		/// \brief <em>Counts the repeats of the animation</em>
		///
		/// \sa numberOfLoops
		int currentLoop;
		/// \brief <em>If \c TRUE, the animation is currently played</em>
		///
		/// \sa SetIsPlayingGIFFlag
		UINT isPlaying : 1;

		/// \brief <em>Creates a memory device context and bitmap, that can be used for off-screen drawing</em>
		///
		/// \sa screenWithoutCurrentFrame, screenWithCurrentFrame, screenWithBackgroundOnly
		typedef struct MemoryDC
		{
			/// \brief <em>The memory device context we create</em>
			///
			/// \sa bitmap
			CDC dc;
			/// \brief <em>The memory bitmap we create</em>
			///
			/// \sa hPreviousBitmap, dc
			CBitmap bitmap;
			/// \brief <em>The memory device context's default bitmap</em>
			///
			/// \sa bitmap
			HBITMAP hPreviousBitmap;

			/// \brief <em>Creates the memory device context and bitmap</em>
			///
			/// \param[in] hCompatibleDC A device context, that the created objects will be compatible to.
			/// \param[in] width The width (in pixels) of the memory bitmap to create.
			/// \param[in] height The height (in pixels) of the memory bitmap to create.
			///
			/// \sa Destroy
			void Create(HDC hCompatibleDC, int width, int height)
			{
				dc.CreateCompatibleDC(hCompatibleDC);
				bitmap.CreateCompatibleBitmap(hCompatibleDC, width, height);
				hPreviousBitmap = dc.SelectBitmap(bitmap);
			}

			/// \brief <em>Destroys the memory device context and bitmap</em>
			///
			/// \sa Create
			void Destroy(void)
			{
				if(!dc.IsNull()) {
					dc.SelectBitmap(hPreviousBitmap);
					dc.DeleteDC();
					bitmap.DeleteObject();
				}
			}
		} MemoryDC;

		/// \brief <em>Buffers the control's client rectangle without the current frame</em>
		///
		/// Buffers the control's client rectangle as it is before the current frame is drawn.
		///
		/// \sa screenWithCurrentFrame, screenWithBackgroundOnly, currentlyBufferedRectangle, MemoryDC
		MemoryDC screenWithoutCurrentFrame;
		/// \brief <em>Buffers the control's client rectangle including the current frame</em>
		///
		/// Buffers the control's client rectangle as it is after the current frame was drawn.
		///
		/// \sa screenWithoutCurrentFrame, bufferedFrame, currentlyBufferedRectangle, MemoryDC
		MemoryDC screenWithCurrentFrame;
		/// \brief <em>Buffers the control's client rectangle with the animation's background only</em>
		///
		/// Buffers the control's client rectangle as it is before any frame is drawn.
		///
		/// \sa screenWithoutCurrentFrame, currentlyBufferedRectangle, MemoryDC
		MemoryDC screenWithBackgroundOnly;
		/// \brief <em>The zero-based index of the frame that the buffers were made for</em>
		///
		/// \sa screenWithCurrentFrame, screenWithBackgroundOnly, MemoryDC
		int bufferedFrame;
		/// \brief <em>The bounding rectangle of the currently buffered area relative to the control's upper-left corner</em>
		///
		/// \sa screenWithCurrentFrame, screenWithBackgroundOnly, MemoryDC, OnWindowPosChanged
		CRect currentlyBufferedRectangle;

		GIFData()
		{
			hasGlobalColorTable = FALSE;
			pGlobalColorTable = NULL;
			globalColorTableSize = 0;
			backColorIndex = 0;
			colorDepth = 0;

			startFrame = 0;
			endFrame = 0;
			numberOfLoops = -1;
			recommendedNumberOfLoops = 1;
			isPlaying = FALSE;
			currentFrame = startFrame;
			currentLoop = 1;

			bufferedFrame = -1;
		}

		~GIFData()
		{
			ReleaseData();
		}

		/// \brief <em>Frees any memory that the GIF has been using and resets the most important member variables to their default</em>
		void ReleaseData(void)
		{
			if(pGlobalColorTable) {
				HeapFree(GetProcessHeap(), 0, pGlobalColorTable);
				pGlobalColorTable = NULL;
			}

			#ifdef USE_STL
				for(std::vector<Frame*>::iterator iter = frames.begin(); iter != frames.end(); ++iter) {
					delete *iter;
				}
				frames.clear();
			#else
				for(size_t i = 0; i < frames.GetCount(); ++i) {
					delete frames[i];
				}
				frames.RemoveAll();
			#endif

			logicalScreenRectangle.left = 0;
			logicalScreenRectangle.top = 0;
			logicalScreenRectangle.right = 0;
			logicalScreenRectangle.bottom = 0;
			hasGlobalColorTable = FALSE;
			globalColorTableSize = 0;
			backColorIndex = 0;
			colorDepth = 0;

			bufferedFrame = -1;
			screenWithoutCurrentFrame.Destroy();
			screenWithCurrentFrame.Destroy();
			screenWithBackgroundOnly.Destroy();
		}
	} gifData;
	//@}
	//////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////
	/// \name Version information
	///
	//@{
	/// \brief <em>Holds version information about comctl32.dll</em>
	///
	/// \sa DllVersion, IsComctl32Version610OrNewer
	DllVersion versionComctl32;

	/// \brief <em>Retrieves whether we're using at least version 6.10 of comctl32.dll</em>
	///
	/// \return \c TRUE if we're using comctl32.dll version 6.10 or higher; otherwise \c FALSE.
	BOOL IsComctl32Version610OrNewer(void);
	//@}
	//////////////////////////////////////////////////////////////////////

private:
};     // Animation

OBJECT_ENTRY_AUTO(__uuidof(Animation), Animation)