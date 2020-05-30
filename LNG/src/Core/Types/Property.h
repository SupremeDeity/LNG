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

/* Base Class For properties. Holds Type, Name & Value*/
class Property {
public:
	virtual Types GetType() const = 0;
	virtual std::string GetName() const = 0;
	virtual void SetName(const std::string& name) = 0;
	virtual std::string ValuesToString() = 0;

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
	
};

class StringProperty : public Property {
public:
	StringProperty() : Value("") {};
	StringProperty(std::string val) :  Value(val) {};
	StringProperty(std::string name, std::string val) : Name(name), Value(val) {};

	void SetValue(std::string value) { Value = value; }

	std::string GetValue() { return Value; };

	// Inherited via Property
	virtual inline Types GetType() const override { return Types::STRING; };
	virtual inline std::string GetName() const override { return Name; };

	virtual inline void SetName(const std::string& name) override { Name = name; };
	virtual std::string ValuesToString() override;

private:
	std::string Name;
	std::string Value;
};

// Name, Type, Key, Value
class FloatProperty : public Property {
public:
	FloatProperty() : Value( 0.0f ) {};
	FloatProperty(float val) : Value(val) {};
	FloatProperty(std::string name, float val) : Name(name), Value(val) {};

	void SetValue(float value) { Value = value; }

	float GetValue() { return Value; };

	// Inherited via Property
	virtual inline Types GetType() const override { return Types::FLOAT; };
	virtual inline std::string GetName() const override { return Name; };
	
	virtual inline void SetName(const std::string& name) override { Name = name; };

	virtual std::string ValuesToString() override;

private:
	std::string Name;
	float Value;
};

class Float2Property : public Property {
public:
	Float2Property() : Value({ 0.0f, 0.0f }) {};
	Float2Property(Float2 val) : Value(val) {};
	Float2Property(std::string name, Float2 val) : Name(name), Value(val) {};

	void SetValue(Float2 value) { Value = value; }

	Float2 GetValue() { return Value; };

	// Inherited via Property
	virtual inline Types GetType() const override { return Types::FLOAT2; };
	virtual inline std::string GetName() const override { return Name; };
	
	virtual inline void SetName(const std::string& name) override { Name = name; };

	virtual std::string ValuesToString() override;

private:
	std::string Name;
	Float2 Value;
};

class Float3Property : public Property {
public:
	Float3Property() : Value({ 0.0f, 0.0f, 0.0f }) {};
	Float3Property(Float3 val) : Value(val) {};
	Float3Property(std::string name, Float3 val) : Name(name), Value(val) {};
	void SetValue(Float3 value) { Value = value; }

	Float3 GetValue() { return Value; };

	// Inherited via Property
	virtual inline Types GetType() const override { return Types::FLOAT3; };
	virtual inline std::string GetName() const override { return Name; };

	virtual inline void SetName(const std::string& name) override { Name = name; };

	virtual std::string ValuesToString() override;

private:
	std::string Name;
	Float3 Value;
};

class Float4Property : public Property {
public:
	Float4Property() : Value({0.0f, 0.0f, 0.0f, 0.0f}) {};
	Float4Property(Float4 val) : Value(val) {};
	Float4Property(std::string name, Float4 val) : Name(name), Value(val) {};
	void SetValue(Float4 value) { Value = value; }

	Float4 GetValue() { return Value; };

	// Inherited via Property
	virtual inline Types GetType() const override { return Types::FLOAT4; };
	virtual inline std::string GetName() const override { return Name; };
	
	virtual inline void SetName(const std::string& name) override { Name = name; };

	virtual std::string ValuesToString() override;

private:
	std::string Name;
	Float4 Value;
};

class IntProperty : public Property {
public:
	IntProperty() : Value(0) {};
	IntProperty(int val) : Value(val) {};
	IntProperty(std::string name, int val) : Name(name), Value(val) {};
	void SetValue(int value) { Value = value; }

	int GetValue() { return Value; };

	// Inherited via Property
	virtual inline Types GetType() const override { return Types::INT; };
	virtual inline std::string GetName() const override { return Name; };
	
	virtual inline void SetName(const std::string& name) override { Name = name; };

	virtual std::string ValuesToString() override;

private:
	std::string Name;
	int Value;
};

class Int2Property : public Property {
public:
	Int2Property() : Value({ 0, 0 }) {};
	Int2Property(Int2 val) : Value(val) {};
	Int2Property(std::string name, Int2 val) : Name(name), Value(val) {}

