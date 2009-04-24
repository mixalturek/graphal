PROJECT = turekm1_thesis_2009
DVIPS = dvips
LATEX = latex
PDFLATEX = pdflatex
BIBTEX = bibtex


all: $(PROJECT).pdf

ref:	$(PROJECT).tex
	$(PDFLATEX) $(PROJECT).tex
	$(BIBTEX) $(PROJECT)
	$(PDFLATEX) $(PROJECT).tex
	$(PDFLATEX) $(PROJECT).tex

bib:
	$(BIBTEX) $(PROJECT)

$(PROJECT).pdf: *.tex
	$(PDFLATEX) $<
	$(PDFLATEX) $<

#$(PROJECT).pdf: *.ps
#	ps2pdf -s PAPERSIZE=a4 $<

$(PROJECT).ps: *.tex
	$(LATEX) $<

clean:
	rm -f *.log *.aux *.bbl *.blg *.lof *.lot *.dvi *.toc *.out *~ *.ps
