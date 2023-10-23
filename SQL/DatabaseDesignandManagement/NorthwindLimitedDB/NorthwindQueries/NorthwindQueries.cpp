// NorthwindQueries.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "sqlite3.h"
//#include "sqlite3ext.h"

using namespace std;

void QueryOne(sqlite3* db) {
/*SELECT COUNT(Customers.CustomerID)
FROM Customers
WHERE Customers.Country = "UK"
OR Customers.Country = "USA"
OR Customers.Country = "Spain"*/
	sqlite3_stmt* myStatement;
	int statusOfPrep = sqlite3_prepare_v2(db, "SELECT COUNT(Customers.CustomerID) FROM Customers WHERE Customers.Country = \"UK\" OR Customers.Country = \"USA\" OR Customers.Country = \"Spain\"", -1, &myStatement, NULL);

	if (statusOfPrep == SQLITE_OK)
	{
		int statusOfStep = sqlite3_step(myStatement);

		cout << "How many customers are in the UK, USA, and Spain?\n\n";

		while (statusOfStep == SQLITE_ROW)
		{
			int count = sqlite3_column_int(myStatement, 0);

			cout << "Number of Customers: " << count << "\n";

			statusOfStep = sqlite3_step(myStatement);
		}

		cout << "\nSQL: SELECT COUNT(Customers.CustomerID) \nFROM Customers WHERE Customers.Country = \"UK\" \nOR Customers.Country = \"USA\" \nOR Customers.Country = \"Spain\"\n\n";

		sqlite3_finalize(myStatement);
	}
	else
	{
		cout << "Problem creating a prepared statement" << endl;
	}

}

void QueryTwo(sqlite3* db) {
/*SELECT Suppliers.CompanyName, Suppliers.Phone
FROM Suppliers
WHERE Suppliers.Phone LIKE "(514%"*/
	sqlite3_stmt* myStatement;
	int statusOfPrep = sqlite3_prepare_v2(db, "SELECT Suppliers.CompanyName, Suppliers.Phone FROM Suppliers WHERE Suppliers.Phone LIKE \"(514%\"", -1, &myStatement, NULL);

	if (statusOfPrep == SQLITE_OK)
	{
		int statusOfStep = sqlite3_step(myStatement);

		cout << "What are the names and phone numbers of suppliers who are in the 514 area code?\n\n";

		while (statusOfStep == SQLITE_ROW)
		{
			string compName = (char*)sqlite3_column_text(myStatement, 0);
			string compPhone = (char*)sqlite3_column_text(myStatement, 1);

			cout << "Supplier Name: " << compName << "\n";
			cout << "Supplier Phone: " << compPhone << "\n";

			statusOfStep = sqlite3_step(myStatement);
		}

		cout << "\nSQL: SELECT Suppliers.CompanyName, Suppliers.Phone \nFROM Suppliers \nWHERE Suppliers.Phone LIKE \"(514%\"\n";

		sqlite3_finalize(myStatement);
	}
	else
	{
		cout << "Problem creating a prepared statement" << endl;
	}

}

void QueryThree(sqlite3* db) {
/*SELECT COUNT(Products.ProductID)
FROM Products
WHERE Products.UnitsInStock >= Products.UnitsOnOrder*/
	sqlite3_stmt* myStatement;
	int statusOfPrep = sqlite3_prepare_v2(db, "SELECT COUNT(Products.ProductID)	FROM Products WHERE Products.UnitsInStock >= Products.UnitsOnOrder", -1, &myStatement, NULL);

	if (statusOfPrep == SQLITE_OK)
	{
		int statusOfStep = sqlite3_step(myStatement);

		cout << "How many products have a greater value of in-stock items compared to the value of items on order?\n\n";

		while (statusOfStep == SQLITE_ROW)
		{
			int count = sqlite3_column_int(myStatement, 0);

			cout << "Number of products with a greater value of in-stock than on order: " << count << "\n";

			statusOfStep = sqlite3_step(myStatement);
		}

		cout << "\nSQL: SELECT COUNT(Products.ProductID) \nFROM Products \nWHERE Products.UnitsInStock >= Products.UnitsOnOrder\n";

		sqlite3_finalize(myStatement);
	}
	else
	{
		cout << "Problem creating a prepared statement" << endl;
	}

}

