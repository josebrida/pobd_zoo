#include "stdafx.h"
#include "myconnectorclassDB.h"
#include <vector>
#include <algorithm>
using namespace std;
CString message;


myconnectorclassDB::myconnectorclassDB()
{
}


myconnectorclassDB::~myconnectorclassDB()
{
}


void myconnectorclassDB::connect()
{
	connection = mysql_init(NULL); //Initialise the instance
	connection = mysql_real_connect(connection, SERVER,
		USER, PASSWORD, DATABASE, 0, NULL, 0);
	// The command mysql_real_connect is included in the
	// libraries
	/*if (connection == NULL) {
		message.Format(_T("Unable to connect!"));
		AfxMessageBox(message);
	}
	else {
		message.Format(_T("Connection successful!"));
		AfxMessageBox(message);
	}*/
}

CString myconnectorclassDB::ReturnCurrentDate()
{
	CString value; // Create the object to receive the answer to the query
	CString query = _T("SELECT CURDATE()");
	//Create a query by combining CStrings, including an
	//input CString
	Query(query); // Pass the query. The result will be
	//stored in the result object.
	while ((row = mysql_fetch_row(result)) != NULL)
		// Method to fetch rows from result
	{
		value = CPtoUnicode(row[0], 1251);
	}
	return value;
}

CString myconnectorclassDB::CalculateDateDiff(CString date1, CString date2)
{
	CString value; // Create the object to receive the answer to the query
	CString query = _T("SELECT DATEDIFF('") + date1 + _T("', '") + date2 + _T("') AS DateDiff");
	//Create a query by combining CStrings, including an
	//input CString
	Query(query); // Pass the query. The result will be
	//stored in the result object.
	while ((row = mysql_fetch_row(result)) != NULL)
		// Method to fetch rows from result
	{
		value = CPtoUnicode(row[0], 1251);
	}
	return value;
}

CString myconnectorclassDB::CheckPassword(CString username)
{
	CString value; // Create the object to receive the answer to the query
		CString query = _T("SELECT user_password FROM user WHERE user.user_ID = '") + username + _T("'");
			//Create a query by combining CStrings, including an
			//input CString
			Query(query); // Pass the query. The result will be
			//stored in the result object.
	while ((row = mysql_fetch_row(result)) != NULL)
		// Method to fetch rows from result
	{
		value = CPtoUnicode(row[0], 1251);
	}
	return value;
}


CString myconnectorclassDB::CheckAnimalInformation(CString animal_ID)
{
	CString value = _T(""); // Create the object to receive the answer to the query
	CString query = _T("SELECT * FROM animal WHERE animal.animal_ID = '") + animal_ID + _T("'");
	//Create a query by combining CStrings, including an
	//input CString
	Query(query); // Pass the query. The result will be
	//stored in the result object.
	while ((row = mysql_fetch_row(result)) != NULL)
		// Method to fetch rows from result
	{
		for (int i = 0; i < 6; i++) {
			value = value + _T("\r\n") + CPtoUnicode(row[i], 1251);
		}
	}
	return value;
}

CString myconnectorclassDB::CheckAnimalName(CString animal_ID)
{
	CString value; // Create the object to receive the answer to the query
	CString query = _T("SELECT animal_name FROM animal WHERE animal.animal_ID = '") + animal_ID + _T("'");
	//Create a query by combining CStrings, including an
	//input CString
	Query(query); // Pass the query. The result will be
	//stored in the result object.
	while ((row = mysql_fetch_row(result)) != NULL)
		// Method to fetch rows from result
	{
		value = CPtoUnicode(row[0], 1251);
	}
	return value;
}

CString myconnectorclassDB::CheckAnimalGender(CString animal_ID)
{
	CString value; // Create the object to receive the answer to the query
	CString query = _T("SELECT gender FROM animal WHERE animal.animal_ID = '") + animal_ID + _T("'");
	//Create a query by combining CStrings, including an
	//input CString
	Query(query); // Pass the query. The result will be
	//stored in the result object.
	while ((row = mysql_fetch_row(result)) != NULL)
		// Method to fetch rows from result
	{
		value = CPtoUnicode(row[0], 1251);
	}
	return value;
}

