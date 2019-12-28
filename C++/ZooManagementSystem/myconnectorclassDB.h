#pragma once
// #include "my_global.h" // The included headers we need
#include "mysql.h"
#include <vector>
#include <algorithm>
using namespace std;
class myconnectorclassDB
{
private:
#define SERVER "db.tecnico.ulisboa.pt"
#define USER "ist425614" // Your IST number
#define PASSWORD "trha2275" // NOT IST password
#define DATABASE "ist425614" // Your IST number
	void Query(CString query); // Main query function
	MYSQL *connection; // Pointer allocation for a connection
	// This is an object creation of an existing class in
	// the mySQL libraries we added.
public:
	MYSQL_ROW row; // Another object based on the existing
	// library, this one stores a single row from queries
	MYSQL_RES *result; // and this one the entire result
	// from a query
	void connect(); // Connection function. Notice how
	// this is public, but the connection itself is
	// private.
	CString CPtoUnicode(const char* CPString, UINT CodePage);
	// Converts data from MySQL format to MFC's CString.
	// My Queries
	CString CheckPassword(CString username);
	CString CheckAnimalInformation(CString animal_ID);
	CString CheckAnimalName(CString animal_ID);
	CString CheckAnimalGender(CString animal_ID);
	CString CheckAnimalBirthDate(CString animal_ID);
	CString CheckAnimalOrigin(CString animal_ID);
	CString CheckAnimalWildDate(CString animal_ID);
	CString CheckAnimalID(CString animal_name);
	std::vector<CString> CheckZoneAnimal(CString zone_ID);
	std::vector<CString> CheckKeeperIDs();
	std::vector<CString> CheckManagerIDs();
	std::vector<CString> CheckVeterinarianIDs();
	std::vector<CString> CheckVisitorIDs();
	std::vector<CString> CheckAvailableAnimalNames();
	std::vector<CString> CheckAvailableAnimalIDs();
	CString CheckSpecieID(CString animal_ID);
	CString CheckSpecieName(CString species_ID);
	CString CheckBirth(CString animal_ID);
	void ApplyGodfather(CString user_ID, CString user_name, CString user_email, CString user_birth, CString user_password, CString animal_ID, CString request_date, CString fee);
	CString LastUser();
	myconnectorclassDB(void);
	virtual ~myconnectorclassDB(void);
};
