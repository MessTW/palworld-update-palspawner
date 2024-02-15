#pragma once

// Dumped with Dumper-7!


namespace SDK
{
//---------------------------------------------------------------------------------------------------------------------
// CLASSES
//---------------------------------------------------------------------------------------------------------------------

// 0x48 (0x478 - 0x430)
// WidgetBlueprintGeneratedClass WBP_PalAim.WBP_PalAim_C
class UWBP_PalAim_C : public UPalUIAimReticleBase
{
public:
	struct FPointerToUberGraphFrame              UberGraphFrame;                                    // 0x430(0x8)(ZeroConstructor, Transient, DuplicateTransient)
	class UCanvasPanel*                          AimCanvas;                                         // 0x438(0x8)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UImage*                                Image_101;                                         // 0x440(0x8)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UWBP_Reticle_Cancel_C*                 WBP_Reticle_Cancel;                                // 0x448(0x8)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	class UWBP_Reticle_Pal_C*                    WBP_Reticle_Pal;                                   // 0x450(0x8)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, RepSkip, NoDestructor, PersistentInstance, HasGetValueTypeHash)
	double                                       TargetScale;                                       // 0x458(0x8)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	double                                       NowScale;                                          // 0x460(0x8)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	bool                                         IsThrowPalMode;                                    // 0x468(0x1)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	uint8                                        Pad_4435[0x7];                                     // Fixing Size After Last Property  [ Dumper-7 ]
	class APalCharacter*                         CurrentCampLiftingPal;                             // 0x470(0x8)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, NoDestructor, HasGetValueTypeHash)

	static class UClass* StaticClass();
	static class UWBP_PalAim_C* GetDefaultObj();

