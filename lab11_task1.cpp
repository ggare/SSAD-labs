#include <iostream>
#include <string>
#include <memory>

using namespace std;

// Implementation (Codec)
class AudioCodec {
public:
    virtual void decode(const string& fileName) = 0;
    virtual ~AudioCodec() {}
};

class MP3Codec : public AudioCodec {
public:
    void decode(const string& fileName) override {
        cout << "Playing " << fileName << " using MP3 codec." << endl;
    }
};

class WAVCodec : public AudioCodec {
public:
    void decode(const string& fileName) override {
        cout << "Playing " << fileName << " using WAV codec." << endl;
    }
};

class FLACCodec : public AudioCodec {
public:
    void decode(const string& fileName) override {
        cout << "Playing " << fileName << " using FLAC codec." << endl;
    }
};

// Abstraction
class MusicPlayer {
protected:
    shared_ptr<AudioCodec> codec;
public:
    MusicPlayer(shared_ptr<AudioCodec> codec) : codec(codec) {}
    virtual void play(const string& fileName) = 0;
    virtual ~MusicPlayer() {}
};

// Refined Abstractions
class PopPlayer : public MusicPlayer {
public:
    PopPlayer(shared_ptr<AudioCodec> codec) : MusicPlayer(codec) {}
    void play(const string& fileName) override {
        cout << "Started Pop Player..." << endl;
        codec->decode(fileName);
    }
};

class JazzPlayer : public MusicPlayer {
public:
    JazzPlayer(shared_ptr<AudioCodec> codec) : MusicPlayer(codec) {}
    void play(const string& fileName) override {
        cout << "Started Jazz Player..." << endl;
        codec->decode(fileName);
    }
};

class RockPlayer : public MusicPlayer {
public:
    RockPlayer(shared_ptr<AudioCodec> codec) : MusicPlayer(codec) {}
    void play(const string& fileName) override {
        cout << "Started Rock Player..." << endl;
        codec->decode(fileName);
    }
};

int main() {
    shared_ptr<AudioCodec> mp3 = make_shared<MP3Codec>();
    shared_ptr<AudioCodec> wav = make_shared<WAVCodec>();
    shared_ptr<AudioCodec> flac = make_shared<FLACCodec>();

    unique_ptr<MusicPlayer> popPlayer = make_unique<PopPlayer>(mp3);
    unique_ptr<MusicPlayer> jazzPlayer = make_unique<JazzPlayer>(wav);
    unique_ptr<MusicPlayer> rockPlayer = make_unique<RockPlayer>(flac);

    popPlayer->play("pop_song.mp3");
    jazzPlayer->play("jazz_song.wav");
    rockPlayer->play("rock_song.flac");

    return 0;
}
