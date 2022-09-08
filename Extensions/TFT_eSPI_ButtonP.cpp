#include "TFT_eSPI_ButtonP.h"

TFT_eSPI_ButtonP::TFT_eSPI_ButtonP(void)
{}

TFT_eSPI_ButtonP::TFT_eSPI_ButtonP(TFT_eSPI *gfx, int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t outline,
                                    uint16_t fill, uint16_t buttonColor, char *label, uint8_t textSize, pressFn fn)
{
  initButton(gfx, x,  y,  w,  h, outline,  fill,  buttonColor, label, textsize, fn);
}

TFT_eSPI_ButtonP::TFT_eSPI_ButtonP(const TFT_eSPI_ButtonP &to_copy)
{
  *this = to_copy;
}

TFT_eSPI_ButtonP &TFT_eSPI_ButtonP::operator=(const TFT_eSPI_ButtonP &assign_to)
{
  if (this == &assign_to)
    return (*this);
  _gfx = assign_to._gfx;
  _x = assign_to._x;
  _y = assign_to._y;
  _w = assign_to._w;
  _h = assign_to._h;
  _xd = assign_to._xd;
  _yd = assign_to._yd;
  _outlineColor = assign_to._outlineColor;
  _bgColor = assign_to._bgColor;
  _fgColor = assign_to._fgColor;
  _pressFn = assign_to._pressFn;
  _buttonState = assign_to._buttonState;
  _lastState = assign_to._lastState;
  _currState = assign_to._currState;
  _textSize = assign_to._textSize;
  strncpy(_label, assign_to._label, 9);
  return (*this);
}

TFT_eSPI_ButtonP::~TFT_eSPI_ButtonP()
{}

void    TFT_eSPI_ButtonP::initButton(TFT_eSPI *gfx, int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t outline,
                                    uint16_t fill, uint16_t buttonColor, char *label, uint8_t textSize, pressFn fn)
{
  initPressable(gfx, x, y, w, h, fn);
  _outlineColor = outline;
  _bgColor = fill;
  _fgColor = buttonColor;
  _textSize = textSize;
  _buttonState = 0;
  _xd = 0;
  _yd = 0;
  strncpy(_label, label, 9);
}

void TFT_eSPI_ButtonP::drawButton(bool inverted, String long_name)
{
  uint16_t fill, outline, text;

  if(!inverted) {
    fill    = _bgColor;
    outline = _outlineColor;
    text    = _fgColor;
  } else {
    fill    = _fgColor;
    outline = _outlineColor;
    text    = _bgColor;
  }

  uint8_t r = min(_w, _h) / 4; // Corner radius
  _gfx->fillRoundRect(_x, _y, _w, _h, r, fill);
  _gfx->drawRoundRect(_x, _y, _w, _h, r, outline);

  if (_gfx->textfont == 255) {
    _gfx->setCursor(_x + (_w / 8),
                    _y + (_h / 4));
    _gfx->setTextColor(text);
    _gfx->setTextSize(_textSize);
    _gfx->print(_label);
  }
  else {
    _gfx->setTextColor(text, fill);
    _gfx->setTextSize(_textSize);

    // uint8_t tempdatum = _gfx->getTextDatum();
    // _gfx->setTextDatum(_textdatum);
    uint16_t tempPadding = _gfx->getTextPadding();
    _gfx->setTextPadding(0);

    if (long_name == "")
      _gfx->drawString(_label, _x + (_w/2) + _xd, _y + (_h/2) - 4 + _yd);
    else
      _gfx->drawString(long_name, _x + (_w/2) + _xd, _y + (_h/2) - 4 + _yd);

    // _gfx->setTextDatum(tempdatum);
    _gfx->setTextPadding(tempPadding);
  }
}

void TFT_eSPI_ButtonP::setLabel(int16_t x_delta, int16_t y_delta)
{
  _x = x_delta;
  _y = y_delta;
}

void    TFT_eSPI_ButtonP::press(bool p)
{
  _lastState = _currState;
  if (this->_pressFn == NULL)
    _currState = false;
  else
    _currState = this->_pressFn();
}
