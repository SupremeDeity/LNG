// Demonstration of parsing lng.

#include <LNG.h>
#include <iostream>

int main(int argc, char** argv) {
	const char* file = nullptr;
	for (int x = 0; x < argc; x++) {
		if ( 0 == strcmp(argv[x], "-f")) {
			if(!((x + 1) >= argc)) {
				file = argv[x + 1];
				break;
			}
			else {
				std::cout << "File path not provided!\n";
				std::cin.get();
				return -1;
			}
		}
	}

	if (file != nullptr) {
		Parser* parser = new Parser(file);
		parser->Parse();

		auto props = parser->GetProperties();

		std::string section = "";

		for (int x = 0; x < props->size(); x++) {
			if (section != props->at(x).first) {
				section = props->at(x).first;
				std::cout << "Section: " << props->at(x).first << std::endl;
			}
			std::cout << "\tKey: " << props->at(x).second->GetName() << "\tValue: " << props->at(x).second->ValuesToString() << std::endl;
		}
	}
	else {
		std::cout << "No file provided to be parsed. Use -f arg together with path to .lng file.\n";
	}
	
	std::cin.get();
}