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
	CString ReturnCurrentDate();
	CString CalculateDateDiff(CString date1, CString date2);
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
	std::vector<CString> CheckAllAnimalIDs();
	std::vector<CString> CheckAvailableAnimalIDs();
	CString CheckSpecieID(CString animal_ID);
	CString CheckSpecieName(CString species_ID);
	CString CheckBirth(CString animal_ID);
	void ApplyGodfather(CString user_ID, CString user_name, CString user_email, CString user_birth, CString user_password, CString animal_ID, CString request_date, CString fee);
	CString LastUser();
	std::vector<CString> CheckPendingGodfathers();
	CString CheckUserName(CString user_ID);
	CString CheckPendingAnimal(CString user_ID);
	CString CheckPendingFee(CString user_ID);
	void ChangeStatus(CString user_ID, CString animal_ID, CString status);
	CString CheckUserID(CString user_name);
	CString CheckSpeciesFee(CString species_ID);
	void SelectGodfatherDate(CString user_ID, CString animal_ID, CString start_date, CString end_date);
	CString AddYear(CString start_date);
	std::vector<CString> CheckAcceptedGodfathersIDs();
	std::vector<CString> AcceptedGodanimalsIDs(CString user_ID);
	void NewManager(CString user_ID, CString user_name, CString user_email, CString user_birth, CString user_password, CString begin_contract, CString end_contract, CString phone);
	void NewKeeper(CString user_ID, CString user_name, CString user_email, CString user_birth, CString user_password, CString begin_contract, CString end_contract, CString phone);
	void NewVeterinarian(CString user_ID, CString user_name, CString user_email, CString user_birth, CString user_password, CString begin_contract, CString end_contract, CString phone);
	void EliminateManager(CString user_ID);
	void EliminateKeeper(CString user_ID);
	void EliminateVeterinarian(CString user_ID);
	std::vector<CString> CheckEmployeeID();
	CString SimpleQuery(CString select, CString from, CString where, CString wanted);
	CString DoubleQuery(CString select, CString from, CString where1, CString wanted1, CString where2, CString wanted2);
	CString DateDiff(CString date1, CString date2);
	std::vector<CString> VectorQuery(CString select, CString from, CString where);
	void UpdateDouble(CString from, CString what, CString to, CString where1, CString wanted1, CString where2, CString wanted2);
	std::vector<CString> CheckFOODID();
	std::vector<CString> CheckMEDICINEID();
	std::vector<CString> CheckResponsibleFOODID();
	std::vector<CString> CheckResponsibleMEDICINEID();
	std::vector<CString> CheckStocksIDs();
	std::vector<CString> CheckFoodUserID();
	std::vector<CString> CheckFoodStockID();
	std::vector<CString> CheckFoodOrderDate();
	std::vector<CString> CheckFoodOrderQuantity();
	std::vector<CString> CheckFoodDescription();
	std::vector<CString> FoodDescriptions();
	std::vector<CString> CheckFoodType();
	CString LastStockID();
	CString CheckStockID(CString stock_Description);
	void NewOrderOldDescription(CString user_ID, CString stock_ID, CString order_date, CString order_quantity);
	void NewOrderNewDescription(CString stock_ID, CString stock_type, CString stock_description, CString initial_quantity, CString unit_value);
	CString CheckNewStockID(CString stock_description);
	std::vector<CString> CheckMedicineDescription();
	std::vector<CString> MedicineDescriptions();
	std::vector<CString> CheckMedicineUserID();
	std::vector<CString> CheckMedicineStockID();
	std::vector<CString> CheckMedicineOrderDate();
	std::vector<CString> CheckMedicineOrderQuantity();
	std::vector<CString> CheckMedicineType();
	void GiveWildDate(CString animal_ID, CString wild_date);
	myconnectorclassDB(void);
	virtual ~myconnectorclassDB(void);
};
