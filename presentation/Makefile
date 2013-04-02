PROJECT = turekm1_thesis_presentation_2009
PDFLATEX = pdflatex -halt-on-error

all: $(PROJECT).pdf

$(PROJECT).pdf: $(PROJECT).tex
	$(PDFLATEX) $<
#	$(PDFLATEX) $<

clean:
	rm -f *.log *.aux *.bbl *.blg *.lof *.lot *.dvi *.toc *.out *~ *.ps *.snm *.nav *.pdf
