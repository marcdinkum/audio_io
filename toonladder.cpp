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
*  File name     : toonladder.cpp
*  System name   : audio_io / Portaudio
* 
*  Description   : chromatic octave on the piano scale
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
#define NUM_SECONDS		0.5

#define FRAMESPERBUFFER		1024


int main(int argc,char** argv)
{
Audio_IO audiostream;
float samplebuffer[FRAMESPERBUFFER * NROFCHANNELS];
unsigned long x=0;		// sample index
unsigned long bufptr=0;		// pointer into sample buffer
double l_freq=440.0;		// base frequency of left channel
double r_freq=440.0;		// base frequency of right channel
double l_amp=0.4;		// base amplitude of left channel
double r_amp=0.4;		// base amplitude of right channel

  audiostream.set_samplerate(SAMPLERATE);
  audiostream.set_nrofchannels(NROFCHANNELS);
  audiostream.set_framesperbuffer(FRAMESPERBUFFER);

  audiostream.initialise();
  for(int note=0;note<=12;note++)
  {
    cout << "note: " << note << " l freq: " << l_freq << endl;
    do{
      for(bufptr=0; bufptr < FRAMESPERBUFFER*NROFCHANNELS; bufptr+=2)
      {
        // Fill a new buffer with samples
        samplebuffer[bufptr] =
          (float)(l_amp * sin( (double)x * l_freq/SAMPLERATE * M_PI * 2.));
        samplebuffer[bufptr + 1] =
          (float)(r_amp * sin( (double)x * r_freq/SAMPLERATE * M_PI * 2.));
        x++;
      } // for
      // send buffer to Portaudio
      audiostream.write(samplebuffer);
    } while(x < (SAMPLERATE * NUM_SECONDS) );

    l_freq *= pow(2,(1/12.0));
    r_freq *= pow(2,(1/12.0));
    x=0;

  } // for

  audiostream.finalise();

  return 0;
} // main()

