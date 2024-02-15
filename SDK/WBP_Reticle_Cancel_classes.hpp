#pragma once

// Dumped with Dumper-7!


namespace SDK
{
//---------------------------------------------------------------------------------------------------------------------
// CLASSES
//---------------------------------------------------------------------------------------------------------------------

// 0x19 (0x299 - 0x280)
// WidgetBlueprintGeneratedClass WBP_Reticle_Cancel.WBP_Reticle_Cancel_C
class UWBP_Reticle_Cancel_C : public UUserWidget
{
public:
	struct FPointerToUberGraphFrame              UberGraphFrame;                                    // 0x280(0x8)(ZeroConstructor, Transient, DuplicateTransient)
	class UBP_PalTextBlock_C*                    Text_Cancel;                                       // 0x288(0x8)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UWBP_PlayerInputKeyGuideIcon_C*        WBP_PlayerInputKeyGuideIcon;                       // 0x290(0x8)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	bool                                         CurrentIsCancel;                                   // 0x298(0x1)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)

	static class UClass* StaticClass();
	static class UWBP_Reticle_Cancel_C* GetDefaultObj();

	void SetKeyGuideInfo(enum class Enum_ReticleCancel_DisplayType DisplayType);
	void ExecuteUbergraph_WBP_Reticle_Cancel(int32 EntryPoint, class FName CallFunc_MakeLiteralName_ReturnValue, enum class Enum_ReticleCancel_DisplayType Temp_byte_Variable, class FName Temp_name_Variable, class FName Temp_name_Variable_1, class FName Temp_name_Variable_2, class FName Temp_name_Variable_3, enum class Enum_ReticleCancel_DisplayType Temp_byte_Variable_1, enum class Enum_ReticleCancel_DisplayType K2Node_CustomEvent_DisplayType, class FName K2Node_Select_Default, class FName CallFunc_MakeLiteralName_ReturnValue_1, class FText CallFunc_GetLocalizedText_ReturnValue, class FName CallFunc_MakeLiteralName_ReturnValue_2, class FName K2Node_Select_Default_1);
};

}


