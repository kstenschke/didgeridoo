/*
  Copyright (c) Kay Stenschke
  All rights reserved.
  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright notice,
     this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   * Neither the name of  nor the names of its contributors may be used to
     endorse or promote products derived from this software without specific
     prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef DIDGERIDOO_STRUCT_PITCH_H_
#define DIDGERIDOO_STRUCT_PITCH_H_

struct Pitch {  // @see http://people.virginia.edu/~pdr4h/pitch-freq.html
  constexpr static const double C_4 = 261.626;
  constexpr static const double CS4 = 277.183;
  constexpr static const double D_4 = 293.665;
  constexpr static const double DS4 = 311.12;
  constexpr static const double E_4 = 329.628;
  constexpr static const double F_4 = 349.228;
  constexpr static const double FS4 = 369.994;
  constexpr static const double G_4 = 391.995;
  constexpr static const double GS4 = 415.305;
  constexpr static const double A_4 = 440.000;
  constexpr static const double AS4 = 466.164;
  constexpr static const double B_4 = 493.883;

  constexpr static const double C_5 = 523.251;
  constexpr static const double CS5 = 554.365;
  constexpr static const double D_5 = 587.330;
  constexpr static const double DS5 = 622.254;
  constexpr static const double E_5 = 659.255;
  constexpr static const double F_5 = 698.457;
  constexpr static const double FS5 = 739.989;
  constexpr static const double G_5 = 783.991;
  constexpr static const double GS5 = 830.609;
  constexpr static const double A_5 = 880.000;
  constexpr static const double AS5 = 932.328;
  constexpr static const double B_5 = 987.767;

  constexpr static const double C_6 = 1046.502;
  constexpr static const double CS6 = 1108.731;
  constexpr static const double D_6 = 1174.659;
  constexpr static const double DS6 = 1244.508;
  constexpr static const double E_6 = 1318.510;
  constexpr static const double F_6 = 1396.913;
  constexpr static const double FS6 = 1479.978;
  constexpr static const double G_6 = 1567.982;
  constexpr static const double GS6 = 1661.219;
  constexpr static const double A_6 = 1760.000;
  constexpr static const double AS6 = 1864.655;
  constexpr static const double B_6 = 1975.533;

  constexpr static const double C_7 = 2093.005;
  constexpr static const double CS7 = 2217.461;
  constexpr static const double D_7 = 2349.318;
  constexpr static const double DS7 = 2489.016;
  constexpr static const double E_7 = 2637.021;
  constexpr static const double F_7 = 2793.826;
  constexpr static const double FS7 = 2959.956;
  constexpr static const double G_7 = 3135.964;
  constexpr static const double GS7 = 3322.438;
  constexpr static const double A_7 = 3520.000;
  constexpr static const double AS7 = 3729.310;
  constexpr static const double B_7 = 3951.066;

  constexpr static const double C_8 = 4186.009;
  constexpr static const double CS8 = 4434.922;
  constexpr static const double D_8 = 4698.637;
  constexpr static const double DS8 = 4978.032;
  constexpr static const double E_8 = 5274.042;
  constexpr static const double F_8 = 5587.652;
  constexpr static const double FS8 = 5919.912;
  constexpr static const double G_8 = 6271.928;
  constexpr static const double GS8 = 6644.876;
  constexpr static const double A_8 = 7040.000;
  constexpr static const double AS8 = 7458.620;
  constexpr static const double B_8 = 7902.133;

  constexpr static const double C_9 =  8372.019;
  constexpr static const double CS9 =  8869.845;
  constexpr static const double D_9 =  9397.273;
  constexpr static const double DS9 =  9956.064;
  constexpr static const double E_9 = 10548.083;
  constexpr static const double F_9 = 11175.305;
  constexpr static const double FS9 = 11839.823;
  constexpr static const double G_9 = 12543.855;
  constexpr static const double GS9 = 13289.752;
};

#endif //DIDGERIDOO_STRUCT_PITCH_H_
