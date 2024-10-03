// Fill out your copyright notice in the Description page of Project Settings.


#include "Taxonomy/TaxonomySubsystem.h"
#include "TaxonomySubsystem.h"

void UTaxonomySubsystem::ChangeXAxisValue(int32 Change)
{
	this->PlayersVsWorldAxis += Change;
}

void UTaxonomySubsystem::ChangeYAxisValue(int32 Change)
{
	this->ActingAxis += Change;
}

void UTaxonomySubsystem::SetXAxisValue(int32 Change)
{
	this->PlayersVsWorldAxis = Change;
}

void UTaxonomySubsystem::SetYAxisValue(int32 Change)
{
	this->ActingAxis = Change;
}