void QueryFour(sqlite3* db) {
/*SELECT Products.ProductName
FROM Products, Orders, \"Order Details\"
WHERE Orders.OrderID = \"Order Details\".OrderID
AND \"Order Details\".ProductID = Products.ProductID
AND Orders.OrderID = "10275"*/
	sqlite3_stmt* myStatement;
	int statusOfPrep = sqlite3_prepare_v2(db, "SELECT Products.ProductName FROM Products, Orders, \"Order Details\" WHERE Orders.OrderID = \"Order Details\".OrderID AND \"Order Details\".ProductID = Products.ProductID AND Orders.OrderID = \"10275\"", -1, &myStatement, NULL);

	if (statusOfPrep == SQLITE_OK)
	{
		int statusOfStep = sqlite3_step(myStatement);

		cout << "What are the names of the products in order #10275?\n\n";

		while (statusOfStep == SQLITE_ROW)
		{
			string productName = (char *)sqlite3_column_text(myStatement, 0);

			cout << "Product name: " << productName << "\n";

			statusOfStep = sqlite3_step(myStatement);
		}

		cout << "\nSQL: SELECT Products.ProductName FROM Products, Orders, \"Order Details\" WHERE Orders.OrderID = \"Order Details\".OrderID AND \"Order Details\".ProductID = Products.ProductID AND Orders.OrderID = \"10275\"\n";

		sqlite3_finalize(myStatement);
	}
	else
	{
		cout << "Problem creating a prepared statement" << endl;
	}

}

void QueryFive(sqlite3* db) {
/*SELECT Managers.FirstName, Managers.LastName, COUNT(*)
FROM Employees AS Managers, Employees AS Worker
WHERE Managers.EmployeeID = Worker.ReportsTo
GROUP BY Worker.ReportsTo, Managers.FirstName, Managers.LastName*/
	sqlite3_stmt* myStatement;
	int statusOfPrep = sqlite3_prepare_v2(db, "SELECT Managers.FirstName, Managers.LastName, COUNT(*) FROM Employees AS Managers, Employees AS Worker WHERE Managers.EmployeeID = Worker.ReportsTo GROUP BY Worker.ReportsTo, Managers.FirstName, Managers.LastName", -1, &myStatement, NULL);

	if (statusOfPrep == SQLITE_OK)
	{
		int statusOfStep = sqlite3_step(myStatement);

		cout << "Who are all the employees who manage others and how many people do they manage?\n\n";

		while (statusOfStep == SQLITE_ROW)
		{
			string firstName = (char*)sqlite3_column_text(myStatement, 0);
			string lastName = (char*)sqlite3_column_text(myStatement, 1);
			int count = sqlite3_column_int(myStatement, 2);

			cout << firstName << " ";
			cout << lastName << ": ";
			cout << count << "\n";

			statusOfStep = sqlite3_step(myStatement);
		}

		cout << "\nSQL: SELECT Managers.FirstName, Managers.LastName, COUNT(*) \nFROM Employees AS Managers, Employees AS Worker \nWHERE Managers.EmployeeID = Worker.ReportsTo \nGROUP BY Worker.ReportsTo, Managers.FirstName, Managers.LastName\n";

		sqlite3_finalize(myStatement);
	}
	else
	{
		cout << "Problem creating a prepared statement" << endl;
	}

}

