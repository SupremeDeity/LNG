#include <LNG.h>
#include <iostream>

int main() {
	Parser* parser = new Parser("assets/test.lng");
	parser->Parse();

	std::cout << parser->GetProperty("RenderProps", "RendererName").second->ValuesToString() << std::endl;

	std::cout << parser->GetProperty("PhysProps", "Color").second->ValuesToString() << std::endl;

	/*parser->Add("PhysProps", new StringProperty("Render", "Yolo"));
	parser->Flush();*/

	std::cin.get();
}