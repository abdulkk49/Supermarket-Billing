
//***************************************************************
//SUPERMARKET BILLING PROJECT
//IT IS ASSUMED THAT ALL PRODUCTS HAVE DIFFERENT PRODUCT NUMBERS.
//****************************************************************
#include<iostream>
#include conio
#include<fstream>
#include<string.h>
#include<stdlib.h>

using namespace std;

//***************************************************************
// CLASS USED IN PROJECT
//***************************************************************
class product
{
    int prod_no;
    char name[50];
    float price, qty, dis;
    public:
        product()
        {
            prod_no = 0; price = 0; qty = 0; dis = 0; strcpy(name , "No product");
        }
        void getProductData()
        {
            cout << "\nPlease Enter The Product No. of The Product: ";
            cin >> prod_no;
            cin.ignore();
            cout << "\n\nPlease Enter The Name of The Product: ";
            cin.get(name, 50);
            cout << "\nPlease Enter The Price of The Product: ";
            cin >> price;
            cout << "\nPlease Enter The Discount (%): ";
            cin >> dis;
            getch();
        }

        void showProductData()
        {
            cout << "\nThe Product No. of The Product : " << prod_no;
            cout << "\nThe Name of The Product : "<< name;
            cout << "\nThe Price of The Product : " << price;
            cout << "\nDiscount : " << dis;
        }
        int storeProductData();
        void viewAllProducts();
        void searchProductData(int);             //FILE HANDLING FUNCTIOMS
        void modifyProductData();
        void deleteProductData();
        void menu();
        void placeOrder();

    }; //class ends here

//***************************************************************
// function to write in file
//****************************************************************

int product:: storeProductData()
{

    if(price == 0)
    {
        cout<<"\nProduct data not initialised";
        return 0;
    }
    ofstream fout;
    fout.open("Supermarket.dat", ios::out | ios::app | ios::binary);
    fout.write((char*) this, sizeof(*this));
    fout.close();
    cout << "\n\nThe Product Has Been Created ";
    return 1;
}
//***************************************************************
// function to read all records from file
//****************************************************************
void product:: viewAllProducts()
{
    system("cls");
    ifstream fin;
    fin.open("Supermarket.dat", ios::in | ios::binary);
    if(!fin)
        cout << "File not found\n";
    else
    {
        fin.read((char*) this, sizeof(*this));
        while(!fin.eof())
        {
           showProductData();
           fin.read((char*) this, sizeof(*this));
        }
    fin.close();
    getch();
    }
}
//***************************************************************
// function to read specific record from file
//****************************************************************
void product:: searchProductData(int n)
{
    int flag = 0;
    ifstream fin;
    fin.open("Supermarket.dat", ios::in | ios::binary);
    if(!fin)
        cout << "File not found\n";
    else
    {
        fin.read((char*) this, sizeof(*this));
        while(!fin.eof())
        {
        if (prod_no == n){
            system("cls");
            showProductData();
            flag = 1;
            }
        if(flag == 1)
            break;
        fin.read((char*) this, sizeof(*this));
        }
    }
    if (flag == 0)
        cout << "\n\nRecord not exist.";
    fin.close();
    getch();
}
//***************************************************************
// function to modify record of file
//****************************************************************
void product:: modifyProductData()
{
    int no, found = 0;
    fstream file;
    system("cls");
    cout << "\n\n\tTo modify a product ";
    cout << "\n\n\tPlease enter the product no. of the product: ";
    cin >> no;
    file.open("Supermarket.dat", ios::in | ios::out | ios::ate | ios::binary);
    file.seekg(0);
    file.read((char*) this, sizeof(*this));
    while (!file.eof())
    {
        if (prod_no == no)
        {
            showProductData();
            cout << "\nPlease Enter The New Details of Product" << endl;
            getProductData();
            int pos = -1 * sizeof(*this);
            file.seekp(pos, ios::cur);
            file.write((char*) this, sizeof(*this));
            cout << "\n\n\t Record Updated";
            found = 1;
        }
        file.read((char*) this, sizeof(*this));

    }
    file.close();
    if (found == 0)
        cout << "\n\n Record Not Found ";
}
//***************************************************************
// function to delete record of file
//****************************************************************
void product:: deleteProductData()
{
    int no;
    system("cls");
    cout << "\n\n\n\tDelete Record";
    cout << "\n\nPlease enter the product no. of the Product you wish to delete: ";
    cin >> no;
    ifstream fin;
    ofstream fout;
    fin.open("Supermarket.dat", ios::in | ios::binary);
    if(!fin)
        cout << "File not found\n";
    else{
    fout.open("tempfile.dat", ios::out | ios::binary);
    fin.read((char*) this, sizeof(*this));
        while(!fin.eof())
        {
            if(prod_no != no)
                fout.write((char*) this, sizeof(*this));
            fin.read((char*) this, sizeof(*this));
        }
    fin.close();
    fout.close();
    remove("Supermarket.dat");
    rename("tempfile.dat", "Supermarket.dat");
    cout << "\n\n\tRecord Deleted ..";
    getch();
    }
}
//***************************************************************
// function to display all products price list
//****************************************************************

