#include <print>
#include <string>
class Task {
public:
	friend struct Builder; // Open Special Access to the Builder(Base)

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
		std::string to_string() const {
			return std::format("{}-{:02d}-{:02d} {:02d}:{:02d}:{:02d}", year, month, day, hour, minute, second);
		}
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
	// Constructor to initialize the "Must Valid" members
	Task(Priority p, CTime d, const std::string& desc)
	    : priority(p)
	    , ddl(d)
	    , taskDescription(desc) {
	}

public:
	static struct Builder builder();

	std::string dump_formated_task() const;

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

struct Builder {
	std::optional<Task::Priority> m_priority;
	std::optional<Task::CTime> m_ddl;
	std::optional<std::string> m_description;
	std::optional<std::string> m_title;
	std::optional<std::string> m_details;

	// What we need is to ADD Casts instead of modifying codes
	// let all derived constructors to actually construct the members
	struct BuilderMain mainBuilder();
	struct BuilderOptional optional();

	Task build() const {
		if (!m_priority || !m_ddl || !m_description) {
			throw std::runtime_error("Task build error: missing required fields");
		}
		Task t { *m_priority, *m_ddl, *m_description };
		if (m_title)
			t.taskTitle = *m_title;
		if (m_details)
			t.taskDescription = *m_details;
		return t;
	}
};

// Main And Must
struct BuilderMain {
	Builder& b;

	BuilderMain(Builder& base)
	    : b(base) { }

	BuilderMain& withPriority(Task::Priority p) {
		b.m_priority = p;
		return *this;
	}
	BuilderMain& withDdl(const Task::CTime& d) {
		b.m_ddl = d;
		return *this;
	}
	BuilderMain& withDescription(std::string desc) {
		b.m_description = std::move(desc);
		return *this;
	}

	// 结束主阶段，返回 base 供 optional 使用或 build
	Builder& doneMain() {
		return b;
	}
};

// Optional
struct BuilderOptional {
	Builder& b;

	BuilderOptional(Builder& base)
	    : b(base) { }

	BuilderOptional& withTitle(std::string t) {
		b.m_title = std::move(t);
		return *this;
	}
	BuilderOptional& withDetails(std::string d) {
		b.m_details = std::move(d);
		return *this;
	}

	Builder& doneOptional() {
		return b;
	}
};

// Cast Interfaces
inline BuilderMain Builder::mainBuilder() {
	return BuilderMain { *this };
}
inline BuilderOptional Builder::optional() {
	return BuilderOptional { *this };
}

inline Builder Task::builder() {
	return Builder {};
}