#include "lngpch.h"
#include "Property.h"

Types Property::StrToType(const std::string & type)
{
	if (type == "String")	{ return Types::STRING; };
	if (type == "String2")	{ return Types::STRING2; };
	if (type == "String3")	{ return Types::STRING3; };
	if (type == "String4")	{ return Types::STRING4; };
	if (type == "Float")	{ return Types::FLOAT; };
	if (type == "Float2")	{ return Types::FLOAT2; };
	if (type == "Float3")	{ return Types::FLOAT3; };
	if (type == "Float4")	{ return Types::FLOAT4; };
	if (type == "Int")		{ return Types::INT; };
	if (type == "Int2")		{ return Types::INT2; };
	if (type == "Int3")		{ return Types::INT3; };
	if (type == "Int4")		{ return Types::INT4; };
	if (type == "Bool")		{ return Types::BOOL; };
	if (type == "Bool2")	{ return Types::BOOL2; };
	if (type == "Bool3")	{ return Types::BOOL3; };
	if (type == "Bool4")	{ return Types::BOOL4; };
}

std::string Property::TypeToStr(Types type)
{
	switch (type)
	{
	case NONE:
		return "NONE";
	case STRING:
		return "String";
	case STRING2:
		return "String2";
	case STRING3:
		return "String3";
	case STRING4:
		return "String4";
	case FLOAT:
		return "Float";
	case FLOAT2:
		return "Float2";
	case FLOAT3:
		return "Float3";
	case FLOAT4:
		return "Float4";
	case INT:
		return "Int";
	case INT2:
		return "Int2";
	case INT3:
		return "Int3";
	case INT4:
		return "Int4";
	case BOOL:
		return "Bool";
	case BOOL2:
		return "Bool2";
	case BOOL3:
		return "Bool3";
	case BOOL4:
		return "Bool4";
	default:
		return "NONE";
	}
	
}

Types Property::ParentType(Types type)
{
	switch (type)
	{
	case NONE:
		break;
	case STRING:
		return Types::STRING;
	case STRING2:
		return Types::STRING;
	case STRING3:
		return Types::STRING;
	case STRING4:
		return Types::STRING;
	case FLOAT:
		return Types::FLOAT;
	case FLOAT2:
		return Types::FLOAT;
	case FLOAT3:
		return Types::FLOAT;
	case FLOAT4:
		return Types::FLOAT;
	case INT:
		return Types::INT;
	case INT2:
		return Types::INT;
	case INT3:
		return Types::INT;
	case INT4:
		return Types::INT;
	case BOOL:
		return Types::BOOL;
	case BOOL2:
		return Types::BOOL;
	case BOOL3:
		return Types::BOOL;
	case BOOL4:
		return Types::BOOL;
	default:
		break;
	}
}

std::string StringProperty::ValuesToString()
{
	std::string Val = Value;
	return Val;
}

std::string String2Property::ValuesToString()
{
	std::string Val = Value.x + ", " + Value.y;
	return Val;
}

std::string String3Property::ValuesToString()
{
	std::string Val = Value.x + ", " + Value.y + ", " + Value.z;
	return Val;
}

std::string String4Property::ValuesToString()
{
	std::string Val = Value.x + ", " + Value.y + ", " + Value.z + ", " + Value.w;
	return Val;
}


std::string BoolProperty::ValuesToString()
{
	return Value ? "True" : "False";
}

std::string Bool2Property::ValuesToString()
{
	std::string Val = std::to_string(Value.x) + ", " + std::to_string(Value.y);
	return Val;
}

std::string Bool3Property::ValuesToString()
{
	std::string Val = std::to_string(Value.x) + ", " + std::to_string(Value.y) + ", " + std::to_string(Value.z);
	return Val;
}


std::string Bool4Property::ValuesToString()
{
	std::string Val = std::to_string(Value.x) + ", " + std::to_string(Value.y) + ", " + std::to_string(Value.z) + ", " + std::to_string(Value.w);
	return Val;
}

std::string IntProperty::ValuesToString()
{
	std::string Val = std::to_string(Value);
	return Val;
}

std::string Int2Property::ValuesToString()
{
	std::string Val = std::to_string(Value.x) + ", " + std::to_string(Value.y);
	return Val;
}

std::string Int3Property::ValuesToString()
{
	std::string Val = std::to_string(Value.x) + ", " + std::to_string(Value.y) + ", " + std::to_string(Value.z);
	return Val;
}


std::string Int4Property::ValuesToString()
{
	std::string Val = std::to_string(Value.x) + ", " + std::to_string(Value.y) + ", " + std::to_string(Value.z) + ", " + std::to_string(Value.w);
	return Val;
}

std::string FloatProperty::ValuesToString()
{
	std::string Val = std::to_string(Value);
	return Val;
}

std::string Float2Property::ValuesToString()
{
	std::string Val = std::to_string(Value.x) + ", " + std::to_string(Value.y) ;
	return Val;
}

std::string Float3Property::ValuesToString()
{
	std::string Val = std::to_string(Value.x) + ", " + std::to_string(Value.y) + ", " + std::to_string(Value.z);
	return Val;
}

std::string Float4Property::ValuesToString()
{
	std::string Val = std::to_string(Value.x) + ", " + std::to_string(Value.y) + ", " + std::to_string(Value.z) + ", " + std::to_string(Value.w);
	return Val;
}
