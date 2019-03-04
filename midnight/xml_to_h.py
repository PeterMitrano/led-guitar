#!/usr/bin/env python3
import numpy as np
import argparse
import music21

"""
The range of notes in the solo is 18 half steps, and the neck of our guitar will have 20 LEDs,
so we can just ignore the last two and map one-to-one. Therefore B3 maps to 0.
"""

num_leds = 60 * 3 + 30 * 2
end_outline_leds = 60 * 3

red = np.array([1, 0, 0])
green = np.array([0, 1, 0])
blue = np.array([0, 0, 1])


class FretEvent:

    def __init__(self):
        self.onset = 0
        self.duration = 0
        self.string_number = 0
        self.fret_number = 0

    def __repr__(self):
        return "({},{},{})".format(self.onset, self.string_number, self.fret_number)


class Event:

    def __init__(self):
        self.onset = 0
        self.duration = 0
        self.midi_number = 0

    def __repr__(self):
        return "({},{})".format(self.onset, self.midi_number)


def define_constant(vartype, name, value):
    return "{} const {} = {};\n".format(vartype, name, value)


def define_fret_events_array(events):
    definition = "constexpr unsigned int const fret_events_size = {};\n".format(len(events))
    definition += "FretEvent const fret_events[] = {\n"
    for e in events:
        definition += "  FretEvent{" + "{}u, {}u, {}u, {}u".format(e.onset, e.duration, e.string_number, e.fret_number) + "},\n"
    definition += "};\n"
    return definition


def define_outline_events_array(events):
    definition = "constexpr unsigned int const outline_events_size = {};\n".format(len(events))
    definition += "OutlineEvent const outline_events[] = {\n"
    for e in events:
        definition += "  OutlineEvent{" + "{}u, {}u, {}u".format(e.onset, e.duration, e.midi_number) + "},\n"
    definition += "};\n"
    return definition


def main():
    np.random.seed(0)

    parser = argparse.ArgumentParser()
    parser.add_argument("infile")
    parser.add_argument("outfile")
    parser.add_argument("--bpm", type=float, default=100)
    args = parser.parse_args()

    seconds_per_quarter = 60.0 / args.bpm
    dt_per_quarter = 32
    us_per_dt = int(seconds_per_quarter / dt_per_quarter * 1000000)

    fret_events = []
    outline_events = []

    score = music21.converter.parse(args.infile)
    fretting_part = score.parts[0].flat.stripTies()  # notated with tablature
    for fret_note in fretting_part.notes:
        fret_event = FretEvent()
        fret_event.onset = int(fret_note.getOffsetInHierarchy(score) * dt_per_quarter)
        fret_event.duration = int(fret_note.quarterLength * dt_per_quarter)
        for articulation in fret_note.articulations:
            if 'FretIndication' in articulation.classSet:
                fret_event.fret_number = int(articulation.number)
            if 'StringIndication' in articulation.classSet:
                fret_event.string_number = int(articulation.number)
        fret_events.append(fret_event)

    outline_part = score.parts[1].flat.stripTies()  # notated with a piano score
    for outline_note in outline_part.notes:
        outline_event = Event()
        outline_event.onset = int(outline_note.getOffsetInHierarchy(score) * dt_per_quarter)
        outline_event.duration = int(outline_note.quarterLength * dt_per_quarter)
        outline_event.midi_number = outline_note.pitch.midi
        outline_events.append(outline_event)

    with open(args.outfile, 'w') as outfile:
        outfile.write('#include "util.h"\n')
        outfile.write(define_constant("unsigned int", "us_per_dt", us_per_dt))
        outfile.write(define_outline_events_array(outline_events))
        outfile.write(define_fret_events_array(fret_events))
        outfile.write("\n")


if __name__ == '__main__':
    main()
