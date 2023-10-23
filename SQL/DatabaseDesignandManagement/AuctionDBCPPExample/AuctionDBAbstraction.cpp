#include <iostream> 
#include <vector> 
 
#include "AuctionDBAbstraction.h" 
 
using namespace std; 
 
AuctionDBAbstraction::AuctionDBAbstraction(string pathToFile) 
	: DBAbstraction(pathToFile) //<- call the base class constructor 
{ 
    //create the auction tables 
	createItemsTable(); 
	createAuctionSiteUsersTable(); 
	createBidsTable(); 
} 
//-- 
void AuctionDBAbstraction::createItemsTable() 
{ 
	//Items (id, itemName, startingBid, sellerUserId) 
	string sql = "CREATE TABLE IF NOT EXISTS Items (id INTEGER PRIMARY KEY NOT NULL, itemName TEXT, startingBid DOUBLE, sellerUserId INTEGER);"; 
 
	//execute the query to create the table 
	if (!executeQueryNoResultsBack(sql)) 
	{ 
		cout << "Error creating Items table" << endl; 
	} 
} 
//-- 
void AuctionDBAbstraction::createAuctionSiteUsersTable() 
{ 
	//AuctionSiteUsers (id, firstName, lastName, email) 
	string sql = "CREATE TABLE IF NOT EXISTS AuctionSiteUsers (id INTEGER PRIMARY KEY NOT NULL, firstName TEXT, lastName TEXT, email TEXT);"; 
 
	//execute the query to create the table 
	if (!executeQueryNoResultsBack(sql)) 
	{ 
		cout << "Error creating AuctionSiteUsers table" << endl; 
	} 
} 
//-- 
void AuctionDBAbstraction::createBidsTable() 
{ 
	//Bids (id, bidAmount, itemId, bidderId) 
	string sql = "CREATE TABLE IF NOT EXISTS Bids (id INTEGER PRIMARY KEY NOT NULL, bidAmount DOUBLE, itemId INTEGER, bidderID INTEGER);"; 
 
	//execute the query to create the table 
	if (!executeQueryNoResultsBack(sql)) 
	{ 
		cout << "Error creating Bids table" << endl; 
	} 
} 
//-- 
void AuctionDBAbstraction::insertAuctionSiteUser(string firstName, string lastName, string email) 
{ 
	//query to insert a user 
	string sql = "INSERT INTO AuctionSiteUsers (firstName, lastName, email) VALUES (?, ?, ?);"; 
 
	//create a statement pointer 
	sqlite3_stmt* myStatement; 
 
	//create the statement object using the prepare() 
	int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL); 
 
	//check to see if the prepared statement was created 
	if (statusOfPrep == SQLITE_OK) 
	{ 
		//add parameters 
		sqlite3_bind_text(myStatement, 1, firstName.c_str(), -1, SQLITE_STATIC); 
		sqlite3_bind_text(myStatement, 2, lastName.c_str(), -1, SQLITE_STATIC); 
		sqlite3_bind_text(myStatement, 3, email.c_str(), -1, SQLITE_STATIC); 
 
		//execute the query to insert a new user 
		if (!executeQueryNoResultsBack(myStatement)) 
		{ 
			cout << "Error inserting into AuctionSiteUsers" << endl; 
		} 
	} 
} 
//-- 
void AuctionDBAbstraction::insertItem(string itemName, double startingBid, int sellerUserId) 
{ 
	//Items (id, itemName, startingBid, sellerUserId) 
 
	//query to insert an item 
	string sql = "INSERT INTO Items (itemName, startingBid, sellerUserId) VALUES (?, ?, ?);"; 
 
	//create a statement pointer 
	sqlite3_stmt* myStatement; 
 
	//create the statement object using the prepare() 
	int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL); 
 
	//check to see if the prepared statement was created 
	if (statusOfPrep == SQLITE_OK) 
	{ 
		//bind parameters 
		sqlite3_bind_text(myStatement, 1, itemName.c_str(), -1, SQLITE_STATIC); 
		sqlite3_bind_double(myStatement, 2, startingBid); 
		sqlite3_bind_int(myStatement, 3, sellerUserId); 
 
		//execute the query to insert a new item 
		if (!executeQueryNoResultsBack(myStatement)) 
		{ 
			cout << "Error inserting into Items" << endl; 
		} 
	} 
} 
//-- 
void AuctionDBAbstraction::insertBid(int itemId, int bidderId, double bidAmount) 
{ 
	//Bids (id, bidAmount, itemId, bidderId) 
 
	//query to insert a bid 
	string sql = "INSERT INTO Bids (bidAmount, itemId, bidderId) VALUES (?, ?, ?);"; 
 
	//create a statement pointer 
	sqlite3_stmt* myStatement; 
 
	//create the statement object using the prepare() 
	int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL); 
 
	//check to see if the prepared statement was created 
	if (statusOfPrep == SQLITE_OK) 
	{ 
		//bind the parameters 
		sqlite3_bind_double(myStatement, 1, bidAmount); 
		sqlite3_bind_int(myStatement, 2, itemId); 
		sqlite3_bind_int(myStatement, 3, bidderId); 
 
		//execute the query to insert a new bid 
		if (!executeQueryNoResultsBack(myStatement)) 
		{ 
			cout << "Error inserting into Bids" << endl; 
		} 
	} 
} 
//-- 
int AuctionDBAbstraction::chooseAuctionSiteUser() 
{ 
	//holds the selected user id (-1 means the user entered a bad option) 
	int userId = -1; 
 
	//holds all of the user ids from the database 
	vector < int > userIds; 
 
	//query to get all of the users 
	string sql = "SELECT id, firstName, lastName, email FROM AuctionSiteUsers;"; 
 
	//create a statement pointer 
	sqlite3_stmt* myStatement; 
 
	//get a statement to iterate through 
	if (prepareQueryWithResults(sql, myStatement)) 
	{ 
		//get a row from the query 
		int statusOfStep = sqlite3_step(myStatement); 
 
		//for printing an option number 
		int numeral = 1; 
 
		//while there are more rows 
		while (statusOfStep == SQLITE_ROW) 
		{ 
			//get the user id from the row 
			int id = sqlite3_column_int(myStatement, 0); 
			//add the user id 
			userIds.push_back(id); 
 
			//get name and email 
			string firstName((char*)sqlite3_column_text(myStatement, 1)); 
			string lastName((char*)sqlite3_column_text(myStatement, 2)); 
			string email((char*)sqlite3_column_text(myStatement, 3)); 
 
			//print out the user info 
			cout << numeral << ". " << firstName << " " << lastName << " (" << email << ")" << endl; 
			numeral++; 
 
			//get the next row 
			statusOfStep = sqlite3_step(myStatement); 
		} 
 
		//clean up and destroy the statement 
		sqlite3_finalize(myStatement); 
	} 
 
	//select a user 
	int option; 
	cout << "Enter in the user: "; 
	cin >> option; 
 
	//if the user entered a valid option 
	if (option >= 1 && option <= userIds.size()) 
	{ 
		//get the id of the user 
		userId = userIds[option - 1]; 
	} 
 
	return userId; 
} 
//-- 
int AuctionDBAbstraction::chooseItem() 
{ 
	//holds the selected item id (-1 means the user entered a bad option) 
	int itemId = -1; 
 
	//holds all of the item ids from the database 
	vector < int > itemIds; 
 
	//query to get all of the items 
	string sql = "SELECT Items.id, Items.itemName FROM Items;"; 
 
	//create a statement pointer 
	sqlite3_stmt* myStatement; 
 
	//get a statement to iterate through 
	if (prepareQueryWithResults(sql, myStatement)) 
	{ 
		//get a row from the query 
		int statusOfStep = sqlite3_step(myStatement); 
 
		//for printing an option number 
		int numeral = 1; 
 
		//while there are more rows 
		while (statusOfStep == SQLITE_ROW) 
		{ 
			//get the item id from the row 
			int id = sqlite3_column_int(myStatement, 0); 
			//add the item id 
			itemIds.push_back(id); 
 
			//get item name 
			string itemName((char*)sqlite3_column_text(myStatement, 1)); 
 
			//print out the item info 
			cout << numeral << ". " << itemName << endl; 
			numeral++; 
 
			//get the next row 
			statusOfStep = sqlite3_step(myStatement); 
		} 
 
		//clean up and destroy the statement 
		sqlite3_finalize(myStatement); 
	} 
 
	//select a user 
	int option; 
	cout << "Enter in the item: "; 
	cin >> option; 
 
	//if the user entered a valid option 
	if (option >= 1 && option <= itemIds.size()) 
	{ 
		//get the id of the user 
		itemId = itemIds[option - 1]; 
	} 
 
	return itemId; 
} 
//-- 
double AuctionDBAbstraction::chooseBidAmount(int itemId) 
{ 
	double bid; 
 
	//get the minimum starting bid 
	float startingBid = getStartingBid(itemId); 
	//get the highest bid so far 
	float highestBid = getHighestBidSoFar(itemId); 
 
	//if there is at least one bid 
	if (highestBid >= startingBid) 
	{ 
		//prompt for a higher bud 
		cout << "Enter in a bid that is greater than $" << highestBid << ": "; 
		cin >> bid; 
 
		//if the user entered in a low bid 
		if (bid <= highestBid) 
		{ 
			bid = -1.0; 
		} 
	} 
	else //now bids, start with the minimum 
	{ 
		cout << "Enter in a bid that is at least $" << startingBid << ": "; 
		cin >> bid; 
 
		//bad bid 
		if (bid < startingBid) 
		{ 
			bid = -1.0; 
		} 
	} 
 
	return bid; 
} 
//-- 
double AuctionDBAbstraction::getStartingBid(int itemId) 
{ 
	float startingBid = 0.0; 
 
	//query to get the starting bid 
	string sql = "SELECT Items.startingBid FROM Items WHERE Items.id = ?;"; 
 
	//create a statement pointer 
	sqlite3_stmt* myStatement; 
 
	//get a statement to iterate through 
	if (prepareQueryWithResults(sql, myStatement)) 
	{ 
		//bind the parameter 
		sqlite3_bind_int(myStatement, 1, itemId); 
 
		//get a row from the query 
		int statusOfStep = sqlite3_step(myStatement); 
 
		//if there is a row 
		if (statusOfStep == SQLITE_ROW) 
		{ 
			//get the starting bid 
			startingBid = sqlite3_column_double(myStatement, 0); 
		} 
 
		//clean up and destroy the statement 
		sqlite3_finalize(myStatement); 
	} 
	return startingBid; 
} 
//-- 
double AuctionDBAbstraction::getHighestBidSoFar(int itemId) 
{ 
	float highestBid = 0.0; 
 
	//query to get the highest bid 
	string sql = "SELECT Bids.bidAmount FROM Bids WHERE Bids.itemId = ? ORDER BY Bids.bidAmount DESC;"; 
 
	//create a statement pointer 
	sqlite3_stmt* myStatement; 
 
	//get a statement to iterate through 
	if (prepareQueryWithResults(sql, myStatement)) 
	{ 
		//bind the parameter 
		sqlite3_bind_int(myStatement, 1, itemId); 
 
		//get a row from the query 
		int statusOfStep = sqlite3_step(myStatement); 
 
		//if there is a row 
		if (statusOfStep == SQLITE_ROW) 
		{ 
			//get the highest bid 
			highestBid = sqlite3_column_double(myStatement, 0); 
		} 
 
		//clean up and destroy the statement 
		sqlite3_finalize(myStatement); 
	} 
 
	return highestBid; 
} 
//-- 
void AuctionDBAbstraction::printAllItemsWithBids() 
{ 
	//query to get all of the items that have a bid 
	string sql = "SELECT Items.itemName, MAX(Bids.bidAmount) FROM Items, Bids WHERE Items.id = Bids.itemId GROUP BY Items.id, Items.itemName;"; 
 
	//create a statement pointer 
	sqlite3_stmt* myStatement; 
 
	//get a statement to iterate through 
	if (prepareQueryWithResults(sql, myStatement)) 
	{ 
		//get a row from the query 
		int statusOfStep = sqlite3_step(myStatement); 
 
		//for printing an option number 
		int numeral = 1; 
 
		//while there are more rows 
		while (statusOfStep == SQLITE_ROW) 
		{ 
			//get item name 
			string itemName((char*)sqlite3_column_text(myStatement, 0)); 
			//get the highest bid so far 
			double highestBid = sqlite3_column_double(myStatement, 1); 
 
			//print out the item info 
			cout << numeral << ". " << itemName << " $" << highestBid << endl; 
			numeral++; 
 
			//get the next row 
			statusOfStep = sqlite3_step(myStatement); 
		} 
 
		//clean up and destroy the statement 
		sqlite3_finalize(myStatement); 
	} 
}