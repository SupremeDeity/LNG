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
