#include "lngpch.h"
#include "Parser.h"


Parser::Parser(const std::string & filepath)
	: m_FilePath(filepath)
{
	std::fstream stream(filepath, std::fstream::in);
	if (!stream.is_open()) {
		std::cout << "Error: FILE " << filepath << " NOT FOUND!!" << std::endl;
		errors++;
		return;
	}

	std::string line;
	while (std::getline(stream, line)) {
		m_FileBuffer.push_back(line);
	}

	std::cout << filepath << ": " << m_FileBuffer.size() << " lines found." << std::endl;
}

Parser::Parser(const std::vector<std::string>& src)
{
	m_FileBuffer = src;
}

Parser::~Parser()
{
	m_FileBuffer.clear();
}

void Parser::Parse()
{
	Lex();
	std::cout << "\nFinished Parsing. Errors: " << errors << ", Warnings: " << warnings << std::endl;
}

std::pair<std::string, Property*> Parser::GetProperty(const std::string section, const std::string key)
{
	for (auto property : m_Properties) {
		if (property.first.compare(section) == 0) {
			if (property.second->GetName() == key) {
				return property;
			}
		}
	}
	return std::pair<std::string, Property*>();
}

void Parser::AddProperty(std::string section, Property * prop)
{
	// Check if property already exists.
	for (auto [key, value] : m_Properties) {
		if (key == section) {
			if (value->GetName() == prop->GetName()) {
				if (Assert(value->GetName() != prop->GetName(), "Warning: A Property named '" + prop->GetName() + "' already exists. Ignoring", AssertType::WARNING)) { return; }
			}
		}
	}

	m_Properties.push_back({ section, prop });
}

void Parser::Flush()
{
	if (errors > 0) { std::cout << "Error: Could not write to file due to errors found while parsing.\n"; return; }


	// Create Section
	std::vector<std::string> file;
	std::string currentSection = "";
	for (int x = 0; x < m_Properties.size(); x++) {
		// Set the section
		if (currentSection.empty()) {
			currentSection = m_Properties[x].first;
			if (x == 0) { file.push_back("@SECTION (" + currentSection + ")"); }
			else { file.push_back("\n@SECTION (" + currentSection + ")"); }
		}
		else if (currentSection != m_Properties[x].first) {
			// If a new section has been started, we end the section
			file.push_back("@SECTION [END]");
			currentSection = m_Properties[x].first;
			// Then we create the new section
			file.push_back("\n@SECTION (" + currentSection + ")");
		}

		std::string TypePart = "[" + m_Properties[x].second->TypeToStr(m_Properties[x].second->GetType()) + "]";
		std::string NamePart = "(" + m_Properties[x].second->GetName() + ")";

		std::string ValuesPart;

		if (m_Properties[x].second->ParentType(m_Properties[x].second->GetType()) == Types::STRING) {
			ValuesPart = "{\"" + m_Properties[x].second->ValuesToString() + "\"}";
		}
		else {
			ValuesPart = "{" + m_Properties[x].second->ValuesToString() + "}";
		}

		std::string FormattedLine = TypePart + NamePart + ": " + ValuesPart;
		file.push_back(FormattedLine);

		if (((int64_t)x + 1) == m_Properties.size()) {
			if (!currentSection.empty()) {
				file.push_back("@SECTION [END]");
			}
		}

	}

	std::ofstream FileStream(m_FilePath, std::ios::trunc);
	if (!FileStream.is_open()) { std::cout << "Error: Failed to open file\n"; errors++; }

	for (auto x : file) {
		FileStream << x + "\n";
	}
	FileStream.close();

	std::cout << "\nFlush Finished. Errors: " << errors << ", Warnings: " << warnings << std::endl;
}

//##########################
//####### PRIVATE ##########
//##########################

