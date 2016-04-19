/**
  @author: <alfin akhret> alfin.akhret@gmail.com and <alvan hafiz> smilepiss86@gmail.com
  Scenario LED menggunakan library FadeInFadeOut.h
  Untuk konfigurasi warna lihat file /scenario/ColorConfig.h

  cara penggunaan pada main.ino
  
  #include <ShiftPWM.h>
  #include "scenario/FadeSeries.h"
  
  void loop() {
    FadeSeries();
  }
**/

// sertakan file library yang dibutuhkan 


void FadeSeries() {
  FadeInFadeOut fifo; // Buat object FadeInFadeOut dg nama fifo

  // Toska ke magenta
  fifo.crossFade(0, off, magenta, 10, 0);        // transisi dari keaddan off ke magenta dalam 10 ms/loop
  fifo.crossFade(0, magenta, toska, 5, 2000);    // transisi dari magenta ke toska dlm 5ms/loop, tahan di toska selama 2000ms
  fifo.crossFade(0, toska, magenta, 5, 2000);    // transisi dari toska ke magenta dalam 5ms/loop, tahan di magenta selama 2000ms
  fifo.crossFade(0, magenta, off, 5, 0);         // transisi dari magenta ke off dlm 10ms/loop, tahan di off selama 0ms

  // Ungu ke Orange
  fifo.crossFade(1, off, ungu, 10, 0);
  fifo.crossFade(1, ungu, orange, 5, 2000);
  fifo.crossFade(1, orange, ungu, 5, 2000);
  fifo.crossFade(1, ungu, off, 5, 0);

  // toska ke merah
  fifo.crossFade(2, off, toska, 10, 0);
  fifo.crossFade(2, toska, merah, 5, 2000);
  fifo.crossFade(2, merah, toska, 5, 2000);
  fifo.crossFade(2, toska, off, 5, 0);

  // magenta ke biru
  fifo.crossFade(3, off, magenta, 10, 0);
  fifo.crossFade(3, magenta, biru, 5, 2000);
  fifo.crossFade(3, biru, magenta, 5, 2000);
  fifo.crossFade(3, magenta, off, 5, 0);
  
  // hijau ke magenta
  fifo.crossFade(4, off, hijau, 10, 0);
  fifo.crossFade(4, hijau, magenta, 5, 2000);
  fifo.crossFade(4, magenta, hijau, 5, 2000);
  fifo.crossFade(4, hijau, off, 5, 0);

  /** more example **/
  /* transisi dari toska ke magenta selama 5 kali 
    for (int i = 0; i < 5; i++) {
      fifo.crossFade(0, toska, magenta, 10, 2000);
    }
  */
}