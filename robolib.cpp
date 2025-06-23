#include <iostream> 
#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include <curses.h>

using namespace std;

class Robot {
protected:
    string name;
    int id;
    float weight;

public:
    Robot(string n, int i, float w) : name(n), id(i), weight(w) {}
    virtual string getType() const = 0;
    virtual void displayInfo() const {
        printw("Name: %s\nID: %d\nWeight: %.1f kg\n", name.c_str(), id, weight);
    }
    string getName() const { return name; }
    int getId() const { return id; }
    float getWeight() const { return weight; }

    virtual void saveToFile() const {
        ofstream file(name + "_robot.txt");
        file << "Name: " << name << "\nID: " << id << "\nWeight: " << weight << "\nType: " << getType() << "\n";
    }

    virtual void modifyParameters() = 0;
};

class LineFollower : public Robot {
private:
    float speed;
    float pid[3];

public:
    LineFollower(string n, int i, float w) : Robot(n, i, w), speed(0), pid{0, 0, 0} {}

    string getType() const override { return "Line Follower"; }

    void modifyParameters() override {
        clear();
        printw("Modify Line Follower Parameters:\n");
        
        echo(); // Enable echoing for user input display
        printw("Enter new speed: ");
        scanw("%f", &speed);

        printw("Enter PID values (P, I, D): ");
        scanw("%f %f %f", &pid[0], &pid[1], &pid[2]);
        noecho(); // Disable echoing after input
        
        saveToFile();
        printw("Parameters updated successfully!\n");
        printw("\nPress any key to return to the menu...");
        getch();
    }

    void saveToFile() const override {
        ofstream file(name + "_robot.txt");
        file << "Name: " << name << "\nID: " << id << "\nWeight: " << weight
             << "\nType: Line Follower\nSpeed: " << speed
             << "\nPID: " << pid[0] << ", " << pid[1] << ", " << pid[2] << "\n";
    }
};

class MazeSolver : public Robot {
private:
    float speed;
    float pid[3];

public:
    MazeSolver(string n, int i, float w) : Robot(n, i, w), speed(0), pid{0, 0, 0} {}

    string getType() const override { return "Maze Solver"; }

    void modifyParameters() override {
        clear();
        printw("Modify Maze Solver Parameters:\n");

        echo(); // Enable echoing for user input display
        printw("Enter new speed: ");
        scanw("%f", &speed);

        printw("Enter PID values (P, I, D): ");
        scanw("%f %f %f", &pid[0], &pid[1], &pid[2]);
        noecho(); // Disable echoing after input

        saveToFile();
        printw("Parameters updated successfully!\n");
        printw("\nPress any key to return to the menu...");
        getch();
    }

    void saveToFile() const override {
        ofstream file(name + "_robot.txt");
        file << "Name: " << name << "\nID: " << id << "\nWeight: " << weight
             << "\nType: Maze Solver\nSpeed: " << speed
             << "\nPID: " << pid[0] << ", " << pid[1] << ", " << pid[2] << "\n";
    }
};

class Drone : public Robot {
private:
    float speed;
    float location[2];

public:
    Drone(string n, int i, float w) : Robot(n, i, w), speed(0), location{0, 0} {}

    string getType() const override { return "Drone"; }

    void modifyParameters() override {
        clear();
        printw("Modify Drone Parameters:\n");

        echo(); // Enable echoing for user input display
        printw("Enter new speed: ");
        scanw("%f", &speed);

        printw("Enter new location (x, y): ");
        scanw("%f %f", &location[0], &location[1]);
        noecho(); // Disable echoing after input

        saveToFile();
        printw("Parameters updated successfully!\n");
        printw("\nPress any key to return to the menu...");
        getch();
    }

    void saveToFile() const override {
        ofstream file(name + "_robot.txt");
        file << "Name: " << name << "\nID: " << id << "\nWeight: " << weight
             << "\nType: Drone\nSpeed: " << speed
             << "\nLocation: (" << location[0] << ", " << location[1] << ")\n";
    }
};

