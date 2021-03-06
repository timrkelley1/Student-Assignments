// BY Timothy Kelley, CSCI 2170-001, Due: 10/15/19
// PROGRAM ID: bakery.cpp / Prints Monthly Cost of Products Forecast
// REMARKS:  This program calculates and prints the Monthly Cost of Bakery
// Products Forecast table. The program obtains all input from three data
// files. The products file contains the number of products and a list of
// the names. The ingredients file contains the number of ingredients and a
// list of the amount of ingredient used in each product. The costs file
// contains values representing the beginning and ending months of the report
// and a list containing the price of each ingredient for each month. The
// program reads in this data, processes it, and prints a formatted table. 

// Includes:
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;


// Global constants:
const int MAX_PRODUCTS = 24;           // Maximum number of products
const int MAX_INGREDIENTS = 30;        // Maximum number of ingredients
const int MAX_NAME_LEN = 12;           // Maximum product name length
const int MAX_MONTHS = 12;             // Maximum number of months

const string PRODUCTS_FILE =  "products.dat";     // Products filename
const string INGREDIENTS_FILE="ingredients.dat";  // Ingredients filename
const string PRICES_FILE =    "prices.dat";       // Prices filename


// Function prototypes:
void GetProducts(int& numberOfProducts, string product[]);
//               OUT                    OUT

void GetRecipes(int numberOfProducts,                 // IN
                int& numberOfIngredients,             // OUT
                int recipe[][MAX_INGREDIENTS]);       // OUT

void GetPrices(int numberOfIngredients,               // IN
               int& numberOfMonths,                   // OUT
               int& beginningMonth,                   // OUT
               int& endingMonth,                      // OUT
               int price[][MAX_MONTHS]);              // OUT

void ForecastMonthlyProductCosts(
               int numberOfProducts,                  // IN
               int numberOfIngredients,               // IN
         const int recipe[][MAX_INGREDIENTS],         // IN
               int numberOfMonths,                    // IN
         const int price[][MAX_MONTHS],               // IN
               int forecastCost[][MAX_MONTHS]);       // OUT

void PrintTable(int numberOfProducts,                 // IN
                int numberOfMonths,                   // IN
                int beginningMonth,                   // IN
                int endingMonth,                      // IN
          const string product[],                     // IN
          const int forecastCost[][MAX_MONTHS]);      // IN

void PrintTableHeading(
  int numberOfMonths, int beginningMonth, int endingMonth);
//IN                  IN                  IN

void PrintTableRow(
                int numberOfMonths,                   // IN
                string product,                       // IN
          const int monthlyCost[MAX_MONTHS]);         // IN


// Main routine
int main()
{
	// Local variables
	int numberOfProducts;              // Number of products
	int numberOfIngredients;           // Number of ingredients
	int numberOfMonths;                // Number of months in report
	int beginningMonth;                // Beginning month of report
	int endingMonth;                   // Ending month of report
	
	string product[MAX_PRODUCTS];                   // Names of products
	int recipe[MAX_PRODUCTS][MAX_INGREDIENTS];      // Ingredient quantities
	int price[MAX_INGREDIENTS][MAX_MONTHS];         // Ingredient prices
	int forecastCost[MAX_PRODUCTS][MAX_MONTHS];     // Forecast Product costs
	

	// Get product names
	GetProducts(numberOfProducts, product);
	
	// Get recipe ingredient quantities
	GetRecipes(numberOfProducts, numberOfIngredients, recipe);
	
	// Get monthly prices of ingredients
	GetPrices(numberOfIngredients, 
	  numberOfMonths, beginningMonth, endingMonth, price);
	
	// Calculate forecast product costs, by month
	ForecastMonthlyProductCosts(numberOfProducts, numberOfIngredients,
	  recipe, numberOfMonths, price, forecastCost);

	// Print the forecast table
	PrintTable(numberOfProducts, numberOfMonths, beginningMonth, endingMonth,
	  product, forecastCost);
	
	return 0;
} // end main


void GetProducts(int& numberOfProducts, string product[])
//               OUT                    OUT
// Read in the number of products and the product names from the
// products file.
// Pre:  The global constant PRODUCTS_FILE has been set.
// Post: 'numberOfProducts' contains the total number of products and
//       'products' contains the product names.
{
	ifstream productsIn;               // PRODUCTS_FILE input handle
	
	// Open file stream and check for error
	productsIn.open( PRODUCTS_FILE.c_str() );
	if( !productsIn )
	{
		cerr << "Could not open " << PRODUCTS_FILE << endl;
		exit(1);
	}
	
	// Read in Number of products contained in file
	productsIn >> numberOfProducts;
	
	// Skip over the trailing newline
	productsIn.ignore(80,'\n');

	// Read in product names one line at a time and store in array
	for (int i=0;i < numberOfProducts; i++)
		getline(productsIn, product[i]);

	// Close the file stream    
	productsIn.close();

	return;
} // end GetProducts


void GetRecipes(int numberOfProducts,                 // IN
                int& numberOfIngredients,             // OUT
                int recipe[][MAX_INGREDIENTS])        // OUT
// Read in the amounts of ingredients used in each product from the
// ingredients file.
// Pre:  numberOfProducts has been set to the total number of products
//       and the global constant INGREDIENTS_FILE has been set.
// Post: 'numberOfIngredients' contains the total number of ingredients
//       and 'numberOfProducts' rows of 'recipe' contain
//       'numberOfIngredients' elements with the ingredient amounts.
{
    ifstream ingredientsIn; // INGREDIENTS_FILE input handle
    
    // Open file stream and check for error
    ingredientsIn.open(INGREDIENTS_FILE.c_str() );
    
    if(!ingredientsIn) {
        cerr << "Could not open " << INGREDIENTS_FILE << endl;
		exit(1);
    }
    
    // Read in number of ingredients
    ingredientsIn >> numberOfIngredients;

    // Read in amounts of ingredients for each product
    for(int i = 0; i < numberOfProducts; i++)
        for(int j = 0; j < numberOfIngredients; j++)
            ingredientsIn >> recipe[i][j];
        
    //Close file stream
    ingredientsIn.close();
    
	return;
} // end GetRecipes


