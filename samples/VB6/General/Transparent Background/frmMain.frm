VERSION 5.00
Object = "{49D3E26C-8EA8-4137-86CE-D83F41BD4741}#2.7#0"; "AnimU.ocx"
Begin VB.Form frmMain 
   BorderStyle     =   3  'Fester Dialog
   Caption         =   "Animation 2.7 - Transparent Background Sample"
   ClientHeight    =   2925
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   7800
   BeginProperty Font 
      Name            =   "Tahoma"
      Size            =   8.25
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   Picture         =   "frmMain.frx":0000
   ScaleHeight     =   195
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   520
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'Bildschirmmitte
   Begin VB.CommandButton cmdAbout 
      Caption         =   "&About..."
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   6240
      TabIndex        =   0
      Top             =   120
      Width           =   1455
   End
   Begin AnimLibUCtl.Animation AnimU 
      Height          =   2775
      Left            =   0
      Top             =   0
      Width           =   6015
      _cx             =   10610
      _cy             =   4895
      AnimationBackStyle=   0
      Appearance      =   0
      AutoStartReplay =   -1  'True
      BackColor       =   -2147483633
      BorderStyle     =   0
      CenterAnimation =   -1  'True
      DisabledEvents  =   3
      DontRedraw      =   0   'False
      Enabled         =   -1  'True
      HoverTime       =   -1
      MousePointer    =   0
      RegisterForOLEDragDrop=   -1  'True
      SupportOLEDragImages=   -1  'True
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

  Implements ISubclassedWindow


  Private Type DLLVERSIONINFO
    cbSize As Long
    dwMajor As Long
    dwMinor As Long
    dwBuildNumber As Long
    dwPlatformId As Long
  End Type

  Private Type POINTAPI
    x As Long
    y As Long
  End Type

  Private Type RECT
    Left As Long
    Top As Long
    Right As Long
    Bottom As Long
  End Type


  Private hBackBrush As Long


  Private Declare Function BitBlt Lib "gdi32.dll" (ByVal hDestDC As Long, ByVal x As Long, ByVal y As Long, ByVal nWidth As Long, ByVal nHeight As Long, ByVal hSrcDC As Long, ByVal xSrc As Long, ByVal ySrc As Long, ByVal dwRop As Long) As Long
  Private Declare Function CreateCompatibleBitmap Lib "gdi32.dll" (ByVal hDC As Long, ByVal nWidth As Long, ByVal nHeight As Long) As Long
  Private Declare Function CreateCompatibleDC Lib "gdi32.dll" (ByVal hDC As Long) As Long
  Private Declare Function CreatePatternBrush Lib "gdi32.dll" (ByVal hBitmap As Long) As Long
  Private Declare Function DeleteDC Lib "gdi32.dll" (ByVal hDC As Long) As Long
  Private Declare Function DeleteObject Lib "gdi32.dll" (ByVal hObject As Long) As Long
  Private Declare Function DllGetVersion_comctl32 Lib "comctl32.dll" Alias "DllGetVersion" (Data As DLLVERSIONINFO) As Long
  Private Declare Function FreeLibrary Lib "kernel32.dll" (ByVal hModule As Long) As Long
  Private Declare Function GetWindowRect Lib "user32.dll" (ByVal hWnd As Long, ByRef lpRect As RECT) As Long
  Private Declare Sub InitCommonControls Lib "comctl32.dll" ()
  Private Declare Function LoadLibrary Lib "kernel32.dll" Alias "LoadLibraryW" (ByVal lpFileName As Long) As Long
  Private Declare Function ScreenToClient Lib "user32.dll" (ByVal hWnd As Long, ByRef lpPoint As POINTAPI) As Long
  Private Declare Function SelectObject Lib "gdi32.dll" (ByVal hDC As Long, ByVal hObject As Long) As Long


Private Function ISubclassedWindow_HandleMessage(ByVal hWnd As Long, ByVal uMsg As Long, ByVal wParam As Long, ByVal lParam As Long, ByVal eSubclassID As EnumSubclassID, bCallDefProc As Boolean) As Long
  Dim lRet As Long

  On Error GoTo StdHandler_Error
  Select Case eSubclassID
    Case EnumSubclassID.escidFrmMain
      lRet = HandleMessage_Form(hWnd, uMsg, wParam, lParam, bCallDefProc)
    Case Else
      Debug.Print "frmMain.ISubclassedWindow_HandleMessage: Unknown Subclassing ID " & CStr(eSubclassID)
  End Select

StdHandler_Ende:
  ISubclassedWindow_HandleMessage = lRet
  Exit Function

StdHandler_Error:
  Debug.Print "Error in frmMain.ISubclassedWindow_HandleMessage (SubclassID=" & CStr(eSubclassID) & ": ", Err.Number, Err.Description
  Resume StdHandler_Ende
