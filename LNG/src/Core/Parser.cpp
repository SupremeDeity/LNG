#include "lngpch.h"
#include "Parser.h"

Parser::Parser(const std::string & filepath)
	: m_FilePath(filepath)
{
	std::fstream stream(filepath, std::fstream::in);
	if (!stream.is_open()) { 
		std::cout << "FILE " << filepath << " NOT FOUND!! EXITING!." << std::endl;
		std::exit(-1);
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
	delete this;
}

void Parser::Parse()
{
	// Version Check
	CheckVersion();
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

//##########################
//####### PRIVATE ##########
//##########################

void Parser::CheckVersion()
{
	for (int line = 0; line < m_FileBuffer.size(); line++) {
		if (m_FileBuffer[line].find("@VERSION") != std::string::npos) {
			int startbracket = m_FileBuffer[line].find("{");
			int endbracket = m_FileBuffer[line].find("}");
			int dot = m_FileBuffer[line].find(".");

			if(startbracket == std::string::npos) {
				std::cout << "Line " << line + 1 << ": Expected '{'\n";
			}
			if(endbracket == std::string::npos) {
				std::cout << "Line " << line + 1 << ": Expected '}'\n";
			}
			if (dot == std::string::npos) {
				std::cout << "Line " << line + 1 << ": Expected '.'\n";
			}

			// Converting Char to int
			int reqMajor = m_FileBuffer[line].at(dot - 1) - '0';
			int reqMinor = m_FileBuffer[line].at(dot + 1) - '0';

			if (reqMajor > LNG_VERSION_MAJOR) {
				std::cout << "ERROR!: Current Parser Version is lower than the required minimum" << std::endl;
			}

			else if (reqMajor == LNG_VERSION_MAJOR) {
				if (reqMinor > LNG_VERSION_MINOR) {
					std::cout << "ERROR!: Current Parser Version is lower than the required minimum" << std::endl;
				}
			}

			break;
		}
	}
}

void Parser::Lex()
{
	std::string section = "";

	for (int line = 0; line < m_FileBuffer.size(); line++) {

		// Find A Section.
		if (m_FileBuffer[line].find("@SECTION") != std::string::npos) {

			// Section has ended
			if (m_FileBuffer[line].find("[END]") != std::string::npos) {
				if (section.empty()) { std::cout << "Line " << line + 1 << " : No Current Section!.\n"; return; }
				section = "";

				continue;
			}

			if (!section.empty()) {
				std::cout << "Line " << line + 1 << " : New section started before end of last section '" << section << "'. Did you forgot to call @SECTION [END]?\n";
				return;
			}

			// In Section...
			int fbracket = m_FileBuffer[line].find("(");
			int sbracket = m_FileBuffer[line].find(")");

			if (fbracket == std::string::npos) { std::cout << "Line " << line + 1 << ": '(' Expected!"; break; return; }
			if (sbracket == std::string::npos) { std::cout << "Line " << line + 1 << ": ')' Expected!"; break; return; }

			section = m_FileBuffer[line].substr(fbracket + 1, (sbracket - fbracket) - 1);

			continue;

		}

		else if(!section.empty() && !m_FileBuffer[line].empty()) {
			
			int fsbracket = m_FileBuffer[line].find("[");
			int ssbracket = m_FileBuffer[line].find("]");
			int fbracket = m_FileBuffer[line].find("(");
			int sbracket = m_FileBuffer[line].find(")");
			int fcbracket = m_FileBuffer[line].find("{");
			int scbracket = m_FileBuffer[line].find("}");

			if (fsbracket == std::string::npos) { std::cout << "Line " << line + 1 << ": '[' Expected!"; break; return; }
			if (ssbracket == std::string::npos) { std::cout << "Line " << line + 1 << "': ']' Expected!"; break; return; }

			if (fbracket == std::string::npos) { std::cout << "Line " << line + 1 << ": '(' Expected!"; break; return; }
			if (sbracket == std::string::npos) { std::cout << "Line " << line + 1 << ": ')' Expected!"; break; return; }

			if (fcbracket == std::string::npos) { std::cout << "Line " << line + 1 << ": '{' Expected!"; break; return; }
			if (scbracket == std::string::npos) { std::cout << "Line " << line + 1 << ": '}' Expected!"; break; return; }


			std::string typeStr = m_FileBuffer[line].substr(fsbracket + 1, (ssbracket - fsbracket) - 1);
			Types type = Property::StrToType(typeStr);

			std::string name = m_FileBuffer[line].substr(fbracket + 1, (sbracket - fbracket) - 1);

			Property* prop = nullptr;

			//////#######EXPERIMENTAL##########///////
			// First we split the string using the delim ','
			std::vector<std::string> out;
			std::string params = m_FileBuffer[line].substr(fcbracket + 1, (scbracket - fcbracket) - 1);
			params.erase(remove(params.begin(), params.end(), ' '), params.end());

			GetValueDelim(params, ',', out);
			
			prop = SetPropertyValues(type, out);
			//////#############################//////

			// This is common in all properties
			prop->SetName(name);
			

			// Experiment
			m_Properties.push_back({ section, prop });

			continue;
		}
	}
}

// TODO: SHORTEN THIS UP!
Property * Parser::SetPropertyValues(Types type, std::vector<std::string> vals)
{
	const int a = 2;
	if (type == Types::STRING) {
		return new StringProperty({ vals[0] });
	}

	else if (type == Types::STRING2) {
		return new String2Property({ vals[0] , vals[1] });
	}

	else if (type == Types::STRING3) {
		return new String3Property({ vals[0] , vals[1], vals[2] });
	}

	else if (type == Types::STRING4) {
		return new String4Property({ vals[0] , vals[1], vals[2], vals[3] });
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
}

void Parser::GetValueDelim(std::string const & str, const char delim, std::vector<std::string>& out)
{
	// construct a stream from the string
	std::stringstream ss(str);

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
}