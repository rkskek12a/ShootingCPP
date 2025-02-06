// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCPP_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta= (BindWidget))
	class UButton* ButtonRestart;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* ButtonQuit;

protected:
	virtual void NativeConstruct() override;

private:

	UFUNCTION()
	void Restart();

	UFUNCTION()
	void Quit();

};
