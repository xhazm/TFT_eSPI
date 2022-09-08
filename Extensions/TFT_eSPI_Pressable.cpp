#include "TFT_eSPI_Pressable.h"

TFT_eSPI_Pressable::TFT_eSPI_Pressable(void)
{}

TFT_eSPI_Pressable::TFT_eSPI_Pressable(TFT_eSPI *gfx, int16_t x, int16_t y, uint16_t w, uint16_t h, pressFn fn)
{
  initPressable(gfx, x,  y,  w,  h, fn);
}

TFT_eSPI_Pressable::TFT_eSPI_Pressable(const TFT_eSPI_Pressable &to_copy)
{
  *this = to_copy;
}

TFT_eSPI_Pressable& TFT_eSPI_Pressable::operator=(const TFT_eSPI_Pressable &assign_to)
{
  if (this == &assign_to)
    return (*this);
  _x = assign_to._x;
  _y = assign_to._y;
  _w = assign_to._w;
  _h = assign_to._h;
  _pressFn = assign_to._pressFn;
  _lastState = assign_to._lastState;
  _currState = assign_to._currState;
  return (*this);
}


TFT_eSPI_Pressable::~TFT_eSPI_Pressable()
{}

void    TFT_eSPI_Pressable::initPressable(TFT_eSPI *gfx, int16_t x, int16_t y, uint16_t w, uint16_t h, pressFn fn)
{
  _gfx = gfx;
  _x = x;
  _y = y;
  _w = w;
  _h = h;
  _pressFn = fn;
  _lastState = 0;
  _currState = 0;
}

bool    TFT_eSPI_Pressable::contains(int16_t x, int16_t y) const
{
  return ((x >= _x) && (x < (_x + _w)) &&
          (y >= _y) && (y < (_y + _h)));
}

void    TFT_eSPI_Pressable::press(bool p)
{
  _lastState = _currState;
  _currState = this->_pressFn();
}

bool TFT_eSPI_Pressable::isPressed() const   { return (_currState); }
bool TFT_eSPI_Pressable::justPressed() const { return (_currState && !_lastState); }
bool TFT_eSPI_Pressable::justReleased() const { return (!_currState && _lastState); }