void Parser::Lex()
{
	std::string section = "";

	for (int line = 0; line < m_FileBuffer.size(); line++) {

		// Find A Section.
		if (m_FileBuffer[line].find("@SECTION") != std::string::npos) {

			// Section has ended
			if (m_FileBuffer[line].find("[END]") != std::string::npos) {
				if (Assert(!section.empty(), "Line: " + std::to_string((line + 1)) + ": No current section!", AssertType::ERROR)) { return; }
				section = "";

				continue;
			}

			if (!section.empty()) {
				std::cout << "Error: Line " << line + 1 << " : New section started before end of last section '" << section << "'. Did you forgot to call @SECTION [END]?\n";
				errors++;
				return;
			}

			// In Section...
			size_t fbracket = m_FileBuffer[line].find("(");
			size_t sbracket = m_FileBuffer[line].find(")");

			if (Assert(fbracket != std::string::npos, "Line: " + std::to_string((line + 1)) + ": Expected '('", AssertType::ERROR)) { return; }
			if (Assert(sbracket != std::string::npos, "Line: " + std::to_string((line + 1)) + ": Expected ')'", AssertType::ERROR)) { return; }

			section = m_FileBuffer[line].substr((int64_t)fbracket + 1, ((int64_t)sbracket - (int64_t)fbracket) - 1);

			continue;

		}

		else if (!section.empty() && !m_FileBuffer[line].empty()) {

			size_t fsbracket = m_FileBuffer[line].find("[");
			size_t ssbracket = m_FileBuffer[line].find("]", fsbracket + 1);
			size_t fbracket = m_FileBuffer[line].find("(", ssbracket + 1);
			size_t sbracket = m_FileBuffer[line].find(")", fbracket);
			size_t colon = m_FileBuffer[line].find(":", sbracket + 1);
			size_t fcbracket = m_FileBuffer[line].find("{", colon + 1);
			size_t scbracket = m_FileBuffer[line].find("}", fcbracket + 1);
			size_t fquote = m_FileBuffer[line].find("\"", fcbracket + 1);
			size_t squote = m_FileBuffer[line].find("\"", fquote + 1);

			if (Assert(fsbracket != std::string::npos, "Line: " + std::to_string((line + 1)) + ": Expected '['", AssertType::ERROR)) { return; }
			if (Assert(ssbracket != std::string::npos, "Line: " + std::to_string((line + 1)) + ": Expected ']'", AssertType::ERROR)) { return; }

			if (Assert(fbracket != std::string::npos, "Line: " + std::to_string((line + 1)) + ": Expected '('", AssertType::ERROR)) { return; }
			if (Assert(sbracket != std::string::npos, "Line: " + std::to_string((line + 1)) + ": Expected ')'", AssertType::ERROR)) { return; }

			if (Assert(fcbracket != std::string::npos, "Line: " + std::to_string((line + 1)) + ": Expected '{'", AssertType::ERROR)) { return; }
			if (Assert(scbracket != std::string::npos, "Line: " + std::to_string((line + 1)) + ": Expected '}'", AssertType::ERROR)) { return; }

			if (Assert(colon != std::string::npos, "Line: " + std::to_string((line + 1)) + ": Expected ':'", AssertType::ERROR)) { return; }


			std::string typeStr = m_FileBuffer[line].substr((int64_t)fsbracket + 1, ((int64_t)ssbracket - (int64_t)fsbracket) - 1);
			Types type = Property::StrToType(typeStr);

			if (type == Types::STRING) {
				if (Assert(fquote != std::string::npos, "Line: " + std::to_string((line + 1)) + ": Expected '\"'", AssertType::ERROR)) { return; }
				if (Assert(squote != std::string::npos, "Line: " + std::to_string((line + 1)) + ": Expected Closing '\"'", AssertType::ERROR)) { return; }
			}
			else {
				// If quotes are used but type != String
				if (fquote != std::string::npos || squote != std::string::npos) {
					if (Assert(false, "Line: " + std::to_string((line + 1)) + ": Expected 'String', got " + Property::TypeToStr(type) + " instead", AssertType::ERROR)) { return; }
					errors++;
					return;
				}
			}


			std::string name = m_FileBuffer[line].substr((int64_t)fbracket + 1, ((int64_t)sbracket - (int64_t)fbracket) - 1);

			Property* prop = nullptr;

			// First we split the string using the delim ','
			std::vector<std::string> out;
			std::string params;

			if (type == Types::STRING) {
				params = m_FileBuffer[line].substr((int64_t)fquote + 1, ((int64_t)squote - (int64_t)fquote) - 1);
			}
			else {
				params = m_FileBuffer[line].substr((int64_t)fcbracket + 1, ((int64_t)scbracket - (int64_t)fcbracket) - 1);
			}

			// Split the params if variable is a vector type.
			Split(params, ',', out);

			if (Assert(out.size() == Property::ParamCountForProperty(type), "Line: " + std::to_string(line + 1) + ": Invalid number of arguments provided!", AssertType::ERROR)) { return; }

			prop = SetPropertyValues(type, out);

			// This is common in all properties
			prop->SetName(name);

			// Give warning if property exists
			for (auto prop : m_Properties) {
				if (prop.first == section && prop.second->GetName() == name) {
					if (Assert(false, "Line: " + std::to_string(line + 1) + " : Duplicate Key \"" + name + "\" Found in Section \"" + section + "\"", AssertType::WARNING)) {}
				}
			}

			// Add Property to buffer
			m_Properties.push_back({ section, prop });
			
			continue;
		}
	}
}

