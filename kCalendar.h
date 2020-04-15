#ifndef __KCALENDAR__
#define __KCALENDAR__

//Đây là một class dùng kiểu thiết kế hướng đối tượng singleton
struct kJob {
	void (*func)();
	bool (*conditionStop)();
  int intersec_count;

};
class kCalendar {
private:
	long long m_count;
	long long m_lastCheckedJobId;

	kJob *m_jobs;
protected:
	void insertJob(kJob &);
public:
	static kCalendar* getInstance() {
		static kCalendar *instance = new kCalendar();
		return instance;
	}
	
	void initialize();
	
	void startFirstJob();
	
	void update();
	void Delay(float delayTime, void (*func)());
 void addJob(void (*func)(),int intersec);
 void addJob(void (*func)(), bool (*conditionStop)());
};
#endif
