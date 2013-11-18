#include "stdafx.h"
#include "CaptionButton.h"
#include "MiscWapppers.h"

namespace MetroWindow
{

CCaptionButton::CCaptionButton(LONG hitTest, CMetroCaptionTheme& theme)
	: _theme(theme), _hitTest(hitTest), _image(NULL)
{
    _pressed = false;
    _hovered = false;
    _enabled = true;
    _visible = true;
}


CCaptionButton::~CCaptionButton(void)
{
}

void CCaptionButton::Draw(HDC hdc)
{
    if (!Visible()) return;

    HBITMAP image = _image;
    CRect srcRect(0, 0, 14, 14);

    COLORREF backColor;

    if (_pressed)
    {
        FillSolidRect(hdc, &_bounds, _theme.ButtonPressColor());
        srcRect.OffsetRect(28, 0);
    }
    else if (_hovered)
    {
        FillSolidRect(hdc, &_bounds, _theme.ButtonHoverColor());
        srcRect.OffsetRect(14, 0);
    }

    if (image != NULL)
    {
        CRect destRect;
        destRect.top = _bounds.top + (Height() - srcRect.Height()) / 2;
        destRect.left = _bounds.left + (Width() - srcRect.Width()) / 2 + 1;
        destRect.Width(srcRect.Width());
        destRect.Height(srcRect.Height());

        HDC hdcBmpMem = ::CreateCompatibleDC(hdc);
        HBITMAP hbmOldBmp = (HBITMAP)::SelectObject(hdcBmpMem, image);

        BLENDFUNCTION bf = { AC_SRC_OVER, 0, 0xFF, AC_SRC_ALPHA };
        ::GdiAlphaBlend(hdc, destRect.left, destRect.top, destRect.Width(), destRect.Height(), 
            hdcBmpMem, srcRect.left, srcRect.top, srcRect.Width(), srcRect.Height(), bf);

        ::SelectObject(hdcBmpMem, hbmOldBmp);
	    ::DeleteDC(hdcBmpMem);
    }
}

void CCaptionButton::FillSolidRect(HDC hdc, LPCRECT lpRect, COLORREF clr)
{
    COLORREF clrOld = ::SetBkColor(hdc, clr);
    ::ExtTextOut(hdc, 0, 0, ETO_OPAQUE, lpRect, NULL, 0, NULL);
    ::SetBkColor(hdc, clrOld);

    //HBRUSH hBrush = ::CreateSolidBrush(clr);
    //::FillRect(hdc, lpRect, hBrush);
    //::DeleteObject(hBrush);
}

} //namespace MetroWindow
