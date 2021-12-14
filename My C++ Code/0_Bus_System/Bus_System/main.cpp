#include <iostream>
#include <iomanip>
#include <type_traits>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <windows.h>
#include <assert.h>
#include <time.h>
using namespace std;

class Bus
{
public:
    string Bus_Code;
    string LP;
    int CASE = 0;
    int time_A = 0;
    int time_B = 0;

public:
    Bus()
    {
        this->Bus_Code = "";
        this->LP = "";
        this->CASE = 0;
        this->time_A = 0;
        this->time_B = 0;
    }

    Bus(string buscode, string lp, int icase, int timea, int timeb)
    {
        this->Bus_Code = buscode;
        this->LP = lp;
        this->CASE = icase;
        this->time_A = timea;
        this->time_B = timeb;
    }

//    friend ostream &operator<<(ostream &out, const Bus &bus)
//    {
//        out << "Route           : " << bus.Bus_Code << "\n";
//        out << "License Plate   : " << bus.LP << "\n";
//        out << "Direction       : " << bus.CASE << "\n";
//        out << "Depart at       : " << bus.time_A << "\n";
//        out << "Arrive at       : " << bus.time_B;
//
//        return out;
//    }

    friend ostream &operator<<(ostream &out, const Bus &bus)
    {
        out << bus.Bus_Code << setw(3) << "|" << setw(12) << bus.LP
            << setw(3) << "|" << setw(4) << bus.CASE << setw(3) << "|"
            << setw(6) << bus.time_A << setw(3) << "|" << setw(5) << bus.time_B << setw(3) << "|";

        return out;
    }
};

typedef map<string, vector<Bus>> The_Bus_Map;

class BusSystem
{
    friend class Bus;

private:
    The_Bus_Map My_Bus_Map;
    unsigned long long int max_turn;

public:
    BusSystem()
    {
        this->max_turn = 0;
    }

    // Print the entire Bus and Route List
    void print_the_Bus_Map()
    {
        cout << "\n--------------------------------------------------------------------\n";
        cout << "DANH SACH CAC TUYEN VA CHUYEN BUS:\n";

        map<string, vector<Bus>>::iterator current_iterator = My_Bus_Map.begin();

        for (; current_iterator != My_Bus_Map.end(); current_iterator++)
        {
            for (auto index : current_iterator->second)
            {
                cout << index;
                cout << "\n................................\n";
            }

            cout << "------ END OF THIS ROUTE'S LIST --------\n";
        }

        cout << "--------------------------------------------------------------------\n";
    }

    // (Optional, function print list of Bus)
    void print_the_Bus_Map_ver_2()
    {
        map<string, vector<Bus>>::iterator current_iterator = My_Bus_Map.begin();

        cout << "------------------------------------------------\n";
        cout << "| Route | Liense Plate | CASE | Leave | Arrive |\n";
        cout << "------------------------------------------------\n";


        for (; current_iterator != My_Bus_Map.end(); current_iterator++)
        {
            for (auto index : current_iterator->second)
            {
                cout << "|" << setw(5) << index << endl;
            }

            cout << ",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n";
            cout << "|                END THIS ROUTE                |\n";
            cout << "''''''''''''''''''''''''''''''''''''''''''''''''\n";
        }
    }

    string query(string);
};

// ---------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------

// Console
void console(BusSystem *bus)
{
    cout << "\t\tBus System Program\n";
    cout << "Type \"!help\" for instruction.\n";

    while (1)
    {
        cout << ">> ";

        string command;
        getline(cin, command);

        if (command == "exit")
        {
            system("cls");
            int i = 4;
            while (i--)
            {
                 if (i == 1 || i == 0)
                    cout << "Exiting in " << i << " second.";
                else
                    cout << "Exiting in " << i << " seconds.";

                Sleep(1000);
                system("cls");
            }
            delete bus;
            break;
        }

        if (command == "!help")
        {
            cout << ">> : operator for input line\n";
            cout << "exit: stop program\n";
            continue;
        }

        bus->query(command);
        system("cls");

        bus->print_the_Bus_Map_ver_2();
    }
}

