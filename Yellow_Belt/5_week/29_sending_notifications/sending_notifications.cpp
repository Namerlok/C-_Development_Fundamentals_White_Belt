//============================================================================
// Name        : sending_notifications
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>

using namespace std;

void SendSms(const string& number, const string& message) {
  cout << "Send '" << message << "' to number " << number << endl;
}

void SendEmail(const string& email, const string& message) {
  cout << "Send '" << message << "' to e-mail "  << email << endl;
}

class INotifier {
public:
	virtual void Notify(const string& message) = 0;
};

class SmsNotifier : public INotifier {
public:
	SmsNotifier(string phone_) : phone(phone_) {}

	void Notify(const string& message) override {
		SendSms(phone, message);
	}

private:
	const string phone;
};

class EmailNotifier : public INotifier {
public:
	EmailNotifier(string email_) : email(email_) {}

	void Notify(const string& message) override {
		SendEmail(email, message);
	}
private:
	const string email;
};

void Notify(INotifier& notifier, const string& message) {
	notifier.Notify(message);
}


int main() {
  SmsNotifier sms{"+7-495-777-77-77"};
  EmailNotifier email{"na-derevnyu@dedushke.ru"};

  Notify(sms, "I have White belt in C++");
  Notify(email, "And want a Yellow one");
  return 0;
}

/* авторское решение
#include <iostream>
#include <string>

using namespace std;

void SendSms(const string& number, const string& message) {
  cout << "Send '" << message << "' to number " << number << endl;
}

void SendEmail(const string& email, const string& message) {
  cout << "Send '" << message << "' to e-mail " << email << endl;
}

class INotifier {
public:
  virtual void Notify(const string& message) const = 0;
};

class SmsNotifier : public INotifier {
public:
  SmsNotifier(const string& number)
    : Number(number)
  {
  }
  virtual void Notify(const string& message) const override {
    SendSms(Number, message);
  }

private:
  const string Number;
};

class EmailNotifier : public INotifier {
public:
  EmailNotifier(const string& email)
    : Email(email)
  {
  }
  virtual void Notify(const string& message) const override {
    SendEmail(Email, message);
  }

private:
  const string Email;
};

void Notify(const INotifier& notifier, const string& message) {
  notifier.Notify(message);
}

int main() {
  SmsNotifier sms{"+7-495-777-77-77"};
  EmailNotifier email{"na-derevnyu@dedushke.ru"};

  Notify(sms, "I have White belt in C++");
  Notify(email, "And want a Yellow one");
  return 0;
}
 */

