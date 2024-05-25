#include <iostream>
#include <vector>
#include <ctime>
#include <string>

using namespace std;

struct Date {
    uint32_t year;
    uint32_t month;
    uint32_t day;
    uint32_t hour;
    uint32_t minute;
    uint32_t second;
};

class Track {
public:
    string title;
    Date created_date;
    uint32_t duration;

    Track(string title, Date created_date, uint32_t duration) {
        this->title = title;
        this->created_date = created_date;
        this->duration = duration;
    }
};

class Player {
private:
    vector<Track> tracks;
    size_t current_track = 0;
    bool is_playing = false;

public:
    void addTrack(const Track *track) {
        this->tracks.push_back(*track);
    }

    void play() {
        if (!this->is_playing && this->current_track < this->tracks.size()) {
            Track current = this->tracks[current_track];
            cout << "Playing: " << current.title << endl;
            cout << "Date Created: " << current.created_date.year << "-"
                << current.created_date.month << "-"
                << current.created_date.day << endl;
            cout << "Duration: " << current.duration << " seconds" << endl;
            is_playing = true;
        }
    }

    void pause() {
        if (this->is_playing) {
            cout << "Paused" << endl;
            this->is_playing = false;
        } else {
            cout << "Already paused or not playing" << endl;
        }
    }

    void next() {
        if (this->current_track + 1 < this->tracks.size()) {
            this->stop();
            this->current_track++;
            this->play();
        } else {
            this->stop();
            this->current_track = 0;
            this->play();
        }
    }

    void stop() {
        if (this->is_playing) {
            cout << "Stopped" << endl;
            this->is_playing = false;
        } else {
            cout << "Nothing to stop" << endl;
        }
    }

    void exit() {
        cout << "Exiting..." << endl;
    }
};

int main() {
    Player player;
    string command;
    Track *track1;
    Track *track2;
    Track *track3;

    track1 = new Track("Track 1", {2023, 4, 15, 12, 0, 0}, 60);
    track2 = new Track("Track 2", {2023, 4, 15, 12, 0, 0}, 90);
    track3 = new Track("Track 3", {2023, 4, 15, 12, 0, 0}, 120);

    player.addTrack(track1);
    player.addTrack(track2);
    player.addTrack(track3);

    while (true) {
        cout << "Enter command: ";
          getline (cin, command);

        if (command == "play") {
            player.play();
        }
        else if (command == "pause") {
            player.pause();
        }
        else if (command == "next") {
            player.next();
        }
        else if (command == "stop") {
            player.stop();
        }
        else if (command == "exit") {
            player.exit();
            break;
        } else {
            cout << "Invalid command" << endl;
        }
    }

    delete track1;
    delete track2;
    delete track3;

    return 0;
}