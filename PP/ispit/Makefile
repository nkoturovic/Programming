FILENAME=README

.PHONY: clean

$(FILENAME).pdf : $(FILENAME).md template.latex
	./make.sh $(FILENAME)

clean:
	\rm *.pdf
