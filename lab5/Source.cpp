#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void setData(string fileName);
void printAll(int count);
void printPower(int index);
void printPowerTwo(int index);
void findMaxPower();
void findUnarmed();
void printUnarmed(vector<int> index);


int firePowerMaxIndex;
int firePowerMinIndex;
int maxWeaponIndex;
int globalCount = 0;
vector<int> unarmedShips;
vector<int> globalWeaponsCount;
vector<int> totalFirePowerVect;
vector<string> nameVect;
vector<string> classOfShipVect;
vector<short> lengthOfShipVect;
vector<int> shieldVect;
vector<float> maxWarpSpeedVect;
vector<int> weaponsCountVect;
vector<string> weaponNameVect;
vector<int> powerRatingVect;
vector<float> powerConsumptionVect;

fstream someFile;

int main()
{
	cout << "Which file(s) to open?\n";
	cout << "1. friendlyships.shp" << endl;
	cout << "2. enemyships.shp" << endl;
	cout << "3. Both files" << endl;

	int option1;
	cin >> option1;

	if (option1 == 1)
	{
		setData("friendlyships.shp");
	}
	else if (option1 == 2)
	{
		setData("enemyships.shp");
	}
	else if (option1 == 3)
	{
		setData("friendlyships.shp");
		setData("enemyships.shp");
	}
	else
	{
		cout << "Invalid input" << endl;
	}

	findMaxPower();

	cout << "1. Print all ships" << endl;
	cout << "2. Starship with the strongest weapon" << endl;
	cout << "3. Strongest starship overall" << endl;
	cout << "4. Weakest ship (ignoring unarmed)" << endl;
	cout << "5. Unarmed ships" << endl;
	int option;
	cin >> option;

	if (option == 1)
	{
		printAll(globalCount);

	}
	else if (option == 2)
	{
		printPower(maxWeaponIndex);
	}
	else if (option == 3)
	{
		if(option1==2)
		printPowerTwo(firePowerMaxIndex);
		else
			printPower(firePowerMaxIndex);

	}
	else if (option == 4)
	{
		printPower(firePowerMinIndex);

	}
	else if (option == 5)
	{
		findUnarmed();
		printUnarmed(unarmedShips);
	}
	else
	{
		cout << "Invalid input" << endl;
	}


	return 0;
}


void setData(string fileName)
{
	int count;
	int lengthOfName;
	string name;
	int lengthOfClass;
	string classOfShip;
	short lengthOfShip;
	int shield;
	float maxWarpSpeed;
	int weaponsCount;
	int lengthOfWeapon;
	string weaponName;
	int powerRating;
	float powerConsumption;
	int temp = 0;

	ifstream someFile(fileName, ios_base::binary);
	if (someFile.is_open())
	{
		someFile.read((char*)& count, 4);
		globalCount += count;


		for (int i = 0; i < globalCount; i++)
		{
			someFile.read((char*)& lengthOfName, 4);
			char* data = new char[lengthOfName + 1];
			someFile.read(data, lengthOfName * sizeof(data[0]));
			name = data;
			delete[] data;

			someFile.read((char*)& lengthOfClass, 4);
			data = new char[lengthOfClass + 1];
			someFile.read(data, lengthOfClass * sizeof(data[0]));
			classOfShip = data;
			delete[] data;

			someFile.read((char*)& lengthOfShip, 2);
			someFile.read((char*)& shield, 4);
			someFile.read((char*)& maxWarpSpeed, 4);
			someFile.read((char*)& weaponsCount, 4);

			nameVect.push_back(name);
			classOfShipVect.push_back(classOfShip);
			lengthOfShipVect.push_back(lengthOfShip);
			shieldVect.push_back(shield);
			maxWarpSpeedVect.push_back(maxWarpSpeed);
			weaponsCountVect.push_back(weaponsCount);

			int totalFirePower = 0;

			if (weaponsCount != 0)
			{
				globalWeaponsCount.push_back(temp);
				for (int k = 0; k < weaponsCount; k++)
				{
					someFile.read((char*)& lengthOfWeapon, 4);

					data = new char[lengthOfWeapon + 1];
					someFile.read(data, lengthOfWeapon * sizeof(data[0]));
					weaponName = data;
					delete[] data;

					someFile.read((char*)& powerRating, 4);
					someFile.read((char*)& powerConsumption, 4);

					totalFirePower += powerRating;
					temp++;


					weaponNameVect.push_back(weaponName);
					powerRatingVect.push_back(powerRating);
					powerConsumptionVect.push_back(powerConsumption);

				}
			}
			totalFirePowerVect.push_back(totalFirePower);
		}

		someFile.close();
	}

	else
	{
		cout << "could not read file" << endl;
	}
}


