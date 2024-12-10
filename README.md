# Satisfactory ModProfile Library
Custom Profiling Library is a simple header-only lib to allow simple profiling of C++ methods within your mod

I wasn't really happy with Unreal Insights or Jetbrains profiling tools as they tend to take more time to get the information I need in a modding context. This is much simpler and straightforwards.

This library simply outputs the method name and the execution time into the UE Log or if you're also using the ModLog lib the custom logging file. If you don't intend to use the ModLog lib comment it out in the include.



Example Log Output:
```
UResourceRouletteManager::InitMeshesToDestroy executed in 0.01 ms
Persistent callback for tagging new actors has been registered.
UResourceCollectionManager::CollectWorldResources executed in 6.06 ms
UResourcePurityManager::CollectOriginalPurities executed in 0.01 ms
Cached new Original Resource node data.
Resource Scan from Save.
UResourceRouletteManager::ScanWorldResourceNodes executed in 13.04 ms
UResourceRouletteManager::RandomizeWorldResourceNodes executed in 0.01 ms
Number of nodes to spawn: 621
UResourceNodeSpawner::SpawnWorldResources executed in 54.50 ms
UResourceRouletteUtility::AssociateExtractorsWithNodes executed in 0.01 ms
Resources Spawning completed successfully.
```
# How to use

Add the MOD_PROFILE() macro into your method(s) you want to check and profile
```cpp
void WhateverMethodYouWantToProfile()
{
    MOD_PROFILE();

    -- Rest of your method here
}
```
To profile subsections as well (e.g. to profile sub-sections of a method) just wrap your code in brackets and add
a macro there. In this example below, it would profile both the outer scope of the whole function but also each sub-section.

```cpp
void ASomeModdingClass::SomeFunctionName()
{
    MOD_PROFILE();
    // Some Code here

    {
        RR_PROFILE("SubSection 1");
        // Some sbsection code you want to separately profile here
    }
    
    {
        RR_PROFILE("SubSection 2");
        // Some other sbsection code you want to separately profile here
    }
}
```

If you have improvements, please leave a pull request!

