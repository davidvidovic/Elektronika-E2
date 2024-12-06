PORT = COM6

CC = avr-gcc
OBJCOPY = avr-objcopy

SOURCE = main
TARGET = app

program: $(TARGET).hex
	avrdude -c arduino -p ATMEGA328P -P $(PORT) -b 115200 -U flash:w:$(TARGET).hex

$(TARGET).hex: $(TARGET).elf
	${OBJCOPY} -O ihex $(TARGET).elf $(TARGET).hex

$(TARGET).elf: $(SOURCE).o
	${CC} -mmcu=atmega328p $(SOURCE).o -o $(TARGET).elf

$(SOURCE).o: $(SOURCE).c
	${CC} -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o $(SOURCE).o $(SOURCE).c

clean:
	rm *.o *.elf *.hex