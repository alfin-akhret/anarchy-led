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

int leds[5] = {0, 1, 2, 3, 4};
void FadeSync() {
  FadeInFadeOut fifo; // Buat object FadeInFadeOut dg nama fifo

  // go()
  // @desc:     Crossfading dari satu led dari warna pertama ke warna kedua 
  // @params:   
  // int targetLed  nomor LED yang akan dimanipulasi  
  // int[] firstColor   warna RGB awal. berbentuk array. contoh: lihat file colorConfig.h 
  // int[] secondColor  warna RGB akhir. berbentuk array. contoh: lihat file colorConfig.h  
  // int l    lapseTime, waktu yang dibutuhkan untuk transisi dari warna awal ke warna akhir. default 10ms/loop
  // int s    Steady time, waktu yang digunakan untuk "steady" atau diam. 
  //          waktu ini berlaku untuk warna awal dan warna akhir. default 4000 ms 

  fifo.crossFadeSync(leds, 5, off, magenta, 10, 0);
  fifo.crossFadeSync(leds, 5, magenta, toska, 10, 0);
  fifo.crossFadeSync(leds, 5, toska, off, 10, 0);

}