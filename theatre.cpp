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

// Function to check for time conflict
bool checkTimeConflict(const string& newStartTime, int newDuration) {
    for (int i = 0; i < schedule.size(); ++i) {
        const movie& scheduledMovie = schedule[i];
        for (int j = 0; j < scheduledMovie.time.size(); ++j) {
            const string& startTime = scheduledMovie.time[j];
            int pos = -1;
            // Find the position of ':' in the start time string
            for (int k = 0; k < startTime.size(); ++k) {
                if (startTime[k] == ':') {
                    pos = k;
                    break;
                }
            }
            if (pos != -1) {
                int existingHour = 0;
                int existingMinute = 0;
                for (int k = 0; k < pos; ++k) {
                    existingHour = existingHour * 10 + (startTime[k] - '0');
                }
                for (int k = pos + 1; k < startTime.size(); ++k) {
                    existingMinute = existingMinute * 10 + (startTime[k] - '0');
                }
                int newHour = 0;
                int newMinute = 0;
                pos = -1;
                // Find the position of ':' in the new start time string
                for (int k = 0; k < newStartTime.size(); ++k) {
                    if (newStartTime[k] == ':') {
                        pos = k;
                        break;
                    }
                }
                if (pos != -1) {
                    for (int k = 0; k < pos; ++k) {
                        newHour = newHour * 10 + (newStartTime[k] - '0');
                    }
                    for (int k = pos + 1; k < newStartTime.size(); ++k) {
                        newMinute = newMinute * 10 + (newStartTime[k] - '0');
                    }
                    // Convert time to minutes for comparison
                    int existingTime = existingHour * 60 + existingMinute;
                    int newTime = newHour * 60 + newMinute;
                    // Check for time conflict
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
bool validateHallNumber(int hall) {
    return (hall > 0);
}
bool validateDuration(int duration) {
    return (duration > 0 && duration <= 500);
}

// Function to add a movie to the schedule
void addMovie(movie m) {
    // Check for time conflict before adding
    if (checkTimeConflict(m.time[0], m.duration)) {
        cout << "Time conflict detected. The movie cannot be added." << endl;
        return;
    }

    schedule.push_back(m); // Add a movie to the schedule
    ofstream fout("schedule.txt", ios::app); // Open the file to append
    if (!fout) {
        cerr << "Error opening output file!" << endl;
        return;
    }
    fout << "Name: " << m.name << endl;
    fout << "Genre: " << m.genre << endl;
    fout << "Duration: " << m.duration << " minutes" << endl;
    fout << "Hall: " << m.hall << endl;
    fout << "Showtimes: ";
    for (int i = 0; i < m.time.size(); i++) {
        fout << m.time[i];
        if (i != m.time.size() - 1) {
            fout << ", ";
        }
    }
    fout << endl << endl;
    fout.close();
    cout << "Movie added successfully!" << endl;
}

// Function to update movie details
void updateMovie() {
    string movieName;
    cout << "Enter the name of the movie you want to update: ";
    cin.ignore(); // Ignore the newline character in the input buffer
    getline(cin, movieName); // Allowing input with spaces
    bool found = false;

    ifstream fin("schedule.txt");
    if (!fin) {
        cerr << "Error opening input file!" << endl;
        return;
    }

    string line;
    vector<movie> tempSchedule;
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
            // Parse and store showtimes
            stringstream ss(line.substr(11)); // Create a stringstream from the showtimes string
            string time;
            while (getline(ss, time, ',')) {
                m.time.push_back(time);
            }
            tempSchedule.push_back(m); // Add the movie to temporary schedule
        }
    }
    fin.close();

    // Iterate over the temporary schedule to find the movie
    for (int i = 0; i < tempSchedule.size(); ++i) {
        if (tempSchedule[i].name == movieName) {
            found = true;
            char changeTime;
            cout << "Do you want to change the time for the movie? (y/n): ";
            cin >> changeTime;
            if (tolower(changeTime) == 'y') {
                tempSchedule[i].time.clear();
                int numTimes;
                cout << "Enter the number of showtimes: ";
                cin >> numTimes;
                cout << "Enter new times for the movie: ";
                for (int j = 0; j < numTimes; ++j) {
                    string newTime;
                    cin >> newTime;
                    // Check for time conflict before adding
                    if (!checkTimeConflict(newTime, tempSchedule[i].duration)) {
                        tempSchedule[i].time.push_back(newTime);
                    } else {
                        cout << "Time conflict detected. Please choose a different time." << endl;
                    }
                }
            }
            char changeHall;
            cout << "Do you want to change the hall for the movie? (y/n): ";
            cin >> changeHall;
            if (tolower(changeHall) == 'y') {
                cout << "Enter new hall for the movie: ";
                cin >> tempSchedule[i].hall;
            }
            cout << "Movie details updated successfully!" << endl;
            break;
        }
    }

    // Write the updated schedule back to the file
    ofstream fout("schedule.txt");
    if (!fout) {
        cerr << "Error opening output file!" << endl;
        return;
    }
    for (int i = 0; i < tempSchedule.size(); ++i) {
        fout << "Name: " << tempSchedule[i].name << endl;
        fout  << tempSchedule[i].genre << endl; // Write genre to file
        fout << "Duration: " << tempSchedule[i].duration << " minutes" << endl;
        fout << "Hall: " << tempSchedule[i].hall << endl;
        fout << "Showtimes: ";
        for (int j = 0; j < tempSchedule[i].time.size(); j++) {
            fout << tempSchedule[i].time[j];
            if (j != tempSchedule[i].time.size() - 1) {
                fout << ", ";
            }
        }
        fout << endl << endl;
    }
    fout.close();

    if (!found) {
        cout << "Movie not found in the schedule." << endl;
    }
}

void removeMovie() {
    string movieName;
    cout << "Enter the name of the movie you want to remove: ";
    cin.ignore(); // Ignore the newline character in the input buffer
    getline(cin, movieName); // Allowing input with spaces
    bool found = false;

    ifstream fin("schedule.txt");
    if (!fin) {
        cerr << "Error opening input file!" << endl;
        return;
    }

    string line;
    vector<movie> tempSchedule;
    while (getline(fin, line)) {
        if (line.find("Name: ") != string::npos) {
            movie m;
            m.name = line.substr(6);
            getline(fin, line); // Read the genre line
            getline(fin, line); // Read the duration line
            getline(fin, line); // Read the hall line
            getline(fin, line); // Read the showtimes line
            tempSchedule.push_back(m); // Add the movie to temporary schedule
        }
    }
    fin.close();

    // Iterate over the temporary schedule to find and remove the movie
    for (vector<movie>::iterator it = tempSchedule.begin(); it != tempSchedule.end(); ++it) {
        if (it->name == movieName) {
            found = true;
            it = tempSchedule.erase(it);
            cout << "Movie removed successfully!" << endl;
            break;
        }
    }

    // Write the updated schedule back to the file
    ofstream fout("schedule.txt");
    if (!fout) {
        cerr << "Error opening output file!" << endl;
        return;
    }
    for (int i = 0; i < tempSchedule.size(); ++i) {
        fout << "Name: " << tempSchedule[i].name << endl;
        fout << "Genre: " << tempSchedule[i].genre << endl;
        fout << "Duration: " << tempSchedule[i].duration << " minutes" << endl;
        fout << "Hall: " << tempSchedule[i].hall << endl;
        fout << "Showtimes: ";
        for (int j = 0; j < tempSchedule[i].time.size(); j++) {
            fout << tempSchedule[i].time[j];
            if (j != tempSchedule[i].time.size() - 1) {
                fout << ", ";
            }
        }
        fout << endl << endl;
    }
    fout.close();

    if (!found) {
        cout << "Movie not found in the schedule." << endl;
    }
}
void movieReport(const string& movieName) {
    bool found = false;

    ifstream fin("schedule.txt");
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
            // Parse and store showtimes
            stringstream ss(line.substr(11)); // Create a stringstream from the showtimes string
            string time;
            while (getline(ss, time, ',')) {
                m.time.push_back(time);
            }
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
    }
    fin.close();

    if (!found) {
        cout << "Movie '" << movieName << "' not found in the schedule." << endl;
    }
}


// Main function
int main() {
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
            cin >> m.name;
            cout << "Enter the genre of the movie: ";
            cin >> m.genre;
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
            if (!validateShowtimes(m.time)) {
                cout << "Invalid showtimes. Please enter showtimes in HH:MM format." << endl;
                continue;
            }
            for (int i = 0; i < numTimes; ++i) {
                string newTime;
                cin >> newTime;
                m.time.push_back(newTime);
            }
            addMovie(m);
        } else if (choice == 2) {
            updateMovie();
        } else if (choice == 3) {
            removeMovie();
        } else if (choice == 4) {
            string movieName;
            cout << "Enter the name of the movie: ";
            cin >> movieName;
            movieReport(movieName);
        } else if (choice == 5) {
            cout << "Exiting program." << endl;
        } else {
            cout << "Invalid choice. Please enter a number between 1 and 5." << endl;
        }
    } while (choice != 5);

    return 0;
}




