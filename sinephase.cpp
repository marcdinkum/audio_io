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
*  File name     : sinephase.cpp
*  System name   : audio_io / Portaudio
* 
*  Description   : sinephase
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
unsigned long x=0;		// sample index
unsigned long bufptr=0;		// pointer into sample buffer
double l_freq=500.0;		// base frequency of left channel
double r_freq=850.0;		// base frequency of right channel
double l_amp=0.4;		// base amplitude of left channel
double r_amp=0.4;		// base amplitude of right channel
int output_device=0;

  audiostream.set_samplerate(SAMPLERATE);
  audiostream.set_nrofchannels(NROFCHANNELS);
  audiostream.set_framesperbuffer(FRAMESPERBUFFER);

  audiostream.initialise();
  audiostream.list_devices();
  cout << "Give output device number: ";
  cin >> output_device;
  audiostream.set_output_device(output_device);
  audiostream.start_server();

  double l_phase = 0;
  double r_phase = 0;

  do{
    for(bufptr=0; bufptr < FRAMESPERBUFFER*NROFCHANNELS; bufptr+=2)
    {
      // Fill a new buffer with samples
      samplebuffer[bufptr] = (float)(l_amp * sin(2.0*M_PI*l_phase) );
      l_phase += l_freq/SAMPLERATE;

      samplebuffer[bufptr+1] = (float)(r_amp * sin(2.0*M_PI*r_phase) );
      r_phase += r_freq/SAMPLERATE;
      x++;
    } // for

    // send buffer to Portaudio
    audiostream.write(samplebuffer);
  } while(x < (SAMPLERATE * NUM_SECONDS) );

  audiostream.finalise();

  return 0;
} // main()

