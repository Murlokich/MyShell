help:  ## Show this help message
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | \
		sort | \
		awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-20s\033[0m %s\n", $$1, $$2}'

build: ## builds the code
	g++ src/executor/DefaultExecutor.cpp \
		src/parser/DefaultParser.cpp \
		src/reader/InteractiveReader.cpp \
		src/reader/FileReader.cpp \
		src/shell/Wish.cpp \
		src/entities/Command.cpp \
		src/main.cpp \
		-std=c++20 -o wish
	cp wish processes-shell/

run-tests: ## run e2e tests
	cd processes-shell && ./test-wish.sh

run-interactive: ## runs already built wish executable in interactive mode
	./wish

run-file: ## runs already built wish executable in file mode for test.txt
	./wish test.txt