CString myconnectorclassDB::CheckAnimalBirthDate(CString animal_ID)
{
	CString value; // Create the object to receive the answer to the query
	CString query = _T("SELECT birth_date FROM animal WHERE animal.animal_ID = '") + animal_ID + _T("'");
	//Create a query by combining CStrings, including an
	//input CString
	Query(query); // Pass the query. The result will be
	//stored in the result object.
	while ((row = mysql_fetch_row(result)) != NULL)
		// Method to fetch rows from result
	{
		value = CPtoUnicode(row[0], 1251);
	}
	return value;
}

CString myconnectorclassDB::CheckAnimalOrigin(CString animal_ID)
{
	CString value; // Create the object to receive the answer to the query
	CString query = _T("SELECT origin FROM animal WHERE animal.animal_ID = '") + animal_ID + _T("'");
	//Create a query by combining CStrings, including an
	//input CString
	Query(query); // Pass the query. The result will be
	//stored in the result object.
	while ((row = mysql_fetch_row(result)) != NULL)
		// Method to fetch rows from result
	{
		value = CPtoUnicode(row[0], 1251);
	}
	return value;
}

CString myconnectorclassDB::CheckAnimalWildDate(CString animal_ID)
{
	CString value; // Create the object to receive the answer to the query
	CString query = _T("SELECT wild_date FROM animal WHERE animal.animal_ID = '") + animal_ID + _T("'");
	//Create a query by combining CStrings, including an
	//input CString
	Query(query); // Pass the query. The result will be
	//stored in the result object.
	while ((row = mysql_fetch_row(result)) != NULL)
		// Method to fetch rows from result
	{
		value = CPtoUnicode(row[0], 1251);
	}
	return value;
}

CString myconnectorclassDB::CheckAnimalID(CString animal_name)
{
	CString value; // Create the object to receive the answer to the query
	CString query = _T("SELECT animal_ID FROM animal WHERE animal.animal_name = '") + animal_name + _T("'");
	//Create a query by combining CStrings, including an
	//input CString
	Query(query); // Pass the query. The result will be
	//stored in the result object.
	while ((row = mysql_fetch_row(result)) != NULL)
		// Method to fetch rows from result
	{
		value = CPtoUnicode(row[0], 1251);
	}
	return value;
}

std::vector<CString> myconnectorclassDB::CheckZoneAnimal(CString zone_ID)
{
	vector<CString> value; // Create the object to receive the answer to the query
	CString value_int;
	CString query = _T("SELECT * FROM lives WHERE zones_ID = '") + zone_ID + _T("'");
	//Create a query by combining CStrings
	Query(query); // Pass the query. The result will be
	//stored in the result object.
	while ((row = mysql_fetch_row(result)) != NULL)
		// Method to fetch rows from result
	{
		value_int = CPtoUnicode(row[0], 1251);
		value.push_back(value_int);
	}
	return value;
}

std::vector<CString> myconnectorclassDB::CheckAvailableAnimalNames()
{
	vector<CString> value; // Create the object to receive the answer to the query
	CString value_int;
	CString query = _T("SELECT animal_name FROM animal WHERE wild_date is NULL");
	//Create a query by combining CStrings
	Query(query); // Pass the query. The result will be
	//stored in the result object.
	while ((row = mysql_fetch_row(result)) != NULL)
		// Method to fetch rows from result
	{
		value_int = CPtoUnicode(row[0], 1251);
		value.push_back(value_int);
	}
	return value;
}

std::vector<CString> myconnectorclassDB::CheckAvailableAnimalIDs()
{
	vector<CString> value; // Create the object to receive the answer to the query
	CString value_int;
	CString query = _T("SELECT animal_ID FROM animal WHERE wild_date is NULL");
	//Create a query by combining CStrings
	Query(query); // Pass the query. The result will be
	//stored in the result object.
	while ((row = mysql_fetch_row(result)) != NULL)
		// Method to fetch rows from result
	{
		value_int = CPtoUnicode(row[0], 1251);
		value.push_back(value_int);
	}
	return value;
}

CString myconnectorclassDB::CheckSpecieID(CString animal_ID)
{
	CString value; // Create the object to receive the answer to the query
	CString query = _T("SELECT species_ID FROM belongs WHERE animal_ID = '") + animal_ID + _T("'");
	//Create a query by combining CStrings
	Query(query); // Pass the query. The result will be
	//stored in the result object.
	while ((row = mysql_fetch_row(result)) != NULL)
		// Method to fetch rows from result
	{
		value = CPtoUnicode(row[0], 1251);
	}
	return value;
}

