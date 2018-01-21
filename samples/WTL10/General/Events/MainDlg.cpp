// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "MainDlg.h"
#include ".\maindlg.h"


BOOL CMainDlg::PreTranslateMessage(MSG* pMsg)
{
	return CWindow::IsDialogMessage(pMsg);
}

LRESULT CMainDlg::OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CloseDialog(0);
	return 0;
}

LRESULT CMainDlg::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	if(controls.animU) {
		IDispEventImpl<IDC_ANIMU, CMainDlg, &__uuidof(AnimLibU::_IAnimationEvents), &LIBID_AnimLibU, 2, 7>::DispEventUnadvise(controls.animU);
		controls.animU.Release();
	}
	if(controls.animA) {
		IDispEventImpl<IDC_ANIMA, CMainDlg, &__uuidof(AnimLibA::_IAnimationEvents), &LIBID_AnimLibA, 2, 7>::DispEventUnadvise(controls.animA);
		controls.animA.Release();
	}

	// unregister message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);

	bHandled = FALSE;
	return 0;
}

LRESULT CMainDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// Init resizing
	DlgResize_Init(false, false);

	// set icons
	HICON hIcon = static_cast<HICON>(LoadImage(ModuleHelper::GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), IMAGE_ICON, GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR));
	SetIcon(hIcon, TRUE);
	HICON hIconSmall = static_cast<HICON>(LoadImage(ModuleHelper::GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR));
	SetIcon(hIconSmall, FALSE);

	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);

	controls.logEdit = GetDlgItem(IDC_EDITLOG);
	controls.aboutButton = GetDlgItem(ID_APP_ABOUT);

	animUContainerWnd.SubclassWindow(GetDlgItem(IDC_ANIMU));
	animUContainerWnd.QueryControl(__uuidof(AnimLibU::IAnimation), reinterpret_cast<LPVOID*>(&controls.animU));
	if(controls.animU) {
		IDispEventImpl<IDC_ANIMU, CMainDlg, &__uuidof(AnimLibU::_IAnimationEvents), &LIBID_AnimLibU, 2, 7>::DispEventAdvise(controls.animU);
		animUWnd.SubclassWindow(static_cast<HWND>(LongToHandle(controls.animU->GethWnd())));
		SetupAnimationU();
	}

	animAContainerWnd.SubclassWindow(GetDlgItem(IDC_ANIMA));
	animAContainerWnd.QueryControl(__uuidof(AnimLibA::IAnimation), reinterpret_cast<LPVOID*>(&controls.animA));
	if(controls.animA) {
		IDispEventImpl<IDC_ANIMA, CMainDlg, &__uuidof(AnimLibA::_IAnimationEvents), &LIBID_AnimLibA, 2, 7>::DispEventAdvise(controls.animA);
		animAWnd.SubclassWindow(static_cast<HWND>(LongToHandle(controls.animA->GethWnd())));
		SetupAnimationA();
	}

	// force control resize
	WINDOWPOS dummy = {0};
	BOOL b = FALSE;
	OnWindowPosChanged(WM_WINDOWPOSCHANGED, 0, reinterpret_cast<LPARAM>(&dummy), b);

	return TRUE;
}

LRESULT CMainDlg::OnWindowPosChanged(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled)
{
	if(controls.logEdit && controls.aboutButton) {
		LPWINDOWPOS pDetails = reinterpret_cast<LPWINDOWPOS>(lParam);

		if((pDetails->flags & SWP_NOSIZE) == 0) {
			CRect rc;
			GetClientRect(&rc);
			int cx = static_cast<int>(0.4 * static_cast<double>(rc.Width()));
			controls.logEdit.SetWindowPos(NULL, rc.Width() - cx, 0, cx, rc.Height() - 32, 0);
			controls.aboutButton.SetWindowPos(NULL, rc.Width() - cx, rc.Height() - 27, 0, 0, SWP_NOSIZE);
			animUContainerWnd.SetWindowPos(NULL, 0, 0, rc.Width() - cx - 5, (rc.Height() - 5) / 2, SWP_NOMOVE);
			animAContainerWnd.SetWindowPos(NULL, 0, (rc.Height() - 5) / 2 + 5, rc.Width() - cx - 5, (rc.Height() - 5) / 2, 0);
		}
	}

	bHandled = FALSE;
	return 0;
}

