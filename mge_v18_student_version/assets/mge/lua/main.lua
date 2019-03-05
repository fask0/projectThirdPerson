Debug = true;
DrawColliders = true;
WindowWidth = 1920;
WindowHeight = 1080;

--------------------------------------------------------------------------------------
----------------------------------------Level-----------------------------------------
--BaseSize                  --The initial space for enemies that are spawning
--SizeGrowthFrequency       --Amount of waves for the scaling to be applied (1 means it will be applied after every wave)
--EnemyScalingPercentage    --The increasing amount of enemies
--DelayBetweenEnemies       --How much time between each enemy (in seconds)
--------------------------------------------------------------------------------------
--Lane One
LaneOneBaseSize = 20;
LaneOneSizeGrowthFrequency = 1;
LaneOneEnemyScalingPercentage = 10;
LaneOneDelayBetweenEnemies = 1;
--Lane Two
LaneTwoBaseSize = 20;
LaneTwoSizeGrowthFrequency = 1;
LaneTwoEnemyScalingPercentage = 10;
LaneTwoDelayBetweenEnemies = 1.0;
--Lane Three
LaneThreeBaseSize = 20;
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
StartingMoney = 50;
--Toaster tower (basic shooting tower)
ToasterRange = 6;
ToasterAttSpeed = 1;
ToasterCost = 20;

--Honey tower (slows enemies)
HoneyRange = 5;
HoneyAttSpeed = 5;
HoneyCost = 30;

--MouseTrap tower (Crushes enemies in front of it, activated once per round)
MouseTrapRange = 2;
MouseTrapCost = 30;

--Shock tower (Shocks enemies within certain range dealing AoE damage)
ShockRange = 4;
ShockAttSpeed = 0.25;
ShockCost = 50;

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
RatKillValue = 3;
RatEffectRecoverySpeed = 2;
--Chad
ChadSize = 3;            
ChadHealth = 300;         
ChadHealthRegen = 0;
ChadDamage = 5;
ChadSpeed = 1;
ChadKillValue = 3;
ChadEffectRecoverySpeed = 2;
--Sanic
SanicSize = 2;
SanicHealth = 75;         
SanicHealthRegen = 0;
SanicDamage = 5;
SanicSpeed = 4;
SanicKillValue = 3;
SanicEffectRecoverySpeed = 2;
---------------------------------------------------------------------------------------