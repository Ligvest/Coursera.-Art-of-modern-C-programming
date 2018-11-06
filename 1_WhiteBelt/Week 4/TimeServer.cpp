
class TimeServer {
public:
	string GetCurrentTime() {
		try {
			LastFetchedTime = AskTimeServer();
			return LastFetchedTime;
		}
		catch (std::system_error& ex) {
			return LastFetchedTime;
		}		
	}

private:
	string LastFetchedTime = "00:00:00";
};