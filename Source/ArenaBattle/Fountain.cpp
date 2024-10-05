// Fill out your copyright notice in the Description page of Project Settings.


#include "Fountain.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AFountain::AFountain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));
	Water = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WATER"));
	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("LIGHT"));
	Splash = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SPLASH"));

	//StaticMeshComponent인 Body와 Water를 생성
	//AFountain의 루트컴포넌트는 바디(스테틱메시 컴포넌트)
	RootComponent = Body;

	Water->SetupAttachment(Body); //Water MeshComponent를 Body에다가 붙여줌
	Light->SetupAttachment(Body);
	Splash->SetupAttachment(Body);

	Water->SetRelativeLocation(FVector(0.0f, 0.0f, 135.0f)); //높이를 1.35m 높여준다(물)
	Light->SetRelativeLocation(FVector(0.0f, 0.0f, 195.0f)); //빛을 1.95m
	Splash->SetRelativeLocation(FVector(0.0f, 0.0f, 195.0f)); //튀기는 모션을 1.95m

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BODY(TEXT("/Game/InfinityBladeGrassLands/Environments/Plains/Env_Plains_Ruins/StaticMesh/SM_Plains_Castle_Fountain_01.SM_Plains_Castle_Fountain_01"));
	if (SM_BODY.Succeeded()) 
	{
		Body->SetStaticMesh(SM_BODY.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_WATER(TEXT("/Game/InfinityBladeGrassLands/Effects/FX_Meshes/Env/SM_Plains_Fountain_02.SM_Plains_Fountain_02"));
	if (SM_WATER.Succeeded())
	{
		Water->SetStaticMesh(SM_WATER.Object);
	}
	
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_SPLASH(TEXT("/Game/InfinityBladeGrassLands/Effects/FX_Ambient/Water/P_Water_Fountain_Splash_Base_01.P_Water_Fountain_Splash_Base_01"));
	if (PS_SPLASH.Succeeded()) 
	{
		Splash->SetTemplate(PS_SPLASH.Object);
	}

	// light setting
	Light->SetIntensity(14000.0f);
	// randomly setting light color
	float r, g, b;
	r = FMath::RandRange(0.0f, 1.0f);
	g = FMath::RandRange(0.0f, 1.0f);
	b = FMath::RandRange(0.0f, 1.0f);
	FLinearColor myLColor = FLinearColor(r, g, b);
	Light->SetLightColor(myLColor);

	// rotation
	RotateSpeed = 30.0f;

	// random move
	MoveSpeed = 100.0f;
}

// Called when the game starts or when spawned
void AFountain::BeginPlay()
{
	Super::BeginPlay();
	
	// logging
	ABLOG_S(Warning);
	ABLOG(Warning, TEXT("Actor Name : %s, ID: %d, Location x : %.3f"), *GetName(), ID, GetActorLocation().X);
}

void AFountain::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	ABLOG_S(Warning);
}

void AFountain::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABLOG_S(Warning);
}

// Called every frame
void AFountain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalRotation(FRotator(0.0f, RotateSpeed * DeltaTime, 0.0f));


	// Move towards the target location
	FVector CurrentLocation = GetActorLocation();
	FVector dir = (TargetLocation - CurrentLocation).GetSafeNormal();
	FVector NewLocation = CurrentLocation + (dir * MoveSpeed * DeltaTime);
	SetActorLocation(NewLocation);
	if ((TargetLocation - CurrentLocation).Size() < 10.0f) // If close to target
	{
		GenerateRandomDestination(); // Generate new target location
	}
}

void AFountain::GenerateRandomDestination()
{
	float x, y, z;
	float xConstraint = 500.0f;
	float yConstraint = 500.0f;
	x = FMath::RandRange(-1.0f * xConstraint, 1.0f * xConstraint);
	y = FMath::RandRange(-1.0f * yConstraint, 1.0f * yConstraint);
	z = 0.0f;
	TargetLocation = FVector(x, y, z);
	UE_LOG(LogTemp, Log, TEXT("Target Location Generated: %s"), *TargetLocation.ToString());
}
