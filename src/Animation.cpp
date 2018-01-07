// Animation.cpp: Superclasses SysAnimate32.

#include "stdafx.h"
#include "Animation.h"
#include "ClassFactory.h"

#pragma comment(lib, "comctl32.lib")


Animation::Animation()
{
	properties.mouseIcon.InitializePropertyWatcher(this, DISPID_ANIM_MOUSEICON);

	SIZEL size = {100, 70};
	AtlPixelToHiMetric(&size, &m_sizeExtent);

	// always create a window, even if the container supports windowless controls
	m_bWindowOnly = TRUE;

	// Microsoft couldn't make it more difficult to detect whether we should use themes or not...
	flags.usingThemes = FALSE;
	if(CTheme::IsThemingSupported() && RunTimeHelper::IsCommCtrl6()) {
		HMODULE hThemeDLL = LoadLibrary(TEXT("uxtheme.dll"));
		if(hThemeDLL != NULL) {
			typedef BOOL WINAPI IsAppThemedFn();
			IsAppThemedFn* pfnIsAppThemed = static_cast<IsAppThemedFn*>(GetProcAddress(hThemeDLL, "IsAppThemed"));
			if(pfnIsAppThemed()) {
				flags.usingThemes = TRUE;
			}
			FreeLibrary(hThemeDLL);
		}
	}
}


//////////////////////////////////////////////////////////////////////
// implementation of ISupportsErrorInfo
STDMETHODIMP Animation::InterfaceSupportsErrorInfo(REFIID interfaceToCheck)
{
	if(InlineIsEqualGUID(IID_IAnimation, interfaceToCheck)) {
		return S_OK;
	}
	return S_FALSE;
}
// implementation of ISupportsErrorInfo
//////////////////////////////////////////////////////////////////////


STDMETHODIMP Animation::GetSizeMax(ULARGE_INTEGER* pSize)
{
	ATLASSERT_POINTER(pSize, ULARGE_INTEGER);
	if(!pSize) {
		return E_POINTER;
	}

	pSize->LowPart = 0;
	pSize->HighPart = 0;
	pSize->QuadPart = sizeof(LONG/*signature*/) + sizeof(LONG/*version*/) + sizeof(DWORD/*atlVersion*/) + sizeof(m_sizeExtent);

	// we've 7 VT_I4 properties...
	pSize->QuadPart += 7 * (sizeof(VARTYPE) + sizeof(LONG));
	// ...and 6 VT_BOOL properties...
	pSize->QuadPart += 6 * (sizeof(VARTYPE) + sizeof(VARIANT_BOOL));

	// ...and 1 VT_DISPATCH property
	pSize->QuadPart += 1 * (sizeof(VARTYPE) + sizeof(CLSID));

	CComPtr<IPersistStreamInit> pStreamInit = NULL;
	if(properties.mouseIcon.pPictureDisp) {
		if(FAILED(properties.mouseIcon.pPictureDisp->QueryInterface(IID_IPersistStream, reinterpret_cast<LPVOID*>(&pStreamInit)))) {
			properties.mouseIcon.pPictureDisp->QueryInterface(IID_IPersistStreamInit, reinterpret_cast<LPVOID*>(&pStreamInit));
		}
	}
	if(pStreamInit) {
		ULARGE_INTEGER tmp = {0};
		pStreamInit->GetSizeMax(&tmp);
		pSize->QuadPart += tmp.QuadPart;
	}

	return S_OK;
}

STDMETHODIMP Animation::Load(LPSTREAM pStream)
{
	ATLASSUME(pStream);
	if(!pStream) {
		return E_POINTER;
	}

	// NOTE: We neither support legacy streams nor streams with a version < 0x0102.

	HRESULT hr = S_OK;
	LONG signature = 0;
	LONG version = 0;
	if(FAILED(hr = pStream->Read(&signature, sizeof(signature), NULL))) {
		return hr;
	}
	if(signature != 0x08080808/*4x AppID*/) {
		// might be a legacy stream, that starts with the ATL version
		if(signature == 0x0900) {
			version = 0x0099;
		} else {
			return E_FAIL;
		}
	}
	//LONG version = 0;
	if(version != 0x0099) {
		if(FAILED(hr = pStream->Read(&version, sizeof(version), NULL))) {
			return hr;
		}
		if(version > 0x0101) {
			return E_FAIL;
		}
	}

	DWORD atlVersion;
	if(version == 0x0099) {
		atlVersion = 0x0900;
	} else {
		if(FAILED(hr = pStream->Read(&atlVersion, sizeof(atlVersion), NULL))) {
			return hr;
		}
	}
	if(atlVersion > _ATL_VER) {
		return E_FAIL;
	}

	if(version != 0x0100) {
		if(FAILED(hr = pStream->Read(&m_sizeExtent, sizeof(m_sizeExtent), NULL))) {
			return hr;
		}
	}

	typedef HRESULT ReadVariantFromStreamFn(__in LPSTREAM pStream, VARTYPE expectedVarType, __inout LPVARIANT pVariant);
	ReadVariantFromStreamFn* pfnReadVariantFromStream = NULL;
	if(version == 0x0100) {
		pfnReadVariantFromStream = ReadVariantFromStream_Legacy;
	} else {
		pfnReadVariantFromStream = ReadVariantFromStream;
	}

	VARIANT propertyValue;
	VariantInit(&propertyValue);

	if(FAILED(hr = pfnReadVariantFromStream(pStream, VT_I4, &propertyValue))) {
		return hr;
	}
	AnimationBackStyleConstants animationBackStyle = static_cast<AnimationBackStyleConstants>(propertyValue.lVal);
	if(FAILED(hr = pfnReadVariantFromStream(pStream, VT_I4, &propertyValue))) {
		return hr;
	}
	AppearanceConstants appearance = static_cast<AppearanceConstants>(propertyValue.lVal);
	if(FAILED(hr = pfnReadVariantFromStream(pStream, VT_BOOL, &propertyValue))) {
		return hr;
	}
	VARIANT_BOOL autoStartReplay = propertyValue.boolVal;
	if(FAILED(hr = pfnReadVariantFromStream(pStream, VT_I4, &propertyValue))) {
		return hr;
	}
	OLE_COLOR backColor = propertyValue.lVal;
	if(FAILED(hr = pfnReadVariantFromStream(pStream, VT_I4, &propertyValue))) {
		return hr;
	}
	BorderStyleConstants borderStyle = static_cast<BorderStyleConstants>(propertyValue.lVal);
	if(FAILED(hr = pfnReadVariantFromStream(pStream, VT_BOOL, &propertyValue))) {
		return hr;
	}
	VARIANT_BOOL centerAnimation = propertyValue.boolVal;
	if(FAILED(hr = pfnReadVariantFromStream(pStream, VT_I4, &propertyValue))) {
		return hr;
	}
	DisabledEventsConstants disabledEvents = static_cast<DisabledEventsConstants>(propertyValue.lVal);
	if(FAILED(hr = pfnReadVariantFromStream(pStream, VT_BOOL, &propertyValue))) {
		return hr;
	}
	VARIANT_BOOL dontRedraw = propertyValue.boolVal;
	if(FAILED(hr = pfnReadVariantFromStream(pStream, VT_BOOL, &propertyValue))) {
		return hr;
	}
	VARIANT_BOOL enabled = propertyValue.boolVal;
	if(FAILED(hr = pfnReadVariantFromStream(pStream, VT_I4, &propertyValue))) {
		return hr;
	}
	LONG hoverTime = propertyValue.lVal;

	VARTYPE vt;
	if(FAILED(hr = pStream->Read(&vt, sizeof(VARTYPE), NULL)) || (vt != VT_DISPATCH)) {
		return hr;
	}
	CComPtr<IPictureDisp> pMouseIcon = NULL;
	if(FAILED(hr = OleLoadFromStream(pStream, IID_IDispatch, reinterpret_cast<LPVOID*>(&pMouseIcon)))) {
		if(hr != REGDB_E_CLASSNOTREG) {
			return S_OK;
		}
	}

	if(FAILED(hr = pfnReadVariantFromStream(pStream, VT_I4, &propertyValue))) {
		return hr;
	}
	MousePointerConstants mousePointer = static_cast<MousePointerConstants>(propertyValue.lVal);
	if(FAILED(hr = pfnReadVariantFromStream(pStream, VT_BOOL, &propertyValue))) {
		return hr;
	}
	VARIANT_BOOL registerForOLEDragDrop = propertyValue.boolVal;
	if(FAILED(hr = pfnReadVariantFromStream(pStream, VT_BOOL, &propertyValue))) {
		return hr;
	}
	VARIANT_BOOL supportOLEDragImages = propertyValue.boolVal;


	hr = put_AnimationBackStyle(animationBackStyle);
	if(FAILED(hr)) {
		return hr;
	}
	hr = put_Appearance(appearance);
	if(FAILED(hr)) {
		return hr;
	}
	hr = put_AutoStartReplay(autoStartReplay);
	if(FAILED(hr)) {
		return hr;
	}
	hr = put_BackColor(backColor);
	if(FAILED(hr)) {
		return hr;
	}
	hr = put_BorderStyle(borderStyle);
	if(FAILED(hr)) {
		return hr;
	}
	hr = put_CenterAnimation(centerAnimation);
	if(FAILED(hr)) {
		return hr;
	}
	hr = put_DisabledEvents(disabledEvents);
	if(FAILED(hr)) {
		return hr;
	}
	hr = put_DontRedraw(dontRedraw);
	if(FAILED(hr)) {
		return hr;
	}
	hr = put_Enabled(enabled);
	if(FAILED(hr)) {
		return hr;
	}
	hr = put_HoverTime(hoverTime);
	if(FAILED(hr)) {
		return hr;
	}
	hr = put_MouseIcon(pMouseIcon);
	if(FAILED(hr)) {
		return hr;
	}
	hr = put_MousePointer(mousePointer);
	if(FAILED(hr)) {
		return hr;
	}
	hr = put_RegisterForOLEDragDrop(registerForOLEDragDrop);
	if(FAILED(hr)) {
		return hr;
	}
	hr = put_SupportOLEDragImages(supportOLEDragImages);
	if(FAILED(hr)) {
		return hr;
	}

	SetDirty(FALSE);
	return S_OK;
}

STDMETHODIMP Animation::Save(LPSTREAM pStream, BOOL clearDirtyFlag)
{
	ATLASSUME(pStream);
	if(!pStream) {
		return E_POINTER;
	}

	HRESULT hr = S_OK;
	LONG signature = 0x08080808/*4x AppID*/;
	if(FAILED(hr = pStream->Write(&signature, sizeof(signature), NULL))) {
		return hr;
	}
	LONG version = 0x0101;
	if(FAILED(hr = pStream->Write(&version, sizeof(version), NULL))) {
		return hr;
	}

	DWORD atlVersion = _ATL_VER;
	if(FAILED(hr = pStream->Write(&atlVersion, sizeof(atlVersion), NULL))) {
		return hr;
	}

	if(FAILED(hr = pStream->Write(&m_sizeExtent, sizeof(m_sizeExtent), NULL))) {
		return hr;
	}

	VARIANT propertyValue;
	VariantInit(&propertyValue);

	propertyValue.vt = VT_I4;
	propertyValue.lVal = properties.animationBackStyle;
	if(FAILED(hr = WriteVariantToStream(pStream, &propertyValue))) {
		return hr;
	}
	propertyValue.lVal = properties.appearance;
	if(FAILED(hr = WriteVariantToStream(pStream, &propertyValue))) {
		return hr;
	}
	propertyValue.vt = VT_BOOL;
	propertyValue.boolVal = BOOL2VARIANTBOOL(properties.autoStartReplay);
	if(FAILED(hr = WriteVariantToStream(pStream, &propertyValue))) {
		return hr;
	}
	propertyValue.vt = VT_I4;
	propertyValue.lVal = properties.backColor;
	if(FAILED(hr = WriteVariantToStream(pStream, &propertyValue))) {
		return hr;
	}
	propertyValue.lVal = properties.borderStyle;
	if(FAILED(hr = WriteVariantToStream(pStream, &propertyValue))) {
		return hr;
	}
	propertyValue.vt = VT_BOOL;
	propertyValue.boolVal = BOOL2VARIANTBOOL(properties.centerAnimation);
	if(FAILED(hr = WriteVariantToStream(pStream, &propertyValue))) {
		return hr;
	}
	propertyValue.vt = VT_I4;
	propertyValue.lVal = properties.disabledEvents;
	if(FAILED(hr = WriteVariantToStream(pStream, &propertyValue))) {
		return hr;
	}
	propertyValue.vt = VT_BOOL;
	propertyValue.boolVal = BOOL2VARIANTBOOL(properties.dontRedraw);
	if(FAILED(hr = WriteVariantToStream(pStream, &propertyValue))) {
		return hr;
	}
	propertyValue.boolVal = BOOL2VARIANTBOOL(properties.enabled);
	if(FAILED(hr = WriteVariantToStream(pStream, &propertyValue))) {
		return hr;
	}
	propertyValue.vt = VT_I4;
	propertyValue.lVal = properties.hoverTime;
	if(FAILED(hr = WriteVariantToStream(pStream, &propertyValue))) {
		return hr;
	}

	CComPtr<IPersistStream> pPersistStream = NULL;
	if(properties.mouseIcon.pPictureDisp) {
		if(FAILED(hr = properties.mouseIcon.pPictureDisp->QueryInterface(IID_IPersistStream, reinterpret_cast<LPVOID*>(&pPersistStream)))) {
			return hr;
		}
	}
	// store some marker
	VARTYPE vt = VT_DISPATCH;
	if(FAILED(hr = pStream->Write(&vt, sizeof(VARTYPE), NULL))) {
		return hr;
	}
	if(pPersistStream) {
		if(FAILED(hr = OleSaveToStream(pPersistStream, pStream))) {
			return hr;
		}
	} else {
		if(FAILED(hr = WriteClassStm(pStream, CLSID_NULL))) {
			return hr;
		}
	}

	propertyValue.lVal = properties.mousePointer;
	if(FAILED(hr = WriteVariantToStream(pStream, &propertyValue))) {
		return hr;
	}
	propertyValue.vt = VT_BOOL;
	propertyValue.boolVal = BOOL2VARIANTBOOL(properties.registerForOLEDragDrop);
	if(FAILED(hr = WriteVariantToStream(pStream, &propertyValue))) {
		return hr;
	}
	propertyValue.boolVal = BOOL2VARIANTBOOL(properties.supportOLEDragImages);
	if(FAILED(hr = WriteVariantToStream(pStream, &propertyValue))) {
		return hr;
	}

	if(clearDirtyFlag) {
		SetDirty(FALSE);
	}
	return S_OK;
}


HWND Animation::Create(HWND hWndParent, ATL::_U_RECT rect/* = NULL*/, LPCTSTR szWindowName/* = NULL*/, DWORD dwStyle/* = 0*/, DWORD dwExStyle/* = 0*/, ATL::_U_MENUorID MenuOrID/* = 0U*/, LPVOID lpCreateParam/* = NULL*/)
{
	INITCOMMONCONTROLSEX data = {0};
	data.dwSize = sizeof(data);
	data.dwICC = ICC_ANIMATE_CLASS;
	InitCommonControlsEx(&data);

	dwStyle = GetStyleBits();
	dwExStyle = GetExStyleBits();
	return CComControl<Animation>::Create(hWndParent, rect, szWindowName, dwStyle, dwExStyle, MenuOrID, lpCreateParam);
}

