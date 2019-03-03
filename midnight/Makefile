all: solo.h build

solo.h: xml_to_h.py solo.musicxml
	./xml_to_h.py solo.musicxml solo.h

.PHONY: build
build: solo.h midnight.ino
	arduino --verify midnight.ino
