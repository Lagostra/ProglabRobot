'''
    Takes a musicXML file, and creates a file that can be played by my MusicPlayer arduino library.
    Written by Eivind Lie Andreassen, 2016
'''

import xml.dom.minidom
import valueHelper

xmlPath = input("Enter path to MusicXML file: ")
savePath = input("Enter save path of converted file: ")

domTree = xml.dom.minidom.parse(xmlPath)
collection = domTree.documentElement

if(collection.hasAttribute("example")):
    print(collection.getAttribute("sample"))

notesXML = collection.getElementsByTagName("note")

notes = []
noteLengths = []

for note in notesXML:
    if (len(note.getElementsByTagName("rest"))>0):
        noteValue = '0'
    else:
        noteValue = note.getElementsByTagName("step")[0].childNodes[0].data + note.getElementsByTagName("octave")[0].childNodes[0].data
        if len(note.getElementsByTagName("alter")) > 0:
            index = valueHelper.noteValues.index(noteValue) + int(note.getElementsByTagName("alter")[0].childNodes[0].data)
            if(index < 0):
                index = 0
            elif(index >= len(valueHelper.noteValues)):
                index = len(valueHelper.noteValues) - 1
            noteValue = valueHelper.noteValues[index]


    if(len(note.getElementsByTagName("type")) == 0):
        continue

    noteLength = valueHelper.lengthValues[note.getElementsByTagName("type")[0].childNodes[0].data]
    if(len(note.getElementsByTagName("dot")) > 1):
        noteLength *= 1.75
    elif(len(note.getElementsByTagName("dot")) > 0):
        noteLength *= 1.5

    notes.append(noteValue)
    noteLengths.append(noteLength)


output = "NoteNumber: " + str(len(notes)) + "\n\n"

output += "Notes:\n{"
for i in range(len(notes)):
    output += notes[i]
    if(i < len(notes) - 1):
        output += ", "
        if(i != 0 and i % 10 == 0):
            output += "\n"
output += "};\n\n"

output += "NoteLengths:\n{"
for i in range(len(notes)):
    output += str(noteLengths[i])
    if(i < len(notes) - 1):
        output += ", "
        if(i != 0 and i % 10 == 0):
            output += "\n"
output += "};"

with open(savePath, "w") as file:
    file.write(output)