void GetPrices(int numberOfIngredients,               // IN
               int& numberOfMonths,                   // OUT
               int& beginningMonth,                   // OUT
               int& endingMonth,                      // OUT
               int price[][MAX_MONTHS])               // OUT
// Read in the monthly prices of the ingredients and the date range.
// Pre:  'numberOfIngredients' contains the number of ingredients
// and the global constant PRICES_FILE has been set.
// Post: 'numberOfMonths' is calculated from 'beginningMonth' and
//       'endingMonth', which are set, and 'numberOfIngredients' rows
//       of 'price' contain 'numberOfMonths' elements with the
//       corresponding ingredient costs.
{
	ifstream pricesIn;               // PRICES_FILE input handle
	
	// Open file stream and check for error
	pricesIn.open( PRICES_FILE.c_str() );
	
	if( !pricesIn )
	{
		cerr << "Could not open " << PRICES_FILE << endl;
		exit(1);
	}

	// Read in month range points (beginning and ending month)
	pricesIn >> beginningMonth >> endingMonth;
	
	//  If endingMonth number is larger than beginningMonth 
	//  we need to wrap the count back to one
	if ( endingMonth > beginningMonth)
		numberOfMonths = (endingMonth - beginningMonth)+1;
	else
		numberOfMonths = (13 -(beginningMonth - endingMonth));
	
	// Read in the prices of ingredients by Month
	for (int i=0; i < numberOfIngredients; i++) 
		for (int m=0; m < numberOfMonths; m++)
			pricesIn >> price[i][m];

	// Close the file stream
	pricesIn.close();

	return;
} // end GetPrices


void ForecastMonthlyProductCosts(
               int numberOfProducts,                  // IN
               int numberOfIngredients,               // IN
         const int recipe[][MAX_INGREDIENTS],         // IN
               int numberOfMonths,                    // IN
         const int price[][MAX_MONTHS],               // IN
               int forecastCost[][MAX_MONTHS])        // OUT
// Calculate forecast product costs, by month.
// Pre:  All "IN" parameters have correct values.
// Post: The appropriate elements of the 'forecastCost' array will
//       contain the predicted product cost.
{
    int sum = 0; //initialize accumulator for loop to sum
    
    // Calculate forecast cost per month per product
    // then push sum to forecastCost array 
    for(int i = 0; i < numberOfProducts; i++) {
        for(int j = 0; j < numberOfMonths; j++) {
            int sum = 0;
            for(int k = 0; k < numberOfIngredients; k++) {
                sum += recipe[i][k]*price[k][j];
            }
        forecastCost[i][j] = sum;
        }
        
    }
    
	return;
} // end ForecastMonthlyProductCosts


void PrintTable(int numberOfProducts,                 // IN
                int numberOfMonths,                   // IN
                int beginningMonth,                   // IN
                int endingMonth,                      // IN
          const string product[],                     // IN
          const int forecastCost[][MAX_MONTHS])       // IN
// Print nicely formatted forecast product costs, by product, by month.
// Pre:  All "IN" parameters have correct values.
// Post: A table will be printed to stdout.  Long lines are not wrapped.
{
	// Print the forecast table heading
	PrintTableHeading(numberOfMonths, beginningMonth, endingMonth);
	
	// Print each row of the forecast table
	for (int prod=0; prod<numberOfProducts; prod++)
	{
		PrintTableRow(numberOfMonths, product[prod], forecastCost[prod]); 
	}
		
	return;
} // end PrintTable


void PrintTableHeading(
  int numberOfMonths, int beginningMonth, int endingMonth)
//IN                  IN                  IN
// Print the heading for the table.
// Pre:  All "IN" parameters have correct values.
// Post: The table title, column headings, and a separator line
// will be printed to stdout.
{
	int month = beginningMonth;        // Current month to be printed
	
	// Print table title and title of product column
	cout << "Monthly Cost of Bakery Products Forecast" << endl << endl;
	cout << left;
	cout << setw(MAX_NAME_LEN + 1) << "Product";
	
    
    cout << right;
    
    // Print x-axis values for months
    for(int m = 0; m < numberOfMonths; m++) {
        cout << setw(7) << month;
        month++;
        if(month == 13) {
            month = 1;
        }
    }
    
    // Print line seperator 
    cout << endl;
    for(int i = 0; i <= MAX_NAME_LEN; i++)
        cout << "-";
    cout << "+";
    
    for(int m = 0; m < numberOfMonths; m++) {
        for(int n = 0; n < 6; n++) {
            cout << "-";
        }
        cout << "+";
    }
    
    cout << endl;
    
	return;
} // end PrintTableHeading


void PrintTableRow(
                int numberOfMonths,                   // IN
                string product,                       // IN
          const int monthlyCost[MAX_MONTHS])          // IN
// Print the product name and the costs per month for that product.
// Pre:  All "IN" parameters have correct values.
// Post: The product name and cost for each month will be printed
//       to stdout.
{
	// Print product name
	cout << setw(13) << (product+"             ").substr(0,MAX_NAME_LEN+1);

	
	cout << right;
	// Print cost to produce product during each month
    for(int month=0; month<numberOfMonths; month++)
	{
		cout << setw(7) << monthlyCost[month];
	} 
	
	cout << endl;
	
	return;
} // end PrintTableRow
