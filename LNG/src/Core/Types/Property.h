#pragma once

#include <string>
#include "Vector.h"

// All types of properties
enum Types {
	NONE,
	STRING,
	FLOAT, FLOAT2, FLOAT3, FLOAT4,
	INT, INT2, INT3, INT4,
	BOOL, BOOL2, BOOL3, BOOL4
};

/* Base Class For properties. Holds Type, Property & Value */
class Property {
public:
	inline Property(std::string name) : m_Name(name) {}

	virtual Types GetType() const = 0;
	virtual std::string ValuesToString() = 0;

	std::string GetName() const { return m_Name; }
	void SetName(const std::string& name) { m_Name = name; }

	inline bool operator!=(const Property& p)
	{
		return this->GetType() != p.GetType();
	}

	inline bool operator==(const Property& p)
	{
		return this->GetType() == p.GetType();
	}

	static Types StrToType(const std::string& type);
	static Types ParentType(Types type);
	static std::string TypeToStr(Types type);
	static int ParamCountForProperty(Types type);

	static std::string BoolToStr(bool val) {
		if (val)
			return "True";
		else
			return "False";
	}

protected:
	std::string m_Name;

};

class StringProperty : public Property {
public:
	StringProperty() : Value(""), Property("") {};
	StringProperty(std::string val) : Value(val), Property("") {};
	StringProperty(std::string name, std::string val) : Property(name), Value(val) {};

	void SetValue(std::string value) { Value = value; }
	std::string GetValue() { return Value; };

	// Inherited via Property
	virtual inline Types GetType() const override { return Types::STRING; };

	virtual std::string ValuesToString() override;

private:
	std::string Value;
};

class FloatProperty : public Property {
public:
	FloatProperty() : Value(0.0f), Property("") {};
	FloatProperty(float val) : Value(val), Property("") {};
	FloatProperty(std::string name, float val) : Property(name), Value(val) {};

	void SetValue(float value) { Value = value; }
	float GetValue() { return Value; };

	// Inherited via Property
	virtual inline Types GetType() const override { return Types::FLOAT; };
	virtual std::string ValuesToString() override;

private:
	float Value;
};

class Float2Property : public Property {
public:
	Float2Property() : Value({ 0.0f, 0.0f }), Property("") {};
	Float2Property(Float2 val) : Value(val), Property("") {};
	Float2Property(std::string name, Float2 val) : Property(name), Value(val) {};

	void SetValue(Float2 value) { Value = value; }

	Float2 GetValue() { return Value; };

	// Inherited via Property
	virtual inline Types GetType() const override { return Types::FLOAT2; };
	virtual std::string ValuesToString() override;

private:
	Float2 Value;
};

class Float3Property : public Property {
public:
	Float3Property() : Value({ 0.0f, 0.0f, 0.0f }), Property("") {};
	Float3Property(Float3 val) : Value(val), Property("") {};
	Float3Property(std::string name, Float3 val) : Property(name), Value(val) {};

	void SetValue(Float3 value) { Value = value; }
	Float3 GetValue() { return Value; };

	// Inherited via Property
	virtual inline Types GetType() const override { return Types::FLOAT3; };
	virtual std::string ValuesToString() override;

private:
	Float3 Value;
};

class Float4Property : public Property {
public:
	Float4Property() : Value({ 0.0f, 0.0f, 0.0f, 0.0f }), Property("") {};
	Float4Property(Float4 val) : Value(val), Property("") {};
	Float4Property(std::string name, Float4 val) : Property(name), Value(val) {};

	void SetValue(Float4 value) { Value = value; }
	Float4 GetValue() { return Value; };

	// Inherited via Property
	virtual inline Types GetType() const override { return Types::FLOAT4; };
	virtual std::string ValuesToString() override;

private:
	Float4 Value;
};

class IntProperty : public Property {
public:
	IntProperty() : Value(0), Property("") {};
	IntProperty(int val) : Value(val), Property("") {};
	IntProperty(std::string name, int val) : Property(name), Value(val) {};
	
