
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <limits>

using namespace std;

// ==========================================
//             CONSTANTS
// ==========================================

const int MAX_SHOPS = 100;
const int MAX_CUSTOMERS = 100;
const int MAX_BILLS = 500;
const int MAX_PARKING = 100;

const int PARKING_RATE = 50;
const int TOTAL_PARKING_SPACES = 100;

// ==========================================
//             STRUCTURES
// ==========================================

struct Shop
{
    int id;
    string name;
    string category;
    int floor;
    double rent;
};

struct Customer
{
    int id;
    string name;
    string phone;
};

struct Bill
{
    int id;
    int customerID;
    int shopID;
    double subtotal;
    double discount;
    double finalAmount;
};

struct Parking
{
    string vehicleNumber;
    int entryHour;
    int exitHour;
    double fee;
    bool active;
};

// ==========================================
//          GLOBAL VARIABLES
// ==========================================

Shop shops[MAX_SHOPS];
Customer customers[MAX_CUSTOMERS];
Bill bills[MAX_BILLS];
Parking parkingRecords[MAX_PARKING];

int shopCount = 0;
int customerCount = 0;
int billCount = 0;
int parkingCount = 0;

int nextShopID = 1001;
int nextCustomerID = 101;
int nextBillID = 1001;

// ==========================================
//           INPUT FUNCTIONS
// ==========================================

