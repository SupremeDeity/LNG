#include "lngpch.h"
#include "Property.h"

Types Property::StrToType(const std::string & type)
{
	if (type == "String") { return Types::STRING; }
	else if (type == "Float") { return Types::FLOAT; }
	else if (type == "Float2") { return Types::FLOAT2; }
	else if (type == "Float3") { return Types::FLOAT3; }
	else if (type == "Float4") { return Types::FLOAT4; }
	else if (type == "Int") { return Types::INT; }
	else if (type == "Int2") { return Types::INT2; }
	else if (type == "Int3") { return Types::INT3; }
	else if (type == "Int4") { return Types::INT4; }
	else if (type == "Bool") { return Types::BOOL; }
	else if (type == "Bool2") { return Types::BOOL2; }
	else if (type == "Bool3") { return Types::BOOL3; }
	else if (type == "Bool4") { return Types::BOOL4; }
	else { return Types::NONE; }
}

std::string Property::TypeToStr(Types type)
{
	switch (type)
	{
	case STRING:
		return "String";
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

int Property::ParamCountForProperty(Types type)
{
	switch (type)
	{
	case Types::NONE:
		return 0;
	case Types::STRING:
		return 1;
	case Types::FLOAT:
		return 1;
	case Types::FLOAT2:
		return 2;
	case Types::FLOAT3:
		return 3;
	case Types::FLOAT4:
		return 4;
	case Types::INT:
		return 1;
	case Types::INT2:
		return 2;
	case Types::INT3:
		return 3;
	case Types::INT4:
		return 4;
	case Types::BOOL:
		return 1;
	case Types::BOOL2:
		return 2;
	case Types::BOOL3:
		return 3;
	case Types::BOOL4:
		return 4;
	default:
		return 0;
	}
}

Types Property::ParentType(Types type)
{
	switch (type)
	{
	case STRING:
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
		return Types::NONE;
	}
}

std::string StringProperty::ValuesToString()
{
	return Value;
}

std::string BoolProperty::ValuesToString()
{
	return BoolToStr(Value);
}

std::string Bool2Property::ValuesToString()
{
	std::string Val = BoolToStr(Value.x) + ", " + BoolToStr(Value.y);
	return Val;
}

std::string Bool3Property::ValuesToString()
{
	std::string Val = BoolToStr(Value.x) + ", " + BoolToStr(Value.y) + ", " + BoolToStr(Value.z);
	return Val;
}

std::string Bool4Property::ValuesToString()
{
	std::string Val = BoolToStr(Value.x) + ", " + BoolToStr(Value.y) + ", " + BoolToStr(Value.z) + ", " + BoolToStr(Value.w);
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
	std::string Val = std::to_string(Value.x) + ", " + std::to_string(Value.y);
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