	void OnEndLiftCampPal(bool CallFunc_IsValid_ReturnValue);
	void OnLiftCampPal(class APalCharacter* TargetCharacter, bool CallFunc_IsValid_ReturnValue);
	void On_Dead_Detail(class UPalOtomoHolderComponentBase* CallFunc_GetOtomoHolderComponent_ReturnValue, class UPalIndividualCharacterParameter* CallFunc_GetIndividualCharacterParameterByActor_ReturnValue, int32 CallFunc_GetSelectedOtomoID_ReturnValue, bool CallFunc_IsValid_ReturnValue, class UPalIndividualCharacterHandle* CallFunc_GetOtomoIndividualHandle_ReturnValue, class UPalIndividualCharacterParameter* CallFunc_TryGetIndividualParameter_ReturnValue, bool CallFunc_IsValid_ReturnValue_1);
	void DisplayOutlineTarget(struct FHitResult& HitResult);
	void Raycast_Reticle_Direction_Body(const struct FHitResult& ReticleHitResult, const struct FHitResult& CallFunc_Get_Reticle_Hit_Result_hitResult);
	void EndThrowPalMode(bool CallFunc_IsValid_ReturnValue);
	void StartThrowPalMode(bool Temp_bool_Variable, enum class ESlateVisibility Temp_byte_Variable, enum class ESlateVisibility Temp_byte_Variable_1, class UPalOtomoHolderComponentBase* CallFunc_GetOtomoHolderComponent_ReturnValue, bool CallFunc_IsValid_ReturnValue, bool CallFunc_IsValid_ReturnValue_1, bool CallFunc_IsALLEmpty_ReturnValue, enum class ESlateVisibility K2Node_Select_Default, bool CallFunc_BooleanOR_ReturnValue);
	void Get_Reticle_Hit_Result(struct FHitResult* HitResult, const TArray<class AActor*>& IgnoreActors, class APlayerController* CallFunc_GetLocalPlayerController_ReturnValue, bool CallFunc_IsValid_ReturnValue, const struct FRotator& CallFunc_GetCameraRotation_ReturnValue, const struct FVector& CallFunc_GetCameraLocation_ReturnValue, const struct FVector& CallFunc_GetForwardVector_ReturnValue, int32 CallFunc_Array_Add_ReturnValue, const struct FVector& CallFunc_Multiply_VectorFloat_ReturnValue, class APalPlayerCharacter* CallFunc_GetPalmi_ReturnValue, const struct FVector& CallFunc_Add_VectorVector_ReturnValue, TArray<class AActor*>& K2Node_MakeArray_Array, const struct FHitResult& CallFunc_LineTraceSingle_OutHit, bool CallFunc_LineTraceSingle_ReturnValue);
	void GetNowSelectedOtomoParameter(class UPalCharacterParameterComponent** Parameter, class UPalOtomoHolderComponentBase* CallFunc_GetOtomoHolderComponent_ReturnValue, bool CallFunc_IsValid_ReturnValue, int32 CallFunc_GetSelectedOtomoID_ReturnValue, class UPalIndividualCharacterHandle* CallFunc_GetOtomoIndividualHandle_ReturnValue, class APalCharacter* CallFunc_TryGetIndividualActor_ReturnValue, bool CallFunc_IsValid_ReturnValue_1, bool CallFunc_IsValid_ReturnValue_2, class UPalCharacterParameterComponent* CallFunc_GetCharacterParameterComponent_ReturnValue, bool CallFunc_IsValid_ReturnValue_3);
	void Show_Assignable_Throwing_Pal(struct FHitResult& HitResult, bool ShowPalReticle, const struct FPalUIAimReticleMapObjectAssignableData& TempAssignableData, bool CallFunc_IsValid_ReturnValue, const struct FPalUIAimReticleMapObjectAssignableData& CallFunc_IsAssignableToHitResult_outAssignableData, bool CallFunc_EqualEqual_NameName_ReturnValue, class UPalCharacterParameterComponent* CallFunc_GetNowSelectedOtomoParameter_parameter, bool CallFunc_IsValid_ReturnValue_1, const struct FPalUIAimReticleMapObjectAssignableData& CallFunc_IsAssignableToHitResult_outAssignableData_1, bool CallFunc_EqualEqual_NameName_ReturnValue_1);
	void OnChangedWeaon(class APalWeaponBase* Weapon, class ABP_ThrowPalWeapon_C* K2Node_DynamicCast_AsBP_Throw_Pal_Weapon, bool K2Node_DynamicCast_bSuccess, bool CallFunc_IsValid_ReturnValue, class APalPlayerCharacter* CallFunc_GetPalmi_ReturnValue, enum class EPalPlayerInventoryType CallFunc_GetPrimaryInventoryType_ReturnValue, class APalWeaponBase* CallFunc_GetHasWeapon_ReturnValue, bool CallFunc_EqualEqual_ByteByte_ReturnValue, class ABP_ThrowWeapon_Dummy_C* K2Node_DynamicCast_AsBP_Throw_Weapon_Dummy, bool K2Node_DynamicCast_bSuccess_1, bool CallFunc_IsValid_ReturnValue_1, class UPalItemIDManager* CallFunc_GetItemIDManager_ReturnValue, bool CallFunc_IsValid_ReturnValue_2);
	void Setup_AfterCreatedPlayer(FDelegateProperty_ K2Node_CreateDelegate_OutputDelegate, FDelegateProperty_ K2Node_CreateDelegate_OutputDelegate_1, FDelegateProperty_ K2Node_CreateDelegate_OutputDelegate_2, class UPalOtomoHolderComponentBase* CallFunc_GetOtomoHolderComponent_ReturnValue, bool CallFunc_IsValid_ReturnValue, class UBP_OtomoPalHolderComponent_C* K2Node_DynamicCast_AsBP_Otomo_Pal_Holder_Component, bool K2Node_DynamicCast_bSuccess, FDelegateProperty_ K2Node_CreateDelegate_OutputDelegate_3, class APalPlayerCharacter* CallFunc_GetPalmi_ReturnValue, bool CallFunc_IsValid_ReturnValue_1, bool CallFunc_IsValid_ReturnValue_2);
	void Tick(const struct FGeometry& MyGeometry, float InDeltaTime);
	void ExecuteUbergraph_WBP_PalAim(int32 EntryPoint, bool CallFunc_IsValid_ReturnValue, const struct FGeometry& K2Node_Event_MyGeometry, float K2Node_Event_InDeltaTime, const struct FVector2D& CallFunc_GetViewportSize_ReturnValue, class UPalGameSetting* CallFunc_GetGameSetting_ReturnValue, const struct FVector2D& CallFunc_Divide_Vector2DFloat_ReturnValue, float CallFunc_GetViewportScale_ReturnValue, double CallFunc_Divide_DoubleDouble_ReturnValue, class UCanvasPanelSlot* CallFunc_SlotAsCanvasSlot_ReturnValue, const struct FVector2D& CallFunc_Multiply_Vector2DFloat_ReturnValue, const struct FVector2D& CallFunc_Multiply_Vector2DVector2D_ReturnValue, class APalPlayerCharacter* CallFunc_GetPalmi_ReturnValue, bool CallFunc_IsValid_ReturnValue_1, const struct FVector2D& CallFunc_MakeVector2D_ReturnValue, bool CallFunc_IsValid_ReturnValue_2, float CallFunc_GetCurrentBulletBlurRate_ReturnValue, double CallFunc_Add_DoubleDouble_ReturnValue, bool CallFunc_BooleanOR_ReturnValue, double CallFunc_FClamp_ReturnValue, double CallFunc_Divide_DoubleDouble_B_ImplicitCast, double CallFunc_Add_DoubleDouble_A_ImplicitCast);
};

}