void QuerySix(sqlite3* db) {
/*SELECT Products.ProductName
FROM Products, Customers, Orders, \"Order Details\"
WHERE Customers.CustomerID = Orders.CustomerID
AND Orders.OrderID =  \"Order Details\".OrderID
AND \"Order Details\".ProductID = Products.ProductID
AND Customers.CompanyName = "The Big Cheese"
AND \"Order Details\".Quantity >= 10*/
	sqlite3_stmt* myStatement;
	int statusOfPrep = sqlite3_prepare_v2(db, "SELECT Products.ProductName FROM Products, Customers, Orders, \"Order Details\" WHERE Customers.CustomerID = Orders.CustomerID AND Orders.OrderID = \"Order Details\".OrderID AND \"Order Details\".ProductID = Products.ProductID AND Customers.CompanyName = \"The Big Cheese\" AND \"Order Details\".Quantity >= 10", -1, &myStatement, NULL);

	if (statusOfPrep == SQLITE_OK)
	{
		int statusOfStep = sqlite3_step(myStatement);

		cout << "What are the names of the products that were ever ordered by the customer \"The Big Cheese\" in quantities of 10 or more?\n\n";

		while (statusOfStep == SQLITE_ROW)
		{
			string productName = (char*)sqlite3_column_text(myStatement, 0);

			cout << "Product name: " << productName << "\n";

			statusOfStep = sqlite3_step(myStatement);
		}

		cout << "\nSQL: SELECT Products.ProductName \nFROM Products, Customers, Orders, \"Order Details\" \nWHERE Customers.CustomerID = Orders.CustomerID \nAND Orders.OrderID = \"Order Details\".OrderID \nAND \"Order Details\".ProductID = Products.ProductID \nAND Customers.CompanyName = \"The Big Cheese\" \nAND \"Order Details\".Quantity >= 10\n";

		sqlite3_finalize(myStatement);
	}
	else
	{
		cout << "Problem creating a prepared statement" << endl;
	}

}

void QuerySeven(sqlite3* db) {
/*SELECT SUM(Products.UnitPrice) AS TotalPrice
FROM Products, Customers, Orders, \"Order Details\"
WHERE Customers.CustomerID = Orders.CustomerID
AND Orders.OrderID =  \"Order Details\".OrderID
AND \"Order Details\".ProductID = Products.ProductID
AND Customers.CompanyName = "Simons bistro"
AND Orders.OrderDate = "1997-01-16 00:00:00"*/
	sqlite3_stmt* myStatement;
	int statusOfPrep = sqlite3_prepare_v2(db, "SELECT SUM(Products.UnitPrice) AS TotalPrice FROM Products, Customers, Orders, '|Order Details\" WHERE Customers.CustomerID = Orders.CustomerID AND Orders.OrderID = \"Order Details\".OrderID AND \"Order Details\".ProductID = Products.ProductID AND Customers.CompanyName = \"Simons bistro\" AND Orders.OrderDate = \"1997-01-16 00:00:00\"", -1, &myStatement, NULL);

	if (statusOfPrep == SQLITE_OK)
	{
		int statusOfStep = sqlite3_step(myStatement);

		cout << "What was the final order price for all items ordered by the customer \"Simons bistro\" on January 16th 1997?\n\n";

		while (statusOfStep == SQLITE_ROW)
		{
			int productPrice = sqlite3_column_int(myStatement, 0);

			cout << "Final order price: " << productPrice << "\n";

			statusOfStep = sqlite3_step(myStatement);
		}

		cout << "\nSQL: SELECT SUM(Products.UnitPrice) AS TotalPrice \nFROM Products, Customers, Orders, \"Order Details\" \nWHERE Customers.CustomerID = Orders.CustomerID \nAND Orders.OrderID = \"Order Details\".OrderID \nAND \"Order Details\".ProductID = Products.ProductID \nAND Customers.CompanyName = \"Simons bistro\" \nAND Orders.OrderDate = \"1997-01-16 00:00:00\"\n";

		sqlite3_finalize(myStatement);
	}
	else
	{
		cout << "Problem creating a prepared statement" << endl;
	}

}

