// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingGameInstance.h"

void UShootingGameInstance::Init()
{
	Super::Init();
	
	if (SaveManager == nullptr) // !SaveManager�� �� ���� ����
	{
		SaveManager = NewObject<USaveGameManager>(this);
		SaveManager->AddToRoot(); // GC �����ϴ°� ������

	}
}

void UShootingGameInstance::Shutdown()
{
	Super::Shutdown();

	if (SaveManager)
	{
		SaveManager->RemoveFromRoot();
		SaveManager = nullptr;
	}
}

USaveGameManager* UShootingGameInstance::GetSaveGameManager()
{
	return SaveManager;
}
