#include "TFT_eSPI_Icon.h"
#include <stdlib.h>

TFT_eSPI_Icon::TFT_eSPI_Icon(void)
{}

TFT_eSPI_Icon::TFT_eSPI_Icon(TFT_eSPI *gfx, int16_t x, int16_t y, uint16_t w, uint16_t h, const uint8_t *bitmap,
                        const uint8_t *bitmap2, uint16_t outline, uint16_t fill, uint16_t iconcolor, pressFn fn)
{
  initIcon(gfx, x,  y,  w,  h, bitmap, bitmap2,  outline,  fill,  iconcolor, fn);
}

TFT_eSPI_Icon::TFT_eSPI_Icon(const TFT_eSPI_Icon &to_copy)
{
  *this = to_copy;
}

TFT_eSPI_Icon &TFT_eSPI_Icon::operator=(const TFT_eSPI_Icon &assign_to)
{
  if (this == &assign_to)
    return (*this);
  _gfx = assign_to._gfx;
  _x = assign_to._x;
  _y = assign_to._y;
  _w = assign_to._w;
  _h = assign_to._h;
  _bitmap[0] = assign_to._bitmap[0];
  _bitmap[1] = assign_to._bitmap[1];
  _outlineColor = assign_to._outlineColor;
  _bgColor = assign_to._bgColor;
  _fgColor = assign_to._fgColor;
  _pressFn = assign_to._pressFn;
  _iconState = assign_to._iconState;
  _lastState = assign_to._lastState;
  _currState = assign_to._currState;
  return (*this);
}


TFT_eSPI_Icon::~TFT_eSPI_Icon()
{}

void    TFT_eSPI_Icon::initIcon(TFT_eSPI *gfx, int16_t x, int16_t y, uint16_t w, uint16_t h, const uint8_t *bitmap,
                                const uint8_t *bitmap2, uint16_t outline, uint16_t fill, uint16_t iconcolor, pressFn fn)
{
  initPressable(gfx, x, y, w, h, fn);
  _bitmap[0] = bitmap;
  _bitmap[1] = bitmap2;
  _outlineColor = outline;
  _bgColor = fill;
  _fgColor = iconcolor;
  _iconState = 0;
}

void    TFT_eSPI_Icon::drawXBitmap(int iconState, bool ignoreBackground) const
{
  if (_bitmap[iconState] == NULL)
    return ;
  if (ignoreBackground == true)
    _gfx->drawXBitmap(_x, _y, _bitmap[iconState], _w, _h, _fgColor);
  if (ignoreBackground == false)
    _gfx->drawXBitmap(_x, _y, _bitmap[iconState], _w, _h, _fgColor, _bgColor);
}

void    TFT_eSPI_Icon::changeColor(uint16_t iconColor, uint16_t backgroundColor)
{
  _fgColor = iconColor;
  _bgColor = backgroundColor;
}

void    TFT_eSPI_Icon::press(bool p)
{
  _lastState = _currState;
  if (this->_pressFn == NULL)
    _currState = false;
  else
    _currState = this->_pressFn();
  if (_lastState != _currState)
    this->drawXBitmap(_currState, false);
}
