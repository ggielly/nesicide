/*
** FamiTracker - NES/Famicom sound tracker
** Copyright (C) 2005-2014  Jonathan Liss
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful, 
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
** Library General Public License for more details.  To obtain a 
** copy of the GNU Library General Public License, write to the Free 
** Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
**
** Any permitted reproduction of these routines, in whole or in part,
** must bear this legend.
*/

#include "stdafx.h"
#include "FamiTracker.h"
#include "FamiTrackerDoc.h"
#include "FamiTrackerView.h"
#include "MIDI.h"
#include "Settings.h"

/*
 * CMIDI - Wrapper class for input and output MIDI devices
 *
 */

#define ASSEMBLE_STATUS(Message, Channel) (((Message) << 4) | (Channel))
#define ASSEMBLE_PARAM(Status, Byte1, Byte2) ((Status) | ((Byte1) << 8) | ((Byte2) << 16))

// Static stuff
CMIDI *CMIDI::m_pInstance = NULL;

///////////////////////////////////////////////////////// 
//
// Implementation of midiCallback function
///
void CMIDI::midiCallback(double timeStamp, std::vector<unsigned char> *message, void *userData) {
  // Validate CMIDI instance and MIDI message
  if (!validateMidiData(userData, message)) {
    return;
  }

  // Process MIDI message based on type
  CMIDI* instance = static_cast<CMIDI*>(userData);
  instance->handleMidiMessage(*message);
}

bool CMIDI::validateMidiData(void* userData, std::vector<unsigned char>* message) {
  if (userData == nullptr) {
    std::cerr << "Error: Invalid CMIDI instance!" << std::endl;
    return false;
  }

  if (message == nullptr || message->empty()) {
    std::cerr << "Error: Invalid MIDI message!" << std::endl;
    return false;
  }

  return true;
}

void CMIDI::handleMidiMessage(const std::vector<unsigned char>& message) {
  // Extract message data
  unsigned char status = message[0];

  // Process message based on status byte
  if (status == 0x90 && message.size() >= 3) {
    // Process Note-On messages
    unsigned char note = message[1];
    unsigned char velocity = message[2];
    // Perform actions based on note and velocity data
  } else if (status == 0x80 && message.size() >= 3) {
    // Process Note-Off messages
    // Perform actions based on note and velocity data
  }
  // Add more cases as needed for other MIDI message types
}
///////////////////////////////////////// 
///
///


void CMIDI::RtMidiInProc(double timeStamp, std::vector<unsigned char> *message, void *userData)
{
    // MIDI input callback function

    // Uncommented section for processing MIDI input messages based on Windows messages
    /*
    if (wMsg == MIM_DATA) {
        unsigned char Status = (char)(dwParam1 & 0xFF);
        unsigned char Data1   = (char)(dwParam1 >> 8) & 0xFF;
        unsigned char Data2   = (char)(dwParam1 >> 16) & 0xFF;
        m_pInstance->Event(Status, Data1, Data2);
    }
    */

    // Check if the MIDI message is a note-on message (status byte 0x90)
    if (message->size() >= 3 && (*message)[0] == 0x90) {
        unsigned char note = (*message)[1];       // Note number
        unsigned char velocity = (*message)[2];   // Velocity
        // Process the note-on message
    }
}


// Instance stuff

CMIDI::CMIDI() : 
	m_bInStarted(false), 
	m_iInDevice(0),
	m_iOutDevice(0),
	m_iQueueHead(0), 
	m_iQueueTail(0),
	m_hMIDIIn(NULL),
	m_hMIDIOut(NULL),
	m_iTimingCounter(0)
{
	// Allow only one single midi object
	ASSERT( m_pInstance == NULL );
	m_pInstance = this;

   // RtMidiIn constructor
   try {
     midiin = new RtMidiIn();
   }
   catch (RtMidiError &error) {
     // Handle the exception here
     error.printMessage();
   }

   // RtMidiOut constructor
   try {
     midiout = new RtMidiOut();
   }
   catch (RtMidiError &error) {
     // Handle the exception here
     error.printMessage();
   }
}

CMIDI::~CMIDI()
{
	CloseDevices();

   delete midiin;
}

// CMIDI member functions

bool CMIDI::Init(void)
{
	// Load from settings
	m_iInDevice = theApp.GetSettings()->Midi.iMidiDevice;
	m_iOutDevice = theApp.GetSettings()->Midi.iMidiOutDevice;

	m_bMasterSync = theApp.GetSettings()->Midi.bMidiMasterSync;

	// Open devices
	OpenDevices();

	return true;
}

