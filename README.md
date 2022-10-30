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
4. ResourceComponent;
5. SimpleResourceComponent;

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
    * `DisableOnValueZero` - if true, auto increase will be stopped if `Value` reached zero;
3. `AutoDecreaseDta` - a struct with basic parameters for auto decrease of the resource:
    * `IsEnabled` - toggles if auto decrease is enabled;
    * `Power` - the amount of the resource on which `Value` is decreased every tick;
    * `Frequency` - how often the resource will decrease per second;
    * `Thershhold` - if `Value` <= `Threshold`, the auto decrease will start;
    * `StartDelay` - a delay time after which auto decrease starts. If == 0, it starts immediately;
    * `DisableOnValueZero` - if true, auto decrease will be stopped if `Value` reached zero;

#### Functions

1. `DecreaseValue` - decreases `Value` and clamps it to 0;
2. `IncreaseValue` - increases `Value`. If `ClampToMax == true`, the Value will be clamped to MaxValue;
3. `DecreaseMaxValue` - decreases `MaxValue`. If `ClampValue == true` and `Value > MaxValue`, `Value` will be clamped to
   MaxValue;
4. `IncreaseMaxValue` - increases `MaxValue`. If `ClampValue == true` and `Value < MaxValue`, `Value` will be clamped to
   MaxValue;
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

1. `OnValueDecreased` - called when `Value` was successfully decreased;
2. `OnValueIncreased` - called when `Value` was successfully increased;
3. `OnValueZero` - called when `Value` has reached zero;
4. `OnMaxValueDecreased` - called when `MaxValue` was successfully decreased;
5. `OnMaxValueIncreased` - called when `MaxValue` was successfully increased;
6. `OnAutoDecreaseStarted` - called when auto decrease was started;
7. `OnAutoIncreaseStrated` - called when auto increase was started;
8. `OnAutoDecreaseStopped` - called when auto decrease was stopped;
9. `OnAutoIncreaseStopped` - called when auto increase was stopped;

### SimpleEntityResource

A simple version of the entity resource. It doesn't have auto increase/decrease functionality and uses int32.

#### Variables

1. `ResourceData` - a struct with base parameters:
    * `Value` - current value;
    * `MaxValue` - max value;
    * `UseCustomInitialValue` - toggles if `Value = InitialValue` or `Value = MaxValue` on resource creation;

#### Functions

1. `DecreaseValue` - decreases `Value`;
2. `IncreaseValue` - increases `Value`. If `ClampToMax == true`, it'll be clamped to `MaxValue`;
3. `DecreaseMaxValue`- decreases `MaxValue`. If `ClampValue == true` and `Value > MaxValue`, `Value` will be clamped to
   MaxValue;
4. `IncreaseMaxValue` - increases `MaxValue`. If `ClampValue == true` and `Value < MaxValue`, `Value` will be clamped to
   MaxValue;
5. `GetNormalisedValue` - returns normalised `Value`;
6. `GetValue` - returns `Value`;
7. `GetMaxValue` - returns `MaxValue`;

#### Delegates

1. `OnValueDecreased` - called when `Value` was successfully decreased;
2. `OnValueIncreased` - called when `Value` was successfully increased;
3. `OnValueZero` - called when `Value` has reached zero;
4. `OnMaxValueDecreased` - called when `MaxValue` was successfully decreased;
5. `OnMaxValueIncreased` - called when `MaxValue` was successfully increased;

### EntityResourceLibrary

#### Functions

1. `CreateEntityResource` - creates an EntityResource object.
2. `CreateSimpleEntityResource` - creates a SimpleEntityResource object.

### ResourceComponent

A component which handles creating and controlling one EntityResource object.

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
    * `DisableOnValueZero` - if true, auto increase will be stopped if `Value` reached zero;
3. `AutoDecreaseDta` - a struct with basic parameters for auto decrease of the resource:
    * `IsEnabled` - toggles if auto decrease is enabled;
    * `Power` - the amount of the resource on which `Value` is decreased every tick;
    * `Frequency` - how often the resource will decrease per second;
    * `Thershhold` - if `Value` <= `Threshold`, the auto decrease will start;
    * `StartDelay` - a delay time after which auto decrease starts. If == 0, it starts immediately;
    * `DisableOnValueZero` - if true, auto decrease will be stopped if `Value` reached zero;

#### Functions

1. `DecreaseValue` - decreases `Value` and clamps it to 0;
2. `IncreaseValue` - increases `Value`. If `ClampToMax == true`, the Value will be clamped to MaxValue;
3. `DecreaseMaxValue` - decreases `MaxValue`. If `ClampValue == true` and `Value > MaxValue`, `Value` will be clamped to
   MaxValue;
4. `IncreaseMaxValue` - increases `MaxValue`. If `ClampValue == true` and `Value < MaxValue`, `Value` will be clamped to
   MaxValue;
5. `GetNormalisedValue` - returns normalised value of the resource;
6. `GetValue` - returns `Value`;
7. `GetMaxValue` - returns `MaxValue`;
8. `SetAutoIncreaseEnabled` - toggles auto increase;
9. `SetAutoDecreaseEnabled` - toggles auto decrease;
10. `StartAutoDecrease` - starts auto decrease;
11. `StartAutoIncrease` - starts auto increase;
12. `StopAutoDecrease` - stops auto decrease;
13. `StopAutoIncrease` - stops auto increase;

#### Delegates

1. `OnResourceValueDecreased` - called when `Value` was successfully decreased;
2. `OnResourceValueIncreased` - called when `Value` was successfully increased;
3. `OnResourceValueZero` - called when `Value` has reached zero;
4. `OnResourceMaxValueDecreased` - called when `MaxValue` was successfully decreased;
5. `OnResourceMaxValueIncreased` - called when `MaxValue` was successfully increased;
6. `OnResourceAutoDecreaseStarted` - called when auto decrease was started;
7. `OnResourceAutoIncreaseStrated` - called when auto increase was started;
8. `OnResourceAutoDecreaseStopped` - called when auto decrease was stopped;
9. `OnResourceAutoIncreaseStopped` - called when auto increase was stopped;

### SimpleResourceComponent

A component which handles creating and controlling one SimpleEntityResource object.

#### Variables

1. `ResourceData` - a struct with base parameters:
    * `Value` - current value;
    * `MaxValue` - max value;
    * `UseCustomInitialValue` - toggles if `Value = InitialValue` or `Value = MaxValue` on resource creation;

#### Functions

1. `DecreaseValue` - decreases `Value`;
2. `IncreaseValue` - increases `Value`. If `ClampToMax == true`, it'll be clamped to `MaxValue`;
3. `DecreaseMaxValue`- decreases `MaxValue`. If `ClampValue == true` and `Value > MaxValue`, `Value` will be clamped to
   MaxValue;
4. `IncreaseMaxValue` - increases `MaxValue`. If `ClampValue == true` and `Value < MaxValue`, `Value` will be clamped to
   MaxValue;
5. `GetNormalisedValue` - returns normalised `Value`;
6. `GetValue` - returns `Value`;
7. `GetMaxValue` - returns `MaxValue`;

#### Delegates

1. `OnResourceValueDecreased` - called when `Value` was successfully decreased;
2. `OnResourceValueIncreased` - called when `Value` was successfully increased;
3. `OnResourceValueZero` - called when `Value` has reached zero;
4. `OnResourceMaxValueDecreased` - called when `MaxValue` was successfully decreased;
5. `OnResourceMaxValueIncreased` - called when `MaxValue` was successfully increased;

## Quick setup