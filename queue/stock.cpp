/***********************************************************************
 * Implementation:
 *    STOCK
 * Summary:
 *    This will contain the implementation for stocksBuySell() as well
 *    as any other function or class implementation you need
 * Author
 *    James Call
 **********************************************************************/

#include <iostream>    // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>      // for STRING
#include <iomanip>	  // for setw()
#include <cassert>     // for ASSERT
#include "stock.h"     // for STOCK_TRANSACTION
#include "queue.h"     // for QUEUE
using namespace std;

/************************************************
 * STOCKS Display
 * Displays the results of the transactions
 ***********************************************/
void display(Queue <Transaction> qBuy, Queue <Transaction> qSell)
{
	Dollars proceeds;
	Dollars profit;
	
	// display the items in the Buy Queue
	if(!qBuy.empty() && qBuy.front().numStocks != 0)
	{
		cout << "Currently held:\n";
		while (!qBuy.empty())
		{
			cout  << "\tBought "
				  << qBuy.front().numStocks
				  << " shares at "
				  << qBuy.front().buyPrice << endl;
			qBuy.pop();	
		}
	}
	// display the Items in the sell queue
	if (!qSell.empty())
	{
		cout << "Sell History:\n";
		while (!qSell.empty())
		{
			profit = (qSell.front().sellPrice - qSell.front().buyPrice) * qSell.front().numStocks;
			cout  << "\tSold "
				  << qSell.front().numStocks
				  << " shares at "
				  << qSell.front().sellPrice
				  << " for a profit of "
				  << profit << endl;
			proceeds += profit;
			qSell.pop();
		}
	}
	// sho the total profit
	cout << "Proceeds: "
		  << proceeds << endl;



}



/************************************************
 * STOCKS BUY SELL
 * The interactive function allowing the user to
 * buy and sell stocks
 ***********************************************/
void stocksBuySell()
{
   // instructions
   cout << "This program will allow you to buy and sell stocks. "
        << "The actions are:\n";
   cout << "  buy 200 $1.57   - Buy 200 shares at $1.57\n";
   cout << "  sell 150 $2.15  - Sell 150 shares at $2.15\n";
   cout << "  display         - Display your current stock portfolio\n";
   cout << "  quit            - Display a final report and quit the program\n";

   // create items
   Queue <Transaction> qBuy;
   Queue <Transaction> qSell;
   string command;
   int numShare = 0;
   Dollars sellPrice;
   Transaction nBuy;
   Transaction nSell;

   // command loops
   	try
   	{
      	do
    	{
      		cout << "> ";
        	cin  >> command;
        	// input a buy transaction
        	if (command == "buy")
        	{
            	cin >> nBuy.numStocks;
            	cin >> nBuy.buyPrice;
        		qBuy.push(nBuy);
        	}
        	// handle a sell command
        	else if (command == "sell")
        	{
            	cin >> numShare;
            	cin >> sellPrice;
            do
            {
               if (qBuy.front().numStocks == 0)
	         	{
	            	qBuy.pop();
	         	}
	         	nSell.buyPrice = qBuy.front().buyPrice;
	         	nSell.sellPrice = sellPrice;
	         	// if sale is greater than the stocks in the current front purchase
					if (qBuy.front().numStocks <= numShare)
	            	{
	            		nSell.numStocks = qBuy.front().numStocks;
	            		numShare -= qBuy.front().numStocks;
	            		qBuy.front().numStocks = 0;
	            	}

   				// if the sale is less than / equal to the stocks in front purchase
            	else
            	{
            		nSell.numStocks = numShare;
            		qBuy.front().numStocks -= numShare;
            		numShare = 0;
            	}
	            	qSell.push(nSell);
	            }
					while (numShare != 0);
            }
        		
        		// handle display command
        		else if (command == "display")
        		{
        			display(qBuy, qSell);
        		}

        	else if (command == "quit")
       		break;

       	
       	else
            cout << "Invalid command\n";            
      }
      while (command != "quit");
   }
   catch (const char * error)
   {
      cout << error << endl;
   }








   // your code here...
}