class RobotManager {
private:
    vector<unique_ptr<Robot>> robots;

public:
    void addRobot(unique_ptr<Robot> robot) {
        robots.push_back(move(robot));
        robots.back()->saveToFile();
    }

    void displayAllRobots() const {
        clear();
        printw("All Robots:\n\n");
        for (const auto& robot : robots) {
            robot->displayInfo();
            printw("-------------------------\n");
        }
        printw("\nPress any key to return to the menu...");
        getch();
    }

    void modifyRobotParameters() {
        clear();
        printw("Enter Robot ID to modify parameters: ");
        int id;
        echo(); // Enable echo for ID input
        scanw("%d", &id);
        noecho(); // Disable echo after ID input

        for (auto& robot : robots) {
            if (robot->getId() == id) {
                robot->modifyParameters();
                return;
            }
        }
        printw("Robot ID not found.\n");
        printw("\nPress any key to return to the menu...");
        getch();
    }
};

void drawTitle() {
    mvprintw(1, (COLS - 20) / 2, "Robot Management System");
}

void drawMenu(int highlight) {
    const vector<string> menuItems = {"Add Robot", "Display All Robots", "Modify Robot Parameters", "Exit"};
    clear();
    drawTitle();

    // Draw a box around the menu
    int startX = 5, startY = 2, width = 30, height = menuItems.size() + 4;
    box(stdscr, 0, 0);
    mvaddch(startY - 1, startX - 1, ACS_ULCORNER); // Upper left corner
    mvaddch(startY - 1, startX + width, ACS_URCORNER); // Upper right corner
    mvaddch(startY + height, startX - 1, ACS_LLCORNER); // Lower left corner
    mvaddch(startY + height, startX + width, ACS_LRCORNER); // Lower right corner

    for (size_t i = 0; i < menuItems.size(); ++i) {
        if (highlight == i) attron(A_REVERSE);
        mvprintw(startY + i, startX, menuItems[i].c_str());
        attroff(A_REVERSE);
    }
    refresh();
}

void addRobot(RobotManager& manager) {
    char name[50];
    int id;
    float weight;

    clear();
    printw("Add New Robot\n\n");
    printw("Enter Robot Name: ");
    echo();
    getstr(name);

    printw("Enter Robot ID: ");
    scanw("%d", &id);

    printw("Enter Robot Weight: ");
    scanw("%f", &weight);
    noecho();

    printw("Select Robot Type:\n1. Line Follower\n2. Maze Solver\n3. Drone\n");
    int type;
    scanw("%d", &type);

    unique_ptr<Robot> robot;

    if (type == 1) {
        robot = make_unique<LineFollower>(name, id, weight);
    } else if (type == 2) {
        robot = make_unique<MazeSolver>(name, id, weight);
    } else if (type == 3) {
        robot = make_unique<Drone>(name, id, weight);
    } else {
        printw("Invalid type selected. Returning to menu.\n");
        getch();
        return;
    }

    manager.addRobot(move(robot));
    printw("Robot added successfully!\n");
    printw("Press any key to return to the menu...");
    getch();
}

void mainMenu(RobotManager& manager) {
    initscr();
    noecho();
    cbreak();
    curs_set(0); // Hide the cursor
    keypad(stdscr, TRUE);

    int highlight = 0;
    int choice;

    while (true) {
        drawMenu(highlight);

        choice = getch();
        switch (choice) {
            case KEY_UP:
                highlight = (highlight == 0) ? 3 : highlight - 1;
                break;
            case KEY_DOWN:
                highlight = (highlight == 3) ? 0 : highlight + 1;
                break;
            case 10: // Enter key
                if (highlight == 0) addRobot(manager);
                else if (highlight == 1) manager.displayAllRobots();
                else if (highlight == 2) manager.modifyRobotParameters();
                else if (highlight == 3) {
                    endwin();
                    return; // Exit the program
                }
                break;
        }
    }

    endwin();
}

int main() {
    RobotManager manager;
    mainMenu(manager);
    return 0;
}