HRESULT Animation::OnDraw(ATL_DRAWINFO& drawInfo)
{
	if(IsInDesignMode()) {
		CIcon icon;
		icon.LoadIcon(IDI_IDEBACK);
		if(!icon.IsNull()) {
			ICONINFO iconData = {0};
			if(icon.GetIconInfo(&iconData)) {
				BITMAP bitmapData = {0};
				if(GetObject((iconData.hbmColor != NULL ? iconData.hbmColor : iconData.hbmMask), sizeof(bitmapData), &bitmapData)) {
					WTL::CRect boundingRectangle = reinterpret_cast<LPCRECT>(drawInfo.prcBounds);
					WTL::CPoint pt = boundingRectangle.CenterPoint();
					pt.Offset(-bitmapData.bmWidth / 2, -bitmapData.bmHeight / 2);

					HBRUSH hBrushToUseForBackground = NULL;
					if(IsWindow()) {
						CWindow parentWindow = GetParent();
						if(parentWindow.IsWindow()) {
							hBrushToUseForBackground = reinterpret_cast<HBRUSH>(parentWindow.SendMessage(WM_CTLCOLORSTATIC, reinterpret_cast<WPARAM>(drawInfo.hdcDraw), reinterpret_cast<LPARAM>(static_cast<HWND>(*this))));
						} else {
							hBrushToUseForBackground = reinterpret_cast<HBRUSH>(SendMessage(OCM_CTLCOLORSTATIC, reinterpret_cast<WPARAM>(drawInfo.hdcDraw), reinterpret_cast<LPARAM>(static_cast<HWND>(*this))));
						}
					}
					if(!hBrushToUseForBackground) {
						hBrushToUseForBackground = GetSysColorBrush(COLOR_3DFACE);
					}

					FillRect(drawInfo.hdcDraw, &boundingRectangle, hBrushToUseForBackground);
					DrawIconEx(drawInfo.hdcDraw, pt.x, pt.y, icon, 0, 0, 0, NULL, DI_NORMAL);
				}
			}
		}
		return S_OK;
	} else if(IsWindow()) {
		if(flags.animationType != Flags::atAVI) {
			if(flags.animationType == Flags::atGIF) {
				// simply draw what's in the buffers
				BitBlt(drawInfo.hdcDraw, drawInfo.prcBounds->left, drawInfo.prcBounds->top, drawInfo.prcBounds->right - drawInfo.prcBounds->left, drawInfo.prcBounds->bottom - drawInfo.prcBounds->top, gifData.screenWithCurrentFrame.dc, drawInfo.prcBounds->left, drawInfo.prcBounds->top, SRCCOPY);
			} else {
				HBRUSH hBrushToUseForBackground = NULL;
				CWindow parentWindow = GetParent();
				if(parentWindow.IsWindow()) {
					hBrushToUseForBackground = reinterpret_cast<HBRUSH>(parentWindow.SendMessage(WM_CTLCOLORSTATIC, reinterpret_cast<WPARAM>(drawInfo.hdcDraw), reinterpret_cast<LPARAM>(static_cast<HWND>(*this))));
				} else {
					hBrushToUseForBackground = reinterpret_cast<HBRUSH>(SendMessage(OCM_CTLCOLORSTATIC, reinterpret_cast<WPARAM>(drawInfo.hdcDraw), reinterpret_cast<LPARAM>(static_cast<HWND>(*this))));
				}

				FillRect(drawInfo.hdcDraw, reinterpret_cast<LPCRECT>(drawInfo.prcBounds), hBrushToUseForBackground);
			}
		} else {
			PrintClient(drawInfo.hdcDraw, PRF_CHILDREN | PRF_CLIENT | PRF_NONCLIENT);
		}
		return S_OK;
	}
	return CComControl<Animation>::OnDraw(drawInfo);
}

void Animation::OnFinalMessage(HWND /*hWnd*/)
{
	if(dragDropStatus.pDropTargetHelper) {
		dragDropStatus.pDropTargetHelper->Release();
		dragDropStatus.pDropTargetHelper = NULL;
	}
	Release();
}

STDMETHODIMP Animation::IOleObject_SetClientSite(LPOLECLIENTSITE pClientSite)
{
	return CComControl<Animation>::IOleObject_SetClientSite(pClientSite);
}

//////////////////////////////////////////////////////////////////////
// implementation of IDropTarget
STDMETHODIMP Animation::DragEnter(IDataObject* pDataObject, DWORD keyState, POINTL mousePosition, DWORD* pEffect)
{
	// NOTE: pDataObject can be NULL

	if(properties.supportOLEDragImages && !dragDropStatus.pDropTargetHelper) {
		CoCreateInstance(CLSID_DragDropHelper, NULL, CLSCTX_ALL, IID_PPV_ARGS(&dragDropStatus.pDropTargetHelper));
	}

	DROPDESCRIPTION oldDropDescription;
	ZeroMemory(&oldDropDescription, sizeof(DROPDESCRIPTION));
	IDataObject_GetDropDescription(pDataObject, oldDropDescription);

	POINT buffer = {mousePosition.x, mousePosition.y};
	Raise_OLEDragEnter(pDataObject, pEffect, keyState, mousePosition);
	if(dragDropStatus.pDropTargetHelper) {
		dragDropStatus.pDropTargetHelper->DragEnter(*this, pDataObject, &buffer, *pEffect);
	}

	DROPDESCRIPTION newDropDescription;
	ZeroMemory(&newDropDescription, sizeof(DROPDESCRIPTION));
	if(SUCCEEDED(IDataObject_GetDropDescription(pDataObject, newDropDescription)) && memcmp(&oldDropDescription, &newDropDescription, sizeof(DROPDESCRIPTION))) {
		InvalidateDragWindow(pDataObject);
	}
	return S_OK;
}

STDMETHODIMP Animation::DragLeave(void)
{
	Raise_OLEDragLeave();
	if(dragDropStatus.pDropTargetHelper) {
		dragDropStatus.pDropTargetHelper->DragLeave();
		dragDropStatus.pDropTargetHelper->Release();
		dragDropStatus.pDropTargetHelper = NULL;
	}
	return S_OK;
}

STDMETHODIMP Animation::DragOver(DWORD keyState, POINTL mousePosition, DWORD* pEffect)
{
	// NOTE: pDataObject can be NULL

	CComQIPtr<IDataObject> pDataObject = dragDropStatus.pActiveDataObject;
	DROPDESCRIPTION oldDropDescription;
	ZeroMemory(&oldDropDescription, sizeof(DROPDESCRIPTION));
	IDataObject_GetDropDescription(pDataObject, oldDropDescription);

	POINT buffer = {mousePosition.x, mousePosition.y};
	Raise_OLEDragMouseMove(pEffect, keyState, mousePosition);
	if(dragDropStatus.pDropTargetHelper) {
		dragDropStatus.pDropTargetHelper->DragOver(&buffer, *pEffect);
	}

	DROPDESCRIPTION newDropDescription;
	ZeroMemory(&newDropDescription, sizeof(DROPDESCRIPTION));
	if(SUCCEEDED(IDataObject_GetDropDescription(pDataObject, newDropDescription)) && (newDropDescription.type > DROPIMAGE_NONE || memcmp(&oldDropDescription, &newDropDescription, sizeof(DROPDESCRIPTION)))) {
		InvalidateDragWindow(pDataObject);
	}
	return S_OK;
}

STDMETHODIMP Animation::Drop(IDataObject* pDataObject, DWORD keyState, POINTL mousePosition, DWORD* pEffect)
{
	// NOTE: pDataObject can be NULL

	POINT buffer = {mousePosition.x, mousePosition.y};
	dragDropStatus.drop_pDataObject = pDataObject;
	dragDropStatus.drop_mousePosition = buffer;
	dragDropStatus.drop_effect = *pEffect;

	Raise_OLEDragDrop(pDataObject, pEffect, keyState, mousePosition);
	if(dragDropStatus.pDropTargetHelper) {
		dragDropStatus.pDropTargetHelper->Drop(pDataObject, &buffer, *pEffect);
		dragDropStatus.pDropTargetHelper->Release();
		dragDropStatus.pDropTargetHelper = NULL;
	}
	dragDropStatus.drop_pDataObject = NULL;
	return S_OK;
}
// implementation of IDropTarget
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// implementation of ICategorizeProperties
STDMETHODIMP Animation::GetCategoryName(PROPCAT category, LCID /*languageID*/, BSTR* pName)
{
	switch(category) {
		case PROPCAT_Colors:
			*pName = GetResString(IDPC_COLORS).Detach();
			return S_OK;
			break;
		case PROPCAT_DragDrop:
			*pName = GetResString(IDPC_DRAGDROP).Detach();
			return S_OK;
			break;
	}
	return E_FAIL;
}

STDMETHODIMP Animation::MapPropertyToCategory(DISPID property, PROPCAT* pCategory)
{
	if(!pCategory) {
		return E_POINTER;
	}

	switch(property) {
		case DISPID_ANIM_ANIMATIONBACKSTYLE:
		case DISPID_ANIM_APPEARANCE:
		case DISPID_ANIM_BORDERSTYLE:
		case DISPID_ANIM_MOUSEICON:
		case DISPID_ANIM_MOUSEPOINTER:
			*pCategory = PROPCAT_Appearance;
			return S_OK;
			break;
		case DISPID_ANIM_CENTERANIMATION:
		case DISPID_ANIM_DISABLEDEVENTS:
		case DISPID_ANIM_DONTREDRAW:
		case DISPID_ANIM_HOVERTIME:
			*pCategory = PROPCAT_Behavior;
			return S_OK;
			break;
		case DISPID_ANIM_BACKCOLOR:
			*pCategory = PROPCAT_Colors;
			return S_OK;
			break;
		case DISPID_ANIM_APPID:
		case DISPID_ANIM_APPNAME:
		case DISPID_ANIM_APPSHORTNAME:
		case DISPID_ANIM_BUILD:
		case DISPID_ANIM_CHARSET:
		case DISPID_ANIM_HWND:
		case DISPID_ANIM_ISRELEASE:
		case DISPID_ANIM_PROGRAMMER:
		case DISPID_ANIM_TESTER:
		case DISPID_ANIM_VERSION:
			*pCategory = PROPCAT_Data;
			return S_OK;
			break;
		case DISPID_ANIM_REGISTERFOROLEDRAGDROP:
		case DISPID_ANIM_SUPPORTOLEDRAGIMAGES:
			*pCategory = PROPCAT_DragDrop;
			return S_OK;
			break;
		case DISPID_ANIM_ENABLED:
			*pCategory = PROPCAT_Misc;
			return S_OK;
			break;
	}
	return E_FAIL;
}
// implementation of ICategorizeProperties
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// implementation of ICreditsProvider
CAtlString Animation::GetAuthors(void)
{
	CComBSTR buffer;
	get_Programmer(&buffer);
	return CAtlString(buffer);
}

CAtlString Animation::GetHomepage(void)
{
	return TEXT("https://www.TimoSoft-Software.de");
}

CAtlString Animation::GetPaypalLink(void)
{
	return TEXT("https://www.paypal.com/xclick/business=TKunze71216%40gmx.de&item_name=Animation&no_shipping=1&tax=0&currency_code=EUR");
}

CAtlString Animation::GetSpecialThanks(void)
{
	return TEXT("Geoff Chappell, Wine Headquarters");
}

CAtlString Animation::GetThanks(void)
{
	CAtlString ret = TEXT("Google, various newsgroups and mailing lists, many websites,\n");
	ret += TEXT("Heaven Shall Burn, Arch Enemy, Machine Head, Trivium, Deadlock, Draconian, Soulfly, Delain, Lacuna Coil, Ensiferum, Epica, Nightwish, Guns N' Roses and many other musicians");
	return ret;
}

CAtlString Animation::GetVersion(void)
{
	CAtlString ret = TEXT("Version ");
	CComBSTR buffer;
	get_Version(&buffer);
	ret += buffer;
	ret += TEXT(" (");
	get_CharSet(&buffer);
	ret += buffer;
	ret += TEXT(")\nCompilation timestamp: ");
	ret += TEXT(STRTIMESTAMP);
	ret += TEXT("\n");

	VARIANT_BOOL b;
	get_IsRelease(&b);
	if(b == VARIANT_FALSE) {
		ret += TEXT("This version is for debugging only.");
	}

	return ret;
}
// implementation of ICreditsProvider
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// implementation of IPerPropertyBrowsing
STDMETHODIMP Animation::GetDisplayString(DISPID property, BSTR* pDescription)
{
	if(!pDescription) {
		return E_POINTER;
	}

	CComBSTR description;
	HRESULT hr = S_OK;
	switch(property) {
		case DISPID_ANIM_ANIMATIONBACKSTYLE:
			hr = GetDisplayStringForSetting(property, static_cast<DWORD>(properties.animationBackStyle), description);
			break;
		case DISPID_ANIM_APPEARANCE:
			hr = GetDisplayStringForSetting(property, static_cast<DWORD>(properties.appearance), description);
			break;
		case DISPID_ANIM_BORDERSTYLE:
			hr = GetDisplayStringForSetting(property, static_cast<DWORD>(properties.borderStyle), description);
			break;
		case DISPID_ANIM_MOUSEPOINTER:
			hr = GetDisplayStringForSetting(property, static_cast<DWORD>(properties.mousePointer), description);
			break;
		default:
			return IPerPropertyBrowsingImpl<Animation>::GetDisplayString(property, pDescription);
			break;
	}
	if(SUCCEEDED(hr)) {
		*pDescription = description.Detach();
	}

	return *pDescription ? S_OK : E_OUTOFMEMORY;
}

STDMETHODIMP Animation::GetPredefinedStrings(DISPID property, CALPOLESTR* pDescriptions, CADWORD* pCookies)
{
	if(!pDescriptions || !pCookies) {
		return E_POINTER;
	}

	int c = 0;
	switch(property) {
		case DISPID_ANIM_ANIMATIONBACKSTYLE:
		case DISPID_ANIM_BORDERSTYLE:
			c = 2;
			break;
		case DISPID_ANIM_APPEARANCE:
			c = 3;
			break;
		case DISPID_ANIM_MOUSEPOINTER:
			c = 30;
			break;
		default:
			return IPerPropertyBrowsingImpl<Animation>::GetPredefinedStrings(property, pDescriptions, pCookies);
			break;
	}
	pDescriptions->cElems = c;
	pCookies->cElems = c;
	pDescriptions->pElems = static_cast<LPOLESTR*>(CoTaskMemAlloc(pDescriptions->cElems * sizeof(LPOLESTR)));
	pCookies->pElems = static_cast<LPDWORD>(CoTaskMemAlloc(pCookies->cElems * sizeof(DWORD)));

	for(UINT iDescription = 0; iDescription < pDescriptions->cElems; ++iDescription) {
		UINT propertyValue = iDescription;
		if((property == DISPID_ANIM_MOUSEPOINTER) && (iDescription == pDescriptions->cElems - 1)) {
			propertyValue = mpCustom;
		}

		CComBSTR description;
		HRESULT hr = GetDisplayStringForSetting(property, propertyValue, description);
		if(SUCCEEDED(hr)) {
			size_t bufferSize = SysStringLen(description) + 1;
			pDescriptions->pElems[iDescription] = static_cast<LPOLESTR>(CoTaskMemAlloc(bufferSize * sizeof(WCHAR)));
			ATLVERIFY(SUCCEEDED(StringCchCopyW(pDescriptions->pElems[iDescription], bufferSize, description)));
			// simply use the property value as cookie
			pCookies->pElems[iDescription] = propertyValue;
		} else {
			return DISP_E_BADINDEX;
		}
	}
	return S_OK;
}

STDMETHODIMP Animation::GetPredefinedValue(DISPID property, DWORD cookie, VARIANT* pPropertyValue)
{
	switch(property) {
		case DISPID_ANIM_ANIMATIONBACKSTYLE:
		case DISPID_ANIM_APPEARANCE:
		case DISPID_ANIM_BORDERSTYLE:
		case DISPID_ANIM_MOUSEPOINTER:
			VariantInit(pPropertyValue);
			pPropertyValue->vt = VT_I4;
			// we used the property value itself as cookie
			pPropertyValue->lVal = cookie;
			break;
		default:
			return IPerPropertyBrowsingImpl<Animation>::GetPredefinedValue(property, cookie, pPropertyValue);
			break;
	}
	return S_OK;
}

STDMETHODIMP Animation::MapPropertyToPage(DISPID property, CLSID* pPropertyPage)
{
	return IPerPropertyBrowsingImpl<Animation>::MapPropertyToPage(property, pPropertyPage);
}
// implementation of IPerPropertyBrowsing
//////////////////////////////////////////////////////////////////////

