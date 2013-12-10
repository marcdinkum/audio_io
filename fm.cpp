/**********************************************************************
*          Copyright (c) 2013, Hogeschool voor de Kunsten Utrecht
*                      Hilversum, the Netherlands
*                          All rights reserved
***********************************************************************
*  This program is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program.
*  If not, see <http://www.gnu.org/licenses/>.
***********************************************************************
*
*  File name     : fm.cpp
*  System name   : audio_io / Portaudio
* 
*  Description   : frequency modulation
*		   Example for the audio_io C++ class for Portaudio
*
*  Author        : Marc Groenewegen
*  E-mail        : marcg@dinkum.nl
*
**********************************************************************/
#include <iostream>
#include "audio_io.h"

using namespace std;

#define SAMPLERATE		44100
#define NROFCHANNELS		2
#define NUM_SECONDS		3

#define FRAMESPERBUFFER		1024


int main(int argc,char** argv)
{
  Audio_IO audiostream;
  float samplebuffer[FRAMESPERBUFFER * NROFCHANNELS];
  unsigned long bufptr=0;		// pointer into sample buffer
  unsigned long x=0;		// sample index
  double xx;			// 2 PI / Fs version of x

  double l_freq=1500.0;		// base frequency of left channel
  double l_amp=0.4;		// base amplitude [0:1] of left channel
  double l_mod_freq=20;		// modulation freq for left channel
  double l_mod_depth=20*M_PI;

  double r_freq=850.0;		// base frequency of right channel
  double r_amp=0.4;		// base amplitude [0:1] of right channel
  double r_mod_freq=5;
  double r_mod_depth=10*M_PI;

  audiostream.set_samplerate(SAMPLERATE);
  audiostream.set_nrofchannels(NROFCHANNELS);
  audiostream.set_framesperbuffer(FRAMESPERBUFFER);

  audiostream.initialise();

  do{
    for(bufptr=0; bufptr < FRAMESPERBUFFER*NROFCHANNELS; bufptr+=2)
    {

      /*
       * sine shaped frequency (phase) modulation
       */
      xx = x * 2.0*M_PI / SAMPLERATE;

      // Fill a new buffer with samples
      samplebuffer[bufptr] =
        (float)(l_amp * sin(xx*l_freq + l_mod_depth*sin(xx * l_mod_freq)));
      samplebuffer[bufptr + 1]  =
        (float)(r_amp * sin(xx*r_freq + r_mod_depth*sin(xx * r_mod_freq)));

      x++;
      l_mod_freq *= 0.99999; // just for fun
    } // for

    // send buffer to Portaudio
    audiostream.write(samplebuffer);
  } while(x < (SAMPLERATE * NUM_SECONDS) );

  audiostream.finalise();

  return 0;
} // main()

