#pragma once

/**
 * Type of node on the map (enemy, random encounter etc.)
 */
UENUM()
enum EMapNodeType : uint8
{
	EnemyNode = 0,
	BossNode = 1,
	UnknownNode = 2
};
