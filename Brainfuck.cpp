#include "Parser.h"
#include "Executor.h"

int main() {
	Parser parser;
	parser.parseFromInput();

	Executor exec(parser.getCode(), parser.getInputs());
	exec.run();
	return 0;
}
