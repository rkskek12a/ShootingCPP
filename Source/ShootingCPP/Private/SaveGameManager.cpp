// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGameManager.h"
#include "Kismet/GameplayStatics.h"

const FString USaveGameManager::SlotName = TEXT("ShootingGameSaveData");


void USaveGameManager::SaveGameData(int32 UserIndex, int32 NewBestScore)
{
	//저장공간 만드는 로직
	UShootingGameSaveData* SaveGameData = nullptr;

	if (UGameplayStatics::DoesSaveGameExist(SlotName, UserIndex))
	{
		//해당 슬롯 이름으로 되어있고 해당 번호인 세이브 파일이 있다.
		SaveGameData = Cast<UShootingGameSaveData>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));

	}
	if (!SaveGameData)
	{
		SaveGameData = Cast<UShootingGameSaveData>(UGameplayStatics::CreateSaveGameObject(UShootingGameSaveData::StaticClass()));

	}

	//둘중에 더 큰 수를 반환
	SaveGameData->BestScore = FMath::Max(SaveGameData->BestScore, NewBestScore);
	
	//저장 로직
	if (UGameplayStatics::SaveGameToSlot(SaveGameData, SlotName, UserIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("최고 점수 저장 성공!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("세이브 실패 (ERROR)"));
	}
}

UShootingGameSaveData* USaveGameManager::LoadGameData(int32 UserIndex, bool& bSuccess)
{
	if (UGameplayStatics::DoesSaveGameExist(SlotName, UserIndex))
	{
		UShootingGameSaveData* LoadGameData = Cast<UShootingGameSaveData>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));

		if (LoadGameData != nullptr) //!LoadGameData와 같은 문장
		{
			//불러오는데 성공해서 들어왔습니다
			bSuccess = true;
			UE_LOG(LogTemp, Warning, TEXT("세이브 데이터 로드 성공"));

			return LoadGameData;
		}

	}

	UE_LOG(LogTemp, Warning, TEXT("해당 USERINDEX로 저장된 SaveData가 없습니다."));
	bSuccess = false;
	return nullptr;
}
