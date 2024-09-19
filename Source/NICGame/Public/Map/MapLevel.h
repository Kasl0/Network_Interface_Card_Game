#pragma once

#include "Map/MapNode.h"
#include "MapLevel.generated.h"


USTRUCT(BlueprintType)
struct FMapLevel {
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	TArray<UMapNodeWidget*> Level;

	UMapNodeWidget* operator[] (int32 i) {
		return Level[i];
	}

	void Add(UMapNodeWidget* Node) {
		Level.Add(Node);
	}

	int32 Num() {
		return Level.Num();
	}
};
