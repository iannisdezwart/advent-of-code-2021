CFLAGS = -g

.PHONY: all
all:
	for src in `find . -name "*.c"`; do \
		echo "compiling $$src"; \
		$(CC) $(CFLAGS) -o $${src%.c} $$src; \
	done
