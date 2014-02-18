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

#define FRAMESPERBUFFER		2048
#define HALFBUFFER		1024


/*
  filterfunction receives a pointer to a buffer which contains
    an assumed FRAMESPERBUFFER number of frames
  This function modifies the samples in the buffer !!!
*/
void filterfunction(float * buf)
{
  // Quick and dirty Smurf
  for(int c=0; c<HALFBUFFER; c++) buf[c] = buf[2*c];
  for(int c=0; c<HALFBUFFER; c++) buf[HALFBUFFER + c] = buf[c];
}


int main(int argc,char** argv)
{
Audio_IO audiostream;
float samplebuffer[FRAMESPERBUFFER * NROFCHANNELS];
int input_device=-1,output_device=-1;

  audiostream.set_mode(AUDIO_IO_READWRITE);
  audiostream.set_samplerate(SAMPLERATE);
  audiostream.set_nrofchannels(NROFCHANNELS);
  audiostream.set_framesperbuffer(FRAMESPERBUFFER);

  audiostream.initialise();
  audiostream.list_devices();
  cout << "\nGive input device number: ";
  cin >> input_device;
  audiostream.set_input_device(input_device);
  cout << "Give output device number: ";
  cin >> output_device;
  audiostream.set_output_device(output_device);
  audiostream.start_server();

  while(true)
  {
    audiostream.read(samplebuffer);
    filterfunction(samplebuffer);
    audiostream.write(samplebuffer);
  } // while

  audiostream.finalise();

  return 0;
} // main()