void CMIDI::Shutdown(void)
{
	// Store settings
	theApp.GetSettings()->Midi.iMidiDevice = m_iInDevice;
	theApp.GetSettings()->Midi.iMidiOutDevice = m_iOutDevice;

	CloseDevices();
}


/*
bool CMIDI::OpenDevices(void)
{
   MMRESULT Result;

   if (m_iInDevice == 0 && m_iOutDevice == 0)
	  return true;

   // Input
   if (m_iInDevice != 0) {

//		Result = midiInOpen(&m_hMIDIIn, m_iInDevice - 1, (DWORD_PTR)MidiInProc, 0, CALLBACK_FUNCTION);
	  midiin->openPort( m_iInDevice );

//		if (Result != MMSYSERR_NOERROR) {
//			m_hMIDIIn = NULL;
//			AfxMessageBox(IDS_MIDI_ERR_INPUT);
//			return false;
//		}

	  // Auto-enable input device
//		midiInStart(m_hMIDIIn);
	  // Set our callback function.  This should be done immediately after
	  // opening the port to avoid having incoming messages written to the
	  // queue.
	  midiin->setCallback( &RtMidiInProc );
	  // Don't ignore sysex, timing, or active sensing messages.
	  midiin->ignoreTypes( false, false, false );
	  m_bInStarted = true;
   }

   // Output
   if (m_iOutDevice != 0) {

//		Result = midiOutOpen(&m_hMIDIOut, m_iOutDevice - 1, NULL, 0, CALLBACK_NULL);
	  midiout->openPort( m_iOutDevice );

//		if (Result != MMSYSERR_NOERROR) {
//			m_hMIDIOut = NULL;
//			AfxMessageBox(IDS_MIDI_ERR_OUTPUT);
//			return false;
//		}

	  // Set patches
	  unsigned int dwParam1;
//		midiOutShortMsg(m_hMIDIOut, (MIDI_MSG_PROGRAM_CHANGE << 4 | 0x00) | (1 << 8));
	  std::vector<unsigned char> data;
	  data.push_back((MIDI_MSG_PROGRAM_CHANGE << 4 | 0x00));
	  data.push_back((1<<8));
	  midiout->sendMessage(&data);
//		midiOutShortMsg(m_hMIDIOut, (MIDI_MSG_PROGRAM_CHANGE << 4 | 0x01) | (1 << 8));
	  data.push_back((MIDI_MSG_PROGRAM_CHANGE << 4 | 0x01));
	  data.push_back(1);
	  midiout->sendMessage(&data);
//		midiOutShortMsg(m_hMIDIOut, (MIDI_MSG_PROGRAM_CHANGE << 4 | 0x02) | (74 << 8));
	  data.push_back((MIDI_MSG_PROGRAM_CHANGE << 4 | 0x02));
	  data.push_back(74);
	  midiout->sendMessage(&data);
//		midiOutShortMsg(m_hMIDIOut, (MIDI_MSG_PROGRAM_CHANGE << 4 | 0x03) | (115 << 8));
	  data.push_back((MIDI_MSG_PROGRAM_CHANGE << 4 | 0x03));
	  data.push_back(115);
	  midiout->sendMessage(&data);
//		midiOutShortMsg(m_hMIDIOut, (MIDI_MSG_PROGRAM_CHANGE << 4 | 0x04) | (118 << 8));
	  data.push_back((MIDI_MSG_PROGRAM_CHANGE << 4 | 0x04));
	  data.push_back(118);
	  midiout->sendMessage(&data);

//		midiOutReset(m_hMIDIOut);
   }

   m_csQueue.Lock();
   m_iQueueHead = m_iQueueTail = 0;
   m_csQueue.Unlock();

	return true;
}
*/