CString myconnectorclassDB::CheckSpecieName(CString species_ID)
{
	CString value; // Create the object to receive the answer to the query
	CString query = _T("SELECT species_name FROM species WHERE species_ID = '") + species_ID + _T("'");
	//Create a query by combining CStrings
	Query(query); // Pass the query. The result will be
	//stored in the result object.
	while ((row = mysql_fetch_row(result)) != NULL)
		// Method to fetch rows from result
	{
		value = CPtoUnicode(row[0], 1251);
	}
	return value;
}

CString myconnectorclassDB::CheckBirth(CString animal_ID)
{
	CString value; // Create the object to receive the answer to the query
	CString query = _T("SELECT birth_date FROM animal WHERE animal_ID = '") + animal_ID + _T("'");
	//Create a query by combining CStrings
	Query(query); // Pass the query. The result will be
	//stored in the result object.
	while ((row = mysql_fetch_row(result)) != NULL)
		// Method to fetch rows from result
	{
		value = CPtoUnicode(row[0], 1251);
	}
	return value;
}


std::vector<CString> myconnectorclassDB::CheckKeeperIDs()
{
	vector<CString> value; // Create the object to receive the answer to the query
	CString value_int;
	CString query = _T("SELECT user_ID FROM keeper");
	//Create a query by combining CStrings
	Query(query); // Pass the query. The result will be
	//stored in the result object.
	while ((row = mysql_fetch_row(result)) != NULL)
		// Method to fetch rows from result
	{
		value_int = CPtoUnicode(row[0], 1251);
		value.push_back(value_int);
	}
	return value;
}

std::vector<CString> myconnectorclassDB::CheckManagerIDs()
{
	vector<CString> value; // Create the object to receive the answer to the query
	CString value_int;
	CString query = _T("SELECT user_ID FROM manager");
	//Create a query by combining CStrings
	Query(query); // Pass the query. The result will be
	//stored in the result object.
	while ((row = mysql_fetch_row(result)) != NULL)
		// Method to fetch rows from result
	{
		value_int = CPtoUnicode(row[0], 1251);
		value.push_back(value_int);
	}
	return value;
}

std::vector<CString> myconnectorclassDB::CheckVeterinarianIDs()
{
	vector<CString> value; // Create the object to receive the answer to the query
	CString value_int;
	CString query = _T("SELECT user_ID FROM veterinarian");
	//Create a query by combining CStrings
	Query(query); // Pass the query. The result will be
	//stored in the result object.
	while ((row = mysql_fetch_row(result)) != NULL)
		// Method to fetch rows from result
	{
		value_int = CPtoUnicode(row[0], 1251);
		value.push_back(value_int);
	}
	return value;
}

std::vector<CString> myconnectorclassDB::CheckVisitorIDs()
{
	vector<CString> value; // Create the object to receive the answer to the query
	CString value_int;
	CString query = _T("SELECT user_ID FROM visitor");
	//Create a query by combining CStrings
	Query(query); // Pass the query. The result will be
	//stored in the result object.
	while ((row = mysql_fetch_row(result)) != NULL)
		// Method to fetch rows from result
	{
		value_int = CPtoUnicode(row[0], 1251);
		value.push_back(value_int);
	}
	return value;
}

CString myconnectorclassDB::LastUser()
{
	CString value; // Create the object to receive the answer to the query
	CString query = _T("SELECT max(user_ID) FROM user");
	//Create a query by combining CStrings
	Query(query); // Pass the query. The result will be
	//stored in the result object.
	while ((row = mysql_fetch_row(result)) != NULL)
		// Method to fetch rows from result
	{
		value = CPtoUnicode(row[0], 1251);
	}
	return value;
}

void myconnectorclassDB::ApplyGodfather(CString user_ID, CString user_name, CString user_email, CString user_birth, CString user_password, CString animal_ID, CString request_date, CString fee)
{
	CString query1 = _T("INSERT INTO user VALUE (") + user_ID + _T(", '") + user_name + _T("', '") + user_birth + _T("', '") + user_password + _T("', '") + user_email + _T("');");
	//Create a query by combining CStrings
	Query(query1); // Pass the query. The result will be
	//stored in the result object.
	CString query2 = _T("INSERT INTO visitor VALUE (") + user_ID + _T(");");
	//Create a query by combining CStrings
	Query(query2); // Pass the query. The result will be
	//stored in the result object.
	CString query3 = _T("INSERT INTO godfather VALUE (") + animal_ID + _T(", ") +  user_ID + _T(", 'Pending', '") + request_date + _T("', '") + fee + _T("', Null, Null);");
	//Create a query by combining CStrings
	Query(query3); // Pass the query. The result will be
	//stored in the result object.
}