LRESULT CMainDlg::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(controls.animU) {
		controls.animU->About();
	}
	return 0;
}

void CMainDlg::AddLogEntry(CAtlString text)
{
	static int cLines = 0;
	static CAtlString oldText;

	cLines++;
	if(cLines > 50) {
		// delete the first line
		int pos = oldText.Find(TEXT("\r\n"));
		oldText = oldText.Mid(pos + lstrlen(TEXT("\r\n")), oldText.GetLength());
		cLines--;
	}
	oldText += text;
	oldText += TEXT("\r\n");

	controls.logEdit.SetWindowText(oldText);
	int l = oldText.GetLength();
	controls.logEdit.SetSel(l, l);
}

void CMainDlg::CloseDialog(int nVal)
{
	DestroyWindow();
	PostQuitMessage(nVal);
}

void CMainDlg::SetupAnimationA(void)
{
	HMODULE hMod = LoadLibraryEx(TEXT("shell32.dll"), NULL, LOAD_LIBRARY_AS_DATAFILE);
	if(hMod) {
		if(controls.animA->OpenAnimationFromResource(HandleToLong(hMod), 165, _bstr_t("")) == VARIANT_FALSE) {
			controls.animA->OpenAnimationFromResource(HandleToLong(hMod), 164, _bstr_t(""));
		}
		FreeLibrary(hMod);
	}
}

void CMainDlg::SetupAnimationU(void)
{
	HMODULE hMod = LoadLibraryEx(TEXT("shell32.dll"), NULL, LOAD_LIBRARY_AS_DATAFILE);
	if(hMod) {
		if(controls.animU->OpenAnimationFromResource(HandleToLong(hMod), 165, _bstr_t("")) == VARIANT_FALSE) {
			controls.animU->OpenAnimationFromResource(HandleToLong(hMod), 164, _bstr_t(""));
		}
		FreeLibrary(hMod);
	}
}

void __stdcall CMainDlg::ClickAnimu(short button, short shift, long x, long y)
{
	CAtlString str;
	str.Format(TEXT("AnimU_Click: button=%i, shift=%i, x=%i, y=%i"), button, shift, x, y);

	AddLogEntry(str);
}

void __stdcall CMainDlg::ContextMenuAnimu(short button, short shift, long x, long y)
{
	CAtlString str;
	str.Format(TEXT("AnimU_ContextMenu: button=%i, shift=%i, x=%i, y=%i"), button, shift, x, y);

	AddLogEntry(str);
}

void __stdcall CMainDlg::DblClickAnimu(short button, short shift, long x, long y)
{
	CAtlString str;
	str.Format(TEXT("AnimU_DblClick: button=%i, shift=%i, x=%i, y=%i"), button, shift, x, y);

	AddLogEntry(str);
}

void __stdcall CMainDlg::DestroyedControlWindowAnimu(long hWnd)
{
	CAtlString str;
	str.Format(TEXT("AnimU_DestroyedControlWindow: hWnd=0x%X"), hWnd);

	AddLogEntry(str);
}

void __stdcall CMainDlg::MClickAnimu(short button, short shift, long x, long y)
{
	CAtlString str;
	str.Format(TEXT("AnimU_MClick: button=%i, shift=%i, x=%i, y=%i"), button, shift, x, y);

	AddLogEntry(str);
}

void __stdcall CMainDlg::MDblClickAnimu(short button, short shift, long x, long y)
{
	CAtlString str;
	str.Format(TEXT("AnimU_MDblClick: button=%i, shift=%i, x=%i, y=%i"), button, shift, x, y);

	AddLogEntry(str);
}