bool CMIDI::OpenDevices(void)
{
   MMRESULT Result;

   if (m_iInDevice == 0 && m_iOutDevice == 0)
      return true;

   // Input
   if (m_iInDevice != 0) {
      // Open the MIDI input port
      midiin->openPort(m_iInDevice - 1); // Adjust for zero-based index
      // Set the callback function to RtMidiInProc
	  
      //midiin->setCallback(&CMIDI::RtMidiInProc, this); // Pass the current instance as userData
          // Appel de la fonction de rappel MIDI comme fonction statique de la classe CMIDI
    midiin->setCallback(&CMIDI::midiCallback, this); // Passer l'instance actuelle en tant que userData

	  // Don't ignore any MIDI message types
      midiin->ignoreTypes(false, false, false);
      m_bInStarted = true;
   }

   // Output
   if (m_iOutDevice != 0) {
      // Open the MIDI output port
      midiout->openPort(m_iOutDevice - 1); // Adjust for zero-based index

      // Set patches
      std::vector<unsigned char> data;
      data.push_back((MIDI_MSG_PROGRAM_CHANGE << 4 | 0x00));
      data.push_back(1);
      midiout->sendMessage(&data);

      data.clear(); // Clear the vector for the next message
      data.push_back((MIDI_MSG_PROGRAM_CHANGE << 4 | 0x01));
      data.push_back(1);
      midiout->sendMessage(&data);

      data.clear(); // Clear the vector for the next message
      data.push_back((MIDI_MSG_PROGRAM_CHANGE << 4 | 0x02));
      data.push_back(74);
      midiout->sendMessage(&data);

      data.clear(); // Clear the vector for the next message
      data.push_back((MIDI_MSG_PROGRAM_CHANGE << 4 | 0x03));
      data.push_back(115);
      midiout->sendMessage(&data);

      data.clear(); // Clear the vector for the next message
      data.push_back((MIDI_MSG_PROGRAM_CHANGE << 4 | 0x04));
      data.push_back(118);
      midiout->sendMessage(&data);
   }

   // Reset the MIDI queue
   m_csQueue.Lock();
   m_iQueueHead = m_iQueueTail = 0;
   m_csQueue.Unlock();

   return true;
}



bool CMIDI::CloseDevices(void)
{
   if (m_bInStarted) {
//		midiInStop(m_hMIDIIn);
      midiin->cancelCallback();
      m_bInStarted = false;
   }

   if (m_hMIDIIn != NULL) {
//		midiInClose(m_hMIDIIn);
      midiin->closePort();
      m_hMIDIIn = NULL;
   }

   if (m_hMIDIOut != NULL) {
//		midiOutClose(m_hMIDIOut);
      midiout->closePort();
      m_hMIDIOut = NULL;
   }

	return false;
}

int CMIDI::GetNumInputDevices() const
{
   return midiin->getPortCount();
}

int CMIDI::GetNumOutputDevices() const
{
   return midiout->getPortCount();
}

void CMIDI::GetInputDeviceString(int Num, CString &Text) const
{
//	MIDIINCAPS InCaps;
//	midiInGetDevCaps(Num, &InCaps, sizeof(MIDIINCAPS));
//	Text = InCaps.szPname;
   std::string portName;
   try {
     portName = midiin->getPortName(Num);
   }
   catch ( RtMidiError &error ) {
     error.printMessage();
     return;
   }
   Text = portName.c_str();
}

void CMIDI::GetOutputDeviceString(int Num, CString &Text) const
{
//	MIDIOUTCAPS OutCaps;
//	midiOutGetDevCaps(Num, &OutCaps, sizeof(MIDIOUTCAPS));
//	Text = OutCaps.szPname;
   std::string portName;
   try {
     portName = midiout->getPortName(Num);
   }
   catch ( RtMidiError &error ) {
     error.printMessage();
     return;
   }
   Text = portName.c_str();
}

void CMIDI::SetInputDevice(int Device, bool MasterSync)
{
	m_iInDevice = Device;
	m_bMasterSync = MasterSync;

	CloseDevices();
	OpenDevices();
}

void CMIDI::SetOutputDevice(int Device)
{
	m_iOutDevice = Device;

	CloseDevices();
	OpenDevices();
}

void CMIDI::Enqueue(unsigned char MsgType, unsigned char MsgChannel, unsigned char Data1, unsigned char Data2)
{
	m_csQueue.Lock();
	
	m_iMsgTypeQueue[m_iQueueHead] = MsgType;
	m_iMsgChanQueue[m_iQueueHead] = MsgChannel;
	m_iData1Queue[m_iQueueHead]   = Data1;
	m_iData2Queue[m_iQueueHead]   = Data2;
	m_iQuantization[m_iQueueHead] = m_iTimingCounter;

	m_iQueueHead = (m_iQueueHead + 1) % MAX_QUEUE;

	m_csQueue.Unlock();
}

