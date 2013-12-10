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
*  File name     : delay.cpp
*  System name   : audio_io / Portaudio
* 
*  Description   : input-output delay
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
#define NUM_SECONDS		15

#define FRAMESPERBUFFER		1024


int main(int argc,char** argv)
{
Audio_IO audiostream;
float samplebuffer[SAMPLERATE * NROFCHANNELS * NUM_SECONDS];
long buffersize=SAMPLERATE * NROFCHANNELS * NUM_SECONDS;
long bufptr;
int input_device=0,output_device=0;

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


  for(bufptr=0; bufptr < buffersize-FRAMESPERBUFFER*NROFCHANNELS;
      bufptr+=FRAMESPERBUFFER*NROFCHANNELS)
  {
    audiostream.read(samplebuffer+bufptr);
  }

  for(bufptr=0; bufptr < buffersize-FRAMESPERBUFFER*NROFCHANNELS;
    bufptr+=FRAMESPERBUFFER*NROFCHANNELS)
  {
    audiostream.write(samplebuffer+bufptr);
  }

  audiostream.finalise();

  return 0;
} // main()

