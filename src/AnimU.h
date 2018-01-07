

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0613 */
/* at Tue Jan 19 04:14:07 2038
 */
/* Compiler settings for AnimU.idl:
    Oicf, W4, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0613 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */


#ifndef __AnimU_h__
#define __AnimU_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IOLEDataObject_FWD_DEFINED__
#define __IOLEDataObject_FWD_DEFINED__
typedef interface IOLEDataObject IOLEDataObject;

#endif 	/* __IOLEDataObject_FWD_DEFINED__ */


#ifndef ___IOLEDataObjectEvents_FWD_DEFINED__
#define ___IOLEDataObjectEvents_FWD_DEFINED__
typedef interface _IOLEDataObjectEvents _IOLEDataObjectEvents;

#endif 	/* ___IOLEDataObjectEvents_FWD_DEFINED__ */


#ifndef __OLEDataObject_FWD_DEFINED__
#define __OLEDataObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class OLEDataObject OLEDataObject;
#else
typedef struct OLEDataObject OLEDataObject;
#endif /* __cplusplus */

#endif 	/* __OLEDataObject_FWD_DEFINED__ */


#ifndef __IAnimation_FWD_DEFINED__
#define __IAnimation_FWD_DEFINED__
typedef interface IAnimation IAnimation;

#endif 	/* __IAnimation_FWD_DEFINED__ */


#ifndef ___IAnimationEvents_FWD_DEFINED__
#define ___IAnimationEvents_FWD_DEFINED__
typedef interface _IAnimationEvents _IAnimationEvents;

#endif 	/* ___IAnimationEvents_FWD_DEFINED__ */


#ifndef __Animation_FWD_DEFINED__
#define __Animation_FWD_DEFINED__

#ifdef __cplusplus
typedef class Animation Animation;
#else
typedef struct Animation Animation;
#endif /* __cplusplus */

#endif 	/* __Animation_FWD_DEFINED__ */


#ifndef __CommonProperties_FWD_DEFINED__
#define __CommonProperties_FWD_DEFINED__

#ifdef __cplusplus
typedef class CommonProperties CommonProperties;
#else
typedef struct CommonProperties CommonProperties;
#endif /* __cplusplus */

#endif 	/* __CommonProperties_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_AnimU_0000_0000 */
/* [local] */ 

#pragma once





extern RPC_IF_HANDLE __MIDL_itf_AnimU_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AnimU_0000_0000_v0_0_s_ifspec;


#ifndef __AnimLibU_LIBRARY_DEFINED__
#define __AnimLibU_LIBRARY_DEFINED__

/* library AnimLibU */
/* [helpstring][version][uuid] */ 

typedef /* [helpstring] */ 
enum AnimationBackStyleConstants
    {
        absUseBackColor	= 0,
        absDefinedByAnimation	= ( absUseBackColor + 1 ) 
    } 	AnimationBackStyleConstants;

typedef /* [helpstring] */ 
enum AppearanceConstants
    {
        a2D	= 0,
        a3D	= ( a2D + 1 ) ,
        a3DLight	= ( a3D + 1 ) 
    } 	AppearanceConstants;

typedef /* [helpstring] */ 
enum BorderStyleConstants
    {
        bsNone	= 0,
        bsFixedSingle	= ( bsNone + 1 ) 
    } 	BorderStyleConstants;

typedef /* [helpstring] */ 
enum DisabledEventsConstants
    {
        deMouseEvents	= 0x1,
        deClickEvents	= 0x2
    } 	DisabledEventsConstants;

typedef /* [helpstring] */ 
enum DropDescriptionIconConstants
    {
        ddiNone	= -1,
        ddiNoDrop	= 0,
        ddiCopy	= 1,
        ddiMove	= 2,
        ddiLink	= 4,
        ddiMetadataChange	= 6,
        ddiWarning	= 7,
        ddiUseDefault	= 8
    } 	DropDescriptionIconConstants;

typedef /* [helpstring] */ 
enum ExtendedMouseButtonConstants
    {
        embXButton1	= 0x20,
        embXButton2	= 0x40
    } 	ExtendedMouseButtonConstants;

