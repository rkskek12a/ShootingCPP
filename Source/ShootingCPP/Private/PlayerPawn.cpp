// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "bullet.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component"));
	SetRootComponent(BoxComp);
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Static Mesh"));
	MeshComp->SetupAttachment(BoxComp);

	FVector BoxSize = FVector(50.0f, 50.0f, 50.0f);
	BoxComp->SetBoxExtent(BoxSize);

	FirePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("Fireposition"));
	FirePosition->SetupAttachment(BoxComp);

	BoxComp->SetGenerateOverlapEvents(true);
	BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxComp->SetCollisionObjectType(ECC_GameTraceChannel1); //Player로 설정을 하겠다는 의미

	BoxComp->SetCollisionResponseToAllChannels(ECR_Ignore); //boxcomp의 collision을 다 ignore으로 변경
	BoxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Overlap); //boxcomp의 enemy(channel2)


}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (PlayerController != nullptr)
	{
		UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		if (subsystem != nullptr)
		{
			subsystem->AddMappingContext(IMC_PlayerInput, 0);
		}
	}
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Direction = FVector(0, Horizontal, Vertical);

	Direction.Normalize();

	FVector NewLocation = GetActorLocation() + Direction * MoveSpeed * DeltaTime;

	SetActorLocation(NewLocation);


}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent != nullptr)
	{
		EnhancedInputComponent->BindAction(IA_Horizontal, ETriggerEvent::Triggered, this, &APlayerPawn::OnInputHorizontal);
		EnhancedInputComponent->BindAction(IA_Horizontal, ETriggerEvent::Completed, this, &APlayerPawn::OnInputHorizontal);
		EnhancedInputComponent->BindAction(IA_Vertical, ETriggerEvent::Triggered, this, &APlayerPawn::OnInputVertical);
		EnhancedInputComponent->BindAction(IA_Vertical, ETriggerEvent::Completed, this, &APlayerPawn::OnInputVertical);
		EnhancedInputComponent->BindAction(IA_Fire, ETriggerEvent::Started, this, &APlayerPawn::Fire);

	}
}

void APlayerPawn::OnInputHorizontal(const FInputActionValue& value)
{
	Horizontal = value.Get<float>();
	//UE_LOG(LogTemp, Warning, TEXT("Horizontal: %.2f"), Horizontal);
}

void APlayerPawn::OnInputVertical(const FInputActionValue& value)
{
	Vertical = value.Get<float>();
	//UE_LOG(LogTemp, Warning, TEXT("Vertical: %.2f"), Vertical);
}

void APlayerPawn::Fire()
{
	Abullet* bullet = GetWorld()->SpawnActor<Abullet>(
		BulletFactory, FirePosition->GetComponentLocation(), 
		FirePosition->GetComponentRotation());
	UGameplayStatics::PlaySound2D(GetWorld(), FireSound);
}

