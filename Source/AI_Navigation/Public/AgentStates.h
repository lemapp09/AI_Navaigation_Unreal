﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM(BlueprintType)
enum class EAgentStates : uint8
{
	EAS_Patrolling UMETA(DisplayName = "Patrolling"),
	EAS_Chasing UMETA(DisplayName = "Chasing"),
	EAS_Searching UMETA(DisplayName = "Searching"),
	EAS_Attacking UMETA(DisplayName = "Attacking")
};