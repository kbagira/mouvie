#include <bits/stdc++.h>
using namespace std;

struct movie {
    string name;
    string genre;
    int duration;
    string theatre;
    vector<string> time;
};

// Function to write movie details to a file
void addMovie() {
        outfile << "Name: " << m.name << endl;
        outfile << "Genre: " << m.genre << endl;
        outfile << "Duration: " << m.duration << " minutes" << endl;
        outfile << "Theatre: " << m.theatre << endl;
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

void updateMovie(){
	
}

removeMovie(){
	
}

int main() {
    string outputFile = "schedule.txt";

    // Create some movie structs
    movie m1 = {"Titanic", "Drama", 194, "Cosmopark", {"12:00"}};
    movie m2 = {"Avatar", "Science Fiction", 162, "Bishkekpark", {"15:00"}};
    movie m3 = {"Schindler's List", "Biography", 195, "Cosmopark", {"17:30"}};
    movie m4 = {"The Lion King", "Animation", 118, "Dordoiplaza", {"12:00"}};
    movie m5 = {"The Matrix", "Science Fiction", 136, "Bishkekpark", {"19:00"}};

    // Add movies to the schedule file
    addMovie(outputFile, m1);
    addMovie(outputFile, m2);
    addMovie(outputFile, m3);
    addMovie(outputFile, m4);
    addMovie(outputFile, m5);

    return 0;
}

