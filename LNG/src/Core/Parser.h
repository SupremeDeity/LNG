#pragma once
#include "lng.h"
#include "Types/Property.h"
#include <string>

enum AssertType {
	None,
	ERROR,
	WARNING
};

class Parser {

public:
	/*
		Create Parser instance from file.
	*/
	Parser(const std::string& filepath);
	/*
		Create Parser instance from string.
		Each line should be on a separate index.
	*/
	Parser(const std::vector<std::string>& src);
	~Parser();

	/*
		Checks for errors and warnings in the file. Populates Buffer with variables.
	*/
	void Parse();
	std::pair<std::string, Property*> GetProperty(const std::string section, const std::string key);
	inline std::vector<std::pair<std::string, Property*>>* GetProperties() { return &m_Properties; };

	// Add a new property to given section. Creates section if it does not exist.
	void Add(std::string section, Property* prop);

	// Write changes to file.
	void Flush();

private:
	std::string m_FilePath;
	std::vector<std::string> m_FileBuffer;

	// <Section Name, Property>
	std::vector<std::pair<std::string, Property*>> m_Properties;

	int MajorVersion = LNG_VERSION_MAJOR;
	int MinorVersion = LNG_VERSION_MINOR;

	int errors = 0;
	int warnings = 0;

private:
	void Lex();
	bool Assert(bool condition, std::string toThrow, AssertType type);

	bool ConvertFloat(Types type, std::string Val, float &ToVal);
	bool ConvertInt(Types type, std::string Val, int &ToVal);
	bool ConvertBool(Types type, std::string Val, bool &ToVal);
	Property* SetPropertyValues(Types type, std::vector<std::string> vals);

	void GetValueDelim(std::string const &str, const char delim, std::vector<std::string> &out);

};