int getInt(string message)
{
    int value;

    while (true)
    {
        cout << message;

        if (cin >> value)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cout << "Invalid input! Enter a number.\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

double getDouble(string message)
{
    double value;

    while (true)
    {
        cout << message;

        if (cin >> value)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (value >= 0)
                return value;
        }

        cout << "Invalid input! Enter a valid positive amount.\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string getString(string message)
{
    string value;

    cout << message;
    getline(cin, value);

    return value;
}

// ==========================================
//             DISPLAY FUNCTIONS
// ==========================================

void line()
{
    cout << "========================================================\n";
}

void heading(string title)
{
    cout << "\n";
    line();
    cout << "             " << title << "\n";
    line();
}

void success(string message)
{
    cout << "\n[SUCCESS] " << message << "\n";
}

void error(string message)
{
    cout << "\n[ERROR] " << message << "\n";
}

void pauseScreen()
{
    cout << "\nPress Enter to continue...";
    cin.get();
}

// ==========================================
//             FILE HANDLING
// ==========================================

void loadData()
{
    string row;

    // Load shops
    ifstream shopFile("shops.txt");

    while (getline(shopFile, row) && shopCount < MAX_SHOPS)
    {
        stringstream ss(row);
        string temp;

        getline(ss, temp, '|');
        shops[shopCount].id = stoi(temp);

        getline(ss, shops[shopCount].name, '|');
        getline(ss, shops[shopCount].category, '|');

        getline(ss, temp, '|');
        shops[shopCount].floor = stoi(temp);

        getline(ss, temp);
        shops[shopCount].rent = stod(temp);

        if (shops[shopCount].id >= nextShopID)
            nextShopID = shops[shopCount].id + 1;

        shopCount++;
    }

    shopFile.close();

    // Load customers
    ifstream customerFile("customers.txt");

    while (getline(customerFile, row) && customerCount < MAX_CUSTOMERS)
    {
        stringstream ss(row);
        string temp;

        getline(ss, temp, '|');
        customers[customerCount].id = stoi(temp);

        getline(ss, customers[customerCount].name, '|');
        getline(ss, customers[customerCount].phone);

        if (customers[customerCount].id >= nextCustomerID)
            nextCustomerID = customers[customerCount].id + 1;

        customerCount++;
    }

    customerFile.close();

    // Load bills
    ifstream billFile("bills.txt");

    while (getline(billFile, row) && billCount < MAX_BILLS)
    {
        stringstream ss(row);
        string temp;

        getline(ss, temp, '|');
        bills[billCount].id = stoi(temp);

        getline(ss, temp, '|');
        bills[billCount].customerID = stoi(temp);

        getline(ss, temp, '|');
        bills[billCount].shopID = stoi(temp);

        getline(ss, temp, '|');
        bills[billCount].subtotal = stod(temp);

        getline(ss, temp, '|');
        bills[billCount].discount = stod(temp);

        getline(ss, temp);
        bills[billCount].finalAmount = stod(temp);

        if (bills[billCount].id >= nextBillID)
            nextBillID = bills[billCount].id + 1;

        billCount++;
    }

    billFile.close();

    // Load parking records
    ifstream parkingFile("parking.txt");

    while (getline(parkingFile, row) && parkingCount < MAX_PARKING)
    {
        stringstream ss(row);
        string temp;

        getline(ss, parkingRecords[parkingCount].vehicleNumber, '|');

        getline(ss, temp, '|');
        parkingRecords[parkingCount].entryHour = stoi(temp);

        getline(ss, temp, '|');
        parkingRecords[parkingCount].exitHour = stoi(temp);

        getline(ss, temp, '|');
        parkingRecords[parkingCount].fee = stod(temp);

        getline(ss, temp);
        parkingRecords[parkingCount].active = (temp == "1");

        parkingCount++;
    }

    parkingFile.close();
}

void saveData()
{
    // Save shops
    ofstream shopFile("shops.txt");

    for (int i = 0; i < shopCount; i++)
    {
        shopFile << shops[i].id << "|"
                 << shops[i].name << "|"
                 << shops[i].category << "|"
                 << shops[i].floor << "|"
                 << shops[i].rent << "\n";
    }

    shopFile.close();

    // Save customers
    ofstream customerFile("customers.txt");

    for (int i = 0; i < customerCount; i++)
    {
        customerFile << customers[i].id << "|"
                     << customers[i].name << "|"
                     << customers[i].phone << "\n";
    }

    customerFile.close();

    // Save bills
    ofstream billFile("bills.txt");

    for (int i = 0; i < billCount; i++)
    {
        billFile << bills[i].id << "|"
                 << bills[i].customerID << "|"
                 << bills[i].shopID << "|"
                 << bills[i].subtotal << "|"
                 << bills[i].discount << "|"
                 << bills[i].finalAmount << "\n";
    }

    billFile.close();

    // Save parking
    ofstream parkingFile("parking.txt");

    for (int i = 0; i < parkingCount; i++)
    {
        parkingFile << parkingRecords[i].vehicleNumber << "|"
                    << parkingRecords[i].entryHour << "|"
                    << parkingRecords[i].exitHour << "|"
                    << parkingRecords[i].fee << "|"
                    << (parkingRecords[i].active ? 1 : 0) << "\n";
    }

    parkingFile.close();
}

// ==========================================
//              MALL INFORMATION
// ==========================================

void mallInformation()
{
    heading("MALL INFORMATION");

    cout << "Mall Name       : Smart Shopping Mall\n";
    cout << "Location        : Topi, Pakistan\n";
    cout << "Opening Hours   : 10:00 AM - 10:00 PM\n";
    cout << "Total Shops     : " << shopCount << "\n";
    cout << "Total Floors    : 3\n";
    cout << "Parking Spaces  : " << TOTAL_PARKING_SPACES << "\n";

    line();
}

// ==========================================
//              SHOP MANAGEMENT
// ==========================================

int findShop(int id)
{
    for (int i = 0; i < shopCount; i++)
    {
        if (shops[i].id == id)
            return i;
    }

    return -1;
}

void addShop()
{
    heading("REGISTER NEW SHOP");

    if (shopCount >= MAX_SHOPS)
    {
        error("Shop storage is full.");
        return;
    }

    shops[shopCount].id = nextShopID++;

    cout << "Generated Shop ID: " << shops[shopCount].id << "\n";

    shops[shopCount].name = getString("Enter Shop Name: ");
    shops[shopCount].category = getString("Enter Category: ");

    shops[shopCount].floor = getInt("Enter Floor Number: ");
    shops[shopCount].rent = getDouble("Enter Monthly Rent: Rs. ");

    shopCount++;

    saveData();

    success("Shop registered successfully!");
}

void displayShops()
{
    heading("ALL REGISTERED SHOPS");

    if (shopCount == 0)
    {
        cout << "No shops registered yet.\n";
        return;
    }

    cout << left
         << setw(12) << "Shop ID"
         << setw(22) << "Shop Name"
         << setw(18) << "Category"
         << setw(10) << "Floor"
         << "Rent\n";

    line();

    for (int i = 0; i < shopCount; i++)
    {
        cout << left
             << setw(12) << shops[i].id
             << setw(22) << shops[i].name
             << setw(18) << shops[i].category
             << setw(10) << shops[i].floor
             << shops[i].rent << "\n";
    }
}

void searchShop()
{
    heading("SEARCH SHOP");

    int id = getInt("Enter Shop ID: ");

    int index = findShop(id);

    if (index == -1)
    {
        error("Shop not found.");
        return;
    }

    cout << "\nShop ID      : " << shops[index].id;
    cout << "\nShop Name    : " << shops[index].name;
    cout << "\nCategory     : " << shops[index].category;
    cout << "\nFloor        : " << shops[index].floor;
    cout << "\nMonthly Rent : Rs. " << shops[index].rent << "\n";
}

void updateShop()
{
    heading("UPDATE SHOP");

    int id = getInt("Enter Shop ID: ");
    int index = findShop(id);

    if (index == -1)
    {
        error("Shop not found.");
        return;
    }

    shops[index].name = getString("New Shop Name: ");
    shops[index].category = getString("New Category: ");
    shops[index].floor = getInt("New Floor: ");
    shops[index].rent = getDouble("New Monthly Rent: Rs. ");

    saveData();

    success("Shop updated successfully!");
}

void deleteShop()
{
    heading("DELETE SHOP");

    int id = getInt("Enter Shop ID: ");
    int index = findShop(id);

    if (index == -1)
    {
        error("Shop not found.");
        return;
    }

    for (int i = index; i < shopCount - 1; i++)
    {
        shops[i] = shops[i + 1];
    }

    shopCount--;

    saveData();

    success("Shop deleted successfully!");
}

void shopManagement()
{
    int choice;

    do
    {
        heading("SHOP MANAGEMENT");

        cout << "1. Register New Shop\n";
        cout << "2. View All Shops\n";
        cout << "3. Search Shop\n";
        cout << "4. Update Shop\n";
        cout << "5. Delete Shop\n";
        cout << "0. Back to Dashboard\n";

        choice = getInt("\nEnter Choice: ");

        switch (choice)
        {
            case 1: addShop(); break;
            case 2: displayShops(); break;
            case 3: searchShop(); break;
            case 4: updateShop(); break;
            case 5: deleteShop(); break;
            case 0: break;
            default: error("Invalid choice.");
        }

        if (choice != 0)
            pauseScreen();

    } while (choice != 0);
}

// ==========================================
//             CUSTOMER MANAGEMENT
// ==========================================

int findCustomer(int id)
{
    for (int i = 0; i < customerCount; i++)
    {
        if (customers[i].id == id)
            return i;
    }

    return -1;
}

void addCustomer()
{
    heading("CUSTOMER REGISTRATION");

    if (customerCount >= MAX_CUSTOMERS)
    {
        error("Customer storage is full.");
        return;
    }

    customers[customerCount].id = nextCustomerID++;

    cout << "Customer ID: " << customers[customerCount].id << "\n";

    customers[customerCount].name = getString("Customer Name: ");
    customers[customerCount].phone = getString("Phone Number: ");

    customerCount++;

    saveData();

    success("Customer registered successfully!");
}

void displayCustomers()
{
    heading("CUSTOMER RECORDS");

    if (customerCount == 0)
    {
        cout << "No customers registered.\n";
        return;
    }

    cout << left
         << setw(15) << "Customer ID"
         << setw(25) << "Name"
         << "Phone Number\n";

    line();

    for (int i = 0; i < customerCount; i++)
    {
        cout << left
             << setw(15) << customers[i].id
             << setw(25) << customers[i].name
             << customers[i].phone << "\n";
    }
}

void searchCustomer()
{
    heading("SEARCH CUSTOMER");

    int id = getInt("Enter Customer ID: ");

    int index = findCustomer(id);

    if (index == -1)
    {
        error("Customer not found.");
        return;
    }

    cout << "\nCustomer ID : " << customers[index].id;
    cout << "\nName        : " << customers[index].name;
    cout << "\nPhone       : " << customers[index].phone << "\n";
}

void customerManagement()
{
    int choice;

    do
    {
        heading("CUSTOMER MANAGEMENT");

        cout << "1. Register Customer\n";
        cout << "2. View All Customers\n";
        cout << "3. Search Customer\n";
        cout << "0. Back to Dashboard\n";

        choice = getInt("\nEnter Choice: ");

        switch (choice)
        {
            case 1: addCustomer(); break;
            case 2: displayCustomers(); break;
            case 3: searchCustomer(); break;
            case 0: break;
            default: error("Invalid choice.");
        }

        if (choice != 0)
            pauseScreen();

    } while (choice != 0);
}

// ==========================================
//               BILLING SYSTEM
// ==========================================

void billingSystem()
{
    heading("SMART BILLING SYSTEM");

    if (billCount >= MAX_BILLS)
    {
        error("Bill storage is full.");
        return;
    }

    if (customerCount == 0 || shopCount == 0)
    {
        error("Register at least one customer and one shop first.");
        return;
    }

    int customerID = getInt("Enter Customer ID: ");
    int customerIndex = findCustomer(customerID);

    if (customerIndex == -1)
    {
        error("Customer not found.");
        return;
    }

    int shopID = getInt("Enter Shop ID: ");
    int shopIndex = findShop(shopID);

    if (shopIndex == -1)
    {
        error("Shop not found.");
        return;
    }

    int products = getInt("Number of Products: ");

    if (products <= 0 || products > 50)
    {
        error("Enter a quantity between 1 and 50.");
        return;
    }

    double subtotal = 0;

    heading("CUSTOMER PURCHASE DETAILS");

    cout << left
         << setw(22) << "Product"
         << setw(12) << "Price"
         << setw(10) << "Quantity"
         << "Total\n";

    line();

    for (int i = 0; i < products; i++)
    {
        string name = getString("Product Name: ");
        double price = getDouble("Product Price: Rs. ");
        int quantity = getInt("Quantity: ");

        if (quantity <= 0)
        {
            error("Invalid quantity. Enter the item again.");
            i--;
            continue;
        }

        double itemTotal = price * quantity;

        subtotal += itemTotal;

        cout << left
             << setw(22) << name
             << setw(12) << price
             << setw(10) << quantity
             << itemTotal << "\n";
    }

    double discount = 0;

    if (subtotal >= 10000)
        discount = subtotal * 0.10;
    else if (subtotal >= 5000)
        discount = subtotal * 0.05;

    double finalAmount = subtotal - discount;

    int billID = nextBillID++;

    bills[billCount].id = billID;
    bills[billCount].customerID = customerID;
    bills[billCount].shopID = shopID;
    bills[billCount].subtotal = subtotal;
    bills[billCount].discount = discount;
    bills[billCount].finalAmount = finalAmount;

    billCount++;

    saveData();

    heading("CUSTOMER PAYMENT RECEIPT");

    cout << "Bill Number : BILL-" << billID << "\n";
    cout << "Customer    : " << customers[customerIndex].name << "\n";
    cout << "Shop        : " << shops[shopIndex].name << "\n";

    line();

    cout << fixed << setprecision(2);

    cout << "Subtotal    : Rs. " << subtotal << "\n";
    cout << "Discount    : Rs. " << discount << "\n";

    line();

    cout << "FINAL PAYMENT: Rs. " << finalAmount << "\n";

    line();

    cout << "       THANK YOU FOR SHOPPING!\n";

    success("Bill generated and saved successfully!");
}

// ==========================================
//             PARKING MANAGEMENT
// ==========================================

int findVehicle(string number)
{
    for (int i = 0; i < parkingCount; i++)
    {
        if (parkingRecords[i].vehicleNumber == number &&
            parkingRecords[i].active)
        {
            return i;
        }
    }

    return -1;
}

void vehicleEntry()
{
    heading("VEHICLE ENTRY");

    if (parkingCount >= MAX_PARKING)
    {
        error("Parking record storage is full.");
        return;
    }

    int occupied = 0;

    for (int i = 0; i < parkingCount; i++)
    {
        if (parkingRecords[i].active)
            occupied++;
    }

    if (occupied >= TOTAL_PARKING_SPACES)
    {
        error("Parking is full.");
        return;
    }

    string number = getString("Enter Vehicle Number: ");

    if (findVehicle(number) != -1)
    {
        error("This vehicle is already parked.");
        return;
    }

    int hour = getInt("Enter Entry Hour (0-23): ");

    if (hour < 0 || hour > 23)
    {
        error("Invalid hour.");
        return;
    }

    parkingRecords[parkingCount].vehicleNumber = number;
    parkingRecords[parkingCount].entryHour = hour;
    parkingRecords[parkingCount].exitHour = -1;
    parkingRecords[parkingCount].fee = 0;
    parkingRecords[parkingCount].active = true;

    parkingCount++;

    saveData();

    success("Vehicle entry registered!");
}

void vehicleExit()
{
    heading("VEHICLE EXIT");

    string number = getString("Enter Vehicle Number: ");

    int index = findVehicle(number);

    if (index == -1)
    {
        error("Vehicle not found in parking.");
        return;
    }

    int exitHour = getInt("Enter Exit Hour (0-23): ");

    if (exitHour < 0 || exitHour > 23)
    {
        error("Invalid hour.");
        return;
    }

    int duration = exitHour - parkingRecords[index].entryHour;

    if (duration <= 0)
        duration += 24;

    double fee = duration * PARKING_RATE;

    parkingRecords[index].exitHour = exitHour;
    parkingRecords[index].fee = fee;
    parkingRecords[index].active = false;

    saveData();

    heading("PARKING PAYMENT RECEIPT");

    cout << "Vehicle Number : " << number << "\n";
    cout << "Entry Hour     : " << parkingRecords[index].entryHour << "\n";
    cout << "Exit Hour      : " << exitHour << "\n";
    cout << "Duration       : " << duration << " Hours\n";
    cout << "Rate           : Rs. " << PARKING_RATE << "/Hour\n";

    line();

    cout << "Parking Fee    : Rs. " << fee << "\n";

    line();

    success("Vehicle exit registered!");
}

void parkingStatus()
{
    heading("PARKING STATUS");

    int occupied = 0;

    for (int i = 0; i < parkingCount; i++)
    {
        if (parkingRecords[i].active)
            occupied++;
    }

    cout << "Total Spaces     : " << TOTAL_PARKING_SPACES << "\n";
    cout << "Occupied Spaces  : " << occupied << "\n";
    cout << "Available Spaces : "
         << TOTAL_PARKING_SPACES - occupied << "\n";
}

void parkingManagement()
{
    int choice;

    do
    {
        heading("PARKING MANAGEMENT");

        cout << "1. Register Vehicle Entry\n";
        cout << "2. Register Vehicle Exit\n";
        cout << "3. Check Parking Availability\n";
        cout << "0. Back to Dashboard\n";

        choice = getInt("\nEnter Choice: ");

        switch (choice)
        {
            case 1: vehicleEntry(); break;
            case 2: vehicleExit(); break;
            case 3: parkingStatus(); break;
            case 0: break;
            default: error("Invalid choice.");
        }

        if (choice != 0)
            pauseScreen();

    } while (choice != 0);
}

// ==========================================
//              SHOP DIRECTORY
// ==========================================

void shopDirectory()
{
    heading("SHOP DIRECTORY");

    if (shopCount == 0)
    {
        cout << "No shops available.\n";
        return;
    }

    int floor = getInt("Enter Floor Number (0 for all floors): ");

    cout << "\nAvailable Shops:\n";

    line();

    for (int i = 0; i < shopCount; i++)
    {
        if (floor == 0 || shops[i].floor == floor)
        {
            cout << "ID: " << shops[i].id
                 << " | " << shops[i].name
                 << " | " << shops[i].category
                 << " | Floor: " << shops[i].floor << "\n";
        }
    }
}

// ==========================================
//              ADMIN DASHBOARD
// ==========================================

void adminDashboard()
{
    heading("ADMIN DASHBOARD");

    double totalSales = 0;
    double totalParkingRevenue = 0;

    int occupied = 0;

    for (int i = 0; i < billCount; i++)
    {
        totalSales += bills[i].finalAmount;
    }

    for (int i = 0; i < parkingCount; i++)
    {
        totalParkingRevenue += parkingRecords[i].fee;

        if (parkingRecords[i].active)
            occupied++;
    }

    cout << fixed << setprecision(2);

    cout << "\nMALL OVERVIEW\n";

    line();

    cout << "Registered Shops      : " << shopCount << "\n";
    cout << "Registered Customers  : " << customerCount << "\n";
    cout << "Total Bills Generated : " << billCount << "\n";

    cout << "\nFINANCIAL OVERVIEW\n";

    line();

    cout << "Total Sales Revenue   : Rs. " << totalSales << "\n";
    cout << "Parking Revenue       : Rs. " << totalParkingRevenue << "\n";
    cout << "Total Revenue         : Rs. "
         << totalSales + totalParkingRevenue << "\n";

    cout << "\nPARKING STATUS\n";

    line();

    cout << "Total Spaces          : " << TOTAL_PARKING_SPACES << "\n";
    cout << "Occupied Spaces       : " << occupied << "\n";
    cout << "Available Spaces      : "
         << TOTAL_PARKING_SPACES - occupied << "\n";

    line();
}

// ==========================================
//               SALES REPORTS
// ==========================================

void salesReports()
{
    heading("SALES REPORT");

    double totalSales = 0;
    double totalDiscount = 0;

    cout << left
         << setw(15) << "Bill ID"
         << setw(15) << "Customer ID"
         << setw(15) << "Shop ID"
         << setw(15) << "Final Amount\n";

    line();

    for (int i = 0; i < billCount; i++)
    {
        cout << left
             << setw(15) << bills[i].id
             << setw(15) << bills[i].customerID
             << setw(15) << bills[i].shopID
             << bills[i].finalAmount << "\n";

        totalSales += bills[i].finalAmount;
        totalDiscount += bills[i].discount;
    }

    line();

    cout << "Total Bills      : " << billCount << "\n";
    cout << "Total Discounts  : Rs. " << totalDiscount << "\n";
    cout << "Total Sales      : Rs. " << totalSales << "\n";

    line();
}

// ==========================================
//                 ADMIN LOGIN
// ==========================================

bool adminLogin()
{
    heading("ADMIN LOGIN");

    string username;
    string password;

    cout << "Username: ";
    getline(cin, username);

    cout << "Password: ";
    getline(cin, password);

    if (username == "admin" && password == "admin123")
    {
        success("Login successful!");
        return true;
    }

    error("Incorrect username or password.");
    return false;
}

// ==========================================
//                MAIN MENU
// ==========================================

void adminMenu()
{
    int choice;

    do
    {
        heading("SMART MALL - ADMIN CONTROL PANEL");

        cout << "1. Mall Information\n";
        cout << "2. Shop Management\n";
        cout << "3. Customer Management\n";
        cout << "4. Smart Billing System\n";
        cout << "5. Parking Management\n";
        cout << "6. Shop Directory\n";
        cout << "7. Admin Dashboard\n";
        cout << "8. Sales Reports\n";
        cout << "9. Save All Records\n";
        cout << "0. Logout\n";

        choice = getInt("\nEnter Your Choice: ");

        switch (choice)
        {
            case 1: mallInformation(); break;
            case 2: shopManagement(); break;
            case 3: customerManagement(); break;
            case 4: billingSystem(); break;
            case 5: parkingManagement(); break;
            case 6: shopDirectory(); break;
            case 7: adminDashboard(); break;
            case 8: salesReports(); break;

            case 9:
                saveData();
                success("All records saved successfully!");
                break;

            case 0:
                success("Logged out successfully!");
                break;

            default:
                error("Invalid choice. Try again.");
        }

        if (choice != 0)
            pauseScreen();

    } while (choice != 0);
}

// ==========================================
//                 MAIN FUNCTION
// ==========================================

int main()
{
    loadData();

    int choice;

    do
    {
        heading("SMART SHOPPING MALL MANAGEMENT SYSTEM");

        cout << "             WELCOME TO SMART MALL\n\n";

        cout << "1. Admin Login\n";
        cout << "2. Explore Mall Directory\n";
        cout << "0. Exit Application\n";

        choice = getInt("\nEnter Your Choice: ");

        switch (choice)
        {
            case 1:
                if (adminLogin())
                {
                    pauseScreen();
                    adminMenu();
                }
                else
                {
                    pauseScreen();
                }
                break;

            case 2:
                mallInformation();
                shopDirectory();
                pauseScreen();
                break;

            case 0:
                saveData();
                success("Thank you for using Smart Mall!");
                break;

            default:
                error("Invalid choice.");
                pauseScreen();
        }

    } while (choice != 0);

    return 0;
}
