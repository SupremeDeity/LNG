#include "lngpch.h"
#include "LNG.h"

int main() {
	std::cout << "Parsing with LNG " << LNG_VERSION_MAJOR << "." << LNG_VERSION_MINOR << std::endl;

	// Parser
	Parser* parser = new Parser("test.lng");
	parser->Parse();

	auto p1 = parser->GetProperty("RenderProps", "RendererID");
	auto p2 = parser->GetProperty("RenderProps", "RendererName");
	auto p3 = parser->GetProperty("RenderProps", "MaxVI");
	auto p4 = parser->GetProperty("PhysProps", "Color");
	auto p5 = parser->GetProperty("PhysProps", "TexID");
	auto p6 = parser->GetProperty("PhysProps", "MatName");
	auto p7 = parser->GetProperty("PhysProps", "isMetallic");

	std::cin.get();
}