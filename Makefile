BINDIR=bin
EXAMPLEDIR=examples
LIBDIR=src
TARGET=photon
TARGET_VERSION=0.6.2

$(BINDIR)/examples.bin: $(wildcard $(EXAMPLEDIR)/usage/*.ino) $(wildcard $(LIBDIR)/*)
	particle compile $(TARGET) --target $(TARGET_VERSION) $(EXAMPLEDIR) --saveTo $(BINDIR)/examples.bin

clean:
	rm -f $(BINDIR)/*.bin *~
