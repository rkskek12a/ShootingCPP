// Fill out your copyright notice in the Description page of Project Settings.


#include "bullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
Abullet::Abullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	SetRootComponent(BoxComp);
	BoxComp->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));

	BoxComp->SetWorldScale3D(FVector(0.75f, 0.25f, 1.0f));

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StatickMeshComponent"));
	MeshComp->SetupAttachment(BoxComp);
}

// Called when the game starts or when spawned
void Abullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Abullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation() + GetActorForwardVector() * MoveSpeed * DeltaTime;

	SetActorLocation(NewLocation);
}

