#pragma once
#include "lng.h"
#include "Types/Property.h"
#include <string>

class Parser {

public:
	// Parse From File
	Parser(const std::string& filepath);
	// Parse from provided string vector. Each line needs to be in a separate index.
	Parser(const std::vector<std::string>& src);
	~Parser();

	void Parse();
	std::pair<std::string, Property*> GetProperty(const std::string section, const std::string key);
	inline std::pair<std::string, Property*>* GetProperties() { return m_Properties.data(); };

private:
	std::string m_FilePath;
	std::vector<std::string> m_FileBuffer;

	// Section Name, Property -> Name, Type, Value
	std::vector<std::pair<std::string, Property*>> m_Properties;

private:
	void CheckVersion();
	void Lex();

	bool ConvertFloat(Types type, std::string Val, float &ToVal);
	bool ConvertInt(Types type, std::string Val, int &ToVal);
	bool ConvertBool(Types type, std::string Val, bool &ToVal);
	Property* SetPropertyValues(Types type, std::vector<std::string> vals);

	void GetValueDelim(std::string const &str, const char delim, std::vector<std::string> &out);

};
