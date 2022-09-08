#ifndef TFT_ESPI_ICON_H
#define TFT_ESPI_ICON_H

#include "TFT_eSPI_Pressable.h"

class TFT_eSPI_Icon: public TFT_eSPI_Pressable
{
  public:
    TFT_eSPI_Icon();
    TFT_eSPI_Icon(TFT_eSPI *gfx, int16_t x, int16_t y, uint16_t w, uint16_t h,const uint8_t *bitmap,
                 const uint8_t *bitmap2, uint16_t outline, uint16_t fill, uint16_t iconcolor, pressFn);
    TFT_eSPI_Icon(const TFT_eSPI_Icon &to_copy);
    TFT_eSPI_Icon &operator=(const TFT_eSPI_Icon &assign_to);
    ~TFT_eSPI_Icon();

    void    initIcon(TFT_eSPI *gfx, int16_t x, int16_t y, uint16_t w, uint16_t h,const uint8_t *bitmap,
                     const uint8_t *bitmap2, uint16_t outline, uint16_t fill, uint16_t iconcolor, pressFn);

    void    drawXBitmap(int iconState) const;

    void     press(bool p);

  private:
    const uint8_t  *_bitmap[2];
    uint16_t       _fgColor;
    uint16_t       _bgColor;
    uint16_t       _outlineColor;
    bool           _iconState;
};

#endif