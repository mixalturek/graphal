PREFIX = /usr/local/bin

.PHONY: build
.PHONY: install
.PHONY: lines
.PHONY: doc
.PHONY: svnlog
.PHONY: statsvn
.PHONY: clean

build:
	make -C ./bbd/
	cd ./bbdgui/ ; qmake ; cd -
	make -C ./bbdgui/
	make -C ./benchmarks/
	make -C ./graphs_generator/
	make -C ./man/
	make -C ./presentation/
	make -C ./text/

install: build
	cp ./bbd/bbd $(PREFIX)
	cp ./bbdgui/bbdgui $(PREFIX)

uninstall:
	rm $(PREFIX)/bbd
	rm $(PREFIX)/bbdgui

lines:
	cat ./bbd/*.hpp ./bbd/*.cpp ./bbdgui/*.hpp ./bbdgui/*.cpp | wc -l

doc:
	doxygen Doxyfile

svnlog:
	svn log -v > ChangeLog

statsvn:
	svn log -v --xml > logfile.log
	statsvn -output-dir svnstat -title bbd logfile.log .
	rm logfile.log

clean:
	make -C ./bbd/ clean
	rm -rf ./bbd/bin/ ./bbd/obj/
	make -C ./bbdgui/ clean
	rm -f ./bbdgui/bbdgui
	make -C ./benchmarks/ clean
	make -C ./graphs_generator/ clean
	make -C ./man/ clean
	make -C ./presentation/ clean
	rm -rf ./doc/
	rm -rf ./svnstat/
	make -C ./text/ clean
