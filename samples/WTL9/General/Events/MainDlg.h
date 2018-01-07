// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////
#pragma once
#include <initguid.h>

#import <libid:49D3E26C-8EA8-4137-86CE-D83F41BD4741> version("2.7") raw_dispinterfaces
#import <libid:CBA795C4-6941-484d-AE26-6A7EE9170E34> version("2.7") raw_dispinterfaces

DEFINE_GUID(LIBID_AnimLibU, 0x49D3E26C, 0x8EA8, 0x4137, 0x86, 0xCE, 0xD8, 0x3F, 0x41, 0xBD, 0x47, 0x41);
DEFINE_GUID(LIBID_AnimLibA, 0xCBA795C4, 0x6941, 0x484d, 0xAE, 0x26, 0x6A, 0x7E, 0xE9, 0x17, 0x0E, 0x34);

class CMainDlg :
    public CAxDialogImpl<CMainDlg>,
    public CMessageFilter,
    public CDialogResize<CMainDlg>,
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CMainDlg>,
    public IDispEventImpl<IDC_ANIMU, CMainDlg, &__uuidof(AnimLibU::_IAnimationEvents), &LIBID_AnimLibU, 2, 7>,
    public IDispEventImpl<IDC_ANIMA, CMainDlg, &__uuidof(AnimLibA::_IAnimationEvents), &LIBID_AnimLibA, 2, 7>
{
public:
	enum { IDD = IDD_MAINDLG };

	CContainedWindowT<CAxWindow> animUContainerWnd;
	CContainedWindowT<CWindow> animUWnd;
	CContainedWindowT<CAxWindow> animAContainerWnd;
	CContainedWindowT<CWindow> animAWnd;

	CMainDlg() :
	    animUContainerWnd(this, 1),
	    animAContainerWnd(this, 2),
	    animUWnd(this, 3),
	    animAWnd(this, 4)
	{
	}

	struct Controls
	{
		CEdit logEdit;
		CButton aboutButton;
		CComPtr<AnimLibU::IAnimation> animU;
		CComPtr<AnimLibA::IAnimation> animA;
	} controls;

	virtual BOOL PreTranslateMessage(MSG* pMsg);

	BEGIN_MSG_MAP(CMainDlg)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_WINDOWPOSCHANGED, OnWindowPosChanged)

		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)

		CHAIN_MSG_MAP(CDialogResize<CMainDlg>)

		ALT_MSG_MAP(1)
		ALT_MSG_MAP(2)
		ALT_MSG_MAP(3)
		ALT_MSG_MAP(4)
	END_MSG_MAP()

	BEGIN_SINK_MAP(CMainDlg)
		SINK_ENTRY_EX(IDC_ANIMU, __uuidof(AnimLibU::_IAnimationEvents), 0, ClickAnimu)
		SINK_ENTRY_EX(IDC_ANIMU, __uuidof(AnimLibU::_IAnimationEvents), 1, ContextMenuAnimu)
		SINK_ENTRY_EX(IDC_ANIMU, __uuidof(AnimLibU::_IAnimationEvents), 2, DblClickAnimu)
		SINK_ENTRY_EX(IDC_ANIMU, __uuidof(AnimLibU::_IAnimationEvents), 3, DestroyedControlWindowAnimu)
		SINK_ENTRY_EX(IDC_ANIMU, __uuidof(AnimLibU::_IAnimationEvents), 4, MClickAnimu)
		SINK_ENTRY_EX(IDC_ANIMU, __uuidof(AnimLibU::_IAnimationEvents), 5, MDblClickAnimu)
		SINK_ENTRY_EX(IDC_ANIMU, __uuidof(AnimLibU::_IAnimationEvents), 6, MouseDownAnimu)
		SINK_ENTRY_EX(IDC_ANIMU, __uuidof(AnimLibU::_IAnimationEvents), 7, MouseEnterAnimu)
		SINK_ENTRY_EX(IDC_ANIMU, __uuidof(AnimLibU::_IAnimationEvents), 8, MouseHoverAnimu)
		SINK_ENTRY_EX(IDC_ANIMU, __uuidof(AnimLibU::_IAnimationEvents), 9, MouseLeaveAnimu)
		//SINK_ENTRY_EX(IDC_ANIMU, __uuidof(AnimLibU::_IAnimationEvents), 10, MouseMoveAnimu)
		SINK_ENTRY_EX(IDC_ANIMU, __uuidof(AnimLibU::_IAnimationEvents), 11, MouseUpAnimu)
		SINK_ENTRY_EX(IDC_ANIMU, __uuidof(AnimLibU::_IAnimationEvents), 12, OLEDragDropAnimu)
		SINK_ENTRY_EX(IDC_ANIMU, __uuidof(AnimLibU::_IAnimationEvents), 13, OLEDragEnterAnimu)
		SINK_ENTRY_EX(IDC_ANIMU, __uuidof(AnimLibU::_IAnimationEvents), 14, OLEDragLeaveAnimu)
		//SINK_ENTRY_EX(IDC_ANIMU, __uuidof(AnimLibU::_IAnimationEvents), 15, OLEDragMouseMoveAnimu)
		SINK_ENTRY_EX(IDC_ANIMU, __uuidof(AnimLibU::_IAnimationEvents), 16, RClickAnimu)
		SINK_ENTRY_EX(IDC_ANIMU, __uuidof(AnimLibU::_IAnimationEvents), 17, RDblClickAnimu)
		SINK_ENTRY_EX(IDC_ANIMU, __uuidof(AnimLibU::_IAnimationEvents), 18, RecreatedControlWindowAnimu)
		SINK_ENTRY_EX(IDC_ANIMU, __uuidof(AnimLibU::_IAnimationEvents), 19, ResizedControlWindowAnimu)
		SINK_ENTRY_EX(IDC_ANIMU, __uuidof(AnimLibU::_IAnimationEvents), 20, StartedReplayAnimu)
		SINK_ENTRY_EX(IDC_ANIMU, __uuidof(AnimLibU::_IAnimationEvents), 21, StoppedReplayAnimu)
		SINK_ENTRY_EX(IDC_ANIMU, __uuidof(AnimLibU::_IAnimationEvents), 22, XClickAnimu)
		SINK_ENTRY_EX(IDC_ANIMU, __uuidof(AnimLibU::_IAnimationEvents), 23, XDblClickAnimu)

		SINK_ENTRY_EX(IDC_ANIMA, __uuidof(AnimLibA::_IAnimationEvents), 0, ClickAnima)
		SINK_ENTRY_EX(IDC_ANIMA, __uuidof(AnimLibA::_IAnimationEvents), 1, ContextMenuAnima)
		SINK_ENTRY_EX(IDC_ANIMA, __uuidof(AnimLibA::_IAnimationEvents), 2, DblClickAnima)
		SINK_ENTRY_EX(IDC_ANIMA, __uuidof(AnimLibA::_IAnimationEvents), 3, DestroyedControlWindowAnima)
		SINK_ENTRY_EX(IDC_ANIMA, __uuidof(AnimLibA::_IAnimationEvents), 4, MClickAnima)
		SINK_ENTRY_EX(IDC_ANIMA, __uuidof(AnimLibA::_IAnimationEvents), 5, MDblClickAnima)
		SINK_ENTRY_EX(IDC_ANIMA, __uuidof(AnimLibA::_IAnimationEvents), 6, MouseDownAnima)
		SINK_ENTRY_EX(IDC_ANIMA, __uuidof(AnimLibA::_IAnimationEvents), 7, MouseEnterAnima)
		SINK_ENTRY_EX(IDC_ANIMA, __uuidof(AnimLibA::_IAnimationEvents), 8, MouseHoverAnima)
		SINK_ENTRY_EX(IDC_ANIMA, __uuidof(AnimLibA::_IAnimationEvents), 9, MouseLeaveAnima)
		//SINK_ENTRY_EX(IDC_ANIMA, __uuidof(AnimLibA::_IAnimationEvents), 10, MouseMoveAnima)
		SINK_ENTRY_EX(IDC_ANIMA, __uuidof(AnimLibA::_IAnimationEvents), 11, MouseUpAnima)
		SINK_ENTRY_EX(IDC_ANIMA, __uuidof(AnimLibA::_IAnimationEvents), 12, OLEDragDropAnima)
		SINK_ENTRY_EX(IDC_ANIMA, __uuidof(AnimLibA::_IAnimationEvents), 13, OLEDragEnterAnima)
		SINK_ENTRY_EX(IDC_ANIMA, __uuidof(AnimLibA::_IAnimationEvents), 14, OLEDragLeaveAnima)
		//SINK_ENTRY_EX(IDC_ANIMA, __uuidof(AnimLibA::_IAnimationEvents), 15, OLEDragMouseMoveAnima)
		SINK_ENTRY_EX(IDC_ANIMA, __uuidof(AnimLibA::_IAnimationEvents), 16, RClickAnima)
		SINK_ENTRY_EX(IDC_ANIMA, __uuidof(AnimLibA::_IAnimationEvents), 17, RDblClickAnima)
		SINK_ENTRY_EX(IDC_ANIMA, __uuidof(AnimLibA::_IAnimationEvents), 18, RecreatedControlWindowAnima)
		SINK_ENTRY_EX(IDC_ANIMA, __uuidof(AnimLibA::_IAnimationEvents), 19, ResizedControlWindowAnima)
		SINK_ENTRY_EX(IDC_ANIMA, __uuidof(AnimLibA::_IAnimationEvents), 20, StartedReplayAnima)
		SINK_ENTRY_EX(IDC_ANIMA, __uuidof(AnimLibA::_IAnimationEvents), 21, StoppedReplayAnima)
		SINK_ENTRY_EX(IDC_ANIMA, __uuidof(AnimLibA::_IAnimationEvents), 22, XClickAnima)
		SINK_ENTRY_EX(IDC_ANIMA, __uuidof(AnimLibA::_IAnimationEvents), 23, XDblClickAnima)
	END_SINK_MAP()

	BEGIN_DLGRESIZE_MAP(CMainDlg)
	END_DLGRESIZE_MAP()

	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnWindowPosChanged(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled);
	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	void AddLogEntry(CAtlString text);
	void CloseDialog(int nVal);
	void SetupAnimationA(void);
	void SetupAnimationU(void);

	void __stdcall ClickAnimu(short button, short shift, long x, long y);
	void __stdcall ContextMenuAnimu(short button, short shift, long x, long y);
	void __stdcall DblClickAnimu(short button, short shift, long x, long y);
	void __stdcall DestroyedControlWindowAnimu(long hWnd);
	void __stdcall MClickAnimu(short button, short shift, long x, long y);
	void __stdcall MDblClickAnimu(short button, short shift, long x, long y);
	void __stdcall MouseDownAnimu(short button, short shift, long x, long y);
	void __stdcall MouseEnterAnimu(short button, short shift, long x, long y);
	void __stdcall MouseHoverAnimu(short button, short shift, long x, long y);
	void __stdcall MouseLeaveAnimu(short button, short shift, long x, long y);
	void __stdcall MouseMoveAnimu(short button, short shift, long x, long y);
	void __stdcall MouseUpAnimu(short button, short shift, long x, long y);
	void __stdcall OLEDragDropAnimu(LPDISPATCH data, long* effect, short button, short shift, long x, long y);
	void __stdcall OLEDragEnterAnimu(LPDISPATCH data, long* effect, short button, short shift, long x, long y);
	void __stdcall OLEDragLeaveAnimu(LPDISPATCH data, short button, short shift, long x, long y);
	void __stdcall OLEDragMouseMoveAnimu(LPDISPATCH data, long* effect, short button, short shift, long x, long y);
	void __stdcall RClickAnimu(short button, short shift, long x, long y);
	void __stdcall RDblClickAnimu(short button, short shift, long x, long y);
	void __stdcall RecreatedControlWindowAnimu(long hWnd);
	void __stdcall ResizedControlWindowAnimu();
	void __stdcall StartedReplayAnimu();
	void __stdcall StoppedReplayAnimu();
	void __stdcall XClickAnimu(short button, short shift, long x, long y);
	void __stdcall XDblClickAnimu(short button, short shift, long x, long y);

	void __stdcall ClickAnima(short button, short shift, long x, long y);
	void __stdcall ContextMenuAnima(short button, short shift, long x, long y);
	void __stdcall DblClickAnima(short button, short shift, long x, long y);
	void __stdcall DestroyedControlWindowAnima(long hWnd);
	void __stdcall MClickAnima(short button, short shift, long x, long y);
	void __stdcall MDblClickAnima(short button, short shift, long x, long y);
	void __stdcall MouseDownAnima(short button, short shift, long x, long y);
	void __stdcall MouseEnterAnima(short button, short shift, long x, long y);
	void __stdcall MouseHoverAnima(short button, short shift, long x, long y);
	void __stdcall MouseLeaveAnima(short button, short shift, long x, long y);
	void __stdcall MouseMoveAnima(short button, short shift, long x, long y);
	void __stdcall MouseUpAnima(short button, short shift, long x, long y);
	void __stdcall OLEDragDropAnima(LPDISPATCH data, long* effect, short button, short shift, long x, long y);
	void __stdcall OLEDragEnterAnima(LPDISPATCH data, long* effect, short button, short shift, long x, long y);
	void __stdcall OLEDragLeaveAnima(LPDISPATCH data, short button, short shift, long x, long y);
	void __stdcall OLEDragMouseMoveAnima(LPDISPATCH data, long* effect, short button, short shift, long x, long y);
	void __stdcall RClickAnima(short button, short shift, long x, long y);
	void __stdcall RDblClickAnima(short button, short shift, long x, long y);
	void __stdcall RecreatedControlWindowAnima(long hWnd);
	void __stdcall ResizedControlWindowAnima();
	void __stdcall StartedReplayAnima();
	void __stdcall StoppedReplayAnima();
	void __stdcall XClickAnima(short button, short shift, long x, long y);
	void __stdcall XDblClickAnima(short button, short shift, long x, long y);
};
