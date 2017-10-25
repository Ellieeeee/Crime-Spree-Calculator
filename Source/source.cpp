#include <iomanip>
#include <iostream>
using namespace std;

//calculate damage and health
void damageCalc()
{
	//variable and constant spam
	//boosts and helmet popping multipliers
	const float HELMET_POPPING_BONUS = 1.25;
	const float DAMAGE_BOOST_MODIFIER = 0.15;
	const float HEALTH_BOOST_MODIFIER = 0.20;

	//interval that forced modifiers are applied
	const int FORCED_MODIFIER_INTERVAL = 50;

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

	//bool that controls if the program does more than one iteration
	bool continueProgram = true;

	//char used to deterine if continueProgram stays true or is made false
	char yesOrNo;

	//beginning of a while loop that will let the user repeat the program as much as they want
	while (continueProgram == true)
	{
		//prompt user for cs level
		cout << "\nEnter the current crime spree level.\n";
		cin >> crimeSpreeLevel;

		//input verification to make sure the user isn't putting in negative numbers
		//TODO: find a way to check also if the integer has gone over 2147483647 since overflow
		while (crimeSpreeLevel < 0)
		{
			cin.ignore();
			cout << "\nInvalid input, please try again.\n";
			cin >> crimeSpreeLevel;

		}

		//buffer so the program doesn't instantly close from hitting enter
		cin.ignore();

		//calculate how many forced modifiers there are. ALWAYS round down by truncation, we don't want partials here (since no partials of this exist in game)
		numberOfForcedModifiers = crimeSpreeLevel / FORCED_MODIFIER_INTERVAL;

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
		cout << setprecision(0);
		cout << fixed << "Tan Health: " << currentTanHealth << endl;
		cout << fixed << "Tan Breakpoint: " << currentTanBreakpoint << endl;
		cout << fixed << "Taser Health: " << currentTaserHealth << endl;
		cout << fixed << "Taser Breakpoint: " << currentTaserBreakpoint << endl;
		cout << fixed << "Shield Health: " << currentShieldHealth << endl;
		cout << fixed << "Shield Breakpoint: " << currentShieldBreakpoint << endl;
		cout << fixed << "Phalanx Health: " << currentPhalanxHealth << endl;
		cout << fixed << "Phalanx Breakpoint: " << currentPhalanxBreakpoint << endl;
		cout << fixed << "Phalanx: Minimum shots to kill (without crit): " << currentPhalanxMinKillShots << endl;
		cout << fixed << "Bulldozer Health: " << currentBulldozerHealth << endl;
		cout << fixed << "Bulldozer Breakpoint: " << currentBulldozerBreakpoint << endl;

		//damage
		cout << fixed << "\nDamage Values:\n";
		cout << fixed << "Shotgun Tan Damage: " << currentShotgunDamage << endl;
		cout << fixed << "Rifle Tan Damage: " << currentRifleDamage << endl;
		cout << fixed << "Saiga Bulldozer Damage: " << currentSaigaDamage << endl;
		cout << fixed << "M249 Bulldozer Damage: " << currentLMGDamage << endl;
		cout << fixed << "Minigun Bulldozer Damage: " << currentMiniDamage << endl;
		cout << fixed << "Sniper Damage: " << currentSniperDamage << endl;

		//buffer lines so the final line sticks out
		cout << "\n\n";

		//we're done, close the program
		cout << "Enter N to return to the main menu, or any other letter to check another level.\n";
		cin >> yesOrNo;

		//if user wants to continue
		if (yesOrNo == 'N' || yesOrNo == 'n')
		{
			continueProgram = false;
		}

		cin.ignore();

	}




}