void __stdcall CMainDlg::MouseDownAnimu(short button, short shift, long x, long y)
{
	CAtlString str;
	str.Format(TEXT("AnimU_MouseDown: button=%i, shift=%i, x=%i, y=%i"), button, shift, x, y);

	AddLogEntry(str);
}

void __stdcall CMainDlg::MouseEnterAnimu(short button, short shift, long x, long y)
{
	CAtlString str;
	str.Format(TEXT("AnimU_MouseEnter: button=%i, shift=%i, x=%i, y=%i"), button, shift, x, y);

	AddLogEntry(str);
}

void __stdcall CMainDlg::MouseHoverAnimu(short button, short shift, long x, long y)
{
	CAtlString str;
	str.Format(TEXT("AnimU_MouseHover: button=%i, shift=%i, x=%i, y=%i"), button, shift, x, y);

	AddLogEntry(str);
}

void __stdcall CMainDlg::MouseLeaveAnimu(short button, short shift, long x, long y)
{
	CAtlString str;
	str.Format(TEXT("AnimU_MouseLeave: button=%i, shift=%i, x=%i, y=%i"), button, shift, x, y);

	AddLogEntry(str);
}

void __stdcall CMainDlg::MouseMoveAnimu(short button, short shift, long x, long y)
{
	CAtlString str;
	str.Format(TEXT("AnimU_MouseMove: button=%i, shift=%i, x=%i, y=%i"), button, shift, x, y);

	AddLogEntry(str);
}

void __stdcall CMainDlg::MouseUpAnimu(short button, short shift, long x, long y)
{
	CAtlString str;
	str.Format(TEXT("AnimU_MouseUp: button=%i, shift=%i, x=%i, y=%i"), button, shift, x, y);

	AddLogEntry(str);
}

void __stdcall CMainDlg::OLEDragDropAnimu(LPDISPATCH data, long* effect, short button, short shift, long x, long y)
{
	CAtlString str;
	CComQIPtr<AnimLibU::IOLEDataObject> pData = data;
	if(pData) {
		str += TEXT("AnimU_OLEDragDrop: data=");
		if(pData->GetFormat(CF_HDROP, -1, 1) != VARIANT_FALSE) {
			_variant_t files = pData->GetData(CF_HDROP, -1, 1);
			if(files.vt == (VT_BSTR | VT_ARRAY)) {
				CComSafeArray<BSTR> array(files.parray);
				CAtlString tmp;
				tmp.Format(TEXT("%u files"), array.GetCount());
				str += tmp;
			} else {
				str += TEXT("<ERROR>");
			}
		} else {
			str += TEXT("0 files");
		}
	} else {
		str += TEXT("AnimU_OLEDragDrop: data=NULL");
	}
	CAtlString tmp;
	tmp.Format(TEXT(", effect=%i, button=%i, shift=%i, x=%i, y=%i"), *effect, button, shift, x, y);
	str += tmp;

	AddLogEntry(str);

	if(pData->GetFormat(CF_HDROP, -1, 1) != VARIANT_FALSE) {
		_variant_t files = pData->GetData(CF_HDROP, -1, 1);
		if(files.vt == (VT_BSTR | VT_ARRAY)) {
			CComSafeArray<BSTR> array(files.parray);
			str = TEXT("");
			for(int i = array.GetLowerBound(); i <= array.GetUpperBound(); i++) {
				str += array.GetAt(i);
				str += TEXT("\r\n");
			}
			controls.animU->FinishOLEDragDrop();
			MessageBox(str, TEXT("Dropped files"));
		}
	}
}