void QueryEight(sqlite3* db) {
/*SELECT Products.ProductName, MAX(Products.UnitsInStock) AS MostInStock
FROM Products, \"Order Details\"
WHERE \"Order Details\".ProductID = Products.ProductID
AND \"Order Details\".Discount >= 0.25*/
	sqlite3_stmt* myStatement;
	int statusOfPrep = sqlite3_prepare_v2(db, "SELECT Products.ProductName, MAX(Products.UnitsInStock) AS MostInStock FROM Products, \"Order Details\" WHERE \"Order Details\".ProductID = Products.ProductID AND \"Order Details\".Discount >= 0.25", -1, &myStatement, NULL);

	if (statusOfPrep == SQLITE_OK)
	{
		int statusOfStep = sqlite3_step(myStatement);

		cout << "Which product that was ever sold at a discount of 25% or more has the most units in stock (and how many units are in stock)?\n\n";

		while (statusOfStep == SQLITE_ROW)
		{
			string productName = (char *)sqlite3_column_text(myStatement, 0);
			int productCount = sqlite3_column_int(myStatement, 1);

			cout << "Product name: " << productName << "\n";
			cout << "Amount of product in stock: " << productCount << "\n";

			statusOfStep = sqlite3_step(myStatement);
		}

		cout << "\nSQL: SELECT Products.ProductName, MAX(Products.UnitsInStock) AS MostInStock \nFROM Products, \"Order Details\" \nWHERE \"Order Details\".ProductID = Products.ProductID \nAND \"Order Details\".Discount >= 0.25\n";

		sqlite3_finalize(myStatement);
	}
	else
	{
		cout << "Problem creating a prepared statement" << endl;
	}

}

void QueryNine(sqlite3* db) {

	sqlite3_stmt* myStatement;
	int statusOfPrep = sqlite3_prepare_v2(db, "WITH newTable AS(SELECT *FROM \"Order Details\", Products, Orders, Customers WHERE Orders.OrderID = \"Order Details\".OrderID AND Products.ProductID = \"Order Details\".ProductID AND Orders.CustomerID = Customers.CustomerID ) SELECT newTable.CompanyName, newTable.Quantity* (newTable.UnitPrice - (newTable.discount * newTable.UnitPrice)) AS \"Discounted Price\", (newTable.Quantity * newTable.UnitPrice) AS \"Normal Price\", MAX((newTable.Quantity * newTable.UnitPrice) - (newTable.Quantity * (1 - (newTable.Discount)) * newTable.UnitPrice)) AS \"Max Savings\" FROM newTable", -1, &myStatement, NULL);

	if (statusOfPrep == SQLITE_OK)
	{
		int statusOfStep = sqlite3_step(myStatement);

		cout << "What is the name of the company that had the largest discount on any order, how much was that discount, how much did the company pay minus the discount, and how much would they have paid without the discount?\n\n";

		while (statusOfStep == SQLITE_ROW)
		{
			string compName = (char*)sqlite3_column_text(myStatement, 0);
			int priceWithDisc = sqlite3_column_int(myStatement, 1);
			int priceNoDisc = sqlite3_column_int(myStatement, 2);
			int discount = sqlite3_column_int(myStatement, 3);

			cout << "Company Name: " << compName << "\n";
			cout << "Price With Discount: " << priceWithDisc << "\n";
			cout << "Price Without Discount: " << priceNoDisc << "\n";
			cout << "Discount: " << discount << "\n";

			statusOfStep = sqlite3_step(myStatement);
		}

		cout << "\nSQL: WITH newTable AS\n(SELECT * \nFROM \"Order Details\", Products, Orders, Customers \nWHERE Orders.OrderID = \"Order Details\".OrderID \nAND Products.ProductID = \"Order Details\".ProductID \nAND Orders.CustomerID = Customers.CustomerID ) \nSELECT newTable.CompanyName, newTable.Quantity* (newTable.UnitPrice - (newTable.discount * newTable.UnitPrice)) AS \"Discounted Price\", (newTable.Quantity * newTable.UnitPrice) AS \"Normal Price\", \nMAX((newTable.Quantity * newTable.UnitPrice) - (newTable.Quantity * (1 - (newTable.Discount)) * newTable.UnitPrice)) AS \"Max Savings\" \nFROM newTable\n";

		sqlite3_finalize(myStatement);
	}
	else
	{
		cout << "Problem creating a prepared statement" << endl;
	}

}

