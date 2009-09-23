PREFIX = /usr/local/bin

.PHONY: build
.PHONY: install
.PHONY: lines
.PHONY: svnlog
.PHONY: statsvn
.PHONY: clean

build:
	make -C ./bbd/
	make -C ./bbdgui/
	make -C ./benchmarks/
	make -C ./graphs/generator/
	make -C ./text/

install: build
	cp ./bbd/bbd $(PREFIX)
	cp ./bbdgui/bbdgui $(PREFIX)

uninstall:
	rm $(PREFIX)/bbd
	rm $(PREFIX)/bbdgui

lines:
	cat ./bbd/*.hpp ./bbd/*.cpp ./bbdgui/*.hpp ./bbdgui/*.cpp | wc -l

svnlog:
	svn log --revision $(shell svnversion -c | tr 'A-Z' ' ') --verbose

statsvn:
	svn log -v --xml > logfile.log
	statsvn -output-dir statsvn -title bbd logfile.log .
	rm logfile.log

clean:
	make -C ./bbd/ clean
	rm -rf ./bbd/bin/ ./bbd/obj/
	make -C ./bbdgui/ clean
	rm ./bbdgui/bbdgui
	make -C ./benchmarks/ clean
	make -C ./graphs/generator/ clean
	rm -rf ./statsvn/
	make -C ./text/ clean
