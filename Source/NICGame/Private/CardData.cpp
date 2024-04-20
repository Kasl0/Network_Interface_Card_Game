// Fill out your copyright notice in the Description page of Project Settings.

#include "CardData.h"
#include <string>

void UCardData::SetData(std::string Name, std::string Description)
{
	this->Name = UTF8_TO_TCHAR(Name.c_str());
	this->Description = UTF8_TO_TCHAR(Description.c_str());
}