	void SetValue(Int2 value) { Value = value; }

	Int2 GetValue() { return Value; };

	// Inherited via Property
	virtual inline Types GetType() const override { return Types::INT2; };
	virtual inline std::string GetName() const override { return Name; };
	
	virtual inline void SetName(const std::string& name) override { Name = name; };

	virtual std::string ValuesToString() override;

private:
	std::string Name;
	Int2 Value;
};
class Int3Property : public Property {
public:
	Int3Property() : Value({ 0, 0, 0 }) {};
	Int3Property(Int3 val) : Value(val) {};
	Int3Property(std::string name, Int3 val) : Name(name), Value(val) {};

	void SetValue(Int3 value) { Value = value; }

	Int3 GetValue() { return Value; };

	// Inherited via Property
	virtual inline Types GetType() const override { return Types::INT3; };
	virtual inline std::string GetName() const override { return Name; };
	
	virtual inline void SetName(const std::string& name) override { Name = name; };

	virtual std::string ValuesToString() override;

private:
	std::string Name;
	Int3 Value;
};
class Int4Property : public Property {
public:
	Int4Property() : Value({ 0, 0, 0, 0 }) {};
	Int4Property(Int4 val) : Value(val) {};
	Int4Property(std::string name, Int4 val) : Name(name), Value(val) {};

	void SetValue(Int4 value) { Value = value; }

	Int4 GetValue() { return Value; };

	// Inherited via Property
	virtual inline Types GetType() const override { return Types::INT4; };
	virtual inline std::string GetName() const override { return Name; };
	
	virtual inline void SetName(const std::string& name) override { Name = name; };

	virtual std::string ValuesToString() override;

private:
	std::string Name;
	Int4 Value;
};

class BoolProperty : public Property {
public:
	BoolProperty() : Value( false ) {};
	BoolProperty(bool val) : Value(val) {};
	BoolProperty(std::string name, bool val) : Name(name), Value(val) {};
	
	void SetValue(bool value) { Value = value; }

	bool GetValue() { return Value; };

	// Inherited via Property
	virtual inline Types GetType() const override { return Types::BOOL; };
	virtual inline std::string GetName() const override { return Name; };
	
	virtual inline void SetName(const std::string& name) override { Name = name; };

	virtual std::string ValuesToString() override;

private:
	std::string Name;
	bool Value;
};

class Bool2Property : public Property {
public:
	Bool2Property() : Value({ false, false }) {};
	Bool2Property(Bool2 val) : Value(val) {};
	Bool2Property(std::string name, Bool2 val) : Name(name), Value(val) {};

	void SetValue(Bool2 value) { Value = value; }

	Bool2 GetValue() { return Value; };

	// Inherited via Property
	virtual inline Types GetType() const override { return Types::BOOL2; };
	virtual inline std::string GetName() const override { return Name; };

	virtual inline void SetName(const std::string& name) override { Name = name; };

	virtual std::string ValuesToString() override;

private:
	std::string Name;
	Bool2 Value;
};

class Bool3Property : public Property {
public:
	Bool3Property() : Value({ false, false, false }) {};
	Bool3Property(Bool3 val) : Value(val) {};
	Bool3Property(std::string name, Bool3 val) : Name(name), Value(val) {};

	void SetValue(Bool3 value) { Value = value; }

	Bool3 GetValue() { return Value; };

	// Inherited via Property
	virtual inline Types GetType() const override { return Types::BOOL3; };
	virtual inline std::string GetName() const override { return Name; };

	virtual inline void SetName(const std::string& name) override { Name = name; };

	virtual std::string ValuesToString() override;

private:
	std::string Name;
	Bool3 Value;
};

class Bool4Property : public Property {
public:
	Bool4Property() : Value({ false, false, false, false }) {};
	Bool4Property(Bool4 val) : Value(val) {};
	Bool4Property(std::string name, Bool4 val) : Name(name), Value(val) {};

	void SetValue(Bool4 value) { Value = value; }

	Bool4 GetValue() { return Value; };

	// Inherited via Property
	virtual inline Types GetType() const override { return Types::BOOL4; };
	virtual inline std::string GetName() const override { return Name; };

	virtual inline void SetName(const std::string& name) override { Name = name; };

	virtual std::string ValuesToString() override;
private:
	std::string Name;
	Bool4 Value;
};
