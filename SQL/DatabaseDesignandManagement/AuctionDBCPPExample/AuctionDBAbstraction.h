#pragma once 
#include "DBAbstraction.h" 
 
class AuctionDBAbstraction : DBAbstraction 
{ 
public: 
    AuctionDBAbstraction(string pathToFile); 
 
    void insertAuctionSiteUser(string firstName, string lastName, string email); 
	void insertItem(string itemName, double startingBid, int sellerUserId); 
	void insertBid(int itemId, int bidderId, double bidAmount); 
 
    int chooseAuctionSiteUser(); 
	int chooseItem(); 
	double chooseBidAmount(int itemId); 
	double getStartingBid(int itemId); 
	double getHighestBidSoFar(int itemId); 
	void printAllItemsWithBids(); 
     
private: 
    void createItemsTable(); 
	void createAuctionSiteUsersTable(); 
	void createBidsTable(); 
};