#include <print>
#include <string>
class Task {
public:
	struct CTime {
		int year;
		int month;
		int day;
		int hour;
		int minute;
		int second;

		// Constructor that matches the format: {year, month, day, hour, minute, second}
		CTime(int y, int m, int d, int h, int min, int s);

		// A simple method to dump the time for verification
		virtual std::string dumpTimeString() const;
		// current time
		static CTime now();

		// frient operator
		friend bool operator>(const CTime& t1, const CTime& t2);
	};

	enum class Priority {
		Immediate,
		High,
		Medium,
		Low
	};

private: // Making member variables private is a best practice for encapsulation
	// ---------- Must Valid before the Exsitance of Task
	Priority priority;
	CTime ddl;
	std::string taskDescription;
	// ---------- Must Valid before the Exsitance of Task End

	// ---------- Can be configured later by setters and accessed by getter
	std::string taskTitle;
	std::string details;
	// ---------- Can be configured later by setters and accessed by getter End

public:
	// Constructor to initialize the "Must Valid" members
	Task(Priority p, CTime d, const std::string& desc)
	    : priority(p)
	    , ddl(d)
	    , taskDescription(desc) {
		// do some cases of precheck
		if (CTime::now() > d) {
			throw std::invalid_argument("Invalid Time Settings");
		}
		if (desc.empty()) {
			throw std::invalid_argument("Invalid Task Description");
		}

		// ...
		// Maybe we need to log into the databases...

		// Ok, we have finished our sessions
	}

	// Getters for all members
	Priority getPriority() const {
		return priority;
	}

	CTime getDdl() const {
		return ddl;
	}

	const std::string& getTaskDescription() const {
		return taskDescription;
	}

	const std::string& getTaskTitle() const {
		return taskTitle;
	}

	const std::string& getDetails() const {
		return details;
	}

	// Setters for members that can be configured later
	void setTaskTitle(const std::string& title) {
		taskTitle = title;
	}

	void setDetails(const std::string& d) {
		details = d;
	}
};