std::vector<CString> myconnectorclassDB::CheckPendingGodfathers()
{
	vector<CString> value; // Create the object to receive the answer to the query
	CString value_int;
	CString query = _T("SELECT user_ID FROM godfather WHERE status = 'Pending'");
	//Create a query by combining CStrings
	Query(query); // Pass the query. The result will be
	//stored in the result object.
	while ((row = mysql_fetch_row(result)) != NULL)
		// Method to fetch rows from result
	{
		value_int = CPtoUnicode(row[0], 1251);
		value.push_back(value_int);
	}
	return value;
}

CString myconnectorclassDB::CheckUserName(CString user_ID)
{
	CString value; // Create the object to receive the answer to the query
	CString query = _T("SELECT user_name FROM user WHERE user_ID = '") + user_ID + _T("'");
	//Create a query by combining CStrings
	Query(query); // Pass the query. The result will be
	//stored in the result object.
	while ((row = mysql_fetch_row(result)) != NULL)
		// Method to fetch rows from result
	{
		value = CPtoUnicode(row[0], 1251);
	}
	return value;
}

CString myconnectorclassDB::CheckPendingAnimal(CString user_ID)
{
	CString value; // Create the object to receive the answer to the query
	CString query = _T("SELECT animal_ID FROM godfather WHERE user_ID = '") + user_ID + _T("'");
	//Create a query by combining CStrings
	Query(query); // Pass the query. The result will be
	//stored in the result object.
	while ((row = mysql_fetch_row(result)) != NULL)
		// Method to fetch rows from result
	{
		value = CPtoUnicode(row[0], 1251);
	}
	return value;
}

CString myconnectorclassDB::CheckPendingFee(CString user_ID)
{
	CString value; // Create the object to receive the answer to the query
	CString query = _T("SELECT fee FROM godfather WHERE user_ID = '") + user_ID + _T("'");
	//Create a query by combining CStrings
	Query(query); // Pass the query. The result will be
	//stored in the result object.
	while ((row = mysql_fetch_row(result)) != NULL)
		// Method to fetch rows from result
	{
		value = CPtoUnicode(row[0], 1251);
	}
	return value;
}

void myconnectorclassDB::ChangeStatus(CString user_ID, CString status)
{
	CString query = _T("UPDATE godfather SET status = '") + status + _T("' WHERE user_ID = '") + user_ID + _T("'");
	//Create a query by combining CStrings
	Query(query); // Pass the query. The result will be
	//stored in the result object.
	//while ((row = mysql_fetch_row(result)) != NULL)
		// Method to fetch rows from result
	//{
	//	value = CPtoUnicode(row[0], 1251);
	//}
}

CString myconnectorclassDB::CheckUserID(CString user_name)
{
	CString value;
	CString query = _T("SELECT user_ID FROM user WHERE user_name = '") + user_name + _T("'");
	//Create a query by combining CStrings
	Query(query); // Pass the query. The result will be
	//stored in the result object.
	while ((row = mysql_fetch_row(result)) != NULL)
		// Method to fetch rows from result
	{
		value = CPtoUnicode(row[0], 1251);
	}
	return value;
}

CString myconnectorclassDB::CheckSpeciesFee(CString species_ID)
{
	CString value;
	CString query = _T("SELECT base_fee FROM species WHERE species_ID = '") + species_ID + _T("'");
	//Create a query by combining CStrings
	Query(query); // Pass the query. The result will be
	//stored in the result object.
	while ((row = mysql_fetch_row(result)) != NULL)
		// Method to fetch rows from result
	{
		value = CPtoUnicode(row[0], 1251);
	}
	return value;
}

