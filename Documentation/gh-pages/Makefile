# Minimal makefile for Sphinx documentation
#

# You can set these variables from the command line, and also
# from the environment for the first two.
SPHINXOPTS    ?=
SPHINXBUILD   ?= sphinx-build
SOURCEDIR     = source
BUILDDIR      = build
HTMLDIR       = docs

# Put it first so that "make" without argument is like "make help".
help:
	@$(SPHINXBUILD) -M help "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

github:
	@make html
	@rm -rf "$(HTMLDIR)"
	@mv "$(BUILDDIR)/html" "$(HTMLDIR)"
	@touch "$(HTMLDIR)/.nojekyll"
	@mkdir "$(HTMLDIR)/PDFs"
	@cp ../../KEMField/Documentation/manual/manual.pdf "$(HTMLDIR)/PDFs"
	@cp ../../Documentation/gh-pages/source/_files/Furse_2017_New_J_Phys_19_053012_noheader.pdf "$(HTMLDIR)/PDFs"
.PHONY: help github Makefile

# Catch-all target: route all unknown targets to Sphinx using the new
# "make mode" option.  $(O) is meant as a shortcut for $(SPHINXOPTS).
%: Makefile
	@$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)
