// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingGameInstance.h"

void UShootingGameInstance::Init()
{
	Super::Init();
	
	if (SaveManager == nullptr) // !SaveManager로 쓸 수도 있음
	{
		SaveManager = NewObject<USaveGameManager>(this);
		SaveManager->AddToRoot(); // GC 수거하는걸 막아줌

	}
}

USaveGameManager* UShootingGameInstance::GetSaveGameManager()
{
	return SaveManager;
}
