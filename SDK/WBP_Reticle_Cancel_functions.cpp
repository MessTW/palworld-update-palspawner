#pragma once

// Dumped with Dumper-7!


#include "../SDK.hpp"

namespace SDK
{
//---------------------------------------------------------------------------------------------------------------------
// FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------


// WidgetBlueprintGeneratedClass WBP_Reticle_Cancel.WBP_Reticle_Cancel_C
// (None)

class UClass* UWBP_Reticle_Cancel_C::StaticClass()
{
	static class UClass* Clss = nullptr;

	if (!Clss)
		Clss = UObject::FindClassFast("WBP_Reticle_Cancel_C");

	return Clss;
}


// WBP_Reticle_Cancel_C WBP_Reticle_Cancel.Default__WBP_Reticle_Cancel_C
// (Public, ClassDefaultObject, ArchetypeObject, WasLoaded, LoadCompleted)

class UWBP_Reticle_Cancel_C* UWBP_Reticle_Cancel_C::GetDefaultObj()
{
	static class UWBP_Reticle_Cancel_C* Default = nullptr;

	if (!Default)
		Default = static_cast<UWBP_Reticle_Cancel_C*>(UWBP_Reticle_Cancel_C::StaticClass()->DefaultObject);

	return Default;
}


// Function WBP_Reticle_Cancel.WBP_Reticle_Cancel_C.SetKeyGuideInfo
// (BlueprintCallable, BlueprintEvent)
// Parameters:
// enum class Enum_ReticleCancel_DisplayTypeDisplayType                                                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

void UWBP_Reticle_Cancel_C::SetKeyGuideInfo(enum class Enum_ReticleCancel_DisplayType DisplayType)
{
	static class UFunction* Func = nullptr;

	if (!Func)
		Func = Class->GetFunction("WBP_Reticle_Cancel_C", "SetKeyGuideInfo");

	Params::UWBP_Reticle_Cancel_C_SetKeyGuideInfo_Params Parms{};

	Parms.DisplayType = DisplayType;

	UObject::ProcessEvent(Func, &Parms);

}


// Function WBP_Reticle_Cancel.WBP_Reticle_Cancel_C.ExecuteUbergraph_WBP_Reticle_Cancel
// (Final, UbergraphFunction, HasDefaults)
// Parameters:
// int32                              EntryPoint                                                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
// class FName                        CallFunc_MakeLiteralName_ReturnValue                             (ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
// enum class Enum_ReticleCancel_DisplayTypeTemp_byte_Variable                                               (ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
// class FName                        Temp_name_Variable                                               (ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
// class FName                        Temp_name_Variable_1                                             (ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
// class FName                        Temp_name_Variable_2                                             (ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
// class FName                        Temp_name_Variable_3                                             (ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
// enum class Enum_ReticleCancel_DisplayTypeTemp_byte_Variable_1                                             (ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
// enum class Enum_ReticleCancel_DisplayTypeK2Node_CustomEvent_DisplayType                                   (ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
// class FName                        K2Node_Select_Default                                            (ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
// class FName                        CallFunc_MakeLiteralName_ReturnValue_1                           (ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
// class FText                        CallFunc_GetLocalizedText_ReturnValue                            (None)
// class FName                        CallFunc_MakeLiteralName_ReturnValue_2                           (ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
// class FName                        K2Node_Select_Default_1                                          (ConstParm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

void UWBP_Reticle_Cancel_C::ExecuteUbergraph_WBP_Reticle_Cancel(int32 EntryPoint, class FName CallFunc_MakeLiteralName_ReturnValue, enum class Enum_ReticleCancel_DisplayType Temp_byte_Variable, class FName Temp_name_Variable, class FName Temp_name_Variable_1, class FName Temp_name_Variable_2, class FName Temp_name_Variable_3, enum class Enum_ReticleCancel_DisplayType Temp_byte_Variable_1, enum class Enum_ReticleCancel_DisplayType K2Node_CustomEvent_DisplayType, class FName K2Node_Select_Default, class FName CallFunc_MakeLiteralName_ReturnValue_1, class FText CallFunc_GetLocalizedText_ReturnValue, class FName CallFunc_MakeLiteralName_ReturnValue_2, class FName K2Node_Select_Default_1)
{
	static class UFunction* Func = nullptr;

	if (!Func)
		Func = Class->GetFunction("WBP_Reticle_Cancel_C", "ExecuteUbergraph_WBP_Reticle_Cancel");

	Params::UWBP_Reticle_Cancel_C_ExecuteUbergraph_WBP_Reticle_Cancel_Params Parms{};

	Parms.EntryPoint = EntryPoint;
	Parms.CallFunc_MakeLiteralName_ReturnValue = CallFunc_MakeLiteralName_ReturnValue;
	Parms.Temp_byte_Variable = Temp_byte_Variable;
	Parms.Temp_name_Variable = Temp_name_Variable;
	Parms.Temp_name_Variable_1 = Temp_name_Variable_1;
	Parms.Temp_name_Variable_2 = Temp_name_Variable_2;
	Parms.Temp_name_Variable_3 = Temp_name_Variable_3;
	Parms.Temp_byte_Variable_1 = Temp_byte_Variable_1;
	Parms.K2Node_CustomEvent_DisplayType = K2Node_CustomEvent_DisplayType;
	Parms.K2Node_Select_Default = K2Node_Select_Default;
	Parms.CallFunc_MakeLiteralName_ReturnValue_1 = CallFunc_MakeLiteralName_ReturnValue_1;
	Parms.CallFunc_GetLocalizedText_ReturnValue = CallFunc_GetLocalizedText_ReturnValue;
	Parms.CallFunc_MakeLiteralName_ReturnValue_2 = CallFunc_MakeLiteralName_ReturnValue_2;
	Parms.K2Node_Select_Default_1 = K2Node_Select_Default_1;

	UObject::ProcessEvent(Func, &Parms);

}

}


