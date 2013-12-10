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
*  File name     : filter.cpp
*  System name   : audio_io / Portaudio
* 
*  Description   : filter
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
#define NROFCHANNELS		1

#define FRAMESPERBUFFER		1024


/*
  filterfunction receives a pointer to a buffer which contains
    an assumed FRAMESPERBUFFER number of frames
  This function modifies the samples in the buffer !!!
*/
void filterfunction(float * buf)
{
  for(int c=0; c<FRAMESPERBUFFER*NROFCHANNELS; c++)
  {
    buf[c] *= 0.5;
  } // for
}


int main(int argc,char** argv)
{
Audio_IO audiostream;
float samplebuffer[FRAMESPERBUFFER * NROFCHANNELS];

  audiostream.set_mode(AUDIO_IO_READWRITE);
  audiostream.set_samplerate(SAMPLERATE);
  audiostream.set_nrofchannels(NROFCHANNELS);
  audiostream.set_framesperbuffer(FRAMESPERBUFFER);

  audiostream.initialise();

  while(true)
  {
    audiostream.read(samplebuffer);
    filterfunction(samplebuffer);
    audiostream.write(samplebuffer);
  } // while

  audiostream.finalise();

  return 0;
} // main()

