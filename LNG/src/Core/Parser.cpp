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
	std::cout << "\nFinished Parsing. Errors: " << errors << ", Warnings: " << warnings << std::endl;
}

void Parser::Parse()
{
	Lex();
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

void Parser::Add(std::string section, Property * prop)
{
	for (auto property : m_Properties) {
		if (property.first == section) {
			if (property.second->GetName() == prop->GetName()) {
				std::cout << "Warning: A Property named '" + prop->GetName() + "' already exists. Ignoring\n";
				warnings++;
				return;
			}
		}
	}

	m_Properties.push_back({ section, prop });
}

void Parser::Flush()
{
	if (errors > 0) { std::cout << "Error: Could not write to file due to errors found while parsing.\n"; }

	// Really Important to sort because of the method being used.
	std::sort(m_Properties.begin(), m_Properties.end());

	// Create Section
	std::vector<std::string> file;
	std::string currentSection = "";

	for (int x = 0; x < m_Properties.size(); x++) {
		// Set the section
		if (currentSection.empty()) {
			currentSection = m_Properties[x].first;
			file.push_back("\n@SECTION (" + currentSection + ")");
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
		} else {
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
				if (section.empty()) { std::cout << "Error: Line " << line + 1 << " : No Current Section!.\n"; errors++; return; }
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

			if (sbracket == std::string::npos) { std::cout << "Error: Line " << line + 1 << ": ')' Expected!"; errors++;  return; }
			if (fbracket == std::string::npos) { std::cout << "Error: Line " << line + 1 << ": '(' Expected!"; errors++; return; }

			section = m_FileBuffer[line].substr((int64_t)fbracket + 1, ((int64_t)sbracket - (int64_t)fbracket) - 1);

			continue;

		}

		else if(!section.empty() && !m_FileBuffer[line].empty()) {
			
			size_t fsbracket = m_FileBuffer[line].find("[");
			size_t ssbracket = m_FileBuffer[line].find("]");
			size_t fbracket = m_FileBuffer[line].find("(");
			size_t sbracket = m_FileBuffer[line].find(")");
			size_t fcbracket = m_FileBuffer[line].find("{");
			size_t scbracket = m_FileBuffer[line].find("}");
			size_t fquote = m_FileBuffer[line].find("\"");
			size_t squote = m_FileBuffer[line].find("\"", fquote + 1);

			std::string colonSpace = m_FileBuffer[line].substr(sbracket, ((int64_t)sbracket - (int64_t)fcbracket) - 1);
			size_t colon = colonSpace.find(":");

			if (fsbracket == std::string::npos) { std::cout << "Error: Line " << line + 1 << ": '[' Expected!\n"; errors++; return; }
			if (ssbracket == std::string::npos) { std::cout << "Error: Line " << line + 1 << "': ']' Expected!\n"; errors++; return; }

			if (fbracket == std::string::npos) { std::cout << "Error: Line " << line + 1 << ": '(' Expected!\n"; errors++; return; }
			if (sbracket == std::string::npos) { std::cout << "Error: Line " << line + 1 << ": ')' Expected!\n"; errors++; return; }

			if (fcbracket == std::string::npos) { std::cout << "Error: Line " << line + 1 << ": '{' Expected!\n"; errors++; return; }
			if (scbracket == std::string::npos) { std::cout << "Error: Line " << line + 1 << ": '}' Expected!\n"; errors++; return; }

			if (colon == std::string::npos) { std::cout << "Error: Line " << line + 1 << ": ':' Expected!\n"; errors++; return; }


			std::string typeStr = m_FileBuffer[line].substr((int64_t)fsbracket + 1, ((int64_t)ssbracket - (int64_t)fsbracket) - 1);
			Types type = Property::StrToType(typeStr);
			
			if (type == Types::STRING) {
				if (fquote == std::string::npos) { std::cout << "Error: Line " << line + 1 << ": '\"' Expected!\n"; errors++; return; }
				if (squote == std::string::npos) { std::cout << "Error: Line " << line + 1 << ": '\"' Expected!\n"; errors++; return; }
			}
			else {
				if (fquote != std::string::npos || squote != std::string::npos) {
					std::cout << "Error: Line " << line + 1 << ": Expected Type to be 'String', got " << Property::TypeToStr(type) << " instead\n";
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

			params.erase(remove(params.begin(), params.end(), ' '), params.end());

			GetValueDelim(params, ',', out);
			
			prop = SetPropertyValues(type, out);

			// This is common in all properties
			prop->SetName(name);

			m_Properties.push_back({ section, prop });

			continue;
		}
	}
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
			float Converted;
			ConvertFloat(type, toConvert, Converted);
			arr.push_back(Converted);
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
			int Converted;
			ConvertInt(type, toConvert, Converted);
			arr.push_back(Converted);
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

void Parser::GetValueDelim(std::string const & str, const char delim, std::vector<std::string>& out)
{
	// construct a stream from the string
	std::stringstream ss(str);
	
	// Split the string using the given delim
	std::string s;
	while (std::getline(ss, s, delim)) {
		out.push_back(s);
	}
}

bool Parser::ConvertFloat(Types type, std::string Val, float & ToVal)
{
	if (Property::ParentType(type) == Types::FLOAT) {
		char* endptr;
		float i = std::strtof(Val.c_str(), &endptr);
		if ((Val == endptr) || (i == ERANGE))
		{
			return false;
		}
		else
		{
			ToVal = i;
			return true;
		}
		return false;
	}
	return false;
}

bool Parser::ConvertInt(Types type, std::string Val, int & ToVal)
{
	if (Property::ParentType(type) == Types::INT) {
		char* endptr;
		int i = std::strtol(Val.c_str(), &endptr, 0);
		if ((Val == endptr) || (i == ERANGE))
		{
			return false;
		}
		else
		{
			ToVal = i;
			return true;
		}
		return false;
	}
	else return false;

}

bool Parser::ConvertBool(Types type, std::string Val, bool & ToVal)
{
	if (Property::ParentType(type) == Types::BOOL) {
		if (Val.compare("true") == 0 || Val.compare("True") == 0 || Val.compare("1") == 0)
		{
			ToVal = true;
			return true;
		}

		else if (Val.compare("false") == 0 || Val.compare("False") == 0 || Val.compare("0") == 0)
		{
			ToVal = false;
			return true;
		}

		return false;
	}
	return false;
}