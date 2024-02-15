#pragma once

// Dumped with Dumper-7!


namespace SDK
{
//---------------------------------------------------------------------------------------------------------------------
// CLASSES
//---------------------------------------------------------------------------------------------------------------------

// 0x78 (0x618 - 0x5A0)
// BlueprintGeneratedClass BP_HomingSphereLauncher.BP_HomingSphereLauncher_C
class ABP_HomingSphereLauncher_C : public ABP_RocketLauncher_C
{
public:
	struct FPointerToUberGraphFrame              UberGraphFrame;                                    // 0x5A0(0x8)(ZeroConstructor, Transient, DuplicateTransient)
	TArray<class AActor*>                        TargetList;                                        // 0x5A8(0x10)(Edit, BlueprintVisible, DisableEditOnTemplate, DisableEditOnInstance)
	TMap<class FName, enum class EPalCaptureSphereLevelType> ItemName_LevelTypeMap;                             // 0x5B8(0x50)(Edit, BlueprintVisible, BlueprintReadOnly, DisableEditOnInstance)
	FMulticastInlineDelegateProperty_            OnLaunchPalSphere;                                 // 0x608(0x10)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable, BlueprintCallable)

	static class UClass* StaticClass();
	static class ABP_HomingSphereLauncher_C* GetDefaultObj();

