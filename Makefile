SRC := "draft"
SRCXML := $(SRC).xml

all:	text

text:	$(SRCXML)
	xml2rfc $(SRCXML) $(SRC).txt

# Pull and update this repository.
update:
	git checkout master && git remote update && git rebase

push:
	git push -v origin master:master

.PHONY:	$(SRCXML)
