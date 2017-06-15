exercise.pdf: exercise.tex
	pdflatex -shell-escape exercise

clean:
	rm exercise.pdf
