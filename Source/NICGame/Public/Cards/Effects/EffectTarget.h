// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM()
enum EEffectTarget : uint8
{
	// Default; spell can be cast without choosing a target
	NoTarget = 0,
	// Spell can be cast on a minion
	Minion = 1
};
