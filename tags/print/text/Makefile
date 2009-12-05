PROJECT = turekm1_thesis_2009
DVIPS = dvips
LATEX = latex
PDFLATEX = pdflatex -halt-on-error
BIBTEX = bibtex


all: $(PROJECT).pdf

ref:	$(PROJECT).tex
	$(PDFLATEX) $(PROJECT).tex
	$(BIBTEX) $(PROJECT)
	$(PDFLATEX) $(PROJECT).tex
	$(PDFLATEX) $(PROJECT).tex

bib:
	$(BIBTEX) $(PROJECT)

vlna:
	iconv -f utf8 -t ISO_8859-2 < $(PROJECT).tex > $(PROJECT)_iso.tex
	vlna -m -n -w -f $(PROJECT)_iso.tex $(PROJECT)_iso.tex.bak
	iconv -f ISO_8859-2 -t utf8 < $(PROJECT)_iso.tex.bak > $(PROJECT).tex
	rm $(PROJECT)_iso.tex $(PROJECT)_iso.tex.bak

$(PROJECT).pdf: $(PROJECT).tex
	$(PDFLATEX) $<
	$(PDFLATEX) $<

#$(PROJECT).pdf: *.ps
#	ps2pdf -s PAPERSIZE=a4 $<

$(PROJECT).ps: $(PROJECT).tex
	$(LATEX) $<

clean:
	rm -f *.log *.aux *.bbl *.blg *.lof *.lot *.dvi *.toc *.out *~ *.ps