void myconnectorclassDB::SelectGodfatherDate(CString user_ID, CString start_date, CString end_date)
{
	CString query1 = _T("UPDATE godfather SET start_date  = '") + start_date + _T("' WHERE user_ID = '") + user_ID + _T("'");
	//Create a query by combining CStrings
	Query(query1); // Pass the query. The result will be
	//stored in the result object.
	/*while ((row = mysql_fetch_row(result)) != NULL)
		// Method to fetch rows from result
	{
		value = CPtoUnicode(row[0], 1251);
	}
	return value;*/
	CString query2 = _T("UPDATE godfather SET end_date  = '") + end_date + _T("' WHERE user_ID = '") + user_ID + _T("'");
	//Create a query by combining CStrings
	Query(query2);
}

CString myconnectorclassDB::AddYear(CString start_date)
{
	CString value;
	CString query = _T("SELECT ADDDATE('") + start_date + _T("', 365)");
	//Create a query by combining CStrings
	Query(query); // Pass the query. The result will be
	//stored in the result object.
	while ((row = mysql_fetch_row(result)) != NULL)
		// Method to fetch rows from result
	{
		value = CPtoUnicode(row[0], 1251);
	}
	return value;
}

std::vector<CString> myconnectorclassDB::CheckAcceptedGodfathersIDs()
{
	vector<CString> value; // Create the object to receive the answer to the query
	CString value_int;
	CString query = _T("SELECT user_ID FROM godfather WHERE status = 'Approved'");
	//Create a query by combining CStrings
	Query(query); // Pass the query. The result will be
	//stored in the result object.
	while ((row = mysql_fetch_row(result)) != NULL)
		// Method to fetch rows from result
	{
		value_int = CPtoUnicode(row[0], 1251);
		value.push_back(value_int);
	}
	return value;
}

std::vector<CString> myconnectorclassDB::CheckEmployeeID()
{
	vector<CString> value; // Create the object to receive the answer to the query
	CString value_int;
	CString query = _T("SELECT user_ID FROM employee");
	//Create a query by combining CStrings
	Query(query); // Pass the query. The result will be
	//stored in the result object.
	while ((row = mysql_fetch_row(result)) != NULL)
		// Method to fetch rows from result
	{
		value_int = CPtoUnicode(row[0], 1251);
		value.push_back(value_int);
	}
	return value;
}

void myconnectorclassDB::NewKeeper(CString user_ID, CString user_name, CString user_email, CString user_birth, CString user_password, CString begin_contract, CString end_contract, CString phone)
{
	CString query1 = _T("INSERT INTO user VALUE (") + user_ID + _T(", '") + user_name + _T("', '") + user_birth + _T("', '") + user_password + _T("', '") + user_email + _T("');");
	//Create a query by combining CStrings
	Query(query1); // Pass the query. The result will be
	//stored in the result object.
	CString query2 = _T("INSERT INTO employee VALUE (") + user_ID + _T(", '") + begin_contract + _T("', '") + end_contract + _T("', '") + phone + _T("');");
	//Create a query by combining CStrings
	Query(query2); // Pass the query. The result will be
	//stored in the result object.
	CString query3 = _T("INSERT INTO keeper VALUE (") + user_ID + _T(");");
	//Create a query by combining CStrings
	Query(query3); // Pass the query. The result will be
	//stored in the result object.
}


void myconnectorclassDB::NewManager(CString user_ID, CString user_name, CString user_email, CString user_birth, CString user_password, CString begin_contract, CString end_contract, CString phone)
{
	CString query1 = _T("INSERT INTO user VALUE (") + user_ID + _T(", '") + user_name + _T("', '") + user_birth + _T("', '") + user_password + _T("', '") + user_email + _T("');");
	//Create a query by combining CStrings
	Query(query1); // Pass the query. The result will be
	//stored in the result object.
	CString query2 = _T("INSERT INTO employee VALUE (") + user_ID + _T(", '") + begin_contract + _T("', '") + end_contract + _T("', '") + phone + _T("');");
	//Create a query by combining CStrings
	Query(query2); // Pass the query. The result will be
	//stored in the result object.
	CString query3 = _T("INSERT INTO manager VALUE (") + user_ID + _T(");");
	//Create a query by combining CStrings
	Query(query3); // Pass the query. The result will be
	//stored in the result object.
}

