// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShootingGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCPP_API AShootingGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void AddScore(int32 point);

	void ShowMenu();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMainWidget> MainWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMenuWidget> MenuWidget;


protected:
	virtual void BeginPlay() override;

private:
	int32 currentScore = 0;
	int32 BestScore = 0;

	class UMainWidget* MainUI;

	class UMenuWidget* MenuUI;

	void PrintScore();
	void LoadBestScore();
	void SaveBestScore();


};