typedef /* [helpstring] */ 
enum MousePointerConstants
    {
        mpDefault	= 0,
        mpArrow	= ( mpDefault + 1 ) ,
        mpCross	= ( mpArrow + 1 ) ,
        mpIBeam	= ( mpCross + 1 ) ,
        mpIcon	= ( mpIBeam + 1 ) ,
        mpSize	= ( mpIcon + 1 ) ,
        mpSizeNESW	= ( mpSize + 1 ) ,
        mpSizeNS	= ( mpSizeNESW + 1 ) ,
        mpSizeNWSE	= ( mpSizeNS + 1 ) ,
        mpSizeEW	= ( mpSizeNWSE + 1 ) ,
        mpUpArrow	= ( mpSizeEW + 1 ) ,
        mpHourglass	= ( mpUpArrow + 1 ) ,
        mpNoDrop	= ( mpHourglass + 1 ) ,
        mpArrowHourglass	= ( mpNoDrop + 1 ) ,
        mpArrowQuestion	= ( mpArrowHourglass + 1 ) ,
        mpSizeAll	= ( mpArrowQuestion + 1 ) ,
        mpHand	= ( mpSizeAll + 1 ) ,
        mpInsertMedia	= ( mpHand + 1 ) ,
        mpScrollAll	= ( mpInsertMedia + 1 ) ,
        mpScrollN	= ( mpScrollAll + 1 ) ,
        mpScrollNE	= ( mpScrollN + 1 ) ,
        mpScrollE	= ( mpScrollNE + 1 ) ,
        mpScrollSE	= ( mpScrollE + 1 ) ,
        mpScrollS	= ( mpScrollSE + 1 ) ,
        mpScrollSW	= ( mpScrollS + 1 ) ,
        mpScrollW	= ( mpScrollSW + 1 ) ,
        mpScrollNW	= ( mpScrollW + 1 ) ,
        mpScrollNS	= ( mpScrollNW + 1 ) ,
        mpScrollEW	= ( mpScrollNS + 1 ) ,
        mpCustom	= 0x63
    } 	MousePointerConstants;

typedef /* [helpstring] */ 
enum OLEDropEffectConstants
    {
        odeNone	= 0,
        odeCopy	= 1,
        odeMove	= 2,
        odeLink	= 4,
        odeCopyOrMove	= ( odeCopy | odeMove ) ,
        odeScroll	= 0x80000000
    } 	OLEDropEffectConstants;


EXTERN_C const IID LIBID_AnimLibU;

#ifndef __IOLEDataObject_INTERFACE_DEFINED__
#define __IOLEDataObject_INTERFACE_DEFINED__