void CMIDI::Event(unsigned char Status, unsigned char Data1, unsigned char Data2)
{
	const unsigned char MsgType	   = Status >> 4;
	const unsigned char MsgChannel = Status & 0x0F;

	CFrameWnd *pFrame = static_cast<CFrameWnd*>(AfxGetApp()->m_pMainWnd);
	CView *pView = pFrame->GetActiveView();

//	TRACE("%i: MIDI message %02X %02X %02X\n", GetTickCount(), Status, Data1, Data2);

	// Timing
	switch (Status) {
	case 0xF8:	// Timing tick
		if (m_bMasterSync) {
			if (++m_iTimingCounter == 6) {
				m_iTimingCounter = 0;
				Enqueue(MsgType, MsgChannel, Data1, Data2);
				pView->PostMessage(WM_USER_MIDI_EVENT);
			}
		}
		break;
	case 0xFA:	// Start
		m_iTimingCounter = 0;
		break;
	case 0xFC:	// Stop
		m_iTimingCounter = 0;
		break;
	default:
		switch (MsgType) {
			case MIDI_MSG_NOTE_OFF:
			case MIDI_MSG_NOTE_ON: 
			case MIDI_MSG_PITCH_WHEEL:
				Enqueue(MsgType, MsgChannel, Data1, Data2);
				pView->PostMessage(WM_USER_MIDI_EVENT);
				break;
		}
	}
}

bool CMIDI::ReadMessage(unsigned char & Message, unsigned char & Channel, unsigned char & Data1, unsigned char & Data2)
{
	bool Result = false;
	
	m_csQueue.Lock();

	if (m_iQueueHead != m_iQueueTail) {
		Result = true;

		Message = m_iMsgTypeQueue[m_iQueueTail];
		Channel = m_iMsgChanQueue[m_iQueueTail];
		Data1	= m_iData1Queue[m_iQueueTail];
		Data2	= m_iData2Queue[m_iQueueTail];
		m_iQuant = m_iQuantization[m_iQueueTail];

		m_iQueueTail = (m_iQueueTail + 1) % MAX_QUEUE;
	}

	m_csQueue.Unlock();

	return Result;
}

int CMIDI::GetQuantization() const
{
	return m_iQuant;
}

/*void CMIDI::ToggleInput()
{
   if (m_bInStarted)
//		midiInStop(m_hMIDIIn);
      midiin->cancelCallback();
   else
//		midiInStart(m_hMIDIIn);
      midiin->setCallback(&RtMidiInProc);

	m_bInStarted = !m_bInStarted;
}
*/


void CMIDI::ToggleInput()
{
    if (m_bInStarted)
    {
        // Stop MIDI input
        midiin->cancelCallback();
    }
    else
    {
        // Start MIDI input
        midiin->setCallback(&CMIDI::midiCallback, this); // Passer l'instance actuelle en tant que userData
    }

    // Toggle the input status flag
    m_bInStarted = !m_bInStarted;
}





void CMIDI::WriteNote(unsigned char Channel, unsigned char Note, unsigned char Octave, unsigned char Velocity)
{
	static unsigned int LastNote[MAX_CHANNELS];	// Quick hack
//	static unsigned int LastVolume[MAX_CHANNELS];

	if (/*!m_bOpened ||*/ m_iOutDevice == 0 || m_hMIDIOut == NULL)
		return;

	if (Note == 0)
		return;

	Octave++;

	if ((Channel == 4 || Channel == 3) && Octave < 3)
		Octave += 3;

	if (Velocity == 0x10)
		Velocity--;
		/*
		Velocity = LastVolume[Channel];
	else
		LastVolume[Channel] = Velocity;*/

	unsigned int MsgChannel = Channel;
	unsigned int MsgType;

	unsigned int Data1 = Note - 1 + Octave * 12;		// note
	unsigned int Data2 = Velocity * 8;					// velocity

	if (Note == HALT || Note == RELEASE) {
		MsgType = MIDI_MSG_NOTE_OFF;
		Data2 = 0;
		Data1 = LastNote[Channel];
		LastNote[Channel] = 0;
	}
	else {
		if (LastNote[Channel] != 0 && Note != LastNote[Channel])
			WriteNote(Channel, HALT, 0, 0);

		MsgType = MIDI_MSG_NOTE_ON;
		LastNote[Channel] = Data1;
	}

	unsigned int Status = (MsgType << 4) | MsgChannel;
	unsigned int dwParam1 = Status | (Data1 << 8) | (Data2 << 16);

//	midiOutShortMsg(m_hMIDIOut, dwParam1);
   std::vector<unsigned char> data;
   data.push_back(Status);
   data.push_back(Data1);
   data.push_back(Data2);
   midiout->sendMessage(&data);
}

void CMIDI::ResetOutput()
{
//	midiOutReset(m_hMIDIOut);
}

bool CMIDI::IsOpened() const
{
	return m_bInStarted;
}

bool CMIDI::IsAvailable() const
{
	return m_hMIDIIn != NULL;
}

int CMIDI::GetInputDevice() const 
{ 
	return m_iInDevice; 
}

int CMIDI::GetOutputDevice() const 
{ 
	return m_iOutDevice; 
}
