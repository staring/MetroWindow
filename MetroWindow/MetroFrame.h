#pragma once

#include "stdafx.h"
#include "CaptionButton.h"
#include "DwmApi.h"
#include "UxThemeApi.h"
#include <vector>

namespace MetroWindow
{

class METROWINDOW_DECL CMetroFrame
{
public:
    CMetroFrame(HINSTANCE hInstance);
    virtual ~CMetroFrame(void);

    HWND GetHWnd() const { return _hWnd; }
	operator HWND() const { return _hWnd; }

	HINSTANCE GetModuleInstance() const { return _hInst; }

    void SetIcon(UINT nIconRes, UINT nSmallIconRes = 0);

    HICON GetIcon() const { return _hIcon; }
    HICON GetSmallIcon() const { return _hSmallIcon; }

    void Close(UINT nRet = IDOK);

    void CenterWindow(HWND hWndCenter = NULL);

protected:
    virtual LRESULT OnWndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

    virtual LRESULT OnSetText(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    virtual LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    virtual LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    virtual LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    virtual LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    virtual LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    virtual LRESULT OnNcLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    virtual LRESULT OnNcMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    virtual LRESULT OnNcLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    virtual LRESULT OnNcRButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    virtual LRESULT OnWmLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    virtual LRESULT OnNcMouseLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    virtual LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    virtual LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    virtual LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    virtual LRESULT OnDwmCompositionChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    virtual LRESULT OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

private:
    void RemoveWindowBorderStyle();
    BOOL ModifyWindowStyle(LONG removeStyle, LONG addStyle);
    BOOL PaintNonClientArea(HRGN hrgnUpdate);
    void DrawWindowFrame(HDC hdc, const RECT& bounds, const SIZE& borderSize, int captionHeight);
    void DrawCaptionTitle(HDC hdc, LPWSTR title, RECT bounds, COLORREF color);
    void DrawThemeCaptionTitleEx(HDC hdc, LPCWSTR title, const RECT& bounds, COLORREF color, COLORREF bgColor);
    void UpdateCaptionButtons();
    int GetCaptionHeight();
    RECT GetFrameIconBounds(const RECT& windowBounds, SIZE borderSize);
    void FillSolidRect(HDC hdc, LPCRECT lpRect, COLORREF clr);
    MetroRefPtr<CCaptionButton> CommandButtonFromPoint(POINT point);
    MetroRefPtr<CCaptionButton> CommandButtonByHitTest(LONG hitTest);
    void ShowSystemMenu(POINT point);

protected:
    HINSTANCE _hInst;
    HWND _hWnd;
    HICON _hIcon;
    HICON _hSmallIcon;

private:
    HFONT _hCaptionFont;

    bool _isDwmEnabled;
    bool _isUxThemeSupported;
    bool _traceNCMouse;
    bool _isNonClientAreaActive;
    bool _isSizing;
    bool _prepareFullScreen;
    bool _isFullScreen;
    int _captionHeight;

    bool _useCustomTitle;
    bool _clientAreaMovable;
    bool _useThickFrame;
    bool _showIconOnCaption;

    TRACKMOUSEEVENT _trackMouseEvent;

    CDwmApi _dwmApi;
    CUxThemeApi _uxThemeApi;

    std::vector<MetroRefPtr<CCaptionButton>> _captionButtons;
    CMetroCaptionTheme _captionTheme;

    MetroRefPtr<CCaptionButton> _pressedButton;
    MetroRefPtr<CCaptionButton> _hoveredButton;
    MetroRefPtr<CCaptionButton> _minButton;
    MetroRefPtr<CCaptionButton> _maxButton;
};

}; //namespace MetroWindow
