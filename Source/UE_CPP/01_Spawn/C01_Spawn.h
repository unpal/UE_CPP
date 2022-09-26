#pragma once

#include "CoreMinimal.h"
// CoreMinimal : Engine 에서 사용할 수 있는 기본 기능들을 모아놓은 헤더
#include "GameFramework/Actor.h"
// Actor : 월드에 배치될 수 있는 기능을 모아놓은 파일
#include "C01_Spawn.generated.h"
// generated : 리플리케이트로 에디터에서 해당 파일이 있다는 것을 알려주는 파일
/*
class template : cpp 와 h 가 같은 이름으로 선언됨

.h : 구성요소의 성분을 작성, 성분들로 할 수있는 행동 이름 작성
Haeder File : 미리 만들어진 기능들을 모아놓은 파일로 #include 로 추가하게
			  된다면 해당 파일에서 기능들을 사용할 수 있습니다.
.cpp : 행동들의 구체적인 기능을 작성
*/
// UCLASS : Unreal 이 사용할 수 있는 class 라는 것을 명시
UCLASS()
class UE_CPP_API AC01_Spawn : public AActor
{
	GENERATED_BODY()
		// GENERATED_BODY()
		// 해당 위치부터 class 의 몸체라는 것을 의미합니다.
private:
	/*
	UPROPERTY() : Reflection 기능을 사용할 수 있는 키워드입니다.
				  UPROPERTY 가 명시되지 않은 변수들은 에디터에서 관리하지 않습니다.

	Unreal 에서는 세가지 타입이 존재합니다.
	1. c++ 타입 : c++ 로 이루어진 코드를 뜻합니다.
	2. 아키 타입 : c++ 코드를 베이스로 만들어진 블루프린트를 뜻합니다.
	3. 인스턴스 타입 : 아키 타입으로 월드에 배치되어 있는 실제적인 구조를 뜻합니다.
	EditAnywhere : 아키타입, 인스턴스타입 모두 공개하여 편집이 가능합니다.
	EditInstanceOnly : 아키타입에만 공개하며 아키타입에서 편집이 가능합니다.
	EditDefaultsOnly : 인스턴스 타입에만 공개하며 인스턴스 타입에서 편집이 가능합니다.
	VisibleAnywhere : 아키타입과 인스턴스타입 모두 공개하지만 편집이 불가능합니다.
	*/
	UPROPERTY(EditAnywhere)
		int A = 10;
	UPROPERTY(EditInstanceOnly)
		int B = 20;
	UPROPERTY(EditDefaultsOnly)
		int C = 30;
	UPROPERTY(VisibleAnywhere)
		int D = 40;

	/*
	Actor 의 기능을 가진 Variable 이라는 클래스를 생성하고
	맴버 변수 Var1,Var2,Var3,Var4 선언해줭

	Var1 은 아키, 인스턴스 다 공개하고 편집 안됭

	Var2 는 아키 공개 편집 가능

	Var3 는 아키 인스턴스 공개 편집 가능

	Var4 인스턴스 공개 편집 가능
	*/
public:	
	AC01_Spawn();
	//생성자(Constructor) :	객체가 생성될 때 호출하는 함수입니다.
	//						클래스 명과 같은 이름의 함수입니다.
	//객체(object) :			어떠한 구조로 이루어진 소프트웨어에서 실체하는 메모리

protected:
	//BeginPlay() : 게임이 시작될 때 단 한번 호출되는 함수
	virtual void BeginPlay() override;


public:	
	// Tick() : 게임 시작 후 매 프레임마다 호출되는 함수입니다.
	virtual void Tick(float DeltaTime) override;
	
};
