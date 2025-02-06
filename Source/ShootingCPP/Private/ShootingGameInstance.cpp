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

USaveGameManager* UShootingGameInstance::GetSaveGameManager()
{
	return SaveManager;
}