/* interface IOLEDataObject */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IOLEDataObject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2201BC9E-E51C-41a1-A917-6A78AD8C73D2")
    IOLEDataObject : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCanonicalFormat( 
            /* [out][in] */ LONG *formatID,
            /* [out][in] */ LONG *Index,
            /* [out][in] */ LONG *dataOrViewAspect) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetData( 
            /* [in] */ LONG formatID,
            /* [defaultvalue][in] */ LONG Index,
            /* [defaultvalue][in] */ LONG dataOrViewAspect,
            /* [retval][out] */ VARIANT *pData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDropDescription( 
            /* [optional][out][in] */ VARIANT *targetDescription,
            /* [optional][out][in] */ VARIANT *actionDescription,
            /* [defaultvalue][out][in] */ DropDescriptionIconConstants *Icon = 0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFormat( 
            /* [in] */ LONG formatID,
            /* [defaultvalue][in] */ LONG Index,
            /* [defaultvalue][in] */ LONG dataOrViewAspect,
            /* [retval][out] */ VARIANT_BOOL *pFormatAvailable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetData( 
            /* [in] */ LONG formatID,
            /* [optional][in] */ VARIANT data,
            /* [defaultvalue][in] */ LONG Index = -1,
            /* [defaultvalue][in] */ LONG dataOrViewAspect = 1) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDropDescription( 
            /* [optional][in] */ VARIANT targetDescription,
            /* [optional][in] */ VARIANT actionDescription,
            /* [defaultvalue][in] */ DropDescriptionIconConstants Icon = ddiNone) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IOLEDataObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IOLEDataObject * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IOLEDataObject * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IOLEDataObject * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IOLEDataObject * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IOLEDataObject * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IOLEDataObject * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IOLEDataObject * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IOLEDataObject * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCanonicalFormat )( 
            IOLEDataObject * This,
            /* [out][in] */ LONG *formatID,
            /* [out][in] */ LONG *Index,
            /* [out][in] */ LONG *dataOrViewAspect);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetData )( 
            IOLEDataObject * This,
            /* [in] */ LONG formatID,
            /* [defaultvalue][in] */ LONG Index,
            /* [defaultvalue][in] */ LONG dataOrViewAspect,
            /* [retval][out] */ VARIANT *pData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDropDescription )( 
            IOLEDataObject * This,
            /* [optional][out][in] */ VARIANT *targetDescription,
            /* [optional][out][in] */ VARIANT *actionDescription,
            /* [defaultvalue][out][in] */ DropDescriptionIconConstants *Icon);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFormat )( 
            IOLEDataObject * This,
            /* [in] */ LONG formatID,
            /* [defaultvalue][in] */ LONG Index,
            /* [defaultvalue][in] */ LONG dataOrViewAspect,
            /* [retval][out] */ VARIANT_BOOL *pFormatAvailable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetData )( 
            IOLEDataObject * This,
            /* [in] */ LONG formatID,
            /* [optional][in] */ VARIANT data,
            /* [defaultvalue][in] */ LONG Index,
            /* [defaultvalue][in] */ LONG dataOrViewAspect);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDropDescription )( 
            IOLEDataObject * This,
            /* [optional][in] */ VARIANT targetDescription,
            /* [optional][in] */ VARIANT actionDescription,
            /* [defaultvalue][in] */ DropDescriptionIconConstants Icon);
        
        END_INTERFACE
    } IOLEDataObjectVtbl;

    interface IOLEDataObject
    {
        CONST_VTBL struct IOLEDataObjectVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IOLEDataObject_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IOLEDataObject_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IOLEDataObject_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IOLEDataObject_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IOLEDataObject_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IOLEDataObject_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IOLEDataObject_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IOLEDataObject_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IOLEDataObject_GetCanonicalFormat(This,formatID,Index,dataOrViewAspect)	\
    ( (This)->lpVtbl -> GetCanonicalFormat(This,formatID,Index,dataOrViewAspect) ) 

#define IOLEDataObject_GetData(This,formatID,Index,dataOrViewAspect,pData)	\
    ( (This)->lpVtbl -> GetData(This,formatID,Index,dataOrViewAspect,pData) ) 

#define IOLEDataObject_GetDropDescription(This,targetDescription,actionDescription,Icon)	\
    ( (This)->lpVtbl -> GetDropDescription(This,targetDescription,actionDescription,Icon) ) 

#define IOLEDataObject_GetFormat(This,formatID,Index,dataOrViewAspect,pFormatAvailable)	\
    ( (This)->lpVtbl -> GetFormat(This,formatID,Index,dataOrViewAspect,pFormatAvailable) ) 

#define IOLEDataObject_SetData(This,formatID,data,Index,dataOrViewAspect)	\
    ( (This)->lpVtbl -> SetData(This,formatID,data,Index,dataOrViewAspect) ) 

#define IOLEDataObject_SetDropDescription(This,targetDescription,actionDescription,Icon)	\
    ( (This)->lpVtbl -> SetDropDescription(This,targetDescription,actionDescription,Icon) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IOLEDataObject_INTERFACE_DEFINED__ */


#ifndef ___IOLEDataObjectEvents_DISPINTERFACE_DEFINED__
#define ___IOLEDataObjectEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IOLEDataObjectEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IOLEDataObjectEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("2FDC6256-F09C-445d-95F5-CC4D5E292A92")
    _IOLEDataObjectEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IOLEDataObjectEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IOLEDataObjectEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IOLEDataObjectEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IOLEDataObjectEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IOLEDataObjectEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IOLEDataObjectEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IOLEDataObjectEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IOLEDataObjectEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _IOLEDataObjectEventsVtbl;

    interface _IOLEDataObjectEvents
    {
        CONST_VTBL struct _IOLEDataObjectEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IOLEDataObjectEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IOLEDataObjectEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IOLEDataObjectEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IOLEDataObjectEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IOLEDataObjectEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IOLEDataObjectEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IOLEDataObjectEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IOLEDataObjectEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_OLEDataObject;

#ifdef __cplusplus

class DECLSPEC_UUID("DAC6A7E6-8B68-4b93-8B8B-5A7CC8586132")
OLEDataObject;
#endif

#ifndef __IAnimation_INTERFACE_DEFINED__
#define __IAnimation_INTERFACE_DEFINED__

/* interface IAnimation */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IAnimation;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0738DAC4-3779-499a-A024-9FBBD03F3E70")
    IAnimation : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AnimationBackStyle( 
            /* [retval][out] */ AnimationBackStyleConstants *pValue) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AnimationBackStyle( 
            /* [in] */ AnimationBackStyleConstants newValue) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Appearance( 
            /* [retval][out] */ AppearanceConstants *pValue) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Appearance( 
            /* [in] */ AppearanceConstants newValue) = 0;
        
        virtual /* [hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get_AppID( 
            /* [retval][out] */ SHORT *pValue) = 0;
        
        virtual /* [hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get_AppName( 
            /* [retval][out] */ BSTR *pValue) = 0;
        
        virtual /* [hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get_AppShortName( 
            /* [retval][out] */ BSTR *pValue) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AutoStartReplay( 
            /* [retval][out] */ VARIANT_BOOL *pValue) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AutoStartReplay( 
            /* [in] */ VARIANT_BOOL newValue) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BackColor( 
            /* [retval][out] */ OLE_COLOR *pValue) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BackColor( 
            /* [in] */ OLE_COLOR newValue) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BorderStyle( 
            /* [retval][out] */ BorderStyleConstants *pValue) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BorderStyle( 
            /* [in] */ BorderStyleConstants newValue) = 0;
        
        virtual /* [hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get_Build( 
            /* [retval][out] */ LONG *pValue) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CenterAnimation( 
            /* [retval][out] */ VARIANT_BOOL *pValue) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CenterAnimation( 
            /* [in] */ VARIANT_BOOL newValue) = 0;
        
        virtual /* [hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get_CharSet( 
            /* [retval][out] */ BSTR *pValue) = 0;
        
        virtual /* [nonbrowsable][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DisabledEvents( 
            /* [retval][out] */ DisabledEventsConstants *pValue) = 0;
        
        virtual /* [nonbrowsable][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DisabledEvents( 
            /* [in] */ DisabledEventsConstants newValue) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DontRedraw( 
            /* [retval][out] */ VARIANT_BOOL *pValue) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DontRedraw( 
            /* [in] */ VARIANT_BOOL newValue) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Enabled( 
            /* [retval][out] */ VARIANT_BOOL *pValue) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Enabled( 
            /* [in] */ VARIANT_BOOL newValue) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HoverTime( 
            /* [retval][out] */ LONG *pValue) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HoverTime( 
            /* [in] */ LONG newValue) = 0;
        
        virtual /* [nonbrowsable][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hWnd( 
            /* [retval][out] */ OLE_HANDLE *pValue) = 0;
        
        virtual /* [nonbrowsable][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsPlaying( 
            /* [retval][out] */ VARIANT_BOOL *pValue) = 0;
        
        virtual /* [hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsRelease( 
            /* [retval][out] */ VARIANT_BOOL *pValue) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MouseIcon( 
            /* [retval][out] */ IPictureDisp **ppMouseIcon) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MouseIcon( 
            /* [in] */ IPictureDisp *pNewMouseIcon) = 0;
        
        virtual /* [helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_MouseIcon( 
            /* [in] */ IPictureDisp *pNewMouseIcon) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MousePointer( 
            /* [retval][out] */ MousePointerConstants *pValue) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MousePointer( 
            /* [in] */ MousePointerConstants newValue) = 0;
        
        virtual /* [hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get_Programmer( 
            /* [retval][out] */ BSTR *pValue) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RegisterForOLEDragDrop( 
            /* [retval][out] */ VARIANT_BOOL *pValue) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RegisterForOLEDragDrop( 
            /* [in] */ VARIANT_BOOL newValue) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SupportOLEDragImages( 
            /* [retval][out] */ VARIANT_BOOL *pValue) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SupportOLEDragImages( 
            /* [in] */ VARIANT_BOOL newValue) = 0;
        
        virtual /* [hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get_Tester( 
            /* [retval][out] */ BSTR *pValue) = 0;
        
        virtual /* [nonbrowsable][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ BSTR *pValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE About( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CloseAnimation( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DisplayFrame( 
            /* [in] */ LONG frameNumber,
            /* [retval][out] */ VARIANT_BOOL *pSuccess) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadSettingsFromFile( 
            /* [in] */ BSTR file,
            /* [retval][out] */ VARIANT_BOOL *pSucceeded) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenAnimationFromFile( 
            /* [in] */ BSTR filePath,
            /* [retval][out] */ VARIANT_BOOL *pSuccess) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenAnimationFromResource( 
            /* [in] */ LONG hModule,
            /* [in] */ LONG resourceID,
            /* [in] */ BSTR resourceTypeName,
            /* [retval][out] */ VARIANT_BOOL *pSuccess) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveSettingsToFile( 
            /* [in] */ BSTR file,
            /* [retval][out] */ VARIANT_BOOL *pSucceeded) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartReplay( 
            /* [defaultvalue][in] */ LONG startFrame,
            /* [defaultvalue][in] */ LONG endFrame,
            /* [defaultvalue][in] */ LONG repeats,
            /* [retval][out] */ VARIANT_BOOL *pSuccess) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StopReplay( 
            /* [retval][out] */ VARIANT_BOOL *pSuccess) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FinishOLEDragDrop( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAnimationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAnimation * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAnimation * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAnimation * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAnimation * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAnimation * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAnimation * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAnimation * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AnimationBackStyle )( 
            IAnimation * This,
            /* [retval][out] */ AnimationBackStyleConstants *pValue);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AnimationBackStyle )( 
            IAnimation * This,
            /* [in] */ AnimationBackStyleConstants newValue);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Appearance )( 
            IAnimation * This,
            /* [retval][out] */ AppearanceConstants *pValue);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Appearance )( 
            IAnimation * This,
            /* [in] */ AppearanceConstants newValue);
        
        /* [hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AppID )( 
            IAnimation * This,
            /* [retval][out] */ SHORT *pValue);
        
        /* [hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AppName )( 
            IAnimation * This,
            /* [retval][out] */ BSTR *pValue);
        
        /* [hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AppShortName )( 
            IAnimation * This,
            /* [retval][out] */ BSTR *pValue);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AutoStartReplay )( 
            IAnimation * This,
            /* [retval][out] */ VARIANT_BOOL *pValue);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AutoStartReplay )( 
            IAnimation * This,
            /* [in] */ VARIANT_BOOL newValue);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackColor )( 
            IAnimation * This,
            /* [retval][out] */ OLE_COLOR *pValue);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BackColor )( 
            IAnimation * This,
            /* [in] */ OLE_COLOR newValue);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BorderStyle )( 
            IAnimation * This,
            /* [retval][out] */ BorderStyleConstants *pValue);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BorderStyle )( 
            IAnimation * This,
            /* [in] */ BorderStyleConstants newValue);
        
        /* [hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Build )( 
            IAnimation * This,
            /* [retval][out] */ LONG *pValue);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CenterAnimation )( 
            IAnimation * This,
            /* [retval][out] */ VARIANT_BOOL *pValue);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CenterAnimation )( 
            IAnimation * This,
            /* [in] */ VARIANT_BOOL newValue);
        
        /* [hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CharSet )( 
            IAnimation * This,
            /* [retval][out] */ BSTR *pValue);
        
        /* [nonbrowsable][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DisabledEvents )( 
            IAnimation * This,
            /* [retval][out] */ DisabledEventsConstants *pValue);
        
        /* [nonbrowsable][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DisabledEvents )( 
            IAnimation * This,
            /* [in] */ DisabledEventsConstants newValue);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DontRedraw )( 
            IAnimation * This,
            /* [retval][out] */ VARIANT_BOOL *pValue);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DontRedraw )( 
            IAnimation * This,
            /* [in] */ VARIANT_BOOL newValue);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Enabled )( 
            IAnimation * This,
            /* [retval][out] */ VARIANT_BOOL *pValue);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Enabled )( 
            IAnimation * This,
            /* [in] */ VARIANT_BOOL newValue);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HoverTime )( 
            IAnimation * This,
            /* [retval][out] */ LONG *pValue);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HoverTime )( 
            IAnimation * This,
            /* [in] */ LONG newValue);
        
        /* [nonbrowsable][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_hWnd )( 
            IAnimation * This,
            /* [retval][out] */ OLE_HANDLE *pValue);
        
        /* [nonbrowsable][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsPlaying )( 
            IAnimation * This,
            /* [retval][out] */ VARIANT_BOOL *pValue);
        
        /* [hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsRelease )( 
            IAnimation * This,
            /* [retval][out] */ VARIANT_BOOL *pValue);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MouseIcon )( 
            IAnimation * This,
            /* [retval][out] */ IPictureDisp **ppMouseIcon);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MouseIcon )( 
            IAnimation * This,
            /* [in] */ IPictureDisp *pNewMouseIcon);
        
        /* [helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_MouseIcon )( 
            IAnimation * This,
            /* [in] */ IPictureDisp *pNewMouseIcon);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MousePointer )( 
            IAnimation * This,
            /* [retval][out] */ MousePointerConstants *pValue);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MousePointer )( 
            IAnimation * This,
            /* [in] */ MousePointerConstants newValue);
        
        /* [hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Programmer )( 
            IAnimation * This,
            /* [retval][out] */ BSTR *pValue);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RegisterForOLEDragDrop )( 
            IAnimation * This,
            /* [retval][out] */ VARIANT_BOOL *pValue);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RegisterForOLEDragDrop )( 
            IAnimation * This,
            /* [in] */ VARIANT_BOOL newValue);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SupportOLEDragImages )( 
            IAnimation * This,
            /* [retval][out] */ VARIANT_BOOL *pValue);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SupportOLEDragImages )( 
            IAnimation * This,
            /* [in] */ VARIANT_BOOL newValue);
        
        /* [hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Tester )( 
            IAnimation * This,
            /* [retval][out] */ BSTR *pValue);
        
        /* [nonbrowsable][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Version )( 
            IAnimation * This,
            /* [retval][out] */ BSTR *pValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *About )( 
            IAnimation * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CloseAnimation )( 
            IAnimation * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DisplayFrame )( 
            IAnimation * This,
            /* [in] */ LONG frameNumber,
            /* [retval][out] */ VARIANT_BOOL *pSuccess);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadSettingsFromFile )( 
            IAnimation * This,
            /* [in] */ BSTR file,
            /* [retval][out] */ VARIANT_BOOL *pSucceeded);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OpenAnimationFromFile )( 
            IAnimation * This,
            /* [in] */ BSTR filePath,
            /* [retval][out] */ VARIANT_BOOL *pSuccess);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OpenAnimationFromResource )( 
            IAnimation * This,
            /* [in] */ LONG hModule,
            /* [in] */ LONG resourceID,
            /* [in] */ BSTR resourceTypeName,
            /* [retval][out] */ VARIANT_BOOL *pSuccess);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            IAnimation * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SaveSettingsToFile )( 
            IAnimation * This,
            /* [in] */ BSTR file,
            /* [retval][out] */ VARIANT_BOOL *pSucceeded);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StartReplay )( 
            IAnimation * This,
            /* [defaultvalue][in] */ LONG startFrame,
            /* [defaultvalue][in] */ LONG endFrame,
            /* [defaultvalue][in] */ LONG repeats,
            /* [retval][out] */ VARIANT_BOOL *pSuccess);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StopReplay )( 
            IAnimation * This,
            /* [retval][out] */ VARIANT_BOOL *pSuccess);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FinishOLEDragDrop )( 
            IAnimation * This);
        
        END_INTERFACE
    } IAnimationVtbl;

    interface IAnimation
    {
        CONST_VTBL struct IAnimationVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAnimation_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAnimation_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAnimation_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAnimation_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IAnimation_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IAnimation_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IAnimation_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IAnimation_get_AnimationBackStyle(This,pValue)	\
    ( (This)->lpVtbl -> get_AnimationBackStyle(This,pValue) ) 

#define IAnimation_put_AnimationBackStyle(This,newValue)	\
    ( (This)->lpVtbl -> put_AnimationBackStyle(This,newValue) ) 

#define IAnimation_get_Appearance(This,pValue)	\
    ( (This)->lpVtbl -> get_Appearance(This,pValue) ) 

#define IAnimation_put_Appearance(This,newValue)	\
    ( (This)->lpVtbl -> put_Appearance(This,newValue) ) 

#define IAnimation_get_AppID(This,pValue)	\
    ( (This)->lpVtbl -> get_AppID(This,pValue) ) 

#define IAnimation_get_AppName(This,pValue)	\
    ( (This)->lpVtbl -> get_AppName(This,pValue) ) 

#define IAnimation_get_AppShortName(This,pValue)	\
    ( (This)->lpVtbl -> get_AppShortName(This,pValue) ) 

#define IAnimation_get_AutoStartReplay(This,pValue)	\
    ( (This)->lpVtbl -> get_AutoStartReplay(This,pValue) ) 

#define IAnimation_put_AutoStartReplay(This,newValue)	\
    ( (This)->lpVtbl -> put_AutoStartReplay(This,newValue) ) 

#define IAnimation_get_BackColor(This,pValue)	\
    ( (This)->lpVtbl -> get_BackColor(This,pValue) ) 

#define IAnimation_put_BackColor(This,newValue)	\
    ( (This)->lpVtbl -> put_BackColor(This,newValue) ) 

#define IAnimation_get_BorderStyle(This,pValue)	\
    ( (This)->lpVtbl -> get_BorderStyle(This,pValue) ) 

#define IAnimation_put_BorderStyle(This,newValue)	\
    ( (This)->lpVtbl -> put_BorderStyle(This,newValue) ) 

#define IAnimation_get_Build(This,pValue)	\
    ( (This)->lpVtbl -> get_Build(This,pValue) ) 

#define IAnimation_get_CenterAnimation(This,pValue)	\
    ( (This)->lpVtbl -> get_CenterAnimation(This,pValue) ) 

#define IAnimation_put_CenterAnimation(This,newValue)	\
    ( (This)->lpVtbl -> put_CenterAnimation(This,newValue) ) 

#define IAnimation_get_CharSet(This,pValue)	\
    ( (This)->lpVtbl -> get_CharSet(This,pValue) ) 

#define IAnimation_get_DisabledEvents(This,pValue)	\
    ( (This)->lpVtbl -> get_DisabledEvents(This,pValue) ) 

#define IAnimation_put_DisabledEvents(This,newValue)	\
    ( (This)->lpVtbl -> put_DisabledEvents(This,newValue) ) 

#define IAnimation_get_DontRedraw(This,pValue)	\
    ( (This)->lpVtbl -> get_DontRedraw(This,pValue) ) 

#define IAnimation_put_DontRedraw(This,newValue)	\
    ( (This)->lpVtbl -> put_DontRedraw(This,newValue) ) 

#define IAnimation_get_Enabled(This,pValue)	\
    ( (This)->lpVtbl -> get_Enabled(This,pValue) ) 

#define IAnimation_put_Enabled(This,newValue)	\
    ( (This)->lpVtbl -> put_Enabled(This,newValue) ) 

#define IAnimation_get_HoverTime(This,pValue)	\
    ( (This)->lpVtbl -> get_HoverTime(This,pValue) ) 

#define IAnimation_put_HoverTime(This,newValue)	\
    ( (This)->lpVtbl -> put_HoverTime(This,newValue) ) 

#define IAnimation_get_hWnd(This,pValue)	\
    ( (This)->lpVtbl -> get_hWnd(This,pValue) ) 

#define IAnimation_get_IsPlaying(This,pValue)	\
    ( (This)->lpVtbl -> get_IsPlaying(This,pValue) ) 

#define IAnimation_get_IsRelease(This,pValue)	\
    ( (This)->lpVtbl -> get_IsRelease(This,pValue) ) 

#define IAnimation_get_MouseIcon(This,ppMouseIcon)	\
    ( (This)->lpVtbl -> get_MouseIcon(This,ppMouseIcon) ) 

#define IAnimation_put_MouseIcon(This,pNewMouseIcon)	\
    ( (This)->lpVtbl -> put_MouseIcon(This,pNewMouseIcon) ) 

#define IAnimation_putref_MouseIcon(This,pNewMouseIcon)	\
    ( (This)->lpVtbl -> putref_MouseIcon(This,pNewMouseIcon) ) 

#define IAnimation_get_MousePointer(This,pValue)	\
    ( (This)->lpVtbl -> get_MousePointer(This,pValue) ) 

#define IAnimation_put_MousePointer(This,newValue)	\
    ( (This)->lpVtbl -> put_MousePointer(This,newValue) ) 

#define IAnimation_get_Programmer(This,pValue)	\
    ( (This)->lpVtbl -> get_Programmer(This,pValue) ) 

#define IAnimation_get_RegisterForOLEDragDrop(This,pValue)	\
    ( (This)->lpVtbl -> get_RegisterForOLEDragDrop(This,pValue) ) 

#define IAnimation_put_RegisterForOLEDragDrop(This,newValue)	\
    ( (This)->lpVtbl -> put_RegisterForOLEDragDrop(This,newValue) ) 

#define IAnimation_get_SupportOLEDragImages(This,pValue)	\
    ( (This)->lpVtbl -> get_SupportOLEDragImages(This,pValue) ) 

#define IAnimation_put_SupportOLEDragImages(This,newValue)	\
    ( (This)->lpVtbl -> put_SupportOLEDragImages(This,newValue) ) 

#define IAnimation_get_Tester(This,pValue)	\
    ( (This)->lpVtbl -> get_Tester(This,pValue) ) 

#define IAnimation_get_Version(This,pValue)	\
    ( (This)->lpVtbl -> get_Version(This,pValue) ) 

#define IAnimation_About(This)	\
    ( (This)->lpVtbl -> About(This) ) 

#define IAnimation_CloseAnimation(This)	\
    ( (This)->lpVtbl -> CloseAnimation(This) ) 

#define IAnimation_DisplayFrame(This,frameNumber,pSuccess)	\
    ( (This)->lpVtbl -> DisplayFrame(This,frameNumber,pSuccess) ) 

#define IAnimation_LoadSettingsFromFile(This,file,pSucceeded)	\
    ( (This)->lpVtbl -> LoadSettingsFromFile(This,file,pSucceeded) ) 

#define IAnimation_OpenAnimationFromFile(This,filePath,pSuccess)	\
    ( (This)->lpVtbl -> OpenAnimationFromFile(This,filePath,pSuccess) ) 

#define IAnimation_OpenAnimationFromResource(This,hModule,resourceID,resourceTypeName,pSuccess)	\
    ( (This)->lpVtbl -> OpenAnimationFromResource(This,hModule,resourceID,resourceTypeName,pSuccess) ) 

#define IAnimation_Refresh(This)	\
    ( (This)->lpVtbl -> Refresh(This) ) 

#define IAnimation_SaveSettingsToFile(This,file,pSucceeded)	\
    ( (This)->lpVtbl -> SaveSettingsToFile(This,file,pSucceeded) ) 

#define IAnimation_StartReplay(This,startFrame,endFrame,repeats,pSuccess)	\
    ( (This)->lpVtbl -> StartReplay(This,startFrame,endFrame,repeats,pSuccess) ) 

#define IAnimation_StopReplay(This,pSuccess)	\
    ( (This)->lpVtbl -> StopReplay(This,pSuccess) ) 

#define IAnimation_FinishOLEDragDrop(This)	\
    ( (This)->lpVtbl -> FinishOLEDragDrop(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAnimation_INTERFACE_DEFINED__ */


#ifndef ___IAnimationEvents_DISPINTERFACE_DEFINED__
#define ___IAnimationEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IAnimationEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IAnimationEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("FA8C01DF-A2FB-4577-BB25-9154E4DB2FCA")
    _IAnimationEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IAnimationEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IAnimationEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IAnimationEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IAnimationEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IAnimationEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IAnimationEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IAnimationEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IAnimationEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _IAnimationEventsVtbl;

    interface _IAnimationEvents
    {
        CONST_VTBL struct _IAnimationEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IAnimationEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IAnimationEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IAnimationEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IAnimationEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IAnimationEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IAnimationEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IAnimationEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IAnimationEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Animation;

#ifdef __cplusplus

class DECLSPEC_UUID("C85E66A9-EDBB-4785-B1FA-2C86AB6D7680")
Animation;
#endif

EXTERN_C const CLSID CLSID_CommonProperties;

#ifdef __cplusplus

class DECLSPEC_UUID("89D8C63B-30A6-4dc0-95C5-ABB0A3F22B00")
CommonProperties;
#endif
#endif /* __AnimLibU_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


