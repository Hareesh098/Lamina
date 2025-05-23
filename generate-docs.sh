#!/bin/bash
# Generate Doxygen documentation
rm -rf ./docs/html ./docs/latex
cd doxygen
doxygen Doxyfile
cd ../
cd docs
pdflatex README.tex
pdflatex README.tex
mv html/* .
cd latex
make
echo "Documentation generated in docs/html and docs/latex folders"

