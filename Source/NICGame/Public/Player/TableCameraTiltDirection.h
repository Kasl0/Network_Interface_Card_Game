#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM()
enum class TableCameraTiltDirection : uint8
{
	None		UMETA(DisplayName = "None"),
	Forward		UMETA(DisplayName = "Forward"),
	Left		UMETA(DisplayName = "Left"),
	Right		UMETA(DisplayName = "Right")
};
