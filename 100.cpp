#include <iostream>
#include <string>
#include <fstream>  
#include <sstream> 
#include <cstdlib>
#include <ctime>

//машинка
enum Color {
    White, Black, Red, Blue, Green
};
enum Mark {
    Toyota, BMW, Honda, Ford, Lada, Volkswagen
};
enum Model {
    Budget, Average, Pro, Ultra
};


class Car {
private:
    Model model;
    int mileage;
    int ownersCount;
    int horsepower;
    bool IsBroken;
    Color color;
    Mark mark;
    bool exist;

public:
    Car() : model(Model::Budget), mileage(0), ownersCount(0), horsepower(0), IsBroken(false), color(Color::White), mark(Mark::Toyota), exist(false) {}



    void saveToFile(Car myCar, const std::string& filename) {
        if (exist == false) {
            std::cout << "You should gain a car first.\n\n";
            myCar.ui(myCar, filename);
        }
        std::ofstream file(filename);

        if (file.is_open()) {
            file << model << std::endl;
            file << mileage << std::endl;
            file << ownersCount << std::endl;
            file << horsepower << std::endl;
            file << IsBroken << std::endl;
            file << color << std::endl;
            file << mark << std::endl;
            file.close();
            std::cout << "Car data saved to " << filename << "\n\n";
        }
        else {
            std::cout << "Unable to open file for saving." << std::endl;
        }
    }
    bool loadFromFile(Car myCar) {
        std::string filename = "car_data.txt";
        bool dataCorrupted{};
        system("cls");
        std::ifstream file(filename);

        if (file.is_open() && dataCorrupted == false) {
            dataCorrupted = false;


            int temp = 100;
            file >> temp;
            model = (Model)temp;
            file >> mileage;
            file >> ownersCount;
            file >> horsepower;
            file >> IsBroken;
            file >> temp;
            color = (Color)temp;
            file >> temp;
            mark = (Mark)temp;
            file.close();

            if (file.fail() ||
                (Model)temp < 0 || (Model)temp > 3 ||
                (Color)temp < 0 || (Color)temp > 4 ||
                (Mark)temp < 0 || (Mark)temp > 5 ||
                mileage < 0 || mileage > 1000000 ||
                ownersCount < 0 || ownersCount > 100 ||
                horsepower < 50 || horsepower > 200) {

                exist = false;
                std::cout << "Corrupted file, unable to load.\n\n";
                return false;
            }
            /*if (temp > 6 || temp < 0 || mileage < 0 || ownersCount < 0 || horsepower < 50 || horsepower > 120) {
                exist = false;
                std::cout << "Corrupted file, unable to load.\n\n";
                dataCorrupted = true;
                myCar.ui(myCar, filename);
            }*/
            exist = true;
            std::cout << "Car data loaded from " << filename << "\n\n";
            return true;
        }
        else {
            if (dataCorrupted == true) {
                std::cout << "Corrupted file, unable to load.\n\n";
                return false;
            }
            std::cout << "No saved data or unable to open file.\n" << std::endl;
            return false;
        }
    }
    void sale(Car myCar, std::string filename) {
        if (exist == false) {
            std::cout << "You should gain a car first.\n\n";
            myCar.ui(myCar, filename);
        }
        std::cout << "This car was succesfully send out for sale.\n\n";
        ownersCount++;
        exist = false;
    }
    void carCrash() {
        if (IsBroken == true && rand() % 10 < 4) {
            std::cout << "Your car was obliterated in a car crash.\n";
            exist = false;
        }
    }
    void drive(Car myCar, std::string filename) {
        if (exist == false) {
            std::cout << "You should gain a car first.\n\n";
            myCar.ui(myCar, filename);
        }
        std::cout << "Drive this car to gain mileage. How much km would you drive? (0-1000)\n";

        /*std::string abc;
        std::getline(std::cin, abc);
        int km=std::stoi(abc);*/


        int km;
        std::cin >> km;

        while (std::cin.fail() || km < 0 || km>1000) {
            std::cout << "Wrong input. Enter a proper number. (0-1000)\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cin >> km;
        }

        if (IsBroken == true) {
            std::cout << "Car is broken, it needs to be repaired or it can result in a car crash.\n";
        }
        if (km > 0) {
            std::cout << "Car successfully achieved destination.\n";
            mileage += km;
        }
        else if (km == 0) {
            std::cout << "Car successfully waited.\n";
        }
        else {
            std::cout << "Impossible distance.\n";
            /*return;*/
        }
        std::srand(std::time(0));
        if (IsBroken == false && rand() % 10 < 3 && km != 0) {
            IsBroken = true;
            std::cout << "Car got broken.\n";
        }
        if (mileage > 1000000) {
            std::cout << "Car got too much mileage, it got obliterated due to overuse.\n";
            exist = false;
            return;
        }
        carCrash();
    }
    void repair(Car myCar, std::string filename) {
        if (exist == false) {
            std::cout << "You should gain a car first.\n\n";
            myCar.ui(myCar, filename);
        }
        if (IsBroken == false) {
            std::cout << "Car wasn't broken.\n\n";
        }
        else if (IsBroken == true) {
            IsBroken = false;
            std::cout << "Car was fixed.\n\n";
        }
    }
    void carChoose(Car myCar, std::string filename) {
        if (exist == true) {
            std::cout << "You've got a car already, if you want a new car you should sell this one first.\n" << "\n";
            myCar.ui(myCar, filename);
        }
        std::cout << "Choose a car by typing a corresponding number." << "\n";
        std::cout << "1-Average Lada, white color, 12000 km mileage, 12 owners count, 80 horsepower." << "\n";
        std::cout << "2-Pro BMW, black color, 5000 km mileage, 3 owners count, 120 horsepower." << "\n";
        std::cout << "3-Pro Ford, blue color, 6000 km mileage, 5 owners count, 110 horsepower." << "\n";
        std::cout << "4-Budget Toyota, red color, 9000 km mileage, 8 owners count, 70 horsepower." << "\n";
        /*std::cout << "5-Average Ford, green color, 8000 km mileage, 4 owners count, 90 horsepower." << "\n";
        std::cout << "6-Ultra Volkswagen, white color, 6000 km mileage, 2 owners count, 130 horsepower." << "\n";*/

        int chs;
        std::cin >> chs;
        /*std::getline(std::cin, chs);*/
        /*if (chs == '1') {
        }*/
        while (std::cin.fail() || chs > 4 || chs < 1) {
            std::cout << "Wrong input. Enter a proper number (1-4).\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cin >> chs;
        }
        switch (chs) {
        case 1:
            model = Average;
            mileage = 12000;
            ownersCount = 12;
            horsepower = 80;
            color = White;
            mark = Lada;
            exist = true;
            break;
        case 2:
            model = Pro;
            mileage = 5000;
            ownersCount = 3;
            horsepower = 120;
            color = Black;
            mark = BMW;
            exist = true;
            break;
        case 3:
            model = Pro;
            mileage = 6000;
            ownersCount = 5;
            horsepower = 110;
            color = Blue;
            mark = Ford;
            exist = true;
            break;
        case 4:
            model = Budget;
            mileage = 9000;
            ownersCount = 8;
            horsepower = 70;
            color = Red;
            mark = Toyota;
            exist = true;
            break;
        }
        system("cls");
    }
    void carCreate(Car myCar, std::string filename) {
        if (exist == true) {
            std::cout << "You've got a car already, if you want a new car you should sell this one first.\n" << "\n";
            myCar.ui(myCar, filename);
        }
        std::cout << "Create your car.\n\n";
        std::cout << "Choose car's model. 0-Budget, 1-Average, 2-Pro, 3-Ultra." << "\n";
        std::string mdl;
        std::getline(std::cin, mdl);

        while (mdl.length() != 1 || mdl < "0" || mdl > "3") {
            std::cout << "Wrong input. Enter a proper number. (0-3)\n";
            std::getline(std::cin, mdl);
            std::cin.clear();
        }
        model = (Model)std::stoi(mdl);

        std::cout << "Choose car's mileage (number of km driven in total) (0-50000)." << "\n";
        std::cin >> mileage;
        std::string mlg;

        while (std::cin.fail() || mileage < 0 || mileage > 50000) {
            std::cout << "Wrong input. Enter a proper number. (0-50000)\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cin >> mileage;
        }

        std::cout << "Choose car's owners count (how much owners it had) (0-50)" << "\n";
        std::cin >> ownersCount;
        while (std::cin.fail() || ownersCount < 0 || ownersCount > 50) {
            std::cout << "Wrong input. Enter a proper number. (0-50)\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cin >> ownersCount;
        }

        std::cout << "Choose car mark. 0-Toyota, 1-BMW, 2-Honda, 3-Ford, 4-Lada, 5-Volkswagen." << "\n";

        std::string mrk = "0";
        std::getline(std::cin, mrk);
        std::cin.clear();
        while (mrk < "0" || mrk > "5") {
            std::cout << "Wrong input. Enter a proper number. (0-5)\n";
            std::getline(std::cin, mrk);
        }
        mark = (Mark)std::stoi(mrk);

        std::cout << "Choose car's horsepower (number of how powerful it is) (50-140)" << "\n";
        std::cin >> horsepower;
        while (std::cin.fail() || horsepower < 50 || horsepower > 140) {
            std::cout << "Wrong input. Enter a proper number. (50-140)\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cin >> horsepower;
        }

        std::cout << "Choose car's color. 0-white, 1-black, 2-red, 3-blue, 4-green." << "\n";

        std::string clr;
        std::getline(std::cin, clr);
        std::cin.clear();
        while (clr < "0" || clr > "4") {
            std::cout << "Wrong input. Enter a proper number. (0-4)\n";
            std::getline(std::cin, clr);
        }
        color = (Color)std::stoi(clr);
        exist = true;
        std::cout << "Car created.\n";
        return;
    }
    void CarInfo() {
        if (exist == false) {
            std::cout << "You should gain a car first.\n\n";
        }
        else {
            std::cout << "Information of this car.\n";
            std::cout << "Mark:" << mark << "\n";
            std::cout << "Model:" << model << "\n";
            std::cout << "Mileage:" << mileage << "\n";
            std::cout << "Count of previous owners:" << ownersCount << "\n";
            std::cout << "Amounts of Horsepower:" << horsepower << "\n";
            std::cout << "Is it broken?:" << IsBroken << "\n";
            std::cout << "Color:" << color << "\n\n";
        }
    }
    /*void Exit(Car myCar, std::string filename){
        std::cout << "Do you want to exit? (y/n)\n";
        std::string act2;
        std::getline(std::cin, act2);
        if (act2 == "y") {
            return;
        }
    }*/
    void ui(Car myCar, std::string filename) {

        std::string act;
        while (true) {
            
            std::cout << "Choose your action.\n";
            std::cout << "Type 1 to display car information.\n";
            std::cout << "Type 2 to sale car.\n";
            std::cout << "Type 3 to drive car.\n";
            std::cout << "Type 4 to repair car.\n";
            std::cout << "Type 5 to choose car from list.\n";
            std::cout << "Type 6 to create custom car.\n";
            std::cout << "Type 7 to save car.\n";
            std::cout << "Type 8 to load car.\n";
            std::cout << "Type 9 to exit.\n";

            std::getline(std::cin, act);
            if (!(std::cin >> act)) { 
                if (std::cin.eof()) {
                    std::cout << "\nCtrl+z was typed. Returning.\n";
                }
                else {
                    std::cout << "Invalid option. Try again. (1-9)\n\n";
                }
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            }

            system("cls");

            switch (act[0]) {
            case '1':
                myCar.CarInfo();
                break;
            case '2':
                myCar.sale(myCar, filename);
                break;
            case '3':
                myCar.drive(myCar, filename);
                break;
            case '4':
                myCar.repair(myCar, filename);
                break;
            case '5':
                myCar.carChoose(myCar, filename);
                break;
            case '6':
                myCar.carCreate(myCar, filename);
                break;
            case '7':
                myCar.saveToFile(myCar, filename);
                break;
            case '8':
                myCar.loadFromFile(myCar);
                break;
            case '9':
                if (exist == true) {
                    std::cout << "Do you want to save car before exiting? (y/n): \n";
                    std::string saveChoice;
                    std::getline(std::cin, saveChoice);
                    if (saveChoice == "y" || saveChoice == "Y") {
                        saveToFile(myCar, filename);
                    }
                    std::cout << "Exiting.\n";
                    return;
                }
                else {
                    std::cout << "Exiting.\n";
                    return;
                }
                break;
            default:
                /*if (exist==true) {
                    std::cout << "Do you want to save car before exiting? (y/n): \n";
                    std::string saveChoice;
                    std::cin >> saveChoice;
                    if (saveChoice == "y") {
                        myCar.saveToFile(myCar, filename);
                        return;
                    }
                }*/

                std::cout << "Invalid option. Try again. (1-9)\n\n";


                //else {
                //    

                //    /*std::cout << "Do you really want to exit? If not type 'n' to return (y/n): \n";
                //    std::string savechoice;
                //    std::getline(std::cin savechoice;
                //    if (savechoice == "n") {
                //        myCar.ui(myCar, filename);
                //    }
                //    else {
                //        std::cout << "Exiting.\n";
                //        return;
                //    }*/
                //}

            }
            /*std::cout << " \n";*/
        }
    }
};

int main()
{
    std::string filename = "car_data.txt";
    Car myCar;
    myCar = Car();
    myCar.ui(myCar, filename);
    return 0;
}