HRESULT Animation::GetDisplayStringForSetting(DISPID property, DWORD cookie, CComBSTR& description)
{
	switch(property) {
		case DISPID_ANIM_ANIMATIONBACKSTYLE:
			switch(cookie) {
				case absUseBackColor:
					description = GetResStringWithNumber(IDP_ANIMATIONBACKSTYLEUSEBACKCOLOR, absUseBackColor);
					break;
				case absDefinedByAnimation:
					description = GetResStringWithNumber(IDP_ANIMATIONBACKSTYLEDEFINEDBYANIMATION, absDefinedByAnimation);
					break;
				default:
					return DISP_E_BADINDEX;
					break;
			}
			break;
		case DISPID_ANIM_APPEARANCE:
			switch(cookie) {
				case a2D:
					description = GetResStringWithNumber(IDP_APPEARANCE2D, a2D);
					break;
				case a3D:
					description = GetResStringWithNumber(IDP_APPEARANCE3D, a3D);
					break;
				case a3DLight:
					description = GetResStringWithNumber(IDP_APPEARANCE3DLIGHT, a3DLight);
					break;
				default:
					return DISP_E_BADINDEX;
					break;
			}
			break;
		case DISPID_ANIM_BORDERSTYLE:
			switch(cookie) {
				case bsNone:
					description = GetResStringWithNumber(IDP_BORDERSTYLENONE, bsNone);
					break;
				case bsFixedSingle:
					description = GetResStringWithNumber(IDP_BORDERSTYLEFIXEDSINGLE, bsFixedSingle);
					break;
				default:
					return DISP_E_BADINDEX;
					break;
			}
			break;
		case DISPID_ANIM_MOUSEPOINTER:
			switch(cookie) {
				case mpDefault:
					description = GetResStringWithNumber(IDP_MOUSEPOINTERDEFAULT, mpDefault);
					break;
				case mpArrow:
					description = GetResStringWithNumber(IDP_MOUSEPOINTERARROW, mpArrow);
					break;
				case mpCross:
					description = GetResStringWithNumber(IDP_MOUSEPOINTERCROSS, mpCross);
					break;
				case mpIBeam:
					description = GetResStringWithNumber(IDP_MOUSEPOINTERIBEAM, mpIBeam);
					break;
				case mpIcon:
					description = GetResStringWithNumber(IDP_MOUSEPOINTERICON, mpIcon);
					break;
				case mpSize:
					description = GetResStringWithNumber(IDP_MOUSEPOINTERSIZE, mpSize);
					break;
				case mpSizeNESW:
					description = GetResStringWithNumber(IDP_MOUSEPOINTERSIZENESW, mpSizeNESW);
					break;
				case mpSizeNS:
					description = GetResStringWithNumber(IDP_MOUSEPOINTERSIZENS, mpSizeNS);
					break;
				case mpSizeNWSE:
					description = GetResStringWithNumber(IDP_MOUSEPOINTERSIZENWSE, mpSizeNWSE);
					break;
				case mpSizeEW:
					description = GetResStringWithNumber(IDP_MOUSEPOINTERSIZEEW, mpSizeEW);
					break;
				case mpUpArrow:
					description = GetResStringWithNumber(IDP_MOUSEPOINTERUPARROW, mpUpArrow);
					break;
				case mpHourglass:
					description = GetResStringWithNumber(IDP_MOUSEPOINTERHOURGLASS, mpHourglass);
					break;
				case mpNoDrop:
					description = GetResStringWithNumber(IDP_MOUSEPOINTERNODROP, mpNoDrop);
					break;
				case mpArrowHourglass:
					description = GetResStringWithNumber(IDP_MOUSEPOINTERARROWHOURGLASS, mpArrowHourglass);
					break;
				case mpArrowQuestion:
					description = GetResStringWithNumber(IDP_MOUSEPOINTERARROWQUESTION, mpArrowQuestion);
					break;
				case mpSizeAll:
					description = GetResStringWithNumber(IDP_MOUSEPOINTERSIZEALL, mpSizeAll);
					break;
				case mpHand:
					description = GetResStringWithNumber(IDP_MOUSEPOINTERHAND, mpHand);
					break;
				case mpInsertMedia:
					description = GetResStringWithNumber(IDP_MOUSEPOINTERINSERTMEDIA, mpInsertMedia);
					break;
				case mpScrollAll:
					description = GetResStringWithNumber(IDP_MOUSEPOINTERSCROLLALL, mpScrollAll);
					break;
				case mpScrollN:
					description = GetResStringWithNumber(IDP_MOUSEPOINTERSCROLLN, mpScrollN);
					break;
				case mpScrollNE:
					description = GetResStringWithNumber(IDP_MOUSEPOINTERSCROLLNE, mpScrollNE);
					break;
				case mpScrollE:
					description = GetResStringWithNumber(IDP_MOUSEPOINTERSCROLLE, mpScrollE);
					break;
				case mpScrollSE:
					description = GetResStringWithNumber(IDP_MOUSEPOINTERSCROLLSE, mpScrollSE);
					break;
				case mpScrollS:
					description = GetResStringWithNumber(IDP_MOUSEPOINTERSCROLLS, mpScrollS);
					break;
				case mpScrollSW:
					description = GetResStringWithNumber(IDP_MOUSEPOINTERSCROLLSW, mpScrollSW);
					break;
				case mpScrollW:
					description = GetResStringWithNumber(IDP_MOUSEPOINTERSCROLLW, mpScrollW);
					break;
				case mpScrollNW:
					description = GetResStringWithNumber(IDP_MOUSEPOINTERSCROLLNW, mpScrollNW);
					break;
				case mpScrollNS:
					description = GetResStringWithNumber(IDP_MOUSEPOINTERSCROLLNS, mpScrollNS);
					break;
				case mpScrollEW:
					description = GetResStringWithNumber(IDP_MOUSEPOINTERSCROLLEW, mpScrollEW);
					break;
				case mpCustom:
					description = GetResStringWithNumber(IDP_MOUSEPOINTERCUSTOM, mpCustom);
					break;
				default:
					return DISP_E_BADINDEX;
					break;
			}
			break;
		default:
			return DISP_E_BADINDEX;
			break;
	}

	return S_OK;
}

//////////////////////////////////////////////////////////////////////
// implementation of ISpecifyPropertyPages
STDMETHODIMP Animation::GetPages(CAUUID* pPropertyPages)
{
	if(!pPropertyPages) {
		return E_POINTER;
	}

	pPropertyPages->cElems = 3;
	pPropertyPages->pElems = static_cast<LPGUID>(CoTaskMemAlloc(sizeof(GUID) * pPropertyPages->cElems));
	if(pPropertyPages->pElems) {
		pPropertyPages->pElems[0] = CLSID_CommonProperties;
		pPropertyPages->pElems[1] = CLSID_StockColorPage;
		pPropertyPages->pElems[2] = CLSID_StockPicturePage;
		return S_OK;
	}
	return E_OUTOFMEMORY;
}
// implementation of ISpecifyPropertyPages
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// implementation of IOleObject
STDMETHODIMP Animation::DoVerb(LONG verbID, LPMSG pMessage, IOleClientSite* pActiveSite, LONG reserved, HWND hWndParent, LPCRECT pBoundingRectangle)
{
	switch(verbID) {
		case 1:     // About...
			return DoVerbAbout(hWndParent);
			break;
		default:
			return IOleObjectImpl<Animation>::DoVerb(verbID, pMessage, pActiveSite, reserved, hWndParent, pBoundingRectangle);
			break;
	}
}

STDMETHODIMP Animation::EnumVerbs(IEnumOLEVERB** ppEnumerator)
{
	static OLEVERB oleVerbs[3] = {
	    {OLEIVERB_UIACTIVATE, L"&Edit", 0, OLEVERBATTRIB_NEVERDIRTIES | OLEVERBATTRIB_ONCONTAINERMENU},
	    {OLEIVERB_PROPERTIES, L"&Properties...", 0, OLEVERBATTRIB_ONCONTAINERMENU},
	    {1, L"&About...", 0, OLEVERBATTRIB_NEVERDIRTIES | OLEVERBATTRIB_ONCONTAINERMENU},
	};
	return EnumOLEVERB::CreateInstance(oleVerbs, 3, ppEnumerator);
}
// implementation of IOleObject
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// implementation of IOleControl
STDMETHODIMP Animation::GetControlInfo(LPCONTROLINFO pControlInfo)
{
	ATLASSERT_POINTER(pControlInfo, CONTROLINFO);
	if(!pControlInfo) {
		return E_POINTER;
	}

	// our control can have an accelerator
	pControlInfo->cb = sizeof(CONTROLINFO);
	pControlInfo->hAccel = NULL;
	pControlInfo->cAccel = 0;
	pControlInfo->dwFlags = 0;
	return S_OK;
}
// implementation of IOleControl
//////////////////////////////////////////////////////////////////////

HRESULT Animation::DoVerbAbout(HWND hWndParent)
{
	HRESULT hr = S_OK;
	//hr = OnPreVerbAbout();
	if(SUCCEEDED(hr))	{
		AboutDlg dlg;
		dlg.SetOwner(this);
		dlg.DoModal(hWndParent);
		hr = S_OK;
		//hr = OnPostVerbAbout();
	}
	return hr;
}

HRESULT Animation::OnPropertyObjectChanged(DISPID /*propertyObject*/, DISPID /*objectProperty*/)
{
	return S_OK;
}

HRESULT Animation::OnPropertyObjectRequestEdit(DISPID /*propertyObject*/, DISPID /*objectProperty*/)
{
	return S_OK;
}


STDMETHODIMP Animation::get_AnimationBackStyle(AnimationBackStyleConstants* pValue)
{
	ATLASSERT_POINTER(pValue, AnimationBackStyleConstants);
	if(!pValue) {
		return E_POINTER;
	}

	if(!IsInDesignMode() && IsWindow()) {
		properties.animationBackStyle = ((GetStyle() & ACS_TRANSPARENT) == ACS_TRANSPARENT ? absUseBackColor : absDefinedByAnimation);
	}

	*pValue = properties.animationBackStyle;
	return S_OK;
}

STDMETHODIMP Animation::put_AnimationBackStyle(AnimationBackStyleConstants newValue)
{
	PUTPROPPROLOG(DISPID_ANIM_ANIMATIONBACKSTYLE);
	if(properties.animationBackStyle != newValue) {
		properties.animationBackStyle = newValue;
		SetDirty(TRUE);

		if(IsWindow()) {
			RecreateControlWindow();
		}
		FireOnChanged(DISPID_ANIM_ANIMATIONBACKSTYLE);
	}
	return S_OK;
}

STDMETHODIMP Animation::get_Appearance(AppearanceConstants* pValue)
{
	ATLASSERT_POINTER(pValue, AppearanceConstants);
	if(!pValue) {
		return E_POINTER;
	}

	if(!IsInDesignMode() && IsWindow()) {
		if(GetExStyle() & WS_EX_CLIENTEDGE) {
			properties.appearance = a3D;
		} else if(GetExStyle() & WS_EX_STATICEDGE) {
			properties.appearance = a3DLight;
		} else {
			properties.appearance = a2D;
		}
	}

	*pValue = properties.appearance;
	return S_OK;
}

STDMETHODIMP Animation::put_Appearance(AppearanceConstants newValue)
{
	PUTPROPPROLOG(DISPID_ANIM_APPEARANCE);
	if(properties.appearance != newValue) {
		properties.appearance = newValue;
		SetDirty(TRUE);

		if(IsWindow()) {
			switch(properties.appearance) {
				case a2D:
					ModifyStyleEx(WS_EX_CLIENTEDGE | WS_EX_STATICEDGE, 0, SWP_DRAWFRAME | SWP_FRAMECHANGED);
					break;
				case a3D:
					ModifyStyleEx(WS_EX_STATICEDGE, WS_EX_CLIENTEDGE, SWP_DRAWFRAME | SWP_FRAMECHANGED);
					break;
				case a3DLight:
					ModifyStyleEx(WS_EX_CLIENTEDGE, WS_EX_STATICEDGE, SWP_DRAWFRAME | SWP_FRAMECHANGED);
					break;
			}
			FireViewChange();
		}
		FireOnChanged(DISPID_ANIM_APPEARANCE);
	}
	return S_OK;
}

STDMETHODIMP Animation::get_AppID(SHORT* pValue)
{
	ATLASSERT_POINTER(pValue, SHORT);
	if(!pValue) {
		return E_POINTER;
	}

	*pValue = 8;
	return S_OK;
}

STDMETHODIMP Animation::get_AppName(BSTR* pValue)
{
	ATLASSERT_POINTER(pValue, BSTR);
	if(!pValue) {
		return E_POINTER;
	}

	*pValue = SysAllocString(L"Animation");
	return S_OK;
}

STDMETHODIMP Animation::get_AppShortName(BSTR* pValue)
{
	ATLASSERT_POINTER(pValue, BSTR);
	if(!pValue) {
		return E_POINTER;
	}

	*pValue = SysAllocString(L"Anim");
	return S_OK;
}

STDMETHODIMP Animation::get_AutoStartReplay(VARIANT_BOOL* pValue)
{
	ATLASSERT_POINTER(pValue, VARIANT_BOOL);
	if(!pValue) {
		return E_POINTER;
	}

	if(!IsInDesignMode() && IsWindow()) {
		properties.autoStartReplay = ((GetStyle() & ACS_AUTOPLAY) == ACS_AUTOPLAY);
	}

	*pValue = BOOL2VARIANTBOOL(properties.autoStartReplay);
	return S_OK;
}

STDMETHODIMP Animation::put_AutoStartReplay(VARIANT_BOOL newValue)
{
	PUTPROPPROLOG(DISPID_ANIM_AUTOSTARTREPLAY);
	UINT b = VARIANTBOOL2BOOL(newValue);
	if(properties.autoStartReplay != b) {
		properties.autoStartReplay = b;
		SetDirty(TRUE);

		if(IsWindow()) {
			if(properties.autoStartReplay) {
				ModifyStyle(0, ACS_AUTOPLAY);
			} else {
				ModifyStyle(ACS_AUTOPLAY, 0);
			}
		}
		FireOnChanged(DISPID_ANIM_AUTOSTARTREPLAY);
	}
	return S_OK;
}

STDMETHODIMP Animation::get_BackColor(OLE_COLOR* pValue)
{
	ATLASSERT_POINTER(pValue, OLE_COLOR);
	if(!pValue) {
		return E_POINTER;
	}

	*pValue = properties.backColor;
	return S_OK;
}

STDMETHODIMP Animation::put_BackColor(OLE_COLOR newValue)
{
	PUTPROPPROLOG(DISPID_ANIM_BACKCOLOR);
	if(properties.backColor != newValue) {
		properties.backColor = newValue;
		SetDirty(TRUE);

		if(IsWindow()) {
			if(flags.animationType == Flags::atGIF) {
				InitializeScreenBuffersWithSpecifiedGIFFrame(gifData.currentFrame);
			}
			FireViewChange();
		}
		FireOnChanged(DISPID_ANIM_BACKCOLOR);
	}
	return S_OK;
}

STDMETHODIMP Animation::get_BorderStyle(BorderStyleConstants* pValue)
{
	ATLASSERT_POINTER(pValue, BorderStyleConstants);
	if(!pValue) {
		return E_POINTER;
	}

	if(!IsInDesignMode() && IsWindow()) {
		properties.borderStyle = ((GetStyle() & WS_BORDER) == WS_BORDER ? bsFixedSingle : bsNone);
	}

	*pValue = properties.borderStyle;
	return S_OK;
}

STDMETHODIMP Animation::put_BorderStyle(BorderStyleConstants newValue)
{
	PUTPROPPROLOG(DISPID_ANIM_BORDERSTYLE);
	if(properties.borderStyle != newValue) {
		properties.borderStyle = newValue;
		SetDirty(TRUE);

		if(IsWindow()) {
			switch(properties.borderStyle) {
				case bsNone:
					ModifyStyle(WS_BORDER, 0, SWP_DRAWFRAME | SWP_FRAMECHANGED);
					break;
				case bsFixedSingle:
					ModifyStyle(0, WS_BORDER, SWP_DRAWFRAME | SWP_FRAMECHANGED);
					break;
			}
			FireViewChange();
		}
		FireOnChanged(DISPID_ANIM_BORDERSTYLE);
	}
	return S_OK;
}

STDMETHODIMP Animation::get_Build(LONG* pValue)
{
	ATLASSERT_POINTER(pValue, LONG);
	if(!pValue) {
		return E_POINTER;
	}

	*pValue = VERSION_BUILD;
	return S_OK;
}

STDMETHODIMP Animation::get_CenterAnimation(VARIANT_BOOL* pValue)
{
	ATLASSERT_POINTER(pValue, VARIANT_BOOL);
	if(!pValue) {
		return E_POINTER;
	}

	if(!IsInDesignMode() && IsWindow()) {
		properties.centerAnimation = ((GetStyle() & ACS_CENTER) == ACS_CENTER);
	}

	*pValue = BOOL2VARIANTBOOL(properties.centerAnimation);
	return S_OK;
}

STDMETHODIMP Animation::put_CenterAnimation(VARIANT_BOOL newValue)
{
	PUTPROPPROLOG(DISPID_ANIM_CENTERANIMATION);
	UINT b = VARIANTBOOL2BOOL(newValue);
	if(properties.centerAnimation != b) {
		properties.centerAnimation = b;
		SetDirty(TRUE);

		if(IsWindow()) {
			RecreateControlWindow();
		}
		FireOnChanged(DISPID_ANIM_CENTERANIMATION);
	}
	return S_OK;
}

STDMETHODIMP Animation::get_CharSet(BSTR* pValue)
{
	ATLASSERT_POINTER(pValue, BSTR);
	if(!pValue) {
		return E_POINTER;
	}

	#ifdef UNICODE
		*pValue = SysAllocString(L"Unicode");
	#else
		*pValue = SysAllocString(L"ANSI");
	#endif
	return S_OK;
}

STDMETHODIMP Animation::get_DisabledEvents(DisabledEventsConstants* pValue)
{
	ATLASSERT_POINTER(pValue, DisabledEventsConstants);
	if(!pValue) {
		return E_POINTER;
	}

	*pValue = properties.disabledEvents;
	return S_OK;
}

STDMETHODIMP Animation::put_DisabledEvents(DisabledEventsConstants newValue)
{
	PUTPROPPROLOG(DISPID_ANIM_DISABLEDEVENTS);
	if(properties.disabledEvents != newValue) {
		if((static_cast<long>(properties.disabledEvents) & deMouseEvents) != (static_cast<long>(newValue) & deMouseEvents)) {
			if(IsWindow()) {
				if(static_cast<long>(newValue) & deMouseEvents) {
					// nothing to do
				} else {
					TRACKMOUSEEVENT trackingOptions = {0};
					trackingOptions.cbSize = sizeof(trackingOptions);
					trackingOptions.hwndTrack = *this;
					trackingOptions.dwFlags = TME_HOVER | TME_LEAVE | TME_CANCEL;
					TrackMouseEvent(&trackingOptions);
				}
			}
		}

		properties.disabledEvents = newValue;
		SetDirty(TRUE);
		FireOnChanged(DISPID_ANIM_DISABLEDEVENTS);
	}
	return S_OK;
}

STDMETHODIMP Animation::get_DontRedraw(VARIANT_BOOL* pValue)
{
	ATLASSERT_POINTER(pValue, VARIANT_BOOL);
	if(!pValue) {
		return E_POINTER;
	}

	*pValue = BOOL2VARIANTBOOL(properties.dontRedraw);
	return S_OK;
}