void __stdcall CMainDlg::OLEDragEnterAnimu(LPDISPATCH data, long* effect, short button, short shift, long x, long y)
{
	CAtlString str;
	CComQIPtr<AnimLibU::IOLEDataObject> pData = data;
	if(pData) {
		str += TEXT("AnimU_OLEDragEnter: data=");
		if(pData->GetFormat(CF_HDROP, -1, 1) != VARIANT_FALSE) {
			_variant_t files = pData->GetData(CF_HDROP, -1, 1);
			if(files.vt == (VT_BSTR | VT_ARRAY)) {
				CComSafeArray<BSTR> array(files.parray);
				CAtlString tmp;
				tmp.Format(TEXT("%u files"), array.GetCount());
				str += tmp;
			} else {
				str += TEXT("<ERROR>");
			}
		} else {
			str += TEXT("0 files");
		}
	} else {
		str += TEXT("AnimU_OLEDragEnter: data=NULL");
	}
	CAtlString tmp;
	tmp.Format(TEXT(", effect=%i, button=%i, shift=%i, x=%i, y=%i"), *effect, button, shift, x, y);
	str += tmp;

	AddLogEntry(str);
}

void __stdcall CMainDlg::OLEDragLeaveAnimu(LPDISPATCH data, short button, short shift, long x, long y)
{
	CAtlString str;
	CComQIPtr<AnimLibU::IOLEDataObject> pData = data;
	if(pData) {
		str += TEXT("AnimU_OLEDragLeave: data=");
		if(pData->GetFormat(CF_HDROP, -1, 1) != VARIANT_FALSE) {
			_variant_t files = pData->GetData(CF_HDROP, -1, 1);
			if(files.vt == (VT_BSTR | VT_ARRAY)) {
				CComSafeArray<BSTR> array(files.parray);
				CAtlString tmp;
				tmp.Format(TEXT("%u files"), array.GetCount());
				str += tmp;
			} else {
				str += TEXT("<ERROR>");
			}
		} else {
			str += TEXT("0 files");
		}
	} else {
		str += TEXT("AnimU_OLEDragLeave: data=NULL");
	}

	CAtlString tmp;
	tmp.Format(TEXT(", button=%i, shift=%i, x=%i, y=%i"), button, shift, x, y);
	str += tmp;

	AddLogEntry(str);
}

void __stdcall CMainDlg::OLEDragMouseMoveAnimu(LPDISPATCH data, long* effect, short button, short shift, long x, long y)
{
	CAtlString str;
	CComQIPtr<AnimLibU::IOLEDataObject> pData = data;
	if(pData) {
		str += TEXT("AnimU_OLEDragMouseMove: data=");
		if(pData->GetFormat(CF_HDROP, -1, 1) != VARIANT_FALSE) {
			_variant_t files = pData->GetData(CF_HDROP, -1, 1);
			if(files.vt == (VT_BSTR | VT_ARRAY)) {
				CComSafeArray<BSTR> array(files.parray);
				CAtlString tmp;
				tmp.Format(TEXT("%u files"), array.GetCount());
				str += tmp;
			} else {
				str += TEXT("<ERROR>");
			}
		} else {
			str += TEXT("0 files");
		}
	} else {
		str += TEXT("AnimU_OLEDragMouseMove: data=NULL");
	}
	CAtlString tmp;
	tmp.Format(TEXT(", effect=%i, button=%i, shift=%i, x=%i, y=%i"), *effect, button, shift, x, y);
	str += tmp;

	AddLogEntry(str);
}

void __stdcall CMainDlg::RClickAnimu(short button, short shift, long x, long y)
{
	CAtlString str;
	str.Format(TEXT("AnimU_RClick: button=%i, shift=%i, x=%i, y=%i"), button, shift, x, y);

	AddLogEntry(str);
}

void __stdcall CMainDlg::RDblClickAnimu(short button, short shift, long x, long y)
{
	CAtlString str;
	str.Format(TEXT("AnimU_RDblClick: button=%i, shift=%i, x=%i, y=%i"), button, shift, x, y);

	AddLogEntry(str);
}

void __stdcall CMainDlg::RecreatedControlWindowAnimu(long hWnd)
{
	CAtlString str;
	str.Format(TEXT("AnimU_RecreatedControlWindow: hWnd=0x%X"), hWnd);

	AddLogEntry(str);
	SetupAnimationU();
}

