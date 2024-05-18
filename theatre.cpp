#include <bits/stdc++.h>
using namespace std;

struct movie {
    string name;
    string genre;
    int duration;
    int hall;
    vector<string> time;
};

vector<movie> schedule;

// Function to read schedule from file
void readSchedule(const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "Error opening input file!" << endl;
        return;
    }

    string line;
    while (getline(fin, line)) {
        if (line.find("Name: ") != string::npos) {
            movie m;
            m.name = line.substr(6);
            getline(fin, m.genre); // Read the genre line
            getline(fin, line); // Read the duration line
            m.duration = stoi(line.substr(10)); // Convert duration to integer
            getline(fin, line); // Read the hall line
            m.hall = stoi(line.substr(6)); // Convert hall to integer
            getline(fin, line); // Read the showtimes line
            stringstream ss(line.substr(11)); // Create a stringstream from the showtimes string
            string time;
            while (getline(ss, time, ',')) {
                m.time.push_back(time);
            }
            schedule.push_back(m);
        }
    }
    fin.close();
}

// Function to write schedule to file
void writeSchedule(const string& filename) {
    ofstream fout(filename);
    if (!fout) {
        cerr << "Error opening output file!" << endl;
        return;
    }
    for (const movie& m : schedule) {
        fout << "Name: " << m.name << endl;
        fout << m.genre << endl; // Write genre to file
        fout << "Duration: " << m.duration << " minutes" << endl;
        fout << "Hall: " << m.hall << endl;
        fout << "Showtimes: ";
        for (size_t j = 0; j < m.time.size(); ++j) {
            fout << m.time[j];
            if (j != m.time.size() - 1) {
                fout << ", ";
            }
        }
        fout << endl << endl;
    }
    fout.close();
}

// Function to check for time conflict
bool checkTimeConflict(const string& newStartTime, int newDuration) {
    for (const movie& scheduledMovie : schedule) {
        for (const string& startTime : scheduledMovie.time) {
            int pos = startTime.find(':');
            if (pos != string::npos) {
                int existingHour = stoi(startTime.substr(0, pos));
                int existingMinute = stoi(startTime.substr(pos + 1));
                int newPos = newStartTime.find(':');
                if (newPos != string::npos) {
                    int newHour = stoi(newStartTime.substr(0, newPos));
                    int newMinute = stoi(newStartTime.substr(newPos + 1));
                    int existingTime = existingHour * 60 + existingMinute;
                    int newTime = newHour * 60 + newMinute;
                    if ((newTime >= existingTime && newTime < existingTime + newDuration) ||
                        (existingTime >= newTime && existingTime < newTime + newDuration)) {
                        cerr << "Time Conflict: Movie is already scheduled for this time." << endl;
                        return true;
                    }
                } else {
                    cerr << "Symbol ':' not found in string: " << newStartTime << endl;
                }
            } else {
                cerr << "Symbol ':' not found in string: " << startTime << endl;
            }
        }
    }
    return false;
}

// Function to validate showtimes
bool validateShowtimes(const vector<string>& times) {
    for (const auto& time : times) {
        if (time.size() != 5 || time[2] != ':' ||
            !isdigit(time[0]) || !isdigit(time[1]) ||
            !isdigit(time[3]) || !isdigit(time[4])) {
            return false;
        }
        int hour = stoi(time.substr(0, 2));
        int minute = stoi(time.substr(3, 2));
        if (hour < 0 || hour > 23 || minute < 0 || minute > 59) {
            return false;
        }
    }
    return true;
}

// Function to validate hall number
bool validateHallNumber(int hall) {
    return (hall > 0);
}

// Function to validate duration
bool validateDuration(int duration) {
    return (duration > 0 && duration <= 500);
}

// Function to add a movie to the schedule
void addMovie(const movie& m) {
    if (checkTimeConflict(m.time[0], m.duration)) {
        cout << "Time conflict detected. The movie cannot be added." << endl;
        return;
    }
    schedule.push_back(m);
    cout << "Movie added successfully!" << endl;
}