void printAll(int count)
{
	int temp = 0;

	for (int i = 0; i < count; i++)
	{
		cout << "Name: " << nameVect[i] << endl;
		cout << "Class: " << classOfShipVect[i] << endl;
		cout << "Length: " << lengthOfShipVect[i] << endl;
		cout << "Shield capacity: " << shieldVect[i] << endl;
		cout << "Maximum Warp: " << maxWarpSpeedVect[i] << endl;
		cout << "Armaments: " << endl;

		if (weaponsCountVect[i] == 0)
		{
			cout << "Unarmed" << endl;
		}
		else
		{
			for (int k = 0; k < weaponsCountVect[i]; k++)
			{
				cout << weaponNameVect[temp] << ", ";
				cout << powerRatingVect[temp] << ", ";
				cout << powerConsumptionVect[temp] << endl;
				temp++;
			}
			cout << "Total firepower: " << totalFirePowerVect[i] << endl;
		}
		cout << endl;

	}
}

void findMaxPower()
{
	int mostPower = totalFirePowerVect[0];
	int leastPower = totalFirePowerVect[0];
	for (unsigned int i = 0; i < totalFirePowerVect.size(); i++)
	{
		if (mostPower < totalFirePowerVect[i])
		{
			mostPower = totalFirePowerVect[i];
			firePowerMaxIndex = i;
			//cout << "Most Power: " << mostPower << endl;
			//cout << "MaxIndex: " << firePowerMaxIndex << endl;

		}
		if (leastPower > totalFirePowerVect[i] && totalFirePowerVect[i] != 0)
		{
			leastPower = totalFirePowerVect[i];
			firePowerMinIndex = i;
			//cout << "Least Power: " << leastPower << endl;
		}
	}
}

void findUnarmed()
{
	for (unsigned int i = 0; i < totalFirePowerVect.size(); i++)
	{
		if (totalFirePowerVect[i] == 0)
		{
			unarmedShips.push_back(i);
		}

	}
}


void printPower(int index)
{

	int temp = 0;

	cout << "Name: " << nameVect[index] << endl;
	cout << "Class: " << classOfShipVect[index] << endl;
	cout << "Length: " << lengthOfShipVect[index] << endl;
	cout << "Shield capacity: " << shieldVect[index] << endl;
	cout << "Maximum Warp: " << maxWarpSpeedVect[index] << endl;
	cout << "Armaments: " << endl;

	if (weaponsCountVect[index] == 0)
	{
		cout << "Unarmed" << endl;
	}
	else
	{
		temp = globalWeaponsCount[index-1];
		for (int k = 0; k < weaponsCountVect[index]; k++)
		{
			//cout << "Temp: " << temp << endl;
			cout << weaponNameVect[temp] << ", ";
			cout << powerRatingVect[temp] << ", ";
			cout << powerConsumptionVect[temp] << endl;
			temp++;
		}
		cout << "Total firepower: " << totalFirePowerVect[index] << endl;
	}
	cout << endl;
}

void printPowerTwo(int index)
{

	int temp = 0;

	cout << "Name: " << nameVect[index] << endl;
	cout << "Class: " << classOfShipVect[index] << endl;
	cout << "Length: " << lengthOfShipVect[index] << endl;
	cout << "Shield capacity: " << shieldVect[index] << endl;
	cout << "Maximum Warp: " << maxWarpSpeedVect[index] << endl;
	cout << "Armaments: " << endl;

	if (weaponsCountVect[index] == 0)
	{
		cout << "Unarmed" << endl;
	}
	else
	{
		temp = globalWeaponsCount[index];
		for (int k = 0; k < weaponsCountVect[index]; k++)
		{
			//cout << "Temp: " << temp << endl;
			cout << weaponNameVect[temp] << ", ";
			cout << powerRatingVect[temp] << ", ";
			cout << powerConsumptionVect[temp] << endl;
			temp++;
		}
		cout << "Total firepower: " << totalFirePowerVect[index] << endl;
	}
	cout << endl;
}

void printUnarmed(vector<int> index)
{
	int temp = 0;
	for (unsigned int i = 0; i < index.size(); i++)
	{
		temp = index[i];
		cout << "Name: " << nameVect[temp] << endl;
		cout << "Class: " << classOfShipVect[temp] << endl;
		cout << "Length: " << lengthOfShipVect[temp] << endl;
		cout << "Shield capacity: " << shieldVect[temp] << endl;
		cout << "Maximum Warp: " << maxWarpSpeedVect[temp] << endl;
		cout << "Armaments: " << endl;
		cout << "Unarmed" << endl;
		cout << endl;
	}
}