void product:: menu()
{
    system("cls");
    ifstream fin;
    fin.open("Supermarket.dat", ios::in | ios::binary);
    if (!fin)
    {
        cout << "ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create File ";
        cout << "\n\n\n Program is closing ....";
        getch();
        exit(0);
    }

    cout << "\n\n\t\tProduct MENU\n\n";
    cout << "====================================================\n";
    cout << "PRODUCT NO.\t\tNAME\t\tPRICE\n";
    cout << "====================================================\n";
    fin.read((char * ) this, sizeof(*this));
    while(!fin.eof())
    {
        cout << prod_no << "\t\t" << name << "\t\t" << price << endl;
        fin.read((char *) this, sizeof(*this));
    }
    fin.close();
}

//***************************************************************
// function to place order and generating bill for Products
//****************************************************************

void product:: placeOrder()
{
    int order_arr[50], quan[50], c = 0, x ;
    float amt, damt, total = 0;
    char ch = 'Y';
    menu();
    cout << "\n============================";
    cout << "\n PLACE YOUR ORDER";
    cout << "\n============================\n";
    do
    {
        cout << "\n\nEnter The Product No. Of The Product : ";
        cin >> order_arr[c];
        cout << "\nQuantity in number : ";
        cin >> quan[c];
        c++;
        cout << "\nDo You Want To Order Another Product ? (y/n) : ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    cout << "\n\nThank You For Placing The Order..";
    getch();
    system("cls");
    cout << "\n\n******************************** INVOICE ************************\n";
    cout << "\nPr No.\tPr Name\tQuantity \tPrice \tAmount \tAmount after discount \n ";
    ifstream fin;
    for ( x = 0; x <= c; x++)
    {
        fin.open("Supermarket.dat", ios:: in | ios::binary );
        fin.read((char * ) this, sizeof(*this));
        while (!fin .eof())
        {
            if (prod_no == order_arr[x])
            {
                amt = price * quan[x];
                damt = amt - (amt * dis / 100);
                cout << "\n" << order_arr[x] << "\t" << name <<
                    "\t" << quan[x] << "\t\t" << price << "\t" << amt << "\t\t" << damt;
                total += damt;
            }
            fin.read((char * ) this, sizeof(*this));
        }

        fin.close();
    }
    cout << "\n\n\t\t\t\t\tTOTAL = " << total;
    getch();
}
//***************************************************************
// ADMINSTRATOR MENU FUNCTION
//****************************************************************
void adminMenu(product p1)
{
    system("cls");
    char ch2;
    cout << "\n\n\n\tADMIN MENU";
    cout << "\n\n\t1.CREATE PRODUCT";
    cout << "\n\n\t2.DISPLAY ALL PRODUCTS";
    cout << "\n\n\t3.QUERY ";
    cout << "\n\n\t4.MODIFY PRODUCT";
    cout << "\n\n\t5.DELETE PRODUCT";
    cout << "\n\n\t6.VIEW PRODUCT MENU";
    cout << "\n\n\t7.BACK TO MAIN MENU";
    cout << "\n\n\tPlease Enter Your Choice (1-7) ";
    ch2 = getche();
    switch (ch2)
    {
    case '1':
        system("cls");
        p1.getProductData();
        p1.storeProductData();
        getch();
        break;
    case '2':
        p1.viewAllProducts();
        break;
    case '3':
        int num;
        system("cls");
        cout << "\n\n\tPlease Enter The Product No. ";
        cin >> num;
        p1.searchProductData(num);
        break;
    case '4':
        p1.modifyProductData();
        break;
    case '5':
        cout << "Before Deletion";
        p1.viewAllProducts();
        p1.deleteProductData();
        cout << "After deletion";
        p1.viewAllProducts();
        break;
    case '6':
        p1.menu();
        getch();
    case '7':
        break;
    default:
        cout << "\a";
        adminMenu(p1);
    }
}
//***************************************************************
// THE MAIN FUNCTION OF PROGRAM
//****************************************************************
int main()
{
    system("cls");
    product p1;
    char ch;
    do
    {
        cout<<"\t\t\t ============ AKSHAY SUPERMARKET, BITS PILANI ==============";
        cout << "\n\n\n\t****MAIN MENU****";
        cout << "\n\n\t01. CUSTOMER";
        cout << "\n\n\t02. ADMINISTRATOR";
        cout << "\n\n\t03. EXIT";
        cout << "\n\n\tPlease Select Your Option (1-3): ";
        ch = getche();
        switch (ch)
        {
        case '1':
            system("cls");
            p1.placeOrder();
            break;
        case '2':
            adminMenu(p1);
            break;
        case '3':
            exit(0);
        default:
            cout << "\a";
        }
    } while (ch != '3');
}

//***************************************************************
// END OF PROJECT
//***************************************************************