//calculate rewards
void rewardCalc()
{
	//set up constants for each of the reward values, easy to change if ovk updates
	const float EXP_MULTIPLIER = 20000;
	const float EMONE_MULTIPLIER = 400000;
	const float COIN_MULTIPLIER = 0.4;
	const float CARD_MULTIPLIER = 0.2;
	const float COSMETIC_MULTIPLIER = 0.007;
	const float WINNING_STREAK_MULT = 0.005;

	int crimeSpreeLevel, missionReward, startingCrimeSpreeLevel;
	float rewardMult, finalEXP, finalEmone, finalCoins, finalCards, finalCosmetics;
	char startingLevelFixCheck;
	bool startingLevelDelta = false;

	//bool that controls if the program does more than one iteration
	bool continueProgram = true;

	//char used to deterine if continueProgram stays true or is made false
	char yesOrNo;

	while (continueProgram)
	{
		//ask user if they have the mod installed to fix starting level
		cout << "\nDo you have the Crime Spree Starting Level Fix mod installed? Y/N\n";
		cin >> startingLevelFixCheck;

		//if they don't, we have to calculate the reward with another step later on
		//starting at levels higher than 0 mean that this level has to be subtracted by the current level
		if (startingLevelFixCheck == 'N' || startingLevelFixCheck == 'n')
			startingLevelDelta = true;

		cout << "\nPlease enter the current Crime Spree Level:" << endl;
		cin >> crimeSpreeLevel;
		cin.ignore();

		//input verification, cannot have negative values
		while (crimeSpreeLevel < 0)
		{
			cout << "Please enter a positive integer value for the current Crime Spree Level:" << endl;
			cin >> crimeSpreeLevel;
			cin.ignore();
		}

		//if the fix is not installed, get the starting value and subtract it from current value
		if (startingLevelDelta)
		{
			cout << "\nPlease enter the starting Crime Spree Level (or 0):" << endl;
			cin >> startingCrimeSpreeLevel;
			cin.ignore();

			//input verification, cannot have negative values
			while (startingCrimeSpreeLevel < 0)
			{
				cout << "Please enter a positive integer value for the starting Crime Spree Level:" << endl;
				cin >> startingCrimeSpreeLevel;
				cin.ignore();
			}

			//get the difference between current level and starting level
			crimeSpreeLevel -= startingCrimeSpreeLevel;
		}

		//ask for how much the current heist is giving
		cout << "\nPlease enter the amount added for the given heist (including any catchup bonus):" << endl;
		cin >> missionReward;
		cin.ignore();

		//input verification, cannot have negative values
		while (missionReward < 0)
		{
			cout << "Please enter a positive integer value for the amount added for the given heist (including any catchup bonus):";
			cin >> missionReward;
			cin.ignore();
		}

		//add mission reward to the crime spree level
		crimeSpreeLevel += missionReward;

		//calculate rewards
		rewardMult = (1 + (crimeSpreeLevel * WINNING_STREAK_MULT) * missionReward);
		finalEXP = ceil(EXP_MULTIPLIER * rewardMult);
		finalEmone = ceil(EMONE_MULTIPLIER * rewardMult);
		finalCoins = ceil(COIN_MULTIPLIER * rewardMult);
		finalCards = ceil(CARD_MULTIPLIER * rewardMult);
		finalCosmetics = ceil(COSMETIC_MULTIPLIER * rewardMult);

		//display results
		cout << setprecision(0);
		cout << "\nHeist Reward Results:\n";
		cout << fixed << "Experience: " << finalEXP << endl;
		cout << fixed << "Cash: " << finalEmone << endl;
		cout << fixed << "Coins: " << finalCoins << endl;
		cout << fixed << "Card Drops: " << finalCards << endl;
		cout << fixed << "Cosmetics: " << finalCosmetics << endl;

		//we're done, close the program or check another
		cout << "\nEnter N to return to the main menu, or any other letter to check another level.\n";
		cin >> yesOrNo;

		//if user wants to continue or not
		if (yesOrNo == 'N' || yesOrNo == 'n')
		{
			continueProgram = false;
		}

		cin.ignore();
	}
}


//more information
void moreInfo()
{
	cin.ignore();
	cout << "\nHealth/Damage Calculator:\nThis is a simple way to calculate how much health and damage the enemies are \ngoing to be dealing from the forced modifiers, for any given Crime Spree level.\n";
	cout << "The damage dealt is displayed for the average damage, which is dealt at \n10-20 meters. This means that going closer or further from this range will vary the results.\n";
	cout << "The breakpoints for each enemy type is including the bonus from all perk decks: Helmet Popping, and as such not having this perk will mean that the breakpoints are 25% higher.\n\n";
	cout << "'Phalanx' refers to the minions that accompany Captain Winters, and they will \neventually replace all shield units on the map around level 400 to 500, \ndepending on the host.\n";
	cout << "These units have a hard limit on how much damage they can take at one time. \nThey have a limit of 300 base damage given to them from a single shot, so\nexcess damage is wasted.\n";
	cout << "However, bonuses such as headshot and explosive multipliers bypass this bonus, \nas do critical hits. A critical headshot can deal up to \n300 * 15 * 1.25 * 15 = 84,375 damage!\n";
	cout << "As such, there are two breakpoints listed for these units. One involving\nregular headshots, and the other involving the minimum amount of shots it would take without crits.\n\n";

	cout << "Reward Calculator:\nThis is how to calculate the amount of rewards after one heist,\ngiven any Crime Spree level.\n";
	cout << "It will calculate EXP, Cash, Coins, Card Drops, and Cosmetics (Armor Skins).\n";
	cout << "\n\nIf you have any suggestions on how to improve this information screen, please\nleave a comment on the mod page or the GitHub, and thank you for using\nthis program.\n";

	cout << "\nPress Enter to go back to the main menu.\n";
	cin.ignore();


}

int main()
{
	int menuChoice;

	//going to break one of the rules of programming here, we're going to make an infinite loop
	//this is because it is reliant on the user (or an error) to terminate it
	while (true)
	{
		//display our menu
		cout << "\nPlease make a selection:" << endl;
		cout << "1: Health/Damage Calculator." << endl;
		cout << "2: Reward Calculator." << endl;
		cout << "3: Info/Help." << endl;
		cout << "4: Exit.\n" << endl;


		//ask for the user to enter a number
		cin >> menuChoice;

		//if number is not 1-4, ask for another
		while (menuChoice < 1 || menuChoice > 4)
		{
			cout << "Invalid Input: Please enter a valid selection" << endl;
			cin >> menuChoice;
		}

		if (menuChoice == 1)
			damageCalc();
		else if (menuChoice == 2)
			rewardCalc();
		else if (menuChoice == 3)
			moreInfo();
		else if (menuChoice == 4)
			break;

		//error message if things aren't working properly
		else
		{
			cout << "An unexpected error occured. Please report this bug with the details on the mod page or GitHub." << endl;
			break;
		}
	}
	return 0;
}
