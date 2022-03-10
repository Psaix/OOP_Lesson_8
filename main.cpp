#include <iostream>
#include <string>
#define SIZE 10

//____________________________________________________________________________________________________________
//____________________________________________TASK1___________________________________________________________
//____________________________________________________________________________________________________________


//  Creating exception class DividedByZero

class DividedByZero{
private:
    std::string m_error;

public:
    DividedByZero(std::string error) : m_error(error) {}

    const char* what() {
        return m_error.c_str();
    }
};


// Creating template function for dividing variables.
// Throwing exception DividedByZero if the second variable is zero.

template<class T>
T div(T dividend, T divider)
{
    if (divider == 0)
    {
        throw DividedByZero("Can't be divided by zero!");
    }
    return dividend / divider;
}


//____________________________________________________________________________________________________________
//____________________________________________TASK2___________________________________________________________
//____________________________________________________________________________________________________________


// Creating exception class Ex

class Ex {
public:
    double x;
    Ex(const double &x) : x(x) {}
};

// Creating class Bar

class Bar {
private:
    double y;
public:
    Bar(double y = 0.00) : y(y) {}
    void set(const double &a)
    {
        if (a + y > 100)
            throw Ex(a * y);
        else
            y = a;
    }
};


//____________________________________________________________________________________________________________
//____________________________________________TASK3___________________________________________________________
//____________________________________________________________________________________________________________


inline void clrscr()
{
    system("CLS");
}


// Creating exception class OffTheField

class OffTheField {
private:
    std::string m_error;

public:
    OffTheField(std::string error) : m_error(error) {}

    const char* what() {
        return m_error.c_str();
    }
};


// Creating exception class IllegalCommand

class IllegalCommand {
private:
    std::string m_error;

public:
    IllegalCommand(std::string error) : m_error(error) {}

    const char* what() {
        return m_error.c_str();
    }

};


// Creating class RobCoord to manipulate with Robot class coordinates

class RobCoord {
public:
    int x;
    int y;
};


// Creating Robot class

class Robot {
private:
    int m_x = 4;
    int m_y = 4;

public:

    RobCoord move() {
        RobCoord r;
        r.x = m_x;
        r.y = m_y;
        std::string move;
        std::cout << "Input direction then press ENTER: ";
        std::cin >> move;
        if (size(move) < 2)
        {
            char* mv = (char*)move.c_str();
            switch (*mv) {
            case 'W':case 'w':
                r.x--;
                if (r.x < 0)
                {
                    throw OffTheField("Can't move UP - off the field! Wrong direction.");
                }
                break;
            case 'S':case 's':
                r.x++;
                if (r.x > 9)
                {
                    throw OffTheField("Can't move DOWN - off the field! Wrong direction.");
                }
                break;
            case 'A':case 'a':
                r.y--;
                if (r.y < 0)
                {
                    throw OffTheField("Can't move LEFT - off the field! Wrong direction.");
                }
                break;
            case 'D':case 'd':
                r.y++;
                if (r.y > 9)
                {
                    throw OffTheField("Can't move RIGHT - off the field! Wrong direction.");
                }
                break;
            default:
                throw IllegalCommand("Illegal command! Incorrect direction! Try again.");
                break;
            }
            m_y = r.y;
            m_x = r.x;
            return r;
        }
        else
        {
            throw IllegalCommand("Illegal command! Incorrect direction! Try again.");
        }

    }

    friend std::ostream& operator<<(std::ostream& os, Robot& rb) {
        os << "Position at x:" << rb.m_x << " y:" << rb.m_y;
        return os;
    }

};


// Creating bool function to break do-while cycle in the main function

bool repeat() {
    char answer;
    do {
        std::cout << "Want to continue? Input 'y' or 'n' then press ENTER: " << "\n";
        std::cin >> answer;
        if (answer == 'y')
        {
            return true;
            break;
        }
        else if (answer == 'n')
        {
            std::cout << "Thank you for trying out my programm))...Psaix..." << "\n";
            return false;
            break;
        }
        else
        {
            std::cout << "Wrong answer." << "\n";
        }
    } while (true);
}

// Creating Field class

class Field {
private:
    enum field : char { EMPTY = '_', ROBOT = 2 };

    field roboField[SIZE][SIZE];

public:
    void buildField() {
        for (size_t x = 0; x < SIZE; x++)
        {
            for (size_t y = 0; y < SIZE; y++)
            {
                roboField[x][y] = EMPTY;
            }
        }
        roboField[4][4] = ROBOT;
    }

    RobCoord getCoord(RobCoord g) {
        RobCoord c = g;
        roboField[c.x][c.y] = ROBOT;
        return c;
    }

    void drawField() {

        for (size_t x = 0; x < SIZE; x++)
        {
            std::cout << "  " << "|";
            for (size_t y = 0; y < SIZE; y++)
            {
                std::cout << " " << roboField[x][y] << " " << "|";
            }
            std::cout << " " << std::endl;
        }
        std::cout << "   _______________________________________" << "\n";
    }

    void clear() {
        for (size_t x = 0; x < SIZE; x++)
        {
            for (size_t y = 0; y < SIZE; y++)
            {
                roboField[x][y] = EMPTY;
            }
        }
    }


};

// Instructions function

void instructions() {
    std::cout << "Type 'W' or 'w' - to move up, 'S' or 's' - to move down, " << "\n"
        << "'A' or 'a' - to move left, and 'D' or 'd' - to move right:" << "\n\n";
    std::cout << "   _______________________________________" << "\n";
}


int main()
{

//____________________________________________TASK1___________________________________________________________


// TASK 1 Try - Catch

    try
    {
        std::cout << div<int>(6, 2) << std::endl;
        std::cout << div<double>(2.5, 0.0) << std::endl;
    }
    catch (DividedByZero& ex)
    {
        std::cerr << "Error!" << ex.what() << std::endl;
    }

//____________________________________________TASK2___________________________________________________________


// TASK 2 Try - Catch

    Bar bar;
    try
    {
        int n;
        std::cin >> n;
        while (n != 0)
        {
            bar.set(n);
            std::cin >> n;
        }
    }
    catch (Ex& ex)
    {
        std::cerr << "Error!" << ex.x << std::endl;
    }


//____________________________________________TASK3___________________________________________________________

    Robot rb;
    Field field;
    field.buildField();
    instructions();
    field.drawField();
    bool check = true;
    do {
        try
        {
            field.clear();
            field.getCoord(rb.move());
            clrscr();
            instructions();
            field.drawField();

        }
        catch (OffTheField& ex)
        {
            std::cerr << ex.what() << " " << rb << std::endl;
            check = repeat();
        }
        catch (IllegalCommand& ex)
        {
            std::cerr << ex.what() << " " << rb << std::endl;
            check = repeat();
        }
    } while (check);



    return 0;
}

