#ifndef TFT_ESPI_BUTTONP_H
#define TFT_ESPI_BUTTONP_H

#include "TFT_eSPI_Pressable.h"

class TFT_eSPI_ButtonP: public TFT_eSPI_Pressable
{
  public:
    TFT_eSPI_ButtonP();
    TFT_eSPI_ButtonP(TFT_eSPI *gfx, int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t outline,
                      uint16_t fill, uint16_t buttonColor, char *label, uint8_t textsize, pressFn);
    TFT_eSPI_ButtonP(const TFT_eSPI_ButtonP &to_copy);
    TFT_eSPI_ButtonP &operator=(const TFT_eSPI_ButtonP &assign_to);
    ~TFT_eSPI_ButtonP();

    void     initButton(TFT_eSPI *gfx, int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t outline,
                      uint16_t fill, uint16_t buttonColor, char *label, uint8_t textsize, pressFn);
    void     drawButton(bool inverted, String long_name);

    void     press(bool p);
    void     setLabel(int16_t x_delta, int16_t y_delta);
    

  private:
    uint8_t        _textSize;
    int16_t        _xd;
    int16_t        _yd;
    uint16_t       _fgColor;
    uint16_t       _bgColor;
    uint16_t       _outlineColor;
    bool           _buttonState;
    char           _label[10]; // Button text is 9 chars maximum unless long_name used
};

#endif