void __stdcall CMainDlg::ResizedControlWindowAnimu()
{
	AddLogEntry(CAtlString(TEXT("AnimU_ResizedControlWindow")));
}

void __stdcall CMainDlg::StartedReplayAnimu()
{
	AddLogEntry(CAtlString(TEXT("AnimU_StartedReplay")));
}

void __stdcall CMainDlg::StoppedReplayAnimu()
{
	AddLogEntry(CAtlString(TEXT("AnimU_StoppedReplay")));
}

void __stdcall CMainDlg::XClickAnimu(short button, short shift, long x, long y)
{
	CAtlString str;
	str.Format(TEXT("AnimU_XClick: button=%i, shift=%i, x=%i, y=%i"), button, shift, x, y);

	AddLogEntry(str);
}

void __stdcall CMainDlg::XDblClickAnimu(short button, short shift, long x, long y)
{
	CAtlString str;
	str.Format(TEXT("AnimU_XDblClick: button=%i, shift=%i, x=%i, y=%i"), button, shift, x, y);

	AddLogEntry(str);
}


void __stdcall CMainDlg::ClickAnima(short button, short shift, long x, long y)
{
	CAtlString str;
	str.Format(TEXT("AnimA_Click: button=%i, shift=%i, x=%i, y=%i"), button, shift, x, y);

	AddLogEntry(str);
}

void __stdcall CMainDlg::ContextMenuAnima(short button, short shift, long x, long y)
{
	CAtlString str;
	str.Format(TEXT("AnimA_ContextMenu: button=%i, shift=%i, x=%i, y=%i"), button, shift, x, y);

	AddLogEntry(str);
}

void __stdcall CMainDlg::DblClickAnima(short button, short shift, long x, long y)
{
	CAtlString str;
	str.Format(TEXT("AnimA_DblClick: button=%i, shift=%i, x=%i, y=%i"), button, shift, x, y);

	AddLogEntry(str);
}

void __stdcall CMainDlg::DestroyedControlWindowAnima(long hWnd)
{
	CAtlString str;
	str.Format(TEXT("AnimA_DestroyedControlWindow: hWnd=0x%X"), hWnd);

	AddLogEntry(str);
}

void __stdcall CMainDlg::MClickAnima(short button, short shift, long x, long y)
{
	CAtlString str;
	str.Format(TEXT("AnimA_MClick: button=%i, shift=%i, x=%i, y=%i"), button, shift, x, y);

	AddLogEntry(str);
}

void __stdcall CMainDlg::MDblClickAnima(short button, short shift, long x, long y)
{
	CAtlString str;
	str.Format(TEXT("AnimA_MDblClick: button=%i, shift=%i, x=%i, y=%i"), button, shift, x, y);

	AddLogEntry(str);
}

void __stdcall CMainDlg::MouseDownAnima(short button, short shift, long x, long y)
{
	CAtlString str;
	str.Format(TEXT("AnimA_MouseDown: button=%i, shift=%i, x=%i, y=%i"), button, shift, x, y);

	AddLogEntry(str);
}

void __stdcall CMainDlg::MouseEnterAnima(short button, short shift, long x, long y)
{
	CAtlString str;
	str.Format(TEXT("AnimA_MouseEnter: button=%i, shift=%i, x=%i, y=%i"), button, shift, x, y);

	AddLogEntry(str);
}

void __stdcall CMainDlg::MouseHoverAnima(short button, short shift, long x, long y)
{
	CAtlString str;
	str.Format(TEXT("AnimA_MouseHover: button=%i, shift=%i, x=%i, y=%i"), button, shift, x, y);

	AddLogEntry(str);
}

void __stdcall CMainDlg::MouseLeaveAnima(short button, short shift, long x, long y)
{
	CAtlString str;
	str.Format(TEXT("AnimA_MouseLeave: button=%i, shift=%i, x=%i, y=%i"), button, shift, x, y);

	AddLogEntry(str);
}