void QueryTen(sqlite3* db) {
	/*SELECT Suppliers.CompanyName
	FROM Products, Suppliers
	WHERE Products.SupplierID = Suppliers.SupplierID
	AND Products.UnitsOnOrder >= 100*/
	sqlite3_stmt* myStatement;
	int statusOfPrep = sqlite3_prepare_v2(db, "SELECT Suppliers.CompanyName FROM Products, Suppliers WHERE Products.SupplierID = Suppliers.SupplierID AND Products.UnitsOnOrder >= 100", -1, &myStatement, NULL);

	if (statusOfPrep == SQLITE_OK)
	{
		int statusOfStep = sqlite3_step(myStatement);

		cout << "Who are the suppliers whose products have 100 units or more on order?\n\n";

		while (statusOfStep == SQLITE_ROW)
		{
			string supplierName = (char*)sqlite3_column_text(myStatement, 0);

			cout << "Supplier with 100 units or more of product on order: " << supplierName << "\n";

			statusOfStep = sqlite3_step(myStatement);
		}

		cout << "\nSQL: SELECT Suppliers.CompanyName \nFROM Products, Suppliers \nWHERE Products.SupplierID = Suppliers.SupplierID \nAND Products.UnitsOnOrder >= 100\n";

		sqlite3_finalize(myStatement);
	}
	else
	{
		cout << "Problem creating a prepared statement" << endl;
	}

}

int main()
{
    const char * pathToDB = "C:/Users/braph/Desktop/Portfolio/SQL/Database Design and Management/NorthwindLimitedDB/NorthwindLimited.sqlite";
	sqlite3* db;
	int select = 0;
	int statusOfOpen = sqlite3_open(pathToDB, &db);

	if (statusOfOpen == SQLITE_OK) {

		cout << "Successfully opened the database.\n\n";

	}
	else {

		cout << "ERROR: Error opening the database, check file path.\n";
		exit(0);

	}

	while (select != -1) {

		cout << "\n1. Query 1\n";
		cout << "2. Query 2\n";
		cout << "3. Query 3\n";
		cout << "4. Query 4\n";
		cout << "5. Query 5\n";
		cout << "6. Query 6\n";
		cout << "7. Query 7\n";
		cout << "8. Query 8\n";
		cout << "9. Query 9\n";
		cout << "10. Query 10\n\n";

		cout << "Choose a query to execute (-1 to quit): ";
		cin >> select;

		if (select == 1) {

			QueryOne(db);

		}
		else if (select == 2) {

			QueryTwo(db);
		}
		else if (select == 3) {

			QueryThree(db);
		}
		else if (select == 4) {

			QueryFour(db);
		}
		else if (select == 5) {

			QueryFive(db);
		}
		else if (select == 6) {

			QuerySix(db);
		}
		else if (select == 7) {

			QuerySeven(db);
		}
		else if (select == 8) {

			QueryEight(db);

		}
		else if (select == 9) {

			QueryNine(db);
		}
		else if (select == 10) {

			QueryTen(db);
		}
		else if (select > 10 || select == 0 || select <= -2) {

			cout << "Please select a number 1-10 or -1 to quit.\n";
		}

	}

	sqlite3_close(db);

	return 0;

}