	void ClearAttackTarget();
	void GetAttackTarget(class APalCharacter** Target, class AActor* CallFunc_GetOwner_ReturnValue, class APalPlayerCharacter* K2Node_DynamicCast_AsPal_Player_Character, bool K2Node_DynamicCast_bSuccess, class AActor* CallFunc_FindHomingTarget_ForPlayer_ReturnValue, class APalCharacter* K2Node_DynamicCast_AsPal_Character, bool K2Node_DynamicCast_bSuccess_1);
	void GetMuzzleTransform(struct FTransform* Transform, const struct FTransform& CallFunc_GetSocketTransform_ReturnValue);
	void GetShootTransformList(double BaseAnglePitch, double BaseAngleYaw, double BlurAngle, TArray<struct FTransform>* ShootTransformList, const struct FTransform& BaseTransform, const TArray<struct FTransform>& TransformList, int32 Temp_int_Variable, bool CallFunc_LessEqual_IntInt_ReturnValue, int32 CallFunc_Add_IntInt_ReturnValue, double CallFunc_Multiply_IntFloat_ReturnValue, const struct FTransform& CallFunc_GetMuzzleTransform_Transform, const struct FVector& CallFunc_BreakTransform_Location, const struct FRotator& CallFunc_BreakTransform_Rotation, const struct FVector& CallFunc_BreakTransform_Scale, const struct FVector& CallFunc_GetTargetPosition_TargetPosition, const struct FTransform& CallFunc_GetMuzzleTransform_Transform_1, const struct FVector& CallFunc_BreakTransform_Location_1, const struct FRotator& CallFunc_BreakTransform_Rotation_1, const struct FVector& CallFunc_BreakTransform_Scale_1, double CallFunc_Multiply_DoubleDouble_ReturnValue, const struct FVector& CallFunc_Subtract_VectorVector_ReturnValue, const struct FRotator& CallFunc_MakeRotFromX_ReturnValue, double CallFunc_RandomFloatInRange_ReturnValue, const struct FTransform& CallFunc_MakeTransform_ReturnValue, double CallFunc_Multiply_DoubleDouble_ReturnValue_1, double CallFunc_RandomFloatInRange_ReturnValue_1, double CallFunc_Add_DoubleDouble_ReturnValue, int32 Temp_int_Variable_1, double CallFunc_Multiply_IntFloat_ReturnValue_1, double CallFunc_Add_DoubleDouble_ReturnValue_1, const struct FRotator& CallFunc_MakeRotator_ReturnValue, bool CallFunc_LessEqual_IntInt_ReturnValue_1, const struct FRotator& CallFunc_ComposeRotators_ReturnValue, const struct FTransform& CallFunc_MakeTransform_ReturnValue_1, int32 CallFunc_Add_IntInt_ReturnValue_1, int32 CallFunc_Array_Add_ReturnValue, float CallFunc_MakeRotator_Yaw_ImplicitCast, float CallFunc_MakeRotator_Pitch_ImplicitCast);
	void GetAimingBlurAngle(double* Angle);
	void GetBlurAngle(double* Angle);
	void OnShoot();
	void GetShootInterval(double* Time);
	void GetMuzzleRotator(struct FRotator* Rotator, const struct FRotator& CallFunc_GetMuzzleRotator_Rotator);
	void GetMuzzleLocation(struct FVector* MuzzleLocation, const struct FVector& CallFunc_GetMuzzleLocation_MuzzleLocation);
	void GetBulletClass(class UClass** NewParam);
	void ShootBullet(class ABP_PalSphere_HomingThrowObjectBase_C* TempHomingObject, class FName ItemName, class UPalGameSetting* CallFunc_GetGameSetting_ReturnValue, class FName CallFunc_DecrementCurrentSelectPalSphere_UsedItemID, int32 CallFunc_DecrementCurrentSelectPalSphere_ReturnValue, bool CallFunc_Greater_IntInt_ReturnValue, enum class EPalCaptureSphereLevelType CallFunc_Map_Find_Value, bool CallFunc_Map_Find_ReturnValue, int32 CallFunc_GetCaptureLevelBySphereType_ReturnValue, double CallFunc_RandomFloatInRange_ReturnValue, double CallFunc_RandomFloatInRange_ReturnValue_1, const struct FVector& CallFunc_Conv_DoubleToVector_ReturnValue, const struct FVector& CallFunc_Conv_DoubleToVector_ReturnValue_1, double CallFunc_RandomFloatInRange_ReturnValue_2, const struct FTransform& CallFunc_GetMuzzleTransform_Transform, const struct FVector& CallFunc_Conv_DoubleToVector_ReturnValue_2, const struct FVector& CallFunc_BreakTransform_Location, const struct FRotator& CallFunc_BreakTransform_Rotation, const struct FVector& CallFunc_BreakTransform_Scale, class APalCharacter* CallFunc_GetAttackTarget_Target, const struct FVector& CallFunc_GetForwardVector_ReturnValue, const struct FVector& CallFunc_Multiply_VectorVector_ReturnValue, const struct FVector& CallFunc_GetRightVector_ReturnValue, const struct FVector& CallFunc_GetForwardVector_ReturnValue_1, const struct FVector& CallFunc_Multiply_VectorVector_ReturnValue_1, const struct FVector& CallFunc_Add_VectorVector_ReturnValue, const struct FTransform& CallFunc_GetMuzzleTransform_Transform_1, const struct FVector& CallFunc_Normal_ReturnValue, class UClass* CallFunc_GetBulletClass_NewParam, const struct FVector& CallFunc_Multiply_VectorVector_ReturnValue_2, class UPalBulletCreator* CallFunc_GetBulletCreator_ReturnValue, int32 CallFunc_GetWeaponDamage_ReturnValue, class APalBullet* CallFunc_CreateBullet_ReturnValue, class ABP_PalSphere_HomingThrowObjectBase_C* K2Node_DynamicCast_AsBP_Pal_Sphere_Homing_Throw_Object_Base, bool K2Node_DynamicCast_bSuccess, bool CallFunc_CanShoot_can);
	void ChangeTransformForRocketWhenReloadIsDone(const struct FVector& Location, const struct FRotator& Lotation);
	void ChangeTransformForRocketReload(const struct FVector& Location, const struct FRotator& Rotation);
	void ReceiveBeginPlay();
	void CustomEvent(int32 bulletsNum);
	void OnReleaseTrigger();
	void ExecuteUbergraph_BP_HomingSphereLauncher(int32 EntryPoint, FDelegateProperty_ K2Node_CreateDelegate_OutputDelegate, int32 K2Node_CustomEvent_bulletsNum, bool CallFunc_K2_AttachToComponent_ReturnValue);
	void OnLaunchPalSphere__DelegateSignature(class AActor* Bullet);
};

}