STDMETHODIMP Animation::put_DontRedraw(VARIANT_BOOL newValue)
{
	PUTPROPPROLOG(DISPID_ANIM_DONTREDRAW);
	UINT b = VARIANTBOOL2BOOL(newValue);
	if(properties.dontRedraw != b) {
		properties.dontRedraw = b;
		SetDirty(TRUE);

		if(IsWindow()) {
			SetRedraw(!b);
		}
		FireOnChanged(DISPID_ANIM_DONTREDRAW);
	}
	return S_OK;
}

STDMETHODIMP Animation::get_Enabled(VARIANT_BOOL* pValue)
{
	ATLASSERT_POINTER(pValue, VARIANT_BOOL);
	if(!pValue) {
		return E_POINTER;
	}

	if(!IsInDesignMode() && IsWindow()) {
		properties.enabled = !(GetStyle() & WS_DISABLED);
	}

	*pValue = BOOL2VARIANTBOOL(properties.enabled);
	return S_OK;
}

STDMETHODIMP Animation::put_Enabled(VARIANT_BOOL newValue)
{
	PUTPROPPROLOG(DISPID_ANIM_ENABLED);
	UINT b = VARIANTBOOL2BOOL(newValue);
	if(properties.enabled != b) {
		properties.enabled = b;
		SetDirty(TRUE);

		if(IsWindow()) {
			EnableWindow(properties.enabled);
			FireViewChange();
		}

		if(!properties.enabled) {
			IOleInPlaceObject_UIDeactivate();
		}

		FireOnChanged(DISPID_ANIM_ENABLED);
	}
	return S_OK;
}

STDMETHODIMP Animation::get_HoverTime(LONG* pValue)
{
	ATLASSERT_POINTER(pValue, LONG);
	if(!pValue) {
		return E_POINTER;
	}

	*pValue = properties.hoverTime;
	return S_OK;
}

STDMETHODIMP Animation::put_HoverTime(LONG newValue)
{
	PUTPROPPROLOG(DISPID_ANIM_HOVERTIME);
	if((newValue < 0) && (newValue != -1)) {
		// invalid value - raise VB runtime error 380
		return MAKE_HRESULT(1, FACILITY_WINDOWS | FACILITY_DISPATCH, 380);
	}

	if(properties.hoverTime != newValue) {
		properties.hoverTime = newValue;
		SetDirty(TRUE);
		FireOnChanged(DISPID_ANIM_HOVERTIME);
	}
	return S_OK;
}

STDMETHODIMP Animation::get_hWnd(OLE_HANDLE* pValue)
{
	ATLASSERT_POINTER(pValue, OLE_HANDLE);
	if(!pValue) {
		return E_POINTER;
	}

	*pValue = HandleToLong(static_cast<HWND>(*this));
	return S_OK;
}

STDMETHODIMP Animation::get_IsPlaying(VARIANT_BOOL* pValue)
{
	ATLASSERT_POINTER(pValue, VARIANT_BOOL);
	if(!pValue) {
		return E_POINTER;
	}

	if(IsWindow()) {
		switch(flags.animationType) {
			case Flags::atAVI:
				if(IsComctl32Version610OrNewer()) {
					*pValue = BOOL2VARIANTBOOL(SendMessage(ACM_ISPLAYING, 0, 0));
				} else {
					*pValue = BOOL2VARIANTBOOL(flags.isPlayingAVI);
				}
				return S_OK;
				break;
			case Flags::atGIF:
				*pValue = BOOL2VARIANTBOOL(gifData.isPlaying);
				return S_OK;
				break;
		}
	}
	return E_FAIL;
}

STDMETHODIMP Animation::get_IsRelease(VARIANT_BOOL* pValue)
{
	ATLASSERT_POINTER(pValue, VARIANT_BOOL);
	if(!pValue) {
		return E_POINTER;
	}

	#ifdef NDEBUG
		*pValue = VARIANT_TRUE;
	#else
		*pValue = VARIANT_FALSE;
	#endif
	return S_OK;
}

STDMETHODIMP Animation::get_MouseIcon(IPictureDisp** ppMouseIcon)
{
	ATLASSERT_POINTER(ppMouseIcon, IPictureDisp*);
	if(!ppMouseIcon) {
		return E_POINTER;
	}

	if(*ppMouseIcon) {
		(*ppMouseIcon)->Release();
		*ppMouseIcon = NULL;
	}
	if(properties.mouseIcon.pPictureDisp) {
		properties.mouseIcon.pPictureDisp->QueryInterface(IID_IPictureDisp, reinterpret_cast<LPVOID*>(ppMouseIcon));
	}
	return S_OK;
}

STDMETHODIMP Animation::put_MouseIcon(IPictureDisp* pNewMouseIcon)
{
	PUTPROPPROLOG(DISPID_ANIM_MOUSEICON);
	if(properties.mouseIcon.pPictureDisp != pNewMouseIcon) {
		properties.mouseIcon.StopWatching();
		if(properties.mouseIcon.pPictureDisp) {
			properties.mouseIcon.pPictureDisp->Release();
			properties.mouseIcon.pPictureDisp = NULL;
		}
		if(pNewMouseIcon) {
			// clone the picture by storing it into a stream
			CComQIPtr<IPersistStream, &IID_IPersistStream> pPersistStream(pNewMouseIcon);
			if(pPersistStream) {
				ULARGE_INTEGER pictureSize = {0};
				pPersistStream->GetSizeMax(&pictureSize);
				HGLOBAL hGlobalMem = GlobalAlloc(GHND, pictureSize.LowPart);
				if(hGlobalMem) {
					CComPtr<IStream> pStream = NULL;
					CreateStreamOnHGlobal(hGlobalMem, TRUE, &pStream);
					if(pStream) {
						if(SUCCEEDED(pPersistStream->Save(pStream, FALSE))) {
							LARGE_INTEGER startPosition = {0};
							pStream->Seek(startPosition, STREAM_SEEK_SET, NULL);
							OleLoadPicture(pStream, startPosition.LowPart, FALSE, IID_IPictureDisp, reinterpret_cast<LPVOID*>(&properties.mouseIcon.pPictureDisp));
						}
						pStream.Release();
					}
					GlobalFree(hGlobalMem);
				}
			}
		}
		properties.mouseIcon.StartWatching();
	}

	SetDirty(TRUE);
	FireOnChanged(DISPID_ANIM_MOUSEICON);
	return S_OK;
}

STDMETHODIMP Animation::putref_MouseIcon(IPictureDisp* pNewMouseIcon)
{
	PUTPROPPROLOG(DISPID_ANIM_MOUSEICON);
	if(properties.mouseIcon.pPictureDisp != pNewMouseIcon) {
		properties.mouseIcon.StopWatching();
		if(properties.mouseIcon.pPictureDisp) {
			properties.mouseIcon.pPictureDisp->Release();
			properties.mouseIcon.pPictureDisp = NULL;
		}
		if(pNewMouseIcon) {
			pNewMouseIcon->QueryInterface(IID_IPictureDisp, reinterpret_cast<LPVOID*>(&properties.mouseIcon.pPictureDisp));
		}
		properties.mouseIcon.StartWatching();
	} else if(pNewMouseIcon) {
		pNewMouseIcon->AddRef();
	}

	SetDirty(TRUE);
	FireOnChanged(DISPID_ANIM_MOUSEICON);
	return S_OK;
}

STDMETHODIMP Animation::get_MousePointer(MousePointerConstants* pValue)
{
	ATLASSERT_POINTER(pValue, MousePointerConstants);
	if(!pValue) {
		return E_POINTER;
	}

	*pValue = properties.mousePointer;
	return S_OK;
}

STDMETHODIMP Animation::put_MousePointer(MousePointerConstants newValue)
{
	PUTPROPPROLOG(DISPID_ANIM_MOUSEPOINTER);
	if(properties.mousePointer != newValue) {
		properties.mousePointer = newValue;
		SetDirty(TRUE);
		FireOnChanged(DISPID_ANIM_MOUSEPOINTER);
	}
	return S_OK;
}

STDMETHODIMP Animation::get_Programmer(BSTR* pValue)
{
	ATLASSERT_POINTER(pValue, BSTR);
	if(!pValue) {
		return E_POINTER;
	}

	*pValue = SysAllocString(L"Timo \"TimoSoft\" Kunze");
	return S_OK;
}

STDMETHODIMP Animation::get_RegisterForOLEDragDrop(VARIANT_BOOL* pValue)
{
	ATLASSERT_POINTER(pValue, VARIANT_BOOL);
	if(!pValue) {
		return E_POINTER;
	}

	*pValue = BOOL2VARIANTBOOL(properties.registerForOLEDragDrop);
	return S_OK;
}

STDMETHODIMP Animation::put_RegisterForOLEDragDrop(VARIANT_BOOL newValue)
{
	PUTPROPPROLOG(DISPID_ANIM_REGISTERFOROLEDRAGDROP);
	UINT b = VARIANTBOOL2BOOL(newValue);
	if(properties.registerForOLEDragDrop != b) {
		properties.registerForOLEDragDrop = b;
		SetDirty(TRUE);

		if(IsWindow()) {
			if(properties.registerForOLEDragDrop) {
				ATLVERIFY(RegisterDragDrop(*this, static_cast<IDropTarget*>(this)) == S_OK);
			} else {
				ATLVERIFY(RevokeDragDrop(*this) == S_OK);
			}
		}
		FireOnChanged(DISPID_ANIM_REGISTERFOROLEDRAGDROP);
	}
	return S_OK;
}

STDMETHODIMP Animation::get_SupportOLEDragImages(VARIANT_BOOL* pValue)
{
	ATLASSERT_POINTER(pValue, VARIANT_BOOL);
	if(!pValue) {
		return E_POINTER;
	}

	*pValue = BOOL2VARIANTBOOL(properties.supportOLEDragImages);
	return S_OK;
}

STDMETHODIMP Animation::put_SupportOLEDragImages(VARIANT_BOOL newValue)
{
	PUTPROPPROLOG(DISPID_ANIM_SUPPORTOLEDRAGIMAGES);
	UINT b = VARIANTBOOL2BOOL(newValue);
	if(properties.supportOLEDragImages != b) {
		properties.supportOLEDragImages = b;
		SetDirty(TRUE);
		FireOnChanged(DISPID_ANIM_SUPPORTOLEDRAGIMAGES);
	}
	return S_OK;
}

STDMETHODIMP Animation::get_Tester(BSTR* pValue)
{
	ATLASSERT_POINTER(pValue, BSTR);
	if(!pValue) {
		return E_POINTER;
	}

	*pValue = SysAllocString(L"Timo \"TimoSoft\" Kunze");
	return S_OK;
}

STDMETHODIMP Animation::get_Version(BSTR* pValue)
{
	ATLASSERT_POINTER(pValue, BSTR);
	if(!pValue) {
		return E_POINTER;
	}

	TCHAR pBuffer[50];
	ATLVERIFY(SUCCEEDED(StringCbPrintf(pBuffer, 50 * sizeof(TCHAR), TEXT("%i.%i.%i.%i"), VERSION_MAJOR, VERSION_MINOR, VERSION_REVISION1, VERSION_BUILD)));
	*pValue = CComBSTR(pBuffer);
	return S_OK;
}

STDMETHODIMP Animation::About(void)
{
	AboutDlg dlg;
	dlg.SetOwner(this);
	dlg.DoModal();
	return S_OK;
}

STDMETHODIMP Animation::CloseAnimation(void)
{
	if(IsWindow()) {
		switch(flags.animationType) {
			case Flags::atAVI:
				SendMessage(ACM_OPEN, 0, 0);
				break;
			case Flags::atGIF:
				gifData.ReleaseData();
				break;
		}
		flags.animationType = Flags::atNone;
		Invalidate();
		return S_OK;
	}
	return E_FAIL;
}

STDMETHODIMP Animation::DisplayFrame(LONG frameNumber, VARIANT_BOOL* pSuccess)
{
	return StartReplay(frameNumber, frameNumber, 1, pSuccess);
}

STDMETHODIMP Animation::FinishOLEDragDrop(void)
{
	if(dragDropStatus.pDropTargetHelper && dragDropStatus.drop_pDataObject) {
		dragDropStatus.pDropTargetHelper->Drop(dragDropStatus.drop_pDataObject, &dragDropStatus.drop_mousePosition, dragDropStatus.drop_effect);
		dragDropStatus.pDropTargetHelper->Release();
		dragDropStatus.pDropTargetHelper = NULL;
		return S_OK;
	}
	// Can't perform requested operation - raise VB runtime error 17
	return MAKE_HRESULT(1, FACILITY_WINDOWS | FACILITY_DISPATCH, 17);
}

STDMETHODIMP Animation::LoadSettingsFromFile(BSTR file, VARIANT_BOOL* pSucceeded)
{
	ATLASSERT_POINTER(pSucceeded, VARIANT_BOOL);
	if(!pSucceeded) {
		return E_POINTER;
	}
	*pSucceeded = VARIANT_FALSE;

	// open the file
	COLE2T converter(file);
	LPTSTR pFilePath = converter;
	CComPtr<IStream> pStream = NULL;
	HRESULT hr = SHCreateStreamOnFile(pFilePath, STGM_READ | STGM_SHARE_DENY_WRITE, &pStream);
	if(SUCCEEDED(hr) && pStream) {
		// read settings
		if(Load(pStream) == S_OK) {
			*pSucceeded = VARIANT_TRUE;
		}
	}
	return S_OK;
}

STDMETHODIMP Animation::OpenAnimationFromFile(BSTR filePath, VARIANT_BOOL* pSuccess)
{
	ATLASSERT_POINTER(pSuccess, VARIANT_BOOL);
	if(!pSuccess) {
		return E_POINTER;
	}

	if(IsWindow()) {
		COLE2T converter(filePath);
		LPTSTR pFilePath = converter;

		CComPtr<IStream> pStream = NULL;
		HRESULT hr = SHCreateStreamOnFile(pFilePath, STGM_READ | STGM_SHARE_DENY_WRITE, &pStream);
		if(SUCCEEDED(hr) && pStream) {
			// check signature
			CHAR signature[6] = {'\0'};
			if(SUCCEEDED(pStream->Read(signature, 6, NULL))) {
				if((memcmp(signature, "GIF87a", 6) == 0) || (memcmp(signature, "GIF89a", 6) == 0)) {
					// a GIF file - close the current animation and open the GIF animation
					CloseAnimation();
					*pSuccess = BOOL2VARIANTBOOL(LoadGIF(pFilePath) == S_OK);
					if(*pSuccess != VARIANT_FALSE) {
						if(GetStyle() & ACS_AUTOPLAY) {
							VARIANT_BOOL dummy;
							StartReplay(0, -1, -2, &dummy);
						} else {
							// display the first frame
							VARIANT_BOOL dummy;
							DisplayFrame(0, &dummy);
						}
					}
					return S_OK;
				} else {
					// assume an AVI file
					*pSuccess = BOOL2VARIANTBOOL(SendMessage(ACM_OPEN, 0, reinterpret_cast<LPARAM>(pFilePath)));
					return S_OK;
				}
			}
		}
	}
	return E_FAIL;
}

STDMETHODIMP Animation::OpenAnimationFromResource(LONG hModule, LONG resourceID, BSTR resourceTypeName, VARIANT_BOOL* pSuccess)
{
	ATLASSERT_POINTER(pSuccess, VARIANT_BOOL);
	if(!pSuccess) {
		return E_POINTER;
	}

	if(IsWindow()) {
		COLE2T converter(resourceTypeName);
		if(lstrcmp(converter, TEXT("")) == 0) {
			// try to load it as an AVI animation
			*pSuccess = BOOL2VARIANTBOOL(SendMessage(ACM_OPEN, hModule, reinterpret_cast<LPARAM>(MAKEINTRESOURCE(resourceID))));
			return S_OK;
		} else {
			// try to load it as a GIF animation
			*pSuccess = SUCCEEDED(LoadGIF(static_cast<HMODULE>(LongToHandle(hModule)), resourceID, converter));
			if(*pSuccess != VARIANT_FALSE) {
				if(GetStyle() & ACS_AUTOPLAY) {
					VARIANT_BOOL dummy;
					StartReplay(0, -1, -2, &dummy);
				} else {
					// display the first frame
					VARIANT_BOOL dummy;
					DisplayFrame(0, &dummy);
				}
			}
			return S_OK;
		}
	}
	return E_FAIL;
}

STDMETHODIMP Animation::Refresh(void)
{
	if(IsWindow()) {
		Invalidate();
		UpdateWindow();
	}
	return S_OK;
}

STDMETHODIMP Animation::SaveSettingsToFile(BSTR file, VARIANT_BOOL* pSucceeded)
{
	ATLASSERT_POINTER(pSucceeded, VARIANT_BOOL);
	if(!pSucceeded) {
		return E_POINTER;
	}
	*pSucceeded = VARIANT_FALSE;

	// create the file
	COLE2T converter(file);
	LPTSTR pFilePath = converter;
	CComPtr<IStream> pStream = NULL;
	HRESULT hr = SHCreateStreamOnFile(pFilePath, STGM_CREATE | STGM_WRITE | STGM_SHARE_DENY_WRITE, &pStream);
	if(SUCCEEDED(hr) && pStream) {
		// write settings
		if(Save(pStream, FALSE) == S_OK) {
			if(FAILED(pStream->Commit(STGC_DEFAULT))) {
				return S_OK;
			}
			*pSucceeded = VARIANT_TRUE;
		}
	}
	return S_OK;
}

