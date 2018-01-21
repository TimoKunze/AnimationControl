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

LRESULT CMainDlg::OnCtlColorDlg(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	return reinterpret_cast<LRESULT>(static_cast<HBRUSH>(dialogBackgroundBrush));
}

LRESULT CMainDlg::OnCtlColorStatic(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if(static_cast<HWND>(LongToHandle(controls.animU->GethWnd())) == reinterpret_cast<HWND>(lParam)) {
		if(!animationBackgroundBrush.IsNull()) {
			animationBackgroundBrush.DeleteObject();
		}

		CRect windowRectangle;
		::GetWindowRect(reinterpret_cast<HWND>(lParam), &windowRectangle);
		ScreenToClient(&windowRectangle);
		WTL::CBitmap animationBackgroundTexture;
		WTL::CDC animBkDC;
		animBkDC.CreateCompatibleDC(reinterpret_cast<HDC>(wParam));
		animationBackgroundTexture.CreateCompatibleBitmap(reinterpret_cast<HDC>(wParam), windowRectangle.Width(), windowRectangle.Height());
		HBITMAP hPreviousBitmap1 = animBkDC.SelectBitmap(animationBackgroundTexture);

		WTL::CDC dialogBkDC;
		dialogBkDC.CreateCompatibleDC(reinterpret_cast<HDC>(wParam));
		HBITMAP hPreviousBitmap2 = dialogBkDC.SelectBitmap(dialogBackgroundTexture);

		animBkDC.BitBlt(0, 0, windowRectangle.Width(), windowRectangle.Height(), dialogBkDC, windowRectangle.left, windowRectangle.top, SRCCOPY);

		dialogBkDC.SelectBitmap(hPreviousBitmap2);
		animBkDC.SelectBitmap(hPreviousBitmap1);

		animationBackgroundBrush.CreatePatternBrush(animationBackgroundTexture);
		return reinterpret_cast<LRESULT>(static_cast<HBRUSH>(animationBackgroundBrush));
	}
	bHandled = FALSE;
	return 0;
}

LRESULT CMainDlg::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	if(controls.animU) {
		DispEventUnadvise(controls.animU);
		controls.animU.Release();
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

	dialogBackgroundTexture = LoadBitmap(ModuleHelper::GetResourceInstance(), MAKEINTRESOURCE(IDB_BACKGROUND));
	dialogBackgroundBrush.CreatePatternBrush(dialogBackgroundTexture);

	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);

	controls.aboutButton = GetDlgItem(ID_APP_ABOUT);

	animUWnd.SubclassWindow(GetDlgItem(IDC_ANIMU));
	animUWnd.QueryControl(__uuidof(IAnimation), reinterpret_cast<LPVOID*>(&controls.animU));
	if(controls.animU) {
		DispEventAdvise(controls.animU);
		SetupAnimationU();
	}

	return TRUE;
}

LRESULT CMainDlg::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(controls.animU) {
		controls.animU->About();
	}
	return 0;
}

void CMainDlg::CloseDialog(int nVal)
{
	DestroyWindow();
	PostQuitMessage(nVal);
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

void __stdcall CMainDlg::RecreatedControlWindowAnimu(long /*hWnd*/)
{
	SetupAnimationU();
}
