#pragma once

#include "CoreMinimal.h"
#include "Windows/WindowsPlatformTime.h"

// Comment this out if you're not using custom logging lib
#include "ModLogUtility.h"

//////////////////////////////////////////////////////////////////////////////////
// Profiling Toggle: Set to 1 to enable profiling, 0 to disable profiling       //
// Remember to **SET TO ZERO BEFORE RELEASING MOD**		                        //
//////////////////////////////////////////////////////////////////////////////////
#define ENABLE_PROFILING 1

//////////////////////////////////////////////////////////////////////////////////
// Set this to your logging utility (if using ModLog) or to UE_Log if you       //
// prefer having to search through the game log to find the profiling info		//
// 0 - Log to Unreal Engine log                                                 //
// 1 - Log to ModLog							                                //
//////////////////////////////////////////////////////////////////////////////////
#define USE_CUSTOM_LOG 1

#if ENABLE_PROFILING
#define MOD_PROFILE() FModProfiler ScopedProfiler(TEXT(__FUNCTION__))
#define MOD_PROFILE_SUBSECTION(SubsectionName) FModProfilerSubsection ScopedSubProfiler(TEXT(__FUNCTION__), TEXT(SubsectionName))
#else
#define MOD_PROFILE()
#define MOD_PROFILE_SUBSECTION(SubsectionName)
#endif

// Called with MOD_PROFILE();
class FModProfiler
{
public:
	explicit FModProfiler(const FString& InFunctionName): FunctionName(InFunctionName)
	{
		StartTime = FPlatformTime::Seconds();
	}

	~FModProfiler()
	{
		const double EndTime = FPlatformTime::Seconds();
		const double ElapsedTime = (EndTime - StartTime) * 1000.0;

		LogMessage(FString::Printf(TEXT("%s executed in %.3f ms"), *FunctionName, ElapsedTime));
	}

private:
	double StartTime;
	FString FunctionName;

	static void LogMessage(const FString& Message)
	{
#if USE_CUSTOM_LOG
		// ModLog for logging
		FModLogUtility::Get().LogMessage(Message, ELogLevel::Debug);
#else
		// UE log
		UE_LOG(LogTemp, Log, TEXT("%s"), *Message);
#endif
	}
};

// Called with MOD_PROFILE_SUBSECTION("Some Subsection Name");
class FModProfilerSubsection
{
public:
	FModProfilerSubsection(const FString& InFunctionName, const FString& InSubsectionName)
	{
		StartTime = FPlatformTime::Seconds();
		SubsectionName = FString::Printf(TEXT("%s - %s"), *InFunctionName, *InSubsectionName);
	}

	~FModProfilerSubsection()
	{
		const double EndTime = FPlatformTime::Seconds();
		const double ElapsedTime = (EndTime - StartTime) * 1000.0;

		LogMessage(FString::Printf(TEXT("%s executed in %.3f ms"), *SubsectionName, ElapsedTime));
	}

private:
	double StartTime;
	FString SubsectionName;

	static void LogMessage(const FString& Message)
	{
#if USE_CUSTOM_LOG
		// ModLog for logging
		FModLogUtility::Get().LogMessage(Message, ELogLevel::Debug);
#else
		// UE log
		UE_LOG(LogTemp, Log, TEXT("%s"), *Message);
#endif
	}
};