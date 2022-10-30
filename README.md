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

1. `ResourceData`
2. `AutoIncreaseData`
3. `AutoDecreaseDta`

#### Functions

1. `DecreaseValue`
2. `IncreaseValue`
3. `DecreaseMaxValue`
4. `IncreaseMaxValue`
5. `GetNormalisedValue`
6. `GetValue`
7. `GetMaxValue`
8. `SetAutoIncreaseEnabled`
9. `SetAutoDecreaseEnabled`
10. `SetAutoIncreaseData`
11. `SetAutodecreaseData`
12. `GetAutoIncreaseData`
13. `GetAutoDecreaseData`
14. `StartAutoDecrease`
15. `StartAutoIncrease`
16. `StopAutoDecrease`
17. `StopAutoIncrease`

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