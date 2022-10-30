# TrickyEntityResources
A collection of game objects which help to quickly implement health, mana, stamina, overheat etc.

## Installation

The plugin can be used in both C++ and Blueprint projects.

### Blueprint projects

**At the moment, the package is compatible only with Unreal Engine 4.**

1. Download [**package file**](https://github.com/TrickyFatCat/TrickyEntityResuorces/releases/tag/v1.0);
2. Unzip the package to the Plugins folder in engine folder, e.g. `C:\Program Files\Epic Games\UE_4.27\Engine\Plugins`;
3. Restart the project;

In this case the plugin can be used for any blueprint project.

### C++ projects

1. Create the Plugins folder in the project directory;
2. Create the TrickyAnimationComponents folder in the Plugins folder;
3. Download the plugin source code into that folder;
4. Rebuild the project;

## Content

The plugin has:
1. EntityResource object;
2. SimpleEntityResource object;
3. EntityResourcesLibrary;

### EntityResource

Main entity resource which can automatically increase and decrease current value.

#### Variables

1. `ResourceData` - a struct with the basic parameters of the entity resource:
   * `Value` - current value;
   * `Maximum Value` - maximum value;
   * `UseCustomInitialValue` - toggles if the resource must have a custom `Value` on creation;
   * `InitialValue` - determines the custom value of `Value` on creation;
2. `AutoIncreaseData` - a struct with basic parameters for auto increase of the resource:
   * `IsEnabled` - toggles if auto increase is enabled;
   * `Power` - the amount of the resource on which `Value` is increased every tick;
   * `Frequency` - how often the resource will increase per second;
   * `Thershhold` - if `Value` <= `Threshold`, the auto increase will start;
   * `StartDelay` - a delay time after which auto increase starts. If == 0, it starts immediately;
3. `AutoDecreaseDta` - a struct with basic parameters for auto decrease of the resource:
   * `IsEnabled` - toggles if auto decrease is enabled;
   * `Power` - the amount of the resource on which `Value` is decreased every tick;
   * `Frequency` - how often the resource will decrease per second;
   * `Thershhold` - if `Value` <= `Threshold`, the auto decrease will start;
   * `StartDelay` - a delay time after which auto decrease starts. If == 0, it starts immediately;

#### Functions

1. `DecreaseValue` - decreases `Value` and clamps it to 0;
2. `IncreaseValue` - increases Value. If ClampToMax == true, the Value will be clamped to MaxValue;
3. `DecreaseMaxValue` - decreases MaxValue. If ClampValue == true and Value > MaxValue, Value will be clamped to MaxValue;
4. `IncreaseMaxValue` - increases MaxValue. If ClampValue == true and Value < MaxValue, Value will be clamped to MaxValue;
5. `GetNormalisedValue` - returns normalised value of the resource;
6. `GetValue` - returns `Value`;
7. `GetMaxValue` - returns `MaxValue`;
8. `SetAutoIncreaseEnabled` - toggles auto increase;
9. `SetAutoDecreaseEnabled` - toggles auto decrease;
10. `SetAutoIncreaseData` - sets `AutoIncreaseData`;
11. `SetAutodecreaseData` - sets `AutoDecreaseData`;
12. `GetAutoIncreaseData` - returns `AutoIncreaseData` by reference;
13. `GetAutoDecreaseData` - returns `AutoDecreaseData` by reference;
14. `StartAutoDecrease` - starts auto decrease;
15. `StartAutoIncrease` - starts auto increase;
16. `StopAutoDecrease` - stops auto decrease;
17. `StopAutoIncrease` - stops auto increase;

#### Delegates

1. `OnValueDecreased`
2. `OnValueIncreased`
3. `OnValueZero`
4. `OnMaxValueDecreased`
5. `OnMaxValueIncreased`
6. `OnAutoDecreaseStarted`
7. `OnAutoIncreaseStrated`
8. `OnAutoDecreaseStopped`
9. `OnAutoIncreaseStopped`

### SimpleEntityResource

#### Variables

1. `ResourceData`

#### Functions
 
1. `DecreaseValue`
2. `IncreaseValue`
3. `DecreaseMaxValue`
4. `IncreaseMaxValue`
5. `GetNormalisedValue`
6. `GetValue`
7. `GetMaxValue`

#### Delegates

1. `OnValueDecreased`
2. `OnValueIncreased`
3. `OnValueZero`
4. `OnMaxValueDecreased`
5. `OnMaxValueIncreased`

### EntityResourceLibrary

#### Functions

1. `CreateEntityResource`
2. `CreateSimpleEntityResource`

## Quick setup