void __stdcall CMainDlg::MouseMoveAnima(short button, short shift, long x, long y)
{
	CAtlString str;
	str.Format(TEXT("AnimA_MouseMove: button=%i, shift=%i, x=%i, y=%i"), button, shift, x, y);

	AddLogEntry(str);
}

void __stdcall CMainDlg::MouseUpAnima(short button, short shift, long x, long y)
{
	CAtlString str;
	str.Format(TEXT("AnimA_MouseUp: button=%i, shift=%i, x=%i, y=%i"), button, shift, x, y);

	AddLogEntry(str);
}

void __stdcall CMainDlg::OLEDragDropAnima(LPDISPATCH data, long* effect, short button, short shift, long x, long y)
{
	CAtlString str;
	CComQIPtr<AnimLibU::IOLEDataObject> pData = data;
	if(pData) {
		str += TEXT("AnimA_OLEDragDrop: data=");
		if(pData->GetFormat(CF_HDROP, -1, 1) != VARIANT_FALSE) {
			_variant_t files = pData->GetData(CF_HDROP, -1, 1);
			if(files.vt == (VT_BSTR | VT_ARRAY)) {
				CComSafeArray<BSTR> array(files.parray);
				CAtlString tmp;
				tmp.Format(TEXT("%u files"), array.GetCount());
				str += tmp;
			} else {
				str += TEXT("<ERROR>");
			}
		} else {
			str += TEXT("0 files");
		}
	} else {
		str += TEXT("AnimA_OLEDragDrop: data=NULL");
	}
	CAtlString tmp;
	tmp.Format(TEXT(", effect=%i, button=%i, shift=%i, x=%i, y=%i"), *effect, button, shift, x, y);
	str += tmp;

	AddLogEntry(str);

	if(pData->GetFormat(CF_HDROP, -1, 1) != VARIANT_FALSE) {
		_variant_t files = pData->GetData(CF_HDROP, -1, 1);
		if(files.vt == (VT_BSTR | VT_ARRAY)) {
			CComSafeArray<BSTR> array(files.parray);
			str = TEXT("");
			for(int i = array.GetLowerBound(); i <= array.GetUpperBound(); i++) {
				str += array.GetAt(i);
				str += TEXT("\r\n");
			}
			controls.animA->FinishOLEDragDrop();
			MessageBox(str, TEXT("Dropped files"));
		}
	}
}

void __stdcall CMainDlg::OLEDragEnterAnima(LPDISPATCH data, long* effect, short button, short shift, long x, long y)
{
	CAtlString str;
	CComQIPtr<AnimLibU::IOLEDataObject> pData = data;
	if(pData) {
		str += TEXT("AnimA_OLEDragEnter: data=");
		if(pData->GetFormat(CF_HDROP, -1, 1) != VARIANT_FALSE) {
			_variant_t files = pData->GetData(CF_HDROP, -1, 1);
			if(files.vt == (VT_BSTR | VT_ARRAY)) {
				CComSafeArray<BSTR> array(files.parray);
				CAtlString tmp;
				tmp.Format(TEXT("%u files"), array.GetCount());
				str += tmp;
			} else {
				str += TEXT("<ERROR>");
			}
		} else {
			str += TEXT("0 files");
		}
	} else {
		str += TEXT("AnimA_OLEDragEnter: data=NULL");
	}
	CAtlString tmp;
	tmp.Format(TEXT(", effect=%i, button=%i, shift=%i, x=%i, y=%i"), *effect, button, shift, x, y);
	str += tmp;

	AddLogEntry(str);
}