bool Parser::Assert(bool condition, std::string toThrow, AssertType type)
{
	std::string typeStr = "";
	if (type == AssertType::ERROR) { typeStr = "ERROR"; }
	else if (type == AssertType::WARNING) { typeStr = "WARNING"; }
	else { typeStr = "NONE"; }
	if (!condition) {
		std::cout << typeStr << ": " << toThrow << std::endl;
		if (type == AssertType::ERROR) {
			errors++;
		}
		else if (type == AssertType::WARNING) {
			warnings++;
		}
		return true;
	}
	return false;
}

Property * Parser::SetPropertyValues(Types type, std::vector<std::string> vals)
{
	const int a = 2;
	if (type == Types::STRING) {
		return new StringProperty({ vals[0] });
	}

	if (Property::ParentType(type) == Types::FLOAT) {
		std::vector<float> arr;

		for (auto toConvert : vals) {
			arr.push_back(std::stof(toConvert));
		}

		switch (type)
		{
		case FLOAT:
			return new FloatProperty({ arr[0] });
		case FLOAT2:
			return new Float2Property({ arr[0],  arr[1] });
		case FLOAT3:
			return new Float3Property({ arr[0], arr[1],  arr[2] });
		case FLOAT4:
			return new Float4Property({ arr[0], arr[1],  arr[2], arr[3] });

		default:
			break;
		}
	}

	if (Property::ParentType(type) == Types::INT) {
		std::vector<int> arr;

		for (auto toConvert : vals) {
			arr.push_back(std::stoi(toConvert));
		}

		switch (type)
		{
		case INT:
			return new IntProperty({ arr[0] });
		case INT2:
			return new Int2Property({ arr[0],  arr[1] });
		case INT3:
			return new Int3Property({ arr[0], arr[1],  arr[2] });
		case INT4:
			return new Int4Property({ arr[0], arr[1],  arr[2], arr[3] });

		default:
			break;
		}
	}

	if (Property::ParentType(type) == Types::BOOL) {
		std::vector<bool> arr;

		for (auto toConvert : vals) {
			bool Converted;
			ConvertBool(type, toConvert, Converted);
			arr.push_back(Converted);
		}

		switch (type)
		{
		case BOOL:
			return new BoolProperty(arr[0]);
		case BOOL2:
			return new Bool2Property({ arr[0],  arr[1] });
		case BOOL3:
			return new Bool3Property({ arr[0], arr[1],  arr[2] });
		case BOOL4:
			return new Bool4Property({ arr[0], arr[1],  arr[2], arr[3] });

		default:
			break;
		}
	}
	return nullptr;
}

void Parser::Split(std::string const & str, const char delim, std::vector<std::string>& out)
{
	// construct a stream from the string
	std::stringstream ss(str);

	// Split the string using the given delim
	std::string Value;
	while (std::getline(ss, Value, delim)) {
		out.push_back(Value);
	}
}

bool Parser::ConvertBool(Types type, std::string Val, bool & ToVal)
{
	
	Val.erase(std::remove_if(Val.begin(), Val.end(), isspace), Val.end());
	
	if (Property::ParentType(type) == Types::BOOL) {
		if ((Val.compare("true") == 0) || (Val.compare("True") == 0) || (Val.compare("1") == 0))
		{
			ToVal = true;
			return true;
		}

		else if ((Val.compare("false") == 0) || (Val.compare("False") == 0) || (Val.compare("0") == 0))
		{
			ToVal = false;
			return true;
		}

		return false;
	}
	return false;
}

