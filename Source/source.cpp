//program that prompts the user for their crime spree level, and when entered, will return the HP and breakpoints for relevant units, as well as their damage

#include <iostream>
using namespace std;

int main()
{
	//variable and constant spam
	//boosts and helmet popping multipliers
	const float HELMET_POPPING_BONUS = 1.25;
	const float DAMAGE_BOOST_MODIFIER = 0.15;
	const float HEALTH_BOOST_MODIFIER = 0.20;

	//health and headshot multipliers
	//tan
	const float TAN_HEALTH = 480;
	const int TAN_HEADSHOT_MULTIPLIER = 6;

	//taser
	const float TASER_HEALTH = 900;
	const int TASER_HEADSHOT_MULTIPLIER = 6;

	//bulldozer
	const float BULLDOZER_HEALTH = 6000;
	const int BULLDOZER_HEADSHOT_MULTIPLIER = 15;

	//shield
	const float SHIELD_HEALTH = 240;
	const int SHIELD_HEADSHOT_MULTIPLIER = 6;

	//phalanx minion (winters shield)
	//we have a third constant here for the damage clamp, this is used because there is a limit to how much can be dealt at once
	//however, any multipliers happen after this number, so it is still possible to 1 shot kill them at a low enough crime spree (or crit headshot, which deals up to around 84000 damage)
	const float PHALANX_HEALTH = 3000;
	const int PHALANX_HEADSHOT_MULTIPLIER = 15;
	const int PHALANX_DAMAGE_CLAMP = 300;

	//weapon damage
	//R870
	const float TAN_870_DAMAGE = 75;
	
	//M4
	const float TAN_M4_DAMAGE = 15;

	//Saiga
	const float BULLDOZER_SAIGA_DAMAGE = 45;

	//M249
	const float BULLDOZER_M249_DAMAGE = 30;

	//M134 Minigun
	const float BULLDOZER_MINI_DAMAGE = 70;

	//PSG-1 Sniper
	const float SNIPER_DAMAGE = 200;

	//ints for these values because we need to truncate them or they have to be a whole number
	int crimeSpreeLevel, numberOfForcedModifiers, currentPhalanxMinKillShots;

	//floats we use for the health and damage boost values
	//these are used as multiples, so we add the number 1 to these later
	float healthBoost, damageBoost;

	//variables for each unit and their respective health/breakpoints
	float currentTanHealth, currentTanBreakpoint, currentTaserHealth, currentTaserBreakpoint, currentShieldHealth, currentShieldBreakpoint, currentPhalanxHealth, currentPhalanxBreakpoint, currentBulldozerHealth, currentBulldozerBreakpoint;
	
	//variables for weapon damage
	float currentShotgunDamage, currentRifleDamage, currentSaigaDamage, currentLMGDamage, currentMiniDamage, currentSniperDamage;

	//prompt user for cs level
	cout << "\nEnter the current crime spree level.\n";
	cin >> crimeSpreeLevel;

	//buffer so the program doesn't instantly close from hitting enter
	cin.ignore();

	//calculate how many forced modifiers there are. ALWAYS round down by truncation, we don't want partials here (since no partials of this exist in game)
	numberOfForcedModifiers = crimeSpreeLevel / 50;

	//calculate the numbers we're going to use for multiplication
	healthBoost = 1 + (numberOfForcedModifiers * HEALTH_BOOST_MODIFIER);
	damageBoost = 1 + (numberOfForcedModifiers * DAMAGE_BOOST_MODIFIER);

	//calculate current health values
	//tan
	currentTanHealth = (TAN_HEALTH * healthBoost);
	currentTanBreakpoint = (currentTanHealth / TAN_HEADSHOT_MULTIPLIER) / HELMET_POPPING_BONUS;

	//taser
	currentTaserHealth = (TASER_HEALTH * healthBoost);
	currentTaserBreakpoint = (currentTaserHealth / TASER_HEADSHOT_MULTIPLIER) / HELMET_POPPING_BONUS;

	//shield
	currentShieldHealth = (SHIELD_HEALTH * healthBoost);
	currentShieldBreakpoint = (currentShieldHealth / SHIELD_HEADSHOT_MULTIPLIER) / HELMET_POPPING_BONUS;

	//phalanx
	currentPhalanxHealth = (PHALANX_HEALTH * healthBoost);
	currentPhalanxBreakpoint = (currentPhalanxHealth / PHALANX_HEADSHOT_MULTIPLIER) / HELMET_POPPING_BONUS;
	currentPhalanxMinKillShots = (currentPhalanxBreakpoint / PHALANX_DAMAGE_CLAMP) + 1;

	//bulldozer
	currentBulldozerHealth = (BULLDOZER_HEALTH * healthBoost);
	currentBulldozerBreakpoint = (currentBulldozerHealth / BULLDOZER_HEADSHOT_MULTIPLIER) / HELMET_POPPING_BONUS;

	//calculate damage values
	//R870
	currentShotgunDamage = TAN_870_DAMAGE * damageBoost;

	//M4
	currentRifleDamage = TAN_M4_DAMAGE * damageBoost;

	//Saiga
	currentSaigaDamage = BULLDOZER_SAIGA_DAMAGE * damageBoost;

	//M249
	currentLMGDamage = BULLDOZER_M249_DAMAGE * damageBoost;

	//M134 Minigun
	currentMiniDamage = BULLDOZER_MINI_DAMAGE * damageBoost;

	//PSG-1 Sniper
	currentSniperDamage = SNIPER_DAMAGE * damageBoost;

	//show it back to the user
	cout << "\nResults:\n";

	//health
	cout << "\nHealth Values:\n";
	cout << "Tan Health: " << currentTanHealth << endl;
	cout << "Tan Breakpoint: " << currentTanBreakpoint << endl;
	cout << "Taser Health: " << currentTaserHealth << endl;
	cout << "Taser Breakpoint: " << currentTaserBreakpoint << endl;
	cout << "Shield Health: " << currentShieldHealth << endl;
	cout << "Shield Breakpoint: " << currentShieldBreakpoint << endl;
	cout << "Phalanx Health: " << currentPhalanxHealth << endl;
	cout << "Phalanx Breakpoint: " << currentPhalanxBreakpoint << endl;
	cout << "Phalanx: Minimum shots to kill (without crit): " << currentPhalanxMinKillShots << endl;
	cout << "Bulldozer Health: " << currentBulldozerHealth << endl;
	cout << "Bulldozer Breakpoint: " << currentBulldozerBreakpoint << endl;

	//damage
	cout << "\nDamage Values:\n";
	cout << "Shotgun Tan Damage: " << currentShotgunDamage << endl;
	cout << "Rifle Tan Damage: " << currentRifleDamage << endl;
	cout << "Saiga Bulldozer Damage: " << currentSaigaDamage << endl;
	cout << "M249 Bulldozer Damage: " << currentLMGDamage << endl;
	cout << "Minigun Bulldozer Damage: " << currentMiniDamage << endl;
	cout << "Sniper Damage: " << currentSniperDamage << endl;

	//buffer lines so the final line sticks out
	cout << "\n\n";

	//we're done, close the program
	cout << "Press Enter to close the program.";
	cin.ignore();



	return 0;
}
