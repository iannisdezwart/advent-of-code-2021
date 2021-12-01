CFLAGS = -g

.PHONY: all
all:
	for src in `find . -name "*.s"`; do \
		echo "compiling $$src"; \
		$(CC) $(CFLAGS) -o $${src%.s} $$src; \
	done
