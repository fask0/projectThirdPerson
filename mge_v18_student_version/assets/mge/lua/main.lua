Debug = false;
DrawColliders = false;
WindowWidth = 1920;
WindowHeight = 1080;
MaxMusicVolume = 80;   -- 0 to 100
MaxSFXVolume = 50;     -- 0 to 100
MaxHealth = 10000;

--------------------------------------------------------------------------------------
----------------------------------------Level-----------------------------------------
--BaseSize                  --The initial space for enemies that are spawning
--SizeGrowthFrequency       --Amount of waves for the scaling to be applied (1 means it will be applied after every wave)
--EnemyScalingPercentage    --The increasing amount of enemies
--DelayBetweenEnemies       --How much time between each enemy (in seconds)
--------------------------------------------------------------------------------------
--Lane One
LaneOneBaseSize = 60;
LaneOneSizeGrowthFrequency = 1;
LaneOneEnemyScalingPercentage = 10;
LaneOneDelayBetweenEnemies = 1;
--Lane Two
LaneTwoBaseSize = 60;
LaneTwoSizeGrowthFrequency = 1;
LaneTwoEnemyScalingPercentage = 10;
LaneTwoDelayBetweenEnemies = 1.0;
--Lane Three
LaneThreeBaseSize = 60;
LaneThreeSizeGrowthFrequency = 1;
LaneThreeEnemyScalingPercentage = 10;
LaneThreeDelayBetweenEnemies = 1.0;
--Lane Four
LaneFourBaseSize = 20;
LaneFourSizeGrowthFrequency = 1;
LaneFourEnemyScalingPercentage = 10;
LaneFourDelayBetweenEnemies = 1.0;
--------------------------------------------------------------------------------------
----------------------------------------Towers----------------------------------------
--------------------------------------------------------------------------------------
StartingMoney = 5000; -- Doesnt do anything
--Toaster tower (basic shooting tower)
ToasterRange = 6;
ToasterAttSpeed = 0.60;
ToasterCost = 25;
ToasterDamage = 20;

--Honey tower (Slows enemies)
HoneyRange = 5;
HoneyAttSpeed = 4;
HoneyCost = 25;
HoneySlowAmount = 50;

--Shock tower (Shocks enemies within certain range dealing AoE damage)
ShockRange = 4;
ShockAttSpeed = 0.3;
ShockCost = 50;
ShockDamage = 2;

--Ice tower (Crushes enemies in front of it, activated once per round)
IceRange = 5;
IceAttSpeed = 2;
IceFreezeTime = 1;
IceCost = 50;
IceDamage = 1;

--Magnifying glass tower
MagnifyingRange = 0; -- should always be 0
MagnifyingFireDamage = 15;
MagnifyingFireRate = 1;
MagnifyingFireDuration = 5;
MagnifyingCost = 35;

--Sniper tower
SniperRange = 12;
SniperAttSpeed = 3;
SniperCost = 45;
SniperDamage = 150;


---------------------------------------------------------------------------------------
----------------------------------------Enemies----------------------------------------
--Size                  --Amount of spots it will take in current wave/lane
--Health                --Max health
--HealthRegen           --Health gained per second
--Damage                --Damage dealt to mouse fortress
--Speed                 --Movement Speed
--EffectRecoverySpeed   --The time it takes to recover from slow down/kockback effects
---------------------------------------------------------------------------------------
--Rat
RatSize = 1;
RatHealth = 100;
RatHealthRegen = 0;
RatDamage = 5;
RatSpeed = 2;
RatKillValue = 1;
RatEffectRecoverySpeed = 2;
--Chad
ChadSize = 3;
ChadHealth = 350;
ChadHealthRegen = 0;
ChadDamage = 5;
ChadSpeed = 1;
ChadKillValue = 3;
ChadEffectRecoverySpeed = 2;
--Sanic
SanicSize = 2;
SanicHealth = 70;
SanicHealthRegen = 0;
SanicDamage = 5;
SanicSpeed = 4;
SanicKillValue = 2;
SanicEffectRecoverySpeed = 2;
---------------------------------------------------------------------------------------