// TAKE THE FUCKING STRING, PLZ
// Remember to reference the string
string take_that_string(string &the_string)
{
    int i = 0;
    string result = "";
    string space = " ";

    int32_t found = the_string.find(space);

    if (found != -1)
    {
        while (the_string[i] != ' ')
        {
            result += the_string[i];
            i++;
        }
        the_string.erase(0, i + 1);
    }
    else
    {
        result = the_string;
        the_string.clear();
    }

    return result;
}

// Is the command valid ?
bool is_valid_instruction(string the_instruction)
{
    // Check special character
    // + - dont add
    string invalid_char = "!@#$%^&*(){}[]:;<>,.'|~`?/=";
    int invalid_char_size = invalid_char.size();

    // Checking special character
    for (int i = 0; i < invalid_char_size; i++)
    {
        int32_t found = the_instruction.find(invalid_char[i]);

        if (found != -1)
        {
            //cout << "\nHong duoc dau nhe!\n";
            return false;
        }
    }

    // Multiple spacebar
    int the_instruction_size = the_instruction.size();
    for (int i = 0; i < the_instruction_size - 1; i++)
    {
        if (the_instruction[i] == ' ' && the_instruction[i + 1] == ' ')
        {
            return false;
        }
    }

    // Check
    if (the_instruction[the_instruction_size - 1] == ' ' || the_instruction[0] == ' ')
        return false;
    else
        return true;
}

// Is the number valid ?
// truyen vao mot chuoi ma no se thanh so
bool is_valid_number(string the_instruction)
{
    // A1234
    if (the_instruction[0] < '0' || the_instruction[0] > '9')
        return false;

    // 000000
    if (stoi(the_instruction) == 0)
        return true;

    // Empty
    if (the_instruction == "")
        return false;

    int count_zero = 0;

    //vd 00012AB3 => 12AB3
    if (the_instruction[0] == '0')
    {
        while (the_instruction[count_zero] == '0')
        {
            count_zero += 1;
        }

        the_instruction.erase(0, count_zero);
    }

    if ((to_string(stoi(the_instruction)) != the_instruction) || stoi(the_instruction) < 0)
        return false;

    return true;
}

