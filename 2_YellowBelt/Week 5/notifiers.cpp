class INotifier {
public:
	virtual void Notify(const std::string& message) = 0;
};

class SmsNotifier : public INotifier {
public:
	SmsNotifier(std::string sPhoneNumber) : sPhoneNumber_(sPhoneNumber) {}
	void Notify(const std::string& sMessage) override {
		SendSms(sPhoneNumber_, sMessage);
	}

private:
	std::string sPhoneNumber_;
};

class EmailNotifier : public INotifier {
public:
	EmailNotifier(std::string sEmailAddress) : sEmailAddress_(sEmailAddress) {}
	void Notify(const std::string& sMessage) override {
		SendEmail(sEmailAddress_, sMessage);
	}

private:
	std::string sEmailAddress_;
};