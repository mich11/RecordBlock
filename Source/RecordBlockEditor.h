/*
    ------------------------------------------------------------------

    This file is part of the Open Ephys GUI
    Copyright (C) 2013 Open Ephys

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

#ifndef __RECORDBLOCKEDITOR_H_F9C69E2B__
#define __RECORDBLOCKEDITOR_H_F9C69E2B__

#include <EditorHeaders.h>

/**

  User interface for the RecordBlock processor.

  @see RecordBlock

*/

class RecordBlockEditor : public GenericEditor,
    public ComboBox::Listener
{
public:
    RecordBlockEditor(GenericProcessor* parentNode, bool useDefaultParameterEditors);
    ~RecordBlockEditor();
    void comboBoxChanged(ComboBox* comboBox);
    void updateSettings();
    void loadCustomParameters(XmlElement*);
    void saveCustomParameters(XmlElement*);

private:
	struct EventSources
	{
		unsigned int eventIndex;
		unsigned int channel;
	};

	Array<EventSources> eventSourceArray;
    ScopedPointer<ComboBox> availableChans, triggerMode, triggerPol;
    ScopedPointer<Label> chanSel, triggerLabel, polLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RecordBlockEditor);

};


#endif