// ---------------------------------------------------------------------------------------------
// THE QUERY FUNCTION, LADIES AND GENTLEMENS
string BusSystem::query(string instruction)
{
    // Invalid command
    if (!is_valid_instruction(instruction))
        return "-1";

    int request = 10;
    string the_request = "";
    // Get the request
    the_request = take_that_string(instruction);

    // Select the request
    {
        if (the_request == "SQ")
            request = 1;
        else if (the_request == "INS")
            request = 2;
        else if (the_request == "DEL")
            request = 3;
        else if (the_request == "CS")
            request = 4;
        else if (the_request == "CE")
            request = 5;
        else if (the_request == "GS")
            request = 6;
        else if (the_request == "GE")
            request = 7;
        else
            return "-1"; // Lenh ko hop le
    }

    string the_code = "";
    string the_LP = "";
    int the_case = 2;
    int the_timeA = 0;
    int the_timeB = 0;

    // Do the request
    {
        switch (request)
        {
        case 1: // SQ
        {
            if (!is_valid_number(instruction))
                return "-1";

            this->max_turn = stoi(instruction);
            //cout << this->max_turn;
            return "1";
            break;
        }
        case 2: // INS
        {
            // Take the information
            {
                // Get the CODE
                the_code = take_that_string(instruction);
                if (the_code.length() > 5)
                    return "-1";
                //cout << the_code << endl;

                // Get the LP
                the_LP = take_that_string(instruction);
                //cout << the_LP << endl;

                if (instruction == "")
                    return "-1";

                // Luu y:
                // 1 la time A
                // INS SG553 TDH-132001 1 5
                string pumpkin_1 = take_that_string(instruction);
                //cout << pumpkin_1 << endl;

                if (instruction == "")
                    return "-1";

                string pumpkin_2 = take_that_string(instruction);
                //cout << pumpkin_2 << endl;

                // CASE
                // Time A == 0 || 1
                if (pumpkin_1 == "0" || pumpkin_1 == "1")
                {
                    // Khong co case
                    if (instruction == "")
                    {
                        the_case = 0;

                        if (!is_valid_number(pumpkin_2))
                            return "-1";

                        the_timeA = stoi(pumpkin_1);
                        the_timeB = stoi(pumpkin_2);
                    }
                    // Still have CASE
                    else
                    {
                        if (!is_valid_number(pumpkin_1) || !is_valid_number(pumpkin_2))
                            return "-1";

                        // Get the CASE
                        the_case = stoi(pumpkin_1);
                        // Get the timeA
                        the_timeA = stoi(pumpkin_2);
                        // Get the time B
                        string temp_timeB = take_that_string(instruction);

                        if (!is_valid_number(temp_timeB))
                            return "-1";

                        the_timeB = stoi(temp_timeB);
                    }
                }
                // PUMPKIN_1 == 0000, 12345, .......
                else
                {
                    if (instruction == "")
                    {
                        if (!is_valid_number(pumpkin_1) || !is_valid_number(pumpkin_2))
                            return "-1";

                        the_case = 0;
                        the_timeA = stoi(pumpkin_1);
                        the_timeB = stoi(pumpkin_2);
                    }
                    else
                    {
                        return "-1";
                    }
                }
            }

            // Time A > Time B
            // Tuyen da dat so chuyen toi da
            if (My_Bus_Map[the_code].size() == this->max_turn || the_timeA >= the_timeB)
                return "-1";

            // Create new Bus
            Bus insert_Bus(the_code, the_LP, the_case, the_timeA, the_timeB);

            // Insertion
            bool success = true;

            // Map is empty || the CODE is empty
            if (My_Bus_Map.empty() || My_Bus_Map[the_code].empty())
            {
                My_Bus_Map[the_code].push_back(insert_Bus);
                success = true;
            }
            // Map is not empty but the CODE is also not empty
            else if (!My_Bus_Map[the_code].empty())
            {
                vector<Bus>::iterator current_iterator = My_Bus_Map[the_code].begin();
                while (current_iterator != My_Bus_Map[the_code].end())
                {
                    // Khong co chuyen Bus cung gio xuat ben trong cung 1 tuyen
                    if ((*current_iterator).CASE == the_case && (*current_iterator).time_A == the_timeA)
                    {
                        success = false;
                        break;
                    }

                    // Bien kiem soat da ton tai
                    // Gio xuat ben  > gio cap ben truoc do
                    if ((*current_iterator).LP == the_LP)
                    {
                        if ((*current_iterator).time_B < the_timeA)
                        {
                            success = true;
                        }
                        else
                        {
                            success = false;
                            break;
                        }
                    }

                    current_iterator++;
                }

                if (success)
                    My_Bus_Map[the_code].push_back(insert_Bus);
            }

            // Return value
            if (success)
            {
                int a = My_Bus_Map[the_code].size();
                return to_string(a);
            }
            else
                return "-1";

            break;
        }
        case 3: // DEL
        {
            int count_delete = 0;

            if (instruction == "")
                return "-1";

            // Get the CODE
            the_code = take_that_string(instruction);
            if (the_code.length() > 5)
                    return "-1";

            // Xoa tat ca
            if (instruction == "")
            {
                count_delete = My_Bus_Map[the_code].size();

                // Tao 1 vector Bus trong
                vector<Bus> empty_Bus_List;
                My_Bus_Map[the_code] = empty_Bus_List;
            }
            // Chi xoa 1 phan
            else
            {
                string temp = take_that_string(instruction);
                if (!is_valid_number(temp))
                    return "-1";

                int first_limit = stoi(temp);

                // Khong co 2nd limit
                if (instruction == "")
                {
                    vector<Bus>::iterator current_iterator = My_Bus_Map[the_code].begin();

                    // Neu chi co 1 moc thoi gian thi
                    // == moc thoi gian do
                    int ite_count = 0;
                    int vector_size = My_Bus_Map[the_code].size();
                    while (current_iterator != My_Bus_Map[the_code].end())
                    {
                        // khi swap xong thi current_iterator se tro vao ptu vua swap
                        // 1 2 (3) 4 5
                        // 1 2 (5) 4 3
                        // Neu swap thi ko tang iterator len
                        if ((*current_iterator).time_A == first_limit)
                        {
                            if (ite_count == vector_size - 1)
                            {
                                My_Bus_Map[the_code].pop_back();
                                count_delete += 1;
                                break;
                            }
                            else
                            {
                                swap((*current_iterator), My_Bus_Map[the_code].back());
                                My_Bus_Map[the_code].pop_back();
                                //My_Bus_Map[the_code].erase(current_iterator);
                                count_delete += 1;
                            }
                        }
                        else
                        {
                            ite_count += 1;
                            current_iterator++;
                        }
                    }
                }
                // Co 2nd limit
                else if (instruction != "")
                {
                    temp = take_that_string(instruction);
                    if (!is_valid_number(temp))
                        return "-1";

                    int second_limit = stoi(temp);

                    if (instruction != "")
                        return "-1";

                    // Sai format
                    if (first_limit > second_limit)
                        return "-1";

                    vector<Bus>::iterator current_iterator = My_Bus_Map[the_code].begin();
                    int ite_count = 0;
                    int vector_size = My_Bus_Map[the_code].size();
                    while (current_iterator != My_Bus_Map[the_code].end())
                    {
                        if ((*current_iterator).time_A >= first_limit && (*current_iterator).time_A <= second_limit)
                        {
                            if (ite_count == vector_size - 1)
                            {
                                My_Bus_Map[the_code].pop_back();
                                count_delete += 1;
                                break;
                            }
                            else
                            {
                                swap((*current_iterator), My_Bus_Map[the_code].back());
                                My_Bus_Map[the_code].pop_back();
                                //My_Bus_Map[the_code].erase(current_iterator);
                                count_delete += 1;
                            }
                        }
                        else
                        {
                            ite_count += 1;
                            current_iterator++;
                        }
                    }
                }
            }

            return to_string(count_delete);
            break;
        }
        case 4: // CS
        {
            // Take the information
            // Get the CODE
            the_code = take_that_string(instruction);
            if (the_code.length() > 5)
                    return "-1";

            // Get the current time
            string the_current_time = take_that_string(instruction);
            if (!is_valid_number(the_current_time))
                return "-1";

            int current_time = stoi(the_current_time);

            // Get the CASE
            if (instruction == "")
                the_case = 3;
            else
            {
                string for_the_case = take_that_string(instruction);

                if (instruction != "")
                    return "-1";

                if (to_string(stoi(for_the_case)) != for_the_case)
                    return "-1";

                if (for_the_case == "0")
                    the_case = stoi(for_the_case);
                else if (for_the_case == "1")
                    the_case = stoi(for_the_case);
                else if (for_the_case != "0" || for_the_case != "1")
                    return "-1";
            }

            // Counting.......
            int result = 0;
            vector<Bus>::iterator current_iterator = My_Bus_Map[the_code].begin();
            while (current_iterator != My_Bus_Map[the_code].end())
            {
                if ((*current_iterator).CASE == the_case && (*current_iterator).time_A <= current_time && (*current_iterator).time_B >= current_time)
                {
                    result += 1;
                }
                else if (the_case == 3)
                {
                    if ((*current_iterator).time_A <= current_time && (*current_iterator).time_B >= current_time)
                        result += 1;
                }

                current_iterator++;
            }

            return to_string(result);
            break;
        }
        case 5: // CE
        {
            // Take the information
            // Get the CODE
            the_code = take_that_string(instruction);
            if (the_code.length() > 5)
                    return "-1";

            // Get the current time
            string the_current_time = take_that_string(instruction);
            if (!is_valid_number(the_current_time))
                return "-1";

            int current_time = stoi(the_current_time);

            // Get the CASE
            if (instruction == "")
                the_case = 3;
            else
            {
                string for_the_case = take_that_string(instruction);

                if (instruction != "")
                    return "-1";

                if (to_string(stoi(for_the_case)) != for_the_case)
                    return "-1";

                if (for_the_case == "0")
                    the_case = stoi(for_the_case);
                else if (for_the_case == "1")
                    the_case = stoi(for_the_case);
                else if (for_the_case != "0" || for_the_case != "1")
                    return "-1";
            }

            // Counting.......
            int result = 0;
            vector<Bus>::iterator current_iterator = My_Bus_Map[the_code].begin();
            while (current_iterator != My_Bus_Map[the_code].end())
            {
                if ((*current_iterator).CASE == the_case && (*current_iterator).time_B < current_time)
                {
                    result += 1;
                }
                else if (the_case == 3)
                {
                    if ((*current_iterator).time_B < current_time)
                        result += 1;
                }

                current_iterator++;
            }

            return to_string(result);
            break;
        }
        case 6: // GS
        {
            string result = "";
            int check_duplicate = 2;

            // Get the CODE
            the_code = take_that_string(instruction);
            if (the_code.length() > 5)
                    return "-1";

            // Get the current time
            string the_current_time = take_that_string(instruction);
            if (!is_valid_number(the_current_time))
                return "-1";

            int current_time = stoi(the_current_time);

            // Get the CASE
            if (instruction == "")
                the_case = 3;
            else
            {
                string for_the_case = take_that_string(instruction);

                if (instruction != "")
                    return "-1";

                if (to_string(stoi(for_the_case)) != for_the_case)
                    return "-1";

                if (for_the_case == "0")
                    the_case = stoi(for_the_case);
                else if (for_the_case == "1")
                    the_case = stoi(for_the_case);
                else if (for_the_case != "0" || for_the_case != "1")
                    return "-1";
            }

            // Set min diff
            int min_diff = -1;
            vector<Bus>::iterator current_iterator = My_Bus_Map[the_code].begin();
            while (current_iterator != My_Bus_Map[the_code].end())
            {
                if (the_case == 3)
                {
                    if ((*current_iterator).time_A <= current_time)
                    {
                        min_diff = current_time - (*current_iterator).time_A;
                        result = (*current_iterator).LP;
                        break;
                    }
                }
                // case == 0 || 1
                else if (the_case == 0 || the_case == 1)
                {
                    if ((*current_iterator).time_A <= current_time && (*current_iterator).CASE == the_case)
                    {
                        min_diff = current_time - (*current_iterator).time_A;
                        result = (*current_iterator).LP;
                        break;
                    }
                }

                current_iterator++;
            }

            // Find the one
            //current_iterator = My_Bus_Map[the_code].begin();
            while (current_iterator != My_Bus_Map[the_code].end())
            {
                current_iterator++;

                if (the_case == 0 || the_case == 1)
                {
                    if ((*current_iterator).CASE == the_case && (*current_iterator).time_A <= current_time)
                    {
                        int a = current_time - (*current_iterator).time_A;

                        if (a < min_diff)
                        {
                            min_diff = a;
                            result = (*current_iterator).LP;
                        }
                    }
                }
                else if (the_case == 3)
                {
                    if ((*current_iterator).time_A <= current_time)
                    {
                        int a = current_time - (*current_iterator).time_A;

                        // Truong hop co 2 chuyen deu thoa, uu tien chieu di 0
                        if (a == min_diff)
                        {
                            if (check_duplicate == 1 && (*current_iterator).CASE == 0)
                            {
                                check_duplicate = 0;
                                result = (*current_iterator).LP;
                            }
                            else if (check_duplicate == 0 && (*current_iterator).CASE == 1)
                            {
                                check_duplicate = 0;
                            }
                        }
                        else if (a < min_diff)
                        {
                            check_duplicate = (*current_iterator).CASE;
                            min_diff = a;
                            result = (*current_iterator).LP;

                        }
                    }
                }
            }

            if (result == "")
                return "-1";
            else
                return result;

            break;
        }
        case 7: // GE
        {
            string result = "";
            int check_duplicate = 2;

            // Get the CODE
            the_code = take_that_string(instruction);
            if (the_code.length() > 5)
                    return "-1";

            // Get the current time
            string the_current_time = take_that_string(instruction);
            if (!is_valid_number(the_current_time))
                return "-1";

            int current_time = stoi(the_current_time);

            // Get the CASE
            if (instruction == "")
                the_case = 3;
            else
            {
                string for_the_case = take_that_string(instruction);

                if (instruction != "")
                    return "-1";

                if (to_string(stoi(for_the_case)) != for_the_case)
                    return "-1";

                if (for_the_case == "0")
                    the_case = stoi(for_the_case);
                else if (for_the_case == "1")
                    the_case = stoi(for_the_case);
                else if (for_the_case != "0" || for_the_case != "1")
                    return "-1";
            }

            // Set min diff
            int min_diff = -1;
            vector<Bus>::iterator current_iterator = My_Bus_Map[the_code].begin();
            while (current_iterator != My_Bus_Map[the_code].end())
            {
                if (the_case == 3)
                {
                    if ((*current_iterator).time_B < current_time)
                    {
                        min_diff = current_time - (*current_iterator).time_B;
                        result = (*current_iterator).LP;
                        break;
                    }
                }
                // case == 0 || 1
                else if (the_case == 0 || the_case == 1)
                {
                    if ((*current_iterator).time_B < current_time && (*current_iterator).CASE == the_case)
                    {
                        min_diff = current_time - (*current_iterator).time_B;
                        result = (*current_iterator).LP;
                        break;
                    }
                }

                current_iterator++;
            }

            // Khong tim thay Time B nho hon
            if (min_diff == -1)
                return "-1";

            // Find the one
            //current_iterator = My_Bus_Map[the_code].begin();
            while (current_iterator != My_Bus_Map[the_code].end())
            {
                current_iterator++;

                if (the_case == 0 || the_case == 1)
                {
                    if ((*current_iterator).CASE == the_case && (*current_iterator).time_B < current_time)
                    {
                        int a = current_time - (*current_iterator).time_B;

                        if (a < min_diff)
                        {
                            min_diff = a;
                            result = (*current_iterator).LP;
                        }
                    }
                }
                else if (the_case == 3)
                {
                    if ((*current_iterator).time_B < current_time)
                    {
                        int b = current_time - (*current_iterator).time_B;

                        // Truong hop co 2 chuyen deu thoa, uu tien chieu di 0
                        if (b == min_diff)
                        {
                            if (check_duplicate == 1 && (*current_iterator).CASE == 0)
                            {
                                check_duplicate = 0;
                                result = (*current_iterator).LP;
                            }
                            else if (check_duplicate == 0 && (*current_iterator).CASE == 1)
                            {
                                check_duplicate = 0;
                            }
                        }
                        else if (b < min_diff)
                        {
                            check_duplicate = (*current_iterator).CASE;
                            min_diff = b;
                            result = (*current_iterator).LP;
                        }
                    }
                }
            }

            if (result == "")
                return "-1";
            else
                return result;

            break;
        }
        }
    }

    return "-1";
}

int main()
{
    BusSystem *bs = new BusSystem();
    console(bs);
    delete bs;
    return 0;
}


//int main()
//{
//    BusSystem *bs = new BusSystem();
//
//    bs->query("SQ 12");
//    bs->query("INS A 0-A 001 100");
//    bs->query("INS A 1-A 101 200");
//    bs->query("INS A 5-A 51 400");
//    bs->query("INS A 8-A 1 651 750");
//
//    bs->print_the_Bus_Map_ver_2();
//    return 0;
//}

