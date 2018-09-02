// Job.h

#ifndef _JOB_h
#define _JOB_h

#include <Timer.h>

class Job {
public:
	static Job& getInstance() {
		static Job instance;
		return instance;
	}

	void Start();
	void Stop();
	void Reset();
	void SetDuration(int seconds);
	void Update();

	int RemainingTime;

	bool IsRunning;

private:
	Timer t;
	Job() { }
};

#endif

