#include "libs/FadeInFadeOut.h"
#include "ColorConfig.h"
void FadeSeries() {
  FadeInFadeOut fifo; // Memanggil fade in fade out

  // Toska ke magenta
  for(int i = 0; i < 1; i++){
    fifo.go(0, off, magenta, 10, 0);
    fifo.go(0, magenta, toska, 5, 2000);
    fifo.go(0, toska, magenta, 5, 2000);
  }
  fifo.go(0, magenta, off, 5, 0);


  // Ungu ke Orange
  for(int i = 0; i < 1; i++){
    fifo.go(1, off, ungu, 10, 0);
    fifo.go(1, ungu, orange, 5, 2000);
    fifo.go(1, orange, ungu, 5, 2000);
  }
  fifo.go(1, ungu, off, 5, 0);

  // toska ke merah
  for(int i = 0; i < 1; i++){
    fifo.go(2, off, toska, 10, 0);
    fifo.go(2, toska, merah, 5, 2000);
    fifo.go(2, merah, toska, 5, 2000);
  }
  fifo.go(2, toska, off, 5, 0);

  // magenta ke biru
  for(int i = 0; i < 1; i++){
    fifo.go(3, off, magenta, 10, 0);
    fifo.go(3, magenta, biru, 5, 2000);
    fifo.go(3, biru, magenta, 5, 2000);
  }
  fifo.go(3, magenta, off, 5, 0);
  
  // hijau ke magenta
  for(int i = 0; i < 1; i++){
    fifo.go(4, off, hijau, 10, 0);
    fifo.go(4, hijau, magenta, 5, 2000);
    fifo.go(4, magenta, hijau, 5, 2000);
  }
  fifo.go(4, hijau, off, 5, 0);
}