	void SetValue(int value) { Value = value; }
	int GetValue() { return Value; };

	// Inherited via Property
	virtual inline Types GetType() const override { return Types::INT; };
	virtual std::string ValuesToString() override;

private:
	int Value;
};

class Int2Property : public Property {
public:
	Int2Property() : Value({ 0, 0 }), Property("") {};
	Int2Property(Int2 val) : Value(val), Property("") {};
	Int2Property(std::string name, Int2 val) : Property(name), Value(val) {}

	void SetValue(Int2 value) { Value = value; }
	Int2 GetValue() { return Value; };

	// Inherited via Property
	virtual inline Types GetType() const override { return Types::INT2; };
	virtual std::string ValuesToString() override;

private:
	Int2 Value;
};
class Int3Property : public Property {
public:
	Int3Property() : Value({ 0, 0, 0 }), Property("") {};
	Int3Property(Int3 val) : Value(val), Property("") {};
	Int3Property(std::string name, Int3 val) : Property(name), Value(val) {};

	void SetValue(Int3 value) { Value = value; }
	Int3 GetValue() { return Value; };

	// Inherited via Property
	virtual inline Types GetType() const override { return Types::INT3; };
	virtual std::string ValuesToString() override;

private:
	Int3 Value;
};
class Int4Property : public Property {
public:
	Int4Property() : Value({ 0, 0, 0, 0 }), Property("") {};
	Int4Property(Int4 val) : Value(val), Property("") {};
	Int4Property(std::string name, Int4 val) : Property(name), Value(val) {};

	void SetValue(Int4 value) { Value = value; }
	Int4 GetValue() { return Value; };

	// Inherited via Property
	virtual inline Types GetType() const override { return Types::INT4; };
	virtual std::string ValuesToString() override;

private:
	Int4 Value;
};

class BoolProperty : public Property {
public:
	BoolProperty() : Value(false), Property("") {};
	BoolProperty(bool val) : Value(val), Property("") {};
	BoolProperty(std::string name, bool val) : Property(name), Value(val) {};

	void SetValue(bool value) { Value = value; }
	bool GetValue() { return Value; };

	// Inherited via Property
	virtual inline Types GetType() const override { return Types::BOOL; };
	virtual std::string ValuesToString() override;

private:
	bool Value;
};

class Bool2Property : public Property {
public:
	Bool2Property() : Value({ false, false }), Property("") {};
	Bool2Property(Bool2 val) : Value(val), Property("") {};
	Bool2Property(std::string name, Bool2 val) : Property(name), Value(val) {};

	void SetValue(Bool2 value) { Value = value; }
	Bool2 GetValue() { return Value; };

	// Inherited via Property
	virtual inline Types GetType() const override { return Types::BOOL2; };
	virtual std::string ValuesToString() override;

private:
	Bool2 Value;
};

class Bool3Property : public Property {
public:
	Bool3Property() : Value({ false, false, false }), Property("") {};
	Bool3Property(Bool3 val) : Value(val), Property("") {};
	Bool3Property(std::string name, Bool3 val) : Property(name), Value(val) {};

	void SetValue(Bool3 value) { Value = value; }
	Bool3 GetValue() { return Value; };

	// Inherited via Property
	virtual inline Types GetType() const override { return Types::BOOL3; };
	virtual std::string ValuesToString() override;

private:
	Bool3 Value;
};

class Bool4Property : public Property {
public:
	Bool4Property() : Value({ false, false, false, false }), Property("") {};
	Bool4Property(Bool4 val) : Value(val), Property("") {};
	Bool4Property(std::string name, Bool4 val) :
		Property(name), Value(val) {};

	void SetValue(Bool4 value) { Value = value; }
	Bool4 GetValue() { return Value; };

	// Inherited via Property
	virtual inline Types GetType() const override { return Types::BOOL4; };
	virtual std::string ValuesToString() override;
private:
	Bool4 Value;
};