End Function

Private Function HandleMessage_Form(ByVal hWnd As Long, ByVal uMsg As Long, ByVal wParam As Long, ByVal lParam As Long, bCallDefProc As Boolean) As Long
  Const SRCCOPY = &HCC0020
  Const WM_CTLCOLORSTATIC = &H138
  Dim hAnimBkDC As Long
  Dim hAnimationBackgroundTexture As Long
  Dim hDialogBkDC As Long
  Dim hPreviousBitmap1 As Long
  Dim hPreviousBitmap2 As Long
  Dim pt As POINTAPI
  Dim lRet As Long
  Dim windowRectangle As RECT

  On Error GoTo StdHandler_Error
  Select Case uMsg
    Case WM_CTLCOLORSTATIC
      ' draw the control's background into a bitmap and create a pattern brush from it
      ' Windows will use this brush whenever it needs to draw the control's background
      If hBackBrush Then
        DeleteObject hBackBrush
        hBackBrush = 0
      End If
      GetWindowRect lParam, windowRectangle
      pt.x = windowRectangle.Left
      pt.y = windowRectangle.Top
      ScreenToClient Me.hWnd, pt
      windowRectangle.Left = pt.x
      windowRectangle.Top = pt.y
      pt.x = windowRectangle.Right
      pt.y = windowRectangle.Bottom
      ScreenToClient Me.hWnd, pt
      windowRectangle.Right = pt.x
      windowRectangle.Bottom = pt.y

      hAnimBkDC = CreateCompatibleDC(wParam)
      hAnimationBackgroundTexture = CreateCompatibleBitmap(wParam, windowRectangle.Right - windowRectangle.Left, windowRectangle.Bottom - windowRectangle.Top)
      hPreviousBitmap1 = SelectObject(hAnimBkDC, hAnimationBackgroundTexture)

      hDialogBkDC = CreateCompatibleDC(wParam)
      hPreviousBitmap2 = SelectObject(hDialogBkDC, Me.Picture.Handle)

      BitBlt hAnimBkDC, 0, 0, windowRectangle.Right - windowRectangle.Left, windowRectangle.Bottom - windowRectangle.Top, hDialogBkDC, windowRectangle.Left, windowRectangle.Top, SRCCOPY

      SelectObject hDialogBkDC, hPreviousBitmap2
      SelectObject hAnimBkDC, hPreviousBitmap1

      hBackBrush = CreatePatternBrush(hAnimationBackgroundTexture)

      DeleteObject hAnimationBackgroundTexture
      DeleteDC hAnimBkDC
      DeleteDC hDialogBkDC

      lRet = hBackBrush
      bCallDefProc = False
  End Select

StdHandler_Ende:
  HandleMessage_Form = lRet
  Exit Function

StdHandler_Error:
  Debug.Print "Error in frmMain.HandleMessage_Form: ", Err.Number, Err.Description
  Resume StdHandler_Ende
End Function


Private Sub AnimU_RecreatedControlWindow(ByVal hWnd As Long)
  SetupAnimationU
End Sub

Private Sub cmdAbout_Click()
  AnimU.About
End Sub

Private Sub Form_Initialize()
  Dim bComctl32Version600OrNewer As Boolean
  Dim DLLVerData As DLLVERSIONINFO

  InitCommonControls

  With DLLVerData
    .cbSize = LenB(DLLVerData)
    DllGetVersion_comctl32 DLLVerData
    bComctl32Version600OrNewer = (.dwMajor >= 6)
  End With

  If Not bComctl32Version600OrNewer Then
    MsgBox "This sample requires version 6.0 or newer of comctl32.dll.", VbMsgBoxStyle.vbCritical, "Error"
    End
  End If
End Sub

Private Sub Form_Load()
  If Not SubclassWindow(Me.hWnd, Me, EnumSubclassID.escidFrmMain) Then
    Debug.Print "Subclassing failed!"
  End If

  SetupAnimationU
End Sub

Private Sub Form_Unload(Cancel As Integer)
  If Not UnSubclassWindow(Me.hWnd, EnumSubclassID.escidFrmMain) Then
    Debug.Print "UnSubclassing failed!"
  End If

  If hBackBrush Then
    DeleteObject hBackBrush
  End If
End Sub


Private Sub SetupAnimationU()
  Dim hMod As Long

  hMod = LoadLibrary(StrPtr("shell32.dll"))
  If hMod Then
    If Not AnimU.OpenAnimationFromResource(hMod, 165, "") Then
      AnimU.OpenAnimationFromResource hMod, 164, ""
    End If
    FreeLibrary hMod
  End If
End Sub
