// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ShootingGameSaveData.h"
#include "SaveGameManager.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCPP_API USaveGameManager : public UObject
{
	GENERATED_BODY()
	
public:
	void SaveGameData(int32 UserIndex, int32 NewBestScore);
	UShootingGameSaveData* LoadGameData(int32 UserIndex, bool& bSuccess);

private:
	//UObject에서는 const를 선언하려면 static이 필수이다.
	static const FString SlotName;


};
