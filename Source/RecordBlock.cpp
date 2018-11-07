/*
    ------------------------------------------------------------------

    This file is part of the Open Ephys GUI
    Copyright (C) 2016 Open Ephys

    ------------------------------------------------------------------

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <stdio.h>
#include "RecordBlock.h"


RecordBlock::RecordBlock()
    : GenericProcessor  ("Record Block")
    , triggerChannel    (0)
{
    setProcessorType (PROCESSOR_TYPE_UTILITY);
}


RecordBlock::~RecordBlock()
{
}


AudioProcessorEditor* RecordBlock::createEditor()
{
    editor = new RecordBlockEditor (this, true);
    return editor;
}


void RecordBlock::setParameter (int parameterIndex, float newValue)
{
    if (parameterIndex == 0)
    {
		triggerEvent = static_cast<int>(newValue);
    }
	else if (parameterIndex == 1)
	{
		triggerChannel = static_cast<int>(newValue);
	}
    else if (parameterIndex == 2)
    {
        triggerType = (Types)((int)newValue - 1);
    }
    else if (parameterIndex == 3)
    {
        triggerEdge = (Edges)((int)newValue - 1);
    }
}


bool RecordBlock::enable()
{
    return true;
}


void RecordBlock::process (AudioSampleBuffer& buffer)
{
    checkForEvents ();
}


void RecordBlock::handleEvent (const EventChannel* eventInfo, const MidiMessage& event, int)
{
	if (triggerEvent < 0) return;
    if (eventInfo->getChannelType() == EventChannel::TTL && eventInfo == eventChannelArray[triggerEvent])
    {
		TTLEventPtr ttl = TTLEvent::deserializeFromMessage(event, eventInfo);
		if (ttl->getChannel() == triggerChannel)
		{
			int eventId = ttl->getState() ? 1 : 0;
			int edge = triggerEdge == RISING ? 1 : 0;

			const MessageManagerLock mmLock;

			if (triggerType == SET)
			{
				if (eventId == edge)
				{
					CoreServices::setRecordingStatus(true);
				}
				else
				{
					CoreServices::setRecordingStatus(false);
				}
			}
			else if (triggerType == TOGGLE && eventId == edge)
			{
				CoreServices::setRecordingStatus(!CoreServices::getRecordingStatus());
			}
		}
    }
}