STDMETHODIMP Animation::StartReplay(LONG startFrame/* = 0*/, LONG endFrame/* = -1*/, LONG repeats/* = -2*/, VARIANT_BOOL* pSuccess/* = NULL*/)
{
	ATLASSERT_POINTER(pSuccess, VARIANT_BOOL);
	if(!pSuccess) {
		return E_POINTER;
	}

	if(IsWindow()) {
		switch(flags.animationType) {
			case Flags::atAVI:
				*pSuccess = BOOL2VARIANTBOOL(SendMessage(ACM_PLAY, repeats, MAKELPARAM(startFrame, endFrame)));
				break;
			case Flags::atGIF: {
				VARIANT_BOOL dummy;
				StopReplay(&dummy);

				gifData.startFrame = startFrame;
				#ifdef USE_STL
					gifData.endFrame = (endFrame < 0 ? static_cast<int>(gifData.frames.size()) - 1 : endFrame);
				#else
					gifData.endFrame = (endFrame < 0 ? static_cast<int>(gifData.frames.GetCount()) - 1 : endFrame);
				#endif
				gifData.numberOfLoops = (repeats == -2 ? gifData.recommendedNumberOfLoops : repeats);
				gifData.currentFrame = gifData.startFrame;
				gifData.currentLoop = 1;
				SetIsPlayingGIFFlag(gifData.numberOfLoops != 0);

				InitializeScreenBuffersWithSpecifiedGIFFrame(gifData.startFrame);

				// update the screen
				Invalidate();
				if(gifData.frames[gifData.currentFrame]->delayTime > 0) {
					SetTimer(timers.ID_DRAWGIFFRAME, gifData.frames[gifData.currentFrame]->delayTime);
				}
				*pSuccess = VARIANT_TRUE;
				break;
			}
		}
		return S_OK;
	}
	return E_FAIL;
}

STDMETHODIMP Animation::StopReplay(VARIANT_BOOL* pSuccess)
{
	ATLASSERT_POINTER(pSuccess, VARIANT_BOOL);
	if(!pSuccess) {
		return E_POINTER;
	}

	if(IsWindow()) {
		switch(flags.animationType) {
			case Flags::atAVI:
				*pSuccess = BOOL2VARIANTBOOL(SendMessage(ACM_STOP, 0, 0));
				break;
			case Flags::atGIF:
				KillTimer(timers.ID_DRAWGIFFRAME);
				SetIsPlayingGIFFlag(FALSE);
				*pSuccess = VARIANT_TRUE;
				break;
		}
		return S_OK;
	}
	return E_FAIL;
}


