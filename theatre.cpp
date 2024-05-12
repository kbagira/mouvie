#include <bits/stdc++.h>
using namespace std;

struct movie {
    string name;
    string genre;
    int duration;
    int hall;
    vector<string> time;
};

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

bool checkTimeConflict(const string& newStartTime, int newDuration) {
    for (int i = 0; i < schedule.size(); ++i) {
        const auto& scheduledMovie = schedule[i];
        for (int j = 0; j < scheduledMovie.time.size(); ++j) {
            const string& startTime = scheduledMovie.time[j];
            int pos = -1;
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


void addMovie(movie m) {
    ofstream fout("schedule.txt");
    if (!fout) {
        cerr << "Error opening output file!" << endl;
        return;
    }
    fout << "Name: " << m.name << endl;
    fout << "Genre: " << m.genre << endl;
    fout << "Duration: " << m.duration << " minutes" << endl;
    fout << "Hall: " << m.duration << endl;
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

void updateMovie() {
    string movieName;
    cout << "Enter the name of the movie you want to update: ";
    cin >> movieName;
    bool found = false;
    for (int i = 0; i < schedule.size(); ++i) {
        if (schedule[i].name == movieName) {
            found = true;
            cout << "Enter new genre for the movie: ";
            cin >> schedule[i].genre;
            char changeTime;
            cout << "Do you want to change the time for the movie? (y/n): ";
            cin >> changeTime;
            if (tolower(changeTime) == 'y') {
                schedule[i].time.clear(); // î÷èùàåì ñòàðûå âðåìåíà
                int numTimes;
                cout << "Enter the number of showtimes: ";
                cin >> numTimes;
                cout << "Enter new times for the movie: ";
                for (int j = 0; j < numTimes; ++j) {
                    string newTime;
                    cin >> newTime;
                    schedule[i].time.push_back(newTime);
                }
            }
            char changeHall;
            cout << "Do you want to change the hall for the movie? (y/n): ";
            cin >> changeHall;
            if (tolower(changeHall) == 'y') {
                cout << "Enter new hall for the movie: ";
                cin >> schedule[i].hall;
            }
            cout << "Movie details updated successfully!" << endl;
            break;
        }
    }
    if (!found) {
        cout << "Movie not found in the schedule." << endl;
    }
}

void removeMovie() {
    string movieName;
    cout << "Enter the name of the movie you want to remove: ";
    cin >> movieName;
    bool found = false;
    for (auto it = schedule.begin(); it != schedule.end(); ++it) {
        if (it->name == movieName) {
            found = true;
            it = schedule.erase(it); // remove the movie from the schedule
            cout << "Movie removed successfully!" << endl;
            break;
        }
    }
    if (!found) {
        cout << "Movie not found in the schedule." << endl;
    }
}

int main() {
    movie m;
    string outputFile = "schedule.txt";
    addMovie(m);
    updateMovie();
    // âûçîâ ôóíêöèè removeMovie() äîëæåí áûòü çäåñü, åñëè íåîáõîäèìî
    return 0;
}




// Function to write movie details to a file
void addMovie() {
	    ofstream fout("schedule.txt");
	    if (!fout) {
        cerr << "Error opening output file!" << endl;
        return 1;
        }
        outfile << "Name: " << m.name << endl;
        outfile << "Genre: " << m.genre << endl;
        outfile << "Duration: " << m.duration << " minutes" << endl;
        outfile << "Hall: " << m.duration << endl;
        outfile << "Showtimes: ";
        for (int i = 0; i < m.time.size(); i++) {
            outfile << m.time[i];
            if (i != m.time.size() - 1) {
                outfile << ", ";
            }
        }
        outfile << endl << endl;
        outfile.close();
        cout << "Movie added successfully!" << endl;
    } 
}

void updateMovie() {
    // Prompt user for movie identifier (name, ID, etc.)
    string movieName;
    cout << "Enter the name of the movie you want to update: ";
    cin >> movieName;

    // Search for the movie in the schedule
    bool found = false;
    for (int i = 0; i < schedule.size(); ++i) {
        if (schedule[i].name == movieName) {
        
            found = true;

            cout << "Enter new genre for the movie: ";
            cin >> schedule[i].genre;

            char changeTime;
            cout << "Do you want to change the time for the movie? (y/n): ";
            cin >> changeTime;

            if (tolower(changeTime) == 'y') {
                cout << "Enter new time for the movie: ";
                cin >> schedule[i].time; 
            }
            char changeHall;
            cout << "Do you want to change the hall for the movie? (y/n): ";
            cin >> changeHall;

            if (tolower(changeHall) == 'y') {
                cout << "Enter new hall for the movie: ";
                cin >> schedule[i].hall;
            }

            cout << "Movie details updated successfully!" << endl;
            break;
        }
    }

    if (!found) {
        cout << "Movie not found in the schedule." << endl;
    }
}


void removeMovie() {
    string movieName;
    cout << "Enter the name of the movie you want to remove: ";
    cin >> movieName;
    bool found = false;
    for (auto it = schedule.begin(); it != schedule.end(); ++it) {
        if (it->name == movieName) {
            found = true;
            it = schedule.erase(it); 
            cout << "Movie removed successfully!" << endl;
            break;
        }
    }

    if (!found) {
        cout << "Movie not found in the schedule." << endl;
    }
}


int main() {
    string outputFile = "schedule.txt";
    addMovie();
    updateMouvie();
    removeMovie();
    

   
    

    return 0;
}