void __stdcall CMainDlg::OLEDragLeaveAnima(LPDISPATCH data, short button, short shift, long x, long y)
{
	CAtlString str;
	CComQIPtr<AnimLibU::IOLEDataObject> pData = data;
	if(pData) {
		str += TEXT("AnimA_OLEDragLeave: data=");
		if(pData->GetFormat(CF_HDROP, -1, 1) != VARIANT_FALSE) {
			_variant_t files = pData->GetData(CF_HDROP, -1, 1);
			if(files.vt == (VT_BSTR | VT_ARRAY)) {
				CComSafeArray<BSTR> array(files.parray);
				CAtlString tmp;
				tmp.Format(TEXT("%u files"), array.GetCount());
				str += tmp;
			} else {
				str += TEXT("<ERROR>");
			}
		} else {
			str += TEXT("0 files");
		}
	} else {
		str += TEXT("AnimA_OLEDragLeave: data=NULL");
	}

	CAtlString tmp;
	tmp.Format(TEXT(", button=%i, shift=%i, x=%i, y=%i"), button, shift, x, y);
	str += tmp;

	AddLogEntry(str);
}

void __stdcall CMainDlg::OLEDragMouseMoveAnima(LPDISPATCH data, long* effect, short button, short shift, long x, long y)
{
	CAtlString str;
	CComQIPtr<AnimLibU::IOLEDataObject> pData = data;
	if(pData) {
		str += TEXT("AnimA_OLEDragMouseMove: data=");
		if(pData->GetFormat(CF_HDROP, -1, 1) != VARIANT_FALSE) {
			_variant_t files = pData->GetData(CF_HDROP, -1, 1);
			if(files.vt == (VT_BSTR | VT_ARRAY)) {
				CComSafeArray<BSTR> array(files.parray);
				CAtlString tmp;
				tmp.Format(TEXT("%u files"), array.GetCount());
				str += tmp;
			} else {
				str += TEXT("<ERROR>");
			}
		} else {
			str += TEXT("0 files");
		}
	} else {
		str += TEXT("AnimA_OLEDragMouseMove: data=NULL");
	}
	CAtlString tmp;
	tmp.Format(TEXT(", effect=%i, button=%i, shift=%i, x=%i, y=%i"), *effect, button, shift, x, y);
	str += tmp;

	AddLogEntry(str);
}

void __stdcall CMainDlg::RClickAnima(short button, short shift, long x, long y)
{
	CAtlString str;
	str.Format(TEXT("AnimA_RClick: button=%i, shift=%i, x=%i, y=%i"), button, shift, x, y);

	AddLogEntry(str);
}

void __stdcall CMainDlg::RDblClickAnima(short button, short shift, long x, long y)
{
	CAtlString str;
	str.Format(TEXT("AnimA_RDblClick: button=%i, shift=%i, x=%i, y=%i"), button, shift, x, y);

	AddLogEntry(str);
}

void __stdcall CMainDlg::RecreatedControlWindowAnima(long hWnd)
{
	CAtlString str;
	str.Format(TEXT("AnimA_RecreatedControlWindow: hWnd=0x%X"), hWnd);

	AddLogEntry(str);
	SetupAnimationU();
}

void __stdcall CMainDlg::ResizedControlWindowAnima()
{
	AddLogEntry(CAtlString(TEXT("AnimA_ResizedControlWindow")));
}

void __stdcall CMainDlg::StartedReplayAnima()
{
	AddLogEntry(CAtlString(TEXT("AnimA_StartedReplay")));
}

void __stdcall CMainDlg::StoppedReplayAnima()
{
	AddLogEntry(CAtlString(TEXT("AnimA_StoppedReplay")));
}

void __stdcall CMainDlg::XClickAnima(short button, short shift, long x, long y)
{
	CAtlString str;
	str.Format(TEXT("AnimA_XClick: button=%i, shift=%i, x=%i, y=%i"), button, shift, x, y);

	AddLogEntry(str);
}

void __stdcall CMainDlg::XDblClickAnima(short button, short shift, long x, long y)
{
	CAtlString str;
	str.Format(TEXT("AnimA_XDblClick: button=%i, shift=%i, x=%i, y=%i"), button, shift, x, y);

	AddLogEntry(str);
}