// Function to update movie details
void updateMovie() {
    string movieName;
    cout << "Enter the name of the movie you want to update: ";
    cin.ignore(); // Ignore the newline character in the input buffer
    getline(cin, movieName); // Allowing input with spaces
    bool found = false;

    for (movie& m : schedule) {
        if (m.name == movieName) {
            found = true;
            char changeTime;
            cout << "Do you want to change the time for the movie? (y/n): ";
            cin >> changeTime;
            if (tolower(changeTime) == 'y') {
                vector<string> newTimes;
                int numTimes;
                cout << "Enter the number of showtimes: ";
                cin >> numTimes;
                cout << "Enter new times for the movie: ";
                for (int j = 0; j < numTimes; ++j) {
                    string newTime;
                    cin >> newTime;
                    if (!checkTimeConflict(newTime, m.duration)) {
                        newTimes.push_back(newTime);
                    } else {
                        cout << "Time conflict detected. Please choose a different time." << endl;
                    }
                }
                m.time = newTimes;
            }
            char changeHall;
            cout << "Do you want to change the hall for the movie? (y/n): ";
            cin >> changeHall;
            if (tolower(changeHall) == 'y') {
                cout << "Enter new hall for the movie: ";
                cin >> m.hall;
            }
            cout << "Movie details updated successfully!" << endl;
            break;
        }
    }

    if (!found) {
        cout << "Movie not found in the schedule." << endl;
    }
}

// Function to remove a movie from the schedule
void removeMovie() {
    string movieName;
    cout << "Enter the name of the movie you want to remove: ";
    cin.ignore(); // Ignore the newline character in the input buffer
    getline(cin, movieName); // Allowing input with spaces
    bool found = false;

    for (auto it = schedule.begin(); it != schedule.end(); ++it) {
        if (it->name == movieName) {
            found = true;
            schedule.erase(it);
            cout << "Movie removed successfully!" << endl;
            break;
        }
    }

    if (!found) {
        cout << "Movie not found in the schedule." << endl;
    }
}

// Function to generate a movie report
void movieReport(const string& movieName) {
    bool found = false;

    for (const movie& m : schedule) {
        if (m.name == movieName) {
            found = true;
            cout << "Movie Information:" << endl;
            cout << "Name: " << m.name << endl;
            cout << "Genre: " << m.genre << endl;
            cout << "Duration: " << m.duration << " minutes" << endl;
            cout << "Hall: " << m.hall << endl;
            cout << "Showtimes: ";
            for (size_t i = 0; i < m.time.size(); ++i) {
                cout << m.time[i];
                if (i != m.time.size() - 1) {
                    cout << ", ";
                }
            }
            cout << endl;
            break;
        }
    }

    if (!found) {
        cout << "Movie '" << movieName << "' not found in the schedule." << endl;
    }
}

// Main function
int main() {
    readSchedule("schedule.txt");

    int choice;
    // Display the action menu
    do {
        cout << "Choose an action:" << endl;
        cout << "1. Add a movie" << endl;
        cout << "2. Update a movie" << endl;
        cout << "3. Remove a movie" << endl;
        cout << "4. Movie report" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            movie m;
            cout << "Enter the name of the movie: ";
            cin.ignore(); // Ignore the newline character in the input buffer
            getline(cin, m.name); // Allowing input with spaces
            cout << "Enter the genre of the movie: ";
            getline(cin, m.genre);
            cout << "Enter the duration of the movie (in minutes): ";
            cin >> m.duration;
            if (!validateDuration(m.duration)) {
                cout << "Invalid duration number. Please enter a positive duration number." << endl;
                continue;
            }
            cout << "Enter the hall number for the movie: ";
            cin >> m.hall;
            if (!validateHallNumber(m.hall)) {
                cout << "Invalid hall number. Please enter a positive hall number." << endl;
                continue;
            }
            int numTimes;
            cout << "Enter the number of showtimes: ";
            cin >> numTimes;
            cout << "Enter showtimes for the movie (format: HH:MM): ";
            vector<string> times;
            for (int i = 0; i < numTimes; ++i) {
                string newTime;
                cin >> newTime;
                times.push_back(newTime);
            }
            if (!validateShowtimes(times)) {
                cout << "Invalid showtimes. Please enter showtimes in HH:MM format." << endl;
                continue;
            }
            m.time = times;
            addMovie(m);
        } else if (choice == 2) {
            updateMovie();
        } else if (choice == 3) {
            removeMovie();
        } else if (choice == 4) {
            string movieName;
            cout << "Enter the name of the movie: ";
            cin.ignore(); // Ignore the newline character in the input buffer
            getline(cin, movieName); // Allowing input with spaces
            movieReport(movieName);
        } else if (choice == 5) {
            cout << "Exiting program." << endl;
        } else {
            cout << "Invalid choice. Please enter a number between 1 and 5." << endl;
        }
    } while (choice != 5);

    writeSchedule("schedule.txt");

    return 0;
}