LRESULT Animation::OnContextMenu(UINT /*message*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*wasHandled*/)
{
	POINT mousePosition = {GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
	if((mousePosition.x != -1) && (mousePosition.y != -1)) {
		ScreenToClient(&mousePosition);
	}

	SHORT button = 0;
	SHORT shift = 0;
	WPARAM2BUTTONANDSHIFT(-1, button, shift);
	Raise_ContextMenu(button, shift, mousePosition.x, mousePosition.y);
	return 0;
}

LRESULT Animation::OnCreate(UINT message, WPARAM wParam, LPARAM lParam, BOOL& /*wasHandled*/)
{
	LRESULT lr = DefWindowProc(message, wParam, lParam);

	if(*this) {
		// this will keep the object alive if the client destroys the control window in an event handler
		AddRef();

		Raise_RecreatedControlWindow(HandleToLong(static_cast<HWND>(*this)));
	}
	return lr;
}

LRESULT Animation::OnDestroy(UINT /*message*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& wasHandled)
{
	Raise_DestroyedControlWindow(HandleToLong(static_cast<HWND>(*this)));

	wasHandled = FALSE;
	return 0;
}

LRESULT Animation::OnLButtonDown(UINT /*message*/, WPARAM wParam, LPARAM lParam, BOOL& wasHandled)
{
	wasHandled = FALSE;

	SHORT button = 0;
	SHORT shift = 0;
	WPARAM2BUTTONANDSHIFT(wParam, button, shift);
	button = 1/*MouseButtonConstants.vbLeftButton*/;
	Raise_MouseDown(button, shift, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

	return 0;
}

LRESULT Animation::OnLButtonUp(UINT /*message*/, WPARAM wParam, LPARAM lParam, BOOL& wasHandled)
{
	wasHandled = FALSE;

	SHORT button = 0;
	SHORT shift = 0;
	WPARAM2BUTTONANDSHIFT(wParam, button, shift);
	button = 1/*MouseButtonConstants.vbLeftButton*/;
	Raise_MouseUp(button, shift, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

	return 0;
}

LRESULT Animation::OnMButtonDown(UINT /*message*/, WPARAM wParam, LPARAM lParam, BOOL& wasHandled)
{
	wasHandled = FALSE;

	SHORT button = 0;
	SHORT shift = 0;
	WPARAM2BUTTONANDSHIFT(wParam, button, shift);
	button = 4/*MouseButtonConstants.vbMiddleButton*/;
	Raise_MouseDown(button, shift, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

	return 0;
}

LRESULT Animation::OnMButtonUp(UINT /*message*/, WPARAM wParam, LPARAM lParam, BOOL& wasHandled)
{
	wasHandled = FALSE;

	SHORT button = 0;
	SHORT shift = 0;
	WPARAM2BUTTONANDSHIFT(wParam, button, shift);
	button = 4/*MouseButtonConstants.vbMiddleButton*/;
	Raise_MouseUp(button, shift, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

	return 0;
}

LRESULT Animation::OnMouseActivate(UINT /*message*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& wasHandled)
{
	BOOL inDesignMode = IsInDesignMode();
	if(!inDesignMode) {
		TCHAR pBuffer[200];
		ZeroMemory(pBuffer, 200 * sizeof(TCHAR));
		GetModuleFileName(NULL, pBuffer, 200);
		PathStripPath(pBuffer);
		if(lstrcmpi(pBuffer, TEXT("vb6.exe")) == 0) {
			HWND hWnd = GetParent();
			while(hWnd) {
				if(GetClassName(hWnd, pBuffer, 200) && lstrcmpi(pBuffer, TEXT("DesignerWindow")) == 0) {
					hWnd = ::GetParent(hWnd);
					if(hWnd && GetClassName(hWnd, pBuffer, 200) && lstrcmpi(pBuffer, TEXT("MDIClient")) == 0) {
						hWnd = ::GetParent(hWnd);
						if(hWnd && GetClassName(hWnd, pBuffer, 200) && lstrcmpi(pBuffer, TEXT("wndclass_desked_gsk")) == 0) {
							inDesignMode = TRUE;
						}
					}
					break;
				}
				hWnd = ::GetParent(hWnd);
			}
		}
	}
	if(!inDesignMode) {
		DWORD position = GetMessagePos();
		POINT mousePosition = {GET_X_LPARAM(position), GET_Y_LPARAM(position)};
		if(WindowFromPoint(mousePosition) == *this) {
			ScreenToClient(&mousePosition);
			SHORT button = 0;
			SHORT shift = 0;
			WPARAM2BUTTONANDSHIFT(-1, button, shift);
			if(HIWORD(lParam) == WM_LBUTTONDOWN) {
				button = 1/*MouseButtonConstants.vbLeftButton*/;
				Raise_MouseDown(button, shift, mousePosition.x, mousePosition.y);
			} else if(HIWORD(lParam) == WM_MBUTTONDOWN) {
				button = 4/*MouseButtonConstants.vbMiddleButton*/;
				Raise_MouseDown(button, shift, mousePosition.x, mousePosition.y);
			} else if(HIWORD(lParam) == WM_RBUTTONDOWN) {
				button = 2/*MouseButtonConstants.vbRightButton*/;
				Raise_MouseDown(button, shift, mousePosition.x, mousePosition.y);
			} else if(HIWORD(lParam) == WM_XBUTTONDOWN) {
				Raise_MouseDown(button, shift, mousePosition.x, mousePosition.y);
			}
			return MA_NOACTIVATEANDEAT;
		}
	}

	wasHandled = FALSE;
	return 0;
}

LRESULT Animation::OnMouseHover(UINT /*message*/, WPARAM wParam, LPARAM lParam, BOOL& wasHandled)
{
	wasHandled = FALSE;

	SHORT button = 0;
	SHORT shift = 0;
	WPARAM2BUTTONANDSHIFT(wParam, button, shift);
	Raise_MouseHover(button, shift, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

	return 0;
}

LRESULT Animation::OnMouseLeave(UINT /*message*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& wasHandled)
{
	wasHandled = FALSE;

	SHORT button = 0;
	SHORT shift = 0;
	WPARAM2BUTTONANDSHIFT(-1, button, shift);
	Raise_MouseLeave(button, shift, mouseStatus.lastPosition.x, mouseStatus.lastPosition.y);

	return 0;
}

LRESULT Animation::OnMouseMove(UINT /*message*/, WPARAM wParam, LPARAM lParam, BOOL& wasHandled)
{
	wasHandled = FALSE;

	if(!(properties.disabledEvents & deMouseEvents)) {
		SHORT button = 0;
		SHORT shift = 0;
		WPARAM2BUTTONANDSHIFT(wParam, button, shift);
		Raise_MouseMove(button, shift, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	} else if(!mouseStatus.enteredControl) {
		mouseStatus.EnterControl();
	}

	return 0;
}

LRESULT Animation::OnMouseWheel(UINT message, WPARAM wParam, LPARAM lParam, BOOL& wasHandled)
{
	wasHandled = FALSE;

	if(!(properties.disabledEvents & deMouseEvents)) {
		SHORT button = 0;
		SHORT shift = 0;
		POINT mousePosition = {GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
		if(message == WM_MOUSEHWHEEL) {
			// wParam and lParam seem to be 0
			WPARAM2BUTTONANDSHIFT(-1, button, shift);
			GetCursorPos(&mousePosition);
		} else {
			WPARAM2BUTTONANDSHIFT(GET_KEYSTATE_WPARAM(wParam), button, shift);
		}
		ScreenToClient(&mousePosition);
		//Raise_MouseWheel(button, shift, mousePosition.x, mousePosition.y, message == WM_MOUSEHWHEEL ? saHorizontal : saVertical, GET_WHEEL_DELTA_WPARAM(wParam));
	} else if(!mouseStatus.enteredControl) {
		//mouseStatus.EnterControl();
	}

	return 0;
}

LRESULT Animation::OnNCHitTest(UINT /*message*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*wasHandled*/)
{
	return HTCLIENT;
}

LRESULT Animation::OnRButtonDown(UINT /*message*/, WPARAM wParam, LPARAM lParam, BOOL& wasHandled)
{
	wasHandled = FALSE;

	SHORT button = 0;
	SHORT shift = 0;
	WPARAM2BUTTONANDSHIFT(wParam, button, shift);
	button = 2/*MouseButtonConstants.vbRightButton*/;
	Raise_MouseDown(button, shift, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

	return 0;
}

LRESULT Animation::OnRButtonUp(UINT /*message*/, WPARAM wParam, LPARAM lParam, BOOL& wasHandled)
{
	wasHandled = FALSE;

	SHORT button = 0;
	SHORT shift = 0;
	WPARAM2BUTTONANDSHIFT(wParam, button, shift);
	button = 2/*MouseButtonConstants.vbRightButton*/;
	Raise_MouseUp(button, shift, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

	return 0;
}

LRESULT Animation::OnSetCursor(UINT /*message*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& wasHandled)
{
	HCURSOR hCursor = NULL;
	BOOL setCursor = FALSE;

	// Are we really over the control?
	WTL::CRect clientArea;
	GetClientRect(&clientArea);
	ClientToScreen(&clientArea);
	DWORD position = GetMessagePos();
	POINT mousePosition = {GET_X_LPARAM(position), GET_Y_LPARAM(position)};
	if(clientArea.PtInRect(mousePosition)) {
		// maybe the control is overlapped by a foreign window
		if(WindowFromPoint(mousePosition) == *this) {
			setCursor = TRUE;
		}
	}

	if(setCursor) {
		if(properties.mousePointer == mpCustom) {
			if(properties.mouseIcon.pPictureDisp) {
				CComQIPtr<IPicture, &IID_IPicture> pPicture(properties.mouseIcon.pPictureDisp);
				if(pPicture) {
					OLE_HANDLE h = NULL;
					pPicture->get_Handle(&h);
					hCursor = static_cast<HCURSOR>(LongToHandle(h));
				}
			}
		} else {
			hCursor = MousePointerConst2hCursor(properties.mousePointer);
		}

		if(hCursor) {
			SetCursor(hCursor);
			return TRUE;
		}
	}

	wasHandled = FALSE;
	return FALSE;
}

LRESULT Animation::OnSetRedraw(UINT message, WPARAM wParam, LPARAM lParam, BOOL& /*wasHandled*/)
{
	if(lParam == 71216) {
		// the message was sent by ourselves
		lParam = 0;
		if(wParam) {
			// We're gonna activate redrawing - does the client allow this?
			if(properties.dontRedraw) {
				// no, so eat this message
				return 0;
			}
		}
	} else {
		// TODO: Should we really do this?
		properties.dontRedraw = !wParam;
	}

	return DefWindowProc(message, wParam, lParam);
}

LRESULT Animation::OnThemeChanged(UINT /*message*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& wasHandled)
{
	// Microsoft couldn't make it more difficult to detect whether we should use themes or not...
	flags.usingThemes = FALSE;
	if(CTheme::IsThemingSupported() && RunTimeHelper::IsCommCtrl6()) {
		HMODULE hThemeDLL = LoadLibrary(TEXT("uxtheme.dll"));
		if(hThemeDLL != NULL) {
			typedef BOOL WINAPI IsAppThemedFn();
			IsAppThemedFn* pfnIsAppThemed = static_cast<IsAppThemedFn*>(GetProcAddress(hThemeDLL, "IsAppThemed"));
			if(pfnIsAppThemed()) {
				flags.usingThemes = TRUE;
			}
			FreeLibrary(hThemeDLL);
		}
	}

	wasHandled = FALSE;
	return 0;
}

LRESULT Animation::OnTimer(UINT /*message*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& wasHandled)
{
	switch(wParam) {
		case timers.ID_REDRAW:
			if(IsWindowVisible()) {
				KillTimer(timers.ID_REDRAW);
				SetRedraw(!properties.dontRedraw);
			} else {
				// wait... (this fixes visibility problems if another control displays a nag screen)
			}
			break;

		case timers.ID_DRAWGIFFRAME: {
			KillTimer(timers.ID_DRAWGIFFRAME);

			if(gifData.isPlaying) {
				// prepare next frame
				if((gifData.numberOfLoops < 0) || (gifData.currentLoop <= gifData.numberOfLoops)) {
					if(gifData.currentFrame < gifData.endFrame) {
						++gifData.currentFrame;
					} else if(gifData.currentLoop == gifData.numberOfLoops) {
						// last frame in last loop - stop animation
						SetIsPlayingGIFFlag(FALSE);
						break;
					} else {
						gifData.currentFrame = gifData.startFrame;
						if(gifData.numberOfLoops >= 0) {
							++gifData.currentLoop;
						}
					}
				} else {
					// we're already past the last loop
					SetIsPlayingGIFFlag(FALSE);
					break;
				}

				// update the buffers
				if(gifData.currentFrame == gifData.startFrame) {
					InitializeScreenBuffersWithSpecifiedGIFFrame(gifData.startFrame);
				} else {
					WTL::CPoint position(0, 0);
					DWORD style = GetStyle();
					if(style & ACS_CENTER) {
						position.x = (gifData.currentlyBufferedRectangle.Width() - gifData.logicalScreenRectangle.Width()) / 2;
						position.y = (gifData.currentlyBufferedRectangle.Height() - gifData.logicalScreenRectangle.Height()) / 2;
					}
					RenderGIFFrameBackground(gifData.currentFrame, gifData.screenWithoutCurrentFrame.dc, position, (style & ACS_TRANSPARENT) == ACS_TRANSPARENT);

					gifData.screenWithCurrentFrame.dc.BitBlt(0, 0, gifData.currentlyBufferedRectangle.Width(), gifData.currentlyBufferedRectangle.Height(), gifData.screenWithoutCurrentFrame.dc, 0, 0, SRCCOPY);
					RenderGIFFrame(gifData.currentFrame, gifData.screenWithCurrentFrame.dc, position);
					gifData.bufferedFrame = gifData.currentFrame;
				}

				// update the screen
				Invalidate(FALSE);

				if(gifData.frames[gifData.currentFrame]->delayTime > 0) {
					SetTimer(timers.ID_DRAWGIFFRAME, gifData.frames[gifData.currentFrame]->delayTime);
				}
			}
			break;
		}

		default:
			wasHandled = FALSE;
			break;
	}
	return 0;
}

LRESULT Animation::OnWindowPosChanged(UINT /*message*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& wasHandled)
{
	LPWINDOWPOS pDetails = reinterpret_cast<LPWINDOWPOS>(lParam);

	WTL::CRect windowRectangle = m_rcPos;
	/* Ugly hack: We depend on this message being sent without SWP_NOMOVE at least once, but this requirement
	              not always will be fulfilled. Fortunately pDetails seems to contain correct x and y values
	              even if SWP_NOMOVE is set.
	 */
	if(!(pDetails->flags & SWP_NOMOVE) || (windowRectangle.IsRectNull() && pDetails->x != 0 && pDetails->y != 0)) {
		windowRectangle.MoveToXY(pDetails->x, pDetails->y);
	}
	if(!(pDetails->flags & SWP_NOSIZE)) {
		windowRectangle.right = windowRectangle.left + pDetails->cx;
		windowRectangle.bottom = windowRectangle.top + pDetails->cy;
	}

	if(!(pDetails->flags & SWP_NOMOVE) || !(pDetails->flags & SWP_NOSIZE)) {
		Invalidate();
		ATLASSUME(m_spInPlaceSite);
		if(m_spInPlaceSite && !windowRectangle.EqualRect(&m_rcPos)) {
			m_spInPlaceSite->OnPosRectChange(&windowRectangle);
		}
		if(!(pDetails->flags & SWP_NOSIZE)) {
			/* Problem: When the control is resized, m_rcPos already contains the new rectangle, even before the
			 *          message is sent without SWP_NOSIZE. Therefore raise the event even if the rectangles are
			 *          equal. Raising the event too often is better than raising it too few.
			 */
			Raise_ResizedControlWindow();
		}
	}

	wasHandled = FALSE;
	return 0;
}

LRESULT Animation::OnXButtonDown(UINT /*message*/, WPARAM wParam, LPARAM lParam, BOOL& wasHandled)
{
	wasHandled = FALSE;

	SHORT button = 0;
	SHORT shift = 0;
	WPARAM2BUTTONANDSHIFT(GET_KEYSTATE_WPARAM(wParam), button, shift);
	switch(GET_XBUTTON_WPARAM(wParam)) {
		case XBUTTON1:
			button = embXButton1;
			break;
		case XBUTTON2:
			button = embXButton2;
			break;
	}
	Raise_MouseDown(button, shift, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

	return 0;
}

LRESULT Animation::OnXButtonUp(UINT /*message*/, WPARAM wParam, LPARAM lParam, BOOL& wasHandled)
{
	wasHandled = FALSE;

	SHORT button = 0;
	SHORT shift = 0;
	WPARAM2BUTTONANDSHIFT(GET_KEYSTATE_WPARAM(wParam), button, shift);
	switch(GET_XBUTTON_WPARAM(wParam)) {
		case XBUTTON1:
			button = embXButton1;
			break;
		case XBUTTON2:
			button = embXButton2;
			break;
	}
	Raise_MouseUp(button, shift, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

	return 0;
}

LRESULT Animation::OnReflectedCtlColorStatic(UINT /*message*/, WPARAM wParam, LPARAM lParam, BOOL& /*wasHandled*/)
{
	if(flags.usingThemes) {
		RECT clientRectangle;
		::GetClientRect(reinterpret_cast<HWND>(lParam), &clientRectangle);
		if(IsComctl32Version610OrNewer()) {
			FillRect(reinterpret_cast<HDC>(wParam), &clientRectangle, GetSysColorBrush(COLOR_3DFACE));
			DrawThemeParentBackground(*this, reinterpret_cast<HDC>(wParam), &clientRectangle);
			return reinterpret_cast<LRESULT>(static_cast<HBRUSH>(GetStockObject(NULL_BRUSH)));
		} else {
			/* TODO: Find a better solution for Windows XP. The main problem is NULL_BRUSH, which causes
			 *       a black background, even if the control is located on a tab strip.
			 *       Drawing the background in WM_ERASEBKGND doesn't seem to help, too.
			 */
			WTL::CRect clientRectangle;
			::GetClientRect(reinterpret_cast<HWND>(lParam), &clientRectangle);

			CDC memoryDC;
			memoryDC.CreateCompatibleDC(reinterpret_cast<HDC>(wParam));
			CBitmap memoryBitmap;
			memoryBitmap.CreateCompatibleBitmap(reinterpret_cast<HDC>(wParam), clientRectangle.Width(), clientRectangle.Height());
			HBITMAP hPreviousBitmap = memoryDC.SelectBitmap(memoryBitmap);
			memoryDC.SetViewportOrg(-clientRectangle.left, -clientRectangle.top);

			memoryDC.FillRect(&clientRectangle, GetSysColorBrush(COLOR_3DFACE));
			DrawThemeParentBackground(reinterpret_cast<HWND>(lParam), memoryDC, &clientRectangle);

			memoryDC.SelectBitmap(hPreviousBitmap);
			if(!themedBackBrush.IsNull()) {
				themedBackBrush.DeleteObject();
			}
			themedBackBrush.CreatePatternBrush(memoryBitmap);
			return reinterpret_cast<LRESULT>(static_cast<HBRUSH>(themedBackBrush));
		}
	}
	SetBkColor(reinterpret_cast<HDC>(wParam), OLECOLOR2COLORREF(properties.backColor));
	if(!flags.usingThemes && !(properties.backColor & 0x80000000)) {
		SetDCBrushColor(reinterpret_cast<HDC>(wParam), OLECOLOR2COLORREF(properties.backColor));
		return reinterpret_cast<LRESULT>(static_cast<HBRUSH>(GetStockObject(DC_BRUSH)));
	} else {
		return reinterpret_cast<LRESULT>(GetSysColorBrush(properties.backColor & 0x0FFFFFFF));
	}
}

LRESULT Animation::OnOpen(UINT message, WPARAM wParam, LPARAM lParam, BOOL& /*wasHandled*/)
{
	LRESULT lr = DefWindowProc(message, wParam, lParam);
	if(lr) {
		flags.animationType = (lParam == 0 ? Flags::atNone : Flags::atAVI);
	}
	return lr;
}


LRESULT Animation::OnReflectedStart(WORD /*notifyCode*/, WORD /*controlID*/, HWND /*hWnd*/, BOOL& /*wasHandled*/)
{
	flags.isPlayingAVI = TRUE;
	Raise_StartedReplay();
	return 0;
}

LRESULT Animation::OnReflectedStop(WORD /*notifyCode*/, WORD /*controlID*/, HWND /*hWnd*/, BOOL& /*wasHandled*/)
{
	flags.isPlayingAVI = FALSE;
	Raise_StoppedReplay();
	return 0;
}


inline HRESULT Animation::Raise_Click(SHORT button, SHORT shift, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y)
{
	//if(m_nFreezeEvents == 0) {
		return Fire_Click(button, shift, x, y);
	//}
	//return S_OK;
}

inline HRESULT Animation::Raise_ContextMenu(SHORT button, SHORT shift, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y)
{
	//if(m_nFreezeEvents == 0) {
		/*if((x == -1) && (y == -1)) {
			// the event was caused by the keyboard
		}*/

		return Fire_ContextMenu(button, shift, x, y);
	//}
	//return S_OK;
}

inline HRESULT Animation::Raise_DblClick(SHORT button, SHORT shift, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y)
{
	//if(m_nFreezeEvents == 0) {
		return Fire_DblClick(button, shift, x, y);
	//}
	//return S_OK;
}

inline HRESULT Animation::Raise_DestroyedControlWindow(LONG hWnd)
{
	KillTimer(timers.ID_REDRAW);
	if(properties.registerForOLEDragDrop) {
		ATLVERIFY(RevokeDragDrop(*this) == S_OK);
	}

	//if(m_nFreezeEvents == 0) {
		return Fire_DestroyedControlWindow(hWnd);
	//}
	//return S_OK;
}

inline HRESULT Animation::Raise_MClick(SHORT button, SHORT shift, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y)
{
	//if(m_nFreezeEvents == 0) {
		return Fire_MClick(button, shift, x, y);
	//}
	//return S_OK;
}

inline HRESULT Animation::Raise_MDblClick(SHORT button, SHORT shift, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y)
{
	//if(m_nFreezeEvents == 0) {
		return Fire_MDblClick(button, shift, x, y);
	//}
	//return S_OK;
}

inline HRESULT Animation::Raise_MouseDown(SHORT button, SHORT shift, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y)
{
	BOOL fireMouseDown = FALSE;
	if(/*(m_nFreezeEvents == 0) && */!(properties.disabledEvents & deMouseEvents)) {
		if(!mouseStatus.enteredControl) {
			Raise_MouseEnter(button, shift, x, y);
		}
		if(!mouseStatus.hoveredControl) {
			TRACKMOUSEEVENT trackingOptions = {0};
			trackingOptions.cbSize = sizeof(trackingOptions);
			trackingOptions.hwndTrack = *this;
			trackingOptions.dwFlags = TME_HOVER | TME_CANCEL;
			TrackMouseEvent(&trackingOptions);

			Raise_MouseHover(button, shift, x, y);
		}
		fireMouseDown = TRUE;
	} else {
		if(!mouseStatus.enteredControl) {
			mouseStatus.EnterControl();
		}
		if(!mouseStatus.hoveredControl) {
			mouseStatus.HoverControl();
		}
	}
	mouseStatus.StoreClickCandidate(button);
	SetCapture();

	if(mouseStatus.IsDoubleClickCandidate(button)) {
		/* Watch for double-clicks.
		   Are we still within the control's client area? */
		BOOL hasLeftControl = FALSE;
		DWORD position = GetMessagePos();
		POINT cursorPosition = {GET_X_LPARAM(position), GET_Y_LPARAM(position)};
		RECT clientArea = {0};
		GetClientRect(&clientArea);
		ClientToScreen(&clientArea);
		if(PtInRect(&clientArea, cursorPosition)) {
			// maybe the control is overlapped by a foreign window
			if(WindowFromPoint(cursorPosition) != *this) {
				hasLeftControl = TRUE;
			}
		} else {
			hasLeftControl = TRUE;
		}

		if(!hasLeftControl) {
			// we don't have left the control, so raise the double-click event
			switch(button) {
				case 1/*MouseButtonConstants.vbLeftButton*/:
					if(!(properties.disabledEvents & deClickEvents)) {
						Raise_DblClick(button, shift, x, y);
					}
					break;
				case 2/*MouseButtonConstants.vbRightButton*/:
					if(!(properties.disabledEvents & deClickEvents)) {
						Raise_RDblClick(button, shift, x, y);
					}
					break;
				case 4/*MouseButtonConstants.vbMiddleButton*/:
					if(!(properties.disabledEvents & deClickEvents)) {
						Raise_MDblClick(button, shift, x, y);
					}
					break;
				case embXButton1:
				case embXButton2:
					if(!(properties.disabledEvents & deClickEvents)) {
						Raise_XDblClick(button, shift, x, y);
					}
					break;
			}
			mouseStatus.RemoveAllDoubleClickCandidates();
		}

		mouseStatus.RemoveClickCandidate(button);
		if(GetCapture() == *this) {
			ReleaseCapture();
		}
		fireMouseDown = FALSE;
	} else {
		mouseStatus.RemoveAllDoubleClickCandidates();
	}

	HRESULT hr = S_OK;
	if(fireMouseDown) {
		hr = Fire_MouseDown(button, shift, x, y);
	}
	return hr;
}

inline HRESULT Animation::Raise_MouseEnter(SHORT button, SHORT shift, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y)
{
	TRACKMOUSEEVENT trackingOptions = {0};
	trackingOptions.cbSize = sizeof(trackingOptions);
	trackingOptions.hwndTrack = *this;
	trackingOptions.dwHoverTime = (properties.hoverTime == -1 ? HOVER_DEFAULT : properties.hoverTime);
	trackingOptions.dwFlags = TME_HOVER | TME_LEAVE;
	TrackMouseEvent(&trackingOptions);

	mouseStatus.EnterControl();

	//if(m_nFreezeEvents == 0) {
		return Fire_MouseEnter(button, shift, x, y);
	//}
	//return S_OK;
}

inline HRESULT Animation::Raise_MouseHover(SHORT button, SHORT shift, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y)
{
	mouseStatus.HoverControl();

	if(/*(m_nFreezeEvents == 0) && */!(properties.disabledEvents & deMouseEvents)) {
		return Fire_MouseHover(button, shift, x, y);
	}
	return S_OK;
}

inline HRESULT Animation::Raise_MouseLeave(SHORT button, SHORT shift, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y)
{
	mouseStatus.LeaveControl();

	if(/*(m_nFreezeEvents == 0) && */!(properties.disabledEvents & deMouseEvents)) {
		return Fire_MouseLeave(button, shift, x, y);
	}
	return S_OK;
}

inline HRESULT Animation::Raise_MouseMove(SHORT button, SHORT shift, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y)
{
	if(!mouseStatus.enteredControl) {
		Raise_MouseEnter(button, shift, x, y);
	}
	mouseStatus.lastPosition.x = x;
	mouseStatus.lastPosition.y = y;

	//if(m_nFreezeEvents == 0) {
		return Fire_MouseMove(button, shift, x, y);
	//}
	//return S_OK;
}

inline HRESULT Animation::Raise_MouseUp(SHORT button, SHORT shift, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y)
{
	HRESULT hr = S_OK;
	if(/*(m_nFreezeEvents == 0) && */!(properties.disabledEvents & deMouseEvents)) {
		hr = Fire_MouseUp(button, shift, x, y);
	}

	if(mouseStatus.IsClickCandidate(button)) {
		/* Watch for clicks.
		   Are we still within the control's client area? */
		BOOL hasLeftControl = FALSE;
		DWORD position = GetMessagePos();
		POINT cursorPosition = {GET_X_LPARAM(position), GET_Y_LPARAM(position)};
		RECT clientArea = {0};
		GetClientRect(&clientArea);
		ClientToScreen(&clientArea);
		if(PtInRect(&clientArea, cursorPosition)) {
			// maybe the control is overlapped by a foreign window
			if(WindowFromPoint(cursorPosition) != *this) {
				hasLeftControl = TRUE;
			}
		} else {
			hasLeftControl = TRUE;
		}
		if(GetCapture() == *this) {
			ReleaseCapture();
		}

		if(!hasLeftControl) {
			// we don't have left the control, so raise the click event
			switch(button) {
				case 1/*MouseButtonConstants.vbLeftButton*/:
					if(!(properties.disabledEvents & deClickEvents)) {
						Raise_Click(button, shift, x, y);
					}
					break;
				case 2/*MouseButtonConstants.vbRightButton*/:
					if(!(properties.disabledEvents & deClickEvents)) {
						Raise_RClick(button, shift, x, y);
					}
					break;
				case 4/*MouseButtonConstants.vbMiddleButton*/:
					if(!(properties.disabledEvents & deClickEvents)) {
						Raise_MClick(button, shift, x, y);
					}
					break;
				case embXButton1:
				case embXButton2:
					if(!(properties.disabledEvents & deClickEvents)) {
						Raise_XClick(button, shift, x, y);
					}
					break;
			}
			mouseStatus.StoreDoubleClickCandidate(button);
		}

		mouseStatus.RemoveClickCandidate(button);
	}

	return hr;
}

//inline HRESULT Animation::Raise_MouseWheel(SHORT button, SHORT shift, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y, ScrollAxisConstants scrollAxis, SHORT wheelDelta)
//{
//	if(!mouseStatus.enteredControl) {
//		Raise_MouseEnter(button, shift, x, y);
//	}
//
//	//if(m_nFreezeEvents == 0) {
//		return Fire_MouseWheel(button, shift, x, y, scrollAxis, wheelDelta);
//	//}
//	//return S_OK;
//}

inline HRESULT Animation::Raise_OLEDragDrop(IDataObject* pData, DWORD* pEffect, DWORD keyState, POINTL mousePosition)
{
	// NOTE: pData can be NULL

	HRESULT hr = S_OK;
	//if(m_nFreezeEvents == 0) {
		ScreenToClient(reinterpret_cast<LPPOINT>(&mousePosition));
		SHORT button = 0;
		SHORT shift = 0;
		OLEKEYSTATE2BUTTONANDSHIFT(keyState, button, shift);

		if(pData) {
			/* Actually we wouldn't need the next line, because the data object passed to this method should
				 always be the same as the data object that was passed to Raise_OLEDragEnter. */
			dragDropStatus.pActiveDataObject = ClassFactory::InitOLEDataObject(pData);
		} else {
			dragDropStatus.pActiveDataObject = NULL;
		}
		if(dragDropStatus.pActiveDataObject) {
			hr = Fire_OLEDragDrop(dragDropStatus.pActiveDataObject, reinterpret_cast<OLEDropEffectConstants*>(pEffect), button, shift, mousePosition.x, mousePosition.y);
		}
	//}

	dragDropStatus.pActiveDataObject = NULL;
	dragDropStatus.OLEDragLeaveOrDrop();
	Invalidate();

	return hr;
}

inline HRESULT Animation::Raise_OLEDragEnter(IDataObject* pData, DWORD* pEffect, DWORD keyState, POINTL mousePosition)
{
	// NOTE: pData can be NULL

	ScreenToClient(reinterpret_cast<LPPOINT>(&mousePosition));
	SHORT button = 0;
	SHORT shift = 0;
	OLEKEYSTATE2BUTTONANDSHIFT(keyState, button, shift);

	dragDropStatus.OLEDragEnter();

	if(pData) {
		dragDropStatus.pActiveDataObject = ClassFactory::InitOLEDataObject(pData);
	} else {
		dragDropStatus.pActiveDataObject = NULL;
	}
	//if(m_nFreezeEvents == 0) {
		if(dragDropStatus.pActiveDataObject) {
			return Fire_OLEDragEnter(dragDropStatus.pActiveDataObject, reinterpret_cast<OLEDropEffectConstants*>(pEffect), button, shift, mousePosition.x, mousePosition.y);
		}
	//}
	return S_OK;
}

inline HRESULT Animation::Raise_OLEDragLeave(void)
{
	HRESULT hr = S_OK;
	//if(m_nFreezeEvents == 0) {
		SHORT button = 0;
		SHORT shift = 0;
		WPARAM2BUTTONANDSHIFT(-1, button, shift);

		if(dragDropStatus.pActiveDataObject) {
			hr = Fire_OLEDragLeave(dragDropStatus.pActiveDataObject, button, shift, dragDropStatus.lastMousePosition.x, dragDropStatus.lastMousePosition.y);
		}
	//}

	dragDropStatus.pActiveDataObject = NULL;
	dragDropStatus.OLEDragLeaveOrDrop();
	Invalidate();

	return hr;
}

inline HRESULT Animation::Raise_OLEDragMouseMove(DWORD* pEffect, DWORD keyState, POINTL mousePosition)
{
	ScreenToClient(reinterpret_cast<LPPOINT>(&mousePosition));
	dragDropStatus.lastMousePosition = mousePosition;
	SHORT button = 0;
	SHORT shift = 0;
	OLEKEYSTATE2BUTTONANDSHIFT(keyState, button, shift);

	//if(m_nFreezeEvents == 0) {
		if(dragDropStatus.pActiveDataObject) {
			return Fire_OLEDragMouseMove(dragDropStatus.pActiveDataObject, reinterpret_cast<OLEDropEffectConstants*>(pEffect), button, shift, mousePosition.x, mousePosition.y);
		}
	//}
	return S_OK;
}

inline HRESULT Animation::Raise_RClick(SHORT button, SHORT shift, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y)
{
	//if(m_nFreezeEvents == 0) {
		return Fire_RClick(button, shift, x, y);
	//}
	//return S_OK;
}

inline HRESULT Animation::Raise_RDblClick(SHORT button, SHORT shift, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y)
{
	//if(m_nFreezeEvents == 0) {
		return Fire_RDblClick(button, shift, x, y);
	//}
	//return S_OK;
}

inline HRESULT Animation::Raise_RecreatedControlWindow(LONG hWnd)
{
	// configure the control
	SendConfigurationMessages();

	if(properties.registerForOLEDragDrop) {
		ATLVERIFY(RegisterDragDrop(*this, static_cast<IDropTarget*>(this)) == S_OK);
	}

	if(properties.dontRedraw) {
		SetTimer(timers.ID_REDRAW, timers.INT_REDRAW);
	}

	//if(m_nFreezeEvents == 0) {
		return Fire_RecreatedControlWindow(hWnd);
	//}
	//return S_OK;
}

inline HRESULT Animation::Raise_ResizedControlWindow(void)
{
	if(flags.animationType == Flags::atGIF) {
		InitializeScreenBuffersWithSpecifiedGIFFrame(gifData.currentFrame);
	}

	//if(m_nFreezeEvents == 0) {
		return Fire_ResizedControlWindow();
	//}
	//return S_OK;
}

inline HRESULT Animation::Raise_StartedReplay(void)
{
	//if(m_nFreezeEvents == 0) {
		return Fire_StartedReplay();
	//}
	//return S_OK;
}

inline HRESULT Animation::Raise_StoppedReplay(void)
{
	//if(m_nFreezeEvents == 0) {
		return Fire_StoppedReplay();
	//}
	//return S_OK;
}

inline HRESULT Animation::Raise_XClick(SHORT button, SHORT shift, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y)
{
	//if(m_nFreezeEvents == 0) {
		return Fire_XClick(button, shift, x, y);
	//}
	//return S_OK;
}

inline HRESULT Animation::Raise_XDblClick(SHORT button, SHORT shift, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y)
{
	//if(m_nFreezeEvents == 0) {
		return Fire_XDblClick(button, shift, x, y);
	//}
	//return S_OK;
}


void Animation::RecreateControlWindow(void)
{
	if(m_bInPlaceActive) {
		BOOL isUIActive = m_bUIActive;
		InPlaceDeactivate();
		ATLASSERT(m_hWnd == NULL);
		InPlaceActivate((isUIActive ? OLEIVERB_UIACTIVATE : OLEIVERB_INPLACEACTIVATE));
	}
}

DWORD Animation::GetExStyleBits(void)
{
	DWORD extendedStyle = WS_EX_LEFT | WS_EX_LTRREADING;
	switch(properties.appearance) {
		case a3D:
			extendedStyle |= WS_EX_CLIENTEDGE;
			break;
		case a3DLight:
			extendedStyle |= WS_EX_STATICEDGE;
			break;
	}
	return extendedStyle;
}

DWORD Animation::GetStyleBits(void)
{
	DWORD style = WS_CHILDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE;
	switch(properties.borderStyle) {
		case bsFixedSingle:
			style |= WS_BORDER;
			break;
	}
	if(!properties.enabled) {
		style |= WS_DISABLED;
	}

	switch(properties.animationBackStyle) {
		case absUseBackColor:
			style |= ACS_TRANSPARENT;
			break;
	}
	if(properties.autoStartReplay) {
		style |= ACS_AUTOPLAY;
	}
	if(properties.centerAnimation) {
		style |= ACS_CENTER;
	}
	return style;
}

void Animation::SendConfigurationMessages(void)
{
}

HCURSOR Animation::MousePointerConst2hCursor(MousePointerConstants mousePointer)
{
	WORD flag = 0;
	switch(mousePointer) {
		case mpArrow:
			flag = OCR_NORMAL;
			break;
		case mpCross:
			flag = OCR_CROSS;
			break;
		case mpIBeam:
			flag = OCR_IBEAM;
			break;
		case mpIcon:
			flag = OCR_ICOCUR;
			break;
		case mpSize:
			flag = OCR_SIZEALL;     // OCR_SIZE is obsolete
			break;
		case mpSizeNESW:
			flag = OCR_SIZENESW;
			break;
		case mpSizeNS:
			flag = OCR_SIZENS;
			break;
		case mpSizeNWSE:
			flag = OCR_SIZENWSE;
			break;
		case mpSizeEW:
			flag = OCR_SIZEWE;
			break;
		case mpUpArrow:
			flag = OCR_UP;
			break;
		case mpHourglass:
			flag = OCR_WAIT;
			break;
		case mpNoDrop:
			flag = OCR_NO;
			break;
		case mpArrowHourglass:
			flag = OCR_APPSTARTING;
			break;
		case mpArrowQuestion:
			flag = 32651;
			break;
		case mpSizeAll:
			flag = OCR_SIZEALL;
			break;
		case mpHand:
			flag = OCR_HAND;
			break;
		case mpInsertMedia:
			flag = 32663;
			break;
		case mpScrollAll:
			flag = 32654;
			break;
		case mpScrollN:
			flag = 32655;
			break;
		case mpScrollNE:
			flag = 32660;
			break;
		case mpScrollE:
			flag = 32658;
			break;
		case mpScrollSE:
			flag = 32662;
			break;
		case mpScrollS:
			flag = 32656;
			break;
		case mpScrollSW:
			flag = 32661;
			break;
		case mpScrollW:
			flag = 32657;
			break;
		case mpScrollNW:
			flag = 32659;
			break;
		case mpScrollNS:
			flag = 32652;
			break;
		case mpScrollEW:
			flag = 32653;
			break;
		default:
			return NULL;
	}

	return static_cast<HCURSOR>(LoadImage(0, MAKEINTRESOURCE(flag), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_SHARED));
}

BOOL Animation::IsInDesignMode(void)
{
	BOOL b = TRUE;
	GetAmbientUserMode(b);
	return !b;
}


HRESULT Animation::LoadGIF(LPSTREAM pInputStream)
{
	ATLASSUME(pInputStream);

	if(pInputStream) {
		// read header (signature + version, "GIF87a" or "GIF89a")
		CHAR signature[6] = {'\0'};
		if(FAILED(pInputStream->Read(signature, 6, NULL)) || ((memcmp(signature, "GIF87a", 6) != 0) && (memcmp(signature, "GIF89a", 6) != 0))) {
			return E_FAIL;
		}

		#ifdef _WIN32
			#pragma pack(push, r1, 1)
		#endif

		struct GIFLOGICALSCREENDESCRIPTOR
		{
			USHORT screenWidth;
			USHORT screenHeight;
			BYTE globalColorTableSize : 3;
			BYTE sortFlag : 1;
			BYTE colorDepth : 3;
			BYTE hasGlobalColorTable : 1;
			BYTE backColorIndex;
			BYTE pixelAspectRatio;
		} gifLogicalScreenDescriptor;

		struct GIFIMAGEDESCRIPTOR
		{
			USHORT frameLeft;
			USHORT frameTop;
			USHORT frameWidth;
			USHORT frameHeight;
			BYTE localColorTableSize : 3;
			BYTE reserved : 2;
			BYTE sortFlag : 1;
			BYTE interlaced : 1;
			BYTE hasLocalColorTable : 1;
		} gifImageDescriptor = {0};

		struct GIFGRAPHICALCONTROLEXTENSION
		{
			BYTE blockSize;
			BYTE hasTransparentColor : 1;
			BYTE waitForUserInput : 1;
			BYTE disposalMethod : 3;
			BYTE reserved : 3;
			USHORT delayTime;
			BYTE transparentColorIndex;
			BYTE blockTerminator;
		} gifGraphicalControlExtension = {0};

		#ifdef _WIN32
			#pragma pack(pop, r1)
		#endif

		// read logical screen descriptor
		if(FAILED(pInputStream->Read(&gifLogicalScreenDescriptor, sizeof(GIFLOGICALSCREENDESCRIPTOR), NULL))) {
			return E_FAIL;
		}

		gifData.logicalScreenRectangle.left = 0;
		gifData.logicalScreenRectangle.right = gifLogicalScreenDescriptor.screenWidth;
		gifData.logicalScreenRectangle.top = 0;
		gifData.logicalScreenRectangle.bottom = gifLogicalScreenDescriptor.screenHeight;
		gifData.globalColorTableSize = 1 << (gifLogicalScreenDescriptor.globalColorTableSize + 1);
		gifData.hasGlobalColorTable = gifLogicalScreenDescriptor.hasGlobalColorTable;
		gifData.colorDepth = gifLogicalScreenDescriptor.colorDepth + 1;
		ATLASSERT((gifLogicalScreenDescriptor.pixelAspectRatio == 0) || (gifLogicalScreenDescriptor.pixelAspectRatio == 1));

		// read/generate global color map
		if(gifData.hasGlobalColorTable) {
			// file has a global color map and it follows the logical screen descriptor
			gifData.pGlobalColorTable = static_cast<Color*>(HeapAlloc(GetProcessHeap(), 0, gifData.globalColorTableSize * sizeof(Color)));
			if(!gifData.pGlobalColorTable) {
				return E_OUTOFMEMORY;
			}
			for(int i = 0; i < gifData.globalColorTableSize; ++i) {
				pInputStream->Read(&gifData.pGlobalColorTable[i].r, 1, NULL);
				pInputStream->Read(&gifData.pGlobalColorTable[i].g, 1, NULL);
				pInputStream->Read(&gifData.pGlobalColorTable[i].b, 1, NULL);
			}
			gifData.backColorIndex = gifLogicalScreenDescriptor.backColorIndex;
		} else {
			// provide an internal default palette
			gifData.pGlobalColorTable = static_cast<Color*>(HeapAlloc(GetProcessHeap(), 0, gifData.globalColorTableSize * sizeof(Color)));
			if(!gifData.pGlobalColorTable) {
				return E_OUTOFMEMORY;
			}
			ATLASSERT(gifData.colorDepth <= 8);
			for(UCHAR i = 0; i < gifData.globalColorTableSize; ++i) {
				gifData.pGlobalColorTable[i].r = gifData.pGlobalColorTable[i].g = gifData.pGlobalColorTable[i].b = i;
			}
			gifData.backColorIndex = -1;
		}

		/* now we have 3 possibilities:
		     a) get an extension block (blocks with additional information)
		     b) get an image separator (introductor to an image)
		     c) get the trailer char (end of GIF file) */

		BOOL noErrorOccurred = TRUE;
		BOOL hasFoundGraphicExtension = FALSE;
		do {
			BYTE blockType = 0;
			noErrorOccurred = SUCCEEDED(pInputStream->Read(&blockType, 1, NULL));

			if(blockType == 0x21) {
				// extension block
				BYTE blockSubType = 0;
				noErrorOccurred = noErrorOccurred && SUCCEEDED(pInputStream->Read(&blockSubType, 1, NULL));
				switch(blockSubType) {
					case 0xF9: {
						// graphic control extension
						noErrorOccurred = noErrorOccurred && SUCCEEDED(pInputStream->Read(&gifGraphicalControlExtension, sizeof(GIFGRAPHICALCONTROLEXTENSION), NULL));
						hasFoundGraphicExtension = TRUE;
						break;
					}
					case 0xFF: {
						// application extension
						BYTE blockLength = 0;
						noErrorOccurred = noErrorOccurred && SUCCEEDED(pInputStream->Read(&blockLength, 1, NULL));
						ULARGE_INTEGER blockStartPosition = {0};
						LARGE_INTEGER distance = {0};
						noErrorOccurred = noErrorOccurred && SUCCEEDED(pInputStream->Seek(distance, STREAM_SEEK_CUR, &blockStartPosition));

						if(noErrorOccurred && (blockLength == 11)) {
							CHAR applicationID[11] = {'\0'};
							noErrorOccurred = noErrorOccurred && SUCCEEDED(pInputStream->Read(applicationID, blockLength, NULL));
							if(noErrorOccurred && (memcmp(applicationID, "NETSCAPE2.0", blockLength) == 0)) {
								BYTE subBlockLength = 0;
								noErrorOccurred = noErrorOccurred && SUCCEEDED(pInputStream->Read(&subBlockLength, 1, NULL));
								if(noErrorOccurred && (subBlockLength == 3)) {
									BYTE subBlockID = 0;
									noErrorOccurred = noErrorOccurred && SUCCEEDED(pInputStream->Read(&subBlockID, 1, NULL));
									if(noErrorOccurred && (subBlockID == 1)) {
										SHORT loopCount = 0;
										noErrorOccurred = noErrorOccurred && SUCCEEDED(pInputStream->Read(&loopCount, 2, NULL));
										if(noErrorOccurred) {
											ATLASSERT(loopCount == 0);
											gifData.recommendedNumberOfLoops = (loopCount <= 0 ? -1 : loopCount);
										}
										distance.QuadPart = static_cast<LONGLONG>(blockStartPosition.QuadPart);
										noErrorOccurred = noErrorOccurred && SUCCEEDED(pInputStream->Seek(distance, STREAM_SEEK_SET, NULL));
									} else {
										distance.QuadPart = static_cast<LONGLONG>(blockStartPosition.QuadPart);
										noErrorOccurred = noErrorOccurred && SUCCEEDED(pInputStream->Seek(distance, STREAM_SEEK_SET, NULL));
									}
								} else {
									distance.QuadPart = static_cast<LONGLONG>(blockStartPosition.QuadPart);
									noErrorOccurred = noErrorOccurred && SUCCEEDED(pInputStream->Seek(distance, STREAM_SEEK_SET, NULL));
								}
							} else {
								distance.QuadPart = static_cast<LONGLONG>(blockStartPosition.QuadPart);
								noErrorOccurred = noErrorOccurred && SUCCEEDED(pInputStream->Seek(distance, STREAM_SEEK_SET, NULL));
							}
						}

						// skip data sub-blocks
						while(noErrorOccurred && (blockLength > 0)) {
							distance.QuadPart = blockLength;
							noErrorOccurred = noErrorOccurred && SUCCEEDED(pInputStream->Seek(distance, STREAM_SEEK_CUR, NULL));
							noErrorOccurred = noErrorOccurred && SUCCEEDED(pInputStream->Read(&blockLength, 1, NULL));
						}
						break;
					}
					case 0x01:   // PlainText extension (ignored)
						ATLASSERT(FALSE);
					case 0xFE:   // comment extension (ignored)
					default:   // unknown extension (ignored)
						// skip data sub-blocks
						BYTE blockLength = 0;
						noErrorOccurred = noErrorOccurred && SUCCEEDED(pInputStream->Read(&blockLength, 1, NULL));
						while(noErrorOccurred && (blockLength > 0)) {
							LARGE_INTEGER distance;
							distance.QuadPart = blockLength;
							noErrorOccurred = noErrorOccurred && SUCCEEDED(pInputStream->Seek(distance, STREAM_SEEK_CUR, NULL));
							noErrorOccurred = noErrorOccurred && SUCCEEDED(pInputStream->Read(&blockLength, 1, NULL));
						}
						break;
				}

			} else if(blockType == 0x2C) {
				// image separator
				Frame* pFrame = new Frame;

				// read image descriptor
				noErrorOccurred = noErrorOccurred && SUCCEEDED(pInputStream->Read(&gifImageDescriptor, sizeof(GIFIMAGEDESCRIPTOR), NULL));

				pFrame->boundingRectangle.left = gifImageDescriptor.frameLeft;
				pFrame->boundingRectangle.top = gifImageDescriptor.frameTop;
				pFrame->boundingRectangle.right = pFrame->boundingRectangle.left + gifImageDescriptor.frameWidth;
				pFrame->boundingRectangle.bottom = pFrame->boundingRectangle.top + gifImageDescriptor.frameHeight;
				pFrame->hasLocalColorTable = gifImageDescriptor.hasLocalColorTable;

				// read optional local color map
				if(pFrame->hasLocalColorTable) {
					// frame has a local color map and it follows the image descriptor
					pFrame->localColorTableSize = 1 << (gifImageDescriptor.localColorTableSize + 1);
					pFrame->Initialize();
					ATLASSERT(pFrame->pLocalColorTable != NULL);
					if(!pFrame->pLocalColorTable || !pFrame->pPixels) {
						delete pFrame;
						return E_OUTOFMEMORY;
					}
					for(int i = 0; noErrorOccurred && (i < pFrame->localColorTableSize); ++i) {
						noErrorOccurred = noErrorOccurred && SUCCEEDED(pInputStream->Read(&pFrame->pLocalColorTable[i].r, 1, NULL));
						noErrorOccurred = noErrorOccurred && SUCCEEDED(pInputStream->Read(&pFrame->pLocalColorTable[i].g, 1, NULL));
						noErrorOccurred = noErrorOccurred && SUCCEEDED(pInputStream->Read(&pFrame->pLocalColorTable[i].b, 1, NULL));
					}
				} else {
					// frame has no local color map, so we'll use the global color map
					ATLASSERT(gifData.globalColorTableSize >= 1 << gifData.colorDepth);
					pFrame->localColorTableSize = gifData.globalColorTableSize;
					pFrame->Initialize();
					ATLASSERT(pFrame->pLocalColorTable != NULL);
					if(!pFrame->pLocalColorTable || !pFrame->pPixels) {
						delete pFrame;
						return E_OUTOFMEMORY;
					}
					CopyMemory(pFrame->pLocalColorTable, gifData.pGlobalColorTable, sizeof(Color) * gifData.globalColorTableSize);
				}

				if(hasFoundGraphicExtension) {
					pFrame->hasTransparentColor = gifGraphicalControlExtension.hasTransparentColor;
					pFrame->transparentColorIndex = gifGraphicalControlExtension.transparentColorIndex;
					if(gifGraphicalControlExtension.delayTime <= 5) {
						pFrame->delayTime = 100;
					} else {
						pFrame->delayTime = gifGraphicalControlExtension.delayTime * 10;
					}
					pFrame->waitForUserInput = gifGraphicalControlExtension.waitForUserInput;
					pFrame->disposalMethod = static_cast<Frame::DisposalMethod>(gifGraphicalControlExtension.disposalMethod);
				}
				if(!pFrame->hasTransparentColor) {
					// if the frame doesn't cover the whole logical screen or is offset, it MUST be transparent
					if((pFrame->boundingRectangle.left != 0) || (pFrame->boundingRectangle.top != 0) || (pFrame->boundingRectangle.Width() != gifData.logicalScreenRectangle.Width()) || (pFrame->boundingRectangle.Height() != gifData.logicalScreenRectangle.Height())) {
						pFrame->hasTransparentColor = TRUE;
						if(pFrame->transparentColorIndex == -1) {
							pFrame->transparentColorIndex = 0;
						}
					}
				}

				// call LZW decoder
				BOOL success = gifData.lzwDecoder.Decode(pInputStream, pFrame->pPixels, pFrame->bytesPerRow * pFrame->boundingRectangle.Height(), static_cast<SHORT>(pFrame->boundingRectangle.Width()), static_cast<SHORT>(pFrame->boundingRectangle.Height()), gifImageDescriptor.interlaced);
				if(success) {
					#ifdef USE_STL
						gifData.frames.push_back(pFrame);
					#else
						gifData.frames.Add(pFrame);
					#endif
				} else {
					delete pFrame;
					noErrorOccurred = FALSE;
				}

				// some cleanup
				hasFoundGraphicExtension = FALSE;

			} else if(blockType == 0x3B) {
				// trailer
				break;
			}
		} while(noErrorOccurred);

		ATLASSERT(noErrorOccurred);

		if(noErrorOccurred) {
			flags.animationType = Flags::atGIF;
		}

		return (noErrorOccurred ? S_OK : E_FAIL);
	}
	return E_FAIL;
}

HRESULT Animation::LoadGIF(LPTSTR pFile)
{
	CComPtr<IStream> pStream = NULL;
	HRESULT hr = SHCreateStreamOnFile(pFile, STGM_READ | STGM_SHARE_DENY_WRITE, &pStream);
	if(SUCCEEDED(hr) && pStream) {
		return LoadGIF(pStream);
	}
	return hr;
}

HRESULT Animation::LoadGIF(HMODULE hModule, int resourceID, LPTSTR pResourceTypeName)
{
	HRESULT hr = E_FAIL;

	HRSRC hResource = FindResource(hModule, MAKEINTRESOURCE(resourceID), pResourceTypeName);
	if(hResource) {
		HGLOBAL hMem = LoadResource(hModule, hResource);
		if(hMem) {
			/* CreateStreamOnHGlobal() requires global memory that has been created by GlobalAlloc() using the
			   GMEM_MOVEABLE flag, so we have to copy the resource data to a buffer. */
			LPVOID pResourceData = LockResource(hMem);
			if(pResourceData) {
				DWORD sizeOfResource = SizeofResource(hModule, hResource);
				HGLOBAL hBuffer = GlobalAlloc(GMEM_MOVEABLE, sizeOfResource);
				if(hBuffer) {
					LPVOID pBuffer = GlobalLock(hBuffer);
					if(pBuffer) {
						CopyMemory(pBuffer, pResourceData, sizeOfResource);

						LPSTREAM pInputStream = NULL;
						if(SUCCEEDED(CreateStreamOnHGlobal(hBuffer, TRUE, &pInputStream))) {
							hr = LoadGIF(pInputStream);
						}

						GlobalUnlock(hBuffer);
					}
					GlobalFree(hBuffer);
				}
			}
		}
	}
	return hr;
}

UINT Animation::SetIsPlayingGIFFlag(UINT newState)
{
	UINT oldState = gifData.isPlaying;
	if(newState != oldState) {
		gifData.isPlaying = newState;
		if(newState) {
			Raise_StartedReplay();
		} else {
			Raise_StoppedReplay();
		}
	}
	return oldState;
}

void Animation::InitializeScreenBuffersWithSpecifiedGIFFrame(int frameToInitializeWith)
{
	// re-initialize the buffers
	gifData.screenWithBackgroundOnly.Destroy();
	gifData.screenWithCurrentFrame.Destroy();
	gifData.screenWithoutCurrentFrame.Destroy();

	HDC hCompatibleDC = GetDC();

	GetClientRect(&gifData.currentlyBufferedRectangle);
	gifData.screenWithBackgroundOnly.Create(hCompatibleDC, gifData.currentlyBufferedRectangle.Width(), gifData.currentlyBufferedRectangle.Height());
	gifData.screenWithCurrentFrame.Create(hCompatibleDC, gifData.currentlyBufferedRectangle.Width(), gifData.currentlyBufferedRectangle.Height());
	gifData.screenWithoutCurrentFrame.Create(hCompatibleDC, gifData.currentlyBufferedRectangle.Width(), gifData.currentlyBufferedRectangle.Height());

	ReleaseDC(hCompatibleDC);

	// start with the background
	HBRUSH hBrushToUseForBackground = NULL;
	CWindow parentWindow = GetParent();
	if(parentWindow.IsWindow()) {
		hBrushToUseForBackground = reinterpret_cast<HBRUSH>(parentWindow.SendMessage(WM_CTLCOLORSTATIC, reinterpret_cast<WPARAM>(static_cast<HDC>(gifData.screenWithoutCurrentFrame.dc)), reinterpret_cast<LPARAM>(static_cast<HWND>(*this))));
	} else {
		hBrushToUseForBackground = reinterpret_cast<HBRUSH>(SendMessage(OCM_CTLCOLORSTATIC, reinterpret_cast<WPARAM>(static_cast<HDC>(gifData.screenWithoutCurrentFrame.dc)), reinterpret_cast<LPARAM>(static_cast<HWND>(*this))));
	}

	gifData.screenWithoutCurrentFrame.dc.FillRect(&gifData.currentlyBufferedRectangle, hBrushToUseForBackground);
	// the message handler might have drawn into the dc, so we need to copy the content
	gifData.screenWithBackgroundOnly.dc.BitBlt(0, 0, gifData.currentlyBufferedRectangle.Width(), gifData.currentlyBufferedRectangle.Height(), gifData.screenWithoutCurrentFrame.dc, 0, 0, SRCCOPY);

	WTL::CPoint position(0, 0);
	DWORD style = GetStyle();
	if(style & ACS_CENTER) {
		position.x = (gifData.currentlyBufferedRectangle.Width() - gifData.logicalScreenRectangle.Width()) / 2;
		position.y = (gifData.currentlyBufferedRectangle.Height() - gifData.logicalScreenRectangle.Height()) / 2;
	}

	// simply call our rendering methods in a loop
	// TODO: Problems may arise if OnDraw or OnTimer are called while we're within this loop!
	for(int i = 0; i <= frameToInitializeWith; ++i) {
		RenderGIFFrameBackground(i, gifData.screenWithoutCurrentFrame.dc, position, (style & ACS_TRANSPARENT) == ACS_TRANSPARENT);

		gifData.screenWithCurrentFrame.dc.BitBlt(0, 0, gifData.currentlyBufferedRectangle.Width(), gifData.currentlyBufferedRectangle.Height(), gifData.screenWithoutCurrentFrame.dc, 0, 0, SRCCOPY);
		RenderGIFFrame(i, gifData.screenWithCurrentFrame.dc, position);
		gifData.bufferedFrame = i;
	}
	gifData.currentFrame = frameToInitializeWith;
}

void Animation::RenderGIFFrame(int frameToRender, CDC& targetDC, WTL::CPoint& position)
{
	ATLASSERT(frameToRender >= 0);
	#ifdef USE_STL
		ATLASSERT(frameToRender < static_cast<int>(gifData.frames.size()));
	#else
		ATLASSERT(frameToRender < static_cast<int>(gifData.frames.GetCount()));
	#endif

	Frame* pFrameToRender = gifData.frames[frameToRender];
	ATLASSERT_POINTER(pFrameToRender, Frame);
	if(!pFrameToRender) {
		return;
	}

	SIZE frameSize = {pFrameToRender->boundingRectangle.Width(), pFrameToRender->boundingRectangle.Height()};
	BYTE colorIndex;
	Color pixelColor;
	if(pFrameToRender->hasTransparentColor) {
		for(int y = 0; y < frameSize.cy; ++y) {
			for(int x = 0; x < frameSize.cx; ++x) {
				colorIndex = pFrameToRender->pPixels[y * frameSize.cx + x];
				if(colorIndex != pFrameToRender->transparentColorIndex) {
					pixelColor = pFrameToRender->pLocalColorTable[colorIndex];
					targetDC.SetPixelV(position.x + pFrameToRender->boundingRectangle.left + x, position.y + pFrameToRender->boundingRectangle.top + y, RGB(pixelColor.r, pixelColor.g, pixelColor.b));
				}
			}
		}
	} else {
		for(int y = 0; y < frameSize.cy; ++y) {
			for(int x = 0; x < frameSize.cx; ++x) {
				colorIndex = pFrameToRender->pPixels[y * frameSize.cx + x];
				pixelColor = pFrameToRender->pLocalColorTable[colorIndex];
				targetDC.SetPixelV(position.x + pFrameToRender->boundingRectangle.left + x, position.y + pFrameToRender->boundingRectangle.top + y, RGB(pixelColor.r, pixelColor.g, pixelColor.b));
			}
		}
	}
}

void Animation::RenderGIFFrameBackground(int frameToRenderBackgroundFor, CDC& targetDC, WTL::CPoint& position, BOOL drawTransparent)
{
	ATLASSERT(frameToRenderBackgroundFor >= 0);
	#ifdef USE_STL
		ATLASSERT(frameToRenderBackgroundFor < static_cast<int>(gifData.frames.size()));
	#else
		ATLASSERT(frameToRenderBackgroundFor < static_cast<int>(gifData.frames.GetCount()));
	#endif

	if(frameToRenderBackgroundFor == 0) {
		if(drawTransparent) {
			// fill the logical screen's rectangle with the control's background
			targetDC.BitBlt(position.x, position.y, gifData.logicalScreenRectangle.Width(), gifData.logicalScreenRectangle.Height(), gifData.screenWithBackgroundOnly.dc, position.x, position.y, SRCCOPY);
		} else {
			// fill the logical screen's rectangle with the GIF's background color
			WTL::CBrush hBackBrush;
			Color backColor = gifData.pGlobalColorTable[gifData.backColorIndex];
			hBackBrush.CreateSolidBrush(RGB(backColor.r, backColor.g, backColor.b));
			WTL::CRect rc(&gifData.logicalScreenRectangle);
			rc.OffsetRect(position);
			targetDC.FillRect(&rc, hBackBrush);
		}
	} else {
		// maybe the previous frame must be removed
		Frame* pPreviousFrame = gifData.frames[frameToRenderBackgroundFor - 1];
		ATLASSERT_POINTER(pPreviousFrame, Frame);
		if(!pPreviousFrame) {
			return;
		}

		switch(pPreviousFrame->disposalMethod) {
			case Frame::dmNotSpecified:
				// no disposal specified
			case Frame::dmLeaveInPlace:
				// do not dispose - leave the previous frame in place
				if(frameToRenderBackgroundFor == gifData.bufferedFrame + 1) {
					// use the buffered data
					targetDC.BitBlt(position.x, position.y, gifData.logicalScreenRectangle.Width(), gifData.logicalScreenRectangle.Height(), gifData.screenWithCurrentFrame.dc, position.x, position.y, SRCCOPY);
				} else {
					// render recursively
					RenderGIFFrame(frameToRenderBackgroundFor - 1, targetDC, position);
				}
				break;
			case Frame::dmRestoreToBackground:
				// restore the area occupied by the previous frame to the background color
				if(drawTransparent) {
					// use the control's background
					targetDC.BitBlt(position.x + pPreviousFrame->boundingRectangle.left, position.y + pPreviousFrame->boundingRectangle.top, pPreviousFrame->boundingRectangle.Width(), pPreviousFrame->boundingRectangle.Height(), gifData.screenWithBackgroundOnly.dc, position.x + pPreviousFrame->boundingRectangle.left, position.y + pPreviousFrame->boundingRectangle.top, SRCCOPY);
				} else {
					// use the GIF's background color
					WTL::CBrush hBackBrush;
					Color backColor = gifData.pGlobalColorTable[gifData.backColorIndex];
					hBackBrush.CreateSolidBrush(RGB(backColor.r, backColor.g, backColor.b));
					WTL::CRect rc(&pPreviousFrame->boundingRectangle);
					rc.OffsetRect(position);
					targetDC.FillRect(&rc, hBackBrush);
				}
				break;
			case Frame::dmRestoreToWhatWasThereBefore:
				/* restore the area occupied by the previous frame to what was there before the previous frame was
				   rendered */
				if(frameToRenderBackgroundFor == gifData.bufferedFrame + 1) {
					// use the buffered data
					targetDC.BitBlt(position.x, position.y, gifData.logicalScreenRectangle.Width(), gifData.logicalScreenRectangle.Height(), gifData.screenWithoutCurrentFrame.dc, position.x, position.y, SRCCOPY);
				} else if(frameToRenderBackgroundFor == 1) {
					// restore the area occupied by the previous frame to the background color
					if(drawTransparent) {
						// use the control's background
						targetDC.BitBlt(position.x + pPreviousFrame->boundingRectangle.left, position.y + pPreviousFrame->boundingRectangle.top, pPreviousFrame->boundingRectangle.Width(), pPreviousFrame->boundingRectangle.Height(), gifData.screenWithBackgroundOnly.dc, position.x + pPreviousFrame->boundingRectangle.left, position.y + pPreviousFrame->boundingRectangle.top, SRCCOPY);
					} else {
						// use the GIF's background color
						WTL::CBrush hBackBrush;
						Color backColor = gifData.pGlobalColorTable[gifData.backColorIndex];
						hBackBrush.CreateSolidBrush(RGB(backColor.r, backColor.g, backColor.b));
						WTL::CRect rc(&pPreviousFrame->boundingRectangle);
						rc.OffsetRect(position);
						targetDC.FillRect(&rc, hBackBrush);
					}
				} else {
					// render recursively
					RenderGIFFrame(frameToRenderBackgroundFor - 2, targetDC, position);
				}
				break;
			default:
				ATLASSERT((pPreviousFrame->disposalMethod >= 0) && (pPreviousFrame->disposalMethod <= 3));
		}
	}
}


BOOL Animation::IsComctl32Version610OrNewer(void)
{
	DWORD major = 0;
	DWORD minor = 0;
	HRESULT hr = ATL::AtlGetCommCtrlVersion(&major, &minor);
	if(SUCCEEDED(hr)) {
		return (((major == 6) && (minor >= 10)) || (major > 6));
	}
	return FALSE;
}