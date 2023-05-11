#pragma once
#ifndef IMP_TIMER_H_
#define IMP_TIMER_H_

class ImpTimer
{
public:
	ImpTimer();

	//bắt đầu chạy đếm thgian
	void start();

	int get_ticks();

private:
	//time at started
	int start_tick_;
	//The ticks stored when the timer was paused
	int paused_ticks_;
	
	bool is_paused_;
	bool is_started_;
};

#endif