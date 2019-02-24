#!/usr/bin/env python3
import argparse
import music21


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("infile")
    parser.add_argument("--bpm", type=float, default=100)
    args = parser.parse_args()

    score = music21.converter.parse(args.infile)
    score = score.stripTies()
    onsets = []
    seconds_per_quarter = 60.0 / args.bpm
    for n in score.recurse().notes:
        onsets.append(n.getOffsetInHierarchy(score) * seconds_per_quarter)

    print(onsets)


if __name__ == '__main__':
    main()
