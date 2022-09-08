#ifndef TFT_ESPI_PRESSABLE_H
#define TFT_ESPI_PRESSABLE_H

typedef int (*pressFn)();

class TFT_eSPI_Pressable: protected TFT_eSPI
{
  public:
    TFT_eSPI_Pressable();
    TFT_eSPI_Pressable(TFT_eSPI *gfx, int16_t x, int16_t y, uint16_t w, uint16_t h, pressFn);
    TFT_eSPI_Pressable(const TFT_eSPI_Pressable &to_copy);
    TFT_eSPI_Pressable &operator=(const TFT_eSPI_Pressable &assign_to);
    ~TFT_eSPI_Pressable();

    void    initPressable(TFT_eSPI *gfx, int16_t x, int16_t y, uint16_t w, uint16_t h, pressFn);

    bool    contains(int16_t x, int16_t y) const;

    virtual void     press(bool p);
    virtual bool     isPressed() const;
    virtual bool     justPressed() const;
    virtual bool     justReleased() const;

  protected:
    pressFn       _pressFn;

    TFT_eSPI       *_gfx;
    int16_t        _x;
    int16_t        _y;
    uint16_t       _w;
    uint16_t       _h;
    bool           _lastState;
    bool           _currState;
};

#endif