void myconnectorclassDB::NewVeterinarian(CString user_ID, CString user_name, CString user_email, CString user_birth, CString user_password, CString begin_contract, CString end_contract, CString phone)
{
	CString query1 = _T("INSERT INTO user VALUE (") + user_ID + _T(", '") + user_name + _T("', '") + user_birth + _T("', '") + user_password + _T("', '") + user_email + _T("');");
	//Create a query by combining CStrings
	Query(query1); // Pass the query. The result will be
	//stored in the result object.
	CString query2 = _T("INSERT INTO employee VALUE (") + user_ID + _T(", '") + begin_contract + _T("', '") + end_contract + _T("', '") + phone + _T("');");
	//Create a query by combining CStrings
	Query(query2); // Pass the query. The result will be
	//stored in the result object.
	CString query3 = _T("INSERT INTO veterinarian VALUE (") + user_ID + _T(");");
	//Create a query by combining CStrings
	Query(query3); // Pass the query. The result will be
	//stored in the result object.
}







void myconnectorclassDB::EliminateManager(CString user_ID)
{
	CString query1 = _T("DELETE FROM manager WHERE user_ID = '") + user_ID + ("'");
	//Create a query by combining CStrings
	Query(query1); // Pass the query. The result will be
	//stored in the result object.
	CString query2 = _T("DELETE FROM employee WHERE user_ID = '") + user_ID + ("'");
	//Create a query by combining CStrings
	Query(query2); // Pass the query. The result will be
	//stored in the result object.
	CString query3 = _T("DELETE FROM user WHERE user_ID = '") + user_ID + ("'");
	//Create a query by combining CStrings
	Query(query3); // Pass the query. The result will be
	//stored in the result object.

}

void myconnectorclassDB::EliminateKeeper(CString user_ID)
{
	CString query0 = _T("DELETE FROM assigned WHERE user_ID = '") + user_ID + ("'");
	//Create a query by combining CStrings
	Query(query0); // Pass the query. The result will be
	//stored in the result object.
	CString query1 = _T("DELETE FROM keeper WHERE user_ID = '") + user_ID + ("'");
	//Create a query by combining CStrings
	Query(query1); // Pass the query. The result will be
	//stored in the result object.
	CString query2 = _T("DELETE FROM employee WHERE user_ID = '") + user_ID + ("'");
	//Create a query by combining CStrings
	Query(query2); // Pass the query. The result will be
	//stored in the result object.
	CString query3 = _T("DELETE FROM user WHERE user_ID = '") + user_ID + ("'");
	//Create a query by combining CStrings
	Query(query3); // Pass the query. The result will be
	//stored in the result object.

}


void myconnectorclassDB::EliminateVeterinarian(CString user_ID)
{
	CString query0 = _T("DELETE FROM medical_record WHERE user_ID = '") + user_ID + ("'");
	//Create a query by combining CStrings
	Query(query0); // Pass the query. The result will be
	//stored in the result object.
	CString query1 = _T("DELETE FROM veterinarian WHERE user_ID = '") + user_ID + ("'");
	//Create a query by combining CStrings
	Query(query1); // Pass the query. The result will be
	//stored in the result object.
	CString query2 = _T("DELETE FROM employee WHERE user_ID = '") + user_ID + ("'");
	//Create a query by combining CStrings
	Query(query2); // Pass the query. The result will be
	//stored in the result object.
	CString query3 = _T("DELETE FROM user WHERE user_ID = '") + user_ID + ("'");
	//Create a query by combining CStrings
	Query(query3); // Pass the query. The result will be
	//stored in the result object.

}







void myconnectorclassDB::Query(CString query)
{
	wchar_t *p = query.GetBuffer();
	char bufUTF8[MAX_PATH];
	WideCharToMultiByte(CP_UTF8, 0, p, -1, bufUTF8,
		sizeof(bufUTF8), NULL, NULL);
	/* MySQL uses a different character set from MFC's in
	VS. A weird conversion has to be done. The good newis
	you only have to copy and paste this code once. */
	mysql_query(connection, bufUTF8); // Send a query
	result = mysql_store_result(connection); // Store the
	//result
}

CString myconnectorclassDB::CPtoUnicode(const char* CPString, UINT
	CodePage)
{
	CString retValue;
	int len = MultiByteToWideChar(CodePage, 0, CPString, -1, NULL, 0);
	if (len == 0) { return retValue; }
	LPWSTR buffer = retValue.GetBuffer(len);
	MultiByteToWideChar(CodePage, 0, CPString, -1, buffer, len);
	retValue.ReleaseBuffer();
	return retValue;
}

