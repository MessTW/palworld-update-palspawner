#pragma once

// Dumped with Dumper-7!


namespace SDK
{
//---------------------------------------------------------------------------------------------------------------------
// CLASSES
//---------------------------------------------------------------------------------------------------------------------

// 0x0 (0x28 - 0x28)
// BlueprintGeneratedClass BP_PalRichTextDecorator_UICommon.BP_PalRichTextDecorator_UICommon_C
class UBP_PalRichTextDecorator_UICommon_C : public UPalRichTextDecorator_TagText
{
public:

	static class UClass* StaticClass();
	static class UBP_PalRichTextDecorator_UICommon_C* GetDefaultObj();

	class FString GetTextStringInternal(class UObject* WorldContextObject, class FName ID, class FText CallFunc_GetLocalizedText_ReturnValue, const class FString& CallFunc_Conv_TextToString_ReturnValue);
	class FString GetTagName();
};

}


