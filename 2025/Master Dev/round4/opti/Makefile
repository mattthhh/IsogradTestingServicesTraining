CC=gcc
CFLAGS=-Wall -Wextra -O2
SRC=code.c
BIN=code
SAMPLE_DIR=sample

.PHONY: all test clean

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) -o $(BIN) $(SRC) -lm

test: $(BIN)
	@success=0; \
	total=0; \
	for input in $(SAMPLE_DIR)/input*.txt; do \
		num=$${input##*input}; num=$${num%%.txt}; \
		output_file=$(SAMPLE_DIR)/output$${num}.txt; \
		if [ -f "$$output_file" ]; then \
			total=$$((total+1)); \
			# Compare la sortie du programme (stdin) à la sortie attendue \($$output_file\) via un pipe compatible sh \(sans substitution de processus\) \
			if ./$(BIN) < "$$input" | diff -q - "$$output_file" > /dev/null; then \
				echo "Test $$num: OK"; \
				success=$$((success+1)); \
			else \
				echo "Test $$num: FAILED"; \
				./$(BIN) < "$$input" | diff -u - "$$output_file" || true; \
			fi; \
		fi; \
	done; \
	echo "$$success/$$total tests passed."; \
	if [ "$$success" -eq "$$total" ]; then exit 0; else exit 1; fi

clean:
	rm -f $(BIN)
