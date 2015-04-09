include_files = \
    title \
    body \
    document

.PHONY: all
all: document.pdf
	pdflatex -interaction=batchmode document > /dev/null

document.pdf: $(include_files:=.tex)
	pdflatex -interaction=batchmode document > /dev/null

.PHONY: clean
clean:
	rm -v --force \
            document.pdf \
            document.log
	rm -v --force $(include_files:=.aux)
