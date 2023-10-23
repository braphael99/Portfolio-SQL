#include <iostream> 
#include <string> 
#include "AuctionDBAbstraction.h" 
 
using namespace std; 
 
int main() 
{ 
	//create an auction db abstraction object 
	AuctionDBAbstraction db("/Users/markm/Documents/Auction.sqlite"); 
 
    //menu option 
	int option; 
 
	while (true) 
	{ 
		//display the menu and gather some user input 
		cout << "1. Add a user" << endl; 
		cout << "2. Add an item" << endl; 
		cout << "3. Make a bid" << endl; 
		cout << "4. List all items with bids" << endl; 
		cout << "5. Quit" << endl << endl; 
 
		cout << "Enter in an option: "; 
		cin >> option; 
 
		//add a new auction site user 
		if (option == 1) 
		{ 
			string firstName; 
			string lastName; 
			string email; 
 
			cout << "Enter in the new user's first name: "; 
			cin >> firstName; 
			cout << "Enter in the new user's last name: "; 
			cin >> lastName; 
			cout << "Enter in the new user's email: "; 
			cin >> email; 
 
			//add a user 
			db.insertAuctionSiteUser(firstName, lastName, email); 
		} 
		//add a new item 
		else if (option == 2) 
		{ 
			string itemName; 
			double price; 
			int sellerId; 
 
			cout << "Enter in the item name: "; 
			cin >> itemName; 
			cout << "Enter in the starting price: "; 
			cin >> price; 
			cout << "Choose the seller of the item" << endl; 
			sellerId = db.chooseAuctionSiteUser(); 
 
			//if they chose a valid user 
			if (sellerId >= 0) 
			{ 
				//add an item 
				db.insertItem(itemName, price, sellerId); 
			} 
			else //chose an invalid seller 
			{ 
				cout << "Error: you entered an incorrect user" << endl; 
			} 
		} 
		//make a bid on an item 
		else if (option == 3) 
		{ 
			//bid on an item 
			int itemId; 
			int bidderId; 
			double bidAmount; 
 
			cout << "Choose the item" << endl; 
			itemId = db.chooseItem(); 
 
			cout << "Choose the bidder of the item" << endl; 
			bidderId = db.chooseAuctionSiteUser(); 
 
			cout << "Enter a bid: "; 
			bidAmount = db.chooseBidAmount(itemId); 
 
			//if the bid amount is valid 
			if (bidAmount > 0.0) 
			{ 
				//insert the bid 
				db.insertBid(itemId, bidderId, bidAmount); 
			} 
			else //bid was too low 
			{ 
				cout << "Error: The bid was too low" << endl; 
			} 
		} 
		else if (option == 4) 
		{ 
			//print all the items with bids 
			db.printAllItemsWithBids(); 
		} 
		else //quit 
		{ 
			//quit 
			break; 
		} 
 
		cout << endl << endl; 
	